#include <stdio.h>
//#include <stdlib.h>
#include "pico/stdlib.h"
#include "pico/divider.h"
//#include <pico/platform.h>
#include "hardware/spi.h"
#include "hardware/dma.h"
#include "hardware/timer.h"
#include "hardware/clocks.h"
#include "hardware/adc.h"
#include "Scene3D/Scene3D.hpp"
#include "FixedPoint/FixedPoint.hpp"


#include "SSD1306Driver/SSD1306Driver.hpp"
#include "Button/Button.hpp"
#include <vector>


// <-- DMA tutorial
//   Data will be copied from src to dst
//const char src[] = "Hello, world! (from DMA)";
//char dst[count_of(src)];

// <-- alarm tutorial
//int64_t alarm_callback(alarm_id_t id, void *user_data) {
//    // Put your timeout handler code in here/
//    return 0;
//}

unsigned int counter = 8;

SSD1306Driver display;

Button button_1(10);
Button button_4(8);


int main()
{
    stdio_init_all();

    /* <-- DMA tutorial
    // Get a free channel, panic() if there are none
    int chan = dma_claim_unused_channel(true);
    
    // 8 bit transfers. Both read and write address increment after each
    // transfer (each pointing to a location in src or dst respectively).
    // No DREQ is selected, so the DMA transfers as fast as it can.
    
    dma_channel_config c = dma_channel_get_default_config(chan);
    channel_config_set_transfer_data_size(&c, DMA_SIZE_8);
    channel_config_set_read_increment(&c, true);
    channel_config_set_write_increment(&c, true);
    
    dma_channel_configure(
        chan,          // Channel to be configured
        &c,            // The configuration we just created
        dst,           // The initial write address
        src,           // The initial read address
        count_of(src), // Number of transfers; in this case each is 1 byte.
        true           // Start immediately.
    );
    
    // We could choose to go and do something else whilst the DMA is doing its
    // thing. In this case the processor has nothing else to do, so we just
    // wait for the DMA to finish.
    dma_channel_wait_for_finish_blocking(chan);
    
    // The DMA has now copied our text from the transmit buffer (src) to the
    // receive buffer (dst), so we can print it out from there.
    puts(dst);
    */

    // Timer example code - This example fires off the callback after 2000ms
    //add_alarm_in_ms(2000, alarm_callback, NULL, false);
    // For more examples of timer use see https://github.com/raspberrypi/pico-examples/tree/master/timer

    //printf("System Clock Frequency is %d Hz\n", clock_get_hz(clk_sys));
    //printf("USB Clock Frequency is %d Hz\n", clock_get_hz(clk_usb));
    // For more examples of clocks use see https://github.com/raspberrypi/pico-examples/tree/master/clocks

    button_1.begin();
    button_4.begin();

    display.begin();

    display.display();

    
    while(true)
    {

        display.clearDisplay();
        display.drawTriangleShaded(24, 18, 97, 14, 67, 49, counter % 17);
        display.display();
        
        sleep_ms(5);
    }
}
