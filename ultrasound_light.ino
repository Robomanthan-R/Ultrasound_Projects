// Define pins for Ultrasonic Sensor and LED
const int trigPin = 33;   // Trigger pin of the ultrasonic sensor
const int echoPin = 32;  // Echo pin of the ultrasonic sensor
const int ledPin = 2;   // LED pin (built-in or external)

long duration;
int distance;
int thresholdDistance = 10;  // Set threshold distance in centimeters

void setup() {
  // Initialize pins
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(ledPin, OUTPUT);
  
  // Start serial communication
  Serial.begin(9600);
}

void loop() {
  // Clear the trigger pin
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);

  // Trigger the sensor by sending a 10us high pulse
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  // Read the echo pin and calculate the distance
  duration = pulseIn(echoPin, HIGH);
  distance = duration * 0.034 / 2;  // Convert time to distance in cm

  // Print the distance to the Serial Monitor (optional for debugging)
  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");

  // Check if the distance is less than the threshold distance
  if (distance < thresholdDistance) {
    digitalWrite(ledPin, HIGH);  // Turn on the LED
  } else {
    digitalWrite(ledPin, LOW);   // Turn off the LED
  }

  // Add a short delay before the next reading
  delay(200);
}
