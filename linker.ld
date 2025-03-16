MEMORY
{
	ROM (rx)	: ORIGIN = 0x00000000, LENGTH = 8K
	RAM (rwx)	: ORIGIN = 0x80000000, LENGTH = 8K
}

ENTRY(_start)

SECTIONS
{
	. = 0x00000000;

	.text ALIGN(4):
	{
		_TEXT_START_ROM = .;
		*(.text._start)
		*(.text)
		_TEXT_END_ROM = .;
	} > ROM

	.rodata ALIGN(4):
	{
		_RODATA_START_ROM = .;
		*(.rodata)
		*(.srodata)
		_RODATA_END_ROM = .;
	} > ROM

	.data : ALIGN(4)
	{
		_DATA_START_RAM = .;
		*(.data)
		*(.sdata)
		_DATA_END_RAM = .;
	} > RAM AT> ROM
	_DATA_START_ROM = LOADADDR(.data);
	_DATA_SIZE = _DATA_END_RAM - _DATA_START_RAM;

	.bss : ALIGN(4)
	{
		_BSS_START_RAM = .;
		*(.bss)
		*(.sbss)
		_BSS_END_RAM = .;
	} > RAM AT> ROM
	_BSS_START_ROM = LOADADDR(.bss);
	_BSS_SIZE = _BSS_END_RAM - _BSS_START_RAM;
}
