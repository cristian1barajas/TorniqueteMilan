#include <Arduino.h>
#include <UIPEthernet.h>

#define LED_ETHERNET_CONNECTED 26
#define LED_ETHERNET_DISCONNECTED 25

#define INPUT_SOLENOID_RELAY 27
#define OUTPUT_SOLENOID_RELAY 12

#define INPUT_INDICATOR 14
#define OUTPUT_INDICATOR 13

bool inputRelayState = false;
bool outputRelayState = false;
unsigned long currentMillisInput = 0;
unsigned long currentMillisOutput = 0;
const long interval = 5000;

uint8_t mac[6] = {0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED};
byte ipLocal[] = {192, 168, 0, 92};
byte ipServer[] = {192, 168, 0, 80};
const int portRemote = 9081;

String preUrl = "GET /api/v1/registrovisitas/visitantes/validarAcceso?codigoBuscar=";
String postUrlInput = "&operacion=E&estacion=P-03&lugar=5";
String postUrlOutput = "&operacion=S&estacion=P-03&lugar=5";
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