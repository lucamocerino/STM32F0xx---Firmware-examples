/**
  ******************************************************************************
  * @file    PWR_CurrentConsumption/main.c
  * @author  MCD Application Team
  * @version V1.0.0
  * @date    23-March-2012
  * @brief   Main program body
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT 2012 STMicroelectronics</center></h2>
  *
  * Licensed under MCD-ST Liberty SW License Agreement V2, (the "License");
  * You may not use this file except in compliance with the License.
  * You may obtain a copy of the License at:
  *
  *        http://www.st.com/software_license_agreement_liberty_v2
  *
  * Unless required by applicable law or agreed to in writing, software
  * distributed under the License is distributed on an "AS IS" BASIS,
  * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  * See the License for the specific language governing permissions and
  * limitations under the License.
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "stm32f0_discovery.h"
#include "stm32f0xx_lp_modes.h"

/** @addtogroup STM32F0_Discovery_Peripheral_Examples
  * @{
  */

/** @addtogroup PWR_CurrentConsumption
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
__IO uint32_t i = 0;
static __IO uint32_t TimingDelay; //for delay
int j=0;
uint8_t BlinkSpeed = 0;
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/



void Delay(__IO uint32_t nTime) //time in ms
{
  TimingDelay = nTime;

  while(TimingDelay != 0);
}

void TimingDelay_Decrement(void)
{
  if (TimingDelay != 0x00)
  {
    TimingDelay--;
  }
}


/**
  * @brief  Main program
  * @param  None
  * @retval None
  */
int main(void)
{

  /*!< At this stage the microcontroller clock setting is already configured,
    this is done through SystemInit() function which is called from startup
    file (startup_stm32f0xx.s) before to branch to application main.
    To reconfigure the default setting of SystemInit() function, refer to
    system_stm32f0xx.c file
    */
    /* Configure User Button */
    STM_EVAL_PBInit(BUTTON_USER,BUTTON_MODE_GPIO); //Wake up Sleep Mode

	 /* Initialize LED3 on STM32F0-Discovery board */
		STM_EVAL_LEDInit(LED3);
		STM_EVAL_LEDInit(LED4);



    /* Enable PWR APB1 Clock */
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_PWR, ENABLE);

    /* Allow access to Backup */   //Start
    PWR_BackupAccessCmd(ENABLE);		//The application can write or read data to and from these registers.
																		//They are powered-on by VBAT when VDD is switched off, so that they are not reset by
																		//System reset, and their contents remain valid when the device operates in low-power mode.

    /* Reset RTC Domain */
    RCC_BackupResetCmd(ENABLE);
    RCC_BackupResetCmd(DISABLE);		//END

				//Turn on the blue led, and waiting for push button
				STM_EVAL_LEDOn(LED4);
				while (STM_EVAL_PBGetState(BUTTON_USER) != SET){}
				STM_EVAL_LEDOff(LED4);
			  StopMode_Measure();//STOP MODE
				//exit from stop mode after a while using RTC(5 s in this case)

				//Initialize again peripheral that have been turned off in StopMode
				STM_EVAL_LEDInit(LED3);
				STM_EVAL_LEDInit(LED4);
				STM_EVAL_PBInit(BUTTON_USER,BUTTON_MODE_GPIO);

				STM_EVAL_LEDOn(LED3);
				while (STM_EVAL_PBGetState(BUTTON_USER) != SET){}
				STM_EVAL_LEDOff(LED3);
				while (STM_EVAL_PBGetState(BUTTON_USER) == SET){}


				SleepMode_Measure(); //SLEEP MODE
				//Wakeup using EXTI Line (User Button PA.00)

				//Initialize again peripheral that have been turned off in StopMode
				STM_EVAL_LEDInit(LED3);
				STM_EVAL_LEDInit(LED4);
				STM_EVAL_PBInit(BUTTON_USER,BUTTON_MODE_GPIO);

				STM_EVAL_LEDOn(LED4);
				while (STM_EVAL_PBGetState(BUTTON_USER) != SET){}
				STM_EVAL_LEDOff(LED4);
				StandbyRTCMode_Measure(); //STANDYBY MODE
				//exit from stop mode after a while using RTC(5 s in this case)
				//reset and start from the beginning of programm


}

#ifdef  USE_FULL_ASSERT

/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t* file, uint32_t line)
{
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */

  /* Infinite loop */
  while (1)
  {
  }
}
#endif

/**
  * @}
  */

/**
  * @}
  */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
