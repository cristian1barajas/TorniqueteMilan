#include <Arduino.h>
#include <UIPEthernet.h>

byte mac[] = {0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED};
byte ipServer[] = {192, 168, 1, 90};
const byte portRemote = 80;
byte ipLocal[] = {192, 168, 1, 91};

void ethernetShieldConnection(void);
void ethernetCableConnection(void);