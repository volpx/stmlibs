/*
 * "THE BEER-WARE LICENSE" (Revision 69):
 * Not a Squadra Corse firmware team wrote this file. As long as you retain this notice
 * you can do whatever you want with this stuff. If we meet some day, and you 
 * think this stuff is worth it, you can buy us a beer in return.
 * 
 * Authors
 * - Filippo Volpe [filippovolpe98+dev@gmail.com]
 */

/*
 * Read ann array as if it was sheetmusic.
 * the library decouples the reading of the notes from the actual note generation.
 * The unit of duration is the 1/32 note, the other durations have to be an integer multiple of it. 
 */

#ifndef MUSIC_H
#define MUSIC_H

#include "main.h"
#include "tim.h"
#include <stdint.h>
#include <inttypes.h>

#ifndef MUSIC_SHEET_LENGTH
    #define MUSIC_SHEET_LENGTH 256
#endif //MUSIC_SHEET_LENGTH

typedef struct MUSIC_ChannelHandleStruct {
    uint8_t note[MUSIC_SHEET_LENGTH];
    uint8_t duration[MUSIC_SHEET_LENGTH];
    void (*set_note_callback)();
    uint32_t _index;
    uint64_t _time_start;
    uint64_t (*_get_tick)();
} MUSIC_ChannelHandleTypeDef;

/**
 * @brief     Initialize a MUSIC_HandleTypeDef structure
 * 
 * @param     handle Reference to the struct to be initialized
 * @param     htim Reference counter, already initialized
 * @return    HAL_OK on success, HAL_ERROR on failure
 */
HAL_StatusTypeDef MUSIC_init(MUSIC_ChannelHandleTypeDef *handle, uint64_t (*get_tick)());
/**
 * @brief     Gets the MUSIC_HandleTypeDef 
 * 
 * @param     handle Reference to the handle
 * @return    long counter value
 */
uint8_t MUSIC_get_note(MUSIC_ChannelHandleTypeDef *handle);

#endif //MUSIC_H