/*
 * "THE BEER-WARE LICENSE" (Revision 69):
 * Not a Squadra Corse firmware team wrote this file. As long as you retain this notice
 * you can do whatever you want with this stuff. If we meet some day, and you 
 * think this stuff is worth it, you can buy us a beer in return.
 * 
 * Authors
 * - Filippo Volpe [filippovolpe98+dev@gmail.com]
 */

#include "music.h"

HAL_StatusTypeDef MUSIC_init(MUSIC_ChannelHandleTypeDef *handle, uint64_t (*get_tick)()) {
    if(handle == NULL || get_tick == NULL) {
        return HAL_ERROR;
    }

    handle->set_note_callback=0;
    handle->_index=0;
    handle->_time_start=UINT64_MAX;
    handle->_get_tick=get_tick;

    return HAL_OK;
}

HAL_StatusTypeDef MUSIC_start(MUSIC_ChannelHandleTypeDef *handle) {
    handle->_index=0;
    handle->_time_start=handle->_get_tick();
    return HAL_OK;
}

HAL_StatusTypeDef MUSIC_routine(MUSIC_ChannelHandleTypeDef *handle) {
    if ( handle->_time_start == UINT64_MAX ){
        // hold state, skip
        return HAL_OK;
    }

    uint64_t time_now = handle->_get_tick();
    if(time_now - handle->_time_start > handle->duration[handle->_index]){
        // Go to the next
        handle->_index++;
        handle->_time_start=time_now;

        if(handle->set_note_callback){
            handle->set_note_callback();
        }
    }

    return HAL_OK;
}

uint8_t MUSIC_get_note(MUSIC_ChannelHandleTypeDef *handle) {
    return handle->note[handle->_index];
}