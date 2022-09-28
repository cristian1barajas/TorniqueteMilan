/**
 * @file main.cpp
 * @author BotLAB.co (botlab.co@gmail.com)
 * @brief Programa para la implementación de un dispositivo conectado por Ethernet
 * con la shield W5500 y ESP32-WROOM con el fin de automatizar varios torniquetes
 * @version 0.1
 * @date 2022-09-28
 * @copyright Copyright (c) 2022
 */

#include <config.h>

EthernetClient client;

void setup() {
  Ethernet.init(5);
  Serial.begin(9600);
  Serial.println("Ethernet Client Project");

  Ethernet.begin(mac, ipLocal);
  ethernetShieldConnection();
  ethernetCableConnection();
}

void loop() {
  
}

void ethernetShieldConnection() {
  if (Ethernet.hardwareStatus() == EthernetNoHardware) {
    Serial.println("Ethernet shield was not found.  Sorry, can't run without hardware. :(");
    while (true) {
      delay(1);
    }
  }
}

void ethernetCableConnection() {
  if (Ethernet.linkStatus() == LinkOFF) {
    Serial.println("Ethernet cable is not connected.");
  }
}