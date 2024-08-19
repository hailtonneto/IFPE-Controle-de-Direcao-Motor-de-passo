#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C LCD = LiquidCrystal_I2C(0x27, 16, 2);

#define ENABLE 17
#define STEP 4
#define DIR 2

#define BOTAO_POWER 15
#define DIR_BOTAO 16

int steps_per_rev = 200;

bool motorEnabled = false;
bool motorDirection = true;
bool limparLCD = true;

void ligaDesliga(){
  motorEnabled = !motorEnabled;
}

void sentido(){
  motorDirection = !motorDirection;
}

void setup(){
  LCD.init();
  LCD.backlight();
  LCD.setCursor(0, 0);
  LCD.print("Controle do");
  LCD.setCursor(0, 1);
  LCD.print("Motor de Passo");

  pinMode(ENABLE, OUTPUT);
  pinMode(STEP, OUTPUT);
  pinMode(DIR, OUTPUT);

  pinMode(BOTAO_POWER, INPUT_PULLUP);
  pinMode(DIR_BOTAO, INPUT_PULLUP);

  digitalWrite(ENABLE, HIGH);
  digitalWrite(STEP, LOW);
  digitalWrite(DIR, LOW);

  attachInterrupt(digitalPinToInterrupt(BOTAO_POWER), ligaDesliga, FALLING);
  attachInterrupt(digitalPinToInterrupt(DIR_BOTAO), sentido, FALLING);
}

void motorGirando(){
  digitalWrite(STEP, HIGH);
  delayMicroseconds(1000);
  digitalWrite(STEP, LOW);
  delayMicroseconds(1000);
}

void loop(){ 
  if (motorEnabled){
    digitalWrite(ENABLE, motorEnabled ? LOW : HIGH);

    if (motorDirection){
      if(limparLCD){
        LCD.clear();
        limparLCD = !limparLCD;
      }

      LCD.setCursor(0, 0);
      LCD.print("Sentido:");

      LCD.setCursor(0, 1);
      LCD.print("Horario");

      digitalWrite(DIR, HIGH);

      for (int i = 0; i < steps_per_rev; i++){
        motorGirando();
      }

      digitalWrite(DIR, LOW);

      for (int i = 0; i < steps_per_rev; i++){
        motorGirando();
      }
    } else {
      if(limparLCD == false){
        LCD.clear();
        limparLCD = !limparLCD;
      }

      LCD.setCursor(0, 0);
      LCD.print("Sentido:");

      LCD.setCursor(0, 1);
      LCD.print("Anti-Horario");

      digitalWrite(DIR, LOW);

      for (int i = 0; i < steps_per_rev; i++){
        motorGirando();
      }

      digitalWrite(DIR, HIGH);

      for (int i = 0; i < steps_per_rev; i++){
        motorGirando();
      }
    }
  }
}