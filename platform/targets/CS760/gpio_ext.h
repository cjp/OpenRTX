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

#ifndef GPIO_EXT_H
#define GPIO_EXT_H

#include <stm32f4xx.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Initialize the GPIO extender interface.
 */
void gpioExt_init();

/**
 * Shut down the GPIO extender interface. Shift register outputs keep the last
 * assigned state.
 */
void gpioExt_terminate();

/**
 * Update the outputs of the GPIO extender shift register.
 */
void gpioExt_update();

/**
 * Set one or more GPIO extender outputs to logic high level.
 *
 * @param mask: GPIO bitmask.
 */
static inline void gpioExt_set(const uint32_t mask)
{
    extern uint32_t externalGpios;

    __disable_irq();
    externalGpios |= mask;
    __enable_irq();
}

/**
 * Set one or more GPIO extender outputs to logic high level and update the
 * shift register outputs.
 *
 * @param mask: GPIO bitmask.
 */
static inline void gpioExt_setUpdate(const uint32_t mask)
{
    gpioExt_set(mask);
    gpioExt_update();
}

/**
 * Set one or more GPIO extender outputs to logic low level.
 *
 * @param mask: GPIO bitmask.
 */
static inline void gpioExt_clear(const uint32_t mask)
{
    extern uint32_t externalGpios;

    __disable_irq();
    externalGpios &= ~mask;
    __enable_irq();
}

/**
 * Set one or more GPIO extender outputs to logic low level and update the
 * shift register outputs.
 *
 * @param mask: GPIO bitmask.
 */
static inline void gpioExt_clearUpdate(const uint32_t mask)
{
    gpioExt_clear(mask);
    gpioExt_update();
}

#ifdef __cplusplus
}
#endif

#endif /* GPIO_EXT_H */
