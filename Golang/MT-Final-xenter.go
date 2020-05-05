package main
import (
	"fmt"//Funciones básicas
	"strconv"//Funciones para strings
	"os"//Funciones para operar el funcionamiento del sistema
	"os/exec"//Ejecuta comandos externos
	//"time"//Provee funcionalidades para medir el tiempo
  "bufio" //Funcionalidades I/O
)
//Matriz de transiciones
var estados = [][]string {
	{"0L0","1L0","AR1","-","-"},
	{"0R1","1R1","ZL2","-","-"},
	{"bR6","bR3","bL2","-","bL8"},
	{"-","-","bR3","ZR4","-"},
	{"0R4","1R4","1L5","-","-"},
	{"0L5","1L5","-","ZL2","-"},
	{"-","-","bR6","ZR7","-"},
	{"0R7","1R7","0L5","-","-"},
	{"-","-","bR8","bR9","-"},
}
//Variables
var cinta []string
var str string
var alf int
//Función que crea la cinta
func creaCinta(){
	i := 0
	cinta = append(cinta, "b", "b")
	for i < len(str){
		cinta = append(cinta, string(str[i]))
		i++
	}
	cinta = append(cinta, "b", "b")
}
//Función que mueve la posisción en la cinta y
//se posiciona en la matriz de transiciones
func mover(edo int, move int){
  //Obtiene lo que esta en la cinta
	aux := string(cinta[move])
  //Obtiene la "j" de la matriz
	if aux == "0" { alf = 0 }
	if aux == "1" { alf = 1 }
	if aux == "b" { alf = 2 }
	if aux == "Z" { alf = 3 }
	if aux == "A" { alf = 4 }

	fmt.Println("S( q",edo,",",alf,")")
  //Obtiene la posicion de la matriz
	sig := estados[edo][alf]
  //Obtiene loq ue se va a escribir, la dirección
  //y el estado a donde va
	escribe := string(sig[0])
	dir := string(sig[1])
	edo, err:= strconv.Atoi(string(sig[2]))
  //Sobreescribe en la cinta
	cinta[move] = escribe
  //Aumenta o disminuye en uno "move" para la dirección
  if dir == "L" { move-- }
	if dir == "R" { move++ }
  //Aumenta espacios en blanco para que no haya desborde en la cinta
	if edo == 3 && aux == "b" { cinta = append(cinta, "b", "b") }
  if edo == 6 && aux == "b" { cinta = append(cinta, "b", "b") }

	imprimir(edo,escribe,dir)
	fmt.Println(err)
  //Si el estado llega a 9, éste es el final
  //por lo tanot termina el programa
	if edo == 9 { os.Exit(3) }
  //Llama la función clear()
  clear()
  //Se llama a si mismo, pasando el estado y dirección siguiente
	mover(edo, move)
}
//Limpia la pantalla en 1 segundo cada estado
func clear(){
  reader:=bufio.NewReader(os.Stdin)
  r, _, err :=reader.ReadRune()
  if(r == 'x'){
  //  duracion:= time.Duration(1)*time.Second
  	//time.Sleep(duracion)
    fmt.Println(err)
  	cmd:= exec.Command("clear")
  	cmd.Stdout = os.Stdout
  	cmd.Run()
  }
}
func imprimir(edo int, e string, d string){
	fmt.Println(" = ( q",edo,", ",e,", ",d," )")
	fmt.Println(cinta)
}
//Comienzo del programa
func main() {
	fmt.Println("Ingrese cadena: ")
	fmt.Scanln(&str)
  i:=0
  for i < len(str){//Valida la cadena
		if string(str[i]) == "0" || string(str[i]) == "1"{

    }else{
      fmt.Println("Cadena no válida")
      os.Exit(3)
    }
    i++
	}
  fmt.Println("Cadena válida")
	creaCinta()
	move := len(cinta)-3 //Empeza al final de la cadena
	mover(0,move)
}
