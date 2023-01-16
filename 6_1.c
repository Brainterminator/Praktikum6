#include "bcm2835.h"

#define PIN RPI_BPLUS_GPIO_J8_12

int main(void)
{

    bcm2835_init();
    bcm2835_gpio_fsel(PIN, BCM2835_GPIO_FSEL_OUTP);



    while(1)
    {
        bcm2835_delay(1000);
        bcm2835_gpio_set(PIN);
        bcm2835_delay(1000);
        bcm2835_gpio_clr(PIN);
    }
    bcm2835_close();

    return 0;
}
