// PORTAS DA PONTE H
#define dirFrente 5
#define dirTras   3
#define esqFrente 9
#define esqTras   6

int velocidadeE 110
int velocidadeD 110

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

void setup() {
  Serial.begin(9600);

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
}

void loop()
{

}