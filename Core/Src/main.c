/* USER CODE BEGIN Header */
/**
 ******************************************************************************
 * @file           : main.c
 * @brief          : Main program body
 ******************************************************************************
 * @attention
 *
 * Copyright (c) 2023 STMicroelectronics.
 * All rights reserved.
 *
 * This software is licensed under terms that can be found in the LICENSE file
 * in the root directory of this software component.
 * If no LICENSE file comes with this software, it is provided AS-IS.
 *
 ******************************************************************************
 */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "eth.h"
#include "tim.h"
#include "usart.h"
#include "usb_otg.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
uint8_t keyboard;

char readKeypad (void)
{
	/* Make ROW 1 LOW and all other ROWs HIGH */
	HAL_GPIO_WritePin (Row1_GPIO_Port, Row1_Pin, GPIO_PIN_RESET);  //Pull the R1 low
	HAL_GPIO_WritePin (Row2_GPIO_Port, Row2_Pin, GPIO_PIN_SET);  // Pull the R2 High
	HAL_GPIO_WritePin (Row3_GPIO_Port, Row3_Pin, GPIO_PIN_SET);  // Pull the R3 High
	HAL_GPIO_WritePin (Row4_GPIO_Port, Row4_Pin, GPIO_PIN_SET);  // Pull the R4 High

	if (!(HAL_GPIO_ReadPin (Col1_GPIO_Port, Col1_Pin)))   // if the Col 1 is low
	{
		while (!(HAL_GPIO_ReadPin (Col1_GPIO_Port, Col1_Pin)));   // wait till the button is pressed
		return '1';
	}

	if (!(HAL_GPIO_ReadPin (Col2_GPIO_Port, Col2_Pin)))   // if the Col 2 is low
	{
		while (!(HAL_GPIO_ReadPin (Col2_GPIO_Port, Col2_Pin)));   // wait till the button is pressed
		return '2';
	}

	if (!(HAL_GPIO_ReadPin (Col3_GPIO_Port, Col3_Pin)))   // if the Col 3 is low
	{
		while (!(HAL_GPIO_ReadPin (Col3_GPIO_Port, Col3_Pin)));   // wait till the button is pressed
		return '3';
	}

	/* Make ROW 2 LOW and all other ROWs HIGH */
	HAL_GPIO_WritePin (Row1_GPIO_Port, Row1_Pin, GPIO_PIN_SET);  //Pull the R1 low
	HAL_GPIO_WritePin (Row2_GPIO_Port, Row2_Pin, GPIO_PIN_RESET);  // Pull the R2 High
	HAL_GPIO_WritePin (Row3_GPIO_Port, Row3_Pin, GPIO_PIN_SET);  // Pull the R3 High
	HAL_GPIO_WritePin (Row4_GPIO_Port, Row4_Pin, GPIO_PIN_SET);  // Pull the R4 High

	if (!(HAL_GPIO_ReadPin (Col1_GPIO_Port, Col1_Pin)))   // if the Col 1 is low
	{
		while (!(HAL_GPIO_ReadPin (Col1_GPIO_Port, Col1_Pin)));   // wait till the button is pressed
		return '4';
	}

	if (!(HAL_GPIO_ReadPin (Col2_GPIO_Port, Col2_Pin)))   // if the Col 2 is low
	{
		while (!(HAL_GPIO_ReadPin (Col2_GPIO_Port, Col2_Pin)));   // wait till the button is pressed
		return '5';
	}

	if (!(HAL_GPIO_ReadPin (Col3_GPIO_Port, Col3_Pin)))   // if the Col 3 is low
	{
		while (!(HAL_GPIO_ReadPin (Col3_GPIO_Port, Col3_Pin)));   // wait till the button is pressed
		return '6';
	}

	/* Make ROW 3 LOW and all other ROWs HIGH */
	HAL_GPIO_WritePin (Row1_GPIO_Port, Row1_Pin, GPIO_PIN_SET);  //Pull the R1 low
	HAL_GPIO_WritePin (Row2_GPIO_Port, Row2_Pin, GPIO_PIN_SET);  // Pull the R2 High
	HAL_GPIO_WritePin (Row3_GPIO_Port, Row3_Pin, GPIO_PIN_RESET);  // Pull the R3 High
	HAL_GPIO_WritePin (Row4_GPIO_Port, Row4_Pin, GPIO_PIN_SET);  // Pull the R4 High

	if (!(HAL_GPIO_ReadPin (Col1_GPIO_Port, Col1_Pin)))   // if the Col 1 is low
	{
		while (!(HAL_GPIO_ReadPin (Col1_GPIO_Port, Col1_Pin)));   // wait till the button is pressed
		return '7';
	}

	if (!(HAL_GPIO_ReadPin (Col2_GPIO_Port, Col2_Pin)))   // if the Col 2 is low
	{
		while (!(HAL_GPIO_ReadPin (Col2_GPIO_Port, Col2_Pin)));   // wait till the button is pressed
		return '8';
	}

	if (!(HAL_GPIO_ReadPin (Col3_GPIO_Port, Col3_Pin)))   // if the Col 3 is low
	{
		while (!(HAL_GPIO_ReadPin (Col3_GPIO_Port, Col3_Pin)));   // wait till the button is pressed
		return '9';
	}

	/* Make ROW 4 LOW and all other ROWs HIGH */
	HAL_GPIO_WritePin (Row1_GPIO_Port, Row1_Pin, GPIO_PIN_SET);  //Pull the R1 low
	HAL_GPIO_WritePin (Row2_GPIO_Port, Row2_Pin, GPIO_PIN_SET);  // Pull the R2 High
	HAL_GPIO_WritePin (Row3_GPIO_Port, Row3_Pin, GPIO_PIN_SET);  // Pull the R3 High
	HAL_GPIO_WritePin (Row4_GPIO_Port, Row4_Pin, GPIO_PIN_RESET);  // Pull the R4 High

	if (!(HAL_GPIO_ReadPin (Col1_GPIO_Port, Col1_Pin)))   // if the Col 1 is low
	{
		while (!(HAL_GPIO_ReadPin (Col1_GPIO_Port, Col1_Pin)));   // wait till the button is pressed
		return '*';
	}

	if (!(HAL_GPIO_ReadPin (Col2_GPIO_Port, Col2_Pin)))   // if the Col 2 is low
	{
		while (!(HAL_GPIO_ReadPin (Col2_GPIO_Port, Col2_Pin)));   // wait till the button is pressed
		return '0';
	}

	if (!(HAL_GPIO_ReadPin (Col3_GPIO_Port, Col3_Pin)))   // if the Col 3 is low
	{
		while (!(HAL_GPIO_ReadPin (Col3_GPIO_Port, Col3_Pin)));   // wait till the button is pressed
		return '#';
	}
}

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_ETH_Init();
  MX_USART3_UART_Init();
  MX_USB_OTG_FS_PCD_Init();
  MX_TIM2_Init();
  MX_TIM3_Init();
  /* USER CODE BEGIN 2 */
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
	while (1) {
    /* USER CODE END WHILE */
		keyboard = readKeypad();

		if (keyboard!=0x01) {
			HAL_UART_Transmit(&huart3, &keyboard, 1, 1000);
			HAL_UART_Transmit(&huart3, "\n", 1, 1000);
		}
		HAL_Delay(200);

    /* USER CODE BEGIN 3 */
	}
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Configure LSE Drive Capability
  */
  HAL_PWR_EnableBkUpAccess();

  /** Configure the main internal regulator output voltage
  */
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE3);

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_BYPASS;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = 4;
  RCC_OscInitStruct.PLL.PLLN = 72;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 3;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
	/* User can add his own implementation to report the HAL error return state */
	__disable_irq();
	while (1) {
	}
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
