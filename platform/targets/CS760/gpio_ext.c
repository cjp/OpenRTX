/***************************************************************************
 *   Copyright (C) 2024 by Silvano Seva IU2KWO                             *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 3 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, see <http://www.gnu.org/licenses/>   *
 ***************************************************************************/

#include <interfaces/delays.h>
#include <peripherals/gpio.h>
#include <pinmap.h>
#include <stdio.h>
#include "gpio_ext.h"


uint32_t externalGpios;

void gpioExt_init()
{
    externalGpios = 0;

    gpio_setMode(GPIOEXT_CLK, OUTPUT);
    gpio_setMode(GPIOEXT_DAT, OUTPUT);
    gpio_setMode(GPIOEXT_STR, OUTPUT);
    gpio_setOutputSpeed(GPIOEXT_CLK, HIGH);
    gpio_setOutputSpeed(GPIOEXT_DAT, HIGH);
    gpio_setOutputSpeed(GPIOEXT_STR, HIGH);

    gpio_clearPin(GPIOEXT_CLK);
    gpio_clearPin(GPIOEXT_DAT);
    gpio_clearPin(GPIOEXT_STR);

    gpioExt_update();
}

void gpioExt_terminate()
{
    gpio_setMode(GPIOEXT_CLK, INPUT);
    gpio_setMode(GPIOEXT_DAT, INPUT);
    gpio_setMode(GPIOEXT_STR, INPUT);
}

void gpioExt_update()
{
    __disable_irq();

    gpio_clearPin(GPIOEXT_STR);

    uint32_t tmp = externalGpios;
    for(uint8_t i = 0; i < 24; i++)
    {
        gpio_clearPin(GPIOEXT_CLK);

        if((tmp & 0x800000) != 0)
            gpio_setPin(GPIOEXT_DAT);
        else
            gpio_clearPin(GPIOEXT_DAT);

        tmp <<= 1;
        gpio_setPin(GPIOEXT_CLK);
    }

    gpio_setPin(GPIOEXT_STR);

    __enable_irq();
}

#ifdef __cplusplus
}
#endif
