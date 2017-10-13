import random

ROW_LENGTH = 500
RIEGO_PERIOD = int(ROW_LENGTH/5)
LOW_THRESHOLD = 2.
HIGH_THRESHOLD = 80.

archivo_random = open('data-log.log', 'w')

archivo_random.write("Temp		    	HumS		    	HumA		    	Luz			        Caudal			  Flujo			\n")

hum_s = 0.
flujo = 0.

for i in range(ROW_LENGTH):
    temp = 20 + random.uniform(0, 5)
    if (hum_s <= LOW_THRESHOLD):
        flujo = 1
    elif (hum_s > HIGH_THRESHOLD):
        flujo = 0
    if (flujo == 1):
        hum_s = hum_s + random.uniform(0, LOW_THRESHOLD)
        caudal = random.uniform(10,20)
    else:
        if (hum_s < LOW_THRESHOLD):
            hum_s = hum_s
        else:
            hum_s = hum_s - random.uniform(0, LOW_THRESHOLD)
        caudal = 0.
    hum_a = 80 + random.uniform(0, 5)
    luz = 261.00
    archivo_random.write("%f			%f			%f			%f			%f			%f			\n"%(temp,hum_s,hum_a,luz,caudal,flujo))
