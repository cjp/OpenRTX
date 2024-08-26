/***************************************************************************
 *   Copyright (C) 2020 - 2023 by Federico Amedeo Izzo IU2NUO,             *
 *                                Niccolò Izzo IU2KIN                      *
 *                                Frederik Saraci IU2NRO                   *
 *                                Silvano Seva IU2KWO                      *
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

#include <stdio.h>
#include <interfaces/platform.h>
#include <interfaces/audio.h>
#include <interfaces/delays.h>
#include <peripherals/gpio.h>
#include <M17/M17Modulator.hpp>
#include <M17/M17Prbs.hpp>
#include "USART3.h"

static void fill(M17::frame_t& frame, M17::PRBS9& prbs)
{
    for(size_t i = 0; i < frame.size(); i++)
    {
        uint8_t byte = 0;
        for(size_t j = 0; j < 8; j++)
            byte |= prbs.generateBit() << j;

        frame[i] = byte;
    }
}

int main()
{
    // platform_init();
    // usart3_init(115200);
    audio_init();

    M17::PRBS9 prbs;

    M17::frame_t frame;
    // frame.fill(0x77);
    fill(frame, prbs);

    M17::M17Modulator mod;
    mod.init();
    mod.start();
    // mod.sendPreamble();
    mod.sendFrame(frame);

    while(1)
    {
        fill(frame, prbs);
        mod.sendFrame(frame);
    }

    return 0;
}
