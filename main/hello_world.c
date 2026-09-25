#include <stdio.h>
#include <string.h>

#include "driver/gpio.h"
#include "driver/uart.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#define LED_PIN 4
#define UART_PORT UART_NUM_0
#define UART_RX_BUFFER_SIZE 1024
#define COMMAND_SIZE 128

static int led_state = 0;

void led_init(void)
{
    gpio_set_direction(LED_PIN, GPIO_MODE_OUTPUT);
    gpio_set_level(LED_PIN, 0);

    led_state = 0;
}

void uart_init(void)
{
    uart_config_t uart_config = {
        .baud_rate = 115200,
        .data_bits = UART_DATA_8_BITS,
        .parity = UART_PARITY_DISABLE,
        .stop_bits = UART_STOP_BITS_1,
        .flow_ctrl = UART_HW_FLOWCTRL_DISABLE,
    };

    uart_param_config(UART_PORT, &uart_config);

    uart_driver_install(
        UART_PORT,
        UART_RX_BUFFER_SIZE,
        0,
        0,
        NULL,
        0
    );
}

void process_command(char *command)
{
    if (strcmp(command, "LED ON") == 0)
    {
        gpio_set_level(LED_PIN, 1);
        led_state = 1;

        printf("LED turned ON.\n");
    }
    else if (strcmp(command, "LED OFF") == 0)
    {
        gpio_set_level(LED_PIN, 0);
        led_state = 0;

        printf("LED turned OFF.\n");
    }
    else if (strcmp(command, "STATUS") == 0)
    {
        if (led_state)
        {
            printf("LED status: ON\n");
        }
        else
        {
            printf("LED status: OFF\n");
        }
    }
    else if (strcmp(command, "HELP") == 0)
    {
        printf("Available commands:\n");
        printf("LED ON\n");
        printf("LED OFF\n");
        printf("STATUS\n");
        printf("HELP\n");
    }
    else if (strlen(command) > 0)
    {
        printf("Unknown command.\n");
    }
}

void app_main(void)
{
    uint8_t data[128];
    char command[COMMAND_SIZE];
    int index = 0;

    led_init();
    uart_init();

    printf("UART LED Controller started.\n");
    printf("Type HELP to see available commands.\n");

    while (1)
    {
        int len = uart_read_bytes(
            UART_PORT,
            data,
            sizeof(data),
            pdMS_TO_TICKS(100)
        );

        if (len > 0)
        {
            for (int i = 0; i < len; i++)
            {
                if (data[i] == '\r' || data[i] == '\n')
                {
                    command[index] = '\0';

                    process_command(command);

                    index = 0;
                }
                else
                {
                    if (index < COMMAND_SIZE - 1)
                    {
                        command[index] = data[i];
                        index++;
                    }
                }
            }
        }
    }
}