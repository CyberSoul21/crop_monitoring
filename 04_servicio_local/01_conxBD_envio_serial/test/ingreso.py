


import pymysql

db = pymysql.connect("mynodered.ddns.net","usuariow","usuariow","monitoreo2")
cursor = db.cursor()

cursor.execute("SELECT Planta, Valor FROM monitoreo2")
resultado = cursor.fetchall()
for x in resultado:
    #resultado = cursor.fetchall()
    a1, b1, c1, d1, e1, f1, g1, h1= resultado
    A1, A2= a1
    B1, B2= b1
    C1, C2= c1
    D1, D2= d1
    E1, E2= e1
    F1, F2= f1
    G1, G2= g1
    H1, H2= h1

#condicion para temperatura valida planta 2
if A2 > 10 and A2 < 20:
    A3 =  1
elif A2 <= 10:
    A3 = 0
elif A2 >= 20:
    A3 = 0

#condicion para humedad valida planta 2
if B2 > 10 and B2 < 20:
    B3 =  1
elif B2 <= 10:
    B3 = 0
elif B2 >= 20:
    B3 = 0

#condicion para luz valida planta 2
if C2 > 10 and C2 < 20:
    C3 =  1
elif C2 <= 10:
    C3 = 0
elif C2 >= 20:
    C3 = 0

#condicion para CO valida planta 2
if D2 > 10 and D2 < 20:
    D3 =  1
elif D2 <= 10:
    D3 = 0
elif D2 >= 20:
    D3 = 0

#condicion para temperatura valida planta 1
if E2 > 10 and E2 < 20:
    E3 =  1
elif E2 <= 10:
    E3 = 0
elif E2 >= 20:
    E3 = 0

#condicion para humedad valida planta 1
if F2 > 10 and F2 < 20:
    F3 =  1
elif F2 <= 10:
    F3 = 0
elif F2 >= 20:
    F3 = 0

#condicion para luz valida planta 1
if G2 > 10 and G2 < 20:
    G3 =  1
elif G2 <= 10:
    G3 = 0
elif G2 >= 20:
    G3 = 0

#condicion para CO valida planta 1
if H2 > 10 and H2 < 20:
    H3 =  1
elif H2 <= 10:
    H3 = 0
elif H2 >= 20:
    H3 = 0


enviar = str(A1) + ":" + str(A2) + ":" + str(A3) + ":" + str(B2) + ":" + str(B3) + ":" + str(C2) + ":" + str(C3) + ":" + str(D2) + ":" + str(D3)
enviar2 = str(E1) + ":" + str(E2) + ":" + str(E3) + ":" + str(F2) + ":" + str(F3) + ":" + str(G2) + ":" + str(G3) + ":" + str(H2) + ":" + str(H3)
print (enviar)
print (enviar2)
#print (A1, A2, A3)
#print (B1, B2, B3)
#print (C1, C2, C3)
#print (D1, D2, D3)
#print (E1, E2, E3)
#print (F1, F2, F3)
#print (G1, G2, G3)
#print (H1, H2, H3)



db.close()
