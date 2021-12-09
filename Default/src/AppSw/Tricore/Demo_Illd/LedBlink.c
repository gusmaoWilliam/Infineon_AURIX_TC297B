/*
 * LedBlink.c
 *
 *  Created on: 23 de out de 2021
 *      Author: willi
 */


#include "externas.h"
#include "IfxPort.h"
#include "../tft/tfthw.h"
#include "../tft/touch.h"
#include "../src/BaseSw/Qspi/Qspi0.h"
#include "../src/BaseSw/GPT12_Timer_Interrupt.h"
#include "../lvgl/lvgl.h"
#include "../lvgl/lv_init.h"
#include "../lv_examples/lv_examples.h"
#include "imagem.h"
#include "image2.h"


unsigned long tempo = 0;
void BlinkLed(unsigned int tempo_blink)
{
	if((touchTimeUp-tempo) >= (tempo_blink/10))
	{
		tempo = touchTimeUp;
		IfxPort_togglePin(LED_D107);
	}/*
    if ((touch_driver.touchmode & MASK_TOUCH_DOWN) != 0 || (touch_driver.touchmode & MASK_TOUCH_MOVE) != 0)
    {

        touch_driver.touchmode &= ~MASK_TOUCH_DOWN;   //clear
        touch_driver.touchmode &= ~MASK_TOUCH_MOVE;   //clear
        tft_display_setxy(touch_driver.xdisp,touch_driver.ydisp,touch_driver.xdisp,touch_driver.ydisp);
        uint16 buff[4]={0xf100,0xf100,0xf100,0xf100};
        tft_flush_row_buff(4, &buff[0]);

    }*/
}
void InitLed()
{
    lv_configure();
    initGpt12Timer();
    lv_obj_t *teste;
	LV_IMG_DECLARE(image2);
	lv_img_set_src(teste,&image2);
	/* Initialization of the LED used in this example */
	IfxPort_setPinModeOutput(LED_D107, IfxPort_OutputMode_pushPull, IfxPort_OutputIdx_general);

	/* Switch OFF the LED (low-level active) */
	IfxPort_setPinHigh(LED_D107);
}
