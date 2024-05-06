#include <HCSR04.h> // Inclui a biblioteca do sensor HC SR04

#define fault          8   // detecção de falha da ponte H (DRV 8833)
#define sleep          7   // controle sleep
// Controles específicos da ponte H utilizada (DRV 8833)

#define triggerFront   5   // ultrassônico frente
#define echoFront      4
#define triggerLeft    12  // ultrassônico esquerda
#define echoLeft       13
#define triggerRight   3   // ultrassônico direita
#define echoRight      2
#define motordir       10 
#define motordirtras   11
#define motoresq       6
#define motoresqtras   9

// Inicializa o sensor usando os pinos TRIGGER and ECHO.
UltraSonicDistanceSensor sensorFront(triggerFront, echoFront);  
UltraSonicDistanceSensor sensorLeft(triggerLeft, echoLeft); 
UltraSonicDistanceSensor sensorRight(triggerRight, echoRight); 

void setup () {
  
  pinMode(fault, INPUT_PULLUP);
  pinMode(motordir, OUTPUT);
  pinMode(motoresq, OUTPUT);
  pinMode(motoresqtras, OUTPUT);
  pinMode(motordirtras, OUTPUT);
  digitalWrite(sleep, HIGH);

  analogWrite(motordir, 0);
  analogWrite(motoresq, 0);
  analogWrite(motoresqtras, 0);
  analogWrite(motordirtras, 0);

  Serial.begin(9600);  //Inicializa a porta serial do Arduino com 9600 de baud rate
}

bool justiceiroAtivo = false;

void loop () {
  while(true){

    // Controle de início dos valores do ultrassônico
    int distFront = 0;
    int distLeft = 0;
    int distRight = 0;

    int vel = 200;           // Variável de controle da velocidade (0 A 255)
    int distParachoque = 20; // Distância mínima para encontrar algo na frente
    int distLateral = 25;    // Distância mínima para encontrar algo nas lateriais 
                             // Os ultrassônicos laterais são posicionados mais internamente no robô
    
    //Variável recebe o valor da função da biblioteca
    distFront = sensorFront.measureDistanceCm();
    distLeft = sensorLeft.measureDistanceCm();
    distRight = sensorRight.measureDistanceCm();

    // Serial.print("Esquerda: ");
    // Serial.print(distLeft);
    // Serial.print(" | ");
    // Serial.print("Frente: ");
    // Serial.println(distFront);
    // Serial.print(" | ");
    // Serial.print("Direita: ");
    // Serial.println(distRight);
    // delay(600);

    if (!justiceiroAtivo){
      if (distFront > 10){
        Serial.print("Seguindo em frente");
        Serial.println(distFront);
        analogWrite(motoresq, vel);
        analogWrite(motordir, vel);
      } 
      if (distFront > 2 && distFront < 10) {
        Serial.print("Achei!");
        Serial.println(distFront);
        analogWrite(motoresq, 1);
        analogWrite(motordir, 1);
        justiceiro(); // Tarefa de loop para seguir o adversário
      }
    }
  }
}


void justiceiro () {
  justiceiroAtivo = true;
  Serial.println("Partiu!");
}
