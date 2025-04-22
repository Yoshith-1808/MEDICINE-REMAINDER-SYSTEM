#include <lpc214x.h>
#include "rtc.h"

unsigned char decimal_to_bcd(unsigned char d) {
    return ((d / 10) << 4) | (d % 10);
}

unsigned char bcd_to_decimal(unsigned char b) {
    return ((b >> 4) * 10 + (b & 0x0F));
}

void rtc_init() {
    I2C0CONCLR = 0x6C;
    I2C0CONSET = 0x40;
    I2C0SCLH = 60;
    I2C0SCLL = 60;
}

void i2c_start() {
    I2C0CONSET = 0x20;
    while (!(I2C0CONSET & 0x08));
}

void i2c_stop() {
    I2C0CONSET = 0x10;
    I2C0CONCLR = 0x20;
}

void i2c_write(unsigned char data) {
    I2C0DAT = data;
    I2C0CONCLR = 0x08;
    while (!(I2C0CONSET & 0x08));
}

unsigned char i2c_read(unsigned char ack) {
    if (ack)
        I2C0CONSET = 0x04;
    else
        I2C0CONCLR = 0x04;

    I2C0CONCLR = 0x08;
    while (!(I2C0CONSET & 0x08));
    return I2C0DAT;
}

void rtc_get_time(uint8_t* h, uint8_t* m, uint8_t* s) {
    i2c_start();
    i2c_write(0xD0);
    i2c_write(0x00);
    i2c_start();
    i2c_write(0xD1);

    *s = bcd_to_decimal(i2c_read(1));
    *m = bcd_to_decimal(i2c_read(1));
    *h = bcd_to_decimal(i2c_read(0));

    i2c_stop();
}
