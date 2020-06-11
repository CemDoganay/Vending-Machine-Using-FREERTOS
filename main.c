/*Created by:
Cem Doganay
Ahmed Haroon
James Howe

/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2020 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under Ultimate Liberty license
  * SLA0044, the "License"; You may not use this file except in compliance with
  * the License. You may obtain a copy of the License at:
  *                             www.st.com/SLA0044
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "cmsis_os.h"

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
osThreadId Task1Handle;
osThreadId Task2Handle;
osThreadId Task3Handle;
osThreadId Task4Handle;
osThreadId Task5Handle;
osMessageQId Queue1Handle;
osMessageQId Queue2Handle;
osMessageQId Queue3Handle;
osMessageQId Queue4Handle;
/* USER CODE BEGIN PV */
int balance = 0;
int money_input = 0;

TickType_t badTempStartTime;
TickType_t timer;

/*
PCO = LED5
PC1 = LED4
PC2 = LED3
PC3 = LED2
PB12 = LED1

PD9 = BUTTON1
PD8 = BUTTON2
PB15 = BUTTON3
PB14 = BUTTON4
PB13 = BUTTON5 */


/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
void v_Task1(void const * argument);
void v_Task2(void const * argument);
void v_Task3(void const * argument);
void v_Task4(void const * argument);
void v_Task5(void const * argument);

/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

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
  /* USER CODE BEGIN 2 */

  /* USER CODE END 2 */

  /* USER CODE BEGIN RTOS_MUTEX */
  /* add mutexes, ... */
  /* USER CODE END RTOS_MUTEX */

  /* USER CODE BEGIN RTOS_SEMAPHORES */
  /* add semaphores, ... */
  /* USER CODE END RTOS_SEMAPHORES */

  /* USER CODE BEGIN RTOS_TIMERS */
  /* start timers, add new ones, ... */
  /* USER CODE END RTOS_TIMERS */

  /* Create the queue(s) */
  /* definition and creation of Queue1 */
  osMessageQDef(Queue1, 1, uint16_t);
  Queue1Handle = osMessageCreate(osMessageQ(Queue1), NULL);

  /* definition and creation of Queue2 */
  osMessageQDef(Queue2, 1, uint16_t);
  Queue2Handle = osMessageCreate(osMessageQ(Queue2), NULL);

  /* definition and creation of Queue3 */
  osMessageQDef(Queue3, 1, uint16_t);
  Queue3Handle = osMessageCreate(osMessageQ(Queue3), NULL);

  /* definition and creation of Queue4 */
  osMessageQDef(Queue4, 1, uint16_t);
  Queue4Handle = osMessageCreate(osMessageQ(Queue4), NULL);

  /* USER CODE BEGIN RTOS_QUEUES */
  /* add queues, ... */
  /* USER CODE END RTOS_QUEUES */

  /* Create the thread(s) */
  /* definition and creation of Task1 */
  osThreadDef(Task1, v_Task1, osPriorityLow, 0, 128);
  Task1Handle = osThreadCreate(osThread(Task1), NULL);

  /* definition and creation of Task2 */
  osThreadDef(Task2, v_Task2, osPriorityNormal, 0, 128);
  Task2Handle = osThreadCreate(osThread(Task2), NULL);

  /* definition and creation of Task3 */
  osThreadDef(Task3, v_Task3, osPriorityBelowNormal, 0, 128);
  Task3Handle = osThreadCreate(osThread(Task3), NULL);

  /* definition and creation of Task4 */
  osThreadDef(Task4, v_Task4, osPriorityAboveNormal, 0, 128);
  Task4Handle = osThreadCreate(osThread(Task4), NULL);

  /* definition and creation of Task5 */
  osThreadDef(Task5, v_Task5, osPriorityHigh, 0, 128);
  Task5Handle = osThreadCreate(osThread(Task5), NULL);

  /* USER CODE BEGIN RTOS_THREADS */
  /* add threads, ... */
  /* USER CODE END RTOS_THREADS */

  /* Start scheduler */
  osKernelStart();
 
  /* We should never get here as control is now taken by the scheduler */
  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* USER CODE END WHILE */

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

  /** Configure the main internal regulator output voltage 
  */
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);
  /** Initializes the CPU, AHB and APB busses clocks 
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  /** Initializes the CPU, AHB and APB busses clocks 
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_HSI;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOH_CLK_ENABLE();
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();
  __HAL_RCC_GPIOD_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOC, GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_12, GPIO_PIN_RESET);

  /*Configure GPIO pins : PC0 PC1 PC2 PC3 */
  GPIO_InitStruct.Pin = GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

  /*Configure GPIO pin : PB12 */
  GPIO_InitStruct.Pin = GPIO_PIN_12;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /*Configure GPIO pins : PB13 PB14 PB15 */
  GPIO_InitStruct.Pin = GPIO_PIN_13|GPIO_PIN_14|GPIO_PIN_15;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /*Configure GPIO pins : PD8 PD9 */
  GPIO_InitStruct.Pin = GPIO_PIN_8|GPIO_PIN_9;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);

}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/* USER CODE BEGIN Header_v_Task1 */
/**
  * @brief  Function implementing the Task1 thread.
  * @param  argument: Not used 
  * @retval None
  */
/* USER CODE END Header_v_Task1 */
void v_Task1(void const * argument)
{
	TickType_t start = xTaskGetTickCount();
	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_0, GPIO_PIN_RESET); //signals payment phase

	for (;;)
	{
		money_input = 0;
		
		//xQueueSendToBack(Queue4Handle, Task1Handle, portMAX_DELAY); critical task
		
		if (balance >= 15)
		{
			xQueueSendToBack(Queue2Handle, Task1Handle, portMAX_DELAY);
		}

		if ((xTaskGetTickCount() - start) >= pdMS_TO_TICKS(15000)) 
			{
			xQueueSendToBack(Queue3Handle, Task1Handle, portMAX_DELAY);
			start = xTaskGetTickCount();
			HAL_GPIO_WritePin(GPIOC, GPIO_PIN_0, GPIO_PIN_RESET);
		}
		
		if (HAL_GPIO_ReadPin(GPIOD, GPIO_PIN_9)) //1 dollar button 
		{
			money_input = 1;
			xQueueSendToBack(Queue1Handle, Task1Handle, portMAX_DELAY);
			start = xTaskGetTickCount();
		}

		if (HAL_GPIO_ReadPin(GPIOD, GPIO_PIN_8)) //2 dollar button 
		{
			money_input = 2;
			xQueueSendToBack(Queue1Handle, Task1Handle, portMAX_DELAY);
			start = xTaskGetTickCount();
		}

		if (HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_13)) // next button     
		{
			xQueueSendToBack(Queue2Handle, Task1Handle, portMAX_DELAY);
			TickType_t start = xTaskGetTickCount();
			HAL_GPIO_WritePin(GPIOC, GPIO_PIN_0, GPIO_PIN_RESET);
		}
	}
}

/* USER CODE BEGIN Header_v_Task2 */
/**
* @brief Function implementing the Task2 thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_v_Task2 */
void v_Task3(void const * argument)
{
 
	xQueueReceive(Queue2Handle, Task3Handle, portMAX_DELAY);
	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_0, GPIO_PIN_SET); // signals selection phase
	HAL_Delay(200);
	
	  /* Infinite loop */

	for (;;)
	{
		
		money_input = 0;
		// xQueueSendToBack(Queue4Handle, Task3Handle, portMAX_DELAY); safety critical task		


	 if (HAL_GPIO_ReadPin(GPIOD, GPIO_PIN_9)) //button for $1 chocolate
		{
			money_input = -1;
			xQueueSendToBack(Queue1Handle, Task3Handle, portMAX_DELAY);
		}

		else if (HAL_GPIO_ReadPin(GPIOD, GPIO_PIN_8)) //button for $2 chocolate
		{
			money_input = -2;
			xQueueSendToBack(Queue1Handle, Task3Handle, portMAX_DELAY);
		}

		else if (HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_15)) //button $3 chocolate
		{
			money_input = -3;
			xQueueSendToBack(Queue1Handle, Task3Handle, portMAX_DELAY);
		}
		
		else if (HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_14)) //button $4 chocolate
		{
			money_input = -4;
			xQueueSendToBack(Queue1Handle, Task3Handle, portMAX_DELAY);
		}
		
		else if (HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_13)) //done transaction and/or refund selection button
		{
			xQueueSendToBack(Queue3Handle, Task3Handle, portMAX_DELAY);
			xQueueReceive(Queue2Handle, Task3Handle, portMAX_DELAY);
			HAL_GPIO_WritePin(GPIOC, GPIO_PIN_0, GPIO_PIN_SET);
		
		}
		
	}
}

/* USER CODE BEGIN Header_v_Task3 */
/**
* @brief Function implementing the Task3 thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_v_Task3 */
void v_Task2(void const * argument)
{
{
    int n = 0;
		
		
    for (;;)
    {
		
        xQueueReceive(Queue1Handle, Task2Handle, portMAX_DELAY);

        if (balance + money_input >= 0)
        {
            balance = balance + money_input;
        }
				money_input = 0;
        

        HAL_GPIO_WritePin(GPIOB, GPIO_PIN_12, GPIO_PIN_RESET); // update!
        HAL_GPIO_WritePin(GPIOC, GPIO_PIN_3, GPIO_PIN_RESET); // update!
        HAL_GPIO_WritePin(GPIOC, GPIO_PIN_2, GPIO_PIN_RESET); // update!
        HAL_GPIO_WritePin(GPIOC, GPIO_PIN_1, GPIO_PIN_RESET); // update!
        
				n = balance;
				
        // function to convert decimal to binary

				int binaryNum[4] = {0,0,0,0};
         // array to store binary number
        

        // counter for binary array
        int i = 0;
        while (n > 0) {

            // storing remainder in binary array
            binaryNum[i] = n % 2;
            n = n / 2;
            i++;
        }

        // printing binary array in reverse order
        if (binaryNum[0] == 1)
        {
            HAL_GPIO_WritePin(GPIOB, GPIO_PIN_12, GPIO_PIN_SET); // update!	
						HAL_Delay(200);
						/*HAL_GPIO_WritePin(GPIOB, GPIO_PIN_12, GPIO_PIN_RESET); // update!	
						HAL_Delay(500);
						HAL_GPIO_WritePin(GPIOB, GPIO_PIN_12, GPIO_PIN_SET); // update!	
						HAL_Delay(500);  */
        }

        if (binaryNum[1] == 1)
        {
            HAL_GPIO_WritePin(GPIOC, GPIO_PIN_3, GPIO_PIN_SET); // update!
						HAL_Delay(200);
					/*HAL_GPIO_WritePin(GPIOC, GPIO_PIN_3, GPIO_PIN_RESET); // update!	
						HAL_Delay(500);
						HAL_GPIO_WritePin(GPIOC, GPIO_PIN_3, GPIO_PIN_SET); // update!	
						HAL_Delay(500);	*/			
        }

        if (binaryNum[2] == 1)
        {
            HAL_GPIO_WritePin(GPIOC, GPIO_PIN_2, GPIO_PIN_SET); // update!	
						HAL_Delay(200);
					/*HAL_GPIO_WritePin(GPIOC, GPIO_PIN_2, GPIO_PIN_RESET); // update!	
						HAL_Delay(500);
						HAL_GPIO_WritePin(GPIOC, GPIO_PIN_2, GPIO_PIN_SET); // update!	
						HAL_Delay(500); */
        }

        if (binaryNum[3] == 1)
        {
            HAL_GPIO_WritePin(GPIOC, GPIO_PIN_1, GPIO_PIN_SET); // update!
						HAL_Delay(200);
					/*	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_1, GPIO_PIN_RESET); // update!	
						HAL_Delay(500);
						HAL_GPIO_WritePin(GPIOC, GPIO_PIN_1, GPIO_PIN_SET); // update!	
						HAL_Delay(500);	*/		
        }

    }

}
}

/* USER CODE BEGIN Header_v_Task4 */
/**
* @brief Function implementing the Task4 thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_v_Task4 */
void v_Task4(void const * argument)
{
	for(;;)
	{
	
		xQueueReceive(Queue3Handle, Task4Handle, portMAX_DELAY);

    balance = 0;

     HAL_GPIO_WritePin(GPIOB, GPIO_PIN_12, GPIO_PIN_RESET); // update!
     HAL_GPIO_WritePin(GPIOC, GPIO_PIN_3, GPIO_PIN_RESET); // update!
     HAL_GPIO_WritePin(GPIOC, GPIO_PIN_2, GPIO_PIN_RESET); // update!
     HAL_GPIO_WritePin(GPIOC, GPIO_PIN_1, GPIO_PIN_RESET); // update!

    // xQueueReceive(Queue3Handle, Task4Handle, portMAX_DELAY);
	}
}

/* USER CODE BEGIN Header_v_Task5 */
/**
* @brief Function implementing the Task5 thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_v_Task5 */
void v_Task5(void const * argument) //safety critical task
{
int temp = 0;

	for (;;)
	{
	
		xQueueReceive(Queue4Handle, Task5Handle, portMAX_DELAY);

		if (badTempStartTime != 0 && ((xTaskGetTickCount() - badTempStartTime) > pdMS_TO_TICKS(900000)))
			{
				for (;;)
				{
					HAL_GPIO_WritePin(GPIOC, GPIO_PIN_5, GPIO_PIN_SET); 
					HAL_Delay(500);
					HAL_GPIO_WritePin(GPIOC, GPIO_PIN_5, GPIO_PIN_RESET);
					HAL_Delay(500);
				
				}
			}


		/*if (temp != getTemp())       Safety critical section
		{
			if (getTemp() >= 25)
			{
				badTempStartTime = xTaskGetTickCount();
			}
			
			else
			{
				badTempStartTime = 0;
			}
		} */

	}
}

 /**
  * @brief  Period elapsed callback in non blocking mode
  * @note   This function is called  when TIM1 interrupt took place, inside
  * HAL_TIM_IRQHandler(). It makes a direct call to HAL_IncTick() to increment
  * a global variable "uwTick" used as application time base.
  * @param  htim : TIM handle
  * @retval None
  */
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
  /* USER CODE BEGIN Callback 0 */

  /* USER CODE END Callback 0 */
  if (htim->Instance == TIM1) {
    HAL_IncTick();
  }
  /* USER CODE BEGIN Callback 1 */

  /* USER CODE END Callback 1 */
}

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */

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
     tex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
