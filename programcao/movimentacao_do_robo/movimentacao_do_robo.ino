#define ch1   6 //Canal 1 do rádio instanciado à entrada digital 2
#define ch2   5 //Canal 2 do rádio instanciado à entrada digital 3
#define ch3   3 //Canal 3 do rádio instanciado à entrada digital 4
/*#define ch4   5 //Canal 4 do rádio instanciado à entrada digital 5
#define ch5   6 //Canal 5 do rádio instanciado à entrada digital 6
#define ch6   7 //Canal 6 do rádio instanciado à entrada digital 7
#define ch7   8 //Canal 7 do rádio instanciado à entrada digital 8
#define ch8   9 //Canal 8 do rádio instanciado à entrada digital 9
*/
#define LED  13 //LED onboard 
//entradas dos motores 11, 10 , 9, 8
// PORTAS DA PONTE H
#define dirFrente 10
#define dirTras  11
#define esqFrente 9
#define esqTras   8
#define armFrente 11
#define armTras   10

#define velocidadeE 110
#define velocidadeD 110

void frente()
{
    // MOTOR DIREITO PARA FRENTE
    analogWrite(dirFrente,  velocidadeD);
    analogWrite(dirTras,    LOW);

    // MOTOR ESQUERDO PARA FRENTE
    analogWrite(esqFrente,  velocidadeE);
    analogWrite(esqTras,    LOW);
}
void tras ()
{
    // MOTOR DIREITO PARA TRAS
    analogWrite(dirFrente,  LOW);
    analogWrite(dirTras,    velocidadeE);

    // MOTOR ESQUERDO PARA TRAS
    analogWrite(esqFrente,  LOW);
    analogWrite(esqTras,    velocidadeD);
}

void direita()
{
    // MOTOR DIREITO PARA TRAS
    analogWrite(dirFrente,  LOW);
    analogWrite(dirTras,    velocidadeD);

    // MOTOR ESQUERDO PARA FRENTE
    analogWrite(esqFrente,  velocidadeE);
    analogWrite(esqTras,    LOW);
}
void esquerda()
{
    // MOTOR DIREITO PARA FRENTE
    analogWrite(dirFrente,  velocidadeD);
    analogWrite(dirTras,    LOW);

    // MOTOR ESQUERDO PARA TRAS
    analogWrite(esqFrente,  LOW);
    analogWrite(esqTras,    velocidadeE);
}
 
// --- Protótipo das funções auxiliares ---
void read_channels();      //Função para leitura das entradas dos canais
void test_channels();      //Testa os 8 canais do Turnigy9x

 
// --- Declaração de variáveis globais ---

//variáveis para os canais do rádio
int canal_01 = 0, 
    canal_02 = 0, 
    canal_03 = 0, 
   /* canal_04 = 0, 
    canal_05 = 0, 
    canal_06 = 0, 
    canal_07 = 0, 
    canal_08 = 0; 
    
 */
    
    
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
/*  pinMode(ch4, INPUT); //Entrada para o canal 4 do rádio
  pinMode(ch5, INPUT); //Entrada para o canal 5 do rádio
  pinMode(ch6, INPUT); //Entrada para o canal 6 do rádio
  pinMode(ch7, INPUT); //Entrada para o canal 7 do rádio
  pinMode(ch8, INPUT); //Entrada para o canal 8 do rádio
  */
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
    direita();
  else 
    if(canal_01 < 1100) //esquerda
      esquerda();
  if(canal_02 > 1500) //cima
    frente();
  else 
    if(canal_02 < 1100) //baixo
      tras();
  if(canal_03 > 1550)
  {
    analogWrite(armFrente,  velocidadeD);
    analogWrite(armTras,    LOW);

    analogWrite(armFrente,  velocidadeE);
    analogWrite(armTras,    LOW);
  }
  else 
    if(canal_03 < 1100)
    {
      analogWrite(armTras,  velocidadeD);
      analogWrite(armFrente,    LOW);

      analogWrite(armTras,  velocidadeE);
      analogWrite(armFrente,    LOW);
    }  
}//end loop

//Funções auxiliares
void read_channels() //Faz a leitura dos 6 primeiros canais do rádio
{
  canal_01 = pulseIn(ch1, HIGH, 25000); //Lê pulso em nível alto do canal 1 e armazena na variável canal_01
  canal_02 = pulseIn(ch2, HIGH, 25000); //Lê pulso em nível alto do canal 2 e armazena na variável canal_02
  canal_03 = pulseIn(ch3, HIGH, 25000); //Lê pulso em nível alto do canal 3 e armazena na variável canal_03
  /*canal_04 = pulseIn(ch4, HIGH, 25000); //Lê pulso em nível alto do canal 4 e armazena na variável canal_04
  canal_05 = pulseIn(ch5, HIGH, 25000); //Lê pulso em nível alto do canal 5 e armazena na variável canal_05
  canal_06 = pulseIn(ch6, HIGH, 25000); //Lê pulso em nível alto do canal 6 e armazena na variável canal_06
  canal_07 = pulseIn(ch7, HIGH, 25000); //Lê pulso em nível alto do canal 7 e armazena na variável canal_07
  canal_08 = pulseIn(ch8, HIGH, 25000); //Lê pulso em nível alto do canal 8 e armazena na variável canal_08
*/
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
/*      Serial.print(canal_04);
      Serial.print(" | ");
      Serial.print(canal_05);
      Serial.print(" | ");
      Serial.print(canal_06);
      Serial.print(" | ");
      Serial.print(canal_07);
      Serial.print(" | ");
      Serial.print(canal_08);
      Serial.print(" | ");
      */
      Serial.println("");
      Serial.println("");
      Serial.print("Canal:  ");
      Serial.print("  01  ");
      Serial.print("|");
      Serial.print("  02  ");
      Serial.print("|");
      Serial.print("  03  ");
      Serial.print("|");
     /* Serial.print("  04  ");
      Serial.print("|");
      Serial.print("  05  ");
      Serial.print("|");
      Serial.print("  06  ");
      Serial.print("|");
      Serial.print("  07  ");
      Serial.print("|");
      Serial.print("  08  ");
      Serial.print("|");*/
      Serial.println("");
      Serial.println("");
}