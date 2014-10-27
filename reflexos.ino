int led1=8;
int led2=9;
int led3=10;
int boton=6;
long tempoActual;
long tempoAceso=1000;
long numeroChou;
boolean led2Aceso;
int botonAntes=0;
int botonAgora;
int nivel=0;
void setup() {
  Serial.begin(9600);
  pinMode(led1,OUTPUT);
  pinMode(led2,OUTPUT);
  pinMode(led3,OUTPUT);
  pinMode(boton,OUTPUT);
}

void loop(){
        
    encendidoLeds();
        
    botonAgora=digitalRead(boton);
    
    if (botonAgora!=botonAntes && botonAgora==1){
      if (led2Aceso==false) {
          perdiches();
      }
      else {
       acertas();
      }
     }
     else {
       botonAntes=digitalRead(boton);
     }
     
  
}

void encendidoLeds() {
    if ((millis()-tempoActual)>tempoAceso){
      numeroChou=random(1,4);
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
     tempoActual=millis();
   }
   
}

void perdiches(){
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
          botonAntes=0;
          tempoAceso=1000;
          Serial.print("Chegaches ao nivel ");
          Serial.println(nivel);
          nivel=0;
}

void acertas() {
  botonAntes=digitalRead(boton);      
  nivel++;
        digitalWrite (led1,HIGH);
        digitalWrite (led2,HIGH);
        digitalWrite (led3,HIGH);
        delay(30);
        Serial.print("Nivel ");
        Serial.println(nivel);
        tempoAceso=tempoAceso-50;
}
  
