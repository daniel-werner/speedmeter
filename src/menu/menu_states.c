/*******************************************************************************
    Daniel Verner
    vernerd@gmail.com
  *****************************************************************************/

/*----------------------------------------------------------------------------*/

#include <menu/menu_states.h>
#include <timer/rtc.h>
#include <system/system.h>

//#include <gui/images/settings_image.h>
//#include <gui/images/clock_image.h>

//#include <gui/images/base.h>
#include <gui/images/base_no_num.h>

#include <menu/icons/about.h>
#include <menu/icons/settings.h>
#include <menu/icons/diameter.h>
#include <menu/icons/clock.h>
#include <menu/icons/reset.h>
#include <menu/icons/date.h>
#include <menu/icons/history.h>

#include <menu/about.h>

#include <timer/history.h>

/*----------------------------------------------------------------------------*/

// Menu text
const String MT_MENU                    = {STRING("")};
const String MT_MENU_HISTORY            = {STRING("History")};
const String MT_MENU_SETTINGS           = {STRING("Settings")};
const String MT_MENU_SET_TIME           = {STRING("Set time")};
const String MT_MENU_SET_DATE           = {STRING("Set date")};
const String MT_MENU_SET_DIAMETER       = {STRING("Set diameter")};
const String MT_MENU_SET_GAUGE_SCALE    = {STRING("Set scale")};
const String MT_MENU_SET_SPEED_DISPLAY_MODE = {STRING("Set mode")};
const String MT_MENU_ABOUT		        = {STRING("About")};
const String MT_MENU_RESET		        = {STRING("Reset timers")};

/*----------------------------------------------------------------------------*/

const MenuNextState menu_nextstate[] = {
//  STATE                       INPUT       NEXT STATE
    {ST_MENU,                   KEY_ENTER,  ST_MENU_HISTORY},
    {ST_MENU,                   KEY_UP,  	ST_MENU},
    {ST_MENU,                   KEY_DOWN,  	ST_MENU},
    {ST_MENU,                   KEY_ESCAPE,	ST_SHUTDOWN_MENU},

    {ST_SHUTDOWN_MENU,          KEY_ENTER,  ST_SHUTDOWN_MENU},
    {ST_SHUTDOWN_MENU,          KEY_UP,  	ST_SHUTDOWN_MENU},
    {ST_SHUTDOWN_MENU,          KEY_DOWN,  	ST_SHUTDOWN_MENU},
    {ST_SHUTDOWN_MENU,          KEY_ESCAPE,	ST_SHUTDOWN_MENU},

    {ST_MENU_HISTORY,           KEY_UP,   	ST_MENU_RESET},	
    {ST_MENU_HISTORY,           KEY_DOWN,   ST_MENU_ABOUT},	
    {ST_MENU_HISTORY,           KEY_ENTER,  ST_MENU_HISTORY_FUNC},		
	{ST_MENU_HISTORY,           KEY_ESCAPE, ST_MENU},	
	
    {ST_MENU_HISTORY_FUNC,      KEY_UP,   	ST_MENU_HISTORY_FUNC},	
    {ST_MENU_HISTORY_FUNC,      KEY_DOWN,   ST_MENU_HISTORY_FUNC},	
    {ST_MENU_HISTORY_FUNC,      KEY_ENTER,  ST_MENU_HISTORY_FUNC},		
	{ST_MENU_HISTORY_FUNC,      KEY_ESCAPE, ST_MENU_HISTORY_FUNC},

    {ST_MENU_RESET,             KEY_UP,   	ST_MENU_SETTINGS},	
    {ST_MENU_RESET,             KEY_DOWN,   ST_MENU_HISTORY},	
    {ST_MENU_RESET,             KEY_ENTER,  ST_MENU_RESET_FUNC},		
	{ST_MENU_RESET,             KEY_ESCAPE, ST_MENU},	
	
    {ST_MENU_RESET_FUNC,        KEY_UP,   	ST_MENU_RESET_FUNC},	
    {ST_MENU_RESET_FUNC,        KEY_DOWN,   ST_MENU_RESET_FUNC},	
    {ST_MENU_RESET_FUNC,        KEY_ENTER,  ST_MENU_RESET_FUNC},		
	{ST_MENU_RESET_FUNC,        KEY_ESCAPE, ST_MENU_RESET_FUNC},	

	{ST_MENU_SETTINGS,          KEY_UP,   	ST_MENU_ABOUT},
    {ST_MENU_SETTINGS,          KEY_DOWN,   ST_MENU_RESET},		
    {ST_MENU_SETTINGS,          KEY_ESCAPE, ST_MENU},		
    {ST_MENU_SETTINGS,          KEY_ENTER, 	ST_MENU_SET_TIME},	
	
    {ST_MENU_SET_TIME,          KEY_UP,   	ST_MENU_SET_DATE},	
    {ST_MENU_SET_TIME,          KEY_DOWN,   ST_MENU_SET_SPEED_DISPLAY_MODE},	
    {ST_MENU_SET_TIME,          KEY_ENTER,  ST_MENU_SET_TIME_FUNC},		
	{ST_MENU_SET_TIME,          KEY_ESCAPE, ST_MENU_SETTINGS},		
	
    {ST_MENU_SET_TIME_FUNC, 	KEY_UP,   		ST_MENU_SET_TIME_FUNC},	
    {ST_MENU_SET_TIME_FUNC, 	KEY_DOWN,   	ST_MENU_SET_TIME_FUNC},	
    {ST_MENU_SET_TIME_FUNC, 	KEY_ENTER,  	ST_MENU_SET_TIME_FUNC},		
	{ST_MENU_SET_TIME_FUNC, 	KEY_ESCAPE, 	ST_MENU_SET_TIME_FUNC},	
	
    {ST_MENU_SET_DATE,          KEY_UP,   		ST_MENU_SET_DIAMETER},	
    {ST_MENU_SET_DATE,         	KEY_DOWN,   	ST_MENU_SET_TIME},	
    {ST_MENU_SET_DATE,          KEY_ENTER,  	ST_MENU_SET_DATE_FUNC},		
	{ST_MENU_SET_DATE,         	KEY_ESCAPE, 	ST_MENU_SETTINGS},		
	
    {ST_MENU_SET_DATE_FUNC, 	KEY_UP,   		ST_MENU_SET_DATE_FUNC},	
    {ST_MENU_SET_DATE_FUNC, 	KEY_DOWN,   	ST_MENU_SET_DATE_FUNC},	
    {ST_MENU_SET_DATE_FUNC, 	KEY_ENTER,  	ST_MENU_SET_DATE_FUNC},		
	{ST_MENU_SET_DATE_FUNC, 	KEY_ESCAPE, 	ST_MENU_SET_DATE_FUNC},		
	
    {ST_MENU_SET_DIAMETER,      KEY_UP,   	ST_MENU_SET_GAUGE_SCALE},	
    {ST_MENU_SET_DIAMETER,      KEY_DOWN,   ST_MENU_SET_DATE},	
    {ST_MENU_SET_DIAMETER,      KEY_ENTER,  ST_MENU_SET_DIAMETER_FUNC},		
	{ST_MENU_SET_DIAMETER,      KEY_ESCAPE, ST_MENU_SETTINGS},			

    {ST_MENU_SET_DIAMETER_FUNC, KEY_UP,   	ST_MENU_SET_DIAMETER_FUNC},	
    {ST_MENU_SET_DIAMETER_FUNC, KEY_DOWN,   ST_MENU_SET_DIAMETER_FUNC},	
    {ST_MENU_SET_DIAMETER_FUNC, KEY_ENTER,  ST_MENU_SET_DIAMETER_FUNC},		
	{ST_MENU_SET_DIAMETER_FUNC, KEY_ESCAPE, ST_MENU_SET_DIAMETER_FUNC},			
	/*****/
    {ST_MENU_SET_GAUGE_SCALE,      KEY_UP,     ST_MENU_SET_SPEED_DISPLAY_MODE},	
    {ST_MENU_SET_GAUGE_SCALE,      KEY_DOWN,   ST_MENU_SET_DIAMETER},	
    {ST_MENU_SET_GAUGE_SCALE,      KEY_ENTER,  ST_MENU_SET_GAUGE_SCALE_FUNC},		
	{ST_MENU_SET_GAUGE_SCALE,      KEY_ESCAPE, ST_MENU_SETTINGS},			

    {ST_MENU_SET_GAUGE_SCALE_FUNC, KEY_UP,     ST_MENU_SET_GAUGE_SCALE_FUNC},	
    {ST_MENU_SET_GAUGE_SCALE_FUNC, KEY_DOWN,   ST_MENU_SET_GAUGE_SCALE_FUNC},	
    {ST_MENU_SET_GAUGE_SCALE_FUNC, KEY_ENTER,  ST_MENU_SET_GAUGE_SCALE_FUNC},		
	{ST_MENU_SET_GAUGE_SCALE_FUNC, KEY_ESCAPE, ST_MENU_SET_GAUGE_SCALE_FUNC},		

    {ST_MENU_SET_SPEED_DISPLAY_MODE,      KEY_UP,     ST_MENU_SET_TIME},	
    {ST_MENU_SET_SPEED_DISPLAY_MODE,      KEY_DOWN,   ST_MENU_SET_GAUGE_SCALE},	
    {ST_MENU_SET_SPEED_DISPLAY_MODE,      KEY_ENTER,  ST_MENU_SET_SPEED_DISPLAY_MODE_FUNC},		
	{ST_MENU_SET_SPEED_DISPLAY_MODE,      KEY_ESCAPE, ST_MENU_SETTINGS},			

    {ST_MENU_SET_SPEED_DISPLAY_MODE_FUNC, KEY_UP,     ST_MENU_SET_DIAMETER_FUNC},	
    {ST_MENU_SET_SPEED_DISPLAY_MODE_FUNC, KEY_DOWN,   ST_MENU_SET_DIAMETER_FUNC},	
    {ST_MENU_SET_SPEED_DISPLAY_MODE_FUNC, KEY_ENTER,  ST_MENU_SET_DIAMETER_FUNC},		
	{ST_MENU_SET_SPEED_DISPLAY_MODE_FUNC, KEY_ESCAPE, ST_MENU_SET_DIAMETER_FUNC},		
	
	/**-*/

    {ST_MENU_ABOUT,             KEY_UP,   	ST_MENU_HISTORY},	
    {ST_MENU_ABOUT,             KEY_DOWN,   ST_MENU_SETTINGS},	
    {ST_MENU_ABOUT,             KEY_ENTER,  ST_MENU_ABOUT_FUNC},		
	{ST_MENU_ABOUT,             KEY_ESCAPE, ST_MENU},	

    {ST_MENU_ABOUT_FUNC,        KEY_UP,   	ST_MENU_ABOUT_FUNC},	
    {ST_MENU_ABOUT_FUNC,        KEY_DOWN,   ST_MENU_ABOUT_FUNC},	
    {ST_MENU_ABOUT_FUNC,        KEY_ENTER,  ST_MENU_ABOUT_FUNC},		
	{ST_MENU_ABOUT_FUNC,        KEY_ESCAPE, ST_MENU_ABOUT_FUNC},	

    {0,                         0,          0}
};

/*----------------------------------------------------------------------------*/

MenuNextState* get_menu_relations()
{
	return (MenuNextState*)menu_nextstate;
}

/*----------------------------------------------------------------------------*/

const MenuState menu_state[] = {
//  STATE                           STATE TEXT                  STATE_IMAGE  STATE_FUNC
    {ST_MENU,                       		&MT_MENU,                   base_no_num,	SpeedMeter_change_top_display},
    {ST_SHUTDOWN_MENU,                      NULL,	                    NULL,			System_shutdown_menu},	
	{ST_MENU_HISTORY,               		&MT_MENU_HISTORY,           history_image,	NULL},
	{ST_MENU_HISTORY_FUNC,          		NULL,					    history_image,	History_view},
    {ST_MENU_SETTINGS,              		&MT_MENU_SETTINGS,          settings,		NULL},
    {ST_MENU_SET_TIME,              		&MT_MENU_SET_TIME,          clock,			NULL},
    {ST_MENU_SET_TIME_FUNC,         		NULL,				        NULL,			Rtc_set_time},	
    {ST_MENU_SET_DATE,              		&MT_MENU_SET_DATE,          date_image,		NULL},
    {ST_MENU_SET_DATE_FUNC,         		NULL,				        NULL,			Rtc_set_date},		
    {ST_MENU_SET_DIAMETER,          		&MT_MENU_SET_DIAMETER,     	diameter,		NULL},
    {ST_MENU_SET_DIAMETER_FUNC,     		NULL,				      	NULL,			Settings_change_wheer_diameter},
    {ST_MENU_SET_GAUGE_SCALE,          		&MT_MENU_SET_GAUGE_SCALE,     	NULL,			NULL},
    {ST_MENU_SET_GAUGE_SCALE_FUNC,     		NULL,				      	NULL,			Settings_set_gauge_scale},
    {ST_MENU_SET_SPEED_DISPLAY_MODE,        &MT_MENU_SET_SPEED_DISPLAY_MODE,     	NULL,			NULL},
    {ST_MENU_SET_SPEED_DISPLAY_MODE_FUNC,   NULL,				      	NULL,			Settings_set_speed_display_mode},	
    {ST_MENU_ABOUT,    		       			&MT_MENU_ABOUT,          	about,			NULL},
    {ST_MENU_ABOUT_FUNC,    	   			NULL,				        NULL,			About_draw},	
    {ST_MENU_RESET,             			&MT_MENU_RESET,		        reset_image,	NULL},
    {ST_MENU_RESET_FUNC,         			NULL,				        NULL,			Settings_reset},		
	
    {0,                             		NULL,                      				NULL},
    
};

/*----------------------------------------------------------------------------*/

MenuState* get_menu_state()
{
	return (MenuState*)menu_state;
}

/*----------------------------------------------------------------------------*/
