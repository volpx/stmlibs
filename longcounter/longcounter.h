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
 * For upward counting timer it may be too little to have 16bits only,
 * for example at a counting period of 1us the overflow happens every 65s.
 * This library creates a pollable 64bit counter from a normal 16bit counter
 * retaining very high performance which resets every ~500kyears 
 * (if source counter is 1us period).
 * 
 * Note: It's not necessary to have 1us period, it can be whatever really.
 * 
 * This counter can be used as timebase for functions of time, f(t)=sin(w*t), 
 * due to it not resetting.
 */

#ifndef LONGCOUNTER_H
#define LONGCOUNTER_H

#include "main.h"
#include <stdint.h>

#define LONGCOUNTER_TIM_LENGTH 16

typedef uint64_t LONGCOUNTER_Counter_Type;

typedef struct LONGCOUNTER_HandleStruct {
    TIM_HandleTypeDef *_htim;
    LONGCOUNTER_Counter_Type _counter;
} LONGCOUNTER_HandleTypeDef;

/**
 * @brief     Initialize a LONGCOUNTER_HandleTypeDef structure
 * 
 * @param     handle Reference to the struct to be initialized
 * @param     htim Reference counter, already initialized
 * @return    HAL_OK on success, HAL_ERROR on failure
 */
HAL_StatusTypeDef LONGCOUNTER_init(LONGCOUNTER_HandleTypeDef *handle, TIM_HandleTypeDef *htim);
/**
 * @brief     Gets the LONGCOUNTER_HandleTypeDef resulting counter 
 *                much like the get_tick() function
 * 
 * @param     handle Reference to the handle
 * @return    long counter value
 */
LONGCOUNTER_Counter_Type LONGCOUNTER_get_counter(LONGCOUNTER_HandleTypeDef *handle);

/**
 * @brief     Function to be called in the HAL_TIM_PeriodElapsedCallback function
 * 
 * @param     handle Reference to the handle
 * @param     htim Parameter of the HAL_TIM_PeriodElapsedCallback function
 */
void LONGCOUNTER_TIM_OverflowCallback(LONGCOUNTER_HandleTypeDef *handle, TIM_HandleTypeDef *htim);

#endif //LONGCOUNTER_H