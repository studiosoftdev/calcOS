#pragma once

#include "common.h"

#include "peripherals/base.h"

struct GpioPinData {
    reg32 reserved;
    reg32 data[2];
};

struct GpioRegs{ //registers from 0x7E200000 (page 90, BCM2835 ARM Peripherals doc))
    reg32 func_select[6]; //all the function select registers
    struct GpioPinData output_set;
    struct GpioPinData output_clear;
    struct GpioPinData level;
    struct GpioPinData ev_detect_status;
    struct GpioPinData re_detect_enable;
    struct GpioPinData fe_detect_enable;
    struct GpioPinData hi_detect_enable;
    struct GpioPinData lo_detect_enable;
    struct GpioPinData async_re_detect;
    struct GpioPinData async_fe_detect;
    reg32 reserved;
    reg32 pupd_enable;
    reg32 pupd_enable_clocks[2];
};

#define REGS_GPIO ((struct GpioRegs *)(PBASE+0x00200000))