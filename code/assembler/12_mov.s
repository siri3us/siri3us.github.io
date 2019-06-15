.data
hello_str:
	.string "Hello, string!\n"
	.set hello_str_length, . - hello_str - 1
.text
.globl main
.type main, @function
main:
	movq hello_str, %rax
	movq (hello_str), %rax
	movq $hello_str, %rax
	// movq hello_str_length, %rax      // Segmentation fault
	movq $hello_str_length, %rax

	movq $0x10, %rax
	// movq 0x10, %rax                  // Segmentation fault: trying to read from 0x10

	movq $0x0, %rax
	movq $0x1, %rbx
	int $0x80
