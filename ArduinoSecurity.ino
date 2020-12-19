#include <IRremote.h>
#include <Servo.h>

#define b1 0xFF6897
#define b2 0xFF9867
#define b3 0xFFB04F
#define b4 0xFF30CF
#define b5 0xFF18E7
#define b6 0xFF7A85
#define b7 0xFF10EF
#define b8 0xFF38C7
#define b9 0xFF5AA5
#define b0 0xFF4ABF


int receiver = 11;
String pin, input_pin;
bool isAlarmDisabled = false;

int r = 7;
int g = 6;
int b = 5;

Servo lockservo;

IRrecv irrecv(receiver);
decode_results results;

void setup() {
  // put your setup code here, to run once:

  pinMode(r, OUTPUT);
  pinMode(b, OUTPUT);
  pinMode(g, OUTPUT);
  lockservo.attach(9);
  Serial.begin(9600);
  irrecv.enableIRIn();

  pin = String("1234");
  input_pin = String("");
}

void loop() {
  // put your main code here, to run repeatedly:

  analogWrite(b, 0);

  lockservo.write(180);


  Serial.println(results.value, HEX);

  if (irrecv.decode(&results)) {
    if (results.value == b1) {
      input_pin = input_pin + "1";  
    }
    else if (results.value == b2) {
      input_pin = input_pin + "2";  
    }
    else if (results.value == b3) {
      input_pin = input_pin + "3"; 
    }
    else if (results.value == b4) {
      input_pin = input_pin + "4";  
    }
    else if (results.value == b5) {
      input_pin = input_pin + "5";  
    }
    else if (results.value == b6) {
      input_pin = input_pin + "6";  
    }
    else if (results.value == b7) {
      input_pin = input_pin + "7";  
    }
    else if (results.value == b8) {
      input_pin = input_pin + "8";  
    }
    else if (results.value == b9) {
      input_pin = input_pin + "9";  
    }
    else if (results.value == b0) {
      input_pin = input_pin + "0";  
    }
    analogWrite(b, 255);
    delay(500);
    irrecv.resume();  
    Serial.println(input_pin);
  }
  if (input_pin.length() == 4) {
      if (input_pin == pin) {
        isAlarmDisabled = true;
        Serial.println(":)"); 
        lockservo.write(0);
        analogWrite(b, 0);
        analogWrite(r, 0);
        analogWrite(g, 255);
        delay(10000);
        analogWrite(g, 0);
        analogWrite(b, 0);
        
      }
      else {
        isAlarmDisabled = false;
        Serial.println(":(");
        analogWrite(b, 0);
        analogWrite(r, 255);
        analogWrite(g, 0);
        delay(1000);
        analogWrite(r, 0);
      }
      input_pin = String("");  
    }
}
