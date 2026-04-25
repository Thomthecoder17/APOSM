#include <TinyUSB_Mouse_and_Keyboard.h>

const int SENSOR_PIN = 7; // Pin connected to the sensor's OUT pin
int lastState = LOW;      // Previous state
int currentState;         // Current state
int newPotState;   
int tiltsensor = 6;
int pot = 28;
int responseDelay = 2;
int yVal = 0;
int tiltState = 0;
int button = 18;
int mic = 26;
int adcVoltReading;

void setup() {
  Serial.begin(9600);
  pinMode(SENSOR_PIN, INPUT); // Set sensor as input
  pinMode(tiltsensor, INPUT);
  pinMode(pot, INPUT);
  pinMode(button, INPUT_PULLUP);
  Mouse.begin();
}

void loop() {
  if (digitalRead(button) == LOW) {
    exit(0);
  }

  adcVoltReading = analogRead
  
  currentState = digitalRead(SENSOR_PIN); 
  int prevPotState = newPotState;
  newPotState = (analogRead(pot) * 1.75953079179); // Read sensor
  int moveAmount = newPotState-prevPotState;

  Serial.print("tilt: ");
  Serial.println(tiltState);
  Serial.print("pot: ");
  Serial.println(newPotState);

  Mouse.move(moveAmount, yVal, 0);
  if (tiltState == 1){
    yVal = 1;
  }else{
    yVal = -1;
  }

  if(lastState == LOW && currentState == HIGH) {
    Mouse.click();
    Mouse.press();
    Serial.println("Touch detected!"); // Touched
  }
  else if(lastState == HIGH && currentState == LOW) {
    Mouse.release();
    Serial.println("Sensor released"); // Released
  }

  lastState = currentState; // Save state
  delay(10); // Small delay to debounce
}