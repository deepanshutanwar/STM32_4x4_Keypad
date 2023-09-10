/**
 ******************************************************************************
 * @file           : main.c
 * @author         : Deepanshu Tanwar
 * @brief          : Main program body
 ******************************************************************************
 * @attention
 *
 * Copyright (c) 2023 STMicroelectronics.
 * All rights reserved.
 *
 * This software is licensed under terms that can be found in the LICENSE file
 * in the root directory of this software component.
 * If no LICENSE file comes with this software, it is provided AS-IS.
 *
 ******************************************************************************
 */

#include <stdio.h>
#include <stdint.h>

#if !defined(__SOFT_FP__) && defined(__ARM_FP)
  #warning "FPU is not initialized, but the project is compiling for an FPU. Please initialize the FPU before use."
#endif

void delay()
{
    for (uint32_t i = 0; i < 300000; i++);
}

int main(void)
{
    uint32_t volatile *const pClkCtrlReg = (uint32_t*)(0x40023800 + 0x30);
    uint32_t volatile *const pGpioModeReg = (uint32_t*)(0x40020C00);
    uint32_t volatile *const pGpioPushPullReg = (uint32_t*)(0x40020C00 + 0x0C);
    uint32_t volatile *const pGpioInputDataReg = (uint32_t*)(0x40020C00 + 0x10);
    uint32_t volatile *const pGpioOutputDataReg = (uint32_t*)(0x40020C00 + 0x14);

    printf("START\n");
    for (uint32_t i = 0; i < 10; i++) {
        printf("%d\n", i);
    }

    // 1. Enable the peripheral clock of GPIOD peripheral
    *pClkCtrlReg |= (1 << 3);

    // 2. Configure PD0, PD1, PD2, PD3 as output (rows)
    *pGpioModeReg &= ~(0xFF); // clear
    *pGpioModeReg |= 0x55;    // set

    // 3. Configure PD8, PD9, PD10, PD11 as input
    *pGpioModeReg &= ~(0xFF << 16); // clear

    // 4. Enable internal pull-up resistor for PD8, PD9, PD10, PD11
    *pGpioPushPullReg &= ~(0xFF << 16);
    *pGpioPushPullReg |= (0x55 << 16);

    while (1) {
        // Make all rows high
        *pGpioInputDataReg |= 0x0F;

        // Make R1 Low state (PD0)
        *pGpioOutputDataReg |= 0x00;

        // Scan the columns
        // Check C1 (PD8) low or high
        if (!(*pGpioInputDataReg & (1 << 8))) {
            delay();
            // Key is pressed
            printf("1\n");
        }

        if (!(*pGpioInputDataReg & (1 << 9))) {
            delay();
            // Key is pressed
            printf("2\n");
        }

        if (!(*pGpioInputDataReg & (1 << 10))) {
            // Key is pressed
            delay();
            printf("3\n");
        }

        if (!(*pGpioInputDataReg & (1 << 11))) {
            // Key is pressed
            delay();
            printf("A\n");
        }

        // Make all rows high and R2 low
        // Make all rows high
        *pGpioInputDataReg |= 0x0F;
        *pGpioOutputDataReg |= ~(1 << 1); // R2 is low

        // Scan the columns
        // Check C1 (PD8) low or high
        if (!(*pGpioInputDataReg & (1 << 8))) {
            delay();
            // Key is pressed
            printf("4\n");
        }

        if (!(*pGpioInputDataReg & (1 << 9))) {
            delay();
            // Key is pressed
            printf("5\n");
        }

        if (!(*pGpioInputDataReg & (1 << 10))) {
            // Key is pressed
            delay();
            printf("6\n");
        }

        if (!(*pGpioInputDataReg & (1 << 11))) {
            // Key is pressed
            delay();
            printf("B\n");
        }

        // Make all rows high and R3 low
        // Make all rows high
        *pGpioInputDataReg |= 0x0F;
        *pGpioOutputDataReg |= ~(1 << 2); // R3 is low

        // Scan the columns
        // Check C1 (PD8) low or high
        if (!(*pGpioInputDataReg & (1 << 8))) {
            delay();
            // Key is pressed
            printf("7\n");
        }

        if (!(*pGpioInputDataReg & (1 << 9))) {
            delay();
            // Key is pressed
            printf("8\n");
        }

        if (!(*pGpioInputDataReg & (1 << 10))) {
            // Key is pressed
            delay();
            printf("9\n");
        }

        if (!(*pGpioInputDataReg & (1 << 11))) {
            // Key is pressed
            delay();
            printf("C\n");
        }

        // Make all rows high and R4 low
        // Make all rows high
        *pGpioInputDataReg |= 0x0F;
        *pGpioOutputDataReg |= ~(1 << 3); // R4 is low

        // Scan the columns
        // Check C1 (PD8) low or high
        if (!(*pGpioInputDataReg & (1 << 8))) {
            delay();
            // Key is pressed
            printf("*\n");
        }

        if (!(*pGpioInputDataReg & (1 << 9))) {
            delay();
            // Key is pressed
            printf("0\n");
        }

        if (!(*pGpioInputDataReg & (1 << 10))) {
            // Key is pressed
            delay();
            printf("#\n");
        }

        if (!(*pGpioInputDataReg & (1 << 11))) {
            // Key is pressed
            delay();
            printf("D\n");
        }
    }
    // 5. Make all rows (output) high

    /* Loop forever */
}
