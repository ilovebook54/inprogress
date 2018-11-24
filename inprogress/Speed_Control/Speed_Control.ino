/*Arduino code for ir remote control car using the TSOP1738 ir sensor.
  Decode the button code, match and move robot according to button hex value.
  For deocoding the hex values we use IRremote: IRrecvDemo.ino sketch from
  https://www.pjrc.com/teensy/td_libs_IRremote.html.
  By www.maxphi.com
*/

#include <IRremote.h>
#include "pins_arduino.h"
int RECV_PIN = 11;//Pin should be PWM
int MAX_DISTANCE = 38;
const int trigPin = 1;
const int echoPin = 2;
int carspeed = 255;


IRrecv irrecv(RECV_PIN);

decode_results results;
/*
int potPin = A0;
int motorPin = 9;
int potValue = 0;
int motorValue = 0;
*/
//NewPing sonar(trigPin, echoPin, MAX_DISTANCE); // NewPing setup of pins and maximum distance.



long duration;
int distance;

void function_ultrasonic();


void setup()
{
  irrecv.enableIRIn(); // Start the receiver
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(7, OUTPUT);
  pinMode(8, OUTPUT);
  pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
  pinMode(echoPin, INPUT); // Sets the echoPin as an Input
  Serial.begin(9600); // Starts the serial communication
}
void loop()
{
  /*
  potValue = analogRead(potPin);  
 motorValue = map(potValue, 0, 1023, 0, 255);
 analogWrite(motorPin, motorValue);  
 Serial.print("potentiometer = " );     
 Serial.print(potValue);
 Serial.print("t motor = ");
 Serial.println(motorValue);
 delay(2);    
*/
  function_ultrasonic();

  if (irrecv.decode(&results))
  {
    switch (results.value)
    {
      case 0xFD50AF:  Serial.println("Forward"); // Button 2
        function_ultrasonic();
        analogWrite(5, 0);
        analogWrite(6, carspeed);
        analogWrite(7, 0);
        analogWrite(8, carspeed);
        function_ultrasonic();
        break;
      case 0xFD10EF:  Serial.println("Backwards"); // Button 4
        function_ultrasonic();
        analogWrite(5, carspeed);
        analogWrite(6, 0);
        analogWrite(7, carspeed);
        analogWrite(8, 0);
        function_ultrasonic();
        break;
      case 0xFD00FF:  Serial.println("Stop"); // Button 5
        function_ultrasonic();
        analogWrite(5, 0);
        analogWrite(6, 0);
        analogWrite(7, 0);
        analogWrite(8, 0);
        function_ultrasonic();
        break;
      case 0xFD08F7:  Serial.println("Turn"); // Button 6
        function_ultrasonic();
        analogWrite(5, carspeed);
        analogWrite(6, carspeed);
        analogWrite(7, 0);
        analogWrite(8, carspeed);
        function_ultrasonic();
        break;

      case 0xFD807F: Serial.println("Car speed up");

        carspeed++;
        Serial.println(carspeed);
        break;


      case 0xFD906F: Serial.println("Car speed down");

        carspeed = carspeed - 500;
        Serial.println(carspeed);

    }



    irrecv.resume(); // Receive the next value
  }
}


void function_ultrasonic ()
{

  // Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(echoPin, HIGH);

  // Calculating the distance
  distance = duration * 0.034 / 2;

  // Prints the distance on the Serial Monitor
  Serial.print("Distance: ");
  Serial.println(distance);

  if (distance <= 17)
  {
    Serial.println("Ultrasonic");
    digitalWrite(5, LOW);
    digitalWrite(6, LOW);
    digitalWrite(7, LOW);
    digitalWrite(8, LOW);
  }


  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
}
