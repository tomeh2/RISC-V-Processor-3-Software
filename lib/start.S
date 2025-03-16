.align 4

.equ STACK_ADDR, 0x80001000

.globl _start

.align 4
_start:
	li sp, STACK_ADDR
	j main
