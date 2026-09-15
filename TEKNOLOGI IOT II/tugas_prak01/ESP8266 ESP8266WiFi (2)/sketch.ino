const int buttonPin = 4; // GPIO 4 (D2)
const int ledPin = 5;    // GPIO 5 (D1)

int lastButtonState = LOW; // State tracking
bool ledState = false;      // Status ON/OFF LED

void setup() {
  Serial.begin(115200);
  pinMode(buttonPin, INPUT);
  pinMode(ledPin, OUTPUT);
}

void loop() {
  int buttonState = digitalRead(buttonPin);
  
  // State Tracking: Deteksi transisi tombol (Rising Edge)
  if (buttonState == HIGH && lastButtonState == LOW) {
    delay(200); // Debounce: Mencegah flickering/getaran sakelar
    
    ledState = !ledState; // Toggle status
    digitalWrite(ledPin, ledState ? HIGH : LOW);
    
    if (ledState) {
      Serial.println("Tombol ditekan! -> LED ON");
    } else {
      Serial.println("Tombol ditekan! -> LED OFF");
    }
  }
  
  lastButtonState = buttonState;
  delay(10); // Jeda kecil agar Wokwi tidak lag
}