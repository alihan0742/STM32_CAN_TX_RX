#include "main.h"

extern CAN_HandleTypeDef hcan1;
extern TIM_HandleTypeDef htimer6;
extern void CAN1_TX(uint8_t remote);

void SysTick_Handler (void)
{
	HAL_IncTick();
	HAL_SYSTICK_IRQHandler();
}

void Can1_TX_IRQ(void)
{
	HAL_CAN_IRQHandler(&hcan1);
}

void Can1_RX0_IRQ(void)
{
	HAL_CAN_IRQHandler(&hcan1);
}

void CAN1_SCE_IRQ(void)
{
	HAL_CAN_IRQHandler(&hcan1);
}

void TIM6_DAC_IRQ(void)
{
	HAL_TIM_IRQHandler(&htimer6);
}

void EXTI0_IRQ(void)
{
	HAL_TIM_Base_Start_IT(&htimer6);
	HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_0);

}
