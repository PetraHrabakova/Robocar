#include <Servo.h>
#include <Wire.h>
#include <VL53L1X.h>

Servo name_servo;
VL53L1X sensor;

int pos = 0;    // variable to store the servo position
int IN1 = 5; 
int IN2 = 6; 
int IN3 = 9; 
int IN4 = 3;
int pwd1 = 100;
int pwd2 = 230;

void setup() {

  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  
  name_servo.attach(10);  // attaches the servo on pin 10 to the servo object
  Serial.begin(115200);
  Wire.begin();
  Wire.setClock(400000);

  sensor.setTimeout(500);
  if (!sensor.init())
  {
    Serial.println("Failed to detect and initialize sensor!");
    while (1);
  }

  sensor.setDistanceMode(VL53L1X::Short);
  sensor.setMeasurementTimingBudget(20000);

  sensor.startContinuous(50);
}


void moveForward(){
  digitalWrite(IN3, LOW);
  analogWrite(IN4, pwd1);
  analogWrite(IN1, pwd1);
  digitalWrite(IN2, LOW);
}
 
void turnLeft(){
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  analogWrite(IN4, pwd2); 
}
 
void turnRight() {
  analogWrite(IN1, pwd2);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
}



void readSensor(){
  sensor.read();
  Serial.println("range: ");
  Serial.print(sensor.ranging_data.range_mm);
  Serial.print("\tstatus: ");
  Serial.print(VL53L1X::rangeStatusToString(sensor.ranging_data.range_status));
}

void loop()
  {
  for (pos = 40; pos <= 130; pos += 10) { // goes from 40 degrees to 130 degrees
    // in steps of 10 degree
    name_servo.write(pos);              // tell servo to go to position in variable 'pos'
    readSensor();
    delay(50);              // waits 50ms for the servo to reach the position
  }
  for (pos = 130; pos >= 40; pos -= 10) { // goes from 130 degrees to 40 degrees
    name_servo.write(pos);              // tell servo to go to position in variable 'pos'
    readSensor();
    delay(50);                       // waits 50ms for the servo to reach the position
  } 
  readSensor();
  sensor.read();
  if (sensor.ranging_data.range_mm > 400) {
    moveForward();
  }
  if (sensor.ranging_data.range_mm < 400) {
    turnLeft();
    delay(100);
  }
}
