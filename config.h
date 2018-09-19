/*
 * Config the features of startup demo programs.
 */

#ifndef __CONFIG_H__
#define __CONFIG_H__

#ifndef CFG_MAKEFILE
//----------------------------------------------------------------------------------------------------

// Users can configure the defines in this area
// to match different environment setting

//#define CFG_AE100      // platform is AE100
#define   CFG_AE210P      // platform is AE210P
//#define CFG_AG101P      // platform is AG101P

#define CFG_PFM      // The time is come from performance monitor.
//#define CFG_TIMER    // The time is come from Timer Counter.
//----------------------------------------------------------------------------------------------------
#endif


#define GCC_VERSION (__GNUC__ * 10000 + __GNUC_MINOR__ * 100 + __GNUC_PATCHLEVEL__)

// GCC < 4.8.2 (Before BSP400 gcc version)
// Check the GCC version for toolchain builtin macro compatible issue.
#if GCC_VERSION < 40802

#ifdef NDS32_BASELINE_V3
#define __NDS32_ISA_V3__	NDS32_BASELINE_V3
#endif

#ifdef NDS32_BASELINE_V3M
#define __NDS32_ISA_V3M__	NDS32_BASELINE_V3M
#endif

#endif

#ifndef __ASSEMBLER__

#include <nds32_intrinsic.h>

#ifndef __nds32__mtsr_isb
#define __nds32__mtsr_isb(val, srname)  \
do {__nds32__mtsr(val, srname);__nds32__isb();} while(0)
#endif

#ifndef __nds32__mtsr_dsb
#define __nds32__mtsr_dsb(val, srname)	\
do {__nds32__mtsr(val, srname);__nds32__dsb();} while(0)
#endif

#endif

#ifdef  __NDS32_ISA_V3M__
    #define CFG_16MB            1   // Use 24 bit address mode
#endif

#if defined(CFG_AE210P)
#include "ae210p.h"
#elif defined(CFG_AE100)
#include "Andes/ae100.h"
#else
#include "Andes/ag101p.h"
#endif

#ifdef CFG_AE100
    #define LOOP_COUNT              300000 // loop count for the benchmark
#else
    #define LOOP_COUNT              1000000 // loop count for the benchmark
#endif
                                       // For AG101P: set LOOP_COUNT as 1000000 for the real board, and 10000 for simulation.
                                       // For AE100: set LOOP_COUNT 300000 for real board, and as 30000 for simulation.
                                       // To get AE210P benchmark score, it's necessary to run on real board due to AE210P doesn't support simulation yet.
#define CPU_MHz             (CPUFREQ / MHz)     // CPU speed, should be matched with the board or the setting of SID
#define PCLK_MHZ            (PCLKFREQ / MHz)    // PClk speed in MHZ
#ifndef CFG_AE100
    #define USE_DLM                  1             //For AG101P/AE210P, DLM can be used for data sections
                                                 //For AE100 that dosen't have DLM, MEM is used for data sections without any SW initialization.
#endif
#define MALLOC_SIZE             200             // the reserved memory for malloc()

#ifdef	__NDS32_ISA_V3M__
    // for N8/N650
    #define ENABLE_LOOPCACHE    1
#else
    // for other CPU cores
    #define __NDS32_STRCMP__    1   // use the STRING ISA for strcmp() function in assembly, it's not supported by AG102.
    #ifndef CFG_AE100
        #ifndef USE_DLM
            #define ENABLE_CACHE        1   // enable I/D cache if I/D cache is available
            #define WRITE_BACK_CACHE    1   // Use write back mode for cache
                                            // The write through will be used if WRITE_BACK_CACHE is not defined
        #endif // USE_DLM
    #endif
#endif // __NDS32_ISA_V3M__

#define CFG_LLINIT
#define TIME                    1   // The time of Dhrystone is based on library function of time()
                                    // If comment this define, TIMES will be defined in dhry.h
#define PLATFORM_TIMER          1   // Use the timer/pfm of AG101P/AE210P/AE100 to measure time
#define malloc              my_malloc

#endif // __CONFIG_H__
