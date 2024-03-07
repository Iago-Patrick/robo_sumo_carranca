#define ch1   5 //Canal 1 do rádio instanciado à entrada digital 5
#define ch2   6 //Canal 2 do rádio instanciado à entrada digital 6
#define ch3   3 //Canal 3 do rádio instanciado à entrada digital 3

#define LED  13 //LED onboard 
//entradas dos motores 11, 12 , 4, 2
// PORTAS DA PONTE H
#define MOTOR1_A    11
#define MOTOR1_B    4
#define MOTOR2_A    12
#define MOTOR2_B    2
#define MOTOR_AR_A  9
#define MOTOR_AR_B   10
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

void movimento_cima(int velocidadec1, int velocidadeC2)
{
    // MOTOR DIREITO PARA FRENTE
    digitalWrite(MOTOR1_A, LOW );
    analogWrite(MOTOR1_B,  velocidadeC1 );

    // MOTOR ESQUERDO PARA FRENTE
    digitalWrite(MOTOR2_A, LOW );
    analogWrite(MOTOR2_B ,  velocidadeC2 );
}
void movimento_dir (int velocidadec1, int velocidadeC2)
{
    // MOTOR DIREITO PARA FRENTE
    digitalWrite(MOTOR1_A,  LOW); // 11
    analogWrite(MOTOR2_B ,    velocidadeC1); // 9

    // MOTOR ESQUERDO PARA TRAS
    analogWrite(MOTOR2_A ,  velocidadeC2); // 10
    digitalWrite(MOTOR2_B ,    LOW);// 8 
}
void movimento_esq(int velocidadec1, int velocidadeC2)
{
    // MOTOR DIREITO PARA FRENTE
    analogWrite(MOTOR1_A, velocidadeC1 );
    digitalWrite(MOTOR1_B,  LOW );

    // MOTOR ESQUERDO PARA FRENTE
    digitalWrite(MOTOR2_A, LOW );
    analogWrite(MOTOR2_B ,  velocidadeC2 );
}
void movimento_tras (int velocidadec1, int velocidadeC2)
{
    // MOTOR DIREITO PARA TRAS
    analogWrite(MOTOR1_A,  velocidadeC1); // 11
    digitalWrite(MOTOR2_B ,    LOW); // 9

    // MOTOR ESQUERDO PARA TRAS
    analogWrite(MOTOR2_A ,  velocidadeC2); // 10
    digitalWrite(MOTOR2_B ,    LOW);// 8 
}
void movimento_parado()
{
  // MOTOR DIREITO PARA TRAS
    digitalWrite(MOTOR1_A,  HIGH); // 11
    digitalWrite(MOTOR2_B ,    HIGH); // 9

    // MOTOR ESQUERDO PARA TRAS
    digitalWrite(MOTOR2_A ,  HIGH); // 10
    digitalWrite(MOTOR2_B ,   HIGH);// 8 

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
  //test_channels();

  if(canal_01 > 1560  && canal_02 > 1560) //frente
  { 
    velocidadeC1=0;
    velocidadeC2=0;
    velocidadeC1=map(canal_01,980, 1990,0,254);
    velocidadeC2=map(canal_02,980, 1990,0,254);
    movimento_cima(velocidadeC1,velocidadeC2);
  }
  else
  {
    if(canal_01 < 1560 && canal_02 < 1560) //tras 
    {
      velocidadeC1=0;
      velocidadeC2=0;
      velocidadeC1=map(canal_01,980, 1990,0,254);
      velocidadeC2=map(canal_02,980, 1990,0,254);
      movimento_tras(velocidadeC1,velocidadeC2);
    }
    else
    {
      if(canal_01 > 1560 && canal_02 < 1560)
      {
        velocidadeC1=0;
        velocidadeC2=0;
        velocidadeC1=map(canal_01,980, 1990,0,254);
        velocidadeC2=map(canal_02,980, 1990,0,254);
        movimento_esq( velocidadeC1,  velocidadeC2);

      }
      else
      {
        if(canal_01 < 1560 && canal_02 > 1560)
        {
          velocidadeC1=0;
          velocidadeC2=0;
          velocidadeC1=map(canal_01,980, 1990,0,254);
          velocidadeC2=map(canal_02,980, 1990,0,254);
          movimento_dir( velocidadeC1,  velocidadeC2);
        }

      }
    }
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
