/**
**********************************************************************************************************************
*    @file           : led_blink.c
*    @brief          : led blink program body
**********************************************************************************************************************
*    @author     Volodymyr Noha
*    @license    MIT (see License.txt)
*
*    @description:
*    This is a simple firmware for the Aurix TC375 to work with on-board LED`s
*
*    @section  HISTORY
*    v1.0  - First version
*
**********************************************************************************************************************
*/

/*********************************************************************************************************************/
/*-----------------------------------------------------Includes------------------------------------------------------*/
/*********************************************************************************************************************/
#include "IfxPort.h"
#include "Bsp.h"
#include "led_blink.h"

/*********************************************************************************************************************/
/*------------------------------------------------------Macros-------------------------------------------------------*/
/*********************************************************************************************************************/
#define WAIT_MS_CPU0                (Ifx_TickTime)(500)              /* 500 ms delay                                 */
#define WAIT_MS_CPU1                (Ifx_TickTime)(1000)             /* 1000 ms delay                                */
#define WAIT_MS_CPU2                (Ifx_TickTime)(1500)             /* 1500 ms delay                                */

#define GREEN_LED_CPU0              &MODULE_P00,5                    /* LED: Port, Pin definition  (green LED CPU0)  */
#define GREEN_LED_CPU1              &MODULE_P00,6                    /* LED: Port, Pin definition  (green LED CPU1)  */
#define GREEN_LED_CPU2              &MODULE_P02,4                    /* LED: Port, Pin definition  (green LED CPU1)  */

/*********************************************************************************************************************/
/*---------------------------------------------Function Implementations----------------------------------------------*/
/*********************************************************************************************************************/

/**
* @brief Function implementing the initialization for the LED GPIO ports.
* @param argument: Not used
* @retval None
*/
void gpioPreInit(void)
{

    IfxPort_setPinModeOutput(GREEN_LED_CPU0,                    /* Init Signal GREEN_LED_CPU0 port                  */
            IfxPort_OutputMode_pushPull,
            IfxPort_OutputIdx_general);


    IfxPort_setPinModeOutput(GREEN_LED_CPU1,                    /* Init Signal GREEN_LED_CPU1 port                  */
            IfxPort_OutputMode_pushPull,
            IfxPort_OutputIdx_general);


    IfxPort_setPinModeOutput(GREEN_LED_CPU2,                    /* Init Signal GREEN_LED_CPU1 port                  */
            IfxPort_OutputMode_pushPull,
            IfxPort_OutputIdx_general);


    IfxPort_setPinHigh(GREEN_LED_CPU0);                         /* Switch OFF the GREEN_LED_CPU0 (low-level active) */
    IfxPort_setPinHigh(GREEN_LED_CPU1);                         /* Switch OFF the GREEN_LED_CPU1 (low-level active) */
    IfxPort_setPinHigh(GREEN_LED_CPU2);                         /* Switch OFF the GREEN_LED_CPU1 (low-level active) */
}

/**
* @brief Function implementing the led blinking on CPU0.
* @param argument: Not used
* @retval None
*/
void blinkCpu0(void)
{
    IfxPort_togglePin(GREEN_LED_CPU0);
    waitTime(IfxStm_getTicksFromMilliseconds(BSP_DEFAULT_TIMER, WAIT_MS_CPU0));
}

/**
* @brief Function implementing the led blinking on CPU1.
* @param argument: Not used
* @retval None
*/
void blinkCpu1(void)
{
    IfxPort_togglePin(GREEN_LED_CPU1);
    waitTime(IfxStm_getTicksFromMilliseconds(BSP_DEFAULT_TIMER, WAIT_MS_CPU1));
}

/**
* @brief Function implementing the led blinking on CPU2.
* @param argument: Not used
* @retval None
*/
void blinkCpu2(void)
{
    IfxPort_togglePin(GREEN_LED_CPU2);
    waitTime(IfxStm_getTicksFromMilliseconds(BSP_DEFAULT_TIMER, WAIT_MS_CPU2));

}
