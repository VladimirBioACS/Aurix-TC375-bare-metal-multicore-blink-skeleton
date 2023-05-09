/**
 * \file IfxSent.c
 * \brief SENT  basic functionality
 *
 * \version iLLD_1_0_1_15_0_1
 * \copyright Copyright (c) 2019 Infineon Technologies AG. All rights reserved.
 *
 *
 *
 *                                 IMPORTANT NOTICE
 *
 * Use of this file is subject to the terms of use agreed between (i) you or
 * the company in which ordinary course of business you are acting and (ii)
 * Infineon Technologies AG or its licensees. If and as long as no such terms
 * of use are agreed, use of this file is subject to following:
 *
 * Boost Software License - Version 1.0 - August 17th, 2003
 *
 * Permission is hereby granted, free of charge, to any person or organization
 * obtaining a copy of the software and accompanying documentation covered by
 * this license (the "Software") to use, reproduce, display, distribute,
 * execute, and transmit the Software, and to prepare derivative works of the
 * Software, and to permit third-parties to whom the Software is furnished to
 * do so, all subject to the following:
 *
 * The copyright notices in the Software and this entire statement, including
 * the above license grant, this restriction and the following disclaimer, must
 * be included in all copies of the Software, in whole or in part, and all
 * derivative works of the Software, unless such copies or derivative works are
 * solely in the form of machine-executable object code generated by a source
 * language processor.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE, TITLE AND NON-INFRINGEMENT. IN NO EVENT
 * SHALL THE COPYRIGHT HOLDERS OR ANYONE DISTRIBUTING THE SOFTWARE BE LIABLE
 * FOR ANY DAMAGES OR OTHER LIABILITY, WHETHER IN CONTRACT, TORT OR OTHERWISE,
 * ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 * DEALINGS IN THE SOFTWARE.
 *
 *
 *
 */

/******************************************************************************/
/*----------------------------------Includes----------------------------------*/
/******************************************************************************/

#include "IfxSent.h"

/******************************************************************************/
/*-------------------------Function Implementations---------------------------*/
/******************************************************************************/

float32 IfxSent_getChannelUnitTime(Ifx_SENT *sent, IfxSent_ChannelId channelId)
{
    float32 fFracDiv = IfxSent_getModuleClock(sent);
    float32 fPdiv    = fFracDiv / (float32)(sent->CH[channelId].CPDR.B.PDIV + 1);

    uint32  div      = sent->CH[channelId].CFDR.B.DIV;

    if (div > 0)
    {
        float32 fTick = (fPdiv * 56) / div;
        return 1 / fTick;
    }
    else
    {
        return 0.0;
    }
}


float32 IfxSent_getModuleClock(Ifx_SENT *sent)
{
    float32      fsys = IfxScuCcu_getSpbFrequency();

    Ifx_SENT_FDR fdr;
    fdr.U = sent->FDR.U;

    float32      kernelFreq = 0.0;

    if (fdr.B.DM == 1)
    {
        kernelFreq = fsys / (1024 - fdr.B.STEP);
    }
    else if (fdr.B.DM == 2)
    {
        kernelFreq = (fsys * fdr.B.STEP) / 1024;
    }

    return kernelFreq;
}


void IfxSent_initializeChannelUnitTime(Ifx_SENT *sent, IfxSent_ChannelId channelId, float32 tUnit)
{
    float32      fFracDiv = IfxSent_getModuleClock(sent);

    /* const uint32 divMin   = 560; */
    const uint32 divMax = 3276;

    uint32       pDiv;
    uint32       fDiv;

    float32      tResult;
    tResult = fFracDiv * 56 * tUnit;
    pDiv    = tResult / divMax;
    fDiv    = tResult / pDiv;

    if (fDiv > divMax)
    {
        pDiv = pDiv + 1;
        fDiv = tResult / pDiv;
    }

    if ((pDiv > 1024) || (pDiv < 1))
    {
        pDiv = 1025;
        fDiv = tResult / 1024;
    }

    IfxSent_setChannelPreDivider(sent, channelId, (uint16)pDiv - 1);
    IfxSent_setChannelFractionalDivider(sent, channelId, (uint16)fDiv);
}


void IfxSent_initializeModuleClock(Ifx_SENT *sent, IfxSent_ClockDividerMode dividerMode, uint16 stepValue)
{
    Ifx_SENT_FDR tempFDR;
    tempFDR.U      = 0;
    tempFDR.B.STEP = stepValue;
    tempFDR.B.DM   = dividerMode;
    sent->FDR.U    = tempFDR.U;
}


void IfxSent_resetModule(Ifx_SENT *sent)
{
    uint16 passwd = IfxScuWdt_getCpuWatchdogPassword();

    IfxScuWdt_clearCpuEndinit(passwd);
    sent->KRST1.B.RST = 1;      /* Only if both Kernel reset bits are set a reset is executed */
    sent->KRST0.B.RST = 1;
    IfxScuWdt_setCpuEndinit(passwd);

    while (0 == sent->KRST0.B.RSTSTAT)  /* Wait until reset is executed */

    {}

    IfxScuWdt_clearCpuEndinit(passwd);
    sent->KRSTCLR.B.CLR = 1;    /* Clear Kernel reset status bit */
    IfxScuWdt_setCpuEndinit(passwd);
}
