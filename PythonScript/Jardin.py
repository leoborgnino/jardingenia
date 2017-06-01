from Obj_Head import Obj_Head
import struct
import math

class jardin(Obj_Head):

        def __init__(self,com):
                Obj_Head.__init__(self,com,self.save)
                self.temperatura    = 0
                self.humedad        = 0
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
                self.humedad = self.__arreglo_datos[1]
                return self.__arreglo_datos
