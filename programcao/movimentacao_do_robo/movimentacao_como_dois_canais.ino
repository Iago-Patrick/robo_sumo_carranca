#define ch1   6 //Canal 1 do rádio instanciado à entrada digital 2
#define ch2   5 //Canal 2 do rádio instanciado à entrada digital 3
#define ch3   3 //Canal 3 do rádio instanciado à entrada digital 4

#define LED  13 //LED onboard 
//entradas dos motores 11, 10 , 9, 8
// PORTAS DA PONTE H
#define MOTOR1_A    8
#define MOTOR1_B    10
#define MOTOR2_A    9
#define MOTOR2_B    11
#define MOTOR_AR_A  0
#define MOTOR_AR_B   0
#define velocidadeG 110

int velocidadeC1 =0;
int velocidadeC2 =0;

int canal_01 = 0;
int canal_02 = 0;
int canal_03 = 0;

// --- Protótipo das funções auxiliares ---
void read_channels();      //Função para leitura das entradas dos canais
void test_channels();      //Testa os 8 canais do Turnigy9x

void frente();
void tras();
void esquerda();
void direita();

void frente(int velocidade)
{
    // MOTOR DIREITO PARA FRENTE
    digitalWrite(MOTOR1_A, LOW );
    analogWrite(MOTOR1_B,  velocidade );

    // MOTOR ESQUERDO PARA TRAS
    digitalWrite(MOTOR2_A, LOW );
    analogWrite(MOTOR2_B ,  velocidade );
}
void tras (int velocidade)
{
    // MOTOR DIREITO PARA TRAS
    analogWrite(MOTOR1_A,  velocidade); // 11
    digitalWrite(MOTOR2_B ,    LOW); // 9

    // MOTOR ESQUERDO PARA TRAS
    analogWrite(MOTOR2_A ,  velocidade); // 10
    digitalWrite(MOTOR2_B ,    LOW);// 8 
}
void direita(int velocidade)
{
    // MOTOR DIREITO PARA TRAS
    analogWrite(MOTOR1_A,  velocidade);
    digitalWrite(MOTOR1_B,   LOW);

    // MOTOR ESQUERDO PARA FRENTE
    digitalWrite(MOTOR2_A,     LOW);
    digitalWrite(MOTOR2_B,    velocidade);
}
void esquerda(int velocidade)
{
    // MOTOR DIREITO PARA FRENTE
    digitalWrite(MOTOR1_A,  LOW);
    digitalWrite(MOTOR1_B, velocidade);

    // MOTOR ESQUERDO PARA TRAS
    analogWrite(MOTOR2_A, velocidade);
    digitalWrite(MOTOR2_B,    LOW);
}

/*----------------------------SETUP----------------------------------*/

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
  //porta serial
  Serial.begin(9600);
   
}

/*----------------------------LOOP----------------------------------*/

void loop()
{
  read_channels(); //Lê os 8 primeiros canais do rádio
  test_channels();

  if(canal_01 > 1500 && canal_02 > 1500) //direita 
  { 
    velocidadeC1=0;
    velocidadeC2=0;
    velocidadeC1=map(canal_01,1500, 1990,0,254);
    velocidadeC2=map(canal_02,1500, 1990,0,254);
    direita(velocidade);
  }
  else 
    if(canal_01 < 1500) //esquerda      
    {
      velocidadeC1=0;
      velocidadeC2=0;
      velocidade=map(canal_01,1500,980,0,254);
      Serial.println(velocidade);
      esquerda(velocidade);
    }
  if(canal_02 > 1500) //cima
  { 
    velocidadeC1=0;
    velocidadeC2=0; 
    velocidade=map(canal_02,1500, 1990,0,254);
    frente(velocidade);
  }
  else 
    if(canal_02 < 1500  ) //baixo
    {
      velocidadeC1=0;
      velocidadeC2=0;
      velocidade=map(canal_02,1500, 1000,0,254);
      tras(velocidade);
    }

  //arma
  if(canal_03 > 1550)
  {
    analogWrite(MOTOR_AR_A,  velocidadeG);
    analogWrite(MOTOR_AR_B,    LOW);

    analogWrite(MOTOR_AR_A,  velocidadeG);
    analogWrite(MOTOR_AR_B,    LOW);
  }
  else 
    if(canal_03 < 1100)
    {
      analogWrite(MOTOR_AR_A,  velocidadeG);
      analogWrite(MOTOR_AR_B,    LOW);

      analogWrite(MOTOR_AR_A,  velocidadeG);
      analogWrite(MOTOR_AR_B,    LOW);
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