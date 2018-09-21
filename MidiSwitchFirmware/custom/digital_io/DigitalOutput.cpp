/*
 * DigitalOutput.cpp
 *
 * Created: 8/25/2018 3:57:32 PM
 *  Author: Erwin
 */
#include "DigitalOutput.h"


DigitalOutput::DigitalOutput( GPIO_TypeDef* port, uint32_t pin, bool invert, bool initState):
    _port(port),
    _pin(pin),
    _inv(invert)
{
  bool portFound = true;
  GPIO_InitTypeDef GPIO_InitStructure = {0};

  // enable peripheral clock;
  if(_port == GPIOA){
      __HAL_RCC_GPIOA_CLK_ENABLE();
  }
  else if(_port == GPIOB){
      __HAL_RCC_GPIOB_CLK_ENABLE();
  }
  else if(_port == GPIOC){
      __HAL_RCC_GPIOC_CLK_ENABLE();
  }
  else if(_port == GPIOD){
      __HAL_RCC_GPIOD_CLK_ENABLE();
  }
  else if(_port == GPIOE){
      __HAL_RCC_GPIOE_CLK_ENABLE();
  }
  else if(_port == GPIOF){
      __HAL_RCC_GPIOF_CLK_ENABLE();
  }
  else if(_port == GPIOG){
      __HAL_RCC_GPIOG_CLK_ENABLE();
  }
  else if(_port == GPIOH){
      __HAL_RCC_GPIOH_CLK_ENABLE();
  }
  else if(_port == GPIOI){
      __HAL_RCC_GPIOI_CLK_ENABLE();
  }
  else if(_port == GPIOJ){
      __HAL_RCC_GPIOJ_CLK_ENABLE();
  }
  else if(_port == GPIOK){
      __HAL_RCC_GPIOK_CLK_ENABLE();
  }
  else
  {
      portFound = false;
  }
  
  if(portFound == true)
  {
    GPIO_InitStructure.Pin      = _pin;
    GPIO_InitStructure.Mode     = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStructure.Speed    = GPIO_SPEED_FREQ_VERY_HIGH;
    GPIO_InitStructure.Pull     = GPIO_NOPULL;
    HAL_GPIO_Init(_port, &GPIO_InitStructure);
    set(initState);
  }
}


DigitalOutput::~DigitalOutput()
{
  GPIO_InitTypeDef GPIO_InitStructure;
  GPIO_InitStructure.Pin   = _pin;
  GPIO_InitStructure.Mode  = GPIO_MODE_INPUT;
  GPIO_InitStructure.Speed = GPIO_SPEED_FREQ_MEDIUM;
  GPIO_InitStructure.Pull  = GPIO_NOPULL;
  
  HAL_GPIO_Init(_port, &GPIO_InitStructure);
}


void DigitalOutput::set()
{
    GPIO_PinState setState;
    (_inv == true)?(setState = GPIO_PIN_RESET):(setState = GPIO_PIN_SET);
    HAL_GPIO_WritePin(_port, _pin, setState);
}


void DigitalOutput::set(bool state)
{
    GPIO_PinState setState;
    if(state == true)
    {
        (_inv == true)?(setState = GPIO_PIN_RESET):(setState = GPIO_PIN_SET);
    }
    else
    {
        (_inv == true)?(setState = GPIO_PIN_SET):(setState = GPIO_PIN_RESET);
    }
    HAL_GPIO_WritePin(_port, _pin, setState);
}


void DigitalOutput::clear()
{
    GPIO_PinState setState;
    (_inv == true)?(setState = GPIO_PIN_SET):(setState = GPIO_PIN_RESET);
    HAL_GPIO_WritePin(_port, _pin, setState);
}


void DigitalOutput::toggle()
{
    HAL_GPIO_TogglePin(_port, _pin);
}


bool DigitalOutput::read()
{
    bool readState;
    if(HAL_GPIO_ReadPin(_port, _pin) == GPIO_PIN_SET)
    {
        (_inv == true)?(readState = false):(readState = true);
    }
    else
    {
        (_inv == true)?(readState = true):(readState = false);
    }
}


void DigitalOutput::setInversion(bool invert)
{
    _inv = invert;
}


bool DigitalOutput::getInversion()
{
    return _inv;
}
