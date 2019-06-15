.text
.globl main
main:
	push %rbp
	movq %rsp, %rbp
	movq $0x0, %rax
	leave
	ret
