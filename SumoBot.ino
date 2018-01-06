

#include <Ultrasonic.h>
#include <AFMotor.h>

#define ldr1 A5
#define ldr2 A4
int ldrValue1 = 0;
int ldrValue2 = 0;
int frontBlack = 0, backBlack = 0;
int count = 0;
bool turnedRight = false;
Ultrasonic frontSensor(16, 17);
Ultrasonic backSensor(14, 15);
// Motors
AF_DCMotor rightMotor(3, MOTOR12_64KHZ);
AF_DCMotor leftMotor(4, MOTOR12_64KHZ);

void setup() {
  Serial.begin(9600);
  rightMotor.setSpeed(200);
  leftMotor.setSpeed(200);
  frontBlack = analogRead(ldr1) + 20;
  backBlack = analogRead(ldr2) + 20;
}

void ramFront()
{
  rightMotor.setSpeed(225);
  leftMotor.setSpeed(255);
  rightMotor.run(FORWARD);
  leftMotor.run(FORWARD);
}

void ramBack()
{
  rightMotor.setSpeed(255);
  leftMotor.setSpeed(255);
  rightMotor.run(BACKWARD);
  leftMotor.run(BACKWARD);
}

void turnLeft ()
{
  rightMotor.setSpeed(175);
  leftMotor.setSpeed(175);
  rightMotor.run(FORWARD);
  leftMotor.run(BACKWARD);
}

void turnRight() {
  rightMotor.setSpeed(200);
  leftMotor.setSpeed(200);
  rightMotor.run(BACKWARD);
  leftMotor.run(FORWARD);
  Serial.println("right");
  delay(200);
}

void loop() {
  ldrValue1 = analogRead(ldr1); // front ldr
  ldrValue2 = analogRead(ldr2); // back ldr
  Serial.print("front ldr:");
  Serial.print("  ");
  Serial.print(ldrValue1);
  Serial.print("\t");
  Serial.print("back ldr:");
  Serial.print("  ");
  Serial.print(ldrValue2);
  Serial.print("\tback ultrasonic    ");
  Serial.print(backSensor.distanceRead(CM));
  Serial.print("\tfront ultrasonic    ");
  Serial.print(frontSensor.distanceRead(CM));
  Serial.print("    \t");
  Serial.print("BACK black:  ");
  Serial.print(backBlack);
  Serial.print("\t");
  Serial.print("front black:  ");
  Serial.print(frontBlack);
  Serial.print("\t");

  if (analogRead(ldr1) > frontBlack)
  {
    Serial.println("GO BACKWARDS");
    count = 0;
    ramBack();
    delay(1000);
  }
  else if (analogRead(ldr2) > backBlack)
  {
    Serial.println("GO FORWARDS");
    count = 0;
    ramFront();
    delay(1000);
  } else if (count > 50) {
    ramFront();
    count = 0;
    delay(500);
  } else
  {
    if (frontSensor.distanceRead(CM) > 0 && frontSensor.distanceRead(CM) < 65)
    {
      Serial.println(" FORWARDS");
      count = 0;
      ramFront();
      delay(500);

    }
    else if  (backSensor.distanceRead(CM) > 0 && backSensor.distanceRead(CM) < 65)
    {
      Serial.println("BACKWARDS");
      count = 0;
      ramBack();
      delay(500);

    }
    else
    {
      Serial.println("left");
      count+= 1;
      turnedRight = false;
      turnLeft();
    }
  }
  delay(1);
}

