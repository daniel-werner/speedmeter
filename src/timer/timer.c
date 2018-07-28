/*******************************************************************************

     
    ========================================
   

    Daniel Verner
    vernerd@gmail.com
  *****************************************************************************/

/*----------------------------------------------------------------------------*/

#include <timer/timer.h>

/*----------------------------------------------------------------------------*/

i16_t pwm_period;

bool_t timerARunning = FALSE;

/*----------------------------------------------------------------------------*/

bool_t start_timerA(f32_t time)
{
	TA_init(time, NULL);
	timerARunning = TRUE;
 	return TRUE; 
}

/*----------------------------------------------------------------------------*/

bool_t is_running_timerA()
{
	return timerARunning;
}

/*----------------------------------------------------------------------------*/

bool_t delay(f32_t time)
{
timerARunning = TRUE;
 TA_init(time, NULL);
// while(!(TACTL&TAIFG));
 while(timerARunning);
 TACTL &= ~TAIFG;
 TACTL &= ~MC_1;
 return TRUE; 
}

/*----------------------------------------------------------------------------*/

bool_t TA_init(f32_t time,i16_t freq)
{

  TACCR0 = timera_calc(time, freq);          // TimerA ertek - 3E8=1ms, 2710=10ms
//  TACTL = TASSEL1;                        // TASSEL = 0x0200 ez azt jelenti, hogy a TimerA clock forrasa SMCLK
  TACTL = TASSEL1 +  MC_1;		    // TimerA folyamatos mod
  TACCTL0 |= CCIE;		            // CCTL0 ugyanaz, mint TACCTL0
  return TRUE;
}

/*----------------------------------------------------------------------------*/

bool_t pwm_init(i16_t freq,f32_t pwm1_rate,f32_t pwm2_rate)
{
  pwm_period =  timerb_calc(NULL, freq); 
  TBCCR0 = pwm_period-1;                            // PWM Period
  TBCCTL1 = OUTMOD_7;                               // CCR1 reset/set
  TBCCR1 = (i16_t)(pwm_period*pwm1_rate);           // CCR1 PWM duty cycle
  TBCCTL6 = OUTMOD_7;
  TBCCR6 = (i16_t)(pwm_period*pwm2_rate);
  TBCTL = TBSSEL_1 + MC_1;                          // ACLK, up mode
  return TRUE;
}

/*----------------------------------------------------------------------------*/

i16_t timera_calc(f32_t time,i16_t freq)
{
  if (time) return ((i16_t)(TIMERA_CLK*time));
  else if (freq) return (i16_t)((TIMERA_CLK/freq)*1000);
       else return DEFAULT_TIMERA_VALUE;
}

/*----------------------------------------------------------------------------*/

i16_t timerb_calc(i16_t time,i16_t freq)
{
  if (time) return ((TIMERB_CLK*time));
  else if (freq) return (i16_t)((TIMERB_CLK/(freq/10)));
       else return DEFAULT_TIMERB_VALUE;
}

/*----------------------------------------------------------------------------*/

// Timer interrupt service routine
//#pragma vector=TIMERA0_VECTOR
//__interrupt void Timer_A (void)
//{
//	timerARunning = FALSE;
//	TACTL &= ~MC_1;	
//	return;
//}

//#pragma vector=TIMERB0_VECTOR
//__interrupt void Timer_B0 (void) 
//{
//return;
//}
//#pragma vector=TIMERB1_VECTOR
//__interrupt void Timer_B1 (void) 
//{
//return;
//}

