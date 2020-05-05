#!/usr/bin/env perl
#MÁQUINA DE TURING
use strict;
use warnings;
use Time::HiRes qw(usleep);

my $Q ='q0'; #estado inicial
my $apC = 2; #indice inicial de la cinta
my ($x,$y); #indices de la matriz bidi
my $end = 'false'; #bandera para terminar codigo
my @C = ('b','b'); #Cinta con 2 simbolos en blanco
#M = (E={0,1}, T={0,1,A,Z,b}, Q={q0,q1,q2,q3,q4,q5,q6,q7,q8,q9}, F={q9}, S)
#matriz de trancision
my @r0 = ('S','0','1','b','A','Z');
my @r1 = ('q0','q0,0,L','q0,1,L','q1,A,R','-','-');
my @r2 = ('q1','q1,0,R','q1,1,R','q2,Z,L','-','-');
my @r3 = ('q2','q6,b,R','q3,b,R','q2,b,L','q8,b,L','-');
my @r4 = ('q3','-','-','q3,b,R','-','q4,Z,R');
my @r5 = ('q4','q4,0,R','q4,1,R','q5,1,L','-','-');
my @r6 = ('q5','q5,0,L','q5,1,L','-','-','q2,Z,L');
my @r7 = ('q6','-','-','q6,b,R','-','q7,Z,R');
my @r8 = ('q7','q7,0,R','q7,1,R','q5,0,L','-','-');
my @r9 = ('q8','-','-','q8,b,R','-','q9,b,R');
my @matriz = (\@r0,\@r1,\@r2,\@r3,\@r4,\@r5,\@r6,\@r7,\@r8,\@r9);
#INICIO
open (MT, ">mt_salida.txt"); #apuntador y nombre del archivo txt
print "Ingrese cadena de 0 y 1: ";
my $cadena = <STDIN>;#lee la cadena
chomp($cadena);
valCadena();

sub valCadena {
  my $val;
  my @cadena = split("", $cadena); #la cadena se combierte en arreglo
  foreach my $x (@cadena) {
    if ($x eq '1' || $x eq '0' || $x eq ' ') { #si es 1, 0 o espacio en blanco es valida
      if ($x eq ' ') { #si hay un espacio en blanco se remplazaz por b
        $x = 'b';
        $apC++; #el apuntador aumenta indicando donde esta el primer simbolo de la cadena
      }
      $val = 'true'; #si todo se cumple es valida
    }else{
      $val = 'false'; #si no cumple es falso
      last; #se termina el ciclo
    }
  }
  if ($val eq 'true') { #cadena valida, comineza ejecucion
    $apC = $apC + (scalar(@cadena) -1);
    print "¡Cadena valida!\n\n";
    push(@C,@cadena);
    push(@C, ('b','b'));
    maquina(); #se llama la funcion maquina
  }elsif ($val eq 'false') { #cadena no calida, finaliza la ejecucion
    print "¡Cadena no valida!\n\n";
    qError();
  }
}

sub maquina {
  print "\nEN $Q\n";
  print MT "\nEN $Q\n"; #se escribe el estao en el archivo
  $x=0; $y=0;
  if ($Q ne 'q9') { #para cualquier estado diferente de q9
    while ($matriz[$y][0] ne $Q) {
      $y++;
    }
    while ($matriz[0][$x] ne $C[$apC]) {
      $x++;
    }
  } if ($Q eq 'q9') { #solo para q9
    $end = 'true';
    print"--ESTADO FINAL--\n";
    print MT "--ESTADO FINAL--\n";
    print"Cadena original: $cadena\n";
    print MT "Cadena original: $cadena\n";
    verCinta($end);
  }
  print"S($matriz[$y][0],$matriz[0][$x]) = ($matriz[$y][$x])\n"; #imprime la funcion de transicion
  print MT "S($matriz[$y][0],$matriz[0][$x]) = ($matriz[$y][$x])\n"; #se escribe la funcion de transicion en el archivo
  cinta($matriz[$y][$x]); #encia la trancision a la funcion cinta
}

sub cinta {
  if ($Q eq 'q4' && $matriz[$y][$x] eq 'q5,1,L') { #si esto se cumple agrega un simbolo en blanco al final de la cinta
    push(@C, 'b');
  }elsif ($Q eq 'q7' && $matriz[$y][$x] eq 'q5,0,L') { #si esto se cumple agrega un simbolo en blanco al final de la cinta
    push(@C, 'b');
  }
  my @T = split(",",$matriz[$y][$x]); #separa los valores de la trancision
  $Q = $T[0]; #el primer valor es el estado
  $C[$apC] = $T[1]; #el segundo valor es el simbolo escrito en la cinta
  if ($T[2] eq 'R') { #el tercero indica en que direccion se mueve el apuntador
    $apC++;
  }elsif ($T[2] eq 'L') {
    $apC--;
  }
  verCinta($end) #visualiza la cinta
}

sub verCinta {
  print"CINTA: ";
  for (my $i=0; $i<(scalar(@C)); $i++) {  #recorre la cinta de 0 a el tamaño del arreglo
    if ($i == $apC) { #si el subindice es igual al apuntador
      print"|>$C[$i]<|-"; #imprime el apuntador de la cinta
      print MT "|>$C[$i]<|-"; #escribe el apuntador en el archivo
    }else{ #si no es igual
      print"$C[$i]-";  #imprime el simbolo
      print MT "$C[$i]-"; #escribe el simbolo en el archivo
    }
  }
  print"\n\n";
  if ($end eq 'false') { #sera falso mientras este en estados diferentes a q9
    print MT "\n"; #escribe salto de linea en el archivo
    usleep(500000); #tiempo de espera en microsegundos
    system("clear");#limpia la ventana
    maquina(); #regresa a la funcion maquina
  }elsif ($end eq 'true') { #esto solo se cumple cuando llega al estado q9
    close (MT);
    exit; #finaliza ejecucion
  }
}

sub qError {
  print("Fin de la ejecucion\n"); #mensaje de error
  close (MT);
  exit; #finaliza ejecucion
}
