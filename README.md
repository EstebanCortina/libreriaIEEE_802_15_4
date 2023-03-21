# Libreria IEEE_802_15_4

La libreria se basa en la documentación de Digi para comunicación entre sus radios que utilizar comunicación XBEE con el protocolo 802.15.4



## Clase principal

```c++
class IEEE_802_15_4{
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
  
  private:
  uint8_t trama[58];
  uint8_t length[2];
  uint8_t type;
  String MAC16;
  int size;
  String MAC48="00:13:A2:00:";
  uint8_t MAC[2];
  uint8_t rssi;
  uint8_t option;
  String mensaje;
  
};
}
```


## Explicación de la clase:

La el constructor (el que tiene el mismo nombre que la clase), recibe un arreglo del tipo uint8_t que es el arreglo donde vienen los números hexadecimales que se envia desde el otro arduino. Ejemplo de un arreglo permitido:


```c++
uint8_t mensaje[3]={0x01,0xEF,0x81};
//Solo acepta de este tipo.
IEEE_802_15_4 radio(mensaje);
```
## Mensajes de tamaño definido para Tinkercad

En Tinkercad no se puede incluir la libreria <vector.h>, lo que nos limita a definir el tamaño del arreglo desde un inicio. Pero al usarlo en un Arduino físico, podemos incluirla y hacer dinámico el arreglo que recibe. Mientras tanto debemos especificar de que largo será la trama.

# Metodos
````
//Este metodo calcula el tamaño del arreglo para usarse en otros métodos. Es el equivalente a ".length"
int IEEE_802_15_4::tam(uint8_t arreglo[]){
  int sum=0;
  int i=0;
  while(arreglo[i]!=0xEF){
    sum++;
    i++;
  }
  size=sum;
  return sum;
}

//Regresa un string con dos números concatenados (los numeros que vienen en la trama que corresponden a la MAC)
String IEEE_802_15_4::GET_MAC48(){
  return MAC48+=(String(MAC[0])+":"+String(MAC[1]));
}
//Mismo que el método MAC16, solo que se le añade al inicio los valores de una MAC de 48 bits. Los números son los que el IEEE le dio al Digi para ponerle a sus radios. La MAC es un números único para cada dispositivo. Los pimeros numeros significan que son productos de Digi.
String IEEE_802_15_4::GET_MAC16(){
  return MAC16+=(String(MAC[0],HEX)+":"+String(MAC[1],HEX));
}
//Regresa el número correspondiente al Length de la trama. El length es la cantidad bytes que hay entre el campo del length y el checksum, no confundir con checksum.
uint8_t IEEE_802_15_4::GET_LENGTH(){
  return length[1];
}
//Devuelve el byte correspondiente al Option. El option es el que nos dice si hay indicaciones con ese paquete. Algunos bytes indican si es para restransmitir, si necesita confirmación, etc. En este casi el Option nos dice que el ACK está desactivado, el ACK es el acknowledgement (decirle al que lo envió, que ya lo recibió) eso significa que este mensaje no necesita confirmación.
uint8_t IEEE_802_15_4::GET_OPTION(){
  return option;
}
//Devuelve la calidad de la señal. Se convierte en un string de un número decimal y se le colocan los caracteres legibles.
String IEEE_802_15_4::GET_RSSI(){
  
  return "-"+String(rssi)+"db";
}
//El Type es el tipo de paquete, en este caso es un 0x81, o sea que es un receive. Entendí que es un paquete que espera ser recibido.
uint8_t IEEE_802_15_4::GET_TYPE(){
  return type;
}
//El checksum es la cantidad de bytes que hay desde el campo Frame Type, hasta la información que se envía, el payload. Se suman estos números hexadecimales y se restan a 0xFF (255) que es el máximo de envio. El resultado de esta resta nos debe dar el propio número que esta en el campo del checksum. Si es menor entonces significa que el paquete esta corrupto.

//Lo que hace es recorre el arreglo a partir de la posición 3 (o sea el 4to valor) y empezar a sumar los números en la variable sum. Al final se valida si el valor de sum en hexadecimales menos 0xFF es igual a lo qeu esta en el ultimo lugar del arreglo de la trama. Si es cierto devuele un True(1) caso contrario un False(0).
bool IEEE_802_15_4::CHECKSUM(uint8_t arreglo[]){
  uint8_t sum=0;
  for (int i = 3; i < size; i++) {   
    sum += arreglo[i];
  }
  if((0xFF-(sum,HEX))==arreglo[size]){
    Serial.println(arreglo[size]);
  	return true;  
  }else{
    return false;
  }
}
//Devuelve el mensaje secreto. El payload es un string cualquiera.
String IEEE_802_15_4::GET_PAYLOAD(){
  return mensaje;
}

//En esta zona es donde se recibe el arreglo con el los valores de la trama. Los primeros valores son estáticos, por lo que siempre buscaremos en esas posiciones, solo tendríamos que validar que el primero tuviera un delimitador 0x7E que es lo que da inicio a la trama.

//Conforme se va ejecutando, se recorre con el incremento y al llegar al payload se hace un ciclo que recorre hasta que se topa con su propio checksum, podriamos hacer esto más dinámico obteniendo el checksum primero o restando -1 al size del arreglo de la trama. Mientra que arreglo[j]!=arreglo[size-1] que siga. La variable mensaje se concatena con caracteres. Cada valor de esos espacios del arreglo, se convierten a decimales, que despues se convierten a caracteres ASCII. Todo eso ase la función char(). El resultado es un caracter que se concatena a lo que ya hay.
IEEE_802_15_4::IEEE_802_15_4(uint8_t arreglo[]){
  int i=1;
    length[0]=arreglo[i];
  	i++;
  	length[1]=arreglo[i];
  	i++;
    type=arreglo[i];
  	i++;
  	MAC[0]=arreglo[i];
  	i++;
    MAC[1]=arreglo[i];
  	i++;
    rssi=arreglo[i];
  	i++;
    option=arreglo[i];
  	i++;
  	int j=i;
  while(arreglo[j]!=0xEF){
    mensaje+=char(arreglo[j]);
    j++;        
  }
}
````
## Mensajes de tamaño definido para Tinkercad

En Tinkercad no se puede incluir la libreria <vector.h>, lo que nos limita a definir el tamaño del arreglo desde un inicio. Pero al usarlo en un Arduino físico, podemos incluirla y hacer dinámico el arreglo que recibe. Mientras tanto debemos especificar de que largo será la trama.

# Metodos
````
//Este metodo calcula el tamaño del arreglo para usarse en otros métodos. Es el equivalente a ".length"
int IEEE_802_15_4::tam(uint8_t arreglo[]){
  int sum=0;
  int i=0;
  while(arreglo[i]!=0xEF){
    sum++;
    i++;
  }
  size=sum;
  return sum;
}

//Regresa un string con dos números concatenados (los numeros que vienen en la trama que corresponden a la MAC)
String IEEE_802_15_4::GET_MAC48(){
  return MAC48+=(String(MAC[0])+":"+String(MAC[1]));
}
//Mismo que el método MAC16, solo que se le añade al inicio los valores de una MAC de 48 bits. Los números son los que el IEEE le dio al Digi para ponerle a sus radios. La MAC es un números único para cada dispositivo. Los pimeros numeros significan que son productos de Digi.
String IEEE_802_15_4::GET_MAC16(){
  return MAC16+=(String(MAC[0],HEX)+":"+String(MAC[1],HEX));
}
//Regresa el número correspondiente al Length de la trama. El length es la cantidad bytes que hay entre el campo del length y el checksum, no confundir con checksum.
uint8_t IEEE_802_15_4::GET_LENGTH(){
  return length[1];
}
//Devuelve el byte correspondiente al Option. El option es el que nos dice si hay indicaciones con ese paquete. Algunos bytes indican si es para restransmitir, si necesita confirmación, etc. En este casi el Option nos dice que el ACK está desactivado, el ACK es el acknowledgement (decirle al que lo envió, que ya lo recibió) eso significa que este mensaje no necesita confirmación.
uint8_t IEEE_802_15_4::GET_OPTION(){
  return option;
}
//Devuelve la calidad de la señal. Se convierte en un string de un número decimal y se le colocan los caracteres legibles.
String IEEE_802_15_4::GET_RSSI(){
  
  return "-"+String(rssi)+"db";
}
//El Type es el tipo de paquete, en este caso es un 0x81, o sea que es un receive. Entendí que es un paquete que espera ser recibido.
uint8_t IEEE_802_15_4::GET_TYPE(){
  return type;
}
//El checksum es la cantidad de bytes que hay desde el campo Frame Type, hasta la información que se envía, el payload. Se suman estos números hexadecimales y se restan a 0xFF (255) que es el máximo de envio. El resultado de esta resta nos debe dar el propio número que esta en el campo del checksum. Si es menor entonces significa que el paquete esta corrupto.

//Lo que hace es recorre el arreglo a partir de la posición 3 (o sea el 4to valor) y empezar a sumar los números en la variable sum. Al final se valida si el valor de sum en hexadecimales menos 0xFF es igual a lo qeu esta en el ultimo lugar del arreglo de la trama. Si es cierto devuele un True(1) caso contrario un False(0).
bool IEEE_802_15_4::CHECKSUM(uint8_t arreglo[]){
  uint8_t sum=0;
  for (int i = 3; i < size; i++) {   
    sum += arreglo[i];
  }
  if((0xFF-(sum,HEX))==arreglo[size]){
    Serial.println(arreglo[size]);
  	return true;  
  }else{
    return false;
  }
}
//Devuelve el mensaje secreto. El payload es un string cualquiera.
String IEEE_802_15_4::GET_PAYLOAD(){
  return mensaje;
}

//En esta zona es donde se recibe el arreglo con el los valores de la trama. Los primeros valores son estáticos, por lo que siempre buscaremos en esas posiciones, solo tendríamos que validar que el primero tuviera un delimitador 0x7E que es lo que da inicio a la trama.

//Conforme se va ejecutando, se recorre con el incremento y al llegar al payload se hace un ciclo que recorre hasta que se topa con su propio checksum, podriamos hacer esto más dinámico obteniendo el checksum primero o restando -1 al size del arreglo de la trama. Mientra que arreglo[j]!=arreglo[size-1] que siga. La variable mensaje se concatena con caracteres. Cada valor de esos espacios del arreglo, se convierten a decimales, que despues se convierten a caracteres ASCII. Todo eso ase la función char(). El resultado es un caracter que se concatena a lo que ya hay.
IEEE_802_15_4::IEEE_802_15_4(uint8_t arreglo[]){
  int i=1;
    length[0]=arreglo[i];
  	i++;
  	length[1]=arreglo[i];
  	i++;
    type=arreglo[i];
  	i++;
  	MAC[0]=arreglo[i];
  	i++;
    MAC[1]=arreglo[i];
  	i++;
    rssi=arreglo[i];
  	i++;
    option=arreglo[i];
  	i++;
  	int j=i;
  while(arreglo[j]!=0xEF){
    mensaje+=char(arreglo[j]);
    j++;        
  }
}
````