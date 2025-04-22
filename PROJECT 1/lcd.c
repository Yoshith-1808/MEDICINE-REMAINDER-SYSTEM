#include <lpc214x.h>
#include "lcd.h"
#include <stdint.h>   // For uint8_t
#include <stdio.h>    // For sprintf


#define RS (1<<8)
#define EN (1<<9)
#define LCD IO0SET
#define LCDCLR IO0CLR

void lcd_delay() {
    unsigned int i;
    for(i=0;i<1000;i++);
}

void lcd_cmd(unsigned char cmd) {
    IO0CLR = 0xFF << 16;
    IO0SET = (cmd & 0xF0) << 16;
    IO0CLR = RS;
    IO0SET = EN;
    lcd_delay();
    IO0CLR = EN;

    IO0CLR = 0xFF << 16;
    IO0SET = ((cmd & 0x0F) << 4) << 16;
    IO0CLR = RS;
    IO0SET = EN;
    lcd_delay();
    IO0CLR = EN;
}

void lcd_data(unsigned char data) {
    IO0CLR = 0xFF << 16;
    IO0SET = (data & 0xF0) << 16;
    IO0SET = RS;
    IO0SET = EN;
    lcd_delay();
    IO0CLR = EN;

    IO0CLR = 0xFF << 16;
    IO0SET = ((data & 0x0F) << 4) << 16;
    IO0SET = RS;
    IO0SET = EN;
    lcd_delay();
    IO0CLR = EN;
}

void lcd_init() {
    IO0DIR |= 0xFF << 16 | RS | EN;
    lcd_cmd(0x02);
    lcd_cmd(0x28);
    lcd_cmd(0x0C);
    lcd_cmd(0x06);
    lcd_cmd(0x01);
}

void lcd_print(const char *str) {
    while(*str)
        lcd_data(*str++);
}

void lcd_time_display(uint8_t h, uint8_t m, uint8_t s) {
    char buf[17];
    sprintf(buf, "%02d:%02d:%02d", h, m, s);
    lcd_print(buf);
}
