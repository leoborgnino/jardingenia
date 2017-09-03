
#include <TimerOne.h>
#include <Wire.h>
#include <SeeedOLED.h>
//#include "D:\jarga\Documents\GitHub\jardingenia\libraries\Planta\Planta.h"
//#include "D:\jarga\Documents\GitHub\jardingenia\libraries\Planta\Planta.cpp"
//#include "D:\jarga\Documents\GitHub\jardingenia\libraries\DHT\DHT.h"
//#include "D:\jarga\Documents\GitHub\jardingenia\libraries\SI114X\SI114X.h"
//#include "/home/ingenia/jardingenia/libraries/Planta/Planta.h"
//#include "/home/ingenia/jardingenia/libraries/Planta/Planta.cpp"
//#include "/home/ingenia/jardingenia/libraries/SI114X/SI114X.h"
//#include "/home/ingenia/jardingenia/libraries/DHT/DHT.h"
#include "/home/leo/Documentos/jardingenia/libraries/Planta/Planta.h"
#include "/home/leo/Documentos/jardingenia/libraries/Planta/Planta.cpp"
#include "/home/leo/Documentos/jardingenia/libraries/SI114X/SI114X.h"
#include "/home/leo/Documentos/jardingenia/libraries/DHT/DHT.h"
#include "Arduino.h"

/********************************
 *        Constantes            *
/********************************/

#define Relay 6

const int TIEMPO_ESPERA = 10; // 10 sec espera
const int VAL_MAX_BOMBA = 100; 
const long BAUD_RATE = 9600;
const int INTE0 = 2;
const int LIMITE = 6;
const int TIME_SAMPLE = 5;
const double NREGAR = 65;
const double REGAR_INF = 40;
const int   MICRO_ADDR  =   10; 

/********************************
 *    Variables Globales        *
/********************************/

// Banderas

int flag_start_flow = 0;
int contador        = 0;
float caudal_Lm     = 0.;

boolean flag_water         = false;
boolean flag_screen_update = false;

// Variables Comunicación PC

boolean flag_transmision = false;
boolean flag_accion      = false;
int  flag_uart           =  0;
int respuestaid_datos    =  0;
int  contador_backup     =  0;
int  data_len_rx         =  0;
char  SerRx;
char formlist[150];
char data_rec[10];
char mystring[100];
char buff[8][7];
float datos[7];

/********************************
 * Declaración de funciones     *
/********************************/

/**                 
 * @name send_uart
 * @brief Armado de trama + envio de datos a traves del modulo UART
 * @param Cadena de caracteres a enviar. Debe finalizar con el caracter "!" 
 * @param Id del objeto que va a recibir los datos
 */

void send_uart(char*,int);

/**
 * @name receive_uart
 * @brief Extraccion de los datos entramados para posterior procesamiento
 * @param None
 */
void receive_uart();

/**
 * @name activarBomba()
 * @brief Activa el relé que comanda la bomba de agua
 * @param None
 */
boolean activarBomba();

/**
 * @name imprimirEnPantalla();
 * @brief Imprime en pantalla Oled los parámetros de los sensores
 * @param None
 */
void imprimirEnPantalla();

/**
 * @name obtener_datos(datos)
 * @brief Obtiene los datos de los sensores y los guarda en el arreglo que se le pasa como parametro
 * @param datos (array *float)
 */

void obtener_datos(float *datos);

/**   
 * @name setup
 * @brief Inicializacion de variables, interrupciones, comunicacion serie.
 * @param None
 */

Planta planta(40,65,1,1,1,1);


void setup()
{

  Serial.begin(BAUD_RATE); 
  planta.begin();  
  Wire.begin();  
  SeeedOled.init();  //initialze SEEED OLED display

  Serial.println("INICIO");  

  Timer1.initialize(double(1000*1000.0)); // WARNING: Depende de la versión del compilador  // Dispara cada TIME_SAMPLE ms
  Timer1.attachInterrupt(ISR_Timer);     // Activa la interrupcion y la asocia a ISR_Blink
  attachInterrupt(digitalPinToInterrupt(INTE0), sumarPulsos,    RISING); // Interrupcion externa en pin 2 por cambio de nivel

  SeeedOled.clearDisplay();           //clear the screen and set start position to top left corner
  SeeedOled.setNormalDisplay();       //Set display to Normal mode
  SeeedOled.setPageMode();            //Set addressing mode to Page Mode
  
  pinMode(Relay, OUTPUT);
  
}

/**                                  
 * @name loop
 * @brief Main Loop.
 * @param None
 */

void loop()
{

  if (flag_screen_update == true)
    {
      imprimirEnPantalla();
      flag_screen_update = false;
    }
  if (flag_start_flow==3)
    {
      //Serial.print(caudal_Lm);
      SeeedOled.putString("Flujo:");
      SeeedOled.putFloat(caudal_Lm);
      SeeedOled.putString("L/m");
      flag_start_flow=0;
    }

// Send Data
  if ((data_rec[1] == 'g') && (flag_accion))
  {
    respuestaid_datos = data_rec[0];
    //obtener_datos(datos);

    //for(int i=0;i<6;i++)
    //{
    //  dtostrf(datos[i],6,2,buff[i]);
    //}

   //sprintf(mystring, "%s %s %s %s %s %s !", buff[0], buff[1], buff[2], buff[3], buff[4], buff[5]);
   sprintf(mystring, "1 2 3 4 5 6 !");
   send_uart(mystring, respuestaid_datos);
   flag_accion = false;
  }
  
  if (Serial.available() > 0)
    receive_uart();

}

void ISR_INTE0() //PIN2 Encoder
{
  
}

void imprimirEnPantalla()
{
  for(int i=1; i<=LIMITE; i++)
    {
      SeeedOled.setTextXY(i,0); //Set the cursor to 3rd Page, 0th Column  
      switch (i)
        {
        case 1:
          SeeedOled.setPageMode(); 
          SeeedOled.putString("Temp:"); 
          SeeedOled.putFloat(planta.cheqTemp());
          SeeedOled.putString("C");
          break;
          
        case 2:
          SeeedOled.putString("HumS:");
          SeeedOled.putFloat(planta.cheqHumS());
          SeeedOled.putString("%");
          break;
          
        case 3:
          
          SeeedOled.putString("HumA:");
          SeeedOled.putFloat(planta.cheqHum());
          SeeedOled.putString("%");
          break;
          
        case 4:
          SeeedOled.putString("Luz:");
          SeeedOled.putFloat(planta.cheqLuz());
          SeeedOled.putString(" lumen");
          break;
          
        case 5:
          flag_start_flow=planta.cheqFlujo();
          break;
        }
    }
}

// Timer Interruption

void ISR_Timer ()
{
  if (flag_start_flow == 2)
    {
      caudal_Lm= (NumPulsos*4)/factor_conv;
      flag_start_flow = 3;
      //Serial.println("estado 2");
    }
  else if (flag_start_flow == 1)
    {
      NumPulsos=0;
      flag_start_flow++;
      //Serial.println("estado 1");
    }

  if((contador%4) == 0)
    flag_screen_update = true;
  
  if(planta.cheqHumS()< planta.humSMin)
    digitalWrite(Relay, HIGH);
  else if(planta.cheqHumS()> planta.humSMax)
    digitalWrite(Relay, LOW);
  
  contador++;
}

void sumarPulsos()
{
  NumPulsos++;
}

// PC Comunication

/*******************************************************************************************************************************************************
 * Arma la trama con el dato a enviar y lo envía por la UART. La trama contiene un encabezado, la longitud del dato high y low, el identificador del ***
 * objeto que requirió el dato, la dirección desde la cual se envía el dato, el DATO y un fin de trama *************************************************
/*******************************************************************************************************************************************************/
void send_uart(char* data_send, int respuestaid)
{
  int data_len    = 0;
  char caracter   = 0;
  int header      = 0;
  int iheader     = 0;
  int PL          = 0;
  int mod_header  = 0;
  int mod_iheader = 0;
  int size_l      = 0;
  int size_h      = 0;

  header = 160;
  iheader = 64;
  while (caracter != '!')
  {
    caracter = data_send[data_len];
    data_len++;
  }
  data_len--;
  PL = 16;
  mod_header = header + PL + ((data_len & 0xf0000) >> 16);
  mod_iheader = iheader;
  size_l = data_len & 0xff;
  size_h = (data_len & 0xff00) >> 8;
  formlist[0] = mod_header;
  formlist[1] = size_h;
  formlist[2] = size_l;
  formlist[3] = respuestaid;
  formlist[4] = MICRO_ADDR;

  for ( int i = 5 ; i < 5 + data_len ; i++)
    formlist[i] = data_send[i - 5];
  formlist[5 + data_len] = mod_iheader;

  for (int i = 0 ; i < data_len + 6; i++)
    Serial.write(formlist[i]);
}

void receive_uart()
{
  SerRx = Serial.read();
  if ( ( flag_uart == 0 ) && ( (SerRx & 0xE0) == 160) ) //Encontramos el MIT
  {
    flag_uart++;
    data_len_rx = (SerRx & 0x0F);
  }
  else if ( flag_uart == 1 )
  {
    data_len_rx = data_len_rx + (SerRx << 8);
    flag_uart++;
  }
  else if ( flag_uart == 2 )
  {
    data_len_rx = data_len_rx + SerRx;
    flag_uart++;
  }
  else if ( ( SerRx == MICRO_ADDR ) && ( flag_uart == 3 ) )
  {
    flag_uart++;
  }
  else if ( flag_uart == 4 )
  {
    data_rec[0] = SerRx;
    flag_uart++;
  }
  else if ( (flag_uart > 4) && (flag_uart < 5 + data_len_rx) )
  {
    data_rec[flag_uart - 4] = SerRx;
    flag_uart++;
  }
  else if ( (SerRx == 64) && ( flag_uart == (5 + data_len_rx) ) ) //termina la recepción de la trama
  {
    flag_uart = 0;
    flag_accion = 1; //Ejecutamos la accion en el loop principal
  }
  else flag_uart = 0;

}

void obtener_datos (float *datos)
{

  //datos[0] = planta.cheqTemp();
  //datos[1] = planta.cheqHumS();
  //datos[2] = planta.cheqHum();
  //datos[3] = planta.cheqLuz();
  //datos[4] = caudal_Lm;
  //datos[5] = flag_bomba_activada;

}


