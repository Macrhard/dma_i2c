#include <nds32_intrinsic.h>
#include "config.h"

/* It will use Default_Handler if you don't have one */
#pragma weak tlb_exception_handler   = Default_Handler
#pragma weak error_exception_handler = Default_Handler
#pragma weak syscall_handler         = Default_Handler
#pragma weak HW0_ISR   = Default_Handler
#pragma weak HW1_ISR   = Default_Handler
#pragma weak HW2_ISR   = Default_Handler
#pragma weak HW3_ISR   = Default_Handler
#pragma weak HW4_ISR   = Default_Handler
#pragma weak HW5_ISR   = Default_Handler
#pragma weak HW6_ISR   = Default_Handler
#pragma weak HW7_ISR   = Default_Handler
#pragma weak HW8_ISR   = Default_Handler
#pragma weak HW9_ISR   = Default_Handler
#pragma weak HW10_ISR  = Default_Handler
#pragma weak HW11_ISR  = Default_Handler
#pragma weak HW12_ISR  = Default_Handler
#pragma weak HW13_ISR  = Default_Handler
#pragma weak HW14_ISR  = Default_Handler
#pragma weak HW15_ISR  = Default_Handler
#pragma weak HW16_ISR  = Default_Handler
#pragma weak HW17_ISR  = Default_Handler
#pragma weak HW18_ISR  = Default_Handler
#pragma weak HW19_ISR  = Default_Handler
#pragma weak HW20_ISR  = Default_Handler
#pragma weak HW21_ISR  = Default_Handler
#pragma weak HW22_ISR  = Default_Handler
#pragma weak HW23_ISR  = Default_Handler
#pragma weak HW24_ISR  = Default_Handler
#pragma weak HW25_ISR  = Default_Handler
#pragma weak HW26_ISR  = Default_Handler
#pragma weak HW27_ISR  = Default_Handler
#pragma weak HW28_ISR  = Default_Handler
#pragma weak HW29_ISR  = Default_Handler
#pragma weak HW30_ISR  = Default_Handler
#pragma weak HW31_ISR  = Default_Handler
#pragma weak SW0_ISR   = Default_Handler
#pragma weak VEP0_ISR  = Default_Handler
#pragma weak VEP1_ISR  = Default_Handler
#pragma weak VEP2_ISR  = Default_Handler
#pragma weak VEP3_ISR  = Default_Handler
#pragma weak VEP4_ISR  = Default_Handler
#pragma weak VEP5_ISR  = Default_Handler
#pragma weak VEP6_ISR  = Default_Handler
#pragma weak VEP7_ISR  = Default_Handler
#pragma weak VEP8_ISR  = Default_Handler
#pragma weak VEP9_ISR  = Default_Handler
#pragma weak VEP10_ISR = Default_Handler
#pragma weak VEP11_ISR = Default_Handler
#pragma weak VEP12_ISR = Default_Handler
#pragma weak VEP13_ISR = Default_Handler
#pragma weak VEP14_ISR = Default_Handler
#pragma weak VEP15_ISR = Default_Handler
#pragma weak VEP16_ISR = Default_Handler
#pragma weak VEP17_ISR = Default_Handler
#pragma weak VEP18_ISR = Default_Handler
#pragma weak VEP19_ISR = Default_Handler
#pragma weak VEP20_ISR = Default_Handler
#pragma weak VEP21_ISR = Default_Handler
#pragma weak VEP22_ISR = Default_Handler
#pragma weak VEP23_ISR = Default_Handler
#pragma weak VEP24_ISR = Default_Handler
#pragma weak VEP25_ISR = Default_Handler
#pragma weak VEP26_ISR = Default_Handler
#pragma weak VEP27_ISR = Default_Handler
#pragma weak VEP28_ISR = Default_Handler
#pragma weak VEP29_ISR = Default_Handler
#pragma weak VEP30_ISR = Default_Handler
#pragma weak VEP31_ISR = Default_Handler
#pragma weak VEP32_ISR = Default_Handler
#pragma weak VEP33_ISR = Default_Handler
#pragma weak VEP34_ISR = Default_Handler
#pragma weak VEP35_ISR = Default_Handler
#pragma weak VEP36_ISR = Default_Handler
#pragma weak VEP37_ISR = Default_Handler
#pragma weak VEP38_ISR = Default_Handler
#pragma weak VEP39_ISR = Default_Handler
#pragma weak VEP40_ISR = Default_Handler
#pragma weak VEP41_ISR = Default_Handler
#pragma weak VEP42_ISR = Default_Handler
#pragma weak VEP43_ISR = Default_Handler
#pragma weak VEP44_ISR = Default_Handler
#pragma weak VEP45_ISR = Default_Handler
#pragma weak VEP46_ISR = Default_Handler
#pragma weak VEP47_ISR = Default_Handler
#pragma weak VEP48_ISR = Default_Handler
#pragma weak VEP49_ISR = Default_Handler
#pragma weak VEP50_ISR = Default_Handler
#pragma weak VEP51_ISR = Default_Handler
#pragma weak VEP52_ISR = Default_Handler
#pragma weak VEP53_ISR = Default_Handler
#pragma weak VEP54_ISR = Default_Handler
#pragma weak VEP55_ISR = Default_Handler
#pragma weak VEP56_ISR = Default_Handler
#pragma weak VEP57_ISR = Default_Handler
#pragma weak VEP58_ISR = Default_Handler
#pragma weak VEP59_ISR = Default_Handler
#pragma weak VEP60_ISR = Default_Handler
#pragma weak VEP61_ISR = Default_Handler
#pragma weak VEP62_ISR = Default_Handler
#pragma weak VEP63_ISR = Default_Handler

#define NDS32_ISET          (0x07 << 0)
#define NDS32_IWAY          (0x07 << 3)
#define NDS32_ISIZE         (0x07 << 6)
#define NDS32_DSET          (0x07 << 0)
#define NDS32_DWAY          (0x07 << 3)
#define NDS32_DSIZE         (0x07 << 6)

unsigned int iset, iway, isize;
unsigned int dset, dway, dsize;

int puts(const char *);

__attribute__((unused))
static void Default_Handler()
{
	puts("Default Handler");
	while (1) ;
}

#pragma weak _nds32_init_mem = __null_function
#pragma weak __soc_init = __null_function

void __null_function()
{;
}

void __c_init()
{
/* Use compiler builtin memcpy and memset */
#define MEMCPY(des, src, n) __builtin_memcpy ((des), (src), (n))
#define MEMSET(s, c, n) __builtin_memset ((s), (c), (n))

	extern char _end;
	extern char __bss_start;
	int size;

	/* If we load code to RAM we don't need to copy
	 * data section and lma will be equal to vma.
	 * */
#if defined(CFG_LLINIT) && !defined(CFG_REMAP) && !defined(CFG_SIMU)
	/* data section will be copied before we remap.
	 * We don't need to copy data section here. */
	extern char __data_lmastart;
	extern char __data_start;
	extern char __data_end;

	/* Copy data section to RAM */
	size = &__data_end - &__data_start;
	MEMCPY(&__data_start, &__data_lmastart, size);

#endif
	/* Clear bss section */
	size = &_end - &__bss_start;
	MEMSET(&__bss_start, 0, size);
	return;
}

void __attribute__ ((optimize("Os"))) __cpu_init()
{
	unsigned int tmp,MMPV;
	extern char _SEG0_BASE;
	extern char _SEG0_END;
	extern char _SEG1_BASE;
	extern char _SEG1_END;

#if defined(__NDS32_ISA_V3__)
	/* turn on BTB, trun off TCM  */
	tmp = 0x1<<3;
#else
	/* turn on BTB */
	tmp = 0x0;
#endif

	__nds32__mtsr(tmp, NDS32_SR_MISC_CTL);

	/* For AE100 to set IVB base address for load mode*/
	HAL_SET_SMU();

	/* disable all hardware interrupts */
	__nds32__mtsr(0x0, NDS32_SR_INT_MASK);
#if (defined(__NDS32_ISA_V3M__) || defined(__NDS32_ISA_V3__))
	if (__nds32__mfsr(NDS32_SR_IVB) & 0x01)
		__nds32__mtsr(0x0, NDS32_SR_INT_MASK);
#endif

	tmp = __nds32__mfsr(NDS32_SR_IVB) & 0xFFFF0000;
#if defined(CFG_EVIC)
	/* set EVIC, vector size: 4 bytes, base: 0x0 */
	__nds32__mtsr(tmp|0x1<<13, NDS32_SR_IVB);
#else
# if defined(USE_C_EXT)
	/* If we use v3/v3m toolchain and want to use
	 * C extension please use USE_C_EXT in CFLAGS
	 */
#ifdef __NDS32_ISA_V3__
	/* set IVIC, vector size: 4 bytes, base: 0x0 */
	__nds32__mtsr(tmp, NDS32_SR_IVB);
#else
	/* set IVIC, vector size: 16 bytes, base: 0x0 */
	__nds32__mtsr(tmp|0x1<<14, NDS32_SR_IVB);
#endif
# else
	/* set IVIC, vector size: 4 bytes, base: 0x0
	 * If we use v3/v3m toolchain and want to use
	 * assembly version please don't use USE_C_EXT
	 * in CFLAGS */
	__nds32__mtsr(tmp, NDS32_SR_IVB);
# endif
#endif
	/* Set PSW INTL to 0 */
	tmp = __nds32__mfsr(NDS32_SR_PSW);
	tmp = tmp & 0xfffffff9;
#if (defined(__NDS32_ISA_V3M__) || defined(__NDS32_ISA_V3__))
	/* Set PSW CPL to 7 to allow any priority */
	tmp = tmp | 0x70008;
#endif
	__nds32__mtsr_dsb(tmp, NDS32_SR_PSW);
#if (defined(__NDS32_ISA_V3M__) || defined(__NDS32_ISA_V3__))
	/* Check interrupt priority programmable*
	* IVB.PROG_PRI_LVL
	*      0: Fixed priority       -- no exist ir18 1r19
	*      1: Programmable priority
	*/
	if (__nds32__mfsr(NDS32_SR_IVB) & 0x01) {
		/* Set PPL2FIX_EN to 0 to enable Programmable
		 * Priority Level */
		__nds32__mtsr(0x0, NDS32_SR_INT_CTRL);
		/* Check IVIC numbers (IVB.NIVIC) */
		if ((__nds32__mfsr(NDS32_SR_IVB) & 0x0E)>>1 == 5) {        // 32IVIC
			/* set priority HW9: 0, HW13: 1, HW19: 2,
			* HW#-: 0 */
			__nds32__mtsr(0x04000000, NDS32_SR_INT_PRI);
			__nds32__mtsr(0x00000080, NDS32_SR_INT_PRI2);
		} else {
			/* set priority HW0: 0, HW1: 1, HW2: 2, HW3: 3
			* HW4-: 0 */
			__nds32__mtsr(0x000000e4, NDS32_SR_INT_PRI);
		}
	}
#endif
	/* enable FPU if the CPU support FPU */
#if defined(__NDS32_EXT_FPU_DP__) || defined(__NDS32_EXT_FPU_SP__)
	tmp = __nds32__mfsr(NDS32_SR_FUCOP_EXIST);
	if ((tmp & 0x80000001) == 0x80000001) {
		tmp = __nds32__mfsr(NDS32_SR_FUCOP_CTL);
		__nds32__mtsr_dsb((tmp | 0x1), NDS32_SR_FUCOP_CTL);

		/* Denormalized flush-to-Zero mode on */
		tmp =__nds32__fmfcsr();
		tmp |= (1 << 12);
		__nds32__fmtcsr(tmp);
		__nds32__dsb();
	}
#endif



#if 0
	/* initialize SMPU with micro-TLB support */
	/* check Memory Management Protection Scheme
	* MMU_CFG.MMPS
	*      0: No memory management
	*      1: Protection Unit
	*      2: TLB MMU
	*/
	if((__nds32__mfsr(NDS32_SR_MMU_CFG) & 0x3) == 0x1) { 	// with Protection Unit
		/* check Protection Version Number
		* MMU_CFG.MMPV
		*    <16: MPU
		*     16: Secure MPU with only PSB field. ( A segment has to
		*         align to its power-of-2 size. ).
		*     24: Secure MPU with PSB and PSE fields.
		*/
		MMPV = (__nds32__mfsr(NDS32_SR_MMU_CFG) & 0x7c)>>2;
		if (MMPV >= 16) { 	// Secure MPU
			/* Setup BG_REGION as default */
			__nds32__mtsr(0x037, NDS32_SR_BG_REGION);

			/* Setup SEG0 for ILM */
			if(MMPV == 24) {
				__nds32__mtsr(0x40037, NDS32_SR_TLB_DATA);
				__nds32__mtsr((unsigned long)&_SEG0_END, NDS32_SR_TLB_MISC);
			}
			__nds32__mtsr_dsb((unsigned long)&_SEG0_BASE, NDS32_SR_TLB_VPN);
			__nds32__tlbop_twr(0x0);
			__nds32__isb();

			/* Setup SEG1 for DLM */
			if(MMPV == 24) {
				__nds32__mtsr(0x40037, NDS32_SR_TLB_DATA);
				__nds32__mtsr((unsigned long)&_SEG1_END, NDS32_SR_TLB_MISC);
			}
			__nds32__mtsr_dsb((unsigned long)&_SEG1_BASE, NDS32_SR_TLB_VPN);
			__nds32__tlbop_twr(0x1);
			__nds32__isb();

			/* Turn on SMPU */
			tmp = __nds32__mfsr(NDS32_SR_MMU_CTL);
			__nds32__mtsr_dsb((tmp | 0x100000), NDS32_SR_MMU_CTL);
		}
	}
#endif


	return;
}

#ifdef ENABLE_CACHE
void flushIDCache()
{
	unsigned long iend, icache_line;
	unsigned long dend, dcache_line;

	/* DCache writeback and invalidate all */
	dcache_line = dsize;
	dend = dcache_line * dway * dset;
	do {
		dend -= dcache_line;
		__nds32__cctlidx_wbinval(NDS32_CCTL_L1D_IX_WB, dend);
		__nds32__cctlidx_wbinval(NDS32_CCTL_L1D_IX_INVAL, dend);
		__nds32__dsb();
	} while (dend > 0);

	/* ICache invalidate all */
	icache_line = isize;
	iend = icache_line * iway * iset;
	do {
		iend -= icache_line;
		__nds32__cctlidx_wbinval(NDS32_CCTL_L1I_IX_INVAL, iend);
		__nds32__dsb();
	} while (iend > 0);
}

int enableIDCache()
{
	unsigned int cache_ctl=0, mmu_ctl, icm_cfg, dcm_cfg;

	/* Get ICache ways, sets, line size  */
	icm_cfg = __nds32__mfsr(NDS32_SR_ICM_CFG);
	if ((icm_cfg & NDS32_ISET) < 7)
		iset = 1 << ((icm_cfg & NDS32_ISET) + 6);
	else
		iset = 0;

	iway = ((icm_cfg & NDS32_IWAY) >> 3) + 1;

	if (((icm_cfg & NDS32_ISIZE) >> 6)
	    && ((icm_cfg & NDS32_ISIZE) >> 6) <= 5)
		isize = 1 << (((icm_cfg & NDS32_ISIZE) >> 6) + 2);
	else if (((icm_cfg & NDS32_ISIZE) >> 6) >= 6) {
		isize = 0;
	} else
		isize = 0;

	/* Get DCache ways, sets, line size  */
	dcm_cfg = __nds32__mfsr(NDS32_SR_DCM_CFG);
	if ((dcm_cfg & NDS32_DSET) < 7)
		dset = 1 << ((dcm_cfg & NDS32_DSET) + 6);
	else
		dset = 0;

	dway = ((dcm_cfg & NDS32_DWAY) >> 3) + 1;

	if (((dcm_cfg & NDS32_DSIZE) >> 6)
	    && ((dcm_cfg & NDS32_DSIZE) >> 6) <= 5)
		dsize = 1 << (((dcm_cfg & NDS32_DSIZE) >> 6) + 2);
	else if (((dcm_cfg & NDS32_DSIZE) >> 6) >= 6) {
		dsize = 0;
	} else
		dsize = 0;

	if ((isize == 0) || (dsize == 0)) {
		// There is no I or D Cache
		return 0;
	}

	/* Enable I and D Cache */
	cache_ctl = __nds32__mfsr(NDS32_SR_CACHE_CTL);
	cache_ctl |= 0x3;
	__nds32__mtsr(cache_ctl, NDS32_SR_CACHE_CTL);

	/* Enable cache for NTC0 */
	mmu_ctl = __nds32__mfsr(NDS32_SR_MMU_CTL);
	mmu_ctl &= (~0x6);
#ifdef WRITE_BACK_CACHE
	mmu_ctl |= (0x2) << 1;
#else
	mmu_ctl |= (0x3) << 1;
#endif
	__nds32__mtsr(mmu_ctl, NDS32_SR_MMU_CTL);

	return 1;
}
#endif
#ifdef __NDS32_ISA_V3M__

void enableLoopCache(void)
{
	unsigned int tmp = __nds32__mfsr(NDS32_SR_MISC_CTL);

#ifdef ENABLE_LOOPCACHE
       tmp &= ~(1 << 5);
#else
       tmp |= (1 << 5);
#endif

       __nds32__mtsr(tmp, NDS32_SR_MISC_CTL);
}
#endif
void __soc_init();

void __init()
{
/*----------------------------------------------------------
   !!  Users should NOT add any code before this comment  !!
------------------------------------------------------------*/
	__cpu_init();

#ifdef ENABLE_CACHE
	enableIDCache();
#endif
#ifdef __NDS32_ISA_V3M__
	enableLoopCache();
#endif


	__c_init();     //copy data section, clean bss

	__soc_init();
}

