/**
  ******************************************************************************
  * @brief   This example briefly describes how to use the stSSD1306lib
  ******************************************************************************
 */

/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "ssd1306.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
#define I2C_TIMING			0x00100306
#define I2C_SLAVE_ADDRESS	0x3C
#define SSD1306_HEIGHT		32

/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
I2C_HandleTypeDef i2c1Handle;

/* Private function prototypes -----------------------------------------------*/
static void SystemClock_Config(void);
static void inizialize_I2C1(void);

/* Private functions ---------------------------------------------------------*/

int main(void)
{
  HAL_Init();
  
  /* Configure the system clock to have a system clock = 72 Mhz */
  SystemClock_Config();
  
  inizialize_I2C1();
  
  SSD1306_HandleTypeDef ssd1306Handle;
  ssd1306_Init(&ssd1306Handle, I2C_SLAVE_ADDRESS, SSD1306_HEIGHT, &i2c1Handle);
  
  BSP_LED_Init(LED_GREEN);
  BSP_LED_Toggle(LED_GREEN);	//All ok!
  
  ssd1306_write_string(&ssd1306Handle, "Temperatura 29 C");
  
  while(1)
  {
	
  }
  
}

/**
  * @brief  Inizializza l'handle I2C1 nelle variabili globali
  * @param  None
  * @retval None
  */
static void inizialize_I2C1(void)
{
	i2c1Handle.Instance					= I2C1;
	i2c1Handle.Init.AddressingMode		= I2C_ADDRESSINGMODE_7BIT;
	i2c1Handle.Init.DualAddressMode		= I2C_DUALADDRESS_DISABLE;
	i2c1Handle.Init.GeneralCallMode		= I2C_GENERALCALL_DISABLE;
	i2c1Handle.Init.NoStretchMode		= I2C_NOSTRETCH_DISABLE;
	i2c1Handle.Init.OwnAddress1			= 0;
	i2c1Handle.Init.OwnAddress2			= 0;
	i2c1Handle.Init.OwnAddress2Masks	= I2C_OA2_NOMASK;
	i2c1Handle.Init.Timing				= I2C_TIMING;
	
	if(HAL_I2C_Init(&i2c1Handle) != HAL_OK) {
		Error_Handler();
	}
}

/**
  * @brief  System Clock Configuration
  *         The system Clock is configured as follow : 
  *            System Clock source            = PLL (HSE)
  *            SYSCLK(Hz)                     = 72000000
  *            HCLK(Hz)                       = 72000000
  *            AHB Prescaler                  = 1
  *            APB1 Prescaler                 = 2
  *            APB2 Prescaler                 = 1
  *            HSE Frequency(Hz)              = 8000000
  *            HSE PREDIV                     = 1
  *            PLLMUL                         = RCC_PLL_MUL9 (9)
  *            Flash Latency(WS)              = 2
  * @param  None
  * @retval None
  */
static void SystemClock_Config(void)
{
  RCC_ClkInitTypeDef RCC_ClkInitStruct;
  RCC_OscInitTypeDef RCC_OscInitStruct;
  
  /* Enable HSE Oscillator and activate PLL with HSE as source */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.HSEPredivValue = RCC_HSE_PREDIV_DIV1;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL9;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct)!= HAL_OK)
  {
    Error_Handler();
  }

  /* Select PLL as system clock source and configure the HCLK, PCLK1 and PCLK2 
     clocks dividers */
  RCC_ClkInitStruct.ClockType = (RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2);
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;  
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;
  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2)!= HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief  This function is executed in case of error occurrence.
  * @param  None
  * @retval None
  */
void Error_Handler(void)
{
  /* User may add here some code to deal with this error */
	BSP_LED_Init(LED_RED);
	BSP_LED_Toggle(LED_RED);
	while(1)
	{
	}
}

#ifdef  USE_FULL_ASSERT

/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(char* file, uint32_t line)
{ 
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */

  /* Infinite loop */
  while (1)
  {
  }
}
#endif