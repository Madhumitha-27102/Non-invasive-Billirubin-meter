#include <Wire.h>
#include "Adafruit_TCS34725.h"
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

// ===== OLED Settings =====
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

// ===== RGB Sensor =====
Adafruit_TCS34725 tcs = Adafruit_TCS34725(TCS34725_INTEGRATIONTIME_600MS, TCS34725_GAIN_1X);

// ===== Mode Switch Button =====
#define MODE_BUTTON 2
bool neonateMode = false; // false = Adult, true = Neonate


// ===== LED Pins =====
#define LED1_PIN 25
#define LED2_PIN 26

// ===== Photodiode Pin =====
#define PD_PIN 4

// ===== Thresholds =====
float thresholdAdultHigh = 10.0; //Normalised of 3.0mg
float thresholdAdultMedium = 14.0;//Normilesd of 1.0mg
float thresholdNeonateHigh = 12.0; ; 
float thresholdNeonateMedium = 10.0;

void setup() {
  Serial.begin(9600);

  // OLED init
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println("SSD1306 init failed!");
    for (;;);
  }
  display.clearDisplay();

  // TCS34725 init
  if (!tcs.begin()) {
    Serial.println("TCS34725 not found!");
    while (1);
  }

  // Pins
  pinMode(MODE_BUTTON, INPUT_PULLUP);
  pinMode(LED1_PIN, OUTPUT);
  pinMode(LED2_PIN, OUTPUT);
  pinMode(PD_PIN, INPUT);
}

void loop() {
  // Mode selection
  neonateMode = (digitalRead(MODE_BUTTON) == LOW);

  // LEDs on for measurement
  digitalWrite(LED1_PIN, HIGH);
  digitalWrite(LED2_PIN, HIGH);
  delay(50);

  // Read RGB
  uint16_t r, g, b, c;
  tcs.getRawData(&r, &g, &b, &c);

  // Normalize RGB
  float sum = r + g + b;
  float rNorm = r / sum;
  float gNorm = g / sum;
  float bNorm = b / sum;

  // Calculate approximate bilirubin
  float bilirubin = (0.5*r + 0.3*g + 0.2*b) / 50.0;

  // Read Photodiode
  int pdRaw = analogRead(PD_PIN);
  float pdVolt = pdRaw * (3.3 / 4095.0);
  float pdBilirubin = pdVolt * 8.0; // scale factor

  // Combine RGB and PD
  float finalBilirubin = (bilirubin + pdBilirubin) / 2.0;

  // Determine Jaundice Level
  String jaundice;
  if (neonateMode) {
    if (finalBilirubin > thresholdNeonateHigh) jaundice = "High";
    else if (finalBilirubin > thresholdNeonateMedium) jaundice = "Medium";
    else jaundice = "Normal";
  } else {
    if (finalBilirubin > thresholdAdultHigh) jaundice = "High";
    else if (finalBilirubin > thresholdAdultMedium) jaundice = "Medium";
    else jaundice = "Normal";
  }

  // LEDs off
  digitalWrite(LED1_PIN, LOW);
  digitalWrite(LED2_PIN, LOW);

  // OLED Display
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0,0);
  display.printf("Mode: %s\n", neonateMode ? "Neonate" : "Adult");
  display.printf("R:%d G:%d B:%d\n", r, g, b);
  display.printf("BilRGB:%.1f\n", bilirubin);//billlirubin level 
  display.printf("BilPD:%.1f\n", pdBilirubin);//pd billirubin 
  display.printf("Final Bil:%.1f\n", finalBilirubin);
  display.printf("Jaundice: %s\n", jaundice.c_str());
  display.display();

  // Serial Output
  Serial.printf("Mode: %s | R:%d G:%d B:%d | Bil:%.2f | Jaundice: %s\n",
                neonateMode ? "Neonate" : "Adult",
                r, g, b, finalBilirubin, jaundice.c_str());

  delay(1000); // 1 second
}