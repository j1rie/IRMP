/*---------------------------------------------------------------------------------------------------------------------------------------------------
 * irmp-main-opencm3.c - demo main module to test IRMP decoder on OPENCM3
 *
 * Copyright (c) 2009-2022 Frank Meyer - frank(at)fli4l.de
 *
 * This demo module is runnable on OPENCM3
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *---------------------------------------------------------------------------------------------------------------------------------------------------
 */

#include "irmp.h"

#ifndef F_CPU
#error F_CPU unknown
#endif

void
timer2_init (void)
{
	rcc_periph_clock_enable(RCC_TIM2);
	timer_set_mode(TIM2, TIM_CR1_CKD_CK_INT, TIM_CR1_CMS_EDGE, TIM_CR1_DIR_UP);
	timer_set_period(TIM2, 7);
	timer_set_prescaler(TIM2, ((F_CPU / F_INTERRUPTS)/8) - 1);

	timer_enable_irq(TIM2, TIM_DIER_UIE);

	nvic_enable_irq(NVIC_TIM2_IRQ);

	timer_enable_counter(TIM2);

	irmp_init();
}

void
tim2_isr(void)                                                              // Timer2 Interrupt Handler
{
  timer_clear_flag(TIM2, TIM_DIER_UIE);
  (void) irmp_ISR();                                                        // call irmp ISR
  // call other timer interrupt routines...
}

int
main (void)
{
    IRMP_DATA irmp_data;

    irmp_init();                                                            // initialize irmp
    timer2_init();                                                          // initialize timer2

    for (;;)
    {
        if (irmp_get_data (&irmp_data))
        {
            // ir signal decoded, do something here...
            // irmp_data.protocol is the protocol, see irmp.h
            // irmp_data.address is the address/manufacturer code of ir sender
            // irmp_data.command is the command code
            // irmp_protocol_names[irmp_data.protocol] is the protocol name (if enabled, see irmpconfig.h)
        }
    }
}
