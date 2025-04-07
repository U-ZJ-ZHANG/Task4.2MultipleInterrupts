//Pin Assignments
const int buttonPin = 2;     // Push button (digital pin D2)
const int sensorPin = 3;     // Grayscale sensor (digital pin D3)
const int led1Pin = 10;      // LED1 controlled by button
const int led2Pin = 11;      // LED2 controlled by sensor

//State Variables (shared with interrupts)
volatile bool led1State = false;
volatile bool led2State = false;

void setup() {
  //Setup Pin Modes
  pinMode(buttonPin, INPUT_PULLUP); 
  pinMode(sensorPin, INPUT);       
  pinMode(led1Pin, OUTPUT);
  pinMode(led2Pin, OUTPUT);

  //Setup Serial Monitor
  Serial.begin(9600);
  Serial.println("System ready...");

  //Attach Interrupts
  attachInterrupt(digitalPinToInterrupt(buttonPin), onButtonPressed, FALLING);  //Trigger on button press
  attachInterrupt(digitalPinToInterrupt(sensorPin), onSensorTriggered, FALLING); //Trigger when dark surface is detected
}

void loop() {
  //Handle LED states based on interrupt changes
  digitalWrite(led1Pin, led1State);
  digitalWrite(led2Pin, led2State);
}

//ISR for Button Press
void onButtonPressed() {
  led1State = !led1State;
  Serial.println("Button pressed: LED1 toggled");
}

//ISR for Grayscale Sensor
void onSensorTriggered() {
  led2State = !led2State;
  Serial.println("Grayscale sensor triggered: LED2 toggled");
}