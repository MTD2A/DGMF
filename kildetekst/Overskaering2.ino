// Overskæring Ulf2 testet på Nano November 2024

#include <Servo.h>

const int irPin = 2;                 // Pin til IR-sensor (KY-032)
const int blinkPin = 9;              // Pin til blinkudgang
const int bellPin = 7;               // Pin til klokkeudgang
const int servoPin = 10;             // Pin til servo

Servo bomServo;

// Tidsintervaller (i millisekunder)
const unsigned long delay15 = 5000;      // 9 sekunder
const unsigned long delay50 = 5000;     // 10 sekunder
const unsigned long blinkInterval = 400; // Blinkfrekvens: 400 ms for tænd/sluk
const unsigned long servoStepDelay = 50; // Forsinkelse mellem hvert servo trin (20 ms)
const unsigned long blinkAfterServoUp = 1000; // Forsinkelse for blink efter bommen er oppe (1 sekund)

// Variabler til at holde styr på sekvensens tilstand
bool isSequenceActive = false;       // Indikerer, om en sekvens er i gang
bool isSensorEnabled = true;         // Tillader sensor aktivering, hvis true
bool isBlinkOn = false;              // Status for blink (tændt/slukket)
bool bomIsDown = false;              // Status for bom (nede/oppe)
bool isServoMoving = false;          // Indikerer, om servoen bevæger sig
unsigned long sequenceStartTime = 0; // Starttidspunkt for sekvens
unsigned long nextActivationTime = 0; // Tidspunkt for næste mulige aktivering
unsigned long lastBlinkTime = 0;     // Tidsstempel for sidste blink
unsigned long lastServoMoveTime = 0; // Tidsstempel for sidste servo bevægelse
unsigned long servoMoveEndTime = 0;  // Tidsstempel for slutningen af servo bevægelse
int currentServoPosition = 39;        // Aktuel position af servoen
int targetServoPosition = 0;         // Målposition for servoen

void setup() {
  pinMode(irPin, INPUT);             // Sætter IR-sensor som input
  pinMode(blinkPin, OUTPUT);         // Sætter blinkudgang som output
  pinMode(bellPin, OUTPUT);          // Sætter klokkeudgang som output
  bomServo.attach(servoPin);         // Tilslutter servo til pin
  bomServo.write(currentServoPosition); // Bommen starter i oppe-position (0 grader)
  digitalWrite(blinkPin, LOW);       // Blinkudgang starter slukket
  digitalWrite(bellPin, LOW);        // Klokkeudgang starter slukket
  
}

void loop() {
  unsigned long currentTime = millis();

  // Tjekker, om IR-sensoren er aktiveret og er klar til at køre ny sekvens
  if (digitalRead(irPin) == LOW && isSensorEnabled) {
    if (!isSequenceActive && !bomIsDown) {
      startSequence(currentTime);
    } else if (bomIsDown && !isSequenceActive) {
      resetCrossing();
    }
  }

  // Håndterer sekvensen, når den er aktiv
  if (isSequenceActive) {
    handleSequence(currentTime);
  }

  // Gør sensoren aktiv igen efter xx sekunder (hvis sekvensen er afsluttet)
  if (!isSequenceActive && currentTime >= nextActivationTime) {
    isSensorEnabled = true;  // Sensor kan nu aktiveres igen
    
  }

  // Håndterer blinkudgangens blink
  if (isSequenceActive || bomIsDown || isServoMoving) {  // Blink fortsætter mens sekvensen er aktiv, bommen er nede, eller servoen bevæger sig
    handleBlink(currentTime);
  }

  // Håndterer servoens bevægelse
  if (isServoMoving) {
    moveServoGradually(currentTime);
  }
}

// Funktion til at starte en ny sekvens
void startSequence(unsigned long currentTime) {
  
  isSequenceActive = true;
  isSensorEnabled = false;           // Deaktiverer sensor for at undgå gentagelse
  sequenceStartTime = currentTime;   // Starttidspunkt for den aktuelle sekvens
  nextActivationTime = currentTime + delay50; // Næste mulige aktiveringstid

  // Starter blink og klokkeudgang
  digitalWrite(bellPin, HIGH);       // Tænder klokkeudgang
}

// Håndterer sekvensens stadier baseret på tid
void handleSequence(unsigned long currentTime) {
  // Efter xx sekunder: bommen kører ned og klokkeudgang stopper
  if (currentTime - sequenceStartTime >= delay15 && !bomIsDown) {
    targetServoPosition = 19;        // Bommen ned (90 grader)
    isServoMoving = true;
    digitalWrite(bellPin, LOW);      // Stopper klokkeudgang
    bomIsDown = true;                // Markerer bommen som nede
    
  }

  // Efter xx sekunder: sekvens slutter, men bommen og blinket forbliver aktive
  if (currentTime - sequenceStartTime >= delay50) {
    isSequenceActive = false;        // Sekvens afsluttet
    
  }
}

// Funktion til at håndtere blink, så det blinker hvert 500 ms
void handleBlink(unsigned long currentTime){
  if (currentTime - lastBlinkTime >= blinkInterval) {
    isBlinkOn = !isBlinkOn;               // Skifter blinkstatus (tænd/sluk)
    digitalWrite(blinkPin, isBlinkOn ? HIGH : LOW);  // Opdaterer blinkudgang
    lastBlinkTime = currentTime;            // Opdaterer sidste blinktid
  }
}

// Funktion til at nulstille overskæringen og stoppe blink
void resetCrossing() {
  
  targetServoPosition = 39;          // Bommen op (0 grader)
  isServoMoving = true;
  servoMoveEndTime = millis() + blinkAfterServoUp; // Sætter slutningen af servo bevægelse
  bomIsDown = false;                // Marker bommen som oppe
  isSensorEnabled = false;          // Deaktiverer sensor indtil xx sekunders ventetid
  nextActivationTime = millis() + delay50; // Sætter næste mulige aktiveringstid
}

// Funktion til at bevæge servoen gradvist
void moveServoGradually(unsigned long currentTime) {
  if (currentTime - lastServoMoveTime >= servoStepDelay) {
    if (currentServoPosition < targetServoPosition) {
      currentServoPosition++;
    } else if (currentServoPosition > targetServoPosition) {
      currentServoPosition--;
    }
    bomServo.write(currentServoPosition);
    lastServoMoveTime = currentTime;

    if (currentServoPosition == targetServoPosition) {
      isServoMoving = false;
      if (targetServoPosition == 0) {
        delay(blinkAfterServoUp);         // Forsinkelse for blink efter bommen er oppe
        digitalWrite(blinkPin, LOW);      // Stopper blinkudgang
      }
    }
  }
}
