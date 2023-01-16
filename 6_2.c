// *********************************************************************
// A5_lm75.c									Version 05.01.2021_S hpw
// Frostwarner
// Dokumentation bcm2835:
// https://www.airspayce.com/mikem/bcm2835/index.html
// *********************************************************************
#include <stdio.h>						    // Header fuer Ein-/Ausgaben
#include "bcm2835.h"					    // Header fuer Broadcom

#define		PIN				RPI_BPLUS_GPIO_J8_12						// LED-Pin
#define		I2C_ADR			0x48										// Adresse LM75

int main(void){
    if(!bcm2835_init()) return 1;										// Library initalisieren

    // Pin als output einstellen
    bcm2835_gpio_fsel(PIN, BCM2835_GPIO_FSEL_OUTP);
    // I2C initalisieren
    if(!bcm2835_i2c_begin())return 1;
    // I2C Adresse einstellen
    bcm2835_i2c_setSlaveAddress(I2C_ADR);
    // I2C Mode einstellen
    bcm2835_i2c_setClockDivider(BCM2835_SPI_CLOCK_DIVIDER_1);
    // In Schleife
    for (int i = 0; i < 10; ++i) {
        // Daten lesen und ausgeben
        char a[2]={0};
        bcm2835_i2c_read(a,2);

        int dezimalwert;

        if (a[0]>>7==1){
            dezimalwert=(((~a[0])<<8)|(~a[1]))>>5;
            dezimalwert++;
            dezimalwert=-dezimalwert;
        } else {
            dezimalwert=((a[0]<<8)|a[1])>>5;
        }



        float temperatur=(float)dezimalwert*0.125;

        printf("%.3f °C\n",temperatur);


        // LED an- bzw. ausschalten
        if(temperatur<0)bcm2835_gpio_set(PIN);
        else bcm2835_gpio_clr(PIN);
        // Pause
        bcm2835_delay(1000);

    }


    // I2C-Pins auf Standard
    bcm2835_gpio_clr(PIN);
    if(bcm2835_close()==0) return 1;									// Library schließen
    return 0;								// Programmende
}
