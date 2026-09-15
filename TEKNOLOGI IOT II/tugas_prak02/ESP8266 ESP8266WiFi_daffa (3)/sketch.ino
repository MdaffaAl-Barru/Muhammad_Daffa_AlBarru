#include <DHT.h>

const int ldrPin = 34;     
const int dhtPin = 21;     
const int relayPin = 15;   
const int ledPin = 5;      

#define DHTTYPE DHT22      
DHT dht(dhtPin, DHTTYPE);

void setup() {
  Serial.begin(115200);
  dht.begin();
  
  pinMode(relayPin, OUTPUT);
  pinMode(ledPin, OUTPUT);
  
  digitalWrite(relayPin, LOW);
  digitalWrite(ledPin, LOW);
  
  Serial.println("Sistem Smart Warehouse Dimulai...");
}

void loop() {
  delay(2500);  
  
  float suhu = dht.readTemperature();
  float kelembapan = dht.readHumidity();
  int nilaiLDR = analogRead(ldrPin);
  
  if (isnan(suhu) || isnan(kelembapan)) {
    Serial.println("Gagal membaca dari sensor DHT!");
    return;
  }
  
  Serial.print("Cahaya (ADC): ");
  Serial.print(nilaiLDR);
  Serial.print(" | Suhu: ");
  Serial.print(suhu);
  Serial.print(" C | Kelembapan: ");
  Serial.print(kelembapan);
  Serial.println(" %");

  if (suhu > 34.0 || nilaiLDR < 300) {
    digitalWrite(relayPin, HIGH); 
    digitalWrite(ledPin, HIGH);
    Serial.println("Peringatan: Aktuator Aktif!");
  } else {
    digitalWrite(relayPin, LOW);
    digitalWrite(ledPin, LOW);
    Serial.println("Kondisi Aman.");
  }
  
  Serial.println("---------------------------------------------");
}