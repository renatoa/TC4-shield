// user.h
//---------
// This file contains user definable compiler directives for aArtisanQ_PID

// *************************************************************************************
// NOTE TO USERS: the following parameters should be
// be reviewed to suit your preferences and hardware setup.  
// First, load and edit this sketch in the Arduino IDE.
// Next compile the sketch and upload it to the Arduino.

#ifndef USER_H
#define USER_H

////////////////////
// Roasting software
// Comment out all if using TC4 stand alone
//#define ROASTLOGGER
#define ARTISAN
#define ANDROID

////////////////////
// Base configurations (leave only one uncommented)
// CONFIG_PAC2_IO3HTR not available for ESP8266 because PWM use same timer as PAC
#define CONFIG_PWM // slow PWM on OT1 (heater); fast PWM output (3.922kHz) on IO3 (DC fan); ZCD not required
//#define CONFIG_PAC2 // phase angle control on OT1 (heater) and OT2 (fan); IO2 used to read the ZCD
//#define CONFIG_PAC2_IO3HTR // phase angle control on OT1 (heater) and OT2 (fan); IO2 reads the req'd ZCD; IO3 reserved for fast PWM output for heater
//#define CONFIG_PAC3 // phase angle control on OT1 (heater) and OT2 (fan); IO3 reads the req'd ZCD; IO3 not available for output

////////////////////
// Temperature Unit
#define CELSIUS // controls only the initial conditions.  Comment out for F.

////////////////////
// LCD Options
// Choose ONE of the following LCD options if using an LCD
//#define LCDAPTER // if the I2C LCDapter board is to be used
#define LCD_I2C // if using a $5 delivered Chinese LCD with I2C module
//#define LCD_PARALLEL // if using a parallel LCD screen

#define LCD_4x20 // if using a 4x20 LCD instead of a 2x16

#define LCD_I2C_ADDRESS 0x27 // adjust I2C address for LCD if required. Try 0x3F, 0x20. Not used for LCDapter.

/////////////////////
// Input Button Options
// Connect button between input pin and ground. Useful if not using LCDapter buttons.
// Only active in standalone mode.
#if ! ( defined ROASTLOGGER || defined ARTISAN || defined ANDROID ) // Stops buttons being read unless in standalone mode. Added to fix crash (due to low memory?).

#define RESET_TIMER_BUTTON 4 // Reset timer using button on pin X
#define TOGGLE_PID_BUTTON 5  // Toggle PID on/off using button on pin X
#define MODE_BUTTON 7        // Switch LCD Mode
#define ENTER_BUTTON 8       // Confirm choice

#if defined RESET_TIMER_BUTTON || defined TOGGLE_PID_BUTTON || defined MODE_BUTTON || defined ENTER_BUTTON 
#define pinButton 1
#endif

#endif

/////////////////////
// AC Power Options
// Needed for CONFIG_PAC options
//#define FREQ60 // 60Hz
#define FREQ50 // 50Hz

////////////////////
// Thermocouple Input Options
// TC type is selectable by input channel
// permissable options:  typeT, typeK, typeJ
#define TC_TYPE1 tcLinear  
//#define TC_TYPE2 typeK  
//#define TC_TYPE3 ... 
//#define TC_TYPE4 ... 

////////////////////
// BAUD Rate for serial communications
#define BAUD 115200

////////////////////
// Analogue inputs (optional)
// Comment out if not required
//#define ANALOGUE1 // if potentiometer connected on ANLG1 (or TC3)
//#define ANALOGUE2 // if potentiometer connected on ANLG2 (or TC4)

////////////////////
// Duty Cycle Adjustment Increment
// Used for rounding/increment for analogue inputs and power UP/DOWN commands
#define DUTY_STEP 1 // Use 1, 2, 4, 5, or 10.

////////////////////
// Physical input channel for RoR display on LCD
// Corresponds to Thermocouple inputs T1-T4
#define ROR_CHAN 2

////////////////////
// PID Control Options
#define PID_CONTROL
#define PID_CHAN 2 // physical channel for PID input (corresponding to thermocouple inputs T1-T4)
#define CT 1000 // default cycle time for the PID, in ms
#define PRO 4.80 // initial proportional parameter
#define INT 0.05 // initial integral parameter
#define DER 0.00 // initial derivative parameter

//#define POM // enable Proportional on Measurement (NOTE: PID PARAMETERS WILL REQUIRE CHANGING). Disable for Proportional on Error.

#define NUM_PROFILES 9 // number of profiles stored in EEPROM

////////////////////
// Heater and Fan Limits/Options
#define MIN_OT1 40 // Set output % for lower limit for OT1.  0% power will always be available
#define MAX_OT1 80 // Set output % for upper limit for OT1

#define MIN_OT2 0 // Set output % for lower limit for OT2.  0% power will always be available
#define MAX_OT2 100 // Set output % for upper limit for OT2

#define MIN_IO3 0 // Set output % for lower limit for IO3.  0% power will always be available
#define MAX_IO3 100  // Set output % for upper limit for IO3

// cut power to Heater if fan duty is less than HTR_CUTOFF_FAN_VAL (to protect heater in air roaster). Set to 0 for no cutoff
#define HTR_CUTOFF_FAN_VAL 0

#define FAN_AUTO_COOL 100 // Set fan output duty for auto cool when using PID;STOP command

////////////////////
// Command Echo
#undef COMMAND_ECHO // Echo all serial commands to LCD for debugging

////////////////////
// Temperature Reading Filters
#define BT_FILTER 10 // filtering level (percent) for BT
#define ET_FILTER 10 // filtering level (percent) for ET
#define AMB_FILTER 10 // 70% filtering on ambient sensor readings

// use RISE_FILTER to adjust the sensitivity of the RoR calculation
// higher values will give a smoother RoR trace, but will also create more
// lag in the RoR value.  A good starting point is 80%, but for air poppers
// or other roasters where BT might be jumpy, then a higher value of RISE_FILTER
// will be needed.  Theoretical max. is 99%, but watch out for the lag when
// you get above 95%.
#define RISE_FILTER 50 // heavy filtering on non-displayed BT for RoR calculations
#define ROR_FILTER 80 // post-filtering for the computed RoR values

// Thermocouple inputs
#define NC 4 // maximum number of physical channels on the TC4

////////////////////
// Calibration Values
// default values for systems without calibration values stored in EEPROM
#define CAL_GAIN 1.00 // you may substitute a known gain adjustment from calibration
#define UV_OFFSET 0 // you may substitute a known value for uV offset in ADC
#define AMB_OFFSET 0.0 // you may substitute a known value for amb temp offset (Celsius)

////////////////////
// Time Base for slow PWM on OT1, OT2
// When NOT using PHASE_ANGLE_CONTROL option
// choose one of the following for the PWM time base for heater output on OT1 or OT2
//#define TIME_BASE pwmN4sec  // recommended for Hottop D which has mechanical relay
//#define TIME_BASE pwmN2sec
#define TIME_BASE pwmN1Hz  // recommended for most electric heaters controlled by standard SSR
//#define TIME_BASE pwmN2Hz
//#define TIME_BASE pwmN4Hz
//#define TIME_BASE pwmN8Hz 
// The faster frequencies below are for advanced users only, and will require changes to the PWM16 Library
//#define TIME_BASE 15 // approx. 977 Hz
//#define TIME_BASE 7 // approx. 1.95kHz
//#define TIME_BASE 6 // approx. 2.2kHz
//#define TIME_BASE 3 // approx. 3.9kHz

////////////////////
// Debugging Options
// Useful for debugging only -- leave inactive otherwise
//#define MEMORY_CHK

// This turns on the "# xxxxxxx\n" acknowledgements after commands
//#define ACKS_ON

////////////////////
// Output Pin Setup
#ifdef ESP8266 
  // phase angle control and integral cycle control outputs
  //#define OT1 D4 // OT1 is on pin D4/GPIO2 
  #define OT1 D0 // OT1 is on pin D0/GPIO16 
  //#define OT2 ... // OT2 is on pin D?? 
  #define OT_PAC OT1 // phase angle control on OT2 (AC fan, usually)
  #define OT_ICC OT1 // integral cycle control on OT1 (AC heater, usually)
#ifdef ARDUINO_ESP8266_NODEMCU
  //#define LED_PIN LED_BUILTIN // on NodeMCU only
  // on NodeMCU LED logic is reversed, LOW = light
#else
  #define LED_PIN LED_BUILTIN // LED pin is D0/GPIO16 for other ESP8266 boards
#endif // ARDUINO_ESP8266_NODEMCU
#elif defined ESP32
// ... TBD
#endif

//////////////////////////////////////////////////////
// Set up parameters for the base configurations
#ifdef CONFIG_PWM // nothing special to configure -- this is the default
#endif

#ifdef CONFIG_PAC2_IO3HTR
  #define PHASE_ANGLE_CONTROL // phase angle control for OT2(fan) and ICC control for OT1(heater)
  #define IO3_HTR_PAC // use PWM (3.922kHz) out on IO3 for heater in PHASE ANGLE CONTROL mode
  // zero cross detector (ZCD) connected to I/O2, D7 on ESP 8266
  #define EXT_INT 0 // interrupt 0
#ifdef ESP8266
  #define INT_PIN D7 // pin GPIO13/D7 on ESP8266
#elif defined ESP32
  // ... TBD
#else // Uno
  #define INT_PIN 2 // pin 2
#endif // platforms
#endif // CONFIG_PAC2_IO3HTR

#ifdef CONFIG_PAC2
  #define PHASE_ANGLE_CONTROL // phase angle control for OT2(fan) and ICC control for OT1(heater)
#ifdef ESP8266
  // zero cross detector (ZCD) connected to GPIO13/D7 
  #define INT_PIN D7 // pin GPIO13/D7 on ESP8266
#elif defined ESP32
  #define INT_PIN ... // pin GPIO??/?? on ESP32
#else // Uno
  // zero cross detector (ZCD) connected to I/O2
  #define EXT_INT 0 // interrupt 0
  #define INT_PIN 2 // pin 2
#endif // platforms
#endif // CONFIG_PAC2

#ifdef CONFIG_PAC3
  #define PHASE_ANGLE_CONTROL // phase angle control for OT2(fan) and ICC control for OT1(heater)
#ifdef ESP8266
  // zero cross detector (ZCD) connected to GPIO13/D7 
  #define INT_PIN D7 // pin GPIO13/D7 on ESP8266
#elif defined ESP32
  #define INT_PIN ... // pin GPIO??/?? on ESP32
#else
  // zero cross detector (ZCD) connected to I/O3
  #define EXT_INT 1 // interrupt 1
  #define INT_PIN 3
#endif // platforms
#endif // CONFIG_PAC3


////////////////////
// Heater and Fan Duty Display Options
// These should NOT need adjusting.  They control what gets streamed back to via serial
// These have no effect on operation and only affect what gets displayed/logged by Artisan
#ifdef PHASE_ANGLE_CONTROL
  #ifdef IO3_HTR_PAC // If using PWM on IO3 for a heater
    #define HEATER_DUTY levelIO3 // Heater output is assumed levelIO3 with heater connected to IO3
  #else // If using ICC control of a heater connected to OT1
    #define HEATER_DUTY levelOT1 // Heater output is assumed levelOT1 with heater connected to OT1
  #endif
  #define FAN_DUTY levelOT2 // Fan output is assumed levelOT2 for phase angle control mode on OT2
#else // PWM Mode
  #define HEATER_DUTY levelOT1 // Heater output is assumed levelOT1 with heater connected to OT1
  #define FAN_DUTY levelIO3 // Fan output is assumed levelIO3 for PWM control of fan connected to IO3
#endif

////////////////////
// Phase Angle Control Options
// When using PHASE_ANGLE_CONTROL option
// Select load type being switched by phase angle control (has no effect on the ICC output)
//#define TRIAC_MOTOR // inductive loads need a longer pulse width to fire at 100%
#define TRIAC_HEATER // enable this for resistive loads, like heaters


#endif

