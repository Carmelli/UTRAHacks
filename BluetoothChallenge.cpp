#include <SoftwareSerial.h> //for serial communication
char t;
SoftwareSerial hc06(0,1); 
//Check https://docs.arduino.cc/learn/built-in-libraries/software-serial
String cmd = "";

void setup() {
Serial.begin(9600);
hc06.begin(9600);
}
 
void loop() {
//Read data from HC06/*
 	if(Serial.available()){
     /*At the start of each loop iteration, check to see if 
     there is a new value for t by reading from the serial*/
  t = Serial.read();
  Serial.println(t);
}

  which was built in on the app. You will likely have to program
  what values are sent via the serial in other projects
  
  What these control conditions do is that they will 
  'turn on' certain motors (via analog write)
  then delay for 30 ms, then stop those motors.
  
  Writing to a pin (analog or digital) in this case
  will write a value, then will not change that
  value until you tell in to. Delaying for a little
  bit allowed us to hold down a button whenever we 
  wanted to do a certain movement, and Pikachu would
  move for as long as we held the button.
  If we did not have the delay, then Pikachu would
  not actually move, because the program would
  quickly switch between writing a value to the pins
  and then writing 0 to the pins.*/
   if(t == 'F'){  
  //forward(all motors rotate in forward direction)
  analogWrite(5,112);
  analogWrite(11,92); 
  delay(30);
  analogWrite(5,0);
  analogWrite(11,0); 
}
else if(t == 'B'){      //move reverse (all
  //motors rotate in reverse direction)
  analogWrite(6,92);
  analogWrite(11,92);
  delay(30);
  analogWrite(6,0);
  analogWrite(11,0);
}

else if(t == 'L'){
  analogWrite(6,112);
  delay(30);
  analogWrite(6, 0);
}
 
else
  if(t == 'R'){
  analogWrite(5,112);
  delay(30);
  analogWrite(5, 0);
}

}