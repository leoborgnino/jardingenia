import matplotlib.pyplot as plt

# Abrir el archivo
archivo_datos = open('data-log.log','r')

# Leerlo por lineas (aca tengo un arreglo de datos donde cada elemento es una linea del texto)
lines = archivo_datos.readlines()

# Reemplazo los caracteres de escape por espacios (replace) y hago un split (separo las lineas en filas donde cada elemento es un dato). Obtengo una matriz de 500x6
splitted_data = []
for i in lines:
    data_replace = i.replace("\n","").replace("\t\t\t"," ")
    splitted_data.append(data_replace.split())
    
#print splitted_data

temp = []
HumS = []
Caudal = []
Flujo = []

PLOT_WINDOW = 230#len(splitted_data)-1

for i in range(PLOT_WINDOW):
    temp.append(splitted_data[i+1][0])
    HumS.append(splitted_data[i+1][1])
    Caudal.append(splitted_data[i+1][4])
    Flujo.append(splitted_data[i+1][5])

x = []
for i in range(len(temp)):
    x.append(i)
    

# Ploteo tres variables

f, (ax1, ax2, ax3) = plt.subplots(3, sharex=True, sharey=False)
ax1.scatter(x, Flujo,color='g')
ax1.set_title('Datos Jardin')
ax2.scatter(x, Caudal)
ax3.scatter(x, HumS, color='r')
#f.subplots_adjust(hspace=0)
plt.setp([a.get_xticklabels() for a in f.axes[:-1]], visible=False)
plt.show()
