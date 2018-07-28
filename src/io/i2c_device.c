/*******************************************************************************
    Daniel Verner
    vernerd@gmail.com
  *****************************************************************************/

/*----------------------------------------------------------------------------*/

#include <io/i2c_device.h>
#include <watchdog/watchdog.h>

/*----------------------------------------------------------------------------*/

u8_t* writeBuffer;
u8_t* readBuffer;
u8_t  bytesToWrite;
u8_t  bytesToRead;

/*----------------------------------------------------------------------------*/

static void ack_polling( const I2cDevice* );
static void I2cDevice_write_init( const I2cDevice* );
static void I2cDevice_read_init( const I2cDevice* );
static bool_t I2cDevice_init( const I2cDevice* );

/*----------------------------------------------------------------------------*/  

void I2cDevice_ctor( I2cDevice* self, u8_t slaveAddress, enum OperationMode operationMode, 
					enum I2cCommSpeed commSpeed )
{
	self->slaveAddress = slaveAddress;
	self->operationMode = operationMode;
	self->commSpeed = commSpeed;

	I2cDevice_init( self );
}

/*----------------------------------------------------------------------------*/

int I2cDevice_write( const I2cDevice* self, void* data, size_t size )
{
	writeBuffer = data;
	bytesToWrite = size;
	I2cDevice_init(self);
	while (I2CDCTL&I2CBUSY);                                             
	I2cDevice_write_init(self);
	I2CNDAT = size;
	I2CTCTL |= I2CSTT+I2CSTP;                                            // Generate start and stop condition
	
	ack_polling(self);
	return TRUE;
}

/*----------------------------------------------------------------------------*/

i_t I2cDevice_read( const I2cDevice* self, void* data, size_t size )
{
	return 1;
}

/*----------------------------------------------------------------------------*/

/*
   Initialize the I2C communication
*/

bool_t I2cDevice_init( const I2cDevice* self )
{
	_DINT();
	
	P3SEL = BIT1 + BIT3;   
	UCTL0 |= SWRST; 
	IE1 &= ~URXIE0;                                // Disable USART0 RX interrupt  
	IE1 &= ~UTXIE0;                                // Disable USART0 RX interrupt    
	U0CTL &= ~CHAR;                            
	ME1 &= ~UTXE0;
	ME1 &= ~URXE0;                           
	U0CTL |= I2C+SYNC;                            // USART0 module in I2C mode
	U0CTL &= ~I2CEN;                              // Disable the I2C module
	I2CTCTL = I2CTRX+I2CSSEL_2;                   // Clock from SMCLK
	
	I2CSA = self->slaveAddress;                         // Set the slave address
	
	I2COA = 0x01A5;                               // Own address setup
	u8_t divider = (u8_t)((f32_t)_MAIN_FREQUENCY / ( 2 * ( (f32_t)self->commSpeed * 1000 ) ) - 2);
	//u8_t divider = 0x04;
	I2CPSC = 0;                                // Clock divider = 1
	I2CSCLH = divider;                               // SCL high = 2*I2C clock
	I2CSCLL = divider;                               // SCL low  = 2*I2C clock
	U0CTL |= I2CEN;                               // Enable the I2C module
	_EINT();
	return TRUE;
}

/*----------------------------------------------------------------------------*/

///*
//   Read from the Tas3103
//*/
//
//bool_t read_TAS( u8_t addr, u8_t subAddr, u8_t* buffer, u8_t size )
// {
//
//  init_I2C(addr);   
//   
//  readBuffer = buffer;
//  while (I2CDCTL&I2CBUSY);                      // Var, amig az I2C modul szabad lesz
//
//  writeBuffer = &subAddr;                          // Tarolja a TAS SubAddresst
//  bytesToWrite = 1;
//
//  I2C_write_init();                               // I2C inicializacioja irasra
//  I2CNDAT = 1;                                  // conrol bajt, es a ket cim bajt kuldese
//  I2CIFG &= ~ARDYIFG;                           // Access ready interrupt flag torlese
//  I2CTCTL |= I2CSTT;                            // Start es stop feltetel generalasa
//                                                // I2C kommunikacio indul csak START feltetel kell!!!
//
//  while ((~I2CIFG)&ARDYIFG);                    // megvarja, amig az atvitel befejezodik
//  I2C_read_init();                                // Olvasas inicializalo alprogram
//  I2CNDAT = size;                               // Byte_Num - nyi bajtot fogad
//
//  bytesToRead = size;
//  I2CIFG &= ~ARDYIFG;                           // Access ready interrupt flag torlese
//  I2CTCTL |= I2CSTT + I2CSTP;                   // Fogadas inditasa, majd a vegen stop feltetel kuldese
//
// while ((~I2CIFG)&ARDYIFG);                     // Megvarja, mig vegeter az atvitel
//
//return TRUE;
// 
//}

/*----------------------------------------------------------------------------*/

/*
Initializing I2C bus for writing
*/

void I2cDevice_read_init( const I2cDevice* self )

{
  I2CTCTL &= ~I2CTRX;                           // Receive mod
  I2CIE = RXRDYIE;                              // Receive ready interrupt engedelyezese
}

/*----------------------------------------------------------------------------*/

/*
   Initializing I2C bus for writing
*/

void I2cDevice_write_init( const I2cDevice* self )

{
  U0CTL |= MST;                                 // define Master Mode
  I2CTCTL |= I2CTRX;                            // I2CTRX=1 => Transmit Mode (R/W bit = 0)
  I2CIFG &= ~TXRDYIFG;                          
  I2CIE = TXRDYIE;                              // Enable transmit ready interrupt
}

/*----------------------------------------------------------------------------*/

/*
   ACK polling from I2C bus
*/

void ack_polling( const I2cDevice* self )
{
	init_watchdog();
  while (I2CDCTL&I2CBUSY);                      // wait till stop bit is reset
  U0CTL &= ~I2CEN;                              // clear I2CEN bit => necessary to re-configure I2C module
  I2CTCTL |= I2CRM;                             // transmission is software controlled
  U0CTL |= I2CEN;                               // enable I2C module
  I2CIFG = NACKIFG;                             // set NACKIFG
  while (NACKIFG & I2CIFG)                      // amig NACKFG =1 addig hajtja vegre
  {
    I2CIFG=0x00;                                // clear I2C interrupt flags
    U0CTL |= MST;                               // define Master Mode
    I2CTCTL |= I2CTRX;                          // I2CTRX=1 => Transmit Mode (R/W bit = 0)
    I2CTCTL |= I2CSTT;                          // start condition is generated
    while (I2CTCTL&I2CSTT);                     // wait till I2CSTT bit was cleared
                                                // (amikor a start feltetelt kikuldte, automatikusan torlodik a bit)

    I2CTCTL |= I2CSTP;                          // stop condition is generated after slave address was sent
                                                //      => I2C communication is started

    while (I2CDCTL&I2CBUSY);                    // wait till stop bit is reset
	
  }
 	stop_watchdog();
  U0CTL &= ~I2CEN;                              // clear I2CEN bit => necessary to re-configure I2C module
  I2CTCTL &= ~I2CRM;                            // transmission is by the I2C module
  U0CTL |= I2CEN;                               // enable I2C module


}

/*---------------------------------------------------------------------------*/
/*  Interrupt routine                                               */


    #pragma vector=USART0TX_VECTOR
    __interrupt void ISR_I2C(void)

{
  switch (I2CIV)
  { case I2CIV_AL:                                                      /* I2C interrupt vector: Arbitration lost (ALIFG) */
                      break;
    case I2CIV_NACK:                                                    /* I2C interrupt vector: No acknowledge (NACKIFG) */
                      break;
    case I2CIV_OA:                                                      /* I2C interrupt vector: Own address (OAIFG) */
                      break;
    case I2CIV_ARDY:                                                    /* I2C interrupt vector: Access ready (ARDYIFG) */
                      break;
    case I2CIV_RXRDY:                                                   /* I2C interrupt vector: Receive ready (RXRDYIFG) */
                      bytesToRead--;         
                      *readBuffer++ = I2CDRB;
                      if ( bytesToRead <= 0 )                               
                      {   
                        I2CIE &= ~TXRDYIE;                              // ha elkuldte az adatokat, akkor interrupt tiltasa
                      }                      
                      break;
    case I2CIV_TXRDY:                                                   /* I2C interrupt vector: Transmit ready (TXRDYIFG) */
						reset_watchdog();
                      I2CDRB = *writeBuffer++;                           // kuldendo adat betoltese a regiszterbe
                      bytesToWrite--;                                 
                      if ( bytesToWrite <= 0 )                               
                      {   
                        I2CIE &= ~TXRDYIE;                              // ha elkuldte az adatokat, akkor interrupt tiltasa
                      }
                      break;
    case I2CIV_GC:                                                      /* I2C interrupt vector: General call (GCIFG) */
                      break;
    case I2CIV_STT:                                                     /* I2C interrupt vector: Start condition (STTIFG) */
                      break;
  }
}

// Watchdog Timer interrupt service routine
#pragma vector=WDT_VECTOR
__interrupt void watchdog_timer(void)
{
  //shit happened
	I2CDCTL |= I2CBUSY;
	
}
