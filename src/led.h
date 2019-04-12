
#ifndef _LED_H
#define _LED_H



void Led_Init(void);
void Beep_Init(void);

#define LED1 PFout(7)
#define LED2 PBout(5)
#define LED3 PAout(8)
#define LED4 PAout(1)

#define BEEP PBout(8)

#endif
