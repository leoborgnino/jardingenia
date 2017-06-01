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

    def read_values(self):
        self.jardin.obtener_datos()
        return [self.jardin.temperatura, self.jardin.humedad]

    def run(self):
        while True:
            values = self.read_values()
            print values
            temperatura = values[0]
            humedad = values[1]
            plt.clf()
            ax = plt.subplot(111)
            ax.plot(temperatura, 'r.')
            ax.grid(True)
            ax.set_title("Temperatura", va='bottom')
            plt.draw()
            plt.show(block=False)
