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

    SIM_SCGC5  |= (1<<13);

    //set the MUX bits to 0
    PORTE->PCR[22] &= ~(0x700);

    SIM->SCGC6 |= 0x8000000; Set bit 27 of SCGC6 to enable ADC0

    // ADICLK=0 (use bus clock), MODE= 10 (10-bit conversion), ADLSMP=0 (short sample time), ADIV=00 (divide ratio is 1).
    ADC0->CFG1 = 0x00000008;

    // software triggered, no compare function enable, no range enable,  no DMA, and default voltage reference
    ADC0->SC2 = 0x00000001;

    for (;;) {

      // channel 3 selected
      ADC0->SC1[0] = 0x03;

      // bit 7 of ADC0_SC1A is 1 when conversion is complete
      while(!(ADC0->SC1[0] & 0x80)) { }

      // Data is read from ADC0_R0
      Data = ADC0->R[0];

      // display digital value on the monitor
      PRINTF(Data);

    }
}
