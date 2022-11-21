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
    Serial.begin(115200);
    Serial2.begin(115200);
    Serial.println("Ethernet Client Project");

    digitalConfiguration();

    Ethernet.begin(mac, IPAddress(192, 168, 0, 92)); // IPv4 Host Address
    Serial.println("Ethernet begin");
    delay(1000);

    ethernetShieldConnection();
    ethernetCableConnection();
}

void loop()
{
    serialPortListeningInput();
    serialPortListeningOutput();
    timerRelayInput();
    timerRelayOutput();
    ethernetCableConnectionStatus();
}

void ethernetShieldConnection()
{
    if (Ethernet.hardwareStatus() == EthernetNoHardware)
    {
        Serial.println("Ethernet shield was not found. Sorry, can't run without hardware. :(");
    }
    else
    {
        Serial.println("Ethernet shield was found. Congratulations. :)");
    }
    delay(1000);
}

void ethernetCableConnection()
{
    if (Ethernet.linkStatus() == LinkOFF)
    {
        Serial.println("Ethernet cable is not connected.");
    }
    else
    {
        Serial.println("Ethernet cable is connected.");
        digitalWrite(LED_ETHERNET_CONNECTED, HIGH);
    }
    delay(1000);
    Serial.println("Initialization!");
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

void sendWebRequest(String webRequest)
{
    if (client.connect(IPAddress(192, 168, 0, 80), 9081))
    {
        Serial.println("Cliente conectado");
        client.println(webRequest);
        client.println("User-Agent: Escaner 1.0");
        client.println();

        while (client.connected())
        {
            if (client.available())
            {
                String answerWeb = client.readStringUntil('\n');
                Serial.println(answerWeb);
                turnOnRelayAndIndicator(answerWeb, webRequest);
            }
        }
    }
    else
    {
        Serial.println("Cliente no conecta");
    }
}

void serialPortListeningInput()
{
    while (Serial2.available() > 0)
    {
        idNumber = Serial2.readStringUntil('\r');
        idNumber.trim();
        Serial.println("\nId detected: " + idNumber);
        String webRequest = preUrl + idNumber + postUrlInput + " HTTP/1.0";
        Serial.println(webRequest);
        sendWebRequest(webRequest);
    }
}

void serialPortListeningOutput()
{
    while (Serial.available() > 0)
    {
        idNumber = Serial.readStringUntil('\r');
        idNumber.trim();
        Serial.println("\nId detected: " + idNumber);
        String webRequest = preUrl + idNumber + postUrlOutput + " HTTP/1.0";
        Serial.println(webRequest);
        sendWebRequest(webRequest);
    }
}

void turnOnRelayAndIndicator(String data, String request)
{
    if (data.substring(0, 1) == "{")
    {
        if (data.substring(11, 15) == "0000")
        {
            if (request.substring(87, 88) == "E")
            {
                Serial.println("Turn On Input!");
                digitalWrite(INPUT_SOLENOID_RELAY, HIGH);
                digitalWrite(INPUT_INDICATOR, HIGH);
                inputRelayState = true;
            }
            else if (request.substring(87, 88) == "S")
            {
                Serial.println("Turn On Output!");
                digitalWrite(OUTPUT_SOLENOID_RELAY, HIGH);
                digitalWrite(OUTPUT_INDICATOR, HIGH);
                outputRelayState = true;
            }
        }
        else
        {
            Serial.println("You do not have permissions to enter!");
        }
    }
}

void timerRelayInput(void)
{
    if (inputRelayState)
    {
        currentMillisInput++;

        if (currentMillisInput >= interval)
        {
            currentMillisInput = 0;
            digitalWrite(INPUT_SOLENOID_RELAY, LOW);
            digitalWrite(INPUT_INDICATOR, LOW);
            inputRelayState = false;
        }
    }
}

void timerRelayOutput(void)
{
    if (outputRelayState)
    {
        currentMillisOutput++;

        if (currentMillisOutput >= interval)
        {
            currentMillisOutput = 0;
            digitalWrite(OUTPUT_SOLENOID_RELAY, LOW);
            digitalWrite(OUTPUT_INDICATOR, LOW);
            outputRelayState = false;
        }
    }
}

void ethernetCableConnectionStatus(void) {
    if (Ethernet.linkStatus() == LinkOFF)
    {
        digitalWrite(LED_ETHERNET_CONNECTED, LOW);
    }
    else
    {
        digitalWrite(LED_ETHERNET_CONNECTED, HIGH);
    }
}