/* Copyright 2019 Nick Brassel (tzarc)
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <stdint.h>
#include <string.h>

#include "nvram_driver.h"
#include "nvram_transient.h"

__attribute__((aligned(4))) static uint8_t transientBuffer[TRANSIENT_EEPROM_SIZE] = {0};

size_t clamp_length(intptr_t offset, size_t len) {
    if (offset + len > TRANSIENT_EEPROM_SIZE) {
        len = TRANSIENT_EEPROM_SIZE - offset;
    }

    return len;
}

void nvram_driver_init(void) { nvram_driver_erase(); }

void nvram_driver_erase(void) { memset(transientBuffer, 0x00, TRANSIENT_EEPROM_SIZE); }

void nvram_read_block(uint32_t addr, void *buf, size_t len) {
    intptr_t offset = (intptr_t)addr;
    memset(buf, 0x00, len);
    len = clamp_length(offset, len);
    if (len > 0) {
        memcpy(buf, &transientBuffer[offset], len);
    }
}

void nvram_write_block(uint32_t addr, const void *buf, size_t len) {
    intptr_t offset = (intptr_t)addr;
    len             = clamp_length(offset, len);
    if (len > 0) {
        memcpy(&transientBuffer[offset], buf, len);
    }
}
