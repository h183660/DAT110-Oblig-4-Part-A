void setup()
{
  Serial.begin(9600);
  pinMode(13, OUTPUT);
  pinMode(12, OUTPUT);
  pinMode(11, OUTPUT);
  pinMode(10, INPUT);
  pinMode(9, INPUT);
  pinMode(8, INPUT);
}

const String CODE = "01";
String entry = "";

const int LOCKED = 1;
const int WAITING = 2;
const int UNLOCKED = 3;
int state = LOCKED;

      int push1handled = 0;
      int push2handled = 0;

int buttonpresses = 0;
int entry1 = 0;
int entry2 = 0;

byte debug = 0;

void loop()
{
  int motion = 0;
  entry = "";
  buttonpresses = 0;
  motion = digitalRead(10);
  
  if(motion == HIGH){
    state = WAITING;
  }
  
  switch (state) {
    
    case LOCKED:
    	digitalWrite(13, HIGH);
     break;  
   
    case WAITING:
    	digitalWrite(12, HIGH);
    
    while(buttonpresses != 2){      
    	int btn1 = digitalRead(9);
  		int btn2 = digitalRead(8);
  
      if (btn1 == LOW){
   		 push1handled = 0;
      }
      
      if (btn2 == LOW){
   		 push2handled = 0;
      }
      
      if((btn1 == HIGH) && (!push1handled)){
        push1handled = 1;
        entry += "0";
        buttonpresses++;
      }
      if((btn2 == HIGH) && (!push2handled)){
        push2handled = 1;
       	entry += "1";
        buttonpresses++;
      }
    }
    
    if(entry == CODE){
      state = UNLOCKED;
    }
    
    if(state != UNLOCKED){
      state = LOCKED;
      break;
    }
    digitalWrite(12, LOW);

   case UNLOCKED:
    	digitalWrite(11, HIGH);
    	delay(15000);
    	state = LOCKED;
    break;
  }
  
  digitalWrite(13, LOW);
  digitalWrite(12, LOW);
  digitalWrite(11, LOW);
  
  // debugging control via serial
  if (Serial.available() > 0) {
     byte input = Serial.read();
     debug = (input == 49);
  }

  // debugging output via serial
  if (debug) {
    Serial.print("<");
    Serial.print(":");
    Serial.println();
  }
}
