#########################################################################################
##  Main Jardin Ingenia                                                                 #
##                                                                                      #
##  execute in terminal: python main.py sys.argv[1]                                     #
##                                                                                      #
##  sys.argv[1] = name of the serial port to use. Example: /dev/ttyUSB0                 #
##                                                                                      #
##                                                                                      #
#########################################################################################

import Comunicacion
import time
import threading
import ThreadHandler
import graphic
import Logue
import Jardin
import sys

BAUD_RATE = 9600

def open_threads():
    hilo_recepcion.start()
    time.sleep(0.05)
    hilo_envio.start()
    time.sleep(0.05)
    hilo_grafico.start()
    time.sleep(0.05)
    hilo_Logue.start()
    time.sleep(0.05)   

def close_threads():
    hilo_recepcion.stop_thread()
    time.sleep(0.05)
    hilo_envio.stop_thread()
    time.sleep(0.05)
    hilo_grafico.stop_thread()
    time.sleep(0.05)
    hilo_Logue.stop_thread()
    time.sleep(0.05)

com = Comunicacion.Comunicacion(sys.argv[1],BAUD_RATE)
jardin = Jardin.jardin(com)
grafico = graphic.grafico(jardin)
Logue = Logue.Logue(jardin)
hilo_recepcion = ThreadHandler.ThreadHandler(com.receive, "Hilo de recepcion")
hilo_envio = ThreadHandler.ThreadHandler(com.send, "Hilo de envio")
hilo_grafico = ThreadHandler.ThreadHandler(grafico.run, "Hilo Grafico")
hilo_Logue = ThreadHandler.ThreadHandler(Logue.run, "Hilo Datos")
open_threads()
# time.sleep(60)
while True:
    pass
close_threads()
