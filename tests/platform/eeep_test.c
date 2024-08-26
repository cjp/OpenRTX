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
#include <string.h>
#include <interfaces/platform.h>
#include <interfaces/delays.h>
#include <posix_file.h>
#include <nvmem_access.h>
#include <eeep.h>

uint8_t data[32];


int main()
{
    platform_init();

    // for(uint8_t i = 0; i < )
    memset(data, 0x55, sizeof(data));
    data[31] = 1;
    nvm_write(1, -1, 0x00, data, sizeof(data));

    memset(data, 0xaa, sizeof(data));
    data[31] = 2;
    nvm_write(1, -1, 0x01, data, sizeof(data));

    memset(data, 0x55, sizeof(data));
    data[31] = 3;
    nvm_write(1, -1, 0x00, data, sizeof(data));

    memset(data, 0xaa, sizeof(data));
    data[31] = 4;
    nvm_write(1, -1, 0x01, data, sizeof(data));

    memset(data, 0x55, sizeof(data));
    data[31] = 5;
    nvm_write(1, -1, 0x00, data, sizeof(data));

    memset(data, 0xbb, sizeof(data));
    nvm_write(1, -1, 0x01, data, sizeof(data));

    memset(data, 0x00, sizeof(data));
    nvm_read(1, -1, 0x00, data, sizeof(data));
    printf("%02x %02x\n", data[0], data[31]);


    return 0;
}
