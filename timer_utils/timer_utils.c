#include "timer_utils.h"

uint32_t TIM_GetInternalClkFreq(TIM_HandleTypeDef *htim) {
  RCC_ClkInitTypeDef clkConfig;
  uint32_t pFlatency;
  uint32_t uwTimClock, uwAPBxPrescaler = 0U;

  /* Get clock configuration */
  HAL_RCC_GetClockConfig(&clkConfig, &pFlatency);

  /* Get APBx prescaler and base clock*/
    if (_M_GET_TIM_APB_PLACEMENT(htim)) {
        uwAPBxPrescaler = clkConfig.APB1CLKDivider;
        uwTimClock      = HAL_RCC_GetPCLK1Freq();
    } else {
        uwAPBxPrescaler = clkConfig.APB2CLKDivider;
        uwTimClock      = HAL_RCC_GetPCLK2Freq();
    }

    /* Compute final clock */
    if (uwAPBxPrescaler != RCC_HCLK_DIV1) {
        /* When the prescaler is not one the frequncy is multipled by 2 for timers */
        uwTimClock *= 2;
    }

    return uwTimClock;
}