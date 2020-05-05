/*
Simulacion de Maquina de Turing
Dise�ar una M�quina de Turing que, dada una palabra w del alfabeto S={0, 1}, proporciona su reverso, wR.
*/
#include<iostream>
#include <fstream>
using namespace std;
//Se declara la cinta como global ya que en una maquina de Turing es un elemento que debe estar simpre disponible y accesible
string cinta, inversa;
// variable que indicara el desplazamiento de la maquina sobre la cinta, un aumento: significa movimiento a la derecha, 
// un decremento: movimiento a la izquierda 
int i=1; 
// Variable que indica cuando se llega al estado valida
bool valida=false;
// Variable de tipo archivo para guradar la ejecucion de la maquina de Turing 
ofstream archivo;
// Funcion que imprime completamente la cinta de la maquina
string imprimeCinta(void){
	return cinta;
}
// funcion de cinta para retornar el valor de la cinta
char valorCinta(){
	return cinta[i]; 
}
void cintaMaquina(char escribir, char mov){
	cinta[i]=escribir;
	if(mov=='R'){
		i++;
	}
	if(mov=='L'){
		i--;
	}
}
// declaracion de las funciones que se utilizaran como estados
void estado_q0(void);
void estado_q1(void);
void estado_q2(void);
void estado_q3(void);
void estado_q4(void);
void estado_q5(void);
void estado_q6(void);
void estado_q7(void);
void estado_q8(void);
void estado_q9(void);
/// Funcion que ayudara a la confeccion de la cinta, para la utilizacion de los espacios en blanco reqeridos por las transiciones, 
// que indican cada una de las reglas
void agregaBlanco(void){
	int j;
	for (j=cinta.size();j>=0;j--){
		cinta=cinta+" ";
	}
	cinta="  "+cinta;
	
}
/// definicion de cada funcion que serviran como estado y sus repectivas reglas. 
void estado_q0(void){
	if(valida==false){
		cout<<"estado q0 cinta: "<<imprimeCinta()<<endl;
		archivo << "estado q0 cinta: " <<imprimeCinta()<<endl;
		if(valorCinta()=='1'){
			 cintaMaquina('1','L');
			estado_q0();
		}
		if(valorCinta()=='0'){
			cintaMaquina('0','L');
			estado_q0();
		}
		if(valorCinta()==' '){
			cintaMaquina('A','R');
			estado_q1();
		}
	}
}
void estado_q1(void){
	if(valida==false){
		cout<<"estado q1 cinta: "<<imprimeCinta()<<endl;
		archivo << "estado q1 cinta: " <<imprimeCinta()<<endl;
	    if(valorCinta()=='1'){
	    	cintaMaquina('1','R');
			estado_q1();
		}
		if(valorCinta()=='0'){
			cintaMaquina('0','R');
			estado_q1();
		}
		if(valorCinta()==' '){
			cintaMaquina('Z','L');
			estado_q2();
		}
	}
}
void estado_q2(void){
	if(valida==false){
		cout<<"estado q2 cinta: "<<imprimeCinta()<<endl;
		archivo<<"estado q2 cinta: "<<imprimeCinta()<<endl;
	    if(valorCinta()==' '){
	    	cintaMaquina(' ','L');
			estado_q2();
		}
		if(valorCinta()=='0'){
			cintaMaquina(' ','R');
			estado_q6();
		}
		if(valorCinta()=='A'){
			cintaMaquina(' ','L');
			////// situacion especial no te puedes ir mas a la izquierda
			estado_q8();
		}
		if(valorCinta()=='1'){
			cintaMaquina(' ','R');
			estado_q3();
		}
	}
}
void estado_q3(void){
	if(valida==false){
		cout<<"estado q3 cinta: "<<imprimeCinta()<<endl;
		archivo<<"estado q3 cinta: "<<imprimeCinta()<<endl;
	    if(valorCinta()==' '){
			cintaMaquina(' ','R');
			estado_q3();
		}
		if(valorCinta()=='Z'){
			cintaMaquina('Z','R');
			estado_q4();
		}
	}
}
void estado_q4(void){
	if(valida==false){
		cout<<"estado q4 cinta: "<<imprimeCinta()<<endl;
		archivo<<"estado q4 cinta: "<<imprimeCinta()<<endl;
	    if(valorCinta()=='1'){
			cintaMaquina('1','R');
			estado_q4();
		}
		if(valorCinta()=='0'){
			cintaMaquina('0','R');
			estado_q4();
		}
		if(valorCinta()==' '){
			cintaMaquina('1','L');
			estado_q5();
		}	
	}
}
void estado_q5(void){
	if(valida==false){
		cout<<"estado q5 cinta: "<<imprimeCinta()<<endl;
		archivo<<"estado q5 cinta: "<<imprimeCinta()<<endl;
	    if(valorCinta()=='1'){
			cintaMaquina('1','L');
			estado_q5();
		}
		if(valorCinta()=='0'){
			cintaMaquina('0','L');
			estado_q5();
		}
		if(valorCinta()=='Z'){
			cintaMaquina('Z','L');
			estado_q2();
		}
	}
}
void estado_q6(void){
	if(valida==false){
		cout<<"estado q6 cinta: "<<imprimeCinta()<<endl;
		archivo<<"estado q6 cinta: "<<imprimeCinta()<<endl;
	    if(valorCinta()==' '){
			cintaMaquina(' ','R');
			estado_q6();
		}
		if(valorCinta()=='Z'){
			cintaMaquina('Z','R');
			estado_q7();
		}
	}
}
void estado_q7(void){
	if(valida==false){
		cout<<"estado q7 cinta: "<<imprimeCinta()<<endl;
		archivo<<"estado q7 cinta: "<<imprimeCinta()<<endl;
	    if(valorCinta()=='1'){
			cintaMaquina('1','R');
			estado_q7();
		}
		if(valorCinta()=='0'){
			cintaMaquina('0','R');
			estado_q7();
		}
		if(valorCinta()==' '){
			cintaMaquina('0','L');
			estado_q5();
		}
	}
}
void estado_q8(void){
	if(valida==false){
		cout<<"estado q8 cinta: "<<imprimeCinta()<<endl;
		archivo<<"estado q8 cinta: "<<imprimeCinta()<<endl;
	    if(valorCinta()==' '){
			cintaMaquina(' ','R');
			estado_q8();
		}
		if(valorCinta()=='Z'){
			cintaMaquina(' ','R');
			estado_q9();
		}	
	}
}
void estado_q9(void){
    cout<<"==> Llega al estado valido Q9 <=="<<endl;
    cout<<"\t=> La maquina se detiene"<<endl;
    valida=true;
	cout<<"\tQ9 -> Valor de la cinta: "<<cinta<<endl;
	////////
	archivo<<"==> Llega al estado valido Q9 <=="<<endl;
    archivo<<"\t=> La maquina se detiene"<<endl;
	archivo<<"\t-> Valor de la cinta en Q9: "<<imprimeCinta()<<endl;	
    for(int k=0;k<cinta.size();k++){
    	if(cinta[k]!=' '){
    		inversa=cinta.substr(k,k);
    		break;
		}
	}
}
int main(){
	string cadena;
	bool esValida=false;
	int inicio,final;
	archivo.open("datos.txt");
	archivo << "Maquina de Turing" <<endl;
	cout<<"** Simulacion Maquina de Turing **"<<endl;
	cout<<" -> Problema 1"<<endl;
	cout<< "\tDise�ar una Maquina de Turing que, dada una palabra w del alfabeto S={0, 1},\n\tproporciona su reverso, wR."<<endl;
	cout<<"\nNota: nombre del archivo de salida es: datos.txt"<<endl;
	cout<<"Escribe una cadena: ";
	getline(cin,cinta);
	cout<<"\n";
	for(int j=0;j<cinta.size();j++){
		if(cinta[j]=='0' || cinta[j]=='1' ){
			esValida=true;
			inicio=j;
		    i=j+1;
			break;
		}
	}
	for(int k=inicio;k<cinta.size();k++){
		if(cinta[k]==' '){
			final=k;
			for(int m=k;m<cinta.size();m++){
				if(cinta[m]=='0' || cinta[m]=='1'){
					esValida=false;
				}
			}
			break;
		}else{
			final=cinta.size();
		}
	}
	i=final;
	if(cinta.empty() || esValida==false){
		cout<<"Cadena No Valida!!"<<endl;
	}else {
		cadena=cinta.substr(inicio,final);
		agregaBlanco();
		estado_q0();
		if(valida==false){
			cout<<"Cadena No Valida!!"<<endl;
		}else {
		cout<<"Cadena: "<<cadena<<endl;
		cout<<"Cadena Inversa: "<<inversa<<endl;	
			}	
	}	
	
	archivo.close();
}
