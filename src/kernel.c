#include "common.h"
#include "mini_uart.h"

void kernel_main() {
    uart_init();
    uart_send_string("pepOS initialised.");

    while(1){
        uart_send(uart_recv()); //send back what the user types
        //uart_send(0); //send 1 to power the light
    }
}