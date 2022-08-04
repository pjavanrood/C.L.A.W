#include "NewPing.h"
#include "Servo.h"

#define VCC_PIN 13
#define TRIG_PIN 12
#define ECHO_PIN 11
#define GND_PIN 10

#define ITERATION 5

#define MAX_DISTANCE 200
#define MIN_DISTANCE 19
#define WAIT 5

int pos = 0;
bool claw_closed = false;
double distance;

NewPing sonar(TRIG_PIN, ECHO_PIN, MAX_DISTANCE);
Servo servo;

void setup() {
  Serial.begin(9600);

  //Sensor
  pinMode(ECHO_PIN, INPUT) ;  
  pinMode(TRIG_PIN, OUTPUT) ;

  //Set GND to 0V
  pinMode(GND_PIN, OUTPUT);
  digitalWrite(GND_PIN,LOW); 

  //Set VCC to 5V
  pinMode(VCC_PIN, OUTPUT); 
  digitalWrite(VCC_PIN, HIGH) ;       
     
  servo.attach(9);
  servo.write(0);
}


void loop() {
  distance = get_distance();
  Serial.print("distance = ");
  Serial.println(distance);
  if(distance <= MIN_DISTANCE && distance > 0.5){
    open_claw(); //goes from 0 to 180
    delay(WAIT * 1000);
    close_claw(); //goes from 180 to 0
  }
}


double get_distance(){ //returns distance in cm
  double u = sonar.ping_median(ITERATION);
  return u * 0.01715; // v_sound / 2 = 0.01715
}


void open_claw(){
  for(pos = 0; pos <= 180; pos++){
    servo.write(pos);
    delay(10);
  }
}

void close_claw(){
  for(pos = 180; pos >= 0; pos--){
    servo.write(pos);
    delay(10);
  }

}
