// Define pins for the ultrasonic sensor
const int trigPin = 9;   // Trig pin of the ultrasonic sensor
const int echoPin = 8;   // Echo pin of the ultrasonic sensor

// Variable to store the duration and distance
long duration;
float distance;

void setup() {
  // Initialize serial communication at 9600 baud rate
  Serial.begin(9600);
  
  // Set the trigPin as OUTPUT and echoPin as INPUT
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
}

void loop() {
  // Clear the trigPin
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);

  // Set the trigPin HIGH for 10 microseconds to send out the sound wave
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  // Read the echoPin, which returns the time in microseconds for the sound wave to travel back
  duration = pulseIn(echoPin, HIGH);

  // Calculate the distance in centimeters
  distance = (duration * 0.034) / 2;

  // Print the distance on the serial monitor
  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");

  // Small delay before the next reading
  delay(500);
}
