/*******************************************************************************

    Register and bit definitions for the board
    ========================================================
   

    Daniel Verner
    vernerd@gmail.com
  *****************************************************************************/


#ifndef _BOARD_H_
#define _BOARD_H_

#include <msp430x16x.h>
#include <setup/setup.h>
#include <types/types.h>

/*==============================================================================
   Register and bit definitions for the filter module board
  ============================================================================*/

    /* PORT1 */
    #define KEYBOARD_SEL       P1SEL
    #define KEYBOARD_DIR       P1DIR
    #define KEYBOARD_IN        P1IN
    #define KEYBOARD_OUT       P1OUT
	#define KEYBOARD_IES	   P1IES
	#define KEYBOARD_IE 	   P1IE
	#define KEYBOARD_IFG 	   P1IFG
    
    /* PORT1 bit definitions*/
    #define KEY_3      0x01
    #define KEY_2      0x02
    #define KEY_1      0x04
    #define KEY_0      0x08  
	#define SPEED_SENSOR 0x10
//    #define NC              0x10
//    #define NC              0x20    
//    #define NC              0x40            
//    #define NC              0x80  

/*----------------------------------------------------------------------------*/

    /* PORT2 */
    #define CPLD_SEL   P2SEL
    #define CPLD_DIR   P2DIR
    #define CPLD_IN    P2IN
    #define CPLD_OUT   P2OUT

	/* PORT2 bit definitions*/
    #define P20        0x01
    #define P21        0x02
    #define P22        0x04
    #define P23        0x08  
/*  #define NC         0x10
    #define NC         0x20 
    #define NC         0x40 
    #define NC         0x80 */

/*----------------------------------------------------------------------------*/

    /* PORT3 */
    #define I2C_SEL         P3SEL
    #define I2C_DIR         P3DIR
    #define I2C_IN          P3IN
    #define I2C_OUT         P3OUT
    
    
    /* PORT3 bit definitions*/
/*	#define NC              0x01 */
    #define SDA             0x02
  	#define LCD_RESET       0x04
    #define SCL             0x08  
    #define DI              0x10 
    #define RO              0x20 
    #define RE              0x40            
    #define DE              0x80 

/*----------------------------------------------------------------------------*/
    
    /* PORT4 */
/*  #define NC    P4SEL
    #define NC    P4DIR
    #define NC    P4IN
    #define NC    P4OUT */
    

    /* PORT4 bit definitions*/
/*  #define NC              0x01
    #define NC              0x02
    #define NC              0x04
    #define NC              0x08  
    #define NC              0x10
    #define NC              0x20
    #define NC              0x40           
    #define NC              0x80*/

/*----------------------------------------------------------------------------*/
    
    /* PORT5 */
    #define LED_SEL         P5SEL
    #define LED_DIR         P5DIR
    #define LED_IN          P5IN
    #define LED_OUT         P5OUT
    
    
    /* PORT5 bit definitions*/
/*    #define D6              0x01
    #define D5              0x02*/
/*  #define NC              0x04
    #define NC              0x08 */
    #define MCLK            0x10
    #define D6              0x20
    #define D5              0x40            
/*    #define NC              0x80 */

/*----------------------------------------------------------------------------*/

    /* PORT6 */
/*
    #define NC         P6SEL
    #define NC         P6DIR
    #define NC         P6IN
    #define NC         P6OUT   */
    
    /* PORT6 bit definitions*/
/*  #define NC              0x01 
    #define NC              0x02
    #define NC              0x04 
    #define NC              0x08  
    #define NC              0x10
    #define NC              0x20
    #define NC              0x40            
    #define NC              0x80 */

/*----------------------------------------------------------------------------*/

/*=============================================================================
   Useful macros for the board
  ============================================================================*/

    /* LEDS */
    #define LED_D5_ON       LED_OUT &= ~D5
    #define LED_D5_OFF      LED_OUT |= D5

    #define LED_D5_TOGGLE       LED_OUT ^= D5;
                              
    #define LED_D6_ON       LED_OUT &= ~D6
    #define LED_D6_OFF      LED_OUT |= D6

    #define LED_D6_TOGGLE       LED_OUT ^= D6;

#endif