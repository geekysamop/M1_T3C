// Define the ultrasound sensor 1 pins
const int trigPin1 = 9;
const int echoPin1 = 10;

// Define the ultrasound sensor 2 pins
const int trigPin2 = 11;
const int echoPin2 = 12;

// Define the LED pin
const int ledPin = 13;

// Define the threshold distance in centimeters
const int threshold = 30;

void setup() {
  Serial.begin(9600);
  pinMode(trigPin1, OUTPUT);
  pinMode(echoPin1, INPUT);
  pinMode(trigPin2, OUTPUT);
  pinMode(echoPin2, INPUT);
  pinMode(ledPin, OUTPUT);
  attachInterrupt(digitalPinToInterrupt(echoPin1), interruptFunction, CHANGE);
  attachInterrupt(digitalPinToInterrupt(echoPin2), interruptFunction, CHANGE);
}

void loop() {
  // Measure distance for sensor 1
  int distance1 = measureDistance(trigPin1, echoPin1);

  // Measure distance for sensor 2
  int distance2 = measureDistance(trigPin2, echoPin2);

  // Print the distances to the serial monitor
  Serial.print("Distance 1: ");
  Serial.print(distance1);
  Serial.println(" cm");
  Serial.print("Distance 2: ");
  Serial.print(distance2);
  Serial.println(" cm");

  // If the distance falls below the threshold for either sensor, blink the LED
  if (distance1 < threshold || distance2 < threshold) {
    digitalWrite(ledPin, HIGH);
    delay(100);
    digitalWrite(ledPin, LOW);
  }

  delay(100);
}

// Interrupt function that is triggered when the echoPin changes state
void interruptFunction() {
  digitalWrite(ledPin, HIGH);
  delay(100);
  digitalWrite(ledPin, LOW);
}

// Helper function to measure the distance using an ultrasound sensor
int measureDistance(int trigPin, int echoPin) {
  // Send a pulse to the ultrasound sensor
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  // Measure the pulse duration
  unsigned long pulseDuration = pulseIn(echoPin, HIGH);

  // Convert the pulse duration to distance in centimeters
  int distance = pulseDuration / 58;

  return distance;
}
