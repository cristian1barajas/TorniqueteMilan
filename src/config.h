#include <Arduino.h>
#include <UIPEthernet.h>

#define LED_ETHERNET_CONNECTED 26
#define LED_ETHERNET_DISCONNECTED 25

#define INPUT_SOLENOID_RELAY 27
#define OUTPUT_SOLENOID_RELAY 12

#define INPUT_INDICATOR 14
#define OUTPUT_INDICATOR 13

uint8_t mac[6] = {0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED};
//byte mac[] = {0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED};
byte ipLocal[] = {192, 168, 1, 90};
byte ipServer[] = {192, 168, 1, 92};
const int portRemote = 9081;

String preUrl = "GET /api/v1/registrovisitas/visitantes/validarAcceso?codigoBuscar=";
String postUrl = "&estacion=P-03&lugar=5";
String idNumber = "1031124702";

void ethernetShieldConnection(void);
void ethernetCableConnection(void);
void digitalConfiguration(void);
void testSequence(void);
void sendWebRequest(void);