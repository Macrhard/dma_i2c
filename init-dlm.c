/*
	This file includes weak (i.e. optional) functions to perform SoC related
	initialization. They are:
	1). _nds32_init_mem():
		Executed before C language initialization to make memory
		ready so that program data can be initialized. An example
		is to initialize DRAM.
		Since this is called before C initialization, please
		use provided macros to avoid problems.
	2). __soc_init():
		Further SoC intialization. Called after C language
		initialization, so it is a typical C function.
*/

#include <nds32_intrinsic.h>
#include "config.h"

#ifdef CFG_LLINIT
/* This must be a leave function, no child funcion. */
#if GCC_VERSION < 40802
void _nds32_init_mem(void) __attribute__((no_prologue, optimize("Os")));
#else
void _nds32_init_mem(void) __attribute__((naked, optimize("Os")));
#endif

void _nds32_init_mem(void) //The function is weak (optional)
{
#ifndef CFG_AE100
#ifdef USE_DLM
	/* init DLM instead of DRAM */
	//extern char _DLM_BASE;
	//__nds32__mtsr_dsb((unsigned long)&_DLM_BASE|0x1, NDS32_SR_DLMB);
    /* Set DLM base to .data start address and enable it */
	extern char __data_start;
    __nds32__mtsr_dsb((unsigned)&__data_start|1, NDS32_SR_DLMB);
#endif
#endif
}
#endif

void gpio_init(void);

void __soc_init() //The function is weak (optional)
{
#ifdef CFG_LLINIT
	void uart_init(void);
	uart_init();
#endif
	gpio_init();
}
