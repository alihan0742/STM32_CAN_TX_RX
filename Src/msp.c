#include "main.h"

void HAL_MspInit(void)
{
	//1. Set up the priority grouping of the arm cortex mx processor
	HAL_NVIC_SetPriorityGrouping(NVIC_PRIORITYGROUP_4);
	//kullanım hatası, bellek hatası ve veri yolu hatası sistemi istisnaları
	SCB->SHCSR |= 0x7 << 16;

	HAL_NVIC_SetPriority(MemoryManagement_IRQn, 0, 0);
	HAL_NVIC_SetPriority(BusFault_IRQn, 0, 0);
	HAL_NVIC_SetPriority(UsageFault_IRQn, 0, 0);
}

void HAL_TIM_Base_MspInit(TIM_HandleTypeDef *htimer6)
{
	//tim6 clock enable
	__HAL_RCC_TIM6_CLK_ENABLE();

	//kesme işleme aktif
	HAL_NVIC_EnableIRQ(TIM6_DAC_IRQn);

	//öncelik sırası
	HAL_NVIC_SetPriority(TIM6_DAC_IRQn, 15, 0);
}

void HAL_UART_MspInit(UART_HandleTypeDef *huart)
{
	GPIO_InitTypeDef gpioUart;

	__HAL_RCC_USART2_CLK_ENABLE();   // usart clock
 	__HAL_RCC_GPIOA_CLK_ENABLE();  //usart a bağlı gpio

 	gpioUart.Pin = GPIO_PIN_2;
 	gpioUart.Mode = GPIO_MODE_AF_PP;
 	gpioUart.Pull = GPIO_PULLUP;
 	gpioUart.Speed = GPIO_SPEED_FREQ_LOW;
 	gpioUart.Alternate = GPIO_AF7_USART2;   //UART2_TX
 	HAL_GPIO_Init(GPIOA, &gpioUart);

 	gpioUart.Pin = GPIO_PIN_3;  // uart2 RX
 	HAL_GPIO_Init(GPIOA,&gpioUart);

 	HAL_NVIC_EnableIRQ(USART2_IRQn);

 	HAL_NVIC_SetPriority(USART2_IRQn, 15, 0);
}

void HAL_CAN_MspInit(CAN_HandleTypeDef *hcan)
{
	GPIO_InitTypeDef GPIO_CAN;
	__HAL_RCC_CAN1_CLK_ENABLE();

	GPIO_CAN.Pin = GPIO_PIN_11|GPIO_PIN_12;
	GPIO_CAN.Mode = GPIO_MODE_AF_PP;
	GPIO_CAN.Pull = GPIO_NOPULL;
	GPIO_CAN.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
	GPIO_CAN.Alternate = GPIO_AF9_CAN1;
	HAL_GPIO_Init(GPIOA, &GPIO_CAN);

	HAL_NVIC_SetPriority(CAN1_TX_IRQn,15,0);
	HAL_NVIC_SetPriority(CAN1_RX0_IRQn,15,0);
	HAL_NVIC_SetPriority(CAN1_RX1_IRQn,15,0);
	HAL_NVIC_SetPriority(CAN1_SCE_IRQn,15,0);

	HAL_NVIC_EnableIRQ(CAN1_TX_IRQn);
	HAL_NVIC_EnableIRQ(CAN1_RX0_IRQn);
	HAL_NVIC_EnableIRQ(CAN1_RX1_IRQn);
	HAL_NVIC_EnableIRQ(CAN1_SCE_IRQn);

}
