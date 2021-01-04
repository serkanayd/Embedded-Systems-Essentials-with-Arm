#include "mbed.h"

DigitalIn START (p5); // START Button, start = 1 (Push Button (p5))
DigitalIn GUARD (p6); // GUARD Sensor, guard closed = 1 (Switch (p6))
DigitalIn TEMP (p7); // TEMPERATURE Senson, excess temp = 1 (Switch (p7))
DigitalIn STOP (p8); // STOP Button, stop = 1 (Push Button (p9))

DigitalOut READY (p9); // Motor is ready to run - Yellow Led
DigitalOut RUNNING (p10); // Motor is running - White Led
DigitalOut FAULT (p11); // Guard opened while motor running - Blue Led
DigitalOut EXCES (p12); // excess temperature - Red Led


int main() {
    
    while (1) {
        while( GUARD == 0 || TEMP == 1) {
            RUNNING = FAULT = EXCES = 0; // Clear all leds
            READY = !READY; // Flash ready, Motor is not ready
            wait(0.2);
        }

        READY = 1; // Motor is ready to run, WHITE_LED

	    while( START == 0) // Wait for START to pressed
	        wait(0.2);
	
	    // Start and Run the motor
	    while( GUARD == 1 && TEMP == 0 && STOP == 0 ){
	        READY = 0;
	        RUNNING = 1;
	        wait(0.2);
	    }  
	    
	    // here if motor to stop, determine and act on cause
	    if(GUARD == 0) {
	       RUNNING = 0;
	       FAULT = 1; // BLUE_LED
	       wait(0.5);
	       FAULT = 0;
	    }
	    if(TEMP == 1){
	       RUNNING = 0;
	       EXCES = 1; // RED_LED
	       wait(0.5);
	       EXCES = !EXCES;
	    }
	    if(STOP == 1)
	       RUNNING = 0; // WHITE_LED
    } //end of the while(1)
}
