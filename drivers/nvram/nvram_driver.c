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

uint8_t nvram_read_u8(uint32_t addr) {
    uint8_t ret = 0;
    nvram_read_block(addr, &ret, 1);
    return ret;
}

uint16_t nvram_read_u16(uint32_t addr) {
    uint16_t ret = 0;
    nvram_read_block(addr, &ret, 2);
    return ret;
}

uint32_t nvram_read_u32(uint32_t addr) {
    uint32_t ret = 0;
    nvram_read_block(addr, &ret, 4);
    return ret;
}

void nvram_write_u8(uint32_t addr, uint8_t value) { nvram_write_block(addr, &value, 1); }

void nvram_write_u16(uint32_t addr, uint16_t value) { nvram_write_block(addr, &value, 2); }

void nvram_write_u32(uint32_t addr, uint32_t value) { nvram_write_block(addr, &value, 4); }

void nvram_update_block(uint32_t addr, const void *buf, size_t len) {
    uint8_t read_buf[len];
    nvram_read_block(addr, read_buf, len);
    if (memcmp(buf, read_buf, len) != 0) {
        nvram_write_block(addr, buf, len);
    }
}

void nvram_update_u8(uint32_t addr, uint8_t value) {
    uint8_t orig = nvram_read_u8(addr);
    if (orig != value) {
        nvram_write_u8(addr, value);
    }
}

void nvram_update_u16(uint32_t addr, uint16_t value) {
    uint16_t orig = nvram_read_u16(addr);
    if (orig != value) {
        nvram_write_u16(addr, value);
    }
}

void nvram_update_u32(uint32_t addr, uint32_t value) {
    uint32_t orig = nvram_read_u32(addr);
    if (orig != value) {
        nvram_write_u32(addr, value);
    }
}
