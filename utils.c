#include "config.h"

#include <stdio.h>
#include <stdarg.h>

#define BAUD_RATE(n)		(UCLKFREQ / (n) / 16)

unsigned char led[16] =
{
	0xC0, /* 0 */
	0xF9, /* 1 */
	0xA4, /* 2 */
	0xB0, /* 3 */
	0x99, /* 4 */
	0x92, /* 5 */
	0x82, /* 6 */
	0xF8, /* 7 */
	0x80, /* 8 */
	0x90, /* 9 */
	0x88, /* A */
	0x83, /* B */
	0xC6, /* C */
	0xA1, /* D */
	0x86, /* E */
	0x8E, /* F */
};
void gpio_init(void)
{
	outw(GPIO_BASE + GPIO_DIR_OFFSET,  0xFFFF0000);
	outw(GPIO_BASE + GPIO_DOUT_OFFSET, 0x00000000);
}

void gpio_set_led(unsigned char num)
{
	unsigned int temp = 0;
	temp = ((unsigned int)(led[num])<<24) | ((unsigned int)(led[num])<<16);
	outw(GPIO_BASE + GPIO_DOUT_OFFSET, temp);
}

void gpio_set_led1(unsigned char num)
{
	unsigned int temp;
	temp = inw(GPIO_BASE + GPIO_DOUT_OFFSET);
	temp &= 0xFF00FFFF;
	outw(GPIO_BASE + GPIO_DOUT_OFFSET, temp | ((unsigned int)led[num]<<16));
}

void gpio_set_led2(unsigned char num)
{
	unsigned int temp;
	temp = inw(GPIO_BASE + GPIO_DOUT_OFFSET);
	temp &= 0x00FFFFFF;
	outw(GPIO_BASE + GPIO_DOUT_OFFSET, temp | ((unsigned int)led[num]<<24));
}

void gpio_set_led3(unsigned char num)
{
	unsigned int temp;
	unsigned char high, low;
	high = num / 10;
	low  = num % 10;
	temp = inw(GPIO_BASE + GPIO_DOUT_OFFSET);
	temp &= 0x0000FFFF;
	temp |= ((unsigned int)led[high]<<24) | ((unsigned int)led[low]<<16);
	outw(GPIO_BASE + GPIO_DOUT_OFFSET, temp);
}

#ifdef CFG_LLINIT
void uart_init(void)
{
	/* Set DLAB to 1 */
	outw(UART_BASE + UART_LCR_OFFSET,
	     inw(UART_BASE + UART_LCR_OFFSET) | 0x80);
	/* Set DLL for baudrate */
	outw(UART_BASE + UART_DLL_OFFSET, (BAUD_RATE(38400) >> 0) & 0xff);
	outw(UART_BASE + UART_DLM_OFFSET, (BAUD_RATE(38400) >> 8) & 0xff);
	/* baud 38400 , LCR: Length 8, no parity, 1 stop bit. */
	outw(UART_BASE + UART_LCR_OFFSET, 0x03);
	/* FCR: Enable FIFO, reset TX and RX. */
	outw(UART_BASE + UART_FCR_OFFSET, 0x0F);
}
#endif

#define SERIAL_LSR_THRE		0x20

#undef putchar
int putchar(int c)
{
	volatile unsigned *status =
	    (volatile unsigned *)(UART_BASE + UART_LSR_OFFSET);

	while ((*status & SERIAL_LSR_THRE) == 0) ;

	if (c =='\n')fflush(stdout);
	*(volatile unsigned *)(UART_BASE + UART_THR_OFFSET) = c;

	if (c == '\n') {
		while ((*status & SERIAL_LSR_THRE) == 0) ;
		*(volatile unsigned *)(UART_BASE + UART_THR_OFFSET) = '\r';
	}
	return c;
}

// wrapper for MCUlib
__attribute__((used))
void nds_write(const unsigned char *buf, int size)
{
	int    i;
	for (i = 0; i < size; i++)
		putchar(buf[i]);
}

// wrapper for Newlib
struct stat;
__attribute__((used))
int _fstat(int fd, struct stat *buf)
{
	return 0;
}

// wrapper for Newlib
__attribute__((used))
int _write(int fd, const unsigned char *buf, int size)
{
	int    i;
	for (i = 0; i < size; i++)
		putchar(buf[i]);

	return i;
}

char *my_malloc(int size)
{
	static char	mem_pool[MALLOC_SIZE];
	static int alloc_pos = 0;
	char	*buf;

	if (alloc_pos + size <= MALLOC_SIZE)
	{
		buf = &mem_pool[alloc_pos];
		alloc_pos += size;

		return buf;
	}
	else
	{
		printf("Cannot allocate memory because memory pool is not enough\n");
		printf("MALLOC_SIZE is %d, Please increase MALLOC_SIZE in config.h\n", MALLOC_SIZE);
		while(1);
	}

	return 0;
}

__attribute__((used))
int scanf(const char *str, ...)
{
	va_list ap;
	int *val;

	va_start(ap, str);
	val = va_arg(ap, int *);
	*val = LOOP_COUNT;
	va_end(ap);

	return 1;
}

#ifdef PLATFORM_TIMER

#define TIMER1		0
#define TIMER2		1
#define TIMER3		2

int	tm1StartCount = 0, tm1StopCount = 0, tm1UsedCount = 0;

__attribute__((used))
long get_time_from_timer(long *retval)
{
	static int	init = 0, val=0;
	if (!init)
	{
		// disable timer1 for decrease counter
		HAL_TIMER_STOP(TIMER1);

		HAL_TIMER_INITIALIZE();
		HAL_TIMER_SET_PERIOD(TIMER1,0xffffffff);

		HAL_TIMER_START(TIMER1);			// enable timer1 for decrease counter

		// workaround for SID in N801, interrupt status may assert wrongly sometimes
		do{
			HAL_TIMER_READ(TIMER1,&val);
		}while (val <= 0x100);

		HAL_TIMER_IRQ_CLR(TIMER1);

		// Timer has been initialized
		init = 1;
	}

	HAL_TIMER_IRQ_STATUS(TIMER1,&val);

	if(val)
	{
		printf ("Measured time too large to obtain meaningful results\n");
		printf ("Please decrease number of runs and try again.\n");
		printf ("\n");
		while(1);
	}

	HAL_TIMER_READ(TIMER1,&val);

	if (tm1StartCount == 0)
	{
		// record the start count for debuggging
		tm1StartCount = val;
	}
	else
	{
		// record the stop count for debuggging
		tm1StopCount = val;
		tm1UsedCount = tm1StopCount - tm1StartCount;
	}

	if (retval)
		return (*retval = val/PCLK_MHZ);
	else
		return val/PCLK_MHZ;
}

#ifndef CFG_TIMER
__attribute__((used))
long get_time_from_pfm(long *retval)
{
	static int	init = 0, val=0;
	if (!init)
	{
		__nds32__mtsr(0, NDS32_SR_PFM_CTL);
		__nds32__mtsr(0, NDS32_SR_PFMC0);
		__nds32__mtsr(0, NDS32_SR_PFMC1);
		__nds32__mtsr(0, NDS32_SR_PFMC2);
		__nds32__mtsr(0x1000B, NDS32_SR_PFM_CTL);

		// pfm has been initialized
		init = 1;
	}
	val = __nds32__mfsr(NDS32_SR_PFMC0);

	if (retval)
		return (*retval = val/CPU_MHz);
	else
		return val/CPU_MHz;
}
#endif

__attribute__((used))
long time(long *retval)
{
	static int init = 0;
	long val;

#ifndef CFG_TIMER
	if( __nds32__mfsr(NDS32_SR_MSC_CFG) & (0x1<<2) ) //with performance monitor
		val=get_time_from_pfm(retval);
	else
#endif
		val=get_time_from_timer(retval);

	if (!init)
		init = 1;
	else
	{
#ifndef CFG_TIMER
		if( __nds32__mfsr(NDS32_SR_MSC_CFG) & (0x1<<2) ) //with performance monitor
			printf("The time is come from performance monitor\n");
		else
#endif
			printf("The time is come from timer counter\n");
	}

	return val;
}
#endif
