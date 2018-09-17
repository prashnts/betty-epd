#define __DELAY_C__

void delay(unsigned int time) // ~ 5+(1+1)*6+3 = 20 us
{
  while(time--);
}