/**
**********************************************************************************************************************
*    @file           : CPU_performance.c
*    @brief          : CPU performance checker setup body
*    @copyright Copyright (C) Infineon Technologies AG 2019
**********************************************************************************************************************
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
*
**********************************************************************************************************************
*/

/*********************************************************************************************************************/
/*-----------------------------------------------------Includes------------------------------------------------------*/
/*********************************************************************************************************************/
#include "IfxCbs_reg.h"
#include "IfxCpu.h"

/*********************************************************************************************************************/
/*------------------------------------------------------Macros-------------------------------------------------------*/
/*********************************************************************************************************************/
#define MAX_LOOP_CNT    190                     /* Maximum loop value for test code                                 */

/*********************************************************************************************************************/
/*-------------------------------------------------Global variables--------------------------------------------------*/
/*********************************************************************************************************************/
IfxCpu_Perf g_perfCounts;                       /* Need to be global to display in the Watch View of the debugger   */

/*********************************************************************************************************************/
/*-------------------------------------------------Function Prototypes-----------------------------------------------*/
/*********************************************************************************************************************/
static void loop(void);

/*********************************************************************************************************************/
/*----------------------------------------------Function Implementations---------------------------------------------*/
/*********************************************************************************************************************/

/**
* @brief Loop function to be measured
* @param argument: Not used
* @retval None
*/
static void loop(void)
{
    volatile uint16 i;                  /* This data type is stored in RAM and cannot be optimized by the compiler  */

    for(i = 0; i < MAX_LOOP_CNT; i++)
    {
        __nop();
    }
}

/**
* @brief Function to run the CPU performance counters
* @param argument: Not used
* @retval None
*/
void runCpuPerfCounters(void)
{
    IfxCpu_resetAndStartCounters(IfxCpu_CounterMode_normal);            /* Reset and start counters in normal mode  */
    loop();                                                             /* Test loop to measure CPU performance     */

    g_perfCounts = IfxCpu_stopCounters();                               /* Stop counters and get results            */
}
