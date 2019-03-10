	.file	"addr.c"
	.section	.rodata
.LC0:
	.string	"&arg0: %p \\ arg0: %08x\n"
.LC1:
	.string	"&arg1: %p \\ arg1: %08x\n"
.LC2:
	.string	"&arg2: %p \\ arg2: %08x\n"
.LC3:
	.string	"------------------"
.LC4:
	.string	"%p: %02hhx \n"
.LC5:
	.string	"%p: [esp]\n"
	.text
	.globl	function
	.type	function, @function
function:
.LFB0:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$32, %rsp
	movl	%edi, -20(%rbp)
	movl	%esi, -24(%rbp)
	movl	%edx, -28(%rbp)
	leaq	-20(%rbp), %rax
	addq	$3, %rax
	movq	%rax, -8(%rbp)
	movl	-20(%rbp), %edx
	leaq	-20(%rbp), %rax
	movq	%rax, %rsi
	movl	$.LC0, %edi
	movl	$0, %eax
	call	printf
	movl	-24(%rbp), %edx
	leaq	-24(%rbp), %rax
	movq	%rax, %rsi
	movl	$.LC1, %edi
	movl	$0, %eax
	call	printf
	movl	-28(%rbp), %edx
	leaq	-28(%rbp), %rax
	movq	%rax, %rsi
	movl	$.LC2, %edi
	movl	$0, %eax
	call	printf
	movl	$0, -12(%rbp)
	jmp	.L2
.L4:
	movl	-12(%rbp), %eax
	andl	$3, %eax
	testl	%eax, %eax
	jne	.L3
	movl	$.LC3, %edi
	call	puts
.L3:
	movq	-8(%rbp), %rax
	movzbl	(%rax), %eax
	movsbl	%al, %edx
	movq	-8(%rbp), %rax
	movq	%rax, %rsi
	movl	$.LC4, %edi
	movl	$0, %eax
	call	printf
	subq	$1, -8(%rbp)
	addl	$1, -12(%rbp)
.L2:
	movl	-12(%rbp), %eax
	cmpl	$11, %eax
	jbe	.L4
	movl	$.LC3, %edi
	call	puts
	movq	-8(%rbp), %rax
	movq	%rax, %rsi
	movl	$.LC5, %edi
	movl	$0, %eax
	call	printf
	nop
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE0:
	.size	function, .-function
	.globl	main
	.type	main, @function
main:
.LFB1:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movl	$305419896, %edx
	movl	$65535, %esi
	movl	$16, %edi
	call	function
	movl	$0, %eax
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE1:
	.size	main, .-main
	.ident	"GCC: (Ubuntu 5.4.0-6ubuntu1~16.04.10) 5.4.0 20160609"
	.section	.note.GNU-stack,"",@progbits
