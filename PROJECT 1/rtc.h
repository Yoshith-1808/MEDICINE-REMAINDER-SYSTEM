#include <stdint.h>
#ifndef RTC_H
#define RTC_H

#include <stdint.h>  // ? This solves the uint8_t issue

void rtc_init(void);
void rtc_get_time(uint8_t* h, uint8_t* m, uint8_t* s);
uint8_t decimal_to_bcd(uint8_t d);
uint8_t bcd_to_decimal(uint8_t b);
void i2c_start(void);
void i2c_stop(void);
void i2c_write(uint8_t data);
uint8_t i2c_read(uint8_t ack);

#endif
