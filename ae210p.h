#ifndef AE210P_REGS
#define AE210P_REGS
/* Check to see if this file has been included already.  */

#ifndef __ASSEMBLER__
#include <nds32_intrinsic.h>
#endif

/* System Clock */
#define MHz                     1000000
#define CPUFREQ                 (40 * MHz)
#define HCLKFREQ                CPUFREQ
#define PCLKFREQ                CPUFREQ
#define UCLKFREQ                (20 * MHz)

/* External memory mapping */
#define EILM_BASE               0x00000000
#define EDLM_BASE               0x00200000

#define ORIG_RAM_BASE           EDLM_BASE

/************************************
 *  TARGET UART CONSTANTS           *
 ************************************/
#define UART1_BASE              0x00F02000
#define UART2_BASE              0x00F03000
#define UART_BASE               UART2_BASE
#define UART_IDREV_OFFSET       0x00
#define UART_HWCFGR_OFFSET      0x10
#define UART_OSCR_OFFSET        0x14
#define UART_RBR_OFFSET         0x20    /* Receiver Buffer Register for Read */
#define UART_THR_OFFSET         0x20    /* Transmitter Holding Register for Write */
#define UART_IER_OFFSET         0x24    /* Interrupt Enable Register */
/* Baud-Rate Divisor Latch (DL, Offset: 0x20, 0x24 when DLAB = 1) */
#define UART_DLL_OFFSET         0x20
#define UART_DLM_OFFSET         0x24
#define UART_IIR_OFFSET         0x28    /* Interrupt Identification Register */
#define UART_FCR_OFFSET         0x28    /* FIFO Control Register */
#define UART_LCR_OFFSET         0x2C    /* Line Control Register */
#define UART_MCR_OFFSET         0x30    /* Modem Control Register */
#define UART_LSR_OFFSET         0x34    /* Line Status Register for Read */
#define UART_MSR_OFFSET         0x38    /* Modem Status Register */
#define UART_SPR_OFFSET         0x3C    /* Scratch Pad Register */

/************************************
 *  TARGET PIT CONSTANTS            *
 ************************************/
#define PIT_BASE                0x00F04000
#define PIT_IDREV_OFFSET        0x00    /* Offset for PIT ID and revision register */
#define PIT_CONFIG_OFFSET       0x10    /* Offset for PIT configure register */
#define PIT_INTE_OFFSET         0x14    /* Offset for PIT interrupt enable counter */
#define PIT_INTS_OFFSET         0x18    /* Offset for PIT interrupt status counter */
#define PIT_CHNEN_OFFSET        0x1C    /* Offset for PIT channel enable register */
#define PIT_CTRL_CHN(N)         (0x20 + 0x10 * (N))
#define PIT_LOAD_CHN(N)         (0x24 + 0x10 * (N))
#define PIT_CNTR_CHN(N)         (0x28 + 0x10 * (N))

/* PIT Channel 0 ~ 3 as Timer 0 ~ 3, ATCPIT100 */
#define TM_IE                   (PIT_BASE + PIT_INTE_OFFSET)
#define TM_STA                  (PIT_BASE + PIT_INTS_OFFSET)
#define TM_CHNEN                (PIT_BASE + PIT_CHNEN_OFFSET)
#define TM_CTRL(N)              (PIT_BASE + PIT_CTRL_CHN(N))
#define TM_LOAD(N)              (PIT_BASE + PIT_LOAD_CHN(N))
#define TM_CNTR(N)              (PIT_BASE + PIT_CNTR_CHN(N))

#define TM_CTRL_32BIT           (0x1 << 0)
#define TM_CTRL_PCLK            (0x1 << 3)

/************************************
 *  TARGET GPIO CONSTANTS           *
 ************************************/
#define GPIO_BASE               0x00F07000
#define GPIO_IDREV_OFFSET       0x00
#define GPIO_CONFIG_OFFSET      0x10
#define GPIO_DIN_OFFSET         0x20
#define GPIO_DOUT_OFFSET        0x24
#define GPIO_DIR_OFFSET         0x28
#define GPIO_DCLEAR_OFFSET      0x2C
#define GPIO_DSET_OFFSET        0x30
#define GPIO_PE_OFFSET          0x40
#define GPIO_PT_OFFSET          0x44
#define GPIO_IE_OFFSET          0x50
#define GPIO_IEMODE_OFFSET(N)   (0x54 + (N) * 4)
#define GPIO_IS_OFFSET          0x64
#define GPIO_BE_OFFSET          0x70    /* BounceEnable */
#define GPIO_BC_OFFSET          0x74    /* BounceControl */

#define GPIO_USED_GCOV          0x02    /* Which GPIO to do GCOV */
#define GPIO_USED_MASK          0x7F    /* Which GPIOs to use */



/* DMA controller */
#define DMAC_BASE       0xE0E000

#define DMAC_IDREV      (DMAC_BASE + 0x00)
#define DMAC_CONFIG     (DMAC_BASE + 0x10)
#define DMAC_CTRL       (DMAC_BASE + 0x20)
#define DMAC_INTRST     (DMAC_BASE + 0x30)
#define DMAC_CHEN       (DMAC_BASE + 0x34)
#define DMAC_CHABORT    (DMAC_BASE + 0x40)
#define DMAC_CHCTRL(N)  (DMAC_BASE + 0x44 + (N) * 0x14)
#define DMAC_CHSRCADDR(N) (DMAC_BASE + 0x48 + (N) * 0x14)
#define DMAC_CHDSTADDR(N) (DMAC_BASE + 0x4C + (N) * 0x14)
#define DMAC_CHTRANSZ(N)  (DMAC_BASE + 0x50 + (N) * 14)
#define DMAC_CHLLP(N)   (DMAC_BASE + 0x54 + (N) * 14)

/************************************
 *  IRQ number                      *
 ************************************/
#define IRQ_RTC_PERIOD          0
#define IRQ_RTC_ALARM           1
#define IRQ_PIT                 2
#define IRQ_SPI1                3
#define IRQ_SPI2                4
#define IRQ_I2C                 5
#define IRQ_GPIO                6
#define IRQ_UART1               7
#define IRQ_UART2               8
#define IRQ_DMA                 9
#define IRQ_BMC                 10
#define IRQ_SWI                 11
#define IRQ_EXTERNAL(N)         (12 + (N))

#define IRQ_TIMER1              IRQ_PIT

/* interrupt sources */
#define IC_SWI                  (1 << IRQ_SWI)
#define IC_GPIO                 (1 << IRQ_GPIO)
#define IC_TIMER1               (1 << IRQ_PIT)


/* Low-level port I/O */
#define inw(reg)        (*((volatile unsigned int *) (reg)))
#define outw(reg, data) ((*((volatile unsigned int *)(reg)))=(unsigned int)(data))

#ifndef NDS32_INTR_DEF
/*
 * NDS32_REG_SET_BITS(addr, mask)
 * Do set bits to 1 at specified location
 * Operation: *addr = (*addr | mask)
 */
#define NDS32_SET_BITS(addr, mask) outw(addr, inw(addr) | mask)

/*
 * NDS32_REG_WAIT4_BIT_ON(addr, mask)
 * Read the contents at addr and use mask to
 * mask off unused bits then wait until all of
 * the remaining bits are on
 *
 * Operation: while(!(*addr & mask));
 */
#define NDS32_REG_WAIT4_BIT_ON(addr, mask) while(0 == (inw(addr) & mask))

/*
 * NDS32_REG_WAIT4_BIT_OFF(addr, mask)
 * Read the contents at addr and use mask to
 * mask off unused bits then wait until all of
 * the remaining bits are off
 *
 * Operation: while((*addr & mask));
 */
#define NDS32_REG_WAIT4_BIT_OFF(addr, mask) while(inw(addr) & mask)

/*
 * NDS32_REG_WRITE(addr, data)
 * Write data to specified location at addr
 *
 * Operation: *addr = data
 * */
#define NDS32_REG_WRITE(addr, data) outw(addr, data)

/*
 * NDS32_FMEMCPY_BYTE(dst, src, size)
 * Do forward (low address to high address) memory copy in byte
 * */
#define NDS32_FMEMCPY_BYTE(dst, src, size) \
	__asm__ __volatile__( \
		"sethi   $r3, hi20(%2)       \n\t" \
		"ori     $r3, $r3, lo12(%2)  \n\t" \
		"sethi   $r1, hi20(%0)       \n\t" \
		"ori     $r1, $r1, lo12(%0)  \n\t" \
		"sethi   $r2, hi20(%1)       \n\t" \
		"ori     $r2, $r2, lo12(%1)  \n\t" \
		"1:\n\t" \
		"lbi.bi  $r0, [$r2], 1       \n\t" \
		"sbi.bi  $r0, [$r1], 1       \n\t" \
		"addi    $r3, $r3, -1        \n\t" \
		"bnez    $r3, 1b             \n\t" \
		::"i"(dst),"i"(src),"i"(size):"$r0", "$r1","$r2","$r3")

#define NDS32_FMEMCPY(dst, src, size) \
	__asm__ __volatile__( \
		"sethi   $r3, hi20(%2)       \n\t" \
		"ori     $r3, $r3, lo12(%2)  \n\t" \
		"sethi   $r1, hi20(%0)       \n\t" \
		"ori     $r1, $r1, lo12(%0)  \n\t" \
		"sethi   $r2, hi20(%1)       \n\t" \
		"ori     $r2, $r2, lo12(%1)  \n\t" \
		"1:\n\t" \
		"lwi.bi  $r0, [$r2], 4       \n\t" \
		"swi.bi  $r0, [$r1], 4       \n\t" \
		"addi    $r3, $r3, -4        \n\t" \
		"bgtz    $r3, 1b             \n\t" \
		::"i"(dst),"i"(src),"i"(size):"$r0", "$r1","$r2","$r3")

#endif

/************************************
 *  HAL Level : Memory interface    *
 ************************************/
#define HAL_MEMORY_SETUP(_base_)                                        \
do {                                                                    \
        /* Enable DLM */                                                \
        __nds32__mtsr_dsb(_base_ | 1, NDS32_SR_DLMB);                       \
} while(0)

#define HAL_MEMORY_REMAP()
#define HAL_MEMORY_REMAP_ADJUST()

/************************************
 *  HAL Level : Interrupt           *
 ************************************/
#define HW_ISR(n)               HW##n##_ISR
#define SET_HWISR(hw)           HW_ISR(hw)

// ISR function name for PIT/GPIO/SWI */
#define TIMER_ISR      	        SET_HWISR(IRQ_PIT)
#define GPIO_ISR                SET_HWISR(IRQ_GPIO)
#define SWI_ISR                 SET_HWISR(IRQ_SWI)
#define DMA_ISR                 SET_HWISR(IRQ_DMA)

// AE210P without interrupt controller
#define HAL_INTC_HWIRQ_ROUTE(_vector_, _hw_)
#define HAL_INTC_IRQ_CONFIGURE(_irqs_, _edge_, _falling_)
#define HAL_INTC_IRQ_MASK(_irqs_)
#define HAL_INTC_IRQ_UNMASK(_irqs_)
#define HAL_INTC_IRQ_CLEAR(_irqs_)
#define HAL_INTC_FIQ_CONFIGURE(_irqs_, _edge_, _falling_)
#define HAL_INTC_FIQ_MASK(_irqs_)
#define HAL_INTC_FIQ_UNMASK(_irqs_)
#define HAL_INTC_FIQ_CLEAR(_irqs_)
#define SR_CLRB32(reg, bit)		\
{					\
	int mask = __nds32__mfsr(reg)& ~(1<<bit);\
        __nds32__mtsr(mask, reg);	 \
	__nds32__dsb();				 \
}

#define SR_SETB32(reg,bit)\
{\
	int mask = __nds32__mfsr(reg)|(1<<bit);\
	__nds32__mtsr(mask, reg);			\
	__nds32__dsb();						\
}

/************************************
 *  HAL Level : Timer               *
 ************************************/
#define HAL_TIMER_INITIALIZE()                                          \
do {                                                                    \
        outw(TM_CHNEN, 0x00000000);                                     \
        outw(TM_CTRL(0), TM_CTRL_32BIT | TM_CTRL_PCLK);                 \
        outw(TM_CTRL(1), TM_CTRL_32BIT | TM_CTRL_PCLK);                 \
        outw(TM_CTRL(2), TM_CTRL_32BIT | TM_CTRL_PCLK);                 \
        outw(TM_CTRL(3), TM_CTRL_32BIT | TM_CTRL_PCLK);                 \
        outw(TM_IE, 0x00000000);                                        \
        outw(TM_STA, 0xFFFFFFFF);                                       \
} while(0)

#define HAL_TIMER_START(_tmr_)                                          \
        outw(TM_CHNEN, inw(TM_CHNEN) | (0x1 << (4 * _tmr_)))

#define HAL_TIMER_STOP(_tmr_)                                           \
         outw(TM_CHNEN, inw(TM_CHNEN) & ~(0x1 << (4 * _tmr_)))

#define HAL_TIMER_READ(_tmr_, _pvalue_)                                 \
        *(volatile unsigned int *)_pvalue_ =                            \
                        inw(TM_LOAD(_tmr_)) - inw(TM_CNTR(_tmr_))

#define HAL_TIMER_SET_PERIOD(_tmr_, _period_)                           \
        outw(TM_LOAD(_tmr_), _period_)

#define HAL_TIMER_IRQ_ENABLE(_tmr_, _ie_)                               \
do {                                                                    \
        if(_ie_)                                                        \
                outw(TM_IE, inw(TM_IE) | (0x1 << (4 * _tmr_)));         \
        else                                                            \
                outw(TM_IE, inw(TM_IE) & ~(0x1 << (4 * _tmr_)));        \
} while(0)

#define HAL_TIMER_IRQ_STATUS(_tmr_,_pvalue_)                            \
        *(volatile unsigned int *)_pvalue_ =                            \
                        (inw(TM_STA) & (0xF << (4 * _tmr_)))

#define HAL_TIMER_IRQ_CLR(_tmr_)                                        \
        outw(TM_STA, 0xF << (4 * _tmr_))

/************************************
 *  HAL Level : GPIO                *
 ************************************/
#define HAL_GPIO_INITIALIZE(_pin_)                                      \
do {                                                                    \
        outw(GPIO_BASE + GPIO_DIR_OFFSET,                               \
		inw(GPIO_BASE + GPIO_DIR_OFFSET) & ~_pin_);             \
        outw(GPIO_BASE + GPIO_DCLEAR_OFFSET, -1);                       \
        outw(GPIO_BASE + GPIO_IEMODE_OFFSET(0), 0x55555555);            \
        outw(GPIO_BASE + GPIO_IEMODE_OFFSET(1), 0x55555555);            \
        outw(GPIO_BASE + GPIO_IEMODE_OFFSET(2), 0x55555555);            \
        outw(GPIO_BASE + GPIO_IEMODE_OFFSET(3), 0x55555555);            \
        outw(GPIO_BASE + GPIO_BC_OFFSET, 0x000000FF);                   \
        outw(GPIO_BASE + GPIO_BE_OFFSET, _pin_);                        \
        outw(GPIO_BASE + GPIO_IS_OFFSET, -1);                           \
        outw(GPIO_BASE + GPIO_IE_OFFSET, _pin_);                        \
} while(0)

#define HAL_GPIO_READ()                 inw(GPIO_BASE + GPIO_DIN_OFFSET)

#define HAL_GPIO_IRQ_CLR(_pin_)         outw(GPIO_BASE + GPIO_IS_OFFSET, _pin_)

/************************************
 *  HAL Level : SMU               *
 ************************************/
#define HAL_SET_SMU() //

#ifdef __ASSEMBLER__
/************************************
 *  HAL : AE210P defined vectors    *
 ************************************/
.macro  hal_hw_vectors
        vector Interrupt_UNDEF   //  (9) Interrupt HW0
        vector Interrupt_UNDEF   // (10) Interrupt HW1
        vector Interrupt_HW2     // (11) Interrupt HW2 (PIT)
        vector Interrupt_UNDEF   // (12) Interrupt HW3
        vector Interrupt_UNDEF   // (13) Interrupt HW4
        vector Interrupt_UNDEF   // (14) Interrupt HW5
        vector Interrupt_HW6     // (15) Interrupt HW6 (GPIO)
        vector Interrupt_UNDEF   // (16) Interrupt HW7
        vector Interrupt_UNDEF   // (17) Interrupt HW8
        vector Interrupt_UNDEF   // (18) Interrupt HW9
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
.endm

.macro	hal_hw_ISR
	Os_Trap_Interrupt_HW	IRQ_PIT
	Os_Trap_Interrupt_HW	IRQ_GPIO
	Os_Trap_Interrupt_HW	IRQ_SWI
.endm

.macro	hal_set_led, val
.endm
#endif  /* __ASSEMBLER__ */

#endif  /* AE210P_REGS */
