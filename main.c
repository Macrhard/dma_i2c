/*
 ============================================================================
 Name        : test.c
 Author      : 
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, ANSI-style
 ============================================================================
 */

#include <stdio.h>
#include <nds32_intrinsic.h>
#include "ae210p.h"

#define  IIC_BASE  0x00F0A000
#define  WDT_BASE  0x00F05000

//#define  DMA_TRANSFER
#define  MAX_LEN   64
#define  SLA_ADDR  0x50  // 7bit, AT24C128
#define  E2P_ADDR  0x1240L  // 2Byte, 16KByte

unsigned char send[MAX_LEN+2];
unsigned char recv[MAX_LEN+2];

void delay(void)
{
	unsigned int i;
	for(i=0; i<100000; i++)
		__nds32__nop();
}

int main(void)
{
	unsigned int i;

	while(1)
	{
		printf("1111111111111111\r\n");
		delay();
	}


	for(i=0; i<MAX_LEN+2; i++)
	{
		send[i] = i;
		recv[i] = 0;
	}

	outw(IIC_BASE+0x28, 5);  // reset i2c
	delay();
	outw(IIC_BASE+0x28, 0);
	outw(IIC_BASE+0x1C, SLA_ADDR);
#ifdef DMA_TRANSFER
	outw(IIC_BASE+0x2C, (4<<24)|(1<<21)|(6<<16)|(0<<13)|(182<<4)|0xD);
	outw(DMAC_CTRL, 1);  /* Reset DMA */
#else
	outw(IIC_BASE+0x2C, (4<<24)|(1<<21)|(6<<16)|(0<<13)|(182<<4)|0x5);
#endif


#ifdef DMA_TRANSFER
	send[0] = E2P_ADDR>>8;
	send[1] = E2P_ADDR;
	outw(DMAC_INTRST, -1);        // clear interrupt status
	outw(DMAC_CHSRCADDR(0), send);
	outw(DMAC_CHDSTADDR(0), IIC_BASE+0x20);
	outw(DMAC_CHTRANSZ(0), MAX_LEN+2);
	/* Enable DMAC channel #0
	 * 1 burst transfers, word width transfer, unmask ABT/ERR/TC
	 * SRC : normal mode, increment address
	 * DST : handshake mode, request select, fixed address
	 */
	outw(DMAC_CHCTRL(0), (0 << 22) | (0 << 20) | (0 << 18) | (1 << 16) | (2 << 12) | (8 << 4) | 0xF);
#endif

	outw(IIC_BASE+0x24, (0xF<<9)|(0<<8)|(MAX_LEN+2)); //write, count = 2Byte addr + MAX_LEN data
	outw(IIC_BASE+0x28, 0x1);                         // start

#ifdef DMA_TRANSFER
	while((inw(DMAC_INTRST) & (1 << 16)) == 0);/* Wait for DMA complete */
#else
	while((inw(IIC_BASE+0x18) & (1<<1)) != 0);
	outw(IIC_BASE+0x20, E2P_ADDR>>8);                 // high byte addr
	while((inw(IIC_BASE+0x18) & (1<<1)) != 0);
	outw(IIC_BASE+0x20, E2P_ADDR);                    // low  byte addr

	for(i=0; i<MAX_LEN; i++)
	{
		while((inw(IIC_BASE+0x18) & (1<<1)) != 0);    // write data
		outw(IIC_BASE+0x20, send[i]);
	}

	while((inw(IIC_BASE+0x18) & (1<<9)) == 0);        // wait transaction complete
	outw(IIC_BASE+0x18, (1<<9));                      // clear complete flag
#endif

	delay(); // delay at least 20ms for write e2prom complete

	outw(IIC_BASE+0x24, (0xF<<9)|(0<<8)|2);           // write 2Byte addr for read
	outw(IIC_BASE+0x28, 0x1);                         // start
	while((inw(IIC_BASE+0x18) & (1<<1)) != 0);
	outw(IIC_BASE+0x20, E2P_ADDR>>8);                 // high byte address
	while((inw(IIC_BASE+0x18) & (1<<1)) != 0);
	outw(IIC_BASE+0x20, E2P_ADDR);                    // low  byte address

	while((inw(IIC_BASE+0x18) & (1<<9)) == 0);        // wait transaction complete
	outw(IIC_BASE+0x18, (1<<9));                      // clear complete flag


#ifdef DMA_TRANSFER
	outw(DMAC_INTRST, -1);        // clear interrupt status
	outw(DMAC_CHSRCADDR(0), IIC_BASE+0x20);
	outw(DMAC_CHDSTADDR(0), recv);     /************* recv+2 **************/
	outw(DMAC_CHTRANSZ(0), MAX_LEN+2); /************* MAX_LEN **************/
	/* Enable DMAC channel #0
	 * 1 burst transfers, word width transfer, unmask ABT/ERR/TC
	 * SRC : handshake mode, request select, fixed address
	 * DST : normal mode, increment address
	 */
	outw(DMAC_CHCTRL(0), (0 << 22) | (0 << 20) | (0 << 18) | (1 << 17) | (2 << 14) | (8 << 8) | 0xF);
#endif

	outw(IIC_BASE+0x24, (0xF<<9)|(1<<8)|MAX_LEN);     // read data
	outw(IIC_BASE+0x28, 0x1);                         // start

#ifdef DMA_TRANSFER
	while((inw(DMAC_INTRST) & (1 << 16)) == 0);/* Wait for DMA complete */
#else
	for(i=0; i<MAX_LEN; i++)
	{
		while((inw(IIC_BASE+0x18) & (1<<0)) != 0);
		recv[i] = inw(IIC_BASE+0x20);
	}
#endif




#ifdef DMA_TRANSFER
	for(i=0; i<MAX_LEN+2; i++)
#else
	for(i=0; i<MAX_LEN; i++)
#endif
	{
		if(recv[i] == send[i])  printf("recv[%03d] = 0x%x\r\n", i, recv[i]);
		else printf("recv[%03d] = 0x%x\tDATA error !!!\r\n", i, recv[i]);
	}

	while(1);

	return 0;
}
