#include <stdint.h>
#include "main.h"
#include "delay.h"
#include "oneWire.h"
#include "ReadingWriting.h"
#include "usart.h"
#include "tim2.h"
#include "regulator.h"

void enableIRQ(void);
void disableIRQ(void);

static unsigned int read = 0;
static float k1 = 0;
static float k2 = 0;
static float w = 0;
static unsigned int tab[9] = {0};
static float y = 0;
static unsigned int u = 0;
static unsigned int er = 0;

unsigned int EskperymentPrzekaznikowyHistereza(float y, float w)
{
        float e = w - y;
        static unsigned int duty = 0;
        if(e <= -1)
        {
                duty = 0;
        }
        else if (e >= 1)
        {
                duty = 1;
        }
        return duty;
}

void set_nastawy(float zk1, float zk2)
{
       disableIRQ();
	k1 = zk1;
	k2 = zk2;
       enableIRQ();
}
void set_w(float wz)
{
       disableIRQ();
	w = wz;
       enableIRQ();
}

int main(void){
	disableIRQ();
	uint32_t x;
	//Range 2 to range 1
	x=ReadPort(PWR_CR1);
	x|=0x100;
	WritePin(PWR_CR1, x);
	
	//flash latency to 2 for 48mhz
	//clk en 
	x = ReadPort(RCC_AHB1ENR);
	x |= (1 << 8);
	WritePin(RCC_AHB1ENR, x);

	//change  to 2WS
	x=ReadPort(FLASH_ACR);
	x&=~0x7;
	x|=0x2;
	WritePin(FLASH_ACR, x);

	//msirregel
	x=ReadPort(RCC_CR);
	x|=0x8;
	WritePin(RCC_CR, x);

	//change freq
	x=ReadPort(RCC_CR);
	x&=~0xF0;
	x|=0x90;
 	WritePin(RCC_CR, x);

	SysTick_Initialization();

	//port b,a enable 
	x = ReadPort(RCC_AHB2ENR);
	x |= RCC_PBEN;
	WritePin(RCC_AHB2ENR, x);

	x = ReadPort(RCC_AHB2ENR);
	x |= RCC_PAEN;
	WritePin(RCC_AHB2ENR, x);

	x = ReadPort(GPIOA_MODER);
	x &= 0xFFFF3FFF;//(1 << 6 & 1 << 7) ;
	x |= (1 << 14);
	WritePin(GPIOA_MODER, x);

	//type open drain setting 
	x = ReadPort(GPIOA_OTYPER);
	x |= (ONE_WIRE);
	WritePin(GPIOA_OTYPER, x);

	//Alternate Fun 
	x = ReadPort(GPIOA_AFRL);
	//x &= ~0xF;
	x |= 0x1;//(1<<4 || 1<<5 || 1<<6);
	WritePin(GPIOA_AFRL, x);

	// PA0 TIM_CH1 
	x = ReadPort(GPIOA_MODER);
	x &= 0xFFFFFFFC;// 0 i 1 równe 0
	x |= (1 << 1);
	WritePin(GPIOA_MODER, x);

	x = ReadPort(GPIOA_OTYPER);
	x &= ~(1 << 0);
	WritePin(GPIOA_OTYPER, x);

	Tim2_Initialization();


	UsartInitialize();


	setDutyPWM(0);  
	
	w = 28.5;
	
	przeliczNastawy(999,200,8.375,&k1,&k2);
	static int lr = -1;
	static unsigned char req[15] = {0};
	unsigned char c = 0;
	int ret = 0;
	unsigned int t_w = w*10;
	unsigned int t_k1 = k1*100;
	int t_k2 = k2*100;
	enableIRQ(); 
	while(1){
		
		if(read == 1)
		{

			printByte((unsigned int)y>> 8);
			printByte((unsigned int)y >> 0);
			disp_char(' ');
			printByte(u>>16);
			printByte(u>>8);
			printByte(u>>0);
			disp_char(' ');
			
			t_w = w*16;
			printByte(t_w>>16);
			printByte(t_w>>8);
			printByte(t_w>>0);
			
			t_k1 = k1 * 100;
			t_k2 = k2 * 100;
			disp_char(' ');
			printByte(t_k1>>8);
			printByte(t_k1>>0);
			
			disp_char(' ');
			printByte(t_k2>>8);
			printByte(t_k2>>0);
			disp_char(' ');
			printByte(er>>8);
			printByte(er>>0);
			
			disp_char(' ');
			for(int i = 1; i >=0 ; i--)
			{
				printByte(tab[i]);
			}
			nextLine();
			

			read=0;
		}
		
		if(ReadPin(USART_ISR, 5) == 1)
		{
			c =  UartRead();
			if( c != 13 && lr < 14 ){ 
				lr++;
				req[lr] =c;
			} else{
				PrzetworzDane(req, lr);
				lr = -1;
				for(unsigned int i = 0; i < 15; i++){
					req[i] = 0;
				}

			}
		}

	
	}
	return 0;
}


unsigned int take_line_buf(int N, unsigned char *r, unsigned int * n){
	unsigned int id = 0;
        for(unsigned int i = 1; i <= N; i++){
		if(r[i] >= '0' || r[i] <= '9' || r[i] == ' '){
			n[i-1] = char2num(r[i]);
			if(r[i] == ' ')
			 id = i-1;
		 }
		 else
			return 0;
	}
	return id;
}

unsigned int odbior_nastaw(int L, int H, unsigned int* n){

	unsigned int z = 0;
	unsigned int d = 1;
	for(int i = H; i > L; i--){
		 z += n[i]*d;
		 d *= 10;
	 }
	return z;
}

unsigned int PrzetworzDane(unsigned char* r, int l){
	unsigned int id = 0;
	float kp = 0;
	float Ti = 0;
	float wz= 0;
	float zk1 = 0;
	float zk2 = 0;

	unsigned int n[11] = {0};
	if(r[0] == 'w'){
		
		id = take_line_buf(l, r, n);
		
                wz = (odbior_nastaw(-1, l-1, n))*0.001; //kwant to 1 mC
		
		set_w(wz);		

                wz = 0;

        } else if(r[0] == 'n'){
		
                
		id = take_line_buf(l, r, n);

                if(id == 0){
                        return 0; //nie ma 2 nastaw
                } else {
                        Ti = (odbior_nastaw(id, l-1, n)); //kwant to 1
                        kp = (odbior_nastaw(-1, id-1, n))*0.0001; //kwant to 0.0001
			przeliczNastawy(Ti, 200, kp, &zk1, &zk2);
			set_nastawy(zk1,zk2);
		       Ti = 0;
		       kp = 0;
                }


        } else{
                return 0;
        }

        return 0;
}



void _exit(int status){
	while(1);
}

void enableIRQ(void)
{
	__asm__ __volatile__("cpsie i":::"memory","cc");
}

void disableIRQ(void)
{
	__asm__ __volatile__("cpsid i":::"memory","cc");
}

void TIM2Handler(void){	
	// pierwse wartosci ustawione sa dla ccr1i i ccr2 w tim2 tu wejda dopiero jak bedzie przerwanie
	static unsigned int x2 = 1;
	unsigned int s;
	static unsigned int T = 0;
	s = ReadPort(TIM2_SR);
	if((s & 4) != 0){
		reqTemp();
	}
	if((s & 8) != 0) {
		
		readTemp(tab, 9);
		T += tab2num(tab,2);
		
		x2 += 1000;
		
		if(x2 >= 100000){
			x2 = 0;
		 	y = (16*T + 50)/100;
			float duty = RegulatorPIsprzet((1/256.0)*y,w,k1,k2); 
			duty = duty * 100000;	
			duty = (unsigned int)duty;
			u = duty;
			setDutyPWM(duty);
			T = 0;
			read = 1;
		}
    		WritePin(TIM2_CCR2, x2 + 255);	
    		WritePin(TIM2_CCR3, x2 + 255 + 500);	

    		
	}
	WritePin(TIM2_SR, ~s);
}

void reqTemp(void)
{
	OneWireInitialization(ONE_WIRE_PIN_NR, GPIOA_BSRR, GPIOA_IDR);
	WriteByte(0xCC,ONE_WIRE_PIN_NR, GPIOA_BSRR);
	WriteByte(0x44,ONE_WIRE_PIN_NR, GPIOA_BSRR);
}

void readTemp(unsigned int *tab, int n)
{
	static unsigned int addErr = 0;
	OneWireInitialization(ONE_WIRE_PIN_NR, GPIOA_BSRR, GPIOA_IDR);
	WriteByte(0xCC,ONE_WIRE_PIN_NR, GPIOA_BSRR);
	WriteByte(0xBE,ONE_WIRE_PIN_NR, GPIOA_BSRR);
	ReadnBytes(tab,n, ONE_WIRE_PIN_NR, GPIOA_BSRR, GPIOA_IDR);
	if(crcCheck(9, tab) != 0) 
	{
		addErr++;
		er =addErr;
		OneWireInitialization(ONE_WIRE_PIN_NR, GPIOA_BSRR, GPIOA_IDR);
		WriteByte(0xCC,ONE_WIRE_PIN_NR, GPIOA_BSRR);
		WriteByte(0xBE,ONE_WIRE_PIN_NR, GPIOA_BSRR);
		ReadnBytes(tab,n, ONE_WIRE_PIN_NR, GPIOA_BSRR, GPIOA_IDR);
	}
}
