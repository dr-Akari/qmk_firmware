/* Copyright 2017 Fred Sundvik
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

#include "eeprom.h"

static uint8_t buffer[TOTAL_EEPROM_BYTE_COUNT];

uint8_t nvram_read_u8(uint32_t addr) {
    uintptr_t offset = (uintptr_t)addr;
    return buffer[offset];
}

void nvram_write_u8(uint32_t addr, uint8_t value) {
    uintptr_t offset = (uintptr_t)addr;
    buffer[offset]   = value;
}

uint16_t nvram_read_u16(uint32_t addr) {
    const uint8_t *p = (const uint8_t *)addr;
    return nvram_read_u8(p) | (nvram_read_u8(p + 1) << 8);
}

uint32_t nvram_read_u32(uint32_t addr) {
    const uint8_t *p = (const uint8_t *)addr;
    return nvram_read_u8(p) | (nvram_read_u8(p + 1) << 8) | (nvram_read_u8(p + 2) << 16) | (nvram_read_u8(p + 3) << 24);
}

void nvram_read_block(uint32_t addr, void *buf, size_t len) {
    const uint8_t *p    = (const uint8_t *)addr;
    uint8_t *      dest = (uint8_t *)buf;
    while (len--) {
        *dest++ = nvram_read_u8(p++);
    }
}

void nvram_write_u16(uint32_t addr, uint16_t value) {
    uint8_t *p = (uint8_t *)addr;
    nvram_write_u8(p++, value);
    nvram_write_u8(p, value >> 8);
}

void nvram_write_u32(uint32_t addr, uint32_t value) {
    uint8_t *p = (uint8_t *)addr;
    nvram_write_u8(p++, value);
    nvram_write_u8(p++, value >> 8);
    nvram_write_u8(p++, value >> 16);
    nvram_write_u8(p, value >> 24);
}

void nvram_write_block(uint32_t addr, const void *buf, size_t len) {
    uint8_t *      p   = (uint8_t *)addr;
    const uint8_t *src = (const uint8_t *)buf;
    while (len--) {
        nvram_write_u8(p++, *src++);
    }
}

void nvram_update_u8(uint32_t addr, uint8_t value) { nvram_write_u8(addr, value); }

void nvram_update_u16(uint32_t addr, uint16_t value) {
    uint8_t *p = (uint8_t *)addr;
    nvram_write_u8(p++, value);
    nvram_write_u8(p, value >> 8);
}

void nvram_update_u32(uint32_t addr, uint32_t value) {
    uint8_t *p = (uint8_t *)addr;
    nvram_write_u8(p++, value);
    nvram_write_u8(p++, value >> 8);
    nvram_write_u8(p++, value >> 16);
    nvram_write_u8(p, value >> 24);
}

void nvram_update_block(uint32_t addr, const void *buf, size_t len) {
    uint8_t *      p   = (uint8_t *)addr;
    const uint8_t *src = (const uint8_t *)buf;
    while (len--) {
        nvram_write_u8(p++, *src++);
    }
}
