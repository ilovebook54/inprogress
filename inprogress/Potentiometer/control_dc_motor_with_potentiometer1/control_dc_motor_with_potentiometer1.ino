int potPin = A0;
int motorPin = 9;
int potValue = 0;
int motorValue = 0;
int MotorPin = 6;
//int MotorPin2
void setup() {
 Serial.begin(9600);
}
void loop() {
 potValue = analogRead(potPin);  
 motorValue = map(potValue, 0, 1023, 0, 255);
 analogWrite(motorPin, motorValue);  
 Serial.print("potentiometer = " );     
 Serial.print(potValue);
 Serial.print("t motor = ");
 Serial.println(motorValue);
 analogWrite(MotorPin , potValue); //Added
 delay(2);    
 
}