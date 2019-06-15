.data
request_message:
	.string "Enter a number in range (0-255):\n"
scanf_number_format:
	.string "%d"
printf_number_format:
	.string "%5d "
printf_end_of_line:
	.string "\n"

.text
.globl main
.type main, @function

main:
	pushq %rbp
	movq %rsp, %rbp

	// Reading the number
	xor %rax, %rax
	movq $request_message, %rdi
	call printf

	subq $0x08, %rsp
	xor %rax, %rax
	movq $scanf_number_format, %rdi
	movq %rsp, %rsi
	call scanf

	xor %rax, %rax
	xor %rcx, %rcx
	xor %rbx, %rbx
	movq $printf_number_format, %rdi
	movq (%rsp), %rsi
	call printf

	xor %rax, %rax
	movq $printf_end_of_line, %rdi
	call printf

	// If we have read not positive number, exit
	movq (%rsp), %rax
	cmpq $0x00, %rax
	jle end

	// Additional 16 bytes lower
	subq $0x10, %rsp
	movq $0x01, 8(%rsp)
print_table_row:
	movq $0x01, (%rsp)
print_table_row_element:
	movq (%rsp), %rax
	mulq 8(%rsp)

	// Print the number
	movq $printf_number_format, %rdi
	movq %rax, %rsi
	xor %rax, %rax
	call printf

	incq (%rsp)
	movq (%rsp), %rcx
	cmpq 0x10(%rsp), %rcx
  jle print_table_row_element

	movq $printf_end_of_line, %rdi
	xor %rax, %rax
	call printf

	incq 0x08(%rsp)
	movq 0x08(%rsp), %rcx
	cmpq 0x10(%rsp), %rcx
	jle print_table_row

end:
	movq $0x01, %rax
	movq $0x00, %rbx
	int $0x80
