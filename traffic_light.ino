// Arduino Pelican Crossing
// Author: Rhys J
// v1.0

// constants for the pin number connected to the component
const int redLED = 10;
const int yellowLED = 9;
const int greenLED = 8;
const int walkRedLED = 6;
const int walkGreenLED = 5;
const int button = 3;

// constants for the stages of the sequence
const int notRunning = 0; // traffic light sequence is not running
const int startSequence = 1; // traffic light sequence is running
const int flashing = 2; // stage of sequence where the yellow and walk green LED are flashing

int time = 0; // timer variable to check 1 minute has passed since traffic was stopped
int sequenceRunning = notRunning; // variable stores the current stage of the sequence
bool buttonPressed = false; // variable if button has been pressed

// this function is run when the button has been pressed, due to the interrupt
void ButtonPressedInterrupt() 
{
  // button press is only registered when the sequence is not running or is flashing
  if(sequenceRunning != startSequence) 
  {
    buttonPressed = true; // button press is registered
  }
}

// this function is run once when program is started
void setup()
{
  // setup all the connected pins
  pinMode(redLED, OUTPUT);
  pinMode(yellowLED, OUTPUT);
  pinMode(greenLED, OUTPUT);
  pinMode(walkRedLED, OUTPUT);
  pinMode(walkGreenLED, OUTPUT);
  pinMode(button, INPUT);
  
  // when button pin goes from high to low the specified function is run
  attachInterrupt(digitalPinToInterrupt(button), ButtonPressedInterrupt, FALLING);
  
  // setup the default lights that are on
  digitalWrite(greenLED, HIGH);
  digitalWrite(walkRedLED, HIGH);
}

// function is repeated indefinitely while the program is running
void loop()
{
  // decrements the timer by 1 every second
  delay(1000);
  time--;
  
  // sequence will run if timer is 0 or less and when button press has been registered
  if (time <= 0 && buttonPressed)
  {
    buttonPressed = false; // button press is no longer pressed
    sequenceRunning = startSequence;
    digitalWrite(greenLED, LOW);
    digitalWrite(yellowLED, HIGH);
    delay(3000);
    digitalWrite(yellowLED, LOW);
    digitalWrite(redLED, HIGH);
    digitalWrite(walkRedLED, LOW);
    digitalWrite(walkGreenLED, HIGH);
    delay(10000);
    digitalWrite(redLED, LOW);
    sequenceRunning = flashing; // button presses from this point will be registered
    
    // loop will repeat 5 times making the lights flash
    for(int i=0; i<5; i++)
    {
      digitalWrite(yellowLED, LOW);
      digitalWrite(walkGreenLED, LOW);
      delay(500);
      digitalWrite(yellowLED, HIGH);
      digitalWrite(walkGreenLED, HIGH);
      delay(500);
    }
    
    digitalWrite(greenLED, HIGH);
    digitalWrite(walkRedLED, HIGH);
    digitalWrite(yellowLED, LOW);
    digitalWrite(walkGreenLED, LOW);
    time = 60; // traffic will not be stopped for 60 seconds
    sequenceRunning = notRunning;
  }
}
