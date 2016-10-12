#include <stddef.h>
#include "stm32l1xx.h"

int i,j;

void adc_init(void)			// inicalizujem ADC a GPIO
  {
  	GPIO_InitTypeDef GPIO_InitStructure;
  	ADC_InitTypeDef ADC_InitStructure;

  	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA, ENABLE);
  	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1 ;
  	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AN;
  	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL ;
  	// LEDka//
  	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5 ;
  	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
  	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
  	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_40MHz;
  	////
  	GPIO_Init(GPIOA, &GPIO_InitStructure);
  	RCC_HSICmd(ENABLE);
  	while(RCC_GetFlagStatus(RCC_FLAG_HSIRDY) == RESET);
  	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE);
  	ADC_StructInit(&ADC_InitStructure);
  	ADC_InitStructure.ADC_Resolution = ADC_Resolution_12b;
  	ADC_InitStructure.ADC_ContinuousConvMode = DISABLE;
  	ADC_InitStructure.ADC_ExternalTrigConvEdge = ADC_ExternalTrigConvEdge_None;
  	ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;
  	ADC_InitStructure.ADC_NbrOfConversion = 1;
  	ADC_Init(ADC1, &ADC_InitStructure);
  	ADC_RegularChannelConfig(ADC1, ADC_Channel_1, 1, ADC_SampleTime_16Cycles);
  	ADC_Cmd(ADC1, ENABLE);
  	while(ADC_GetFlagStatus(ADC1, ADC_FLAG_ADONS) == RESET){}
  	ADC_SoftwareStartConv(ADC1);
  }

void blikamLEDku(int tlacitko){
	if (tlacitko == 0){
		GPIO_ResetBits(GPIOA, GPIO_Pin_5);
	}
	else if (tlacitko == 1){
		GPIO_ToggleBits(GPIOA, GPIO_Pin_5);
		for (i = 1; i <= 200; i++){
			for (j = 1; j <= 200; j++){
				}
		}
	}
	else if (tlacitko == 2){
		GPIO_ToggleBits(GPIOA, GPIO_Pin_5);
		for (i = 1; i <= 400; i++){
			for (j = 1; j <= 400; j++){
				}
		}
	}
	else if (tlacitko == 3){
		GPIO_ToggleBits(GPIOA, GPIO_Pin_5);
		for (i = 1; i <= 700; i++){
			for (j = 1; j <= 700; j++){
				}
		}
	}
	else if (tlacitko == 4){
		GPIO_ToggleBits(GPIOA, GPIO_Pin_5);
		for (i = 1; i <= 1000; i++){
			for (j = 1; j <= 1000; j++){
				}
		}
	}
}

int main(void)
{
	uint16_t AD_value;
	adc_init();
	while (1){
		ADC_SoftwareStartConv(ADC1);
		while(!ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC)){}
		AD_value=ADC_GetConversionValue(ADC1);

		if ((AD_value >= 1980) && (AD_value <= 2100)){
			blikamLEDku(1);
 	 	}
		else if ((AD_value >= 2800) && (AD_value <= 2940)){
			blikamLEDku(2);
 	 	}
		else if ((AD_value >= 3440) && (AD_value <= 3480)){
			blikamLEDku(3);
 	 	}
		else if ((AD_value >= 3640) && (AD_value <= 3680)){
			blikamLEDku(4);
 	 	}
		else if ((AD_value >= 3900)){
			blikamLEDku(0);
		}
	}
  return 0;
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *   where the assert_param error has occurred.
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

/*
 * Minimal __assert_func used by the assert() macro
 * */
void __assert_func(const char *file, int line, const char *func, const char *failedexpr)
{
  while(1)
  {}
}

/*
 * Minimal __assert() uses __assert__func()
 * */
void __assert(const char *file, int line, const char *failedexpr)
{
   __assert_func (file, line, NULL, failedexpr);
}
