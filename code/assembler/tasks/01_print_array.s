.data
printf_format:
	.string "%d\n"
values:
	.long 0x0a, 0x0b, 0x0c, 0x0d
counter:
	.long 0x00

.globl printf_format
.globl values
.globl counter

.text
	.globl main
	.type main, @function
main:
	pushq %rbp
	movq %rsp, %rbp

	movq counter, %rcx
print_array:
	movq values(,%rcx,4), %rsi
	movq $printf_format, %rdi
	call printf

	movl counter, %ecx
	addl $0x01, %ecx
	movl %ecx, counter
	cmpl $0x04, %ecx
	jne print_array

	movq $0x01, %rax
	movq $0x00, %rbx
	int $0x80
