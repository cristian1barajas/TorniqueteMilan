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

void setup()
{
    Ethernet.init(5);
    Serial.begin(9600);
    Serial.println("Ethernet Client Project");

    //digitalConfiguration();

    //Ethernet.begin(mac); // DHCP
    
    Ethernet.begin(mac, IPAddress(192,168,0,92));
    Serial.println("Ethernet begin");
    delay(1000);

    ethernetShieldConnection();
    ethernetCableConnection();
}

void loop()
{
    sendWebRequest();
    //testSequence();
}

void ethernetShieldConnection()
{
    if (Ethernet.hardwareStatus() == EthernetNoHardware)
    {
        Serial.println("Ethernet shield was not found. Sorry, can't run without hardware. :(");
    } else {
        Serial.println("Ethernet shield was found. Congratulations. :)");
    }
}

void ethernetCableConnection()
{
    if (Ethernet.linkStatus() == LinkOFF)
    {
        Serial.println("Ethernet cable is not connected.");
    } else {
        Serial.println("Ethernet cable is connected.");
    }
}

void digitalConfiguration(void)
{
    Serial.println("Configuración salidas digitales");
    pinMode(LED_ETHERNET_CONNECTED, OUTPUT);
    pinMode(LED_ETHERNET_DISCONNECTED, OUTPUT);
    pinMode(INPUT_SOLENOID_RELAY, OUTPUT);
    pinMode(OUTPUT_SOLENOID_RELAY, OUTPUT);
    pinMode(INPUT_INDICATOR, OUTPUT);
    pinMode(OUTPUT_INDICATOR, OUTPUT);
    digitalWrite(LED_ETHERNET_CONNECTED, LOW);
    digitalWrite(LED_ETHERNET_DISCONNECTED, LOW);
    digitalWrite(INPUT_SOLENOID_RELAY, LOW);
    digitalWrite(OUTPUT_SOLENOID_RELAY, LOW);
    digitalWrite(INPUT_INDICATOR, LOW);
    digitalWrite(OUTPUT_INDICATOR, LOW);
}

void testSequence()
{
    Serial.println("Inicio de secuencia");
    digitalWrite(LED_ETHERNET_CONNECTED, HIGH);
    delay(1500);
    digitalWrite(LED_ETHERNET_CONNECTED, LOW);

    digitalWrite(LED_ETHERNET_DISCONNECTED, HIGH);
    delay(1500);
    digitalWrite(LED_ETHERNET_DISCONNECTED, LOW);

    digitalWrite(INPUT_SOLENOID_RELAY, HIGH);
    delay(1500);
    digitalWrite(INPUT_SOLENOID_RELAY, LOW);

    digitalWrite(INPUT_INDICATOR, HIGH);
    delay(1500);
    digitalWrite(INPUT_INDICATOR, LOW);

    digitalWrite(OUTPUT_SOLENOID_RELAY, HIGH);
    delay(1500);
    digitalWrite(OUTPUT_SOLENOID_RELAY, LOW);

    digitalWrite(OUTPUT_INDICATOR, HIGH);
    delay(1500);
    digitalWrite(OUTPUT_INDICATOR, LOW);
}

void sendWebRequest() {
    if (client.connect(IPAddress(192,168,0,93),9081)) {
        Serial.println("Cliente conectado");
        client.println(preUrl + idNumber + postUrl + " HTTP/1.0");
        client.println("User-Agent: Escaner 1.0");
        client.println();

        while (client.connected())
        {
          if (client.available())
          {
            Serial.println("Respuesta: ");
            String answerWeb = client.readStringUntil('\n');
            Serial.println(answerWeb);
          }
        }
    } else {
        Serial.println("Cliente no conecta");
    }

}