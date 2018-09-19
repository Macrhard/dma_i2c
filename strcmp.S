#include "config.h"

#ifdef	__NDS32_STRCMP__
	.section .mdebug.abi_nds32
	.previous
	! frame size: 0, push regs size: 0, outgoing args size: 0
	.text
	.align	2
	.globl	strcmp
	.func	strcmp
	.type	strcmp, @function
strcmp:
L1:
    lmwzb.bm $r2,[$r0],$r2,#0x0
    lmwzb.bm $r3,[$r1],$r3,#0x0
    ffzmism $r2,$r2,$r3
    beqz $r2,L1
    lb $r3,[$r0+($r2<<#0x0)]
    lb $r2,[$r1+($r2<<#0x0)]
    sub $r0,$r3,$r2
    ret $lp
	.endfunc	! strcmp
	.size	strcmp, .-strcmp
#endif
