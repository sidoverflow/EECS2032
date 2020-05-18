#include <stdio.h>
#include "board.h"
#include "peripherals.h"
#include "pin_mux.h"
#include "clock_config.h"
#include "MKL43Z4.h"
#include "fsl_debug_console.h"

void PORTC_PORTD_IRQHandler(void) {
   switch(PORTC->ISFR) { // when there is an interrupt, the corresponding bit=1
        case(0b1000): // there is an interrupt on pin 3
            PORTC->PCR[3] |= PORTC_PCR_ISF_MASK; //clear the flag
            PTE->PDOR = (1 << 31); // turn red LED OFF
            break;
}

void SysTick_Handler(void);

int main(void) {
  /* Init board hardware. */
  BOARD_InitBootPins();
  BOARD_InitBootClocks();
  BOARD_InitBootPeripherals();
  /* Init FSL debug console. */
  BOARD_InitDebugConsole();
  PRINTF("Hello World \n");

  __disable_irq();
  NVIC_DisableIRQ(PORTC_PORTD_IRQn);

  SIM->SCGC5 |= ((1 << 11) | (1 << 12) | (1 << 13));
  PORTC->PCR[3] |= 0x103;
  PORTD->PCR[5] = 0x100; // PORT D PIN 5 GPIO (mux = 1) PS=PE=0 no pull up or down - LEDG
  PORTE->PCR[31] = 0x100; // PORT E PIN 31 GPIO (mux = 1) PS=PE=0 no pull up or down - LEDR

  PTC->PDDR &=~0x08;
  PTD->PDDR |= (1 << 5); // set bit 5 of PORT D to 1 (PIN 5 is output)
  PTE->PDDR |= (1 << 31); // set bit 5 of PORT E to 1 (PIN 31 is output)

  PTD->PDOR = (0 << 5);
  PTE->PDOR = (0 << 31);

  PORTC->PCR[3] &= ~0xF0000;   //Set field IRQC to 0000 (disable ISF)
  PORTC->PCR[3] |= 0xA0000; //Set field IRQC to 1010 (ISF flag and falling edge)
  NVIC_SetPriority(PORTC_PORTD_IRQn, 192);
  NVIC_ClearPendingIRQ(PORTC_PORTD_IRQn);
  NVIC_EnableIRQ(PORTC_PORTD_IRQn);
  __enable_irq();

  SysTick->CTRL |= 1<<0 | 1<<2; //use system clock, initialize, No interrupt
  SysTick->LOAD = 0xF8954400;

  while(1) {
       while((SysTick->CTRL & 0x10000) == 0) {} // wait for the flag to set

       PTE->PDOR = (1 << 31); //turn green LED OFF
  }
}
