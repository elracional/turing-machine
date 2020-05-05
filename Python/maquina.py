import sys
class mt:
    # cadena = []

    def __init__(self):
        self.__tabla = {}
        self.__estado_inicial = ""
        self.__estado_final = ""
        self.cadena = []
        self.delta()
    def agrega_transicion(self, estado, simbolo, nuevo_estado,nuevo_simbolo, accion):
        try:
            self.__tabla[estado]
        except KeyError:
            self.__tabla[estado] = {}
            
        try:
            self.__tabla[estado][simbolo]
        except KeyError:
            self.__tabla[estado][simbolo] = {}
            
        if type(nuevo_estado) == str:
            self.__tabla[estado][simbolo] = (nuevo_estado,nuevo_simbolo,accion)
        else:
            self.__tabla[estado][simbolo] = zip(nuevo_estado,nuevo_simbolo,accion)
    
    def agrega_estado_inicial(self, estado):
        if type(estado) == str:
            self.__estado_inicial=estado
    
    def agrega_estado_final(self, estado):
        if type(estado) == str:
            self.__estado_final=estado
    
    def delta(self):
        self.agrega_estado_inicial("q0")
        self.agrega_estado_final("q9")
        #estado, simbolo, nuevo_estado, nuevo_simbolo, accion
        #-------------------I------------------------
        #δ(q0,0)=(q0,0,L)
        self.agrega_transicion("q0","0","q0","0","L")
        #δ(q0,1)=(q0,1,L)
        self.agrega_transicion("q0","1","q0","1","L")
        #δ(q0,B)=(q1,A,L)
        self.agrega_transicion("q0","B","q1","A","R")
        #-------------------II-----------------------
        #δ(q1,0)=(q1,0,R)
        self.agrega_transicion("q1","0","q1","0","R")
        #δ(q1,1)=(q1,1,R)
        self.agrega_transicion("q1","1","q1","1","R")
        #δ(q1,B)=(q2,Z,L)
        self.agrega_transicion("q1","B","q2","Z","L")
        #-------------------III----------------------
        #δ(q2,B)=(q2,B,L)
        self.agrega_transicion("q2","B","q2","B","L")
        #δ(q2,A)=(q8,B,L)
        self.agrega_transicion("q2","A","q8","B","L")
        #δ(q2,1)=(q3,B,R)
        self.agrega_transicion("q2","1","q3","B","R")
        #δ(q2,0)=(q6,B,R)
        self.agrega_transicion("q2","0","q6","B","R")
        #-------------------IV-----------------------
        #δ(q8,B)=(q8,B,R)
        self.agrega_transicion("q8","B","q8","B","R")
        #δ(q8,Z)=(q9,B,R)
        self.agrega_transicion("q8","Z","q9","B","R")
        #-------------------V------------------------
        #δ(q3,B)=(q3,B,R)
        self.agrega_transicion("q3","B","q3","B","R")
        #δ(q3,Z)=(q4,Z,R)
        self.agrega_transicion("q3","Z","q4","Z","R")
        #δ(q4,B)=(q5,1,L)
        self.agrega_transicion("q4","B","q5","1","L")
        #δ(q4,0)=(q4,0,R)
        self.agrega_transicion("q4","0","q4","0","R")
        #δ(q4,1)=(q4,1,R)
        self.agrega_transicion("q4","1","q4","1","R")
        #-------------------VI-----------------------
        #δ(q5,0)=(q5,0,L)
        self.agrega_transicion("q5","0","q5","0","L")
        #δ(q5,1)=(q5,1,L)
        self.agrega_transicion("q5","1","q5","1","L")
        #δ(q5,Z)=(q2,Z,L)
        self.agrega_transicion("q5","Z","q2","Z","L")
        #-------------------VII----------------------
        #δ(q6,B)=(q6,B,R)
        self.agrega_transicion("q6","B","q6","B","R")
        #δ(q6,Z)=(q7,Z,R)
        self.agrega_transicion("q6","Z","q7","Z","R")
        #δ(q7,B)=(q5,0,L)
        self.agrega_transicion("q7","B","q5","0","L")
        #δ(q7,0)=(q7,0,R)
        self.agrega_transicion("q7","0","q7","0","R")
        #δ(q7,1)=(q7,1,R)
        self.agrega_transicion("q7","1","q7","1","R")
        # print (self.__tabla)

    def evaluate(self, string):
        self.cadena = [i for i in string]
        estado_actual=self.__estado_inicial
        # print (estado_actual)
        apuntador=0
        while True:
            try:
                print ("(%s, '%s')" % (estado_actual,self.cadena[apuntador]))
                estado_actual,nuevo_simbolo,accion=self.__tabla[estado_actual][self.cadena[apuntador]]
                self.cadena[apuntador]=nuevo_simbolo
                apuntador+=self.mueve_cinta(accion,apuntador)
                print ("(%s, '%s',%s)" % (estado_actual, nuevo_simbolo,accion))
                # print(apuntador)
            except IndexError:
                break
            except KeyError:
                break
            pass
        # print (estado_actual)
        # print (nuevo_simbolo)
        # print (accion)
        # print (self.cadena[apuntador])
        # print (self.__tabla)
        print (self.cadena)
        return (bool(estado_actual==self.__estado_final))
    def mueve_cinta(self,accion,apuntador):
        if accion == "L":
            if apuntador < 1:
                self.cadena.insert(0,"B")
                return 0
            return -1
        elif accion == "R":
            if apuntador > (len(self.cadena)-2):
                self.cadena.append("B")
            return 1
        elif accion == "S":
            return 0
    def print_mt(self):
        print ("Table")
        for estado in self.__tabla:
            for simbolo in self.__tabla[estado]:
                    print ("(%s, '%s') -> %s" % (estado, simbolo, self.__tabla[estado][simbolo]))
        print ("\nInitial States:")
        print (self.__estado_inicial)
        print ("\nFinal States:")
        print (self.__estado_final)



cadena = input("Escribe una cadena: ")

#code for redirect stdout to a file
orig_stdout = sys.stdout
f = open('out.txt', 'w')
sys.stdout = f
#code for redirect stdout to a file

maquina_turing = mt()
maquina_turing.print_mt()
print (maquina_turing.evaluate(cadena))




#code for redirect stdout to a file
sys.stdout = orig_stdout
f.close()
#code for redirect stdout to a file