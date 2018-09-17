#include "delay.h"
#include "pindefine.h"
#include "ET011TT2.h"

#include "main.h"

//==============================================================================
// MSP430 MCU initial function
//==============================================================================
void SetVcoreUp(unsigned int level) {
  // Open PMM registers for write
  PMMCTL0_H = PMMPW_H;
  // Set SVS/SVM high side new level
  SVSMHCTL = SVSHE + SVSHRVL0 * level + SVMHE + SVSMHRRL0 * level;
  // Set SVM low side to new level
  SVSMLCTL = SVSLE + SVMLE + SVSMLRRL0 * level;
  // Wait till SVM is settled
  while ((PMMIFG & SVSMLDLYIFG) == 0)
    ;
  // Clear already set flags
  PMMIFG &= ~(SVMLVLRIFG + SVMLIFG);
  // Set VCore to new level
  PMMCTL0_L = PMMCOREV0 * level;
  // Wait till new level reached
  if ((PMMIFG & SVMLIFG))
    while ((PMMIFG & SVMLVLRIFG) == 0)
      ;
  // Set SVS/SVM low side to new level
  SVSMLCTL = SVSLE + SVSLRVL0 * level + SVMLE + SVSMLRRL0 * level;
  // Lock PMM registers for write access
  PMMCTL0_H = 0x00;
}

void SetClockSystem_25MHz(void) {
  // 25MHz

  // Increase Vcore setting to level3 to support fsystem=25MHz
  // NOTE: Change core voltage one level at a time..
  SetVcoreUp(0x01);
  SetVcoreUp(0x02);
  SetVcoreUp(0x03);

  UCSCTL3 = SELREF_2; // Set DCO FLL reference = REFO
  UCSCTL4 |= SELA_2;  // Set ACLK = REFO

  __bis_SR_register(SCG0); // Disable the FLL control loop
  UCSCTL0 = 0x0000;        // Set lowest possible DCOx, MODx
  UCSCTL1 = DCORSEL_7;     // Select DCO range 50MHz operation
  UCSCTL2 = FLLD_1 + 762;  // Set DCO Multiplier for 25MHz
                           // (N + 1) * FLLRef = Fdco
                           // (762 + 1) * 32768 = 25MHz
                           // Set FLL Div = fDCOCLK/2
  __bic_SR_register(SCG0); // Enable the FLL control loop

  // Worst-case settling time for the DCO when the DCO range bits have been
  // changed is n x 32 x 32 x f_MCLK / f_FLL_reference. See UCS chapter in 5xx
  // UG for optimization.
  // 32 x 32 x 25 MHz / 32,768 Hz ~ 780k MCLK cycles for DCO to settle
  __delay_cycles(782000);

  // Loop until XT1,XT2 & DCO stabilizes - In this case only DCO has to
  // stabilize
  do {
    UCSCTL7 &= ~(XT2OFFG + XT1LFOFFG + DCOFFG);
    // Clear XT2,XT1,DCO fault flags
    SFRIFG1 &= ~OFIFG;       // Clear fault flags
  } while (SFRIFG1 & OFIFG); // Test oscillator fault flag

  // 25MHz setup done
}

//===========================================================================================
void main(void) {
  //==============================================================================
  // MSP430 MCU initial setting
  //==============================================================================
  WDTCTL = WDTPW + WDTHOLD; // Stop watchdog timer
  SetClockSystem_25MHz();

  P1DIR |= BIT0 | BIT7;        // Set P1.7,P1.0 to output direction
  P1DIR &= 0x81;               // Set P1.1~P1.6 to input direction
  P5DIR |= BIT0 | BIT1;        // Set P5.0,P5.1 to output direction
  P5DIR &= 0x03;               // Set P5.2~P5.7 to input direction
  P4DIR |= BIT6 | BIT7;        // Set P4.6,P4.7 to output direction
  P4DIR &= 0xC0;               // Set P4.0~P4.5 to input direction
  P6DIR |= BIT0 | BIT1 | BIT3; // Set P6.0,P6.1,P6.3 to output direction
  P6DIR &= 0x0B;               // Set P6.2,P6.4~P6.7 to input direction

  P1REN |= BIT2 | BIT3 | BIT4 | BIT5;
  P1OUT |= BIT2 | BIT3 | BIT4 | BIT5;
  P1IES |= BIT2 | BIT3 | BIT4 | BIT5;
  P1IFG &= ~0x3C;
  P1IE |= BIT2 | BIT3 | BIT4 | BIT5;
  //==============================================================================
  // EPD main function
  //==============================================================================
  P1OUT |= BIT0; // Turn on LED
  EPD_Init();    // second Initial
  EPD_Display_White();
  EPD_Display_Black();
  EPD_Display_White();
  P1OUT &= 0xFE; // Turn off LED
}
//===========================================================================================
