#ifndef LCD_H
#define LCD_H

void lcd_cmd(unsigned char cmd);
void lcd_data(unsigned char data);
void lcd_init(void);
void lcd_print(const char *str);
void lcd_time_display(unsigned char h, unsigned char m, unsigned char s);

#endif
