#include <lpc214x.h>
#include "lcd.h"
#include "rtc.h"

#define BUZZER (1<<10)

void delay_ms(unsigned int ms) {
    unsigned int i,j;
    for(i=0;i<ms;i++)
        for(j=0;j<6000;j++);
}

void buzzer_on() {
    IO0SET = BUZZER;
}

void buzzer_off() {
    IO0CLR = BUZZER;
}

void check_medicine(uint8_t hour, uint8_t min) {
    lcd_cmd(0x01);
    if ((hour == 8 && min == 0)) {
        lcd_print("Take: Med A");
        buzzer_on(); delay_ms(3000); buzzer_off();
    }
    else if ((hour == 14 && min == 0)) {
        lcd_print("Take: Med B");
        buzzer_on(); delay_ms(3000); buzzer_off();
    }
    else if ((hour == 20 && min == 0)) {
        lcd_print("Take: Med C");
        buzzer_on(); delay_ms(3000); buzzer_off();
    } else {
        lcd_print("No medicine now");
    }
}

int main() {
    uint8_t hour, min, sec;

    IO0DIR |= BUZZER; // Buzzer pin as output
    lcd_init();
    rtc_init();

    lcd_print("Medicine Reminder");
    delay_ms(2000);
    lcd_cmd(0x01);

    while (1) {
        rtc_get_time(&hour, &min, &sec);

        lcd_cmd(0x80);
        lcd_print("Time: ");
        lcd_time_display(hour, min, sec);

        check_medicine(hour, min);
        delay_ms(60000); // Check once per minute
    }
}
