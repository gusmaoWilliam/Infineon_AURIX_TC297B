/**
 * \file Ifx_Cfg.h
 * \brief Configuration.
 *
 * \version iLLD_Demos_1_0_1_8_0
 * \copyright Copyright (c) 2014 Infineon Technologies AG. All rights reserved.
 *
 *
 *                                 IMPORTANT NOTICE
 *
 *
 * Infineon Technologies AG (Infineon) is supplying this file for use
 * exclusively with Infineon's microcontroller products. This file can be freely
 * distributed within development tools that are supporting such microcontroller
 * products.
 *
 * THIS SOFTWARE IS PROVIDED "AS IS".  NO WARRANTIES, WHETHER EXPRESS, IMPLIED
 * OR STATUTORY, INCLUDING, BUT NOT LIMITED TO, IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE APPLY TO THIS SOFTWARE.
 * INFINEON SHALL NOT, IN ANY CIRCUMSTANCES, BE LIABLE FOR SPECIAL, INCIDENTAL,
 * OR CONSEQUENTIAL DAMAGES, FOR ANY REASON WHATSOEVER.
 *
 *
 * \defgroup IfxLld_Demo_ScuClockDemo_SrcDoc_IlldConfig iLLD configuration
 * \ingroup IfxLld_Demo_ScuClockDemo_SrcDoc
 */

#ifndef IFX_CFG_H
#define IFX_CFG_H 1

/******************************************************************************/
/*-----------------------------------Macros-----------------------------------*/
/******************************************************************************/

/** \addtogroup IfxLld_Demo_ScuClockDemo_SrcDoc_IlldConfig
 * \{ */

/*______________________________________________________________________________
** Configuration for IfxScu_cfg.h
**____________________________________________________________________________*/
/**
 * \name Frequency configuration
 * \{
/* External oscillator frequency in Hz */
#define IFX_CFG_SCU_XTAL_FREQUENCY      (20000000)  /* Allowed values are: 16000000, 20000000 or 40000000 */
/* PLL frequency in Hz */
#define IFX_CFG_SCU_PLL_FREQUENCY       (300000000) /* Allowed values are: 80000000, 133000000, 160000000, 200000000, 
                                                     * 240000000 or 300000000 */


/** \} */

#endif /* IFX_CFG_H */
