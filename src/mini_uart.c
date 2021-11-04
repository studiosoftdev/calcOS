#include "gpio.h"
#include "utils.h"
#include "peripherals/aux.h"
#include "mini_uart.h"

#define TXD 14 //pins on the baord
#define RXD 15

void uart_init(){
    gpio_pin_set_func(TXD, GFAlt5); //alt5 for these pins are to use muart
    gpio_pin_set_func(RXD, GFAlt5);

    gpio_pin_enable(TXD);
    gpio_pin_enable(RXD);

    REGS_AUX->enables = 1; //set first bit, enables muart
    REGS_AUX->mu_control = 0;
    REGS_AUX->mu_ier = 0;
    REGS_AUX->mu_lcr = 3; //sets 8 bit mode
    REGS_AUX->mu_mcr = 0;
    REGS_AUX->mu_baud_rate = 270; //270 baud rate thus = 115200 @ 250MHz, page 11 of BCM8235 ARM Peripherals doc
    REGS_AUX->mu_control = 3;

    uart_send('\r');
    uart_send('\n');
    uart_send('\n');
}

void uart_send(char c){
    while(!(REGS_AUX->mu_lsr & 0x20)); //bit 5 of mu_lsr tells us whether muart is accepting at least 1 byte, so while it is not set, wait until it is

    REGS_AUX->mu_io = c;
}

char uart_recv(){
    while(!(REGS_AUX->mu_lsr & 1)); //bit 0 of mu_lsr tells us whether muart is holding at least 1 symbol, so while it is not set, wait until it is

    return REGS_AUX->mu_io & 0xFF; //extract 1 char, mu_io is a reg32 so need to and with FF
}

void uart_send_string(char *str) {
    while(*str){ //while dereferenced value is not a null terminator
        if(*str == '\n'){
            uart_send('\r');
        }
        uart_send(*str);
        str++;
    }
}