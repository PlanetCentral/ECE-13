// **** Include libraries here ****
// Standard libraries
#include <stdio.h>

// CMPE13 Support Library
#include "BOARD.h"
#include "Adc.h"
#include "Ascii.h"
#include "Buttons.h"
#include "Leds.h"
#include "Oled.h"
#include "OledDriver.h"

// Microchip libraries
#include <xc.h>
#include <sys/attribs.h>

// **** Set any macros or preprocessor directives here ****
// Set a macro for resetting the timer, makes the code a little clearer.
#define TIMER_2HZ_RESET() (TMR1 = 0)

// **** Set any local typedefs here ****
typedef enum {
    SETUP,
    SELECTOR_CHANGE_PENDING,
    COOKING,
    RESET_PENDING
} OvenState;

typedef enum {
    BAKE,
    TOAST,
    BROIL
} CookingMode;

typedef enum {
    TIME,
    TEMP
} SelectorSetting;

typedef struct {
    OvenState state;
    CookingMode mode;
    SelectorSetting setting;
    int timeRemaining; // in seconds
    int temperature; // in degrees F
    int startTime; // timestamp for when cooking started
    uint8_t buttonEvent;
    uint8_t adcEvent;
    uint8_t timerTickEvent;
} OvenData;

// **** Define any module-level, global, or external variables here ****
static OvenData ovenData; // global oven data
static int freeRunningTimer = 0;

// **** Put any helper functions here ****

/* This function updates the OLED display */
void updateOvenOLED(OvenData ovenData) {
    printf("Updating OLED\n");
    // Clear the OLED display
    OledClear(OLED_COLOR_BLACK);

    // Display cooking mode
    switch (ovenData.mode) {
        case BAKE:
            OledDrawString("Mode: Bake\n");
            break;
        case TOAST:
            OledDrawString("Mode: Toast\n");
            break;
        case BROIL:
            OledDrawString("Mode: Broil\n");
            break;
    }

    // Display temperature if not in Toast mode
    char buffer[32];
    if (ovenData.mode != TOAST) {
        sprintf(buffer, "Temp: %d\n", ovenData.temperature);
        OledDrawString(buffer);
    }

    // Display time remaining
    sprintf(buffer, "Time: %d:%02d\n", ovenData.timeRemaining / 60, ovenData.timeRemaining % 60);
    OledDrawString(buffer);

    // Update the OLED display
    OledUpdate();
    printf("OLED Updated\n");
}

/* This function executes the state machine logic */
void runOvenSM(void) {
    printf("Running State Machine\n");
    switch (ovenData.state) {
        case SETUP:
            printf("State: SETUP\n");
            if (ovenData.buttonEvent & BUTTON_EVENT_3DOWN) {
                // Rotate cooking mode
                printf("Button 3 Down: Rotate Mode\n");
                ovenData.mode = (ovenData.mode + 1) % 3;
                ovenData.buttonEvent &= ~BUTTON_EVENT_3DOWN;
            }
            if (ovenData.buttonEvent & BUTTON_EVENT_4DOWN) {
                // Start cooking
                printf("Button 4 Down: Start Cooking\n");
                ovenData.state = COOKING;
                ovenData.startTime = freeRunningTimer;
                ovenData.buttonEvent &= ~BUTTON_EVENT_4DOWN;
            }
            if (ovenData.adcEvent) {
                // Adjust time or temperature based on ADC value
                uint16_t adcValue = AdcRead();
                printf("ADC Value: %d\n", adcValue);
                if (ovenData.setting == TIME) {
                    ovenData.timeRemaining = ((adcValue >> 2) + 1); // Top 8 bits + 1
                } else if (ovenData.setting == TEMP) {
                    ovenData.temperature = (adcValue >> 2) + 300; // Top 8 bits + 300
                }
                ovenData.adcEvent = 0;
            }
            break;

        case COOKING:
            printf("State: COOKING\n");
            if (ovenData.timerTickEvent) {
                printf("Timer Tick: Decrement Time\n");
                ovenData.timeRemaining--;
                if (ovenData.timeRemaining <= 0) {
                    // Cooking complete
                    printf("Cooking Complete\n");
                    ovenData.state = SETUP;
                    ovenData.timerTickEvent = 0;
                }
            }
            if (ovenData.buttonEvent & BUTTON_EVENT_4DOWN) {
                // Cancel cooking
                printf("Button 4 Down: Cancel Cooking\n");
                ovenData.state = SETUP;
                ovenData.timeRemaining = ovenData.startTime;
                ovenData.buttonEvent &= ~BUTTON_EVENT_4DOWN;
            }
            break;

        case RESET_PENDING:
            printf("State: RESET_PENDING\n");
            ovenData.state = SETUP;
            break;

        case SELECTOR_CHANGE_PENDING:
            printf("State: SELECTOR_CHANGE_PENDING\n");
            ovenData.state = SETUP;
            break;

        default:
            printf("State: DEFAULT\n");
            ovenData.state = SETUP;
            break;
    }

    // Update the OLED display after state transition
    updateOvenOLED(ovenData);
}

int main(void)
{
    BOARD_Init();

    // Initialize the OLED display
    OledInit();
    OledClear(OLED_COLOR_BLACK);
    OledDrawString("OLED Initialized\n");
    OledUpdate();
    printf("OLED Initialized\n");

    // Initialize timers and timer ISRs
    // <editor-fold defaultstate="collapsed" desc="TIMER SETUP">
    
    // Configure Timer 2 using PBCLK as input. We configure it using a 1:16 prescaler, so each timer
    // tick is actually at F_PB / 16 Hz, so setting PR2 to F_PB / 16 / 100 yields a .01s timer.

    T2CON = 0; // everything should be off
    T2CONbits.TCKPS = 0b100; // 1:16 prescaler
    PR2 = BOARD_GetPBClock() / 16 / 100; // interrupt at .01s intervals
    T2CONbits.ON = 1; // turn the timer on

    // Set up the timer interrupt with a priority of 4.
    IFS0bits.T2IF = 0; //clear the interrupt flag before configuring
    IPC2bits.T2IP = 4; // priority of 4
    IPC2bits.T2IS = 0; // subpriority of 0 arbitrarily 
    IEC0bits.T2IE = 1; // turn the interrupt on

    // Configure Timer 3 using PBCLK as input. We configure it using a 1:256 prescaler, so each timer
    // tick is actually at F_PB / 256 Hz, so setting PR3 to F_PB / 256 / 5 yields a .2s timer.

    T3CON = 0; // everything should be off
    T3CONbits.TCKPS = 0b111; // 1:256 prescaler
    PR3 = BOARD_GetPBClock() / 256 / 5; // interrupt at .2s intervals
    T3CONbits.ON = 1; // turn the timer on

    // Set up the timer interrupt with a priority of 4.
    IFS0bits.T3IF = 0; //clear the interrupt flag before configuring
    IPC3bits.T3IP = 4; // priority of 4
    IPC3bits.T3IS = 0; // subpriority of 0 arbitrarily 
    IEC0bits.T3IE = 1; // turn the interrupt on;

    // </editor-fold>
   
    printf("Welcome to Rahil's Lab07 (Toaster Oven).  Compiled on %s %s.\n", __TIME__, __DATE__);

    // Initialize state machine and oven data
    ovenData.state = SETUP;
    ovenData.mode = BAKE;
    ovenData.setting = TIME;
    ovenData.timeRemaining = 60; // default 1 minute
    ovenData.temperature = 350; // default 350 degrees

    // Initialize LEDs
    LEDS_INIT();

    while (1){
        // Check for events and run state machine
        printf("Looping\n");
        if (ovenData.buttonEvent || ovenData.adcEvent || ovenData.timerTickEvent) {
            printf("Event Detected: Button Event=%d, ADC Event=%d, Timer Tick Event=%d\n",
                   ovenData.buttonEvent, ovenData.adcEvent, ovenData.timerTickEvent);
            runOvenSM();
            // Clear event flags
            ovenData.buttonEvent = 0;
            ovenData.adcEvent = 0;
            ovenData.timerTickEvent = 0;
        }
    }
}

/* The 5Hz timer is used to update the free-running timer and to generate TIMER_TICK events */
void __ISR(_TIMER_3_VECTOR, ipl4auto) TimerInterrupt5Hz(void)
{
    // Clear the interrupt flag.
    IFS0CLR = 1 << 12;

    // Increment the free running timer
    freeRunningTimer++;

    // Set the timer tick event flag
    ovenData.timerTickEvent = 1;
    printf("5Hz Timer Interrupt: Timer Tick Event Set\n");
}

/* The 100Hz timer is used to check for button and ADC events */
void __ISR(_TIMER_2_VECTOR, ipl4auto) TimerInterrupt100Hz(void)
{
    // Clear the interrupt flag.
    IFS0CLR = 1 << 8;

    // Checking for button and ADC events
    uint8_t buttonStates = BUTTON_STATES();
    printf("Button States: %d\n", buttonStates);
    ovenData.buttonEvent = ButtonsCheckEvents();
    ovenData.adcEvent = AdcChanged();
    printf("100Hz Timer Interrupt: Button Event=%d, ADC Event=%d\n", ovenData.buttonEvent, ovenData.adcEvent);
}
