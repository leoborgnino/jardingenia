from Obj_Head import Obj_Head
import struct
import math

class jardin(Obj_Head):

        def __init__(self,com):
                Obj_Head.__init__(self,com,self.save)
                self.temperatura    = 0
                self.humedad_suelo  = 0
                self.humedad_ambiente  = 0
                self.luz  = 0
                self.caudal  = 0
                self.bomba_activa  = 0
                self.__flag_datos  = 0
                self.__arreglo_datos = []

        def save(self,datos):
                i = 0
                self.__arreglo_datos = []
                while(i < len(datos)):
                    cadena = ""
                    while(datos[i]) != 32:
                        cadena = cadena + chr(datos[i])
                        i += 1
                    if cadena != "":
		    	self.__arreglo_datos.append(cadena)
                    i += 1
		#print self.__arreglo_datos
                self.__flag_datos = 1

        def print_datos(self):
                print "\nTemperatura: %s \nHumedad: %s" % (self.temperatura,self.humedad)

        def obtener_datos(self):
                self.send(chr(103))
                while not self.__flag_datos:
                        pass
                self.__flag_datos = 0
                self.temperatura = self.__arreglo_datos[0]
                self.humedad_suelo = self.__arreglo_datos[1]
                self.humedad_ambiente = self.__arreglo_datos[2]
                self.luz = self.__arreglo_datos[3]
                self.caudal = self.__arreglo_datos[4]
                self.bomba_activa = self.__arreglo_datos[5]
                print self.__arreglo_datos
                return self.__arreglo_datos
