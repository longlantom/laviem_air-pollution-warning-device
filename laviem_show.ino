/*
 * laviem project
 * Le Trung Hieu (hieult61), Ngu Ba Ly, Le Tuan Loc and Le Sy Tuan Long (longlantom)
 * Coded by longlantom
 */
#include "ESP8266WiFi.h"
#include "BlynkSimpleEsp8266.h"
#include "SimpleTimer.h"

#include "SharpGP2Y10.h"
#include "DHT.h"

SimpleTimer timer;
char auth[] = "B6YRoG0sh0_7h_C1FJlDwdXcHL7XezbG"; //code Blynk
char ssid[] = "LLTK-2.4G"; //name wifi
char pass[] = "0915xxxx"; //pass wifi

//DHT Sensor
#define DHTPIN D4 
#define DHTTYPE DHT11 

DHT dht(DHTPIN, DHTTYPE);

//DUST Sensor
int voPin = A0;
int ledPin = D2;
float vccVol = 3.3;

SharpGP2Y10 dustSensor(voPin, ledPin, vccVol);

void setup() {
    Serial.begin(9600);
    Blynk.begin(auth, ssid, pass);
    dht.begin();
    timer.setInterval(2000, sendUptime);
}

void sendUptime() {
    float h = dht.readHumidity();
    float t = dht.readTemperature();
    
    float dustVal = dustSensor.getDustDensity();
    //float volVal = dustSensor.getVotage();
    //int ADC = dustSensor.getADC();
    
    Serial.println("Nhiệt độ\tĐộ ẩm\t\tMức độ bụi");
    Serial.print(t);
    Serial.print("\t\t");
    Serial.print(h);
    Serial.print("\t\t");
    Serial.println(dustVal);
    //Serial.println(volVal);
    //Serial.println(ADC);

    Blynk.virtualWrite(V5, t);
    Blynk.virtualWrite(V6, h);
    Blynk.virtualWrite(V7, dustVal);
    if (dustVal > 0.1){
        Blynk.notify("Đeo khẩu trang zô!!!");
        //Serial.println("Đeo khẩu trang zô!!!");
        //Serial.println(dustVal);
    }
}

void loop() {
    Blynk.run();
    timer.run();
}
