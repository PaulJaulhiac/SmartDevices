// Load libraries
#include "BluetoothSerial.h"

// Check if Bluetooth configs are enabled
#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run `make menuconfig` to and enable it
#endif

// Bluetooth Serial object
BluetoothSerial SerialBT;

// GPIO where LED is connected to
#define LED 2

// Handle received and sent messages
String message = "";
char incomingChar;

void setup() {
  pinMode(LED, OUTPUT);
  Serial.begin(115200);
  // Bluetooth device name
  SerialBT.begin("ESP32-BT-Paul");
  Serial.println("The device started, now you can pair it with bluetooth!");
}

void loop() {

  // Read received messages (LED control command)
  if (SerialBT.available()){
    char incomingChar = SerialBT.read();
    if (incomingChar != '\n'){
      message += String(incomingChar);
    }
    else{
      message = "";
    }
    Serial.write(incomingChar);  
  }
  // Check received message and control output accordingly
  if (message =="1"){
    digitalWrite(LED, HIGH);
    message = "";
  }
  else if (message =="2"){
    digitalWrite(LED, LOW);
    message = "";
  }
  else if (message =="3"){
    for(int i=0;i<=3;i++){
      digitalWrite(LED, HIGH);
      delay(500);
      digitalWrite(LED, LOW);
      delay(500);
      message = "";
    }
  }
  delay(200);
}