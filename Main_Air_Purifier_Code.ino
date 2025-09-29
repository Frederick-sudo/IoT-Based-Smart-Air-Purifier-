// BS Computer Engineering
// Thesis Project By: Tongco and Corto

#define BLYNK_TEMPLATE_ID "TMPLcEykbvIV"
#define BLYNK_DEVICE_NAME "Quickstart Template"
#define BLYNK_AUTH_TOKEN "YDQeiCC4_R6DCyfiEq3p1TY1Q_u6FB8G"
#define BLYNK_PRINT Serial
#define Fanpin D3


#include <Adafruit_MLX90614.h> //Temp library
Adafruit_MLX90614 mlx = Adafruit_MLX90614();
#include <ESP8266WiFi.h>  // Blynk wifi
#include <BlynkSimpleEsp8266.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <WiFiManager.h>



LiquidCrystal_I2C lcd(0x27,20,4);

char auth[] = BLYNK_AUTH_TOKEN;


BlynkTimer timer;
int dustPin = A0; // dust sensor - Wemos A0 pin
int ledPin = D8;  // dust LED
int samplingTime = 280;
int deltaTime = 40;
int sleepTime = 9680;
float voltsMeasured = 0;
float calcVoltage = 0;
float dustDensity = 0;
 
int pinValue = 0;
const int buzzer = D5;
const int redLed = D6;              //buzzer to nodemcu D1 (GPIO-5)
const int yellowLed = D7;           //LED to nodemcu D2 (GPIO-4)
int analogSensor;                   //Input Sensor
int mq135 = A0;                     //smoke sensor is connected with the analog pin A0
int data = 0;                       //parameter
int Relay = 0;
int fan = D0;
int sensorVal = 0;
//new
float sensorData = readSensor(); 
Blynk.virtualWrite(V5, sensorData);

void myTimer()
{
  Blynk.virtualWrite(V1, sensorVal);
}

BLYNK_WRITE(V0) {
  Relay = param.asInt();
}

BLYNK_READ(V2){
  Blynk.virtualWrite(V2, sensorVal); //LCD Display ng Numbers (NEW!)
}

WidgetLCD lcd(V4); //LCD Display ng Words (NEW!)

BLYNK_CONNECTED (){
  //request the latest state from the server
  Blynk.syncVirtual(V0);
}




void setup() {
 sensorVal = analogRead(A0); // this is an example of reading sensor data
Blynk.virtualWrite(V5, sensorVal);
 
//Blynk.virtualWrite(V1, mq135);
 timer.setInterval(1000, myTimer);

  Serial.begin(115200);

WiFiManager wifiManager;
Serial.println("Conecting.....");
wifiManager.autoConnect("BLYNK WIFI MANAGER");
Serial.println("connected");

  Blynk.begin(auth, ssid, pass);  //PING blynk-cloud.com
  mlx.begin(); // Tempbegin:
  
  pinMode(fan,OUTPUT);
  pinMode(yellowLed, OUTPUT);// yellow LED light
  pinMode(redLed, OUTPUT); // red LED light
  pinMode(buzzer, OUTPUT); //buzzer sound
  pinMode(mq135,INPUT);   //mq135 Module
  pinMode(ledPin,OUTPUT); // LED dust

  lcd.clear(); //(NEW!)
  lcd.init();   
  lcd.backlight();  // backlight ON

}

void loop() {
 
  
  
  Blynk.run();
 int data = analogRead(mq135);           //read A0 pin of NodeMCU
 sensorVal = analogRead(mq135);
 Blynk.virtualWrite(V2, sensorVal); //LCD Display ng Mobile App na Number Pinapakita (NEW!)
 
lcd.setCursor(0,0);
lcd.print("Parameter:");
lcd.print(data);
 Serial.println(data, DEC);
 
 
  if (data < 300 && Relay == 0)
  {
      digitalWrite(fan, HIGH);
      digitalWrite(yellowLed,HIGH);
      lcd.setCursor(14, 0);
      lcd.print("SAFE");
      lcd.print(4, 0, "SAFE!"); //(NEW!)
      digitalWrite(redLed, LOW);
      noTone(buzzer);
  }

  else if (data > 300 || Relay == 1)                     //trigger buzzer if if smoke sensor value is greate than 400
  { 
      digitalWrite(redLed,HIGH);
      digitalWrite(fan, LOW);
      digitalWrite(yellowLed,LOW);
      digitalWrite(buzzer,255);
      tone(buzzer, 1000, 600);        // Send 1KHz sound signal…
      lcd.setCursor(14, 1);
      lcd.print("ALERT!!!");
      lcd.print(4, 0, "ALERT!"); //(NEW!)
  }


// D U S T  S E N S O R

  digitalWrite(ledPin,LOW); // power on the LED
  delayMicroseconds(samplingTime);
  voltsMeasured = analogRead(dustPin); // read the dust value
  delayMicroseconds(deltaTime);
  digitalWrite(ledPin,HIGH); // turn the LED off
  delayMicroseconds(sleepTime);
  //measure your 5v and change below
   calcVoltage = voltsMeasured * (5.0 / 1024.0);
   dustDensity = 170 * calcVoltage - 0.1; 

  Serial.print("Dust Density = ");
  Serial.println(dustDensity); // mg/m3
   lcd.setCursor(0, 3);
   lcd.print("Dust Density:"); 
   lcd.print(dustDensity); 
  Serial.println("");


 // T E M P E R A T U R E    S E N S O R 

  Serial.print("Object = "); Serial.print(mlx.readObjectTempC()); Serial.print("\xC2\xB0");
  Serial.println("C");

   lcd.setCursor(0, 2);
   lcd.print("TemSensor=");
   lcd.print(mlx.readObjectTempC());
   lcd.print("C");
   
   delay(2500);
   lcd.clear();
   timer.run();
   Blynk.run();

}
