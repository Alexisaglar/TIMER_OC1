/*
 * msp.c
 *
 *  Created on: Apr 2, 2020
 *      Author: alexisaglar
 */

#include "main.h"
void HAL_MspInit(void)
{
	//Here will do low level processor specific inits.
	//1. Set up the priority group of the arm cortex mx processor
	HAL_NVIC_SetPriorityGrouping(NVIC_PRIORITYGROUP_4);

	//2. Enable the requiered system exceptions of the arm cortex arm processor
	SCB->SHCSR |= 0x7 << 16; //usg fault, memoryfault, bus fault system exceptions

	//3. Configure the priority for the system exceptions
	HAL_NVIC_SetPriority(MemoryManagement_IRQn, 0, 0);
	HAL_NVIC_SetPriority(BusFault_IRQn, 0, 0);
	HAL_NVIC_SetPriority(UsageFault_IRQn, 0, 0);
}

void HAL_TIM_OC_MspInit(TIM_HandleTypeDef *htim){
	GPIO_InitTypeDef tim3OC_ch_gpios;
	//1. enable the peripheral clock for the timer3 peripheral
	__HAL_RCC_TIM3_CLK_ENABLE();
	__HAL_RCC_GPIOA_CLK_ENABLE();
	__HAL_RCC_GPIOB_CLK_ENABLE();
	//2.
	/*PA6 --> TIM3_CH1
	PA7 --> TIM3_CH2
	PB0 --> TIM3_CH3
	PB1 --> TIM3_CH4
	*/
	tim3OC_ch_gpios.Pin = GPIO_PIN_6 | GPIO_PIN_7;
	tim3OC_ch_gpios.Mode = GPIO_MODE_AF_PP;
	tim3OC_ch_gpios.Pull = GPIO_NOPULL;
	tim3OC_ch_gpios.Speed = GPIO_SPEED_FREQ_LOW;
	tim3OC_ch_gpios.Alternate = GPIO_AF2_TIM3;
	HAL_GPIO_Init(GPIOA,&tim3OC_ch_gpios);


	tim3OC_ch_gpios.Pin = GPIO_PIN_0 | GPIO_PIN_1;
	tim3OC_ch_gpios.Mode = GPIO_MODE_AF_PP;
	tim3OC_ch_gpios.Pull = GPIO_NOPULL;
	tim3OC_ch_gpios.Speed = GPIO_SPEED_FREQ_LOW;
	tim3OC_ch_gpios.Alternate = GPIO_AF2_TIM3;
	HAL_GPIO_Init(GPIOA,&tim3OC_ch_gpios);

	//3. NVIC Settings
	HAL_NVIC_SetPriority(TIM3_IRQn,15,0);
	HAL_NVIC_EnableIRQ(TIM3_IRQn);


}


void HAL_UART_MspInit(UART_HandleTypeDef *huart)
{
  //here we are going to do the low level inits. of the USART2 peripheral
	GPIO_InitTypeDef gpio_uart;
	//1. enable the clock for the USART2 Peripheral
	__HAL_RCC_USART2_CLK_ENABLE();
	__HAL_RCC_GPIOA_CLK_ENABLE();
	//2. Do the pin muxing configurations
	gpio_uart.Pin = GPIO_PIN_2;
	gpio_uart.Mode = GPIO_MODE_AF_PP;
	gpio_uart.Pull = GPIO_PULLUP;
	gpio_uart.Speed = GPIO_SPEED_FREQ_LOW;
	gpio_uart.Alternate = GPIO_AF7_USART2; //UART2_TX
	HAL_GPIO_Init(GPIOA,&gpio_uart);

	gpio_uart.Pin = GPIO_PIN_3; //UART_RX
	HAL_GPIO_Init(GPIOA,&gpio_uart);

	//3. Enable the IRQ and set up the priority (NVIC settings)
	HAL_NVIC_EnableIRQ(USART2_IRQn);
	HAL_NVIC_SetPriority(USART2_IRQn, 15, 0);

}
