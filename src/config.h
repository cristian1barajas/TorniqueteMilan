#include <Arduino.h>
#include <UIPEthernet.h>

#define LED_ETHERNET_CONNECTED 32 
#define LED_ETHERNET_DISCONNECTED 33 

#define INPUT_SOLENOID_RELAY 13
#define OUTPUT_SOLENOID_RELAY 26

#define INPUT_INDICATOR_DISABLE 27
#define INPUT_INDICATOR_ENABLE 25

#define OUTPUT_INDICATOR_DISABLE 12
#define OUTPUT_INDICATOR_ENABLE 14

#define TIME 150

bool inputRelayState = false;
bool outputRelayState = false;
unsigned long currentMillisInput = 0;
unsigned long currentMillisOutput = 0;
const long interval = 5000;

unsigned long previousMillis;
//unsigned long resetInterval = 60000; // Un minuto
//unsigned long resetInterval = 1800000; // Media hora
//unsigned long resetInterval = 3600000; // Una hora
unsigned long resetInterval = 43200000; // 12 horas
//unsigned long resetInterval = 86400000; // 24 horas

uint8_t mac[6] = {0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED};
byte ipLocal[] = {192, 168, 1, 205};
byte ipServer[] = {192, 168, 1, 200};
const int portRemote = 9081;

String preUrl = "GET /api/v1/registrovisitas/visitantes/validarAcceso?codigoBuscar=";
String postUrlInput = "&operacion=E&estacion=P-MB&lugar=5";
String postUrlOutput = "&operacion=S&estacion=P-MB&lugar=5";
String idNumber = "";

void ethernetShieldConnection(void);
void ethernetCableConnection(void);
void digitalConfiguration(void);
void sendWebRequest(String webRequest);
void serialPortListeningInput(void);
void serialPortListeningOutput(void);
void turnOnRelayAndIndicator(String data, String request);
void timerRelayInput(void);
void timerRelayOutput(void);
void ethernetCableConnectionStatus(void);
void reset();