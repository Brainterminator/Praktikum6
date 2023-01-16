// *********************************************************************
// A6_pwm.c										Version 05.01.2021_S hpw
// LED-Dimmer
// Dokumentation bcm2835:
// https://www.airspayce.com/mikem/bcm2835/index.html
// *********************************************************************

#include <stdio.h>						    // Header fuer Ein-/Ausgaben
#include "bcm2835.h"					    // Header fuer Broadcom

#define	PIN				RPI_BPLUS_GPIO_J8_12							// PWM-Pin
#define	PWM_CHANNEL		0												// PWM-Channel
#define	PWM_RANGE		1024											// PWM-Range
#define SPEED			1												// Geschwindigkeit

int main(void){
    if(bcm2835_init()==0) return 1;										// Library initalisieren

    // PWM Funktionalität an Pin freischalten
    bcm2835_gpio_fsel(PIN,BCM2835_GPIO_FSEL_ALT5);
    // PWM Frequenz einstellen
    bcm2835_pwm_set_clock(BCM2835_PWM_CLOCK_DIVIDER_1024);
    // PWM Modus einstellen und starten
    bcm2835_pwm_set_mode(PWM_CHANNEL,1,1);
    // PWM Range einstellen
    bcm2835_pwm_set_range(PWM_CHANNEL,PWM_RANGE);
    // In Schleife
    while(1){
        for (unsigned int i = 0; i < 1000; ++i) {
            bcm2835_pwm_set_data(PWM_CHANNEL, i);
            delay(SPEED);
        }
        for (unsigned int i = 1000; i>0; --i) {
            bcm2835_pwm_set_data(PWM_CHANNEL, i);
            delay(SPEED);
        }
    }
    if(bcm2835_close()==0) return 1;									// Library schließen
    return 0;								// Programmende
}
