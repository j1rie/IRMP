/*---------------------------------------------------------------------------------------------------------------------------------------------------
 * irmp-main-rp2xxx.c - demo main module to test IRMP decoder on RP2xxx
 *
 * Copyright (c) 2023 Joerg Riechardt
 *
 * Copyright (c) 2009-2022 Frank Meyer - frank(at)fli4l.de
 *
 * This demo module is runnable on RP2xxx
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *---------------------------------------------------------------------------------------------------------------------------------------------------
 */

#include "irmp.h"

bool irmp_timer_callback(repeating_timer_t *rt);
repeating_timer_t irmp_timer;

void
timer_init (void)
{
	stdio_init_all();

	add_repeating_timer_us(-1000000 / F_INTERRUPTS, irmp_timer_callback, NULL, &irmp_timer);

	irmp_init();
}

bool
irmp_timer_callback(repeating_timer_t *rt)
{
  (void) irmp_ISR();                                                        // call irmp ISR
  // call other timer interrupt routines...
}

int
main (void)
{
    IRMP_DATA irmp_data;

    irmp_init();                                                            // initialize irmp
    timer_init();                                                           // initialize timer

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
