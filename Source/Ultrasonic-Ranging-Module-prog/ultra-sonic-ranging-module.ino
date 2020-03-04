/*Operation of an ultrasonic sensor HC-SR04 */

/*
- Connect the pin Vcc to 5V.
- Connect the pin Trig on the PIN 2. 
- Connect the pin Echo on the PIN 3. 
- Connect the pin GND on the PIN 4 .
*/

int trig = 2;
int echo = 3;
long lecture_echo;
long cm;

void setup(){

pinMode(trig, OUTPUT);
digitalWrite(trig, LOW);
pinMode(echo, INPUT);
Serial.begin(9600);

}

void loop(){

digitalWrite(trig, HIGH);
delayMicroseconds(10);
digitalWrite(trig, LOW);
lecture_echo = pulseIn(echo,HIGH);
cm = lecture_echo /58;
Serial.print("Distance en cm :");
Serial.println(cm);
delay(1500);
}
