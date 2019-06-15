.globl main
.type main, @function
.globl number

.data
print_format:
	.string "%d\n"
number:
	.long 0xff

.text
main:
	pushq %rbp
	movq %rsp, %rbp
	xor %rsi, %rsi

	movq $0x20, %rcx
	xor %rax, %rax
	movl number, %eax
iter:
	shl %eax
	jb increment
test_iter:
	loop iter
	jmp print_result
increment:
	inc %rsi
	jmp test_iter
print_result:
	movq $print_format, %rdi
	call printf

	movq $0x01, %rax
	movq $0x00, %rbx
	int $0x80
