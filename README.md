# ESP32 UART LED Controller

A simple embedded systems project using an ESP32 and ESP-IDF.

The project allows the user to control an LED through commands sent over UART from a serial terminal.

## Features

* UART communication at 115200 baud
* Command-based control
* LED ON/OFF control
* LED status checking
* Help command
* Basic command parsing
* GPIO control using ESP-IDF

## Commands

| Command   | Description                 |
| --------- | --------------------------- |
| `LED ON`  | Turns the LED on            |
| `LED OFF` | Turns the LED off           |
| `STATUS`  | Shows the current LED state |
| `HELP`    | Shows available commands    |

## Hardware

* ESP32 development board
* LED
* 330Ω resistor
* Breadboard
* Jumper wires

## Circuit

The LED is connected to GPIO 4 through a 330Ω resistor.

```text
ESP32 GPIO4
     │
     │
  330Ω resistor
     │
     │
    LED
     │
     │
   GND
```

## Software

* Language: C
* Framework: ESP-IDF
* ESP-IDF Version: 6.1
* Baud Rate: 115200
* UART: UART0
* LED GPIO: GPIO4

## How It Works

The ESP32 continuously checks the UART interface for incoming data.

Characters received from the serial terminal are stored in a command buffer. When the user presses Enter, the received command is processed.

The command is then compared with the available commands and the corresponding action is performed.

```text
PC Terminal
     │
     │ UART
     ▼
ESP32 UART
     │
     ▼
Command Buffer
     │
     ▼
Command Parser
     │
     ├── LED ON  ──► GPIO4 HIGH
     │
     ├── LED OFF ──► GPIO4 LOW
     │
     ├── STATUS  ──► Show LED state
     │
     └── HELP    ──► Show commands
```

## Build and Flash

Make sure ESP-IDF is installed and the ESP-IDF environment is activated.

Build the project:

```bash
idf.py build
```

Flash the ESP32:

```bash
idf.py -p COM3 flash
```

Open the serial monitor:

```bash
idf.py -p COM3 monitor
```

The default baud rate is 115200.

## Example

```text
UART LED Controller started.
Type HELP to see available commands.

LED ON
LED turned ON.

STATUS
LED status: ON

LED OFF
LED turned OFF.
```

## What I Learned

This project was built to practice basic embedded software concepts, including:

* UART communication
* GPIO control
* UART driver configuration
* Buffer management
* Command parsing
* C strings and `strcmp()`
* ESP-IDF development
* Working with an ESP32 development board

## Future Improvements

Possible improvements for the project:

* Add more GPIO-controlled devices
* Add configurable LED pins
* Improve command parsing
* Add error handling
* Add multiple device commands
* Add UART command history
