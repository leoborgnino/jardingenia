
/********************************
 *        Includes              *
/********************************/

#include <TimerOne.h>
#include <Wire.h>
#include <SeeedOLED.h>
#include "/home/ingenia/jardingenia/libraries/Planta/Planta.h"
#include "/home/ingenia/jardingenia/libraries/Planta/Planta.cpp"
#include "/home/ingenia/jardingenia/libraries/SI114X/SI114X.h"
#include "/home/ingenia/jardingenia/libraries/DHT/DHT.h"
#include "Arduino.h"

/********************************
 *        Constantes            *
/********************************/

const int TIEMPO_ESPERA = 10; // 10 sec espera
const int VAL_MAX_BOMBA = 100; 
const long BAUD_RATE = 9600;
const int INTE0 = 2;
const int LIMITE = 6;
const int TIME_SAMPLE = 5;

/********************************
 *    Variables Globales        *
/********************************/

// Banderas

boolean flag_water = false;

// Clases
//

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
boolean activarBomba();
void imprimirEnPantalla();


/**                                                                                                                                                                  
 * @name setup
 * @brief Inicializacion de variables, interrupciones, comunicacion serie.
 * @param None
 */


Planta planta(1,1,1,1,1);
void setup()
{

  int i;
  Wire.begin();  
  SeeedOled.init();  //initialze SEEED OLED display
  
  Timer1.initialize(double(TIME_SAMPLE*1000.0)); // WARNING: Depende de la versión del compilador  // Dispara cada TIME_SAMPLE ms
  Timer1.attachInterrupt(ISR_Timer);     // Activa la interrupcion y la asocia a ISR_Blink
  
  Serial.begin(BAUD_RATE);               // Inicio la transmision serie
  attachInterrupt(digitalPinToInterrupt(INTE0), ISR_INTE0,    RISING); // Interrupcion externa en pin 2 por cambio de nivel
  SeeedOled.clearDisplay();           //clear the screen and set start position to top left corner
  SeeedOled.setNormalDisplay();       //Set display to Normal mode
  SeeedOled.setPageMode();            //Set addressing mode to Page Mode

}

/**                                                                                                                                                                  
 * @name loop
 * @brief Main Loop.
 * @param None
 */
void loop()
{
  Serial.begin(9600);
  planta.begin();
    for(int i=1; i<=LIMITE; i++){
  SeeedOled.setTextXY(i,0); //Set the cursor to 3rd Page, 0th Column  
  switch (i)
  {
    case 1:
  SeeedOled.putString("Temp:"); //SeeedOled.putString("Temp:"+ metodoget de planta +" °C");
  SeeedOled.putFloat(planta.cheqTemp());
  SeeedOled.putString("C");
  break;

   case 2:
   
  SeeedOled.setPageMode(); 
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

 /* case 5:
  SeeedOled.putString("Flujo:");
  SeeedOled.putFloat(planta.cheqFlujo());
  SeeedOled.putString("%");
  break;*/
  }
  }
 delay (1000);
SeeedOled.clearDisplay();
}

void ISR_INTE0() //PIN2 Encoder
{

}

void imprimirEnPantalla(){

}

void ISR_Timer ()
{
  
  }





