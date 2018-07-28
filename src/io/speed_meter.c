/*******************************************************************************
    Daniel Verner
    vernerd@gmail.com
  *****************************************************************************/

/*----------------------------------------------------------------------------*/

#include <io/speed_meter.h>
#include <system/settings.h>
#include <system/system.h>
#include <types/bcd.h>
#include <types/string.h>
#include <math.h>

#include <gui/displayobjects/text.h>
#include <gui/displayobjects/line.h>
#include <gui/displayobjects/bitmap.h>
#include <gui/displayobjects/mask.h>

#include <menu/menu_states.h>

extern Menu menu;

static SpeedMeter speedMeterInstance;
SpeedMeter* speedMeter = NULL;

/*----------------------------------------------------------------------------*/

static bool_t speed_sensor_interrupt( u8_t value );
static u16_t tempDistance = 0;
static Settings* pSettings;
static System* pSystem;

static String speedStr;
static String distanceStr;
static String averageStr;
static String timeStr;

static Text speedTxt;
static Text distanceTxt;
static Text averageTxt;
static Text timeTxt;

static bool_t updateDistance = FALSE;
static bool_t updateSpeed = FALSE;
static bool_t updateTime = FALSE;

static bool_t isMeasureStarted = FALSE;

/*----------------------------------------------------------------------------*/

#define TIMER_FREQ 32.768

#define STANDBY_TIMEOUT 90

#define SPEED_COEFF 117.9648 // TIMER_FREQ * 3.6 / 1000
#define M_PER_S_TO_KM_PER_H_ 3.6
#define TIMER_TIMEOUT 65535
#define TEST_TIMER_VALUE 4000;
//#define TIMER_TIMEOUT TEST_TIMER_VALUE

#define DISTANCE_CHANGE_VALUE 10000 

#define SPEED_DISPLAY_X 30
#define SPEED_DISPLAY_Y 46

#define GAUGE_CENTER_X 47
#define GAUGE_CENTER_Y 46
#define GAUGE_RADIUS 30

#define TOP_DISPLAY_X 57
#define TOP_DISPLAY_Y 0

/*----------------------------------------------------------------------------*/

static void init_timer()
{
	TBCCR0 = TIMER_TIMEOUT;
	TBCTL = TBSSEL0 +  MC_1;		    // TimerA folyamatos mod, ACLK = lfxtal = 32768
	TBR = 0x0000;
	TBCCTL0 |= CCIE;		            // CCTL0 ugyanaz, mint TACCTL0
	
	TBCCR1 = 32767;
//	TBCTL = TBSSEL0 +  MC_1;		    // TimerA folyamatos mod, ACLK = lfxtal = 32768
//	TBR = 0x0000;
	TBCCTL1 |= CAP + CCIE;		            // CCTL0 ugyanaz, mint TACCTL0	
}

/*----------------------------------------------------------------------------*/

#define MAX_GAUGE_SCALE 250
#define GAUGE_NUMBERS 5

static Pixel s_gaugeCoords[MAX_GAUGE_SCALE];
static Pixel s_gaugeNumberCoords[GAUGE_NUMBERS] = {	{0,37,1},
													{10,12,1},
													{41,1,1},
													{72,12,1},
													{84,37,1}};

static const Pixel gaugeGradeCoords[] = { { 19, 46, 1 },
										  { 29, 28, 1 },
										  { 47, 19, 1 },
										  { 65, 28, 1 },
										  { 75, 46, 1 } };

/*----------------------------------------------------------------------------*/

void SpeedMeter_calculate_gauge_coords( SpeedMeter* self, u_t maxSpeed )
{
	if( maxSpeed > MAX_GAUGE_SCALE || maxSpeed == 0 )
	{
		maxSpeed = MAX_GAUGE_SCALE;
	}
	f32_t angleCoeff = (f32_t)__PI / maxSpeed;
	u_t gaugeGrade = (u_t)(maxSpeed / 4);
	f32_t x;
	f32_t y;
	Pixel pixel;
	u_t gaugeGradeCount = 0;
	
	for( i_t i = 0; i <= maxSpeed; i++ )
	{
		if( i % gaugeGrade == 0  )
		{
			pixel = gaugeGradeCoords[ (u_t)( gaugeGradeCount ) ];
			gaugeGradeCount++;
		}
		else
		{
			x = (f32_t)GAUGE_RADIUS * cos( angleCoeff * i );
			y = (f32_t)GAUGE_RADIUS * sin( angleCoeff * i );
			pixel.x = (coord_t)(GAUGE_CENTER_X - round( x ));
			pixel.y = (coord_t)(GAUGE_CENTER_Y - round( y ));			
		}		

		
		s_gaugeCoords[i] = pixel;
	}
}

/*----------------------------------------------------------------------------*/

Mask clearTopMask;

static void SpeedMeter_ctor( SpeedMeter* self )
{
	pSettings = Settings_get_instance();
	pSystem   = System_get_instance();
	
	self->currentTrip = &(pSettings->currentTrip);
	self->dailyTrip = &(pSettings->dailyTrip);	
	self->allTrip = &(pSettings->allTrip);

	InterruptDevice* pInterruptDevice = InterruptDevice_get_instance( 1 );
	u8_t mask = SPEED_SENSOR;
	
	InterruptDevice_set_interrupt( pInterruptDevice, mask, mask );
	InterruptDevice_set_callback( pInterruptDevice, SPEED_SENSOR, speed_sensor_interrupt );	
	
	init_timer();
	Text_ctor( &speedTxt, SPEED_DISPLAY_X, SPEED_DISPLAY_Y, &speedStr, 2, FALSE, digital_7, 14, FALSE );	
	Text_ctor( &timeTxt, TOP_DISPLAY_X, TOP_DISPLAY_Y, &timeStr, 1, FALSE, ms_reference_sans_serif, 12, TRUE );				
	Text_ctor( &averageTxt, TOP_DISPLAY_X, TOP_DISPLAY_Y, &averageStr, 1, FALSE, ms_reference_sans_serif, 12, TRUE );			
	Text_ctor( &distanceTxt, TOP_DISPLAY_X + 2, TOP_DISPLAY_Y, &distanceStr, 1, FALSE, ms_reference_sans_serif, 12, TRUE );		
	Mask_ctor( &clearTopMask, TOP_DISPLAY_X, TOP_DISPLAY_Y, 41, 11, 0x00, FALSE );	
	SpeedMeter_calculate_gauge_coords( self, pSettings->maxSpeed );
}

/*----------------------------------------------------------------------------*/

SpeedMeter* SpeedMeter_get_instance()
{
	if( speedMeter == NULL )
	{
		SpeedMeter_ctor( &speedMeterInstance );
		speedMeter = &speedMeterInstance;
	}

	return speedMeter;
}

/*----------------------------------------------------------------------------*/

u16_t SpeedMeter_calculate_average_speed( SpeedMeter* self, distance_t distance, u32_t seconds )
{
	return (u16_t)(10 * M_PER_S_TO_KM_PER_H_ * distance / seconds );
}

/*----------------------------------------------------------------------------*/

static u16_t s_timerValue = 0;

bool_t SpeedMeter_calculate_speed( SpeedMeter* self, u16_t timerValue )
{
	speed_t speed;
	
	if( timerValue > 0 )
	{
		speed = (speed_t)(pSettings->wheelPerimeter * (f32_t)SPEED_COEFF / timerValue);
	}
	else
	{
		speed = 0;
	}
	
	if( speed != self->currentSpeed )
	{
		updateSpeed = TRUE;
	}			
	
	self->currentSpeed = speed;
	//self->currentSpeed = 25;	
	return TRUE;
}

/*----------------------------------------------------------------------------*/

static Line indicator;

static void SpeedMeter_draw_gauge( SpeedMeter* self )
{
	speed_t speed = ( self->currentSpeed <= pSettings->maxSpeed ) ? self->currentSpeed : pSettings->maxSpeed;

	indicator.color = 0x00;
	Line_draw( &indicator );
	Pixel pixel = s_gaugeCoords[speed];
	Line_ctor( &indicator, GAUGE_CENTER_X, GAUGE_CENTER_Y, pixel.x, pixel.y, 0x01 );
	Line_draw( &indicator );
	Bitmap bitmap;
	Bitmap_ctor( &bitmap, 44, 43, 98, 64, menu.states[0].bitmap, 0 ); 
	Bitmap_draw_partial( &bitmap, 44, 43, 51, 47 );	
}


/*----------------------------------------------------------------------------*/

void SpeedMeter_draw_gauge_numbers( SpeedMeter* self )
{
	Text numTxt;
	String numStr;
	u_t scale = pSettings->maxSpeed >> 2;
	
	
	for( i_t i = 0; i < GAUGE_NUMBERS; i++ )
	{
		numStr = int2bcd( i * scale, 2, FALSE, 0 , 0 );
			
		Text_ctor( &numTxt, s_gaugeNumberCoords[i].x, s_gaugeNumberCoords[i].y,
				  &numStr, i == 0 ? 0 : 1, FALSE, ms_reference_sans_serif, 12, FALSE );
		Text_draw( &numTxt );
	}

}


/*----------------------------------------------------------------------------*/

i8_t topDisplay = 0;

#define TOP_DISPLAY_MAX_VALUE 2

#define TOP_DISPLAY_CURRENT_DISTANCE 0
#define TOP_DISPLAY_CURRENT_ELAPSED_TIME 1
#define TOP_DISPLAY_CURRENT_AVERAGE_SPEED 2

/*----------------------------------------------------------------------------*/

state_t SpeedMeter_change_top_display( Menu* menu, key_t input )
{
	state_t retVal = ST_MENU;	
	switch( input )
	{
		case KEY_UP:
			topDisplay++;
			if( topDisplay > TOP_DISPLAY_MAX_VALUE )
				topDisplay = 0;			
			break;
		case KEY_DOWN:
			topDisplay--;
			if( topDisplay < 0 )
				topDisplay = TOP_DISPLAY_MAX_VALUE;						
			break;
		case KEY_ENTER:
			retVal = ST_MENU_HISTORY;
			break;
		case KEY_ESCAPE:
			retVal = ST_SHUTDOWN_MENU;
			break;
	}

	
	SpeedMeter_draw( TRUE, TRUE );
	return retVal;
}

/*----------------------------------------------------------------------------*/

i8_t prevTopDisplay = 0;
void SpeedMeter_draw_speed_numeric( SpeedMeter* self )
{
	Text bigSpeedTxt;	
	Text_ctor( &bigSpeedTxt, 15, 10, &speedStr, 2, FALSE, digital_7, 36, FALSE );
	Text_draw( &bigSpeedTxt );	
}


void SpeedMeter_draw( bool_t force, bool_t gauge )
{
	SpeedMeter_calculate_speed( speedMeter, s_timerValue );
	if( updateSpeed || updateDistance || updateTime || force )
	{
		if( updateSpeed || force )
		{

			speedStr = int2bcd( speedMeter->currentSpeed, 3, FALSE, 0, 0);
			if( gauge )
			{
				if( pSettings->speedDisplayMode == SPEED_DISPLAY_MODE_NUMERIC )
				{
					SpeedMeter_draw_speed_numeric( speedMeter );
				}
				else
				{
					SpeedMeter_draw_gauge( speedMeter );					
				}

			}
			if( !gauge || pSettings->speedDisplayMode == SPEED_DISPLAY_MODE_GAUGE )
			Text_draw( &speedTxt );			
			//updateSpeed = FALSE;
		}
	
		if( prevTopDisplay != topDisplay )
		{
			Mask_draw( &clearTopMask );			
		}
	
		prevTopDisplay = topDisplay;
		switch( topDisplay )
		{
			case TOP_DISPLAY_CURRENT_DISTANCE:
				if( updateDistance || force )			
				{
					String_ctor( &distanceStr, STRING("km") );
					Text text;
					Text_ctor( &text, 86, 0, &distanceStr, 0, FALSE, ms_reference_sans_serif, 12, TRUE );
					Text_draw( &text );					
					distanceStr = int2bcd( speedMeter->currentTrip->distance, 4, FALSE, 2, 1 );			
					Text_draw( &distanceTxt );																	
					updateDistance = FALSE;			
				}
				break;
			case TOP_DISPLAY_CURRENT_ELAPSED_TIME:
				if( updateTime || force )
				{
					timeStr = Time_to_string( &speedMeter->currentTrip->elapsedTime, TRUE );
					updateTime = FALSE;
					Text_draw( &timeTxt );																	
				}
				break;
			case TOP_DISPLAY_CURRENT_AVERAGE_SPEED:
				if( updateSpeed || force )			
				{
					String_ctor( &distanceStr, STRING("km/h") );					
					Text text;
					Text_ctor( &text, 79, 0, &distanceStr, 0, FALSE, ms_reference_sans_serif, 12, TRUE );
					Text_draw( &text );					
					u16_t avgSpeed = (u16_t)(10 * M_PER_S_TO_KM_PER_H_ * speedMeter->currentTrip->distance / Time_get_seconds( &speedMeter->currentTrip->elapsedTime ));
					averageStr = int2bcd( avgSpeed, 3, FALSE, 0, 1 );			
					Text_draw( &averageTxt );												
					updateSpeed = FALSE;			
				}			
				break;				
				
		}
	}
}

/*----------------------------------------------------------------------------*/

bool_t SpeedMeter_tick( SpeedMeter* self, u16_t timerValue )
{
	s_timerValue = timerValue;
	if( timerValue > 0 )
	{
		tempDistance += pSettings->wheelPerimeter;
		if( tempDistance >= DISTANCE_CHANGE_VALUE )
		{
			u_t distancem = (u_t)(tempDistance / 1000);
			self->currentTrip->distance += distancem;
			self->allTrip->distance += distancem;			
			self->dailyTrip->distance += distancem;
			updateDistance = TRUE;
			tempDistance = 0;		
		}
	}
	
	if( pSystem->standbyCounter >= STANDBY_TIMEOUT )
	{
		System_standby();
	}
	return TRUE;
}

/*----------------------------------------------------------------------------*/

void SpeedMeter_time_tick( SpeedMeter* self )
{
	if( isMeasureStarted )
	{
		updateTime = TRUE;
		Time_tick( &self->currentTrip->elapsedTime );
		Time_tick( &self->dailyTrip->elapsedTime );
		Time_tick_all( &self->allTrip->elapsedTime );	
	}
}

/*----------------------------------------------------------------------------*/

static bool_t speed_sensor_interrupt( u8_t value )
{
	u16_t timerValue = isMeasureStarted ? TBR : 0;
	TBR = 0x0000;	
	bool_t retVal = SpeedMeter_tick( speedMeter, timerValue ) ;
	isMeasureStarted = TRUE;
	System_wakeup();
	return retVal;
}

#pragma vector=TIMERB0_VECTOR
__interrupt void Timer_B_int (void)
{
	isMeasureStarted = FALSE;
//	u16_t timerValue = TBR;
	TBR = 0x0000;

	pSystem->standbyCounter++;
	SpeedMeter_tick( speedMeter, 0 ) ;	
	_BIC_SR_IRQ(CPUOFF); // Wake up processor, update screen		
}
