// Blynk template information
#define BLYNK_TEMPLATE_ID "TMPL33QYJj3Ss"
#define BLYNK_TEMPLATE_NAME "Plant watering system"

// Include the library files
#include <LiquidCrystal_I2C.h>
#include <Wire.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>

#define triggerPin 33    // Trigger pin for the ultrasonic sensor
#define echoPin 32       // Echo pin for the ultrasonic sensor
#define relay 2          // Relay controlling the AC light

// Initialize the LCD display
LiquidCrystal_I2C lcd(0x27, 16, 2);

BlynkTimer timer;

// Enter your Auth token
char auth[] = "2V4ug0ZLzSvaGuPDHaTmG-3Q108UboHm";

// Enter your WIFI SSID and password
char ssid[] = "Robomanthan4g";
char pass[] = "12345678";

// Function to calculate distance using the ultrasonic sensor
float getDistance() {
  // Send a HIGH pulse to the trigger pin
  digitalWrite(triggerPin, LOW);
  delayMicroseconds(2);
  digitalWrite(triggerPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(triggerPin, LOW);

  // Read the time for the pulse to return
  long duration = pulseIn(echoPin, HIGH);
  
  // Calculate the distance in cm (speed of sound: 34300 cm/s)
  float distance = duration * 0.034 / 2;
  return distance;
}

void setup() {
  // Debug console
  Serial.begin(115200);
  Blynk.begin(auth, ssid, pass, "blynk.cloud", 80);
  
  lcd.init();
  lcd.backlight();
  pinMode(relay, OUTPUT);
  digitalWrite(relay, HIGH);  // Relay initially OFF (AC light OFF)
  
  pinMode(triggerPin, OUTPUT); // Set trigger pin as output
  pinMode(echoPin, INPUT);     // Set echo pin as input
  
  lcd.setCursor(1, 0);
  lcd.print("System Loading");
  for (int a = 0; a <= 15; a++) {
    lcd.setCursor(a, 1);
    lcd.print(".");
    delay(200);
  }
  lcd.clear();
}

// Get the ultrasonic sensor values and control the relay
void ultrasonicCheck() {
  float distance = getDistance();
  Blynk.virtualWrite(V0, distance);  // Send distance to Blynk app
  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");
  
  lcd.setCursor(0, 0);
  lcd.print("Distance :");
  lcd.print(distance);
  lcd.print(" cm ");

  // If the distance is less than 10 cm, turn ON the relay (AC light ON)
  if (distance < 10) {
    digitalWrite(relay, LOW); // Relay ON (AC light ON)
    lcd.setCursor(0, 1);
    lcd.print("Light is ON ");
  } else {
    digitalWrite(relay, HIGH); // Relay OFF (AC light OFF)
    lcd.setCursor(0, 1);
    lcd.print("Light is OFF");
  }
}

// Get the button value from Blynk (optional)
BLYNK_WRITE(V1) {
  bool Relay = param.asInt();
  if (Relay == 1) {
    digitalWrite(relay, LOW);
    lcd.setCursor(0, 1);
    lcd.print("Light is ON ");
  } else {
    digitalWrite(relay, HIGH);
    lcd.setCursor(0, 1);
    lcd.print("Light is OFF");
  }
}

void loop() {
  ultrasonicCheck();  // Check distance and control the relay
  Blynk.run();  // Run the Blynk library
  delay(200);
}
