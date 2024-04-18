/* Servo sweep
 * Rev.2
 *  Copyright yo3hjv https://yo3hjv.blogspot.com
     The user can define:
    -Servo command pin (use one able to do PWM)
    -Initial position (degrees);
    -Target 1 position (150 degrees)
    -Target 2 position (20 degrees)
    -Step in degrees
    -Time per each step
    -Wait time.

I used a finite state machine to define the positions and the timings

  Stage 1: servo at 90 degree. 
  Stage 2: Move to 150 degree, one step per stepTime
  Stage 3: Wait 3 seconds (waitTime) at 150 degree. 
  Stage 4: Move to 90 degree, one step per stepTime
  Stage 5: Wait 3 seconds (waitTime)
  Stage 6: move to 30 degree, one step per stepTime
  Stage 7: Wait 3 seconds (waitTime). 
  Stage 8: move to 90 degrees, one step per stepTime 
  Stage 9: Wait 3 seconds (waitTime). Go to Stage 1.
*/



#include <Servo.h>
#define servoPin 3  // Command pin for servo 
Servo myServo; // Create a servo object

unsigned long stageStartTime = 0; // Variable to store the start time of each stage

//USER DEFINED PARAMETERS
      int referencePosition = 90;      // Reference position of the servo
      int targetPosition1 = 150;       // Target position for stage 2 (90 + 60) degrees
      int targetPosition2 = 20;        // Target position for stage 6 (90 - 60) degrees
      unsigned int stepSize = 1;       // Step size for servo movement in degrees
      unsigned long stepTime = 300;    // Time duration for each step in milliseconds (1 second)
      unsigned long waitTime = 5;      // Wait duration in seconds

int currentStage = 0; // Variable to track the current stage
int currentPosition = 0; // Variable to store current position of the servo

void setup() {
              Serial.begin(9600);                     // Initialize serial communication
              myServo.attach(servoPin);     // 
              myServo.write(referencePosition);       // Set initial position to the reference position
              currentPosition = referencePosition;    // Initialize currentPosition
              delay(500);
              stageStartTime = millis(); // Record the start time
}

void loop() {
                    unsigned long currentMillis = millis(); // Get the current time
                    
                    // Convert waitTime to seconds
                    unsigned long waitTimeMillis = waitTime * 1000;
                    
                    // Check the current stage
                    switch (currentStage) {
                      case 0: // Stage 1: Wait 30 seconds
                        if (currentMillis - stageStartTime >= waitTimeMillis) {
                          currentStage = 1;                   // Move to next stage
                          stageStartTime = currentMillis;     // Record the start time of the next stage
                        }
                        break;
                  
                      case 1: // Stage 2: Move to targetPosition1, one degree per step
                        if (currentMillis - stageStartTime >= stepTime) {
                          currentPosition += stepSize;
                          myServo.write(currentPosition);
                          stageStartTime = currentMillis;     // Record the start time of the next step
                        }
                        if (currentPosition >= targetPosition1) {
                          currentStage = 2;                   // Move to next stage
                          stageStartTime = currentMillis;     // Record the start time of the next stage
                        }
                        break;
                  
                      case 2: // Stage 3: Wait 30 seconds
                        if (currentMillis - stageStartTime >= waitTimeMillis) {
                          currentStage = 3;                   // Move to next stage
                          stageStartTime = currentMillis;     // Record the start time of the next stage
                        }
                        break;
                  
                      case 3: // Stage 4: Move back to referencePosition, one degree per step
                        if (currentMillis - stageStartTime >= stepTime) {
                          currentPosition -= stepSize;
                          myServo.write(currentPosition);
                          stageStartTime = currentMillis;     // Record the start time of the next step
                        }
                        if (currentPosition <= referencePosition) {
                          currentStage = 4;                   // Move to next stage
                          stageStartTime = currentMillis;     // Record the start time of the next stage
                        }
                        break;
                  
                      case 4: // Stage 5: Wait 30 seconds
                        if (currentMillis - stageStartTime >= waitTimeMillis) {
                          currentStage = 5;                   // Move to next stage
                          stageStartTime = currentMillis;     // Record the start time of the next stage
                        }
                        break;
                  
                      case 5: // Stage 6: Move to targetPosition2, one degree per step
                        if (currentMillis - stageStartTime >= stepTime) {
                          currentPosition -= stepSize;
                          myServo.write(currentPosition);
                          stageStartTime = currentMillis;     // Record the start time of the next step
                        }
                        if (currentPosition <= targetPosition2) {
                          currentStage = 6;                   // Move to next stage
                          stageStartTime = currentMillis;     // Record the start time of the next stage
                        }
                        break;
                  
                      case 6: // Stage 7: Wait 30 seconds
                        if (currentMillis - stageStartTime >= waitTimeMillis) {
                          currentStage = 7;                   // Move to next stage
                          stageStartTime = currentMillis;     // Record the start time of the next stage
                        }
                        break;
                  
                      case 7: // Stage 8: Move back to referencePosition, one degree per step
                        if (currentMillis - stageStartTime >= stepTime) {
                          currentPosition += stepSize;
                          myServo.write(currentPosition);
                          stageStartTime = currentMillis;     // Record the start time of the next step
                        }
                        if (currentPosition >= referencePosition) {
                          currentStage = 0;                   // Move back to Stage 1
                          stageStartTime = currentMillis;     // Record the start time of the next loop
                        }
                        break;
                    }
}
