#ifndef	SRC_BUS_FPGA_H_
#define SRC_BUS_FPGA_H_

#define SET_WR      (P5OUT|=BIT5)
#define CLR_WR      (P5OUT&=~BIT5)
#define SET_RD      (P5OUT|=BIT4)
#define CLR_RD      (P5OUT&=~BIT4)
#define ADDR        P9OUT
#define CS_ADDR    	P1OUT
#define WRDAT       PBOUT
#define RDDAT       PBIN
#define SETDAT_OUT  (PBDIR=0XFFFF)
#define SETDAT_IN   (PBDIR=0x0000)


//一共支持15个模块。
#define CS0		0X00
#define CS1		0X10
#define CS2		0X20
#define CS3		0X30
#define CS4		0X40
#define CS5		0X50
#define CS6		0X60
#define CS7		0X70
#define CS8		0X80
#define CS9	        0X90
#define CS10		0XA0
#define CS11		0XB0
#define CS12		0XC0
#define CS13		0XD0
#define CS14		0XE0
#define CS_ADDRH16_REG	0XF0

#define CLR_IFG     (P1IFG&=~0x0f)
typedef void (*FUNC)(void);

FUNC Fun0,Fun1,Fun2,Fun3;
void IOWR(unsigned char BASE,unsigned char OFFSET,unsigned int DATA);
//extern void *KEY_ISR();
void BUSINT_Init()
{
 // Fun0=Fun1=0;
  P1DIR&=~0x0f;
  P1IES&=~0x0f;
  P1IE|=0x0f;
  CLR_IFG;
}
void BUS_Init()
{
  P9DIR=0XFF;
  P1DIR=0XF0;
  PBDIR=0X0000;
  P5OUT&=~(BIT4+BIT5);
  P5DIR|=(BIT4+BIT5);
  IOWR(CS_ADDRH16_REG,1,1);
  IOWR(CS_ADDRH16_REG,1,0);
  IOWR(CS_ADDRH16_REG,1,1);
//软件复位
}

void IOWR(unsigned char BASE,unsigned char OFFSET,unsigned int DATA)
{
  SETDAT_OUT;
  CS_ADDR=BASE;
  ADDR=OFFSET;
  WRDAT=DATA;
  SET_WR;
  _NOP();
  CLR_WR;
}

//BASE -> dataAddr[15:8]
//OFFSET -> dataAddr[7:0]
unsigned int IORD(unsigned char BASE,unsigned char OFFSET)
{
  unsigned int rddat;
  SETDAT_IN;
  CS_ADDR=BASE;
  ADDR=OFFSET;
  SET_RD;
  rddat=RDDAT;
  CLR_RD;
  return rddat;
}
void SET_ADDRH16(unsigned int ADDRH16)
{
	SETDAT_OUT;
	CS_ADDR=CS_ADDRH16_REG;
	WRDAT=ADDRH16;
	SET_WR;
	CLR_WR;
}
//支持模块24位寻址。
void IOWR24(unsigned char BASE,unsigned long OFFSET,unsigned int DATA)
{
	SET_ADDRH16(OFFSET>>8);
	SETDAT_OUT;
	CS_ADDR=BASE;
	ADDR=OFFSET;
	WRDAT=DATA;
	SET_WR;
	CLR_WR;
}

unsigned int IORD24(unsigned char BASE,unsigned long OFFSET)
{
  unsigned int rddat;
  SET_ADDRH16(OFFSET>>8);
  SETDAT_IN;
  CS_ADDR=BASE;
  ADDR=OFFSET;
  SET_RD;
  rddat=RDDAT;
  CLR_RD;
  return rddat;
}

void Register_CallBack(FUNC CallBack,unsigned char INT)
{
  switch(INT)
  {
  case 0:Fun0=CallBack;break;
  case 1:Fun1=CallBack;break;
  case 2:Fun2=CallBack;break;
  case 3:Fun3=CallBack;break;
  default: break;
  }
  
}

#pragma vector=PORT1_VECTOR
__interrupt void Port_1(void)
{
	if(P1IFG&BIT0)
	{
		Fun0();
    	P1IFG&=~BIT0;
	}
	else if(P1IFG&BIT1)
	{
	  Fun1();
	  P1IFG&=~BIT1;
	}
	else if(P1IFG&BIT2)
	{
		Fun2();
    	P1IFG&=~BIT2;
	}
	else if(P1IFG&BIT3)
	{
		Fun3();
    	P1IFG&=~BIT3;
	}
	else
	  CLR_IFG;
}

#endif
