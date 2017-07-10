
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
const double MAXHUM = 80;
const double MINHUM = 5;
int flag_start_flow=0;
float caudal_Lm=0;
int contador =0;
#define Relay 6

/********************************
 *    Variables Globales        *
/********************************/

// Banderas

boolean flag_water = false;
boolean flag_screen_update = false;
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
   Serial.begin(BAUD_RATE); 
  Serial.println("INICIO");
 planta.begin();
  int i;
 Wire.begin();  
 SeeedOled.init();  //initialze SEEED OLED display

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
  if (flag_start_flow==3){
    Serial.print(caudal_Lm);
    SeeedOled.putString("Flujo:");
    SeeedOled.putFloat(caudal_Lm);
    SeeedOled.putString("L/m");
    flag_start_flow=0;
  }
}

void ISR_INTE0() //PIN2 Encoder
{

}

void imprimirEnPantalla(){
    for(int i=1; i<=LIMITE; i++){
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
//
void ISR_Timer ()
{
  if (flag_start_flow == 2){
    caudal_Lm= (NumPulsos*4)/factor_conv;
    flag_start_flow = 3;
    Serial.println("estado 2");
  }
  else if (flag_start_flow == 1){
    NumPulsos=0;
    flag_start_flow++;
    Serial.println("estado 1");
  }
  if((contador%4) == 0){
    flag_screen_update = true;
  }
  if(planta.cheqHumS()>MINHUM)
  {
    digitalWrite(Relay, HIGH);
  }
 else if(planta.cheqHumS()<MAXHUM)
  {
    digitalWrite(Relay, LOW);
  }
  contador++;
}

void sumarPulsos(){
   NumPulsos++;
}

