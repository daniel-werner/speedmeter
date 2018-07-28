
//#include "io430.h"
#include <gui/display.h>
#include <gui/displayobjects/point.h>
#include <gui/displayobjects/line.h>
#include <gui/displayobjects/circle.h>
#include <gui/displayobjects/bitmap.h>
#include <init/hardware_init.h>
#include <io/i2c_device.h>
//#include <gui/lcd.h>
#include <string.h>
#include <gui/drivers/PCF_8548_driver.h>
//#include <gui/font.h>
//#include <gui/ms_sans_serif.h>
#include <gui/displayobjects/character.h>
#include <gui/displayobjects/text.h>
#include <types/string.h>
#include <gui/displayobjects/rectangle.h>
#include <gui/displayobjects/mask.h>
#include <gui/images/background.h>
#include <menu/keyboard.h>
#include <menu/menu.h>
#include <menu/about.h>
#include <timer/timer.h>
#include <io/interrupt_device.h>
//#include <gui/images/base.h>
#include <types/bcd.h>
#include <timer/rtc.h>

//#include <gui/images/splash.h>
//#include <gui/images/gauge.h>

#include <menu/menu_states.h>
#include <io/speed_meter.h>

#include <system/system.h>

//Point p;
//Line line;
//Circle circle;
Bitmap bitmap;
//Character character;
//Text text;
//String string;
//Rectangle rect;
//Mask mask;
Keyboard keyb;
Menu menu;
Rtc rtc = {2010,3,27,817,12,0};

state_t menuState;

int main( void )
{
	System* pSystem;	
	// Stop watchdog timer to prevent time out reset
	WDTCTL = WDTPW + WDTHOLD;
	_DINT();
	//P2DIR = 0x80;
	//P2OUT &= ~0x80;
	//P2OUT |= 0x80;
	
	//I2cDevice iodevice;
	
	hardware_init();
	
	pSystem = System_get_instance();
	//_BIS_SR(LPM3_bits);                       // Enter LPM0		    
	//Settings_get_instance();
	SpeedMeter_get_instance();
	//Keyboard_ctor( &keyb );
	Menu_ctor( &menu );
	menu.iconX = 2;
	menu.iconY = 15;
	menu.iconWidth = 32;
	menu.iconHeight = 32;
	
////	I2cDevice iodevice;
////	I2cDevice_ctor( &iodevice, 0x3C, OP_MODE_MASTER, I2C_COMM_SPEED_400 );
//
//	//for( i_t i = 0; i<255; i++);	
//	//P2OUT &= ~0x80;	
//
////	for( i_t i = 0; i<10000; i++)
////		for(i_t j=0; j<100; j++)
////		{
////			
////		}
//	//P2OUT |= 0x80;	
//
//	//for( i_t i = 0; i<100; i++);
//	
////	u8_t com[] = {0x00, 0x21, 0x16, 0xEA, 0x30, 0x0C };
////	I2cDevice_write( &iodevice, com, 6 );
////	u8_t x = 0x80;
////	
////	u8_t data[256];
//	
//	//while(1)
//	//{
////	i_t count = 65;
////	while(count--)
////	{
////	u8_t data[] = {0x40, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
////	I2cDevice_write( &iodevice, data, 14 );
////	}
//	
//	
////	u8_t coord[] = {0x00,x, 0x40};
////	x++;
////	I2cDevice_write( &iodevice, coord, 3 );
////	for( i_t i = 0; i < 580; i += 254)
////	{
////		data[0] = 0x40;
////		memcpy( &data[1], &lcd[i], 254 );
////		I2cDevice_write( &iodevice, data, 255 );
////	}
////	//}
////
////	u8_t coord1[] = {0x00,0x80, 0x40};
////	I2cDevice_write( &iodevice, coord1, 3 );		
////	
////	i_t count = 65;
////	while(count--)
////	{
////		u8_t data[] = {0x40, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
////		I2cDevice_write( &iodevice, data, 14 );
////	}
////
//	
////	Bitmap_ctor( &bitmap, 0, 0, 98, 64, ms_sans_serif ); 
////	Bitmap_draw( &bitmap );
//	String_ctor( &string, STRING("Ez itt szoveg") );
//	
////	Rectangle_ctor( &rect, 9, 9, 75, 25, 1 );
////	Rectangle_draw( &rect );
////	Text_ctor( &text, 10, 10, &string, 0, FALSE, ms_sans_serif, 11 );
////	Text_draw( &text );
////	
////	Text_ctor( &text, 10, 20, &string, 1, FALSE, calibri, 14 );
////	Text_draw( &text );	
//	
//	string = int2bcd(1567, 4);
//	i_t testNum = bcdString2int( &string );
//	testNum = changeBcdNumber( testNum, 4, 2, -1 );
//	Text_ctor( &text, 10, 10, &string, 0, FALSE, ms_sans_serif, 11 );
//	Text_draw( &text );

//	Mask_ctor( &mask, 0, 0, 98, 64, 1, 0 );
//	Mask_draw( &mask );
	
	Bitmap_ctor( &bitmap, 0, 0, 98, 64, About_get_image(), FALSE ); 
	Bitmap_draw( &bitmap );
	
	Rtc_ctor( &rtc );
	
//	while(1);
//	for( i_t i = 0; i < 20; i++)
//	{
//		Line_ctor( &line, 10, 30 + i, 90, 30 + i, 1 );
//		Line_draw( &line );
//	}
//
//	
////	Text_ctor( &text, 10, 30, &string, 1, TRUE, arial, 14 );
////	Text_draw( &text );		
//	
//	 Character_ctor( &character, 15, 15, 'N', FALSE, ms_sans_serif, 11  );
//	 Character_draw( &character );
//
//	 Character_ctor( &character, 23, 15, 'a', FALSE, ms_sans_serif, 11  );
//	 Character_draw( &character );
//	 
//	 Character_ctor( &character, 30, 15, 'm', TRUE, ms_sans_serif, 11  );
//	 Character_draw( &character );
//
//	 Character_ctor( &character, 40, 15, 'e', TRUE, ms_sans_serif, 11 );
//	 Character_draw( &character );	 
//	 
//	 Character_ctor( &character, 47, 15, 's', TRUE, ms_sans_serif, 11  );
//	 Character_draw( &character );	 	 
//	 
//	Circle_ctor( &circle, 44, 30, 25, 1 );
//	Circle_draw( &circle );	
//	
//	Line_ctor( &line, 0, 30, 90, 30, 1 );
//	Line_draw( &line );
//
//	Line_ctor( &line, 0, 5, 90, 5, 1 );
//	Line_draw( &line );
//	
//	Line_ctor( &line, 0, 55, 90, 55, 1 );
//	Line_draw( &line );	
//	
//	Line_ctor( &line, 44, 0, 44, 62, 1 );
//	Line_draw( &line );	
//
//	Line_ctor( &line, 19, 0, 19, 62, 1 );
//	Line_draw( &line );	
//	
//	Line_ctor( &line, 69, 0, 69, 62, 1 );
//	Line_draw( &line );		
//	
//	Point_ctor( &p, 1, 1, 1 );
//	Point_draw( &p );
//	Point_ctor( &p, 2, 2, 1 );
//	Point_draw( &p );
//	Point_ctor( &p, 3, 3, 1 );
//	Point_draw( &p );
//	Point_ctor( &p, 4, 4, 1 );
//	Point_draw( &p );	
//	
//	Point_ctor( &p, 4, 4, 1 );
//	Point_draw( &p );	
//	Point_ctor( &p, 4, 5, 1 );
//	Point_draw( &p );	
//	Point_ctor( &p, 4, 6, 1 );
//	Point_draw( &p );	
//	Point_ctor( &p, 4, 7, 1 );
//	Point_draw( &p );
//	
//	Point_ctor( &p, 97, 0, 1 );
//	Point_draw( &p );		
//	Point_ctor( &p, 97, 63, 1 );
//	Point_draw( &p );	
//	Point_ctor( &p, 0, 0, 1 );
//	Point_draw( &p );		
//	Point_ctor( &p, 0, 63, 1 );
//	Point_draw( &p );			
//	
//
//	Line_ctor( &line, 90, 0, 0, 60, 1 );
//	Line_draw( &line );
//	
//	Line_ctor( &line, 92, 2, 2, 62, 1 );
//	Line_draw( &line );
//
//	Display_get_instance()->bufferingEnabled = FALSE;
//	
//	Line_ctor( &line, 45, 0, 45, 60, 1 );
//	Line_draw( &line );	
//	
//	Display_get_instance()->bufferingEnabled = FALSE;	
	

//	u8_t color = 0x01;
//	for( coord_t x = 0; x < 102; x++ )
//	{
//		for( coord_t y = 0; y < 64; y++ )
//		{
//			Point_ctor( &p, x, y, color );
//			Point_draw( &p );
//			color ^= 0x01;
//		}
//	}

//	Line line1;
//	
//	Line_ctor( &line, 0, 15, 45, 50, 1 );
//	Line_draw( &line );		
//	
//	Line_ctor( &line1, 0, 15, 46, 50, 1 );
//	Line_draw( &line1 );			
	
	Display_get_instance()->bufferingEnabled = TRUE;

//	Bitmap_ctor( &bitmap, 0, 0, 98, 64, base, FALSE ); 
//	Bitmap_draw( &bitmap );	
	
//	Bitmap_ctor( &bitmap, 0, 58, 98, 64, base, 0 ); 
//	Bitmap_draw_partial( &bitmap, 0, 58, 98, 64 );	
	
//	Bitmap_ctor( &bitmap, 0, 0, 98, 64, base, FALSE ); 
//	Bitmap_draw( &bitmap );	
	_BIS_SR(LPM3_bits + GIE);                       // Enter LPM0		    
	while(1)
	{
		menuState = Menu_process( &menu, FALSE);		
		
		if( menuState != ST_MENU_ABOUT_FUNC )
		{
			SpeedMeter_draw( FALSE, menuState == ST_MENU );
			Rtc_draw( &rtc, FALSE );
		}
		
		_BIS_SR(LPM3_bits + GIE);                       // Enter LPM0		
	}
//	while(1)
//	{
//		if( line.startPoint.x > 90 )
//		{
//			line.color = 0x00;
//			Line_draw( &line );
//			line.color = 0x00;
//			Line_draw( &line1 );			
//			line.startPoint.x = 0;
//			line1.startPoint.x = 1;
//			//line.color ^= 0x01;
//		}
////		for( i_t i = 0; i<1000; i++)
////		for(i_t j=0; j<10; j++)
////		{
////			
////		}
//		
//		coord_t startX = line.startPoint.x < line.endPoint.x ? line.startPoint.x : line.endPoint.x;
//		coord_t endX = line.startPoint.x > line.endPoint.x ? line.startPoint.x : line.endPoint.x;
//		bitmap.position.x = startX;		
//		bitmap.position.y = 15;		
//		Bitmap_draw_partial( &bitmap, startX, 15, endX, 40 );		
//		//line.color = 0x00;
//		//Line_draw( &line );		
//		line.startPoint.x += 1;
//		line.color = 0x01;
//		Line_draw( &line );
//		
//		//line.color = 0x00;
//		//Line_draw( &line1 );		
//		line1.startPoint.x += 1;
//		line1.color = 0x01;
//		Line_draw( &line1 );
//
//	}

//	while(1)
//	{
//		p.x++;
//		p.y++;
//		if( p.x >= 98 )
//		{
//			p.x = 0;
//			//p.y++;
//		}
//		
//		if( p.y >= 64 )
//		{
//			p.y = 0;
//			p.x = 0;
//			p.color ^= 0x01;			
//		}
//		Point_draw( &p );
//	}
	
//	return 0;
}
