/*
 * Copyright:
 * ----------------------------------------------------------------
 * This confidential and proprietary software may be used only as
 * authorised by a licensing agreement from ARM Limited
 *   (C) COPYRIGHT 2014 ARM Limited
 *       ALL RIGHTS RESERVED
 * The entire notice above must be reproduced on all authorised
 * copies and copies may only be made to the extent permitted
 * by a licensing agreement from ARM Limited.
 * ----------------------------------------------------------------
 * File:     uart_stdout.c
 * Release:  Version 2.0
 * ----------------------------------------------------------------
 *
 */

#include <stdio.h>

#include "SMM_MPS3.h"                   // MPS3 common header

#include "uart_stdout.h"

#define CNTLQ       0x11
#define CNTLS       0x13
#define DEL         0x7F
#define BACKSPACE   0x08
#define CR          0x0D
#define LF          0x0A
#define ESC         0x1B

#ifdef FPGA_IMAGE
void UartStdOutInit(void)
{
    CMSDK_UART0->BAUDDIV = SystemCoreClock / 115200;  // 115200 at 25MHz

    CMSDK_UART0->CTRL    = ((1ul <<  0) |              /* TX enable */
                            (1ul <<  1) );             /* RX enable */
    return;
}

// Output a character
unsigned char UartPutc(unsigned char my_ch)
{
  while ((CMSDK_UART0->STATE & 1)); // Wait if Transmit Holding register is full

  if (my_ch == '\n')
  {
	  CMSDK_UART0->DATA  = '\r';
	  while ((CMSDK_UART0->STATE & 1)); // Wait if Transmit Holding register is full
  }

  CMSDK_UART0->DATA = my_ch; // write to transmit holding register

  return (my_ch);
}

// Get a character
unsigned char UartGetc(void)
{
  unsigned char my_ch;
  unsigned int  cnt;

  while ((CMSDK_UART0->STATE & 2)==0) // Wait if Receive Holding register is empty
  {
      cnt = MPS3_FPGAIO->CLK100HZ / 50;
      if (cnt & 0x8)
        MPS3_FPGAIO->LED = 0x01 << (cnt & 0x7);
      else
        MPS3_FPGAIO->LED = 0x80 >> (cnt & 0x7);
  }

  my_ch = CMSDK_UART0->DATA;

  //Convert CR to LF
  if(my_ch == '\r')
	  my_ch = '\n';

  return (my_ch);
}

// Get line from terminal
unsigned int GetLine (char *lp, unsigned int len)
{
   unsigned int cnt = 0;
   char c;

    do {
        c = UartGetc ();
        switch (c) {
            case CNTLQ:                       /* ignore Control S/Q             */
            case CNTLS:
                break;
            case BACKSPACE:
            case DEL:
                if (cnt == 0) {
                    break;
                }
                cnt--;                         /* decrement count                */
                lp--;                          /* and line pointer               */
                UartPutc (0x08);                /* echo backspace                 */
                UartPutc (' ');
                UartPutc (0x08);
                fflush (stdout);
                break;
            case ESC:
            case 0:
            	*lp = 0;                       /* ESC - stop editing line        */
            	return (FALSE);
            case CR:                           /* CR - done, stop editing line   */
            	*lp = c;
            	lp++;                          /* increment line pointer         */
            	cnt++;                         /* and count                      */
            	c = LF;
            default:
            	UartPutc (*lp = c);             /* echo and store character       */
            	fflush (stdout);
            	lp++;                          /* increment line pointer         */
                cnt++;                         /* and count                      */
            	break;
        }
    } while (cnt < len - 2  &&  c != LF);        /* check limit and CR             */
    *lp = 0;                                   /* mark end of string             */
    return (TRUE);
}

#else
// Simulation
void UartStdOutInit(void)
{
  CMSDK_UART0->BAUDDIV = 16;
  CMSDK_UART0->CTRL    = 0x41; // High speed test mode, TX only
  return;
}
// Output a character
unsigned char UartPutc(unsigned char my_ch)
{
  while ((CMSDK_UART0->STATE & 1)); // Wait if Transmit Holding register is full
  CMSDK_UART0->DATA = my_ch; // write to transmit holding register
  return (my_ch);
}
// Get a character
unsigned char UartGetc(void)
{
  while ((CMSDK_UART0->STATE & 2)==0); // Wait if Receive Holding register is empty
  return (CMSDK_UART0->DATA);
}
#endif

void UartEndSimulation(void)
{
  UartPutc((char) 0x4); // End of simulation
  while(1);
}

