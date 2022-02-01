/**********************************************************************************************************************
 * \file Cpu0_Main.c
 * \copyright Copyright (C) Infineon Technologies AG 2019
 *
 * Use of this file is subject to the terms of use agreed between (i) you or the company in which ordinary course of
 * business you are acting and (ii) Infineon Technologies AG or its licensees. If and as long as no such terms of use
 * are agreed, use of this file is subject to following:
 *
 * Boost Software License - Version 1.0 - August 17th, 2003
 *
 * Permission is hereby granted, free of charge, to any person or organization obtaining a copy of the software and
 * accompanying documentation covered by this license (the "Software") to use, reproduce, display, distribute, execute,
 * and transmit the Software, and to prepare derivative works of the Software, and to permit third-parties to whom the
 * Software is furnished to do so, all subject to the following:
 *
 * The copyright notices in the Software and this entire statement, including the above license grant, this restriction
 * and the following disclaimer, must be included in all copies of the Software, in whole or in part, and all
 * derivative works of the Software, unless such copies or derivative works are solely in the form of
 * machine-executable object code generated by a source language processor.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
 * WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE, TITLE AND NON-INFRINGEMENT. IN NO EVENT SHALL THE
 * COPYRIGHT HOLDERS OR ANYONE DISTRIBUTING THE SOFTWARE BE LIABLE FOR ANY DAMAGES OR OTHER LIABILITY, WHETHER IN
 * CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
 * IN THE SOFTWARE.
 *********************************************************************************************************************/
 /*\title Blinky LED
 * \abstract An LED is blinking based on the timing given by a wait function.
 * \description A wait function is used to add delays between switching on and switching off an LED on port pin P13.0.
 * \name Blinky_LED_1_KIT_TC297_TFT
 * \version V1.0.1
 * \board APPLICATION KIT TC2X7 V1.1, KIT_AURIX_TC297_TFT_BC-Step, TC29xTA/TX_B-Step
 * \keywords LED, blinky, GPIO, General Port Input Output, AURIX, Blinky_LED_1
 * \documents https://www.infineon.com/aurix-expert-training/Infineon-AURIX_Blinky_LED_1_KIT_TC297_TFT-TR-v01_00_01-EN.pdf
 * \documents https://www.infineon.com/aurix-expert-training/TC29B_iLLD_UM_1_0_1_12_0.chm
 * \lastUpdated 2020-12-18
 *********************************************************************************************************************/
#include "Ifx_Types.h"
#include "IfxCpu.h"
#include "IfxScuWdt.h"
#include "Blinky_LED.h"
#include "tfthw.h"
#include "touch.h"
#include "Bsp.h"
#include "GPT12_Timer_Interrupt.h"
#include "../lvgl/lvgl.h"
#include "../lvgl/lv_init.h"

IfxCpu_syncEvent g_cpuSyncEvent = 0;
#define BG_LED    &MODULE_P20,13
#define BUTTON &MODULE_P14,4    /* Port pin for the button  */
uint16 buf[320];
uint16 buf2[320];

uint16 bufer[320][240];



int core0_main(void)
{
    IfxCpu_enableInterrupts();

    /* !!WATCHDOG0 AND SAFETY WATCHDOG ARE DISABLED HERE!!
     * Enable the watchdogs and service them periodically if it is required
     */
    IfxScuWdt_disableCpuWatchdog(IfxScuWdt_getCpuWatchdogPassword());
    IfxScuWdt_disableSafetyWatchdog(IfxScuWdt_getSafetyWatchdogPassword());

    /* Wait for CPU sync event */
    IfxCpu_emitEvent(&g_cpuSyncEvent);
    IfxCpu_waitEvent(&g_cpuSyncEvent, 1);

    IfxPort_setPinModeOutput(BG_LED, IfxPort_OutputMode_pushPull, IfxPort_OutputIdx_general);
    IfxPort_setPinMode(BUTTON, IfxPort_Mode_inputPullUp);
    IfxPort_setPinHigh(BG_LED);
    waitTime(IfxStm_getTicksFromMilliseconds(BSP_DEFAULT_TIMER, 100));
    initLED();  /* Initialize the LED port pin      */

    tft_init();
    waitTime(IfxStm_getTicksFromMilliseconds(BSP_DEFAULT_TIMER, 100));
    touch_init();
    waitTime(IfxStm_getTicksFromMilliseconds(BSP_DEFAULT_TIMER, 100));

    
    for(uint32 i = 0; i < (320); i++)
    {
    	if(i < 320/2)
    		buf[i] = 0x07E0;
    	else
    		buf[i] = 0x07E0;
    }
    for(uint32 i = 0; i < (320); i++)
	{
		if(i < 320/2)
			buf2[i] = 0x07E0;
		else
			buf2[i] = 0x07E0;
	}
    for(uint16 j = 0; j < 240; j++)
    {
		tft_display_setxy(0, j, 320, 240);
		if(j < 240/2)
			tft_flush_row_buff(320, buf);
		else
			tft_flush_row_buff(320, buf2);
    }



    for(uint16 i = 0; i < 320; i++)
    {
    	for(uint16 j = 0; j < 240; j++)
    	{
    		bufer[i][j] = 0x780F;
    	}
    }
    tft_display_setxy(105, 80, 215, 130);
    tft_flush_row_buff((51*111), &bufer[0][0]);

    while(1)
    {
    	touch_periodic();
        blinkLED(); /* Make the LED blink           */

        if ((touch_driver.touchmode & MASK_TOUCH_DOWN) != 0 || (touch_driver.touchmode & MASK_TOUCH_MOVE) != 0)
		{
            IfxPort_setPinHigh(&MODULE_P13,0);
			touch_driver.touchmode &= ~MASK_TOUCH_DOWN;   //clear
			touch_driver.touchmode &= ~MASK_TOUCH_MOVE;   //clear
			tft_display_setxy(touch_driver.xdisp-5,touch_driver.ydisp-5,touch_driver.xdisp+5,touch_driver.ydisp+5);
			uint16 buff[100];
			for(uint8 i = 0; i < 100; i++)
			{
				buff[i] = 0x0000;
			}
			tft_flush_row_buff(100, &buff[0]);
            //waitTime(IfxStm_getTicksFromMilliseconds(BSP_DEFAULT_TIMER, 1000));
            
		}
    }
    return (1);
}
