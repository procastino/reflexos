//definimos os pines onde van os leds e o boton
int led1=8;
int led2=9;
int led3=10;
int boton=6;

//definimos as variables que necesitaremos para ter conta do tempo
long tempoActual=0;
long tempoAceso=1000;

//definimos unha variable que almacenara o numero aleatorio que fai que
//se encenda un led determinado
long numeroChou;

//led2Aceso nos indicara se o led numero 2, ao que temos que reaccionar
// estara ou non aceso. Por iso e "boolean" que so admite "true" o "false"
boolean led2Aceso;

//estas duas variables nos serviran para ter conta das pulsacions do boton
int botonAntes=0;
int botonAgora;

//esta variable nos servira para ter conta do nivel ao que chegamos
int nivel=0;

void setup() {
  //iniciamos a comunicacion serie e informamos do comezo
  Serial.begin(9600);
  Serial.println("Comezas no nivel 0!...");
  delay(1000);
  Serial.println("Adiante!");
  //definimos os pines dos leds como saidas e o boton coma entrada
  pinMode(led1,OUTPUT);
  pinMode(led2,OUTPUT);
  pinMode(led3,OUTPUT);
  pinMode(boton,INPUT);
}

void loop(){
   //chamamos a funcion de encendido     
   encendeLeds();
   //leremos o boton e comparamos
   compara();    
  
}

//funcion de encendido de Leds
void encendeLeds() {
  //comproba se xa pasou o interbalo de tempo que definimos como tempoAceso
    if ((millis()-tempoActual)>tempoAceso){
      //Escollemos un numero ao chou que pode ser 1,2 ou 3
      numeroChou=random(1,4);
      //segundo o numero que saia, encendemos un led ou outro e definimos se led2Aceso
      //e "true" o "false"
      switch (numeroChou) {
        case 1:
            digitalWrite (led1,HIGH);
            digitalWrite (led2,LOW);
            digitalWrite (led3,LOW);
            led2Aceso=false;
            break;
        case 2:
            digitalWrite (led1,LOW);
            digitalWrite (led2,HIGH);
            digitalWrite (led3,LOW);
            led2Aceso=true;
            break;
        case 3:
            digitalWrite (led1,LOW);
            digitalWrite (led2,LOW);
            digitalWrite (led3,HIGH);
            led2Aceso=false;
            break;
         
        }
     //con esta liña "reseteamos" o tempoActual
     tempoActual=millis();
   }
   
}

//funcion que le o boton e comproba se acertamos
void compara() {
  //Leo o boton
  botonAgora=digitalRead(boton);
  //Comparo se o boton cambiou de estado
  //Se cambiou de estado e, ademais, vale 1
  if (botonAgora!=botonAntes && botonAgora==1){
      //Se o que estaba aceso non era o led 2 e chamo a funcion "perdiches()"
      if (led2Aceso==false) {
          perdiches();
      }
      //en caso contrario sera que o fixen ben e chamo a funcion "acertas()"
      else {
       acertas();
      }
     }
   //Se non cambiou de estado, gardo o estado en que estea como estado anterior e volto comezar
   else {
       botonAntes=digitalRead(boton);
     }
  }
 
//Funcion en caso de perder
void perdiches(){
  //Encendo e apago os tres leds durante 0,3 seg, cinco veces
  for (int i=0;i<5;i++){
              digitalWrite (led1,HIGH);
              digitalWrite (led2,HIGH);
              digitalWrite (led3,HIGH);
              delay(300);
              digitalWrite (led1,LOW);
              digitalWrite (led2,LOW);
              digitalWrite (led3,LOW);
              delay(300);
          }
          //imprimo o nivel a que cheguei e que volto comezar
          Serial.print("Chegaches ao nivel ");
          Serial.println(nivel);
          Serial.println("Comezas no nivel 0!...");
          delay(1000);
          Serial.println("Adiante!");
          //reinicio o nivel no que comezo
          nivel=0;
          //reinicio a variable de tempo de transicion do led
          tempoAceso=1000;
  }

//Funcion en caso de acertar
void acertas() {
  //Gardo o estado en que estou coma estado anterior
  botonAntes=digitalRead(boton);      
  //subo un nivel
  nivel++;
  //Encendo os tres leds durante 0,6 seg e os apago durante 0,4
  digitalWrite (led1,HIGH);
  digitalWrite (led2,HIGH);
  digitalWrite (led3,HIGH);
  delay(600);
  digitalWrite (led1,LOW);
  digitalWrite (led2,LOW);
  digitalWrite (led3,LOW);
  delay(400);
  //imprimo a que nivel subin
  Serial.print("Nivel ");
  Serial.println(nivel);
  //fago que o tempo de transicion sexa o 90% do anterior
  tempoAceso=tempoAceso*0.9;
  }
