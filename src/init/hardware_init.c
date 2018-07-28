/*******************************************************************************

    Initializing the hardware modules
    =================================
   

    Daniel Verner
    vernerd@gmail.com
  *****************************************************************************/

#include <init/hardware_init.h>

/*----------------------------------------------------------------------------*/

static bool_t clock_init (void);
static bool_t port_init (void);
static bool_t led_init (void);
static bool_t led_init (void);
/* static bool_t dma_init(void); */

/*----------------------------------------------------------------------------*/

void reset_lcd()
{
	P4OUT &= ~0x20;
	for( i_t i = 0; i < 100; i++ );
	
	P4OUT |= 0x20;
}

void test_lcd()
{
  P5SEL |= 0xA;                             // P5.1,3 SPI option select
  P5DIR |= 0xB;                             // P5.0,1,3 output direction	
  
  ME2 |= USPIE1;                            // Enable USART1 SPI
  UCTL1 |= CHAR + SYNC + MM;                // 8-bit SPI Master **SWRST**
  UTCTL1 = CKPH + SSEL0 + STC;       // Inv. delayed, ACLK, 3-pin
  UBR01 = 0x8;                              // ACLK/2 for baud rate
  UBR11 = 0x8;                              // ACLK/2 for baud rate
  UMCTL1 = 0x0;                             // Clear modulation
  UCTL1 &= ~SWRST;                          // Initialize USART state machine
}

/*
Initializing the hardware modules
*/

bool_t hardware_init (void)
{
  clock_init();
  port_init();
  //reset_lcd();
  //test_lcd();
  //led_init();
 
  
  return TRUE;
}

/*----------------------------------------------------------------------------*/

/*
Basic clock module initialization
*/
  
static bool_t clock_init (void)                                                  
{

  volatile unsigned int i;
  WDTCTL = WDTPW + WDTHOLD;                 // Stop WDT
//  BCSCTL1 = 0x00;
////  BCSCTL1 = DIVA_0;                // CS freq
////  BCSCTL1 |= XTS;                           // ACLK= LFXT1 = HF XTAL
//
////  do
////  {
////  IFG1 &= ~OFIFG;                           // Clear OSCFault flag
////  for (i = 0xFF; i > 0; i--);               // Time for flag to set
////  }
////  while ((IFG1 & OFIFG));                   // OSCFault flag still set?
//  //BCSCTL2 = DIVM_0;                          //TAS freq
//  BCSCTL2 |= SELS + SELM_2;                      // MCLK= XT2 SMCLK=XT2
//  DCOCTL = 0x00;
//  
//  return TRUE;
	
	  //BCSCTL1 &= ~XT2OFF;                       // XT2= HF XTAL

    BCSCTL2 = 0x00;
	
	BCSCTL2 |= SELM_1;                  // SMCLK = MCLK= DCO (safe)	
	BCSCTL1 |= RSEL0 + RSEL1 + RSEL2 + XT2OFF;
	DCOCTL = DCO0 + DCO1 + DCO2;  
  
	  do
	  {
	  IFG1 &= ~OFIFG;                           // Clear OSCFault flag
	  for (i = 0xFF; i > 0; i--);               // Time for flag to set
	  }
	  while ((IFG1 & OFIFG));                   // OSCFault flag still set?
	
	return TRUE;	  
}

/*----------------------------------------------------------------------------*/

/*
Initialize the MSP ports (Default state)
*/
  
static bool_t port_init (void)                                                  
{
  
    /* PORT1 SETUP */
/*
    TAS_RESET_SEL = 0x00;
    TAS_RESET_DIR = RESET_TAS1 + RESET_TAS2 + RESET_TAS3 + RESET_TAS4 + OUT_EN + CPLD_SET_RESET;
    TAS_RESET_OUT = 0x00;*/
    
    /* PORT2 SETUP */ 
	/*
    CPLD_SEL = 0x00;
    CPLD_DIR = P20 + P21 + P22 + P23;
    CPLD_OUT = 0x00;*/
    
	//P2DIR = 0x80;
	
    /* PORT3 SETUP */ 
	
    I2C_SEL = SDA + SCL;
    I2C_DIR = LCD_RESET;
    I2C_OUT = 0x00;

    /* PORT4 SETUP */ 
    P4SEL   = 0x00;
    P4DIR   = 0x00;
    P4OUT   = 0x00;
    
    /* PORT5 SETUP */
	/*
    LED_SEL = MCLK;
    LED_DIR = MCLK + D5 + D6;
    LED_OUT = 0x00;*/

    /* PORT6 SETUP */
	/*
    P6SEL = 0x00;
    P6DIR = 0x00;
    P6OUT = 0x00;    */
  
  return TRUE;
}

/*----------------------------------------------------------------------------*/

/*
Initialize the LED outputs (Default state)
*/
  
static bool_t led_init (void)                                                  
{
    LED_D5_ON;
    LED_D6_OFF;
    return TRUE;
}  

/*----------------------------------------------------------------------------*/

/*
DMA initialization
*/
/*
static bool_t dma_init(void)
  {
  
    DMA2SA = U1RXBUF_;                                                                                                        // Engedelyezi a fejlec fogadasat
    DMA2DA = (short)(&g_spiDev) + sizeof(CommDevice_Vtbl*) + sizeof(CommController*)+1;                                       // DMA0 destination address beallitasa
    DMA2SZ = 2;                                                                                                               // DMA0 szamlalo beallitasa
    DMA2CTL = DMADSTINCR_2 + DMASBDB + DMAIE + DMAEN + DMALEVEL;                                                              // DMA0 beallitasai, DMA inditasa
    DMACTL0 = DMA0TSEL_9 + DMA1TSEL_10 + DMA2TSEL_9;                                                                          // UART1 receive, esemenyre lesz aktiv a DMA0  

  return TRUE;    
}
*/
