#include <iostream>
#include <cstdlib>
#include <string>
#include <fstream>
using namespace std;

void q0();
void q1();
void q2();
void q3();
void q4();
void q5();
void q6();
void q7();
void q8();
void q9();
void impCint();

struct Cinta
{
	char did;
	Cinta* L;
	Cinta* R;
};

Cinta* ini;//ACTUAL
Cinta* act;//INICIAL
//crear nuevo en cinta 'R' para derecha 'L' para izquierda, letra
ofstream arch;
void crear(char dir, char let) {
	Cinta* auch = NULL;
	if (dir == 'R') {//derecha
		act->R = (Cinta*)malloc(sizeof(Cinta));//crear a la derecha
		auch = act->R;//marcador del creado
		auch->L = act;//marcador del creador :O
		auch->R = NULL;//pos meh
	}
	if (dir == 'L') {
		act->L = (Cinta*)malloc(sizeof(Cinta));
		auch = act->L;
		auch->R = act;
		auch->L = NULL;
		if (act->L == NULL)
			ini = act->L;
	}
	auch->did = let;
}

void empty(char dir) {//en caso de encontrar un lado vacio lo creamos como vacio en la cinta
	if (dir == 'R' && act->R == NULL)
		crear(dir, NULL);
	if (dir == 'L' && act->L == NULL)
		crear(dir, NULL);
}

void impCint() {//imprimir cinta
	Cinta* me = ini;
	while (me != NULL) {
		if (me == act){
			cout <<".>"<< me->did <<"<.";
			arch<<".>"<< me->did <<"<.";
		}
		else{
			cout <<"."<< me->did<<".";
			arch<<".>"<< me->did <<"<.";
		}
		me = me->R;
	}
	cout << endl;
	arch <<endl;
}

void inst(char sus, char dir, int est) {//instrucciones  --caracter a sustituir, direccion, estado siguiente
	arch << act->did << "," << sus << ":" << dir << endl;
	cout << act->did << "," << sus << ":" << dir << endl;
	act->did = sus;
	empty(dir);
	switch (dir)
	{
	case 'R':
		act = act->R;
		break;
	case 'L':
		act = act->L;
		break;
	case 'S':
		act = act;
		break;
	default:
		arch<< endl << "direccion incorrecta: " << act->did;
		cout << endl << "direccion incorrecta: " << act->did;//en caso de que sea invalido
		exit(EXIT_FAILURE);//salida de error :(
		break;
	}

	switch (est)
	{
	case 0:
		q0();
		break;
	case 1:
		q1();
		break;
	case 2:
		q2();
		break;
	case 3:
		q3();
		break;
	case 4:
		q4();
		break;
	case 5:
		q5();
		break;
	case 6:
		q6();
		break;
	case 7:
		q7();
		break;
	case 8:
		q8();
		break;
	case 9:
		q9();
		break;
	default:
		cout << endl << "estado incorrecto: " << act->did;//en caso de que sea invalido
		arch<< endl << "estado incorrecto: " << act->did;
		exit(EXIT_FAILURE);//salida de error :(
		break;
	}
}
//pongan atencion por que solo lo explicare una vez
void q0() {
	arch << endl << "estado: q0" << endl;
	cout << endl << "estado: q0" << endl;//el estado q0
	impCint();
	switch (act->did)//marca de la cinta
	{
	case '0'://caso
		inst('X', 'R', 1);//estado mandado llamar (escribir, direccion, estado siguiente)
	case '1':
		inst('X', 'R', 2);
		break;
	case '2':
		inst('X', 'R', 3);
		break;
	case '#':
		inst('#', 'R', 8);
		break;
	default:
		cout << endl << "palabra incorrecta en: "<<act->did;//en caso de que sea invalido
		arch << endl << "palabra incorrecta en: "<<act->did;
		exit(EXIT_FAILURE);//salida de error :(
		break;
	}
}

void q1() {
	arch  << endl << "estado: q1" << endl;
	cout << endl << "estado: q1" << endl;
	impCint();
	switch (act->did)
	{
	case '0':
		inst('0', 'R', 1);
		break;
	case '1':
		inst('1', 'R', 1);
		break;
	case '2':
		inst('2', 'R', 1);
		break;
	case '#':
		inst('#', 'R', 4);
		break;
	default:
		cout << endl << "palabra incorrecta en: "<<act->did;
		arch << endl << "palabra incorrecta en: "<<act->did;
		exit(EXIT_FAILURE);
		break;
	}
}

void q2() {
	arch << endl << "estado: q2" << endl;
	cout << endl << "estado: q2" << endl;
	impCint();
	switch (act->did)
	{
	case '0':
		inst('0', 'R', 2);
		break;
	case '1':
		inst('1', 'R', 2);
		break;
	case '2':
		inst('2', 'R', 2);
		break;
	case '#':
		inst('#', 'R', 6);
		break;
	default:
		cout << endl << "palabra incorrecta en: "<<act->did;
		arch << endl << "palabra incorrecta en: "<<act->did;
		exit(EXIT_FAILURE);
		break;
	}
}

void q3() {
	cout << endl << "estado: q3" << endl;
	arch << endl << "estado: q3" << endl;
	impCint();
	switch (act->did)
	{
	case '0':
		inst('0', 'R', 3);
		break;
	case '1':
		inst('1', 'R', 3);
		break;
	case '2':
		inst('2', 'R', 3);
		break;
	case '#':
		inst('#', 'R', 7);
		break;
	default:
		cout << endl << "palabra incorrecta en: "<<act->did;
		arch << endl << "palabra incorrecta en: "<<act->did;
		exit(EXIT_FAILURE);
		break;
	}
}

void q4() {
	arch << endl << "estado: q4" << endl;
	cout << endl << "estado: q4" << endl;
	impCint();
	switch (act->did)
	{
	case 'Y':
		inst('Y', 'R', 4);
		break;
	case '0':
		inst('Y', 'L', 5);
		break;
	default:
		cout << endl << "palabra incorrecta en: "<<act->did;
		arch << endl << "palabra incorrecta en: "<<act->did;
		exit(EXIT_FAILURE);
		break;
	}
}

void q5() {
	arch << endl << "estado: q5" << endl;
	cout << endl << "estado: q5" << endl;
	impCint();
	switch (act->did)
	{
	case '2':
		inst('2', 'L', 5);
		break;
	case '1':
		inst('1', 'L', 5);
		break;
	case '0':
		inst('0', 'L', 5);
		break;
	case '#':
		inst('#', 'L', 5);
		break;
	case 'Y':
		inst('Y', 'L', 5);
		break;
	case 'X':
		inst('X', 'R', 0);
		break;
	default:
		cout << endl << "palabra incorrecta en: "<<act->did;
		arch << endl << "palabra incorrecta en: "<<act->did;
		exit(EXIT_FAILURE);
		break;
	}
}

void q6() {
	arch << endl << "estado: q6" << endl;
	cout << endl << "estado: q6" << endl;
	impCint();
	switch (act->did)
	{
	case 'Y':
		inst('Y', 'R', 6);
		break;
	case '1':
		inst('Y', 'L', 5);
		break;
	default:
		cout << endl << "palabra incorrecta en: "<<act->did;
		arch << endl << "palabra incorrecta en: "<<act->did;
		exit(EXIT_FAILURE);
		break;
	}
}

void q7() {
	arch << endl << "estado: q7" << endl;
	cout << endl << "estado: q7" << endl;
	impCint();
	switch (act->did)
	{
	case 'Y':
		inst('Y', 'R', 7);
		break;
	case '2':
		inst('Y', 'L', 5);
		break;
	default:
		cout << endl << "palabra incorrecta en: "<<act->did;
		arch << endl << "palabra incorrecta en: "<<act->did;
		exit(EXIT_FAILURE);
		break;
	}
}

void q8() {
	arch << endl << "estado: q8" << endl;
	cout << endl << "estado: q8" << endl;
	impCint();
	switch (act->did)
	{
	case 'Y':
		inst('Y', 'R', 8);
		break;
	case NULL:
		inst(NULL, 'S', 9);
		break;
	default:
		cout << endl << "palabra incorrecta en: "<<act->did;
		arch << endl << "palabra incorrecta en: "<<act->did;
		exit(EXIT_FAILURE);
		break;
	}
}

void q9() {
	impCint();//ganastes, digo la palabra es correcta
	cout << "La palabra es correcta :D" << endl;
	arch << "La palabra es correcta :D" << endl;
	exit(EXIT_SUCCESS);// terminar el proceso
}
