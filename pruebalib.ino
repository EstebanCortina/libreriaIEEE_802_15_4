#include "IEEE_802_15_4.h"
void setup()
{
  // put your setup code here, to run once:
  Serial.begin(9600);
  uint8_t array[58] = {0x7E, 0x00, 0x35,
                       0x81, 0x11, 0x11,
                       0x13, 0x01, 0x45,
                       0x73, 0x74, 0x65,
                       0x20, 0x65, 0x73,
                       0x20, 0x65, 0x6C,
                       0x20, 0x67, 0x72,
                       0x75, 0x70, 0x6F,
                       0x20, 0x64, 0x65,
                       0x20, 0x34, 0x49,
                       0x20, 0x79, 0x20,
                       0x73, 0x61, 0x62,
                       0x65, 0x6D, 0x6F,
                       0x73, 0x20, 0x70,
                       0x72, 0x6F, 0x67,
                       0x72, 0x61, 0x6D,
                       0x61, 0x72, 0x20,
                       0x65, 0x6E, 0x20,
                       0x43, 0x2B, 0x2B,
                       0xEF};

  IEEE_802_15_4 radio(array);
  radio.tam(array);
  Serial.println(radio.GET_LENGTH(), HEX);
  Serial.println(radio.GET_MAC48());
  Serial.println(radio.GET_TYPE(), HEX);
  Serial.println(radio.GET_OPTION(), HEX);
  Serial.println(String(radio.MAC16[0], HEX) +":"+String(radio.MAC16[1], HEX));
  Serial.println(radio.CHECKSUM(array));
  Serial.println(radio.GET_PAYLOAD());
  Serial.println(radio.GET_RSSI());
}

void loop()
{
  // put your main code here, to run repeatedly:
}
