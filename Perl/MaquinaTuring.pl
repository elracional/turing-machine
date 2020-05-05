#!/usr/bin/perl
=begin
  Maquina de Turing
=cut

$| = 1;
use strict;
#use warnings;

#--- CLASE CINTA ---
package Cinta;
sub new{ #---- Constructor ----
    my $self={};
    @{$self->{cinta}}=(); #Cinta de maquina
    $self->{lector}=2; #Cabeza lectora de la cinta
    bless $self,"Cinta";
    return $self;
}

sub s{
    my $self = shift;
    #print $_[0],", ",$_[1],", ",$_[2];
    if($_[0] eq $self->{cinta}[$self->{lector}]){
        $self->{cinta}[$self->{lector}]=$_[1];
        if($_[2] eq 'R'){
            $self->{lector}++;
        }elsif($_[2] eq 'L'){
            $self->{lector}--;
        }
        return 1;
    }
}

#--- CLASE AUTOMATA ---
package Automata;
sub new{ #-- Constructor --
  my $self={};
  $self->{cadena}=""; #Cadena a leer
  $self->{cinta1}= Cinta->new();
  bless $self,"Automata";
  return $self;
}

sub setCadena{ #-- Metodo --
  my $val=0;
  my ( $self) = @_;
  do{
     print "Ingresar cadena: ";
     my $var=<STDIN>;
     chomp($var);
     $self->{cadena} = "  " . $var;
     for(my $i=2; $i<length($self->{cadena}); $i++){
         if(substr($self->{cadena},$i,1) eq '1' || substr($self->{cadena},$i,1) eq '0'){
             $val=1;
         }else{
             $val=0;
             $i=length($self->{cadena});
             print "Cadena invalida!!\n";
         }
     }
  }while($val==0);
  for(my $i=0; $i<length($self->{cadena}); $i++){
    $self->{cinta1}->{cinta}[$i] = substr($self->{cadena},$i,1);
  }
  for(my $i=length($self->{cadena}); $i<length($self->{cadena})*2; $i++){
    $self->{cinta1}->{cinta}[$i] = ' ';
  }
}

#---- ESTADOS ----
sub q0{
  my($self)= @_;
  my $aux=join("",@{$self->{cinta1}->{cinta}});
  print "\n En q0 \n";
  print "  CINTA--> ",$aux;
  print "\n LECTOR--> ";
  for(my $i=0; $i<$self->{cinta1}->{lector}; $i++){
    print " ";
  }
  print "^\n";
  if($self->{cinta1}->s("1","1","L")){
      $self->q0();
  }elsif($self->{cinta1}->s("0","0","L")){
      $self->q0();
  }elsif($self->{cinta1}->s(" ","A","R")){
      $self->q1();
  }
}
sub q1{
  my($self)= @_;
  my $aux=join("",@{$self->{cinta1}->{cinta}});
  print "\n En q1 \n";
  print "  CINTA--> ",$aux;
  print "\n LECTOR--> ";
  for(my $i=0; $i<$self->{cinta1}->{lector}; $i++){
    print " ";
  }
  print "^\n";
  if($self->{cinta1}->s("1","1","R")){
      $self->q1();
  }elsif($self->{cinta1}->s("0","0","R")){
      $self->q1();
  }elsif($self->{cinta1}->s(" ","Z","L")){
      $self->q2();
  }
}
sub q2{
  my($self)= @_;
  my $aux=join("",@{$self->{cinta1}->{cinta}});
  print "\n En q2 \n";
  print "  CINTA--> ",$aux;
  print "\n LECTOR--> ";
  for(my $i=0; $i<$self->{cinta1}->{lector}; $i++){
    print " ";
  }
  print "^\n";
  if($self->{cinta1}->s("1"," ","R")){
      $self->q3();
  }elsif($self->{cinta1}->s("0"," ","R")){
      $self->q6();
  }elsif($self->{cinta1}->s("A"," ","L")){
      $self->q8();
  }elsif($self->{cinta1}->s(" "," ","L")){
      $self->q2();
  }
}
sub q3{
  my($self)= @_;
  my $aux=join("",@{$self->{cinta1}->{cinta}});
  print "\n En q3 \n";
  print "  CINTA--> ",$aux;
  print "\n LECTOR--> ";
  for(my $i=0; $i<$self->{cinta1}->{lector}; $i++){
    print " ";
  }
  print "^\n";
  if($self->{cinta1}->s("Z","Z","R")){
      $self->q4();
  }elsif($self->{cinta1}->s(" "," ","R")){
      $self->q3();
  }
}
sub q4{
  my($self)= @_;
  my $aux=join("",@{$self->{cinta1}->{cinta}});
  print "\n En q4 \n";
  print "  CINTA--> ",$aux;
  print "\n LECTOR--> ";
  for(my $i=0; $i<$self->{cinta1}->{lector}; $i++){
    print " ";
  }
  print "^\n";
  if($self->{cinta1}->s("1","1","R")){
      $self->q4();
  }elsif($self->{cinta1}->s("0","0","R")){
      $self->q4();
  }elsif($self->{cinta1}->s(" ","1","L")){
      $self->q5();
  }
}
sub q5{
  my($self)= @_;
  my $aux=join("",@{$self->{cinta1}->{cinta}});
  print "\n En q5 \n";
  print "  CINTA--> ",$aux;
  print "\n LECTOR--> ";
  for(my $i=0; $i<$self->{cinta1}->{lector}; $i++){
    print " ";
  }
  print "^\n";
  if($self->{cinta1}->s("1","1","L")){
      $self->q5();
  }elsif($self->{cinta1}->s("0","0","L")){
      $self->q5();
  }elsif($self->{cinta1}->s("Z","Z","L")){
      $self->q2();
  }
}
sub q6{
  my($self)= @_;
  my $aux=join("",@{$self->{cinta1}->{cinta}});
  print "\n En q6 \n";
  print "  CINTA--> ",$aux;
  print "\n LECTOR--> ";
  for(my $i=0; $i<$self->{cinta1}->{lector}; $i++){
    print " ";
  }
  print "^\n";
  if($self->{cinta1}->s("Z","Z","R")){
      $self->q7();
  }elsif($self->{cinta1}->s(" "," ","R")){
      $self->q6();
  }
}
sub q7{
  my($self)= @_;
  my $aux=join("",@{$self->{cinta1}->{cinta}});
  print "\n En q7 \n";
  print "  CINTA--> ",$aux;
  print "\n LECTOR--> ";
  for(my $i=0; $i<$self->{cinta1}->{lector}; $i++){
    print " ";
  }
  print "^\n";
  if($self->{cinta1}->s("1","1","R")){
      $self->q7();
  }elsif($self->{cinta1}->s("0","0","R")){
      $self->q7();
  }elsif($self->{cinta1}->s(" ","0","L")){
      $self->q5();
  }
}
sub q8{
  my($self)= @_;
  my $aux=join("",@{$self->{cinta1}->{cinta}});
  print "\n En q8 \n";
  print "  CINTA--> ",$aux;
  print "\n LECTOR--> ";
  for(my $i=0; $i<$self->{cinta1}->{lector}; $i++){
    print " ";
  }
  print "^\n";
  if($self->{cinta1}->s("Z"," ","R")){
      $self->q9();
  }elsif($self->{cinta1}->s(" "," ","R")){
      $self->q8();
  }
}
sub q9{ 
  system("clear"); #Borrado de pantalla
  my($self)= @_;
  my $aux=join("",@{$self->{cinta1}->{cinta}});
  print "\n En q9 -- *Estado Valido*\n";
  print "  CINTA--> ",$aux;
  print "\n LECTOR--> ";
  for(my $i=0; $i<$self->{cinta1}->{lector}; $i++){
    print " ";
  }
  print "^\n";
}
1;

# ---- FUNCION PRINCIPAL -----------
package main;
my $auto= Automata->new();
#my $cinta= Cinta->new();
$auto->setCadena();
$auto->q0(); #Inicio de automata
print "\n------------------------------------\n";
print "Maquina de Turing finalizada   :)";