	.text
	.def	 output;
	.scl	2;
	.type	32;
	.endef
	.globl	output
	.p2align	4, 0x90
output:                                 # @output
.Lcfi0:
.seh_proc output
# BB#0:                                 # %entry
	subq	$56, %rsp
.Lcfi1:
	.seh_stackalloc 56
.Lcfi2:
	.seh_endprologue
	movq	%rcx, 48(%rsp)
	movq	48(%rsp), %rcx
	callq	printf
	movl	%eax, 44(%rsp)          # 4-byte Spill
	addq	$56, %rsp
	retq
	.seh_handlerdata
	.text
.Lcfi3:
	.seh_endproc

	.def	 printf;
	.scl	2;
	.type	32;
	.endef
	.section	.text,"xr",discard,printf
	.globl	printf
	.p2align	4, 0x90
printf:                                 # @printf
.Lcfi4:
.seh_proc printf
# BB#0:                                 # %entry
	subq	$72, %rsp
.Lcfi5:
	.seh_stackalloc 72
.Lcfi6:
	.seh_endprologue
	movq	%r9, 104(%rsp)
	movq	%r8, 96(%rsp)
	movq	%rdx, 88(%rsp)
	movq	%rcx, 64(%rsp)
	leaq	88(%rsp), %rcx
	movq	%rcx, 48(%rsp)
	movq	48(%rsp), %r9
	movq	64(%rsp), %rdx
	movl	$1, %ecx
	movq	%r9, 40(%rsp)           # 8-byte Spill
	movq	%rdx, 32(%rsp)          # 8-byte Spill
	callq	__acrt_iob_func
	xorl	%ecx, %ecx
	movl	%ecx, %r8d
	movq	%rax, %rcx
	movq	32(%rsp), %rdx          # 8-byte Reload
	movq	40(%rsp), %r9           # 8-byte Reload
	callq	_vfprintf_l
	movl	%eax, 60(%rsp)
	movl	60(%rsp), %eax
	addq	$72, %rsp
	retq
	.seh_handlerdata
	.section	.text,"xr",discard,printf
.Lcfi7:
	.seh_endproc

	.def	 _vfprintf_l;
	.scl	2;
	.type	32;
	.endef
	.section	.text,"xr",discard,_vfprintf_l
	.globl	_vfprintf_l
	.p2align	4, 0x90
_vfprintf_l:                            # @_vfprintf_l
.Lcfi8:
.seh_proc _vfprintf_l
# BB#0:                                 # %entry
	subq	$104, %rsp
.Lcfi9:
	.seh_stackalloc 104
.Lcfi10:
	.seh_endprologue
	movq	%r9, 96(%rsp)
	movq	%r8, 88(%rsp)
	movq	%rdx, 80(%rsp)
	movq	%rcx, 72(%rsp)
	movq	96(%rsp), %rcx
	movq	88(%rsp), %r9
	movq	80(%rsp), %r8
	movq	72(%rsp), %rdx
	movq	%rcx, 64(%rsp)          # 8-byte Spill
	movq	%r9, 56(%rsp)           # 8-byte Spill
	movq	%r8, 48(%rsp)           # 8-byte Spill
	movq	%rdx, 40(%rsp)          # 8-byte Spill
	callq	__local_stdio_printf_options
	movq	(%rax), %rcx
	movq	40(%rsp), %rdx          # 8-byte Reload
	movq	48(%rsp), %r8           # 8-byte Reload
	movq	56(%rsp), %r9           # 8-byte Reload
	movq	64(%rsp), %rax          # 8-byte Reload
	movq	%rax, 32(%rsp)
	callq	__stdio_common_vfprintf
	nop
	addq	$104, %rsp
	retq
	.seh_handlerdata
	.section	.text,"xr",discard,_vfprintf_l
.Lcfi11:
	.seh_endproc

	.def	 __local_stdio_printf_options;
	.scl	2;
	.type	32;
	.endef
	.section	.text,"xr",discard,__local_stdio_printf_options
	.globl	__local_stdio_printf_options
	.p2align	4, 0x90
__local_stdio_printf_options:           # @__local_stdio_printf_options
# BB#0:                                 # %entry
	leaq	"?_OptionsStorage@?1??__local_stdio_printf_options@@9@4_KA"(%rip), %rax
	retq

	.section	.bss,"bw",discard,"?_OptionsStorage@?1??__local_stdio_printf_options@@9@4_KA"
	.globl	"?_OptionsStorage@?1??__local_stdio_printf_options@@9@4_KA" # @"\01?_OptionsStorage@?1??__local_stdio_printf_options@@9@4_KA"
	.p2align	3
"?_OptionsStorage@?1??__local_stdio_printf_options@@9@4_KA":
	.quad	0                       # 0x0

	.section	.drectve,"yn"
	.ascii	" /FAILIFMISMATCH:\"_CRT_STDIO_ISO_WIDE_SPECIFIERS=0\""

