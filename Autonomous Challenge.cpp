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
int button_pressed;
//11, motor 1 is weaker

void setup(){
    pinMode(TRIGPIN, OUTPUT); 
    pinMode(ECHOPIN, INPUT); 
    pinMode(BUTTONPIN, OUTPUT);
    pinMode(IRPIN1, INPUT);
    pinMode(IRPIN2, INPUT);
    Serial.begin(9600); 

}

int get_distance_cm () {
  //wrote an explanation in challenge 3
    digitalWrite(TRIGPIN, LOW);
    delayMicroseconds(5);
    digitalWrite(TRIGPIN, HIGH);
    delayMicroseconds(10);
    digitalWrite(TRIGPIN, LOW);
    duration = pulseIn(ECHOPIN, HIGH); //pulseIn is a timer function to wait until high voltage is recieved 
    return (duration/2) / 29.1;
}

int drive_forward() {

    cm = get_distance_cm();
    while (cm > 4){
    
        buttonState = digitalRead(BUTTONP IN);
        if (buttonState == HIGH){
          buttonState = LOW;
        return -1;
        }
        irstate1 = digitalRead(IRPIN1);
        irstate2 = digitalRead(IRPIN2);

        if(irstate1== LOW) {
          ++rotation_count1;
          Serial.println(rotation_count1);
        }
        if(irstate2 == LOW) {
          ++rotation_count2;
          Serial.println(rotation_count2);
        }
              if ((rotation_count1 - rotation_count2) > 8) {
            analogWrite(5, 92); 
            analogWrite(11, 78);
        }
        else if ((rotation_count2 - rotation_count1) > 8) {
            analogWrite(5,78); 
            analogWrite(11, 92);
        }
        else {
          analogWrite(5,78);
          analogWrite(11, 78);
        }


        cm = get_distance_cm();
    }
    
    
    digitalWrite(5, 0);
    digitalWrite(11, 0);
    delay(500);
    return 1;
}

void turn_counterclockwise() {
  
     analogWrite(6,94);
     analogWrite(11,94);
     delay(400);
    analogWrite(6,0);
     analogWrite(11,0);
}


void turn_clockwise() {
      analogWrite(5,94);
      analogWrite(10,94);
      delay(400);
      analogWrite(5,0);
      analogWrite(10,0);  
}


int length () {
  
  button_pressed = drive_forward();

  if (button_pressed == -1) return -1; 
  //look left
  turn_counterclockwise();
  delay(500);
  cm = get_distance_cm();
  if (cm < 7) {
    turn_clockwise();
    turn_clockwise();
    delay(500);
    cm = get_distance_cm();
   
    if (cm < 12) {
      return -1;
    }
  }
  delay(500);
  return 1;
}


void loop(){
  buttonState = digitalRead(BUTTONPIN);
  
  if (buttonState == HIGH){
    delay(500);
    while(true) {

  
      button_pressed = length();

      if (button_pressed == -1) {
          buttonState = LOW;
          break;
      }

    }
    digitalWrite(5, 0);
    digitalWrite(11, 0);
    delay(1000);
  }
} 