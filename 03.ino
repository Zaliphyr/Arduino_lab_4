#include <Wire.h>
#include <Zumo32U4.h>

Zumo32U4ButtonA buttonA;
Zumo32U4Buzzer buzzer;
Zumo32U4LineSensors lineSensor;
Zumo32U4Motors motors;
Zumo32U4LCD lcd;

int pos;
unsigned int linesensorValues[5];
int error;

void setup() {
  lineSensor.initFiveSensors();
  
  lcd.init();
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Press A");
  lcd.setCursor(0,1);
  lcd.print("to calb");
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
  buttonA.waitForButton();
  buzzer.playFrequency(440, 500, 8);
  delay(1000);
}

void loop() {
  pos = lineSensor.readLine(linesensorValues);
  error = pos - 2000;
  lcd.clear();
  lcd.print(error);

  if (error > -200 && error < 200){
    motors.setSpeeds(100, 100);
  }else if (error < -200){
    motors.setSpeeds(50, 200);
  } else if (error > 200){
    motors.setSpeeds(200, 50);
  }
}

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
