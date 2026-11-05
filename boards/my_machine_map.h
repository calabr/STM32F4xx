/*
 Blackpill map for testing 
 STM32F411
 based on  Devtronic_CNC_Controller_map.h 
  Part of grblHAL

  Copyright (c) 2023-2025 @nickshl & Terje Io

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

/* Pin Assignments(V2 have optional RS-485 support instead PWM spindle):
 *
 *            Door/Strobe/IN12 A14 -   - A13 Start/IN11
 *                                  | |
 *                                G S D +
 *                                N C I 3
 *                                D K O V
 *                              -----------
 *                          VB |           | +3V
 *              AUX Out0   C13 |           | GND
 *          Coolant Flood  C14 |           | +5V
 *               AUX Out1  C15 | *     - * | B9   I2C SDA
 *                         RST |      |K|  | B8   I2C SCL
 *                  Reset   A0 |       -   | B7   UART11-RX/OUT3
 *         Index/IN8   A1 |           | B6   UART11-TX/OUT2
 *        SPN EN(TX)/OUT7   A2 |           | B5   Z-Step
 *       SPN DIR(RX)/OUT8   A3 |    / \    | B4   Z-Dir
 *                X-Limit   A4 |   <MCU>   | B3   Toolsetter/IN2
 *          Encoder Pulse   A5 |    \ /    | A15  Y-Limit
 *                 Probe    A6 |           | A12  USB D+
 *        PRB Disconnect    A7 |   -   -   | A11  USB D-
 *                SPN-PWM   B0 |  |R| |B|  | A10  MPG/DRO RX
 *              LED0/PWM0   B1 |   -   -   | A9   MPG/DRO TX
 *      SPN1-EM/OUT6/AIn0   B2 |           | A8   BLtouch(PWM1)/OUT3
 *         MotorFault/IN1  B10 |           | B15  Y-Dir
 *                         +3V |   -----   | B14  Y-Step
 *                         GND |  |     |  | B13  X-Dir
 *                         +5V |  | USB |  | B12  X-Step
 *                              -----------
 */

 #if N_ABC_MOTORS > 0
 #error "Axis configuration is not supported!"
 #endif
 
 #define BOARD_NAME "Blackpill test F411"
 
 #define SERIAL_PORT   1   // GPIOA: TX = 9, RX = 10 
 #define I2C_PORT      1   // GPIOB: SCL = 8, SDA = 9
 
 #if MODBUS_ENABLE 
 //  #if ESP_AT_ENABLE
 //  #error " Modbus and ESP_AT not supported together on this board!"
 //  #endif
 #define SERIAL1_PORT  2   // GPIOA: TX = 2, RX = 3
 #define MODBUS_SERIAL_PORT      1
 #define MODBUS_RTU_STREAM       1
 #ifdef MODBUS_DIR_AUX
  #undef MODBUS_DIR_AUX
 #endif
 #define MODBUS_DIR_AUX          4 /* AUX port number for runtime link */
#endif
 
#if ESP_AT_ENABLE
 //  #define SERIAL1_PORT  11   // GPIOB: TX = 6, RX = 7
   #define COPROC_STREAM 1
#else 
  #define AUXOUTPUT1_PORT         GPIOB 
  #define AUXOUTPUT1_PIN          6
  #define AUXOUTPUT2_PORT         GPIOB 
  #define AUXOUTPUT2_PIN          7
#endif

// Define step Pulse / DIR output pins.
#define X_STEP_PORT             GPIOB
#define X_STEP_PIN              12             // X
#define X_DIRECTION_PORT        GPIOB
#define X_DIRECTION_PIN         13

#define Y_STEP_PORT             GPIOB
#define Y_STEP_PIN              14             // Y
#define Y_DIRECTION_PORT        GPIOB
#define Y_DIRECTION_PIN         15

#define Z_STEP_PORT             GPIOB
#define Z_STEP_PIN              5             // Z
#define Z_DIRECTION_PORT        GPIOB
#define Z_DIRECTION_PIN         4

#define STEP_OUTMODE            GPIO_BITBAND
#define DIRECTION_OUTMODE       GPIO_BITBAND
//#define STEP_PINMODE            PINMODE_OD // Uncomment for open drain outputs
//#define DIRECTION_PINMODE       PINMODE_OD // Uncomment for open drain outputs


//// Define homing/hard limit switch input pins.
#define X_LIMIT_PORT            GPIOA
#define X_LIMIT_PIN             4                         // X- Limit

#define Y_LIMIT_PORT            GPIOA
#define Y_LIMIT_PIN             15                         // Y- Limit

#define Z_LIMIT_PORT            GPIOC
#define Z_LIMIT_PIN             8                           // Z- Limit

#define LIMIT_INMODE            GPIO_BITBAND

 
 // Define stepper driver enable/disable output pin.
 #define STEPPERS_ENABLE_PORT    GPIOC
 #define STEPPERS_ENABLE_PIN     12
 #define STEPPERS_ENABLE_MASK    STEPPERS_ENABLE_BIT
 

#define AUXOUTPUT0_PORT       GPIOC //  
#define AUXOUTPUT0_PIN        13

#define AUXOUTPUT6_PORT       GPIOB //  SPN1-EN  
#define AUXOUTPUT6_PIN        2   

#define AUXOUTPUT7_PORT       GPIOA //  SPN-EN  
#define AUXOUTPUT7_PIN        2   

#define AUXOUTPUT8_PORT       GPIOA // SPN-DIR  
#define AUXOUTPUT8_PIN        3

#define AUXOUTPUT9_PORT       GPIOB //  SPN-PWM
#define AUXOUTPUT9_PIN        0

#define AUXOUTPUT10_PORT      GPIOC //  Flood
#define AUXOUTPUT10_PIN       14

#define AUXOUTPUT11_PORT      GPIOC //  Meest
#define AUXOUTPUT11_PIN       11


// PWM outputs
#ifdef PWM_SERVO_ENABLE
 #define AUXOUTPUT1_PWM_PORT     GPIOA // SERVOS BLTOUCH
 #define AUXOUTPUT1_PWM_PIN      8			
#else
 #define AUXOUTPUT3_PORT      GPIOA
 #define AUXOUTPUT3_PIN       8
#endif

// AUX input pins 
#define AUXINPUT0_PORT         GPIOC
#define AUXINPUT0_PIN          5

#define AUXINPUT1_PORT         GPIOB // Motor fault
#define AUXINPUT1_PIN          10

#define AUXINPUT2_PORT         GPIOB // Toolsetter /QEI-B
#define AUXINPUT2_PIN          3

#define AUXINPUT7_PORT         GPIOA // Key ( reset)
#define AUXINPUT7_PIN          0

#define AUXINPUT9_PORT        GPIOA  // 
#define AUXINPUT9_PIN         6 

#define AUXINPUT10_PORT       GPIOA // 
#define AUXINPUT10_PIN        7

#define AUXINPUT11_PORT       GPIOA // 
#define AUXINPUT11_PIN        13

#define AUXINPUT12_PORT       GPIOA // 
#define AUXINPUT12_PIN        14


// Define driver spindle0 pins
#if DRIVER_SPINDLE_ENABLE & SPINDLE_ENA
 #define SPINDLE_ENABLE_PORT     AUXOUTPUT7_PORT  //
 #define SPINDLE_ENABLE_PIN      AUXOUTPUT7_PIN 
#endif

#if DRIVER_SPINDLE_ENABLE & SPINDLE_DIR
 #define SPINDLE_DIRECTION_PORT   AUXOUTPUT8_PORT //
 #define SPINDLE_DIRECTION_PIN    AUXOUTPUT8_PIN   
#endif
#if DRIVER_SPINDLE_ENABLE & SPINDLE_PWM
 #define SPINDLE_PWM_PORT      AUXOUTPUT9_PORT //AUXOUTPUT9_PORT    // HE1
 #define SPINDLE_PWM_PIN       AUXOUTPUT9_PIN // AUXOUTPUT9_PIN

#endif

// Define driver spindle1 pins
#if DRIVER_SPINDLE1_ENABLE & SPINDLE_ENA
 #define SPINDLE1_ENABLE_PORT     AUXOUTPUT6_PORT // 
 #define SPINDLE1_ENABLE_PIN      AUXOUTPUT6_PIN
#endif
#if DRIVER_SPINDLE1_ENABLE & SPINDLE_DIR
 #define SPINDLE1_DIRECTION_PORT  AUXOUTPUT_PORT // 
 #define SPINDLE1_DIRECTION_PIN   AUXOUTPUT_PIN
#endif
#if DRIVER_SPINDLE1_ENABLE & SPINDLE_PWM
 #define SPINDLE1_PWM_PORT        AUXOUTPUT3_PORT  // 
 #define SPINDLE1_PWM_PIN         AUXOUTPUT3_PIN
#endif


 // Define flood and mist coolant enable output pins.
#if COOLANT_ENABLE & COOLANT_FLOOD
 #define COOLANT_FLOOD_PORT      AUXOUTPUT10_PORT	// FAN1
 #define COOLANT_FLOOD_PIN       AUXOUTPUT10_PIN
#endif
#if COOLANT_ENABLE & COOLANT_MIST
 #define COOLANT_MIST_PORT       AUXOUTPUT11_PORT	// HB
 #define COOLANT_MIST_PIN        AUXOUTPUT11_PIN
#endif

// Define user-control control inputs (cycle start, reset, feed hold).
#if CONTROL_ENABLE & CONTROL_HALT
 #define RESET_PORT              AUXINPUT7_PORT
 #define RESET_PIN               AUXINPUT7_PIN
#endif
#if (CONTROL_ENABLE & CONTROL_FEED_HOLD) && AUXINPUT8_PIN
 #define FEED_HOLD_PORT          AUXINPUT8_PORT
 #define FEED_HOLD_PIN           AUXINPUT8_PIN
#endif
#if CONTROL_ENABLE & CONTROL_CYCLE_START
 #define CYCLE_START_PORT        AUXINPUT11_PORT
 #define CYCLE_START_PIN         AUXINPUT11_PIN
#endif

#define CONTROL_INMODE GPIO_BITBAND

#if SAFETY_DOOR_ENABLE
 #define SAFETY_DOOR_PORT        AUXINPUT12_PORT		//  Require IRQ
 #define SAFETY_DOOR_PIN         AUXINPUT12_PIN
#elif I2C_STROBE_ENABLE
 #define I2C_STROBE_PORT         AUXINPUT12_PORT
 #define I2C_STROBE_PIN          AUXINPUT12_PIN
#endif

#if MOTOR_FAULT_ENABLE
  #define MOTOR_FAULT_PORT        AUXINPUT1_PORT // 
  #define MOTOR_FAULT_PIN         AUXINPUT1_PIN
#endif
/*
#if MOTOR_WARNING_ENABLE
 #define AUXINPUT6_PORT          GPIOB
 #define AUXINPUT6_PIN           2
  #define MOTOR_WARNING_PORT        AUXINPUT6_PORT  
  #define MOTOR_WARNING_PIN         AUXINPUT6_PIN
#else
  // analog input pins 0 to 1
  #define AUXINPUT0_ANALOG_PORT  GPIOB // 
  #define AUXINPUT0_ANALOG_PIN   2
#endif
*/
#if PROBE_ENABLE
 #define PROBE_PORT              AUXINPUT9_PORT  //  Require IRQ
 #define PROBE_PIN               AUXINPUT9_PIN
#endif

#if TOOLSETTER_ENABLE
  #define TOOLSETTER_PORT              AUXINPUT2_PORT  // 
  #define TOOLSETTER_PIN               AUXINPUT2_PIN
 #endif 

#if PROBE_DISCONNECT_ENABLE
 #define PROBE_DISCONNECT_PORT  AUXINPUT10_PORT
 #define PROBE_DISCONNECT_PIN   AUXINPUT10_PIN
#endif

 // Spindle encoder pins.
#if SPINDLE_ENCODER_ENABLE
 #define RPM_COUNTER_N           2 // Spindle encoder pulse
 #define RPM_TIMER_N             3 //3 // Spindle timer
 #define SPINDLE_PULSE_PORT      GPIOA
 #define SPINDLE_PULSE_PIN       5			//   PA5 or PA15
 #if SPINDLE_SYNC_ENABLE    // require SPINDLE_ENCODER_ENABLE
  #define SPINDLE_INDEX_PORT     GPIOA   // require IRQ
  #define SPINDLE_INDEX_PIN      1	// 
 #else
  #define AUXINPUT8_PORT         GPIOA // 
  #define AUXINPUT8_PIN          1
 #endif
#else
 #define AUXINPUT8_PORT          GPIOA // TB
 #define AUXINPUT8_PIN           1
 #define AUXINPUT3_PORT          GPIOA // 
 #define AUXINPUT3_PIN           5
#endif

#if RGB_LED_ENABLE
 #define LED_GPO_PORT            GPIOB  // 
 #define LED_GPO_PIN             1
// #define LED_PWM_PORT   GPIOB
 //#define LED_PWM_PIN    1
#else
// #define AUXOUTPUT0_PWM_PORT     GPIOB
// #define AUXOUTPUT0_PWM_PIN      1			
#endif

/*
#if QEI_ENABLE // && !SPINDLE_SYNC_ENABLE  // Quadrature encoder interface require pin IRQ?
 #define QEI_A_PORT              GPIOA
 #define QEI_A_PIN               6
 #define QEI_B_PORT              GPIOA
 #define QEI_B_PIN               7
 #if !SPINDLE_SYNC_ENABLE
  #define QEI_SELECT_PORT AUXINPUT2_PORT 
  #define QEI_SELECT_PIN  AUXINPUT2_PIN
 #endif
#else
 #define AUXOUTPUT2_PORT          GPIOB // 
 #define AUXOUTPUT2_PIN           3
 #define AUXOUTPUT5_PORT          GPIOA // 
 #define AUXOUTPUT5_PIN           7
#endif  // QEI_ENABLE
*/
#if SDCARD_ENABLE
 #error SDcard not supported
#endif
 
 /* EOF */
 