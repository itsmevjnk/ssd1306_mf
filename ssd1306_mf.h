#ifndef SSD1306MF_H
#define SSD1306MF_H

#include "Arduino.h"

/* OLED display config */
#define SSD1306_WIDTH               128
#define SSD1306_HEIGHT              64
#define SSD1306_ADDRESS             0x3C

#define SSD1306_PAGE(y)                 (y / 8)
#define SSD1306_PAGE_OFFSET(y)          (y % 8)

#define SSD1306_TEXT_WIDTH              (SSD1306_WIDTH / 5)
#define SSD1306_TEXT_HEIGHT             (SSD1306_HEIGHT / 8)

class SSD1306: public Print {
public:
    uint8_t framebuffer[SSD1306_HEIGHT/8][SSD1306_WIDTH]; // framebuffer

    void command(uint8_t cmd);
    void command_n(const uint8_t* cmd, uint8_t len);
    void command_n_progmem(const uint8_t* cmd, uint8_t len);

    void init();

    void update();
    void fill(bool color = false);
    void SSD1306::fill_page(uint8_t page, bool color = false);
    void draw_pixel(uint8_t x, uint8_t y, bool color = true);
    bool get_pixel(uint8_t x, uint8_t y);

    uint8_t tty_x = 0, tty_y = 0; // teletype X/Y coordinates
    bool text_invert = false; // set to invert text color

    void print_char(uint8_t tx, uint8_t ty, uint8_t c, bool invert = false, bool set_range = true);

    size_t write(uint8_t c);
    size_t write(const uint8_t* buffer, size_t size);
private:
    uint16_t _update_start_x = 0, _update_start_page = 0, _update_w = 0, _update_h = 0; // framebuffer updating information

    void update_range_helper(uint8_t x, uint8_t y);
};

#endif