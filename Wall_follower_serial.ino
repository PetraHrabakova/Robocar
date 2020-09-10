int IN1 = 5;
int IN2 = 6;
int IN3 = 9;
int IN4 = 3;
int pwd1 = 100;
int pwd2 = 180;

#include <Wire.h>
#include <VL53L1X.h>

VL53L1X sensor;


void setup() {
  Serial.begin(115200);
  Wire.begin();
  Wire.setClock(400000);


  sensor.setTimeout(100);
  if (!sensor.init())
  {
    Serial.println("Failed to detect and initialize sensor!");
    while (1);
  }

  sensor.setDistanceMode(VL53L1X::Short);
  sensor.setMeasurementTimingBudget(50000);

  sensor.startContinuous(25);

  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);


}

int myGetchar ()
{
  int x;

  while ((x = Serial.read()) == -1)
    ;

  return x ;
}


void moveForward()
{
  digitalWrite(IN3, LOW);
  analogWrite(IN4, pwd1);
  analogWrite(IN1, pwd1);
  digitalWrite(IN2, LOW);
}

void turnLeft()
{
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

void readSensor() {
  if (sensor.dataReady()){
  Serial.println(sensor.read());
  }
  //  Serial.print("range: ");
  //Serial.println(sensor.ranging_data.range_mm);
  //  Serial.print("\tstatus: ");
  //  Serial.print(VL53L1X::rangeStatusToString(sensor.ranging_data.range_status));

  //  Serial.println();
}


void loop() {

  readSensor();
  //sensor.read();
  if (Serial.available() > 0) {

    int c;
    c = myGetchar();
    if (c == 'a')
    {
      moveForward();
    }
    if (c == 'b')
    {
      turnLeft();
    }
    if (c == 'c')
    {
      turnRight();
    }
  }
}
