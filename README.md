# AVR-ATmega-328p

```
                          ATmega328p
                          +---------+
(PCINT14/RESET)      PC6 /|1  \_/ 28|\ PC5 (ADC5/SCL/PCINT13)
(PCINT16/RXD)        PD0 /|2      27|\ PC4 (ADC4/SDA/PCINT12)
(PCINT17/TXD)        PD1 /|3      26|\ PC3 (ADC3/PCINT11)
(PCINT18/INT0)       PD2 /|4      25|\ PC2 (ADC2/PCINT10)
(PCINT19/OC2B/INT1)  PD3 /|5      24|\ PC1 (ADC1/PCINT9)
(PCINT20/XCK/T0)     PD4 /|6      23|\ PC0 (ADC0/PCINT8)
VCC                      /|7      22|\     GND
GND                      /|8      21|\     AREF
(PCINT6/XTAL1/TOSC1) PB6 /|9      20|\     AVCC
(PCINT7/XTAL2/TOSC2) PB7 /|10     19|\ PB5 (SCK/PCINT5)
(PCINT21/OC0B/T1)    PD5 /|11     18|\ PB4 (MISO/PCINT4)
(PCINT22/OC0A/AIN0)  PD6 /|12     17|\ PB3 (MOSI/OC2A/PCINT3)
(PCINT23/AIN1)       PD7 /|13     16|\ PB2 (SS/OC1B/PCINT2)
(PCINT0/CLKO/ICP1)   PB0 /|14     15|\ PB1 (OC1A/PCINT1)
                          +---------+
```

# AVR – ATmega328P Complete Bare-Metal Programming Collection

This repository is a full collection of **register-level AVR programs**, written for the **ATmega328P** microcontroller.  
Every folder is a self-contained example demonstrating one concept, peripheral, or driver written completely from scratch.

The purpose of this repo is to serve as a **learning reference**, **practical guide**, and **mini-library** for bare-metal AVR programming.

---

## 🚀 Highlights

- 25+ fully working AVR examples  
- All programs use **direct register access**  
- Covers **GPIO, Timers, PWM, Interrupts, UART, SPI, ADC, Sensors, Motors, LCD**  
- Demonstrates **custom driver development** (LCD, LED driver, BM280, LM35, etc.)  
- Beginner-friendly code structure with clear organization  
- Perfect for students, hobbyists, and embedded learners  

---

## 📂 Project Index (All Folders)

Below is a complete curated list of all examples included in this repository:

### **🔌 Digital I/O, Switches, LEDs**
| Folder | Description |
|-------|-------------|
| `ACTIVE_HIGH_SWITCH` | Pull-down resistor concept with active-high switch input |
| `ACTIVE_LOW_SWITCH` | Pull-up resistor concept with active-low switch input |
| `BLINK_5LED_USING_HEADER_FILE` | Custom driver for blinking 5 LEDs via a header file |
| `BLINK_TWO_LED_HW` | Alternate blinking two LEDs using direct register control |
| `PD3_BLINK_LED` | LED blinking using bitwise operations on PD3 |
| `LED_BLINK_PRESCALAR_1024` | LED blink using Timer0 with 1024 prescaler |

---

### **⏱️ Timers, Delay, PWM, Interrupts**
| Folder | Description |
|-------|-------------|
| `DELAY_TIMER_FUNC` | Delay function using Timer registers |
| `FAST_PWM_TIMER` | Fast PWM using Timer with prescaler 64 |
| `FADING_LED_PWM` | LED fading using PWM duty cycle variation |
| `TIMERO_OVERFLOW_INTERRUPT` | Timer0 overflow interrupt LED example |
| `EXT_INTRRUPT` | External interrupt (INT0) register-level demonstration |

---

### **🛠️ Sensors & ADC**
| Folder | Description |
|-------|-------------|
| `ADC` | Analog to Digital Converter example |
| `LM35_TEMPERATURE_SENSOR` | LM35 temperature sensor reading via ADC & UART |
| `BM280_TEMP_PRESSURE_SENSING` | Temperature & pressure sensing using BM280 |
| `SPI_BM280_SENSOR` | SPI communication with BM280 sensor |

---

### **📡 Serial Communication**
| Folder | Description |
|-------|-------------|
| `UART_PROTOCOL` | Bare-metal UART transmit/receive example |
| `SPI_PROTOCOL` | SPI master/slave demonstration |

---

### **⚙️ Displays**
| Folder | Description |
|-------|-------------|
| `LCD_16X2_DRIVER` | Full custom LCD 16x2 driver (no library, pure C driver code) |

---

### **🌀 Motor Control**
| Folder | Description |
|-------|-------------|
| `DC_MOTOR_SWITCH1` | Basic DC motor control using L293D |
| `MOTOR_FUNCTION_DELAY` | Motor delay and control using L293D functions |
| `L293_MOTOR_DRIVER` | Full L293D motor driver (CW, CCW, STOP) |

---

### **🏗️ Structured / Modular Programming**
| Folder | Description |
|-------|-------------|
| `MODULAR_PROGRAMMING` | Comprehensive view of writing custom drivers & structured code |

---

## 🧰 Requirements

### Hardware
- ATmega328P / Arduino Uno  
- USBasp / USBtinyISP / Arduino-as-ISP programmer  
- Breadboard, jumper wires  
- LEDs, resistors, switches  
- L293D motor driver  
- LCD 16x2 module  
- LM35 / BM280 sensors 

### Software
- `avr-gcc`  
- `avr-libc`  
- `avrdude`  
- `make`  
- Any editor (VS Code recommended)

---

## ⚙️ Build & Flash Instructions

Inside any example folder:

```bash
make clean
make
make flash


