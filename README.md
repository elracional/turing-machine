# Turing Machine

## THEORETICAL FRAMEWORK 
Turing machine 
We call Turing Machine like M = (Σ, T, Q, F, δ) where: 
•	Σ is the alphabet: The finite set of input symbols. 
•	Τ is the set of ribbon symbols. The alphabe-to is a subset of T. 
•	Q is the finite set of states 
•	F is the set of final states. 
•	δ is the function of transitions. 
 
The expression δ (q, X) = (p, Y, D) indicates that in the state q, if the head of the MT points to the ribbon symbol X, 
then the MT writes the ribbon symbol Y in the almost-lla current (changes X to Y) and moves the head almost to D (D can be right, R; 
or left, L) and goes to the state p. 

### Python
I planned to design in Python a turing machine that, given a word of 0's and 1's, could invert this. The solution is much more 
complex than that, in the end it is not only solved the problem, the scope was much higher obtaining a deterministic turing machine 
of a single tape. That I could solve any problem that can be solved with this.

### C++
Demonstrate the operation and application of a Turing Machine that takes care of given a word w of the alphabet Σ = {0, 1}, 
provides its reverse w ^ R, which has all its elements present, to get its correct emulation, in order to be understood by 
any person due to its simple application, thus allowing any interested person to understand the concept. 

* DEVELOPING 
 
The project will consist of a software, written in C ++ language, The software will request the string to be validated 
according to the following statement: given a word w of the alphabet Σ = {0, 1}, it provides its reverse w ^ R. 
and this must be entered according to the definition of the language and that chains that do not belong to the language 
will not be accepted, since the chains comply with this characteristic the machine will be responsible for calculating 
its inverse chain. 

### GO
The propose of create a Turing Machine that revert a chain with the alphabet (0, 1).
So the program is made in Golang. 

### Perl
El código define una cinta en la cual se va a escribir una cadena con 0 y 1, estos conforman la el abecedario de entrada. 
La máquina de Turing se encargará de revisar toda la lista para poder iterar unas veces sobre ella y desplegar lo que será 
su cadena inversa en la misma cinta, borrando la anterior. 

.
