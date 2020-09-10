const int IN1 = 5; 
const int IN2 = 6; 
const int IN3 = 9; 
const int IN4 = 3;
const int pwd = 180;



void setup() {
  Serial.begin(9600);
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

void Forward(){

  digitalWrite(IN3, LOW);
  analogWrite(IN4, pwd);
  analogWrite(IN1, pwd);
  digitalWrite(IN2, LOW);
}

void Backwards(){

  analogWrite(IN3, pwd);
  digitalWrite(IN4, LOW);
  digitalWrite(IN1, LOW);
  analogWrite(IN2, pwd);

}

void turnLeft() {
  digitalWrite(IN1, LOW);
  analogWrite(IN2, pwd);
  digitalWrite(IN3, LOW);
  analogWrite(IN4, pwd); 
}

void turnRight() {
  analogWrite(IN1, pwd);
  digitalWrite(IN2, LOW);
  analogWrite(IN3, pwd);
  digitalWrite(IN4, LOW);
}

void Stop() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
  
}


void loop() {

 int c;
  c = myGetchar();
  if (c == 'W')
  {
    Forward();
  }

  if (c == 'S')
  { 
    Backwards();
  }

  if (c == 'A')
  {
    turnLeft();
  }

  if (c == 'D')
  {
    turnRight();
  }

  if (c == 'B')
  {
    Stop();
  }
  
}
