/*maquina de Turing de suma concatenada*/

using System;
using System.Collections.Generic;
using System.IO;    //libreria para poder crear y escribir en un archivo

namespace _160108_maquinaTuring2
{
    public struct rule          //estructura de datos publica y accesible desde cualquier punto del programa
    {                           //consiste en las reglas que puede tener la transicion entre 2 estados en una maquina de turing 
        public char input;      //el caracter que se analiza
        public char replace;    //el caracter con el que sera remplaado 
        public int move;        //movimiento hacia izquierda o derecha de la cinta/buffer
        public string nextNode; //nombre del siguiente nodo con el que se analizará a la cinta
    }
    class node                  //clase que funge como nodo o estado de una maquina de turing
    {
        public string name;     //nombre o identificador de nodo o estado . P.Ej "q0"
        public List<rule> rules = new List<rule>(); //lista de las reglas o transiciones que tiene un nodo 
    }
    class Program
    {
        public static void initTuringMachine(ref List<node> lista)  //metodo que llena la maquina de turing de suma con sus respectivos nodos y cada nodo con sus reglas o transiciones 
        {

            node q0 = new node();   //se declara un objeto tipo nodo
            q0.name = "q0";         //se nombra con un identificador
            rule r;                 //se declara un objeto de tipo rule; sera una nueva regla
            r.input = '1'; r.replace = '1'; r.move = 1; r.nextNode = "q1";  //llenado de regla
            q0.rules.Add(r);        //se añade regla a la lista de reglas del nodo
            lista.Add(q0);          //Se añade nodo completo a la maquina de turing

            node q1 = new node();   //se repite la misma estrctura con los siguientes nodos
            q1.name = "q1";
            r.input = '0'; r.replace = '0'; r.move = 1; r.nextNode = "q1";
            q1.rules.Add(r);
            r.input = '1'; r.replace = '1'; r.move = 1; r.nextNode = "q1";
            q1.rules.Add(r);
            r.input = ' '; r.replace = ' '; r.move = -1; r.nextNode = "q2";
            q1.rules.Add(r);
            lista.Add(q1);

            node q2 = new node();
            q2.name = "q2";
            r.input = '1'; r.replace = '1'; r.move = -1; r.nextNode = "q2";
            q2.rules.Add(r);
            r.input = '0'; r.replace = '1'; r.move = 1; r.nextNode = "q3";
            q2.rules.Add(r);
            lista.Add(q2);

            node q3 = new node();
            q3.name = "q3";
            r.input = '1'; r.replace = '0'; r.move = 1; r.nextNode = "q4";
            q3.rules.Add(r);
            lista.Add(q3);

            node q4 = new node();
            q4.name = "q4";
            r.input = '0'; r.replace = '0'; r.move = -1; r.nextNode = "q4";
            q4.rules.Add(r);
            r.input = ' '; r.replace = ' '; r.move = -1; r.nextNode = "q4";
            q4.rules.Add(r);
            r.input = '1'; r.replace = '1'; r.move = -1; r.nextNode = "q5";
            q4.rules.Add(r);
            lista.Add(q4);

            node q5 = new node();
            q5.name = "q5";
            r.input = '1'; r.replace = '1'; r.move = -1; r.nextNode = "q5";
            q5.rules.Add(r);
            r.input = '0'; r.replace = '1'; r.move = 1; r.nextNode = "q3";
            q5.rules.Add(r);
            r.input = ' '; r.replace = ' '; r.move = 1; r.nextNode = "q6";
            q5.rules.Add(r);
            lista.Add(q5);

            node q6 = new node();
            q6.name = "q6";
            r.input = '1'; r.replace = '1'; r.move = 1; r.nextNode = "q6";
            q6.rules.Add(r);
            r.input = '0'; r.replace = ' '; r.move = 1; r.nextNode = "q7";
            q6.rules.Add(r);
            lista.Add(q6);

            node q7 = new node();
            q7.name = "q7";
            r.input = '0'; r.replace = ' '; r.move = 1; r.nextNode = "q7";
            q7.rules.Add(r);
            r.input = ' '; r.replace = ' '; r.move = -1; r.nextNode = "q8";
            q7.rules.Add(r);
            lista.Add(q7);

            node q8 = new node();
            q8.name = "q8";
            r.input = ' '; r.replace = ' '; r.move = 0; r.nextNode = "q8";
            q8.rules.Add(r);
            lista.Add(q8);
        }
        
        public static void imprime(char[] cadena, char[] arrow) //funcion que imprime en la consola el estado de la cinta y la posicion en la que se encuentra trabajando
        {   
                Console.WriteLine(cadena);
                Console.WriteLine(arrow);  
        }

        public static void archivoReglas(List<node> tm)         //funcion que crea un archivo de texto con las reglas y nodos de la maquina de turing
        {
            using (StreamWriter sw = File.CreateText("reglasSumaTuring.txt"))   //metodo para poder crear un archivo de texto
            {                                                                   //se requiere que todo aquello que se escriba en el archivo esté entre llave
                for(int i = 0;i < tm.Count; i++)        //se cuentan los nodos
                {
                    sw.WriteLine("\n\nEstado: " + tm[i].name);  //se escribe el identificador del nodo
                    sw.WriteLine("Reglas");
                    for(int j = 0;j < tm[i].rules.Count ; j++)  //se cuentan las reglas del nodo en cuestion
                    {
                        sw.Write("\n"+tm[i].rules[j].input);        //impresion de las reglas
                        sw.Write(" " + tm[i].rules[j].replace);
                        sw.Write(" " + tm[i].rules[j].move);
                        sw.Write(" " + tm[i].rules[j].nextNode);
                    }
                }
            }
        }

        static void Main(string[] args)
        {
            List<node> tm = new List<node>();       //declaracion de la maquina de turing como lista (tabla hash por la lista dentro del tipo node)
            initTuringMachine(ref tm);              //se llena la maquina con los nodos y trnasiciones
            archivoReglas(tm);                      //se crea un archivo de texto con las reglas de la maquina de turing
            

            Console.WriteLine("Maquina de turing de suma\n ejemplo: 111011 (3+2)");
            Console.WriteLine("Escribe el primer numero");              //se pide al usuario que dicte 2 numeros
            String num1 = Console.ReadLine();
            Console.WriteLine("Escribe el segundo numero");
            String num2 = Console.ReadLine();

            String cad = "";
            cad = " " + cad + num1 + "0" + num2 + " ";      //se concatenan ambos numeros en el formato requerido
            char[] cadena = cad.ToCharArray();              //se separa en un arreglo de caracteres para un mejor manejo de la cinta
            char[] arrow = new char[cadena.Length];         //arreglo del mismo tamaño que muestra una flecha, indicando la posicion en la que se encuentra la maquina analizando la cinta
            for (int i = 0; i < cadena.Length; i++)         //llenado del arreglo de flecha
            {
                arrow[i] = ' ';
            }
            int pos = 1;                                    //posicion de inicio de la cinta
            arrow[1] = '^';                                 //se indica la posicion inicial
            Console.Clear();                                //se limpia la pantalla para dejar unicamente las operaciones

            string currentNode = "q0";                      //varaible que funge como identificador de en que estado se encuentra la maquina / comprador con la lista de nodos
            bool error = false;                             //booleano auxiliar que permite parar la maquina si hay un error
            bool findRule = false;                          //booleano auxiliar, complemento de "error"; se activa en caso de que no se encuentre una regla que coincida con la cinta
            using (StreamWriter sw = File.CreateText("sumaTuring.txt"))     //usado para guardar datos en un archivo .txt
            {
                while (error != true && currentNode != "q8")        //la maquina trabaja hasta que encuentre un error o llegue al nodo final
                {
                    findRule = false;
                    Console.WriteLine("Estado: " + currentNode);    //impresioin en consola
                    imprime(cadena, arrow);
                    sw.WriteLine("Estado: " + currentNode);         //impresion en archivo
                    sw.WriteLine(cadena);
                    sw.WriteLine(arrow);
                    for (int i = 0; i < tm.Count; i++)  //se recorre toda la lista hasta encontrar el noodo que sigue
                    {
                        if (currentNode == tm[i].name)
                        {
                            for (int j = 0; j < tm[i].rules.Count; j++)     //si se encuentra el nodo, se busca una regla que coincida con la cinta
                            {
                                if (cadena[pos] == tm[i].rules[j].input)
                                {
                                    cadena[pos] = tm[i].rules[j].replace;   //si se encuentra, se realiza la transicion
                                    arrow[pos] = ' ';                       //se borra la posicion de la flecha
                                    pos += tm[i].rules[j].move;             //movimiento de flecha indicadora a la izquierda o derecha
                                    arrow[pos] = '^';                       //se imprime la flecha en su uneva posicion, indicando la posicion de la cinta
                                    currentNode = tm[i].rules[j].nextNode;  //se indica que cambio de nodo o estado
                                    findRule = true;
                                }
                                if (findRule == true)       //si encuentra una regla, sale del ciclo
                                {
                                    break;
                                }
                            }
                            if (findRule == false)          //si no encuentra una regla que coincida con la cinta, se marca error y para la maquina
                            {
                                Console.WriteLine("Error en nodo " + tm[i].name);
                                sw.WriteLine("Error en nodo " + tm[i].name);
                                error = true;
                                break;
                            }
                            else
                            {
                                break;    //de lo contrario, solo sale del ciclo y continua
                            }
                        }
                    }
                }
                if (error == false)         //si no hubo error, marca el ultimo nodo de la maquina como salida exitosa
                {
                    Console.WriteLine("Estado: " + currentNode);
                    imprime(cadena, arrow);
                    Console.WriteLine("Operacion finalizada");
                    sw.WriteLine("Estado: " + currentNode);
                    sw.WriteLine(cadena);
                    sw.WriteLine(arrow);
                    sw.WriteLine("Operacion finalizada");
                }
            }
        }
    }
}
