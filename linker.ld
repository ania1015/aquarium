MEMORY
{
	FLASH(rx):ORIGIN =0x08000000, LENGTH =256K
	RAM(rwx):ORIGIN =0x20000000, LENGTH =48K
}

ENTRY(ResetHandler);

SECTIONS
{ 
	.text : 
	{ 
		*(.isr_vector)
		*(.text)
		*(.rodata)
		. = ALIGN(4);
		_end_of_text = .; 
	}>FLASH

	.data :
	{
		_s_data = LOADADDR(.data);
		_start_of_data = .;
		*(.data)
		. = ALIGN(4);
		_end_of_data = .;
	}> RAM AT> FLASH

	 .bss :
	{
		__bss_start__ = .;
		_start_bss = .;
		*(.bss)
		. = ALIGN(4);
		_end_bss = .;
		__bss_end__ = .;

	}
}
