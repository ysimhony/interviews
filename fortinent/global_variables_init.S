	.file	"global_variables_init.cpp"
	.text
#APP
	.globl _ZSt21ios_base_library_initv
	.section	.rodata
.LC0:
	.string	"MyClass constructor\n"
#NO_APP
	.section	.text._ZN7MyClassC2Ev,"axG",@progbits,_ZN7MyClassC5Ev,comdat
	.align 2
	.weak	_ZN7MyClassC2Ev
	.type	_ZN7MyClassC2Ev, @function
_ZN7MyClassC2Ev:
.LFB1989:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movq	%rdi, -8(%rbp)
	leaq	.LC0(%rip), %rax
	movq	%rax, %rsi
	leaq	_ZSt4cout(%rip), %rax
	movq	%rax, %rdi
	call	_ZStlsISt11char_traitsIcEERSt13basic_ostreamIcT_ES5_PKc@PLT
	nop
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE1989:
	.size	_ZN7MyClassC2Ev, .-_ZN7MyClassC2Ev
	.weak	_ZN7MyClassC1Ev
	.set	_ZN7MyClassC1Ev,_ZN7MyClassC2Ev
	.section	.rodata
.LC1:
	.string	"MyClass destructor\n"
	.section	.text._ZN7MyClassD2Ev,"axG",@progbits,_ZN7MyClassD5Ev,comdat
	.align 2
	.weak	_ZN7MyClassD2Ev
	.type	_ZN7MyClassD2Ev, @function
_ZN7MyClassD2Ev:
.LFB1992:
	.cfi_startproc
	.cfi_personality 0x9b,DW.ref.__gxx_personality_v0
	.cfi_lsda 0x1b,.LLSDA1992
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movq	%rdi, -8(%rbp)
	leaq	.LC1(%rip), %rax
	movq	%rax, %rsi
	leaq	_ZSt4cout(%rip), %rax
	movq	%rax, %rdi
	call	_ZStlsISt11char_traitsIcEERSt13basic_ostreamIcT_ES5_PKc@PLT
	nop
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE1992:
	.globl	__gxx_personality_v0
	.section	.gcc_except_table._ZN7MyClassD2Ev,"aG",@progbits,_ZN7MyClassD5Ev,comdat
.LLSDA1992:
	.byte	0xff
	.byte	0xff
	.byte	0x1
	.uleb128 .LLSDACSE1992-.LLSDACSB1992
.LLSDACSB1992:
.LLSDACSE1992:
	.section	.text._ZN7MyClassD2Ev,"axG",@progbits,_ZN7MyClassD5Ev,comdat
	.size	_ZN7MyClassD2Ev, .-_ZN7MyClassD2Ev
	.weak	_ZN7MyClassD1Ev
	.set	_ZN7MyClassD1Ev,_ZN7MyClassD2Ev
	.globl	globalObj
	.bss
	.type	globalObj, @object
	.size	globalObj, 1
globalObj:
	.zero	1
	.section	.rodata
.LC2:
	.string	"In main()\n"
	.text
	.globl	main
	.type	main, @function
main:
.LFB1994:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	leaq	.LC2(%rip), %rax
	movq	%rax, %rsi
	leaq	_ZSt4cout(%rip), %rax
	movq	%rax, %rdi
	call	_ZStlsISt11char_traitsIcEERSt13basic_ostreamIcT_ES5_PKc@PLT
	movl	$0, %eax
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE1994:
	.size	main, .-main
	.type	_Z41__static_initialization_and_destruction_0v, @function
_Z41__static_initialization_and_destruction_0v:
.LFB2501:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	leaq	globalObj(%rip), %rax
	movq	%rax, %rdi
	call	_ZN7MyClassC1Ev
	leaq	__dso_handle(%rip), %rax
	movq	%rax, %rdx
	leaq	globalObj(%rip), %rax
	movq	%rax, %rsi
	leaq	_ZN7MyClassD1Ev(%rip), %rax
	movq	%rax, %rdi
	call	__cxa_atexit@PLT
	nop
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE2501:
	.size	_Z41__static_initialization_and_destruction_0v, .-_Z41__static_initialization_and_destruction_0v
	.section	.rodata
	.type	_ZNSt8__detail30__integer_to_chars_is_unsignedIjEE, @object
	.size	_ZNSt8__detail30__integer_to_chars_is_unsignedIjEE, 1
_ZNSt8__detail30__integer_to_chars_is_unsignedIjEE:
	.byte	1
	.type	_ZNSt8__detail30__integer_to_chars_is_unsignedImEE, @object
	.size	_ZNSt8__detail30__integer_to_chars_is_unsignedImEE, 1
_ZNSt8__detail30__integer_to_chars_is_unsignedImEE:
	.byte	1
	.type	_ZNSt8__detail30__integer_to_chars_is_unsignedIyEE, @object
	.size	_ZNSt8__detail30__integer_to_chars_is_unsignedIyEE, 1
_ZNSt8__detail30__integer_to_chars_is_unsignedIyEE:
	.byte	1
	.text
	.type	_GLOBAL__sub_I_globalObj, @function
_GLOBAL__sub_I_globalObj:
.LFB2502:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	call	_Z41__static_initialization_and_destruction_0v
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE2502:
	.size	_GLOBAL__sub_I_globalObj, .-_GLOBAL__sub_I_globalObj
	.section	.init_array,"aw"
	.align 8
	.quad	_GLOBAL__sub_I_globalObj
	.hidden	DW.ref.__gxx_personality_v0
	.weak	DW.ref.__gxx_personality_v0
	.section	.data.rel.local.DW.ref.__gxx_personality_v0,"awG",@progbits,DW.ref.__gxx_personality_v0,comdat
	.align 8
	.type	DW.ref.__gxx_personality_v0, @object
	.size	DW.ref.__gxx_personality_v0, 8
DW.ref.__gxx_personality_v0:
	.quad	__gxx_personality_v0
	.hidden	__dso_handle
	.ident	"GCC: (Ubuntu 13.3.0-6ubuntu2~24.04) 13.3.0"
	.section	.note.GNU-stack,"",@progbits
	.section	.note.gnu.property,"a"
	.align 8
	.long	1f - 0f
	.long	4f - 1f
	.long	5
0:
	.string	"GNU"
1:
	.align 8
	.long	0xc0000002
	.long	3f - 2f
2:
	.long	0x3
3:
	.align 8
4:
