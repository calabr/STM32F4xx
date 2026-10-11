/*
  mks_robin_nano_v3_1_map.h - driver code for STM32F407 ARM processors

  Part of grblHAL

  Copyright (c) 2021 qbazd
  Copyright (c) 2023-2025 Terje Io

  grblHAL is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.

  grblHAL is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with grblHAL. If not, see <http://www.gnu.org/licenses/>.
*/
#if N_ABC_MOTORS > 2
#error "MKS ROBIN-NANO 3.1 supports 5 motors max."
#endif

#if TRINAMIC_ENABLE && N_GANGED > 0
#error "MKS ROBIN-NANO 3.1 does not support ganged motors with Trinamic drivers."
#endif

#if IS_NUCLEO_DEVKIT
// When debugging with Nucleo-144
#define IS_NUCLEO_BOB
#define SERIAL_PORT    32   // GPIOD: TX = 8, RX = 9
#define SERIAL1_PORT    2   // GPIOB: TX = 10, RX = 11
#elif !defined(STM32F407xx) || HSE_VALUE != 8000000
#error "This board has STM32F407 processor with a 8MHz crystal, select a corresponding build!"
#else
#undef EEPROM_ENABLE
#define EEPROM_ENABLE  32
// UART priority: 1: Main (instead of USB) 2: MODBUS 3: MPG /keypad 4: bluetooth
// available serial allocated according to priority: SERIAL, SERIAL1, SERIAL2
#define SERIAL_PORT     1   // GPIOA: TX = 9, RX = 10 ; MPG/DRO/Keypad;  J24/WiFi
#define SERIAL1_PORT    3   // GPIOB: TX = 10, RX = 11 ; J2 USART3
#endif

#define BOARD_NAME "MKS ROBIN-NANO 3.1"
#define BOARD_URL "https://github.com/makerbase-mks/MKS-Robin-Nano-V3.X"

#undef I2C_ENABLE
#define I2C_ENABLE      1
#define I2C_PORT        1
#define I2C1_ALT_PINMAP     // GPIOB, SCL_PIN = 6, SDA_PIN = 7

// If we want to debug, we need to use USART1
//#if defined(DEBUG) && defined(USB_SERIAL_CDC)
//#undef USB_SERIAL_CDC
//#endif

#define AUX_CONTROLS (AUX_CONTROL_SPINDLE|AUX_CONTROL_COOLANT|AUX_CONTROL_DEVICES)

// Define step pulse output pins.
#define X_STEP_PORT             GPIOE
#define X_STEP_PIN              3             // X
#define Y_STEP_PORT             GPIOE
#define Y_STEP_PIN              0             // Y
#define Z_STEP_PORT             GPIOB
#define Z_STEP_PIN              5             // Z
#define STEP_OUTMODE            GPIO_BITBAND
//#define STEP_PINMODE            PINMODE_OD // Uncomment for open drain outputs

// Define step direction output pins.
#define X_DIRECTION_PORT        GPIOE
#define X_DIRECTION_PIN         2
#define Y_DIRECTION_PORT        GPIOB
#define Y_DIRECTION_PIN         9
#define Z_DIRECTION_PORT        GPIOB
#define Z_DIRECTION_PIN         4
#define DIRECTION_OUTMODE       GPIO_BITBAND
//#define DIRECTION_PINMODE       PINMODE_OD // Uncomment for open drain outputs

// Define stepper driver enable/disable output pin.
#define X_ENABLE_PORT           GPIOE
#define X_ENABLE_PIN            4
#define Y_ENABLE_PORT           GPIOE
#define Y_ENABLE_PIN            1
#define Z_ENABLE_PORT           GPIOB
#define Z_ENABLE_PIN            8
//#define STEPPERS_ENABLE_PINMODE PINMODE_OD // Uncomment for open drain outputs

//// Define homing/hard limit switch input pins.
#define X_LIMIT_PORT            GPIOA
#define X_LIMIT_PIN             15                          // X- Limit
#define Y_LIMIT_PORT            GPIOD
#define Y_LIMIT_PIN             2                           // Y- Limit
#define Z_LIMIT_PORT            GPIOC
#define Z_LIMIT_PIN             8                           // Z- Limit
#define LIMIT_INMODE            GPIO_BITBAND

//Define ganged axis or A axis step pulse and step direction output pins.
#if N_ABC_MOTORS > 0
#define M3_AVAILABLE            // E0
#define M3_STEP_PORT            GPIOD
#define M3_STEP_PIN             6
#define M3_DIRECTION_PORT       GPIOD
#define M3_DIRECTION_PIN        3
#define M3_LIMIT_PORT           GPIOC
#define M3_LIMIT_PIN            4
#define M3_ENABLE_PORT          GPIOB
#define M3_ENABLE_PIN           3
#endif

// Define ganged axis or B axis step pulse and step direction output pins.
#if N_ABC_MOTORS > 1
#define M4_AVAILABLE            // E1
#define M4_STEP_PORT            GPIOD
#define M4_STEP_PIN             15
#define M4_DIRECTION_PORT       GPIOA
#define M4_DIRECTION_PIN        1
#define M4_LIMIT_PORT           GPIOE
#define M4_LIMIT_PIN            7
#define M4_ENABLE_PORT          GPIOA
#define M4_ENABLE_PIN           3
#endif

#if TRINAMIC_UART_ENABLE

#undef TRINAMIC_UART_ENABLE
#define TRINAMIC_UART_ENABLE    2

#define MOTOR_UARTX_PORT        GPIOD
#define MOTOR_UARTX_PIN         5
#define MOTOR_UARTY_PORT        GPIOD
#define MOTOR_UARTY_PIN         7
#define MOTOR_UARTZ_PORT        GPIOD
#define MOTOR_UARTZ_PIN         4

#ifdef  M3_AVAILABLE
#define MOTOR_UARTM3_PORT       GPIOD
#define MOTOR_UARTM3_PIN        9
#endif

#ifdef  M4_AVAILABLE
#define MOTOR_UARTM4_PORT       GPIOD
#define MOTOR_UARTM4_PIN        8
#endif

#endif // TRINAMIC_UART_ENABLE

#if TRINAMIC_SPI_ENABLE

#define TRINAMIC_SOFTSPI // GPIOD, SCK_PIN = 0, MISO_PIN = 1, MOSI_PIN = 14

#define MOTOR_CSX_PORT          GPIOD
#define MOTOR_CSX_PIN           5
#define MOTOR_CSY_PORT          GPIOD
#define MOTOR_CSY_PIN           7
#define MOTOR_CSZ_PORT          GPIOD
#define MOTOR_CSZ_PIN           4

#ifdef M3_AVAILABLE
#define MOTOR_CSM3_PORT         GPIOD
#define MOTOR_CSM3_PIN          9
#endif

#ifdef  M4_AVAILABLE
#define MOTOR_CSM4_PORT         GPIOD
#define MOTOR_CSM4_PIN          8
#endif

#endif // TRINAMIC_SPI_PORT


// only 2 out PWN available
#define AUXOUTPUT0_PWM_PORT     GPIOB
#define AUXOUTPUT0_PWM_PIN      1			// FAN2
#define AUXOUTPUT1_PWM_PORT     GPIOA
#define AUXOUTPUT1_PWM_PIN      8			// SERVOS BLTOUCH


#define AUXOUTPUT0_PORT         GPIOB //  PW-OFF
#define AUXOUTPUT0_PIN          2
#define AUXOUTPUT1_PORT         GPIOC //  EXP1.1 (Boozer)
#define AUXOUTPUT1_PIN          5
#define AUXOUTPUT2_PORT         GPIOE //  EXP1.2
#define AUXOUTPUT2_PIN          13
#define AUXOUTPUT3_PORT         GPIOC //  EXP1.4
#define AUXOUTPUT3_PIN          6
#define AUXOUTPUT4_PORT         GPIOE //  EXP1.6
#define AUXOUTPUT4_PIN          15
#define AUXOUTPUT5_PORT         GPIOD //  EXP1.8
#define AUXOUTPUT5_PIN          10
#define AUXOUTPUT6_PORT         GPIOE //  EXP2.3
#define AUXOUTPUT6_PIN          8
#define AUXOUTPUT7_PORT         GPIOE //  EXP2.5
#define AUXOUTPUT7_PIN          11
#define AUXOUTPUT8_PORT         GPIOE //  EXP2.7
#define AUXOUTPUT8_PIN          12
#define AUXOUTPUT9_PORT         GPIOC //  FAN1
#define AUXOUTPUT9_PIN          14

#define AUXOUTPUT10_PORT         GPIOB // HE1
#define AUXOUTPUT10_PIN          0
#define AUXOUTPUT11_PORT         GPIOE // HE0
#define AUXOUTPUT11_PIN          5
#define AUXOUTPUT12_PORT         GPIOA // HB
#define AUXOUTPUT12_PIN          0

// analog input pins 0 to 1
#define AUXINTPUT0_ANALOG_PORT  GPIOA // TH2 Thermistor input
#define AUXINTPUT0_ANALOG_PIN   2

// AUX input pins  0 to 12
#define AUXINPUT0_PORT          GPIOA // PW_DET
#define AUXINPUT0_PIN           13

#define AUXINPUT1_PORT          GPIOA // MT_DET1
#define AUXINPUT1_PIN           4

#define AUXINPUT2_PORT          GPIOE // MT_DET2
#define AUXINPUT2_PIN           6

#define AUXINPUT3_PORT          GPIOC // TB
#define AUXINPUT3_PIN           0
#define AUXINPUT4_PORT          GPIOC // TH1
#define AUXINPUT4_PIN           1
#define AUXINPUT5_PORT          GPIOD // EXP1.3
#define AUXINPUT5_PIN           13
#define AUXINPUT6_PORT          GPIOE // EXP1.5
#define AUXINPUT6_PIN           14
#define AUXINPUT7_PORT          GPIOD // EXP1.7
#define AUXINPUT7_PIN           11
#define AUXINPUT8_PORT          GPIOA // EXP2.1
#define AUXINPUT8_PIN           6
#define AUXINPUT9_PORT          GPIOA // EXP2.2
#define AUXINPUT9_PIN           5
#define AUXINPUT10_PORT         GPIOE // EXP2.4
#define AUXINPUT10_PIN          10
#define AUXINPUT11_PORT         GPIOA // EXP2.6
#define AUXINPUT11_PIN          7
#define AUXINPUT12_PORT         GPIOD // SD_DET
#define AUXINPUT12_PIN          12


/* #if !SPINDLE_SYNC_ENABLE && !QEI_ENABLE
 #define AUXINPUT4_PORT          GPIOE                 // EXP2.4  (i2c-STROBE) IRQ_10
 #define AUXINPUT4_PIN           10
#endif
#if !QEI_ENABLE
 #define AUXINPUT5_PORT          GPIOE                 // EXP2.5  IRQ_11
 #define AUXINPUT5_PIN           11
#endif
 */
// Define driver spindle0 pins
#if DRIVER_SPINDLE_ENABLE & SPINDLE_ENA
 #define SPINDLE_ENABLE_PORT     AUXOUTPUT6_PORT
 #define SPINDLE_ENABLE_PIN      AUXOUTPUT6_PIN     // EXP2.3
#endif
#if DRIVER_SPINDLE_ENABLE & SPINDLE_DIR
 #define SPINDLE_DIRECTION_PORT   AUXOUTPUT7_PORT
 #define SPINDLE_DIRECTION_PIN    AUXOUTPUT7_PIN  // EXP2.5
#endif
#if DRIVER_SPINDLE_ENABLE & SPINDLE_PWM
 #define SPINDLE_PWM_PORT      AUXOUTPUT10_PORT    // HE1
 #define SPINDLE_PWM_PIN       AUXOUTPUT10_PIN
#endif

// Define driver spindle1 pins
#if DRIVER_SPINDLE1_ENABLE & SPINDLE_ENA
 #define SPINDLE1_ENABLE_PORT     AUXOUTPUT8_PORT // EXP2.7
 #define SPINDLE1_ENABLE_PIN      AUXOUTPUT8_PIN
#endif
#if DRIVER_SPINDLE1_ENABLE & SPINDLE_DIR
 #define SPINDLE1_DIRECTION_PORT  AUXOUTPUT5_PORT // EXP1.8
 #define SPINDLE1_DIRECTION_PIN   AUXOUTPUT5_PIN
#endif
#if DRIVER_SPINDLE1_ENABLE & SPINDLE_PWM
 #define SPINDLE1_PWM_PORT        AUXOUTPUT11_PORT  // HE0
 #define SPINDLE1_PWM_PIN         AUXOUTPUT11_PIN
#endif

// Define flood and mist coolant enable output pins.
#if COOLANT_ENABLE & COOLANT_FLOOD
 #define COOLANT_FLOOD_PORT      AUXOUTPUT9_PORT	// FAN1
 #define COOLANT_FLOOD_PIN       AUXOUTPUT9_PIN
#endif
#if COOLANT_ENABLE & COOLANT_MIST
 #define COOLANT_MIST_PORT       AUXOUTPUT12_PORT	// HB
 #define COOLANT_MIST_PIN        AUXOUTPUT12_PIN
#endif


// Define user-control controls (cycle start, reset, feed hold) input pins. Require IRQ
#define RESET_PORT              AUXINPUT4_PORT
#define RESET_PIN               AUXINPUT4_PIN     // Reset buton, TH1, 

#define FEED_HOLD_PORT          AUXINPUT7_PORT   // EXP1.7 
#define FEED_HOLD_PIN           AUXINPUT7_PIN      

#if IS_NUCLEO_DEVKIT
 #define CYCLE_START_PORT        GPIOA
 #define CYCLE_START_PIN         10                // When debugging with Nucleo-144
#else
 #define CYCLE_START_PORT        AUXINPUT6_PORT  // START button, EXP1.5
 #define CYCLE_START_PIN         AUXINPUT6_PIN
#endif

#define CONTROL_INMODE GPIO_BITBAND

#if SAFETY_DOOR_ENABLE
 #define SAFETY_DOOR_PORT        AUXINPUT5_PORT		// EXP1.3  Require IRQ
 #define SAFETY_DOOR_PIN         AUXINPUT5_PIN
 #endif

#if MOTOR_WARNING_ENABLE
 #define MOTOR_WARNING_PORT        AUXINPUT10_PORT  // EXP2.4
 #define MOTOR_WARNING_PIN         AUXINPUT10_PIN
#endif

#if PROBE_ENABLE
 #define PROBE_PORT              AUXINPUT2_PORT  // MT_DET2, Require IRQ
 #define PROBE_PIN               AUXINPUT2_PIN
#endif
#if TOOLSETTER_ENABLE
 #define TOOLSETTER_PORT              AUXINPUT3_PORT  // TB, Require IRQ
 #define TOOLSETTER_PIN               AUXINPUT3_PIN
#endif

#if I2C_STROBE_ENABLE
 #define I2C_STROBE_PORT         AUXINPUT12_PORT // Require IRQ
 #define I2C_STROBE_PIN          AUXINPUT12_PIN
#elif MPG_ENABLE == 1		// switche MPG mode by pin
 #define MPG_AUX_ENABLE
 #define MPG_MODE_PORT           AUXINPUT10_PORT	// Require IRQ
 #define MPG_MODE_PIN            AUXINPUT10_PIN
#elif QEI_SELECT_ENABLE && defined(QEI_ENABLE)
  #define QEI_SELECT_PORT         AUXINPUT10_PORT  // Require IRQ
  #define QEI_SELECT_PIN          AUXINPUT10_PIN
#endif

// Spindle encoder pins.
#if SPINDLE_ENCODER_ENABLE
 #define RPM_COUNTER_N           3 // Spindle encoder pulse
 #define RPM_TIMER_N            2 // Spindle INDEX timer CH1 - INDEX !! contradict with SPINDLE_PWM on PA0
 #define SPINDLE_PULSE_PORT       AUXINPUT9_PORT
 #define SPINDLE_PULSE_PIN        AUXINPUT9_PIN			// EXP2.1  PA6; EXP2.6 PA7
 #if SPINDLE_SYNC_ENABLE    // require SPINDLE_ENCODER_ENABLE
//  #define RPM_TIMER_N            10 // Spindle INDEX timer CH1 - INDEX
//  #define SPINDLE_INDEX_PORT      AUXINPUT11_PORT
//  #define SPINDLE_INDEX_PIN       AUXINPUT11_PIN				// EXP1.4
  #define SPINDLE_INDEX_PORT      AUXINPUT9_PORT
  #define SPINDLE_INDEX_PIN       AUXINPUT9_PIN				// EXP2.2
 #endif
#endif

#if QEI_ENABLE && !SPINDLE_SYNC_ENABLE  // Quadrature encoder interface require pin IRQ
 #define QEI_A_PORT              AUXINPUT8_PORT
 #define QEI_A_PIN               AUXINPUT8_PIN
 #define QEI_B_PORT              AUXINPUT11_PORT
 #define QEI_B_PIN               AUXINPUT11_PIN
#endif  // QEI_ENABLE

#if SDCARD_ENABLE
    #define SD_DETECT_PORT          GPIOD
    #if !I2C_STROBE_ENABLE
     #define SD_DETECT_PIN           12 	// require interrupt
    #endif
    #define SD_CS_PORT              GPIOC
    #define SD_CS_PIN               9
    #define SPI_PORT                3 // GPIOC, SCK_PIN = 10, MISO_PIN = 11, MOSI_PIN = 12 (SPI3)
#endif

