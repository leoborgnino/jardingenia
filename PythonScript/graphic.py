#!/usr/bin/python

import urllib
from math import radians
import time
import math
import matplotlib.pyplot as plt
import numpy as np
import random


class grafico:

    def __init__(self,jardin):
        self.jardin = jardin
        # self.hl, = plt.plot([],[])

    def read_values(self):
        self.jardin.obtener_datos()
        return [self.jardin.temperatura, self.jardin.humedad_suelo, self.jardin.humedad_ambiente, self.jardin.caudal]

    def run(self):
        counter = 0
        array = []
        array_temperatura = []
        array_humedadS = []
        array_humedadA = []
        array_flujo = []
        while True:
            counter = counter + 1
            values = self.read_values()
            print values[0]
            array.append(counter)
            array_temperatura.append(values[0])
            array_humedadS.append(values[1])
            array_humedadA.append(values[2])
            array_flujo.append(values[3])
            plt.clf()
            temperatura_plot = plt.subplot(221)
            temperatura_plot.plot(array,array_temperatura, 'r')
            temperatura_plot.set_ylim([15,40])
            temperatura_plot.grid(True)
            temperatura_plot.set_title("Temperatura", va='bottom')
            humedad_plot = plt.subplot(222)
            humedad_plot.plot(array,array_humedadS, 'b')
            humedad_plot.set_ylim([0,100])
            humedad_plot.grid(True)
            humedad_plot.set_title("Humedad del Suelo", va='bottom')
            humedadA_plot = plt.subplot(223)
            humedadA_plot.plot(array,array_humedadA, 'b')
            humedadA_plot.set_ylim([40,100])
            humedadA_plot.grid(True)
            humedadA_plot.set_title("HumedadA del Ambiente", va='bottom')
            flujo_plot = plt.subplot(224)
            flujo_plot.plot(array,array_flujo, 'b')
            flujo_plot.set_ylim([0,50])
            flujo_plot.grid(True)
            flujo_plot.set_title("Flujo (L/min)", va='bottom')
            plt.draw()
            plt.show(block=False)
            time.sleep(0.5)
