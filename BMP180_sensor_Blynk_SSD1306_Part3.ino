
#define BLYNK_PRINT Serial
#define BLYNK_TEMPLATE_ID "TMPLFMQuemWU"
#define BLYNK_DEVICE_NAME "ESP32 LED IOT"

#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>
#include <Adafruit_BMP085.h>

//adding OLED include library
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <BlynkSimpleEsp32.h>

#define SCREEN_WIDTH 128 //OLED display width, in pixels
#define SCREEN_HEIGHT 64 //OLED display height, in pixels

#define OLED_RESET  -1
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

Adafruit_BMP085 bmp;

char auth[] = "e_noHGOGY2_R-35w3YKTYo1DSMOnKapn";
char ssid[] = "NETGEAR70";
char pass[] = "windypiano374";

BlynkTimer Timer;

float PotVal = 0.0;

void setup() {
  Serial.begin(115200);

  Blynk.begin(auth, ssid, pass);

  if (!bmp.begin()) {
    Serial.println("Could not find a valid BMP180 sensor, check wiring!");
    while (1) {}
  }


  // SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { 
    Serial.println(F("SSD1306 allocation failed"));
    for(;;); // Don't proceed, loop forever
  }

  // Show initial display buffer contents on the screen --
  // the library initializes this with an Adafruit splash screen.
  display.display();
  delay(2000); // Pause for 2 seconds

  Timer.setInterval(2000L, sendData);

}

void loop() {
  Blynk.run();
  Timer.run();

//  PotVal = bmp.readTemperature();
}

void sendData() {
  Serial.print("Temperature = ");
  Serial.print(bmp.readTemperature());
  Serial.println(" *C");
  Serial.print("PotVal = ");
  Serial.println(PotVal);

      
  Blynk.virtualWrite(V2, bmp.readTemperature());
  //Oled display

  PotVal = bmp.readTemperature();
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0,0);
  display.print("Current Temp: ");

  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.setCursor(0,30);
  display.print(PotVal);

  display.display();
  
}
