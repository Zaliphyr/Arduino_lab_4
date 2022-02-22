// Include libraries
#include <Wire.h>
#include <Zumo32U4.h>

// Give components easier names
Zumo32U4ButtonA buttonA;
Zumo32U4Buzzer buzzer;
Zumo32U4LineSensors lineSensor;
Zumo32U4Motors motors;
Zumo32U4LCD lcd;

// Values needed for line follower
int pos;
unsigned int linesensorValues[5];
int error;

void setup() {
  // Start sensors
  lineSensor.initFiveSensors();

  // Start LCD
  lcd.init();

  // Display starting screen
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Press A");
  lcd.setCursor(0,1);
  lcd.print("to calb");

  // When button gets pressed, start the calibration sequence
  buttonA.waitForButton();
  lcd.clear();
  cal();
  delay(1000);
  lcd.setCursor(0,0);
  lcd.print("Calb");
  lcd.setCursor(0,1);
  lcd.print("Done");
  delay(1000);
  lcd.setCursor(0,0);
  lcd.print("Press A");
  lcd.setCursor(0,1);
  lcd.print("to run");

  // After calibration, waits for button press before starting linefollower
  buttonA.waitForButton();
  buzzer.playFrequency(440, 500, 8);
  delay(1000);
}

void loop() {
  // Get readings from linesensor
  pos = lineSensor.readLine(linesensorValues);
  error = pos - 2000;

  // Prints error value to screen
  // 0 means line is in middle
  // negative means line is to the left
  // positive means line is ti the right
  lcd.clear();
  lcd.print(error);

  // turn car in the direction of the line
  if (error > -200 && error < 200){
    motors.setSpeeds(100, 100);
  }else if (error < -200){
    motors.setSpeeds(50, 200);
  } else if (error > 200){
    motors.setSpeeds(200, 50);
  }
}

// Calibration function
// Turns car left and right while calibrating the linesensor
void cal(){
  delay(1000);
  for (int i = 0; i <= 120; i++){
    if (i > 30 && i <= 90){
      motors.setSpeeds(-150, 150);
    } else {
      motors.setSpeeds(150, -150);
    }
    lineSensor.calibrate();
  }
  motors.setSpeeds(0, 0);
}
