.globl array
.type array, @object
.data
printf_format:
	.string "%d\n"
array:
	.long 1
	.long 3
	.long 5
	.long 7

.globl main
.type main, @function
.text

main:
	pushq %rbp
	movq %rsp, %rbp

	movq $0x00, %rsi
	movq $0x03, %rcx
iter:
	addl array(,%rcx,4), %esi
	loop iter
	addl array, %esi

	movq $printf_format, %rdi
	call printf

	leave
	ret
