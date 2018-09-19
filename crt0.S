##==============================================================================
##
##  crt0.S
##
##  nds32 startup code
##
##==============================================================================
##
## Copyright (c) 1995, 1996, 1997, 1998 Cygnus Solutions
##
## The authors hereby grant permission to use, copy, modify, distribute,
## and license this software and its documentation for any purpose, provided
## that existing copyright notices are retained in all copies and that this
## notice is included verbatim in any distributions. No written agreement,
## license, or royalty fee is required for any of the authorized uses.
## Modifications to this software may be copyrighted by their authors
## and need not follow the licensing terms described here, provided that
## the new terms are clearly indicated on the first page of each file where
## they apply.
##

#include <nds32_init.inc>
#include "config.h"
#include "interrupt.h"

##------------------------------------------------------------------------------
	.macro vector name
	.align 2
	j OS_Trap_\name
	.endm

	.macro OS_Trap_Interrupt_HW num
OS_Trap_Interrupt_HW\num:
	push $r0
	li  $r0, \num
	b   common_ISR_wrapper
	.endm

	.macro LED x
	hal_set_led \x
	.endm

	.section .nds32_init, "ax"
!========================================================================
! Vector table
!========================================================================
	.align 2
exception_vector:
	j _start                    !  (0) Trap Reset
	vector TLB_Fill             !  (1) Trap TLB fill
	vector PTE_Not_Present      !  (2) Trap PTE not present
	vector TLB_Misc             !  (3) Trap TLB misc
	vector TLB_VLPT_Miss        !  (4) Trap TLB VLPT miss
	vector Machine_Error        !  (5) Trap Machine error
	vector Debug_Related        !  (6) Trap Debug related
	vector General_Exception    !  (7) Trap General exception
	vector Syscall              !  (8) Syscall

	/* HW interrupt vector layout */
	//hal_hw_vectors
        vector Interrupt_UNDEF   //  (9) Interrupt HW0
        vector Interrupt_UNDEF   // (10) Interrupt HW1
        vector Interrupt_HW2     // (11) Interrupt HW2 (PIT)
        vector Interrupt_UNDEF   // (12) Interrupt HW3
        vector Interrupt_UNDEF   // (13) Interrupt HW4
        vector Interrupt_UNDEF   // (14) Interrupt HW5
        vector Interrupt_HW6     // (15) Interrupt HW6 (GPIO)
        vector Interrupt_UNDEF   // (16) Interrupt HW7
        vector Interrupt_UNDEF   // (17) Interrupt HW8
        vector Interrupt_HW9     // (18) Interrupt HW9 (DMA)
        vector Interrupt_UNDEF   // (19) Interrupt HW10
        vector Interrupt_HW11    // (20) Interrupt HW11 (SWI)
        vector Interrupt_UNDEF   // (21) Interrupt HW12
        vector Interrupt_UNDEF   // (22) Interrupt HW13
        vector Interrupt_UNDEF   // (23) Interrupt HW14
        vector Interrupt_UNDEF   // (24) Interrupt HW15
        vector Interrupt_UNDEF   // (25) Interrupt HW16
        vector Interrupt_UNDEF   // (26) Interrupt HW17
        vector Interrupt_UNDEF   // (27) Interrupt HW18
        vector Interrupt_UNDEF   // (28) Interrupt HW19
        vector Interrupt_UNDEF   // (29) Interrupt HW20
        vector Interrupt_UNDEF   // (30) Interrupt HW21
        vector Interrupt_UNDEF   // (31) Interrupt HW22
        vector Interrupt_UNDEF   // (32) Interrupt HW23
        vector Interrupt_UNDEF   // (33) Interrupt HW24
        vector Interrupt_UNDEF   // (34) Interrupt HW25
        vector Interrupt_UNDEF   // (35) Interrupt HW26
        vector Interrupt_UNDEF   // (36) Interrupt HW27
        vector Interrupt_UNDEF   // (37) Interrupt HW28
        vector Interrupt_UNDEF   // (38) Interrupt HW29
        vector Interrupt_UNDEF   // (39) Interrupt HW30
        vector Interrupt_UNDEF   // (40) Interrupt HW31


	.align  2
exception_vector_end:
exception_handler:
	.long tlb_exception_handler
	.long error_exception_handler
	.long syscall_handler
ISR_TABLE:
	.long HW0_ISR
	.long HW1_ISR
	.long HW2_ISR
	.long HW3_ISR
	.long HW4_ISR
	.long HW5_ISR
	.long HW6_ISR
	.long HW7_ISR
	.long HW8_ISR
	.long HW9_ISR
	.long HW10_ISR
	.long HW11_ISR
	.long HW12_ISR
	.long HW13_ISR
	.long HW14_ISR
	.long HW15_ISR
	.long HW16_ISR
	.long HW17_ISR
	.long HW18_ISR
	.long HW19_ISR
	.long HW20_ISR
	.long HW21_ISR
	.long HW22_ISR
	.long HW23_ISR
	.long HW24_ISR
	.long HW25_ISR
	.long HW26_ISR
	.long HW27_ISR
	.long HW28_ISR
	.long HW29_ISR
	.long HW30_ISR
	.long HW31_ISR
/*
 * exception handlers
 */

/*----------------------------------------------------------------------
   Since N903 doesn't have MMU, make them share the common error handler.
----------------------------------------------------------------------*/
OS_Trap_TLB_Fill:
/*
	SAVE_ALL
	li  $r0, #0x1
	b   tlb_exception_handler
*/

OS_Trap_PTE_Not_Present:
/*
	SAVE_ALL
	li  $r0, #0x2
	b   tlb_exception_handler
*/

OS_Trap_TLB_Misc:
/*
	SAVE_ALL
	li  $r0, #0x3
	b   tlb_exception_handler
*/

OS_Trap_TLB_VLPT_Miss:
1:  b   1b
	SAVE_ALL
//	li  $r0, #0x4
	b   tlb_exception_handler

OS_Trap_Machine_Error:
1:  b   1b
	SAVE_ALL
	li  $r0, #0x5
	b   error_exception_handler

OS_Trap_Debug_Related:
1:  b   1b
	SAVE_ALL
	li  $r0, #0x6
	b   error_exception_handler

OS_Trap_General_Exception:
1:  b   1b
	SAVE_ALL
	li  $r0, #0x7
	b   error_exception_handler

OS_Trap_Syscall:
	SYSCALL_SAVE_ALL
	bal syscall_handler
	SYSCALL_RESTORE_ALL
	iret

common_ISR_wrapper:
	SAVE_ALL_HW
	la  $r1, ISR_TABLE
	lw  $r1, [$r1+$r0<<2]
	jral $r1
	RESTORE_ALL_HW
	iret

OS_Trap_Interrupt_UNDEF:
	push $r0
	li  $r0, 0xff
	b    common_ISR_wrapper

	/* Other HW interrupt handlers */
	//hal_hw_ISR
    Os_Trap_Interrupt_HW    IRQ_PIT
    Os_Trap_Interrupt_HW    IRQ_GPIO
    Os_Trap_Interrupt_HW    IRQ_SWI
    Os_Trap_Interrupt_HW    IRQ_DMA

##------------------------------------------------------------------------------
## Startup code

	.section .text
	.global _start
	.weak _call_exit
	.weak _SDA_BASE_
	.func _start
	.type _start, @function

	.align 2
_start:
	! Please don't modify this code
	! Initialize the registers used by the compiler
	nds32_init              ! NDS32 startup initial macro in <nds32_init.inc>

#ifndef __NDS32_ISA_V3M__
_i:
	mfsr  $r0, $ICM_CFG     ! $r0 = ICM_CFG
	andi  $r0, $r0, 0x1c0   ! $r0 = $r0 & 0x1c0 , take ISZ
	beqz  $r0, _d           ! if no I-Cache, jump to _d

	mfsr  $r0, $CACHE_CTL
	bclr  $r0, $r0, 0
	mtsr  $r0, $CACHE_CTL	! disable I cache

_d:
	mfsr  $r1, $DCM_CFG     ! $r1 = DCM_CFG
	andi  $r1, $r1, 0x1c0   ! $r1 = $r1 & 0x1c0 , take DSZ
	beqz  $r1, _finish      ! if no D-Cache, jump to _finish

	mfsr  $r1, $CACHE_CTL
	bclr  $r1, $r1, 1
	mtsr  $r1, $CACHE_CTL	! disable D cache

_finish:
#endif

#ifdef CFG_LLINIT
	bal _nds32_init_mem
#endif
	bal __init
	bal main
1:  b   1b

	.size _start, .-_start

	.end
