#ifndef SSD1306_DRIVER

#define SSD1306_DRIVER

#ifndef GAME_CONSOLE_GFX
    #include "GameConsoleGFX/GameConsoleGFX.hpp"
#endif

#ifndef _PICO_PLATFORM_H
    #include <pico/platform.h>
#endif

#ifndef _HARDWARE_SPI_H
    #include <hardware/spi.h>
#endif

#define MOSI_PIN 3
#define SCLK_PIN 2
#define CS_PIN 5
#define DC_PIN 4
#define RESET_PIN 6

class SSD1306Driver : public GameConsoleGFX
{
    public:
        SSD1306Driver() : GameConsoleGFX()
        {
        }

        bool begin(bool init_gpios = true)
        {
            if(init_gpios)
            {
                (void)spi_init(spi0, 1000000);
                gpio_set_function(CS_PIN, GPIO_FUNC_SPI);
                gpio_set_function(SCLK_PIN, GPIO_FUNC_SPI);
                gpio_set_function(MOSI_PIN, GPIO_FUNC_SPI);
                gpio_init(DC_PIN);
                gpio_init(RESET_PIN);
                gpio_set_dir(DC_PIN, GPIO_OUT);
                gpio_set_dir(RESET_PIN, GPIO_OUT);
                gpio_put(DC_PIN, false);
                gpio_put(RESET_PIN, true);
                gpio_put(RESET_PIN, false);
                sleep_ms(10);
                gpio_put(RESET_PIN, true);
            }

            
            int written_bytes = spi_write_blocking(spi0, display_init_sequence, 26);
            if(written_bytes != 26)
            {
                panic("Initialization of display failed; did not send the right amount of bytes.");
                return false;
            }
                
            return true;
        }

        void fill_buffer(unsigned char content)
        {
            for(unsigned int i = 0; i < 1024; i++)
                buffer[i] = content;
        }

        bool send_command(unsigned char command)
        {
            gpio_put(DC_PIN, false);
            int written_bytes = spi_write_blocking(spi0, &command, 1);
            if(written_bytes != 1)
            {
                panic("Command tranfer failed; did not send the right amount of bytes.");
                return false;
            }
            return true;
        }

        bool display()
        {
            gpio_put(DC_PIN, true);
            int written_bytes = spi_write_blocking(spi0, buffer, 1024);
            if(written_bytes != 1024)
            {
                panic("Transfer of frame failed; did not send the right amount of bytes.");
                return false;
            }
            return true;
        }
    
    private:
        
        const unsigned char display_init_sequence[26] = {
            0xAE,       // Display off
            0xD5, 0x80, // Display Clock Div
            0xA8, 0x3F, // Multiplex
            0xD3, 0x00, // Display offset
            0x40,       // Display start line -- line #0
            0x8D, 0x14, // Enable charge pump
            0x20, 0x00, // Horizontal addressing mode
            0xA1,       // Segment remap -- 0xA0 - column 0 -> SEG0 / 0xA1 - column 127 -> SEG0
            0xC8,       // COM Output scan direction
            0xDA, 0x12, // COM pins
            0x81, 0xCF, // Contrast
            0xD9, 0xF1, // Pre-charge period
            0xDB, 0x40, // VCOMH Deselect Level -- idk datasheet only has 0x10, 0x20, 0x30
            0xA4,       // Display uses RAM content
            0xA6,       // Normal display (0 in RAM is OFF pixel)
            0x2E,       // Deactivate scroll
            0xAF        // Display on as f*ck
        };

        //const static unsigned char zero_byte = 0;

};

#endif