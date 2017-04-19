/********************************
 *        Includes              *
/********************************/

#include <TimerOne.h>

/********************************
 *        Constantes            *
/********************************/

const int TIEMPO_ESPERA = 10; // 10 sec espera

/********************************
 *    Variables Globales        *
/********************************/

// Banderas

boolean flag_water = false;

// Clases


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
 * @name setup
 * @brief Inicializacion de variables, interrupciones, comunicacion serie.
 * @param None
 */
void setup()
{

  Serial.begin(BAUD_RATE);               // Inicio la transmision serie
  attachInterrupt(digitalPinToInterrupt(INTE0), ISR_INTE0,    RISING); // Interrupcion externa en pin 2 por cambio de nivel

}

/**                                                                                                                                                                  
 * @name loop
 * @brief Main Loop.
 * @param None
 */
void loop()
{


}

void ISR_INTE0() //PIN2 Encoder
{

}
