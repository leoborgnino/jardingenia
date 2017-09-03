#!/usr/bin/python

import urllib
from math import radians
import time
import math
import matplotlib.pyplot as plt
import numpy as np
import random
import os
import sys


class Logue:
    PATH_OUT= "/home/leo/Documentos/LogFiles/"

    def __init__(self,jardin):
        self.jardin = jardin
        try:
            self.file_out = open(self.PATH_OUT + 'data-data.log','w')
        except IOError, e:
            print 'Error: Cannot write file in: ' + self.PATH_OUT + 'data_data.log'
            sys.exit()
        self.file_out.write("Temp\t\t\tHumS\t\t\tHumA\t\t\tCaudal\t\t\t\n")
    def read_values(self):
        self.jardin.obtener_datos()
        return [self.jardin.temperatura, self.jardin.humedad_suelo, self.jardin.humedad_ambiente, self.jardin.caudal]

    def run(self):
        for i in range (3):
            self.file_out.write("%s \t\t\t" %(self.read_values()[i]))
        self.file_out.write("\n")
        time.sleep(1)
        


    
