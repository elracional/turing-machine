#include <iostream>//muchas librerias por que librerias
#include <cstdlib>
#include <string>
#include <fstream>
#include "estados.cpp"//estados de la maquina
using namespace std;

int main()//principal
{
	string palabra;//palabra a utilizar
	char a;
	int band = 0;//bandera para validar solo un #
	//obtenemos la palabra a validar
	cout << "introdusca la palabra: "<< endl;
	getline(cin, palabra);
	//validamos que la palabra tenga el formato de la maquina de turing con su alfabeto
	for (int x = 0; x < palabra.length(); x++) {
		a = palabra[x];//para mas placer
		if (a != '0' && a != '1' && a != '2' && a != '#') {// en caso de no pertenesca al alfabeto
			cout << "Caracteres no validos";//cuando los caracteres no son validos
			return 0;
		}
		else {
			if (a == '#')//para verificar que # solo aparece una vez
				band++;
		}
	}

	if (band != 1) {//eso
		cout << "cantidad de simbolos '#' diferente a los necesarios";
		return 0;
	}

	Cinta* xd = (Cinta*)malloc(sizeof(Cinta));//primer elemento de la cinta
	act = xd;//actual
	act->did = palabra[0];//definimos VALORES del actual
	act->L = NULL;
	act->R = NULL;
	for (int x = 1; x < palabra.length(); x++) {//letra a letra la cinta no se agota
		crear('R', palabra[x]);//agregamos cada letra a su propio struct
		act=act->R;//pasamos a el siguiente struct
	}
	
	act = xd;//volvemos al principio denuevo
	ini = xd;
	string pl = palabra + ".txt";
	arch.open(pl);
	arch << palabra<<endl;
	q0();//iniciar maquina de turing
	arch.close();
	//creamos la cinta
	return 0;
}
