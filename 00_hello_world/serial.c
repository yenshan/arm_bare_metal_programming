#include "serial.h"

#define UART_NUM 3

struct pl011_t {
  uint32_t DR;             /* Data register */
  uint32_t RSR_ECR;        /* Recieve status register/error clear register */
  uint8_t reserved1[0x10]; 
  const uint32_t FR;       /* Flag register */
  uint8_t reserved2[0x4];
  uint32_t LPR;            /* IrDA low-power counter register */
  uint32_t IBRD;           /* Integer baud rate register */
  uint32_t FBRD;           /* Fractional baud rate register */
  uint32_t LCR_H;          /* Line control register */
  uint32_t CR;             /* Control register */
  uint32_t IFLS;           /* Interrupt FIFO level select register */
  uint32_t IMSC;           /* Interrupt mask set/clear register */
  const uint32_t RIS;      /* Raw Interrupt status register */
  const uint32_t MIS;      /* Masked Interrupt status register */
  uint32_t ICR;            /* Interrupt clear register */
  uint32_t DMACR;          /* DMA control register */
}; 

#define UART0 ((volatile struct pl011_t *)0x101f1000)
#define UART1 ((volatile struct pl011_t *)0x101f2000)
#define UART2 ((volatile struct pl011_t *)0x101f3000)

#define TXFF (1<<5)  /* Transmit FIFO full */
#define RXFE (1<<4)  /* Recieve FIFO empty */

volatile struct pl011_t *uarts[UART_NUM] = {
  UART0,
  UART1,
  UART2
};

static int uart_send_byte(int num, unsigned char c)
{
  volatile struct pl011_t *uart = uarts[num];

  /* wait until transimit FIFO is not full */
  while(uart->FR & TXFF)
    ;
  uart->DR = c;

  return 0;
}

void puts(const char *s)
{
  while(*s != '\0') {
    uart_send_byte(0, *s);
    s++;
  }
}

