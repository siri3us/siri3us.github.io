.globl array
.type array, @object

.data
printf_format:
	.string "%d\n"
array:
	.long 1
	.long 2
	.long 3
	.long 4
	.long 5
array_end:
  .set array_size, (. - array) / 4

.globl main
.type main, @function

.text
main:
	pushq %rbp
	movq %rsp, %rbp

	call double_array
	call print_array

	movq $0x01, %rax
	movq $0x00, %rbx
	int $0x80

double_array:
	pushq %rbp
	movq %rsp, %rbp
  movq $array, %rcx
double_array_iter:
  cmpq $array_end, %rcx
  jnl double_array_end
  movl (%rcx), %eax
  shl %eax
  movl %eax, (%rcx)
  addq $0x04, %rcx
  jmp double_array_iter
double_array_end:
	leave
	ret

print_array:
	pushq %rbp
	movq %rsp, %rbp
	movq $array, %rbx
print_array_element:
	movq $printf_format, %rdi
	xor %rsi, %rsi
	movl (%rbx), %esi
	call printf
	addq $0x04, %rbx
	cmpq $array_end, %rbx
	jl print_array_element
	leave
	ret
