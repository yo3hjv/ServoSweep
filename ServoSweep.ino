/* Servo sweep user defined
   Release.
 *  User defined stepts in degrees.
 *  Copyright yo3hjv https://yo3hjv.blogspot.com
 
Stage 1: servo at 90 degree. 
Stage 2: Move to 150 degree, one step per stepTime
Stage 3: Wait 3 seconds (waitTime) at 150 degree. 
Stage 4: Move to 90 degree, one step per stepTime
Stage 5: Wait 3 seconds (waitTime)
Stage 6: move to 30 degree, one step per stepTime
Stage 7: Wait 3 seconds (waitTime). 
Stage 8: move to 90 degrees, one step per stepTime 
Stage 9: Wait 3 seconds (waitTime). Go to Stage 1.

The user can define:
-Initial position;
-Target 1 position (150 degrees) 
-Target 2 position (30 degrees)
-Step in degrees
-Time per each step
-Wait time.
    and can choose how the sweep start (to Pos 1 or to Pos 2)
*/



#include <Servo.h>
#define servoPin 3  // Command pin for servo 
Servo myServo; // Create a servo object

unsigned long stageStartTime = 0; // Variable to store the start time of each stage

//USER DEFINED PARAMETERS
      int referencePosition = 90; // Reference position of the servo
      int targetPosition1 = 170; // Target position (always higher than referencePosition) for stage 2 (90 + 60) degrees
      int targetPosition2 = 15;  // Target position (always lower than referencePosition) for stage 6 (90 - 60) degrees
      unsigned int stepSize = 1; // Step size for servo movement in degrees
      unsigned long stepTime = 100;    // Time duration for each step in milliseconds (1 second)
      unsigned long waitTime = 2;      // Wait duration in seconds

int currentStage = 0; // Variable to track the current stage
int currentPosition = 0; // Variable to store current position of the servo

void setup() {
            Serial.begin(9600); // Initialize serial communication
            myServo.attach(servoPin); // 
              myServo.write(referencePosition); // Set initial position to the reference position
              currentPosition = referencePosition; // Initialize currentPosition
              delay(500);
            stageStartTime = millis(); // Record the start time
}

void loop() {
                  //Leave just one line uncommented depending on how the sweep start
             //     tP1toTp2();      //from High to Low
                    tP2toTp1();      //from Low to High

            // Here other code to be executed without blocking
 
}

void tP2toTp1(){
                    unsigned long currentMillis = millis(); // Get the current time
                    
                    // Convert waitTime to milliseconds
                    unsigned long waitTimeMillis = waitTime * 1000;
                    
                    // Check the current stage
                    switch (currentStage) {
                      case 0: // Stage 1: Wait 30 seconds
                        if (currentMillis - stageStartTime >= waitTimeMillis) {
                          currentStage = 1; // Move to next stage
                          stageStartTime = currentMillis; // Record the start time of the next stage
                        }
                        break;
                  
                      case 1: // Stage 2: Move to 150 degrees, one degree per step
                        if (currentMillis - stageStartTime >= stepTime) {
                          currentPosition += stepSize;
                          myServo.write(currentPosition);
                          stageStartTime = currentMillis; // Record the start time of the next step
                        }
                        if (currentPosition >= targetPosition1) {
                          currentStage = 2; // Move to next stage
                          stageStartTime = currentMillis; // Record the start time of the next stage
                        }
                        break;
                  
                      case 2: // Stage 3: Wait 30 seconds
                        if (currentMillis - stageStartTime >= waitTimeMillis) {
                          currentStage = 3; // Move to next stage
                          stageStartTime = currentMillis; // Record the start time of the next stage
                        }
                        break;
                  
                      case 3: // Stage 4: Move back to 90 degrees, one degree per step
                        if (currentMillis - stageStartTime >= stepTime) {
                          currentPosition -= stepSize;
                          myServo.write(currentPosition);
                          stageStartTime = currentMillis; // Record the start time of the next step
                        }
                        if (currentPosition <= referencePosition) {
                          currentStage = 4; // Move to next stage
                          stageStartTime = currentMillis; // Record the start time of the next stage
                        }
                        break;
                  
                      case 4: // Stage 5: Wait 30 seconds
                        if (currentMillis - stageStartTime >= waitTimeMillis) {
                          currentStage = 5; // Move to next stage
                          stageStartTime = currentMillis; // Record the start time of the next stage
                        }
                        break;
                  
                      case 5: // Stage 6: Move to 30 degrees, one degree per step
                        if (currentMillis - stageStartTime >= stepTime) {
                          currentPosition -= stepSize;
                          myServo.write(currentPosition);
                          stageStartTime = currentMillis; // Record the start time of the next step
                        }
                        if (currentPosition <= targetPosition2) {
                          currentStage = 6; // Move to next stage
                          stageStartTime = currentMillis; // Record the start time of the next stage
                        }
                        break;
                  
                      case 6: // Stage 7: Wait 30 seconds
                        if (currentMillis - stageStartTime >= waitTimeMillis) {
                          currentStage = 7; // Move to next stage
                          stageStartTime = currentMillis; // Record the start time of the next stage
                        }
                        break;
                  
                      case 7: // Stage 8: Move back to 90 degrees, one degree per step
                        if (currentMillis - stageStartTime >= stepTime) {
                          currentPosition += stepSize;
                          myServo.write(currentPosition);
                          stageStartTime = currentMillis; // Record the start time of the next step
                        }
                        if (currentPosition >= referencePosition) {
                          currentStage = 0; // Move back to Stage 1
                          stageStartTime = currentMillis; // Record the start time of the next loop
                        }
                        break;
                    }
}






void tP1toTp2(){
   //targetPosition2 to targetPosition1 sweep
                    unsigned long currentMillis = millis(); // Get the current time
                    
                    // Convert waitTime to milliseconds
                    unsigned long waitTimeMillis = waitTime * 1000;
                    
                    // Check the current stage
                    switch (currentStage) {
                      
                      case 0: // Stage 1: Wait 30 seconds
                        if (currentMillis - stageStartTime >= waitTimeMillis) {
                          currentStage = 1; // Move to next stage
                          stageStartTime = currentMillis; // Record the start time of the next stage
                        }
                        break;
                  
                      case 1: // Stage 2: ref to TargetPosition2, one degree per step
                        if (currentMillis - stageStartTime >= stepTime) {
                          currentPosition -= stepSize;
                          myServo.write(currentPosition);
                          stageStartTime = currentMillis; // Record the start time of the next step
                        }
                        if (currentPosition <= targetPosition2) {
                          currentStage = 2; // Move to next stage
                          stageStartTime = currentMillis; // Record the start time of the next stage
                        }
                        break;
                  
                      case 2: // Stage 3: Wait 30 seconds in targetPosition2
                        if (currentMillis - stageStartTime >= waitTimeMillis) {
                          currentStage = 3; // Move to next stage
                          stageStartTime = currentMillis; // Record the start time of the next stage
                        }
                        break;
                  
                      case 3: // Stage 4: Move back to referencePosition, one degree per step
                        if (currentMillis - stageStartTime >= stepTime) {
                          currentPosition += stepSize;
                          myServo.write(currentPosition);
                          stageStartTime = currentMillis; // Record the start time of the next step
                        }
                        if (currentPosition >= referencePosition) {
                          currentStage = 4; // Move to next stage
                          stageStartTime = currentMillis; // Record the start time of the next stage
                        }
                        break;
                  
                      case 4: // Stage 5: Wait 30 seconds in referencePosition
                        if (currentMillis - stageStartTime >= waitTimeMillis) {
                          currentStage = 5; // Move to next stage
                          stageStartTime = currentMillis; // Record the start time of the next stage
                        }
                        break;
                  
                      case 5: // Stage 6: Move to targetPostition 1 degrees, one degree per step
                        if (currentMillis - stageStartTime >= stepTime) {
                          currentPosition += stepSize;
                          myServo.write(currentPosition);
                          stageStartTime = currentMillis; // Record the start time of the next step
                        }
                        if (currentPosition >= targetPosition1) {
                          currentStage = 6; // Move to next stage
                          stageStartTime = currentMillis; // Record the start time of the next stage
                        }
                        break;
                  
                      case 6: // Stage 7: Wait 30 seconds in targetPosition1
                        if (currentMillis - stageStartTime >= waitTimeMillis) {
                          currentStage = 7; // Move to next stage
                          stageStartTime = currentMillis; // Record the start time of the next stage
                        }
                        break;
                  
                      case 7: // Stage 8: Move back to 90 degrees, one degree per step
                        if (currentMillis - stageStartTime >= stepTime) {
                          currentPosition -= stepSize;
                          myServo.write(currentPosition);
                          stageStartTime = currentMillis; // Record the start time of the next step
                        }
                        if (currentPosition <= referencePosition) {
                          currentStage = 0; // Move back to Stage 1
                          stageStartTime = currentMillis; // Record the start time of the next loop
                        }
                        break;
                    }
}
