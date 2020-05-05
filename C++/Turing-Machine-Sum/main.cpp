/*

*/
#include <string.h> //librer�a para manejo de cadenas
#include <iostream> //libreria  estandar c++
#include <stdlib.h> 
#include<fstream>//librer�a manejo de archivos
using namespace std; 
char n1[100],n2[100], state[]="q1";
ofstream archivo;//declaraci�n del puntero del archivo
string blank="b";//delimitador de cinta
int cont=1;
bool bandera=true;//bandera para cambio de estado
 
char reglas[9][5][3]={ //matriz de transiciones
		{"q1","1","b","R", "q2"},
		{"q2","1","1","R", "q2"},
		{"q2","+","+","R", "q3"},
		{"q3","1","1","R", "q3"},
		{"q3","b","1","L", "q4"},
		{"q4","+","+","L", "q4"},
		{"q4","1","1","L", "q4"},
		{"q4","b","b","R", "q1"},
		{"q1","+","b","S","q5"}
		};
void leer();//funcion para leer los numeros		 
	
main(){
 	archivo.open("cinta.txt",ios::out);//abriendo archivo
	if(archivo.fail()){ //validaci�n de creaci�n del archivo
		cout<<endl<<"No se pudo abrir el archivo"<<endl;
		exit(true);
	}
 	//cout<<"\n";
  	leer();
  	cout<<blank;
  	cout<<"\n"; 

    while(bandera){
    	//fflush(stdin);
    	int i=0;
 		char *aux, *aux2, *aux3; //apuntadores para los estados de la maquina
		aux2=reglas[i][1];
		if(blank[cont]=='+'){//sirve para la ultia regla donde solo queda el signo + por poner en blanco
			bandera=false;
		}//modificar usando las reglas

  			fflush(stdin);//limpiamos buffer
			aux=reglas[i][2];//a remplazar
			blank[cont]=*aux;//se remplaza
			cont++;//nos movemos a la derecha
			i++;
			strcpy(state,reglas[i][4]); //copiamos en el estado la regla que esta en la matriz
			archivo<<state<<endl;
			while(blank[cont]== *aux2){
	  		cont++;
		  	}  
			i++;

		strcpy(state,reglas[i][4]);////copiamos en el estado por la regla que esta en la matriz
		archivo<<state<<endl;
		aux=reglas[i][2];//remplazamos en el estado 
		cont++;
		i++;
		
		aux2=reglas[i][1];
		while(blank[cont]== *aux2){//mientras encontremos 1's en la cinta seguira recorreindose hasta encontrar espaico en blanco
	  		cont++;
		  } 		  
		i++;
		
		aux=reglas[i][2];//si encontramos un signo '+' se deja y se sigue avanzando
		blank[cont]=*aux;//se remplaza
		strcpy(state,reglas[i][4]);//copiando en el estado la regla
		archivo<<state<<endl;//escribiendo en el estado que se encuentra en el archivo
		i++;
		//llegamos al final de la cinta y recorremos a al izquierda
		aux2=reglas[i][1];
		aux3=reglas[i+1][1];
		while(blank[cont]== *aux2 || blank[cont]== *aux3){
	  		cont--;
		  } 
		cont++;
		cout<<blank<<endl; //mostrando movimientos de la cinta
		archivo<<state<<endl;//escribiendo en el estado que se encuentra en el archivo
  	}
  	archivo.close();
  	system("pause");
  	return 0;
 }  
void leer(){
		int i=0;
		cout<<"Ingresa el primer numero: ";
		cin >> n1;
		cout<<"Ingresa el segundo numero: ";
		cin >> n2;
		blank=blank+n1+"+"+n2;//espacio en blanco al inicio de la cadena
		while(i<strlen(n1)){ //espacios en blanco despues de la cadena
			blank=blank+"b";
			i++;
		}
	}
