const int TRIGPIN = 9;
const int ECHOPIN = 8;
const int IRPIN1 = 4;
const int IRPIN2 = 2;
const int BUTTONPIN = 7; //need to define pin
//const int MAX_ROTATION_DIFF = 5;
int buttonState = LOW;
int irstate1 = LOW;
int irstate2 = LOW;
long duration;
long cm;
int calibrate;
bool move = true;
long rotation_count1 = 0;
long rotation_count2 = 0;


void setup(){
    //for ultrasonic sensor
    pinMode(TRIGPIN, OUTPUT); 
    pinMode(ECHOPIN, INPUT); 
    //start button
    pinMode(BUTTONPIN, OUTPUT);

    //infrared sensors
    pinMode(IRPIN1, INPUT);
    pinMode(IRPIN2, INPUT);
    Serial.begin(9600); 

}

int get_distance_cm () {
   
    digitalWrite(TRIGPIN, LOW);
    delayMicroseconds(5);
    digitalWrite(TRIGPIN, HIGH);
    delayMicroseconds(10);
    digitalWrite(TRIGPIN, LOW);
    duration = pulseIn(ECHOPIN, HIGH); //pulseIn is a timer function to wait until high voltage is recieved 
    return (duration/2) / 29.1; // Given formula
}


void loop(){
  //waits until the button is pressed
  buttonState = digitalRead(BUTTONPIN);
  
  
  if (buttonState == HIGH){
    //pause for a moment so the button presser can move
    delay(500);
    //get cm before running so we don't run into an infinite loop
    cm = get_distance_cm();

 
    while (cm > 10){
        //run until were 10 cm away from something
        irstate1 = digitalRead(IRPIN1);
        irstate2 = digitalRead(IRPIN2);
        //read from both ir sensors, logging rotate count every time it hits the shiny surface
        if(irstate1== LOW) {
          ++rotation_count1;
          Serial.println(rotation_count1);
        }
        if(irstate2 == LOW) {
          ++rotation_count2;
          Serial.println(rotation_count2);
        }
        //if rotation count 1 is highest than count 2 by 8 or more
        if ((rotation_count1 - rotation_count2) > 8) {
            analogWrite(5, 130); 
            analogWrite(11, 118);
        }
        //the opposite
        else if ((rotation_count2 - rotation_count1) > 8) {
            analogWrite(5,118); 
            analogWrite(11, 145);
        }
        //difference of less than 8, write same val to pins
        else {
          analogWrite(5, 134);
          analogWrite(11, 134);
        }
        cm = get_distance_cm();
    }
    
    // Stop or do something else
    digitalWrite(5, 0);
    digitalWrite(11, 0);
    //set buttonState to low to wait until its pressed again
    buttonState = LOW;
    //reset the count.
    rotation_count1 = rotation_count2 = 0;
  }

}