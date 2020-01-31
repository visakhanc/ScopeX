

/*
 *
 * Times_12pt
 *
 * created with FontCreator
 * written by F. Maximilian Thiele
 *
 * http://www.apetech.de/fontCreator
 * me@apetech.de
 *
 * File Name           : Times_12pt.h
 * Date                : 12.05.2013
 * Font size in bytes  : 2133
 * Font width          : 10
 * Font height         : 11
 * Font first char     : 65
 * Font last char      : 91
 * Font used chars     : 26
 *
 * The font data are defined as
 *
 * struct _FONT_ {
 *     uint16_t   font_Size_in_Bytes_over_all_included_Size_it_self;
 *     uint8_t    font_Width_in_Pixel_for_fixed_drawing;
 *     uint8_t    font_Height_in_Pixel_for_all_characters;
 *     unit8_t    font_First_Char;
 *     uint8_t    font_Char_Count;
 *
 *     uint8_t    font_Char_Widths[font_Last_Char - font_First_Char +1];
 *                  // for each character the separate width in pixels,
 *                  // characters < 128 have an implicit virtual right empty row
 *
 *     uint8_t    font_data[];
 *                  // bit field of all characters
 */

#include <inttypes.h>
#include <avr/pgmspace.h>

#ifndef TIMES_12PT_H
#define TIMES_12PT_H

#define TIMES_12PT_WIDTH 10
#define TIMES_12PT_HEIGHT 11

uint8_t Times_12[] PROGMEM = {
    0x08, 0x55, // size
    0x0A, // width
    0x0B, // height
    0x41, // first char
    0x1A, // char count
    
    // char widths
    0x08, 0x07, 0x07, 0x08, 0x07, 0x06, 0x08, 0x08, 0x03, 0x04, 
    0x08, 0x07, 0x0B, 0x08, 0x08, 0x06, 0x08, 0x08, 0x05, 0x07, 
    0x08, 0x07, 0x0B, 0x08, 0x08, 0x07, 
    
    // font data
    0x00, 0xC0, 0x3C, 0x23, 0x2C, 0x30, 0xC0, 0x00, 0x20, 0x20, 0x20, 0x00, 0x00, 0x20, 0x20, 0x20, // 65
    0x01, 0xFF, 0x11, 0x11, 0x11, 0x1E, 0xE0, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x00, // 66
    0x7C, 0x82, 0x01, 0x01, 0x01, 0x82, 0x47, 0x00, 0x00, 0x20, 0x20, 0x20, 0x00, 0x00, // 67
    0x01, 0xFF, 0x01, 0x01, 0x01, 0x01, 0x82, 0x7C, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x00, 0x00, // 68
    0x01, 0xFF, 0x11, 0x11, 0x39, 0x03, 0x80, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x00, // 69
    0x01, 0xFF, 0x11, 0x11, 0x39, 0x03, 0x20, 0x20, 0x20, 0x00, 0x00, 0x00, // 70
    0x7C, 0x82, 0x01, 0x01, 0x01, 0x12, 0xF7, 0x10, 0x00, 0x00, 0x20, 0x20, 0x20, 0x20, 0x00, 0x00, // 71
    0x01, 0xFF, 0x11, 0x10, 0x10, 0x11, 0xFF, 0x01, 0x20, 0x20, 0x20, 0x00, 0x00, 0x20, 0x20, 0x20, // 72
    0x01, 0xFF, 0x01, 0x20, 0x20, 0x20, // 73
    0x80, 0x01, 0xFF, 0x01, 0x20, 0x20, 0x00, 0x00, // 74
    0x01, 0xFF, 0x11, 0x28, 0x44, 0x83, 0x01, 0x01, 0x20, 0x20, 0x20, 0x00, 0x00, 0x20, 0x20, 0x20, // 75
    0x01, 0xFF, 0x01, 0x00, 0x00, 0x00, 0x80, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x00, // 76
    0x01, 0xFF, 0x03, 0x0C, 0x70, 0x80, 0x70, 0x0C, 0x03, 0xFF, 0x01, 0x20, 0x20, 0x20, 0x00, 0x00, 0x20, 0x00, 0x00, 0x20, 0x20, 0x20, // 77
    0x01, 0xFF, 0x04, 0x08, 0x30, 0x41, 0xFF, 0x01, 0x20, 0x20, 0x20, 0x00, 0x00, 0x00, 0x20, 0x00, // 78
    0x7C, 0x82, 0x01, 0x01, 0x01, 0x01, 0x82, 0x7C, 0x00, 0x00, 0x20, 0x20, 0x20, 0x20, 0x00, 0x00, // 79
    0x01, 0xFF, 0x11, 0x11, 0x11, 0x0E, 0x20, 0x20, 0x20, 0x00, 0x00, 0x00, // 80
    0x7C, 0x82, 0x01, 0x01, 0x01, 0x01, 0x82, 0x7C, 0x00, 0x00, 0x20, 0x20, 0x60, 0xA0, 0x80, 0x80, // 81
    0x01, 0xFF, 0x11, 0x11, 0x71, 0x8E, 0x00, 0x00, 0x20, 0x20, 0x20, 0x00, 0x00, 0x00, 0x20, 0x20, // 82
    0x86, 0x09, 0x11, 0x11, 0xE3, 0x20, 0x20, 0x20, 0x20, 0x00, // 83
    0x03, 0x01, 0x01, 0xFF, 0x01, 0x01, 0x03, 0x00, 0x00, 0x20, 0x20, 0x20, 0x00, 0x00, // 84
    0x01, 0xFF, 0x01, 0x00, 0x00, 0x01, 0xFF, 0x01, 0x00, 0x00, 0x20, 0x20, 0x20, 0x20, 0x00, 0x00, // 85
    0x01, 0x0F, 0x71, 0x80, 0x71, 0x0F, 0x01, 0x00, 0x00, 0x00, 0x20, 0x00, 0x00, 0x00, // 86
    0x01, 0x0F, 0x71, 0xC0, 0x31, 0x0F, 0x71, 0xC0, 0x39, 0x07, 0x01, 0x00, 0x00, 0x00, 0x20, 0x00, 0x00, 0x00, 0x20, 0x00, 0x00, 0x00, // 87
    0x01, 0x83, 0x45, 0x38, 0x38, 0x45, 0x83, 0x01, 0x20, 0x20, 0x20, 0x00, 0x00, 0x20, 0x20, 0x20, // 88
    0x01, 0x03, 0x1D, 0xE0, 0x18, 0x05, 0x03, 0x01, 0x00, 0x00, 0x20, 0x20, 0x20, 0x00, 0x00, 0x00, // 89
    0x00, 0xC3, 0x21, 0x19, 0x05, 0x03, 0xC1, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20 // 90
    
};

#endif
