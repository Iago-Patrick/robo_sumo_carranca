#define ch1   6 //Canal 1 do rádio instanciado à entrada digital 2
#define ch2   5 //Canal 2 do rádio instanciado à entrada digital 3
#define ch3   3 //Canal 3 do rádio instanciado à entrada digital 4

#define LED  13 //LED onboard 
//entradas dos motores 11, 10 , 9, 8
// PORTAS DA PONTE H
#define dirFrente 10
#define dirTras  11
#define esqFrente 9
#define esqTras   8
#define armFrente 11
#define armTras   10
#define velocidadeG 110

int velocidade =0;



void frente(int velocidade)
{
    // MOTOR DIREITO PARA FRENTE
    analogWrite(dirFrente,  velocidade);
    analogWrite(dirTras,    LOW);

    // MOTOR ESQUERDO PARA FRENTE
    analogWrite(esqFrente,  velocidade);
    analogWrite(esqTras,    LOW);
}
void tras (int velocidade)
{
    // MOTOR DIREITO PARA TRAS
    analogWrite(dirFrente,  LOW);
    analogWrite(dirTras,    velocidade);

    // MOTOR ESQUERDO PARA TRAS
    analogWrite(esqFrente,  LOW);
    analogWrite(esqTras,    velocidade);
}

void direita(int velocidade)
{
    // MOTOR DIREITO PARA TRAS
    analogWrite(dirFrente,  LOW);
    analogWrite(dirTras,    velocidade);

    // MOTOR ESQUERDO PARA FRENTE
    analogWrite(esqFrente,  velocidade);
    analogWrite(esqTras,    LOW);
}
void esquerda(int velocidade)
{
    // MOTOR DIREITO PARA FRENTE
    analogWrite(dirFrente,  velocidade);
    analogWrite(dirTras,    LOW);

    // MOTOR ESQUERDO PARA TRAS
    analogWrite(esqFrente,  LOW);
    analogWrite(esqTras,    velocidade);
}
 
// --- Protótipo das funções auxiliares ---
void read_channels();      //Função para leitura das entradas dos canais
void test_channels();      //Testa os 8 canais do Turnigy9x

 
// --- Declaração de variáveis globais ---

//variáveis para os canais do rádio
int canal_01 = 0, 
    canal_02 = 0, 
    canal_03 = 0;
    
// --- Rotina de Interrupção ---
ISR(TIMER2_OVF_vect)
{
    TCNT2=100;          // Reinicializa o registrador do Timer2
       
    
    if(canal_03 < 1500) digitalWrite(LED, HIGH); //Acende LED se o pulso do canal 3 for menor que 1500µs
    
    else digitalWrite(LED, LOW);                 //Senão, mantém LED apagado
    
    
} //end ISR

// --- Configurações iniciais ---
void setup()
{ 
     
  // -- Direção dos I/Os --
  pinMode(ch1, INPUT); //Entrada para o canal 1 do rádio
  pinMode(ch2, INPUT); //Entrada para o canal 2 do rádio
  pinMode(ch3, INPUT); //Entrada para o canal 3 do rádio

  pinMode(LED, OUTPUT); //saída para o LED onboard
  
  digitalWrite(LED, LOW); //LED inicia desligado
  
     
  Serial.begin(9600);            //Inicia comunicação Serial com 9600 de baud rate
  
  // -- Registradores de configuração do Timer2 --
     TCCR2A = 0x00;   //Timer operando em modo normal
     TCCR2B = 0x07;   //Prescaler 1:1024
     TCNT2  = 100;    //10 ms overflow again
     TIMSK2 = 0x01;   //Habilita interrupção do Timer2
  

  // CONFIGURAÇÃO DOS PINOS DA PONTE-H
  pinMode(dirFrente, OUTPUT);
  pinMode(dirTras,   OUTPUT);
  pinMode(esqFrente, OUTPUT);
  pinMode(esqTras,   OUTPUT);

  // DEIXANDO OS MOTORES PARADOS
  digitalWrite(dirFrente, LOW);
  digitalWrite(dirTras,   LOW);
  digitalWrite(esqFrente, LOW);
  digitalWrite(esqTras,   LOW);
   
} //end setup

//Loop infinito
void loop()
{
    read_channels(); //Lê os 8 primeiros canais do rádio
   
    test_channels(); //Testa os canais e envia informação para o Serial Monitor
    
  if(canal_01 > 1500) //direita 
  { 
    velocidade=map(canal_01,1500, 1900,0,254);
    direita(velocidade);
  }
  else 
    if(canal_01 < 1200) //esquerda
    {
      velocidade=map(canal_01,1200,1030,0,254);
      esquerda(velocidade);
    }
  if(canal_02 > 1500) //cima
  {  
    velocidade=map(canal_02,1500, 1900,0,254);
    frente(velocidade);
  }
  else 
    if(canal_02 < 1200) //baixo
    {
      velocidade=map(canal_02,1200, 1030,0,254);
      tras(velocidade);
    }

  //arma
  if(canal_03 > 1550)
  {
    analogWrite(armFrente,  velocidadeG);
    analogWrite(armTras,    LOW);

    analogWrite(armFrente,  velocidadeG);
    analogWrite(armTras,    LOW);
  }
  else 
    if(canal_03 < 1100)
    {
      analogWrite(armTras,  velocidadeG);
      analogWrite(armFrente,    LOW);

      analogWrite(armTras,  velocidadeG);
      analogWrite(armFrente,    LOW);
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
}