	.file	"03_string_interning.cpp"
	.intel_syntax noprefix
	.text
	.section	.rodata
.LC0:
	.string	"Hello, world!"
	.text
	.globl	_Z15PrintHelloWorldv
	.type	_Z15PrintHelloWorldv, @function
_Z15PrintHelloWorldv:
.LFB0:
	.cfi_startproc
	push	rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	mov	rbp, rsp
	.cfi_def_cfa_register 6
	mov	edi, OFFSET FLAT:.LC0
	call	puts
	nop
	pop	rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE0:
	.size	_Z15PrintHelloWorldv, .-_Z15PrintHelloWorldv
	.section	.rodata
.LC1:
	.string	"world!"
	.text
	.globl	_Z10PrintWorldv
	.type	_Z10PrintWorldv, @function
_Z10PrintWorldv:
.LFB1:
	.cfi_startproc
	push	rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	mov	rbp, rsp
	.cfi_def_cfa_register 6
	mov	edi, OFFSET FLAT:.LC1
	call	puts
	nop
	pop	rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE1:
	.size	_Z10PrintWorldv, .-_Z10PrintWorldv
	.globl	main
	.type	main, @function
main:
.LFB2:
	.cfi_startproc
	push	rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	mov	rbp, rsp
	.cfi_def_cfa_register 6
	call	_Z15PrintHelloWorldv
	call	_Z10PrintWorldv
	mov	eax, 0
	pop	rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE2:
	.size	main, .-main
	.ident	"GCC: (Ubuntu 7.3.0-21ubuntu1~16.04) 7.3.0"
	.section	.note.GNU-stack,"",@progbits
