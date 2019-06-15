.data
hello_str:
	.string "Hello, world!\n"
	.set hello_str_length, . - hello_str - 1
.text
.globl main
.type main, @function

main:
	movq $4, %rax
	movq $1, %rbx
	movq $hello_str, %rcx
	movq $hello_str_length, %rdx
	int $0x80
	movq $1, %rax
	movq $0, %rbx
	int $0x80
	.size main, . - main
