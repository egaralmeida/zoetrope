#define DEBUG // COMMENT OUT FOR DEPLOY!!

// Constants for Audio Control
const byte LEFT = 1;
const byte RIGHT = 2;
const byte CENTER = 3;
const byte RESTART = 4;
const byte MUTE = 5;

// Pinout
const byte ledSquarePin = 11;
const byte ledTrianglePin = 10;

const byte interruptSquarePin = 3;
const byte interruptTrianglePin = 2;

const byte buttonSquarePin = 8;
const byte buttonTrianglePin = 7;

const byte motorSquarePin = 6;
const byte motorTrianglePin = 5;

// Configuration
const byte frameFlashDuration = 2;
const byte frames = 24;

// Behavior
volatile byte stateLedSquare = LOW;
volatile byte stateLedTriangle = LOW;

unsigned long ledSquarePreviousMillis = 0;
unsigned long ledTrianglePreviousMillis = 0;

unsigned long ledSquareCurrentMillis = 0;
unsigned long ledTriangleCurrentMillis = 0;

void setup() {
  // Initialize Serial
  Serial.begin(9600);
  
  // GPIO Config
  pinMode(5, OUTPUT);
  pinMode(ledSquarePin, OUTPUT);
  pinMode(ledTrianglePin, OUTPUT);
  pinMode(interruptSquarePin, INPUT);
  pinMode(interruptTrianglePin, INPUT);  
  pinMode(buttonSquarePin, INPUT_PULLUP);
  pinMode(buttonTrianglePin, INPUT_PULLUP);

  attachInterrupt(digitalPinToInterrupt(interruptSquarePin), ledSquareInterruption, RISING);
  attachInterrupt(digitalPinToInterrupt(interruptTrianglePin), ledTriangleInterruption, RISING);

  // Start the motors
  digitalWrite(motorSquarePin, HIGH);
  digitalWrite(motorTrianglePin, HIGH);

  // Give the motors time to gain speed
#ifndef DEBUG
  delay(10000);
#endif
}

void loop() {

  volatile byte buttonSquareState = digitalRead(buttonSquarePin);
  volatile byte buttonTriangleState = digitalRead(buttonTrianglePin);

  if(buttonSquareState == LOW) {
    digitalWrite(ledSquarePin, stateLedSquare);
    buttonSquareState = HIGH;
  }

  if(buttonTriangleState == LOW) {
    digitalWrite(ledTrianglePin, stateLedTriangle);
    buttonTriangleState = HIGH;
  }
  
  if (stateLedSquare == HIGH) {
    ledSquareCurrentMillis = millis();
    if (ledSquareCurrentMillis - ledSquarePreviousMillis >= frameFlashDuration) {
      ledSquarePreviousMillis = ledSquareCurrentMillis;

      stateLedSquare == LOW;
    }
  }

  if (stateLedTriangle == HIGH) {
    ledTriangleCurrentMillis = millis();
    if (ledTriangleCurrentMillis - ledTrianglePreviousMillis >= frameFlashDuration) {
      ledTrianglePreviousMillis = ledTriangleCurrentMillis;

      stateLedTriangle == LOW;
    }
  }

#ifdef DEBUG
  digitalWrite(13, stateLedTriangle);
#endif
}

void ledSquareInterruption() {
  // Encoder received light
  stateLedSquare = HIGH;
  //ledSquareCurrentMillis = millis();
}

void ledTriangleInterruption() {
  // Encoder received light
  stateLedTriangle = HIGH;
  //ledTriangleCurrentMillis = millis();
}

