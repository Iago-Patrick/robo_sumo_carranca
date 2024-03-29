#define ch1   6 //Canal 1 do rádio instanciado à entrada digital 2
#define ch2   5 //Canal 2 do rádio instanciado à entrada digital 3
#define ch3   3 //Canal 3 do rádio instanciado à entrada digital 4

#define LED  13 //LED onboard 
//entradas dos motores 11, 10 , 9, 8
// PORTAS DA PONTE H
#define MOTOR1_A    11
#define MOTOR1_B    4//p
#define MOTOR2_A    12
#define MOTOR2_B    2//p
#define MOTOR_AR_A  9
#define MOTOR_AR_B   10

int velocidade1 =0;
int velocidade2 =0;
int velocidade3 =0;

int canal_01 = 0;
int canal_02 = 0;
int canal_03 = 0;

void setup()
{ 

  // -- Direção dos I/Os --
  pinMode(ch1, INPUT); //Entrada para o canal 1 do rádio
  pinMode(ch2, INPUT); //Entrada para o canal 2 do rádio
  pinMode(ch3, INPUT); //Entrada para o canal 3 do rádio
  // CONFIGURAÇÃO DOS PINOS DA PONTE-H
  pinMode(MOTOR1_A,     OUTPUT);
  pinMode(MOTOR1_B,     OUTPUT);
  pinMode(MOTOR2_A,     OUTPUT);
  pinMode(MOTOR2_B,     OUTPUT);
  pinMode(MOTOR_AR_A,   OUTPUT);
  pinMode(MOTOR_AR_B,   OUTPUT);
 Serial.begin(9600);

  // DEIXANDO OS MOTORES PARADOS
 /*digitalWrite(dirFrente, LOW);
  digitalWrite(dirTras,   LOW);
  digitalWrite(esqFrente, LOW);
  digitalWrite(esqTras,   LOW);*/
   
} //end setup


void frente(int velocidade1, int velocidade2 )
{
    // MOTOR DIREITO PARA FRENTE
    digitalWrite(MOTOR1_A, velocidade1 );
    analogWrite(MOTOR1_B,  HIGH );

    // MOTOR ESQUERDO PARA TRAS
    digitalWrite(MOTOR2_A, velocidade2 );
    analogWrite(MOTOR2_B ,  HIGH);
} 

void parado(int velocidade1, int velocidade2 )
{
    // MOTOR DIREITO PARA FRENTE
    digitalWrite(MOTOR1_A, velocidade1 );
    analogWrite(MOTOR1_B,  LOW );

    // MOTOR ESQUERDO PARA TRAS
    digitalWrite(MOTOR2_A, velocidade2 );
    analogWrite(MOTOR2_B ,  LOW );
}
void tras (int velocidade1, int velocidade2)
{
    // MOTOR DIREITO PARA TRAS
    analogWrite(MOTOR1_B,velocidade1 ); // 11
    digitalWrite(MOTOR1_A , LOW  ); // 9

    // MOTOR ESQUERDO PARA TRAS
    analogWrite(MOTOR2_B ,  velocidade2); // 10
    digitalWrite(MOTOR2_A ,    LOW);// 8 
}

void direita(int velocidade1, int velocidade2)
{
    // MOTOR DIREITO PARA TRAS
    analogWrite(MOTOR1_B,  HIGH);
    digitalWrite(MOTOR1_A,  velocidade1) ;

    // MOTOR ESQUERDO PARA FRENTE
    digitalWrite(MOTOR2_A,    LOW );
    analogWrite(MOTOR2_B, velocidade2   );
}
void esquerda(int velocidade1, int velocidade2)
{
    // MOTOR DIREITO PARA FRENTE
    digitalWrite(MOTOR1_A,  LOW);
    analogWrite(MOTOR1_B,    velocidade1);

    // MOTOR ESQUERDO PARA TRAS
    digitalWrite(MOTOR2_A,  velocidade2);
    analogWrite(MOTOR2_B,    HIGH);
}
void  arma_frente (int velocidade3)
{
  digitalWrite (MOTOR_AR_A, HIGH);
  analogWrite(MOTOR_AR_B, velocidade3 );
}
void arma_tras (int velocidade3)
{
  digitalWrite (MOTOR_AR_A, LOW);
  analogWrite(MOTOR_AR_B, velocidade3 );
}

 
// --- Protótipo das funções auxiliares ---
void read_channels();      //Função para leitura das entradas dos canais
void test_channels();      //Testa os 8 canais do Turnigy9x

void loop()
{
    read_channels(); //Lê os 8 primeiros canais do rádio
    //test_channels();
   
   
  if(canal_01 > 1600 ) //direita 
  { 
     velocidade2=map(canal_01,1000, 1990,-254,254);
      velocidade1=map(canal_02,1000, 1990,-254,254);
  direita(velocidade1, velocidade2);
  }
  else 
    if(canal_01 < 1380 ) //esquerda
    {
      velocidade1=map(canal_01,1000, 1990,-254,254);
      velocidade2=map(canal_02,1000, 1990,-254,254);

      esquerda(velocidade1, velocidade2);
      
    }
  if(canal_02 > 1600 ) //cima
  {  
    velocidade1=map(canal_01,1000, 1990,-254,254);
    velocidade2=map(canal_02,1000, 1990,-254,254);
    frente(velocidade1, velocidade2 );
  }
  else 
    if(canal_02 < 1380 ) //baixo
    {
      velocidade1=map(canal_01,1000, 1990,-254,254);
      velocidade2=map(canal_02,1000, 1990,-254,254);
       tras(velocidade1, velocidade2);
    }

  //arma
  if(canal_03 > 1500)
  {
    velocidade3=map(canal_03,1500, 1990, 0, 254);
    arma_frente ( velocidade3);
  }
  else 
    if(canal_03 < 1300)
    {
      velocidade3=map(canal_03,1000,1300 , -254, 0);
      arma_tras ( velocidade3);
    }  
    else 
    if (canal_02 > 1379 && canal_02 < 1599 || canal_01 > 1379 && canal_01 < 1599 )
    {
       velocidade1=map(canal_01,1000, 1990,-254,254);
    velocidade2=map(canal_02,1000, 1990,-254,254);
     parado(velocidade1,  velocidade2 );

    }

}//end loop
//Funções auxiliares
void read_channels() //Faz a leitura dos 6 primeiros canais do rádio
{
  canal_01 = pulseIn(ch1, HIGH, 25000); //Lê pulso em nível alto do canal 1 e armazena na variável canal_01
  canal_02 = pulseIn(ch2, HIGH, 25000); //Lê pulso em nível alto do canal 2 e armazena na variável canal_02
  canal_03 = pulseIn(ch3, HIGH, 25000); //Lê pulso em nível alto do canal 3 e armazena na variável canal_03
} //end read channels

void test_channels() //Testa os canais via serial monitor (comentar esta função e só chamar quando necessário)
{  
      Serial.print("Valor:  ");
      Serial.print(canal_01);
      Serial.print(" | ");
      Serial.print(canal_02);
      Serial.print(" | ");
      Serial.print(canal_03);
      Serial.print(" | ");

      Serial.println("");
      Serial.println("");
      Serial.print("Canal:  ");
      Serial.print("  01  ");
      Serial.print("|");
      Serial.print("  02  ");
      Serial.print("|");
      Serial.print("  03  ");
      Serial.print("|");

      Serial.println("");
      Serial.println("");
      delay(1000);
      
}
