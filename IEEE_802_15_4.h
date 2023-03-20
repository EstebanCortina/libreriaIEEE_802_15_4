class IEEE_802_15_4
{
public:
  IEEE_802_15_4(uint8_t arreglo[]);
  String GET_MAC16(void);
  String GET_MAC48(void);
  uint8_t GET_LENGTH(void);
  uint8_t GET_OPTION(void);
  String GET_RSSI(void);
  uint8_t GET_TYPE(void);
  String GET_PAYLOAD(void);
  bool CHECKSUM(uint8_t arreglo[]);
  int tam(uint8_t arreglo[]);
  uint8_t MAC16[2];

private:
  uint8_t trama[58];
  uint8_t length[2];
  uint8_t type;
  int size;
  String MAC48 = "00:13:A2:00:";
  uint8_t rssi;
  uint8_t option;
  String mensaje;
};

int IEEE_802_15_4::tam(uint8_t arreglo[])
{
  int sum = 0;
  int i = 0;
  while (arreglo[i] != 0xEF)
  {
    sum++;
    i++;
  }
  size = sum;
  return sum;
}

String IEEE_802_15_4::GET_MAC48()
{
  return MAC48 += (String(MAC16[0]) + ":" + String(MAC16[1]));
}
String IEEE_802_15_4::GET_MAC16()
{
  return (String(MAC16[0]) + ":" + String(MAC16[1]));
}

uint8_t IEEE_802_15_4::GET_LENGTH()
{
  return length[1];
}

uint8_t IEEE_802_15_4::GET_OPTION()
{
  return option;
}
String IEEE_802_15_4::GET_RSSI()
{

  return "-" + String(rssi) + "db";
}
uint8_t IEEE_802_15_4::GET_TYPE()
{
  return type;
}
bool IEEE_802_15_4::CHECKSUM(uint8_t arreglo[])
{
  uint8_t sum = 0;
  for (int i = 3; i < size; i++)
  {
    sum += arreglo[i];
  }
  if ((0xFF - (sum, HEX)) == arreglo[size])
  {    
    return true;
  }
  else
  {
    return false;
  }
}

String IEEE_802_15_4::GET_PAYLOAD()
{
  return mensaje;
}

IEEE_802_15_4::IEEE_802_15_4(uint8_t arreglo[])
{
  int i = 1;
  length[0] = arreglo[i];
  i++;
  length[1] = arreglo[i];
  i++;
  type = arreglo[i];
  i++;
  MAC16[0] = arreglo[i];
  i++;
  MAC16[1] = arreglo[i];
  i++;
  rssi = arreglo[i];
  i++;
  option = arreglo[i];
  i++;
  int j = i;
  while (arreglo[j] != 0xEF)
  {
    mensaje += char(arreglo[j]);
    j++;
  }
}