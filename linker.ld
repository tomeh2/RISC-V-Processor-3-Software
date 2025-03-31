MEMORY
{
	ROM (rx)	: ORIGIN = 0x00000000, LENGTH = 16K
	RAM (rwx)	: ORIGIN = 0x80000000, LENGTH = 128K
}

ENTRY(_start)

_ROM_START = ORIGIN(ROM);
_ROM_SIZE = LENGTH(ROM);
_RAM_START = ORIGIN(RAM);
_RAM_SIZE = LENGTH(RAM);

_STACK_INIT_ADDR = _RAM_START + _RAM_SIZE / 2;

_HEAP_START = _STACK_INIT_ADDR;
_HEAP_SIZE = _RAM_SIZE / 2;

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
