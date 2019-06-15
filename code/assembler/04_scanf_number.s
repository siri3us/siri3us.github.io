.data
scanf_format:
	.string "%d"
printf_format:
	.string "%d\n"


.globl main
.type main, @function
.text
main:
	pushq %rbp
	movq %rsp, %rbp

	subq $0x08, %rsp
	xor %rax, %rax

	movq $scanf_format, %rdi
	movq %rsp, %rsi
	call scanf

	xor %rax, %rax
	movq $printf_format, %rdi
	movq (%rsp), %rsi
	call printf
	addq $0x08, %rsp

	movq $0x01, %rax
	movq $0x00, %rbx
	int $0x80
