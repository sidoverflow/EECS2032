#include <stdio.h>
#include "board.h"
#include "peripherals.h"
#include "pin_mux.h"
#include "clock_config.h"
#include "MKL43Z4.h"
#include "fsl_debug_console.h"

int main(void) {
    /* Init board hardware. */
  BOARD_InitBootPins();
  BOARD_InitBootClocks();
  BOARD_InitBootPeripherals();
  /* Init FSL debug console. */
  BOARD_InitDebugConsole();
  PRINTF("Hello World\n");

  SIM->SCGC5 |= ((1 << 9) | (1 << 11) | (1 << 12) | (1 << 13));

  PORTA->PCR[4] = 0x103; // PORT A PIN 4 GPIO (mux = 001) PS=PE=1 pull up resistor - SW1
  PORTC->PCR[3] = 0x103; // PORT C PIN 3 GPIO (mux = 001) PS=PE=1 pull up resistor - SW3

  PORTD->PCR[5] = 0x100; // PORT D PIN 5 GPIO (mux = 1) PS=PE=0 no pull up or down - LEDG
  PORTE->PCR[31] = 0x100; // PORT E PIN 31 GPIO (mux = 1) PS=PE=0 no pull up or down - LEDR

  PTA->PDDR &= ~(0x10); // set bit 4 of PORT A to 0 (input)
  PTC->PDDR &= ~(0x08); // set bit 3 of PORT C to 0 (input)

  PTD->PDDR |= (1 << 5); // set bit 5 of PORT D to 1 (PIN 5 is output)
  PTE->PDDR |= (1 << 31); // set bit 5 of PORT E to 1 (PIN 31 is output)

  //initial state before any switches are pressed, both LEDs are OFF
  PTD->PDOR = (1 << 5);
  PTE->PDOR = (1 << 31);

  volatile static int i = 0;
  volatile static int j = 0;

  while (1) {
    i = PTA->PDIR & (1 << 4);
    j = PTC->PDIR & (1 << 3);

    // if i is false, i.e. pressed and j is true, i.e. not pressed
    if (!i && j) {
      // both LEDs are ON
      PTD->PDOR = (0 << 5);
      PTE->PDOR = (0 << 31);
    }

    // if j is false, i.e. pressed and i is true, i.e. not pressed
    else if (!j && i) {
      // LEDG is ON, LEDR is OFF
      PTD->PDOR = (0 << 5);
      PTE->PDOR = (1 << 31);
    }

    // if i and j are true, i.e. not pressed
    else if (i && j) {
      // both LEDs are OFF
      PTD->PDOR = (1 << 5);
      PTE->PDOR = (1 << 31);
    }

    // if i and j are false, i.e. pressed
    else if (!i && !j) {
      // releasing any switch will make LEDG OFF and LEDR ON
      if (i || j) {
        PTD->PDOR = (1 << 5);
        PTE->PDOR = (0 << 31);
      }
    }
  }
}
