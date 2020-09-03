/*
      Sound Sensor Demo
          (v1.0 - 19/02/16)

  Copyright 2017 RoboCore (François) ( http://www.RoboCore.net )
  
  ------------------------------------------------------------------------------
  This program is free software: you can redistribute it and/or modify
  it under the terms of the GNU Lesser General Public License as published by
  the Free Software Foundation, either version 4 of the License, or
  (at your option) any later version.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public License
  along with this program.  If not, see <http://www.gnu.org/licenses/>.
  ------------------------------------------------------------------------------
  
  This code demonstrates de use of the sensor by reading it over an analog
  pin and turning the LEDs on according to the value read. The center reading
  of the sensor is 2,5 V, which corresponds to the yellow LED [5]. 5 green LEDs
  [0-4] and 5 red LEDs [6-11] represent the positive and negative magnitudes
  over the center value.
  
  NOTE: with the debug function enabled the response of the program is
        considerably slower.
  
*/

#include <Arduino.h>

// #define DEBUG

#ifdef DEBUG
#define TAB() 
// {       
//   Serial.print('\t'); 
// }
#else
#define TAB()
#endif

#define ANALOG_2V5        512  // Aref = 5V with 10 bits resolution (4,88 mV/bit)
#define ANALOG_DEVIATION  100  // 0,5 V deviation

const int pinMicrophone = A1;
const int pinLED[] = { 3 , 4 , 5 , 6 , 7 , 8 , 9 , 10 , 11 , 12 , 13 }; // 5x Green + 1x Yellow + 5x Red
const int thresholds[] = { 100 , 200 , 300 , 400 , 512 , 630 , 730 , 830 , 930 };
const int *ptrYellow = &pinLED[5];

int analog_value;

void setup(){
#ifdef DEBUG
  Serial.begin(9600);
  Serial.println("Sound Sensor Demo");
#endif

  for(int i=0 ; i < 11 ; i++){
    pinMode(i, OUTPUT);
    digitalWrite(i, LOW);
  }
  
}


void loop(){
  analog_value = analogRead(pinMicrophone);
  
  if(abs(analog_value - ANALOG_2V5) <= ANALOG_DEVIATION){
      for(int i=0 ; i < 11 ; i++)
        digitalWrite(pinLED[i], LOW);
    digitalWrite(pinLED[5], HIGH);
  } else {
    digitalWrite(pinLED[5], LOW);
  
    if(analog_value < ANALOG_DEVIATION){
      for(int i=0 ; i < 5 ; i++)
        digitalWrite(pinLED[i], LOW);
      
      TAB();
      digitalWrite(pinLED[6], HIGH); // then the first interval must be active
      if(analog_value < 400){
        TAB();
        digitalWrite(pinLED[7], HIGH);
      }
      if(analog_value < 300){
        TAB();
        digitalWrite(pinLED[8], HIGH);
      }
      if(analog_value < 200){
        TAB();
        digitalWrite(pinLED[9], HIGH);
      }
      if(analog_value < 100){
        TAB();
        digitalWrite(pinLED[10], HIGH);
      }
    } else {
      for(int i=6 ; i < 11 ; i++)
        digitalWrite(pinLED[i], LOW);
      
      TAB();
      digitalWrite(pinLED[4], HIGH); // then the first interval must be active
      if(analog_value > 630){
        TAB();
        digitalWrite(pinLED[3], HIGH);
      }
      if(analog_value > 730){
        TAB();
        digitalWrite(pinLED[2], HIGH);
      }
      if(analog_value > 830){
        TAB();
        digitalWrite(pinLED[1], HIGH);
      }
      if(analog_value > 930){
        TAB();
        digitalWrite(pinLED[0], HIGH);
      }
    }
  }
  
#ifdef DEBUG
  Serial.println(analog_value);
  delay(50);
#else
  delay(1);
#endif
}






// #include <Arduino.h>

// int pinoLed = 12; //PINO DIGITAL UTILIZADO PELO LED
// #define pinoSensor A0 //PINO DIGITAL UTILIZADO PELO SENSOR
// int estadoSensor; //VARIÁVEL QUE ARMAZENA O ESTADO DA SAÍDA DO SENSOR (HIGH / LOW)

// void setup(){
//   pinMode(pinoSensor, INPUT); //DEFINE O PINO COMO ENTRADA
//   pinMode(pinoLed, OUTPUT); //DEFINE O PINO COMO SAÍDA
// }

// void loop(){
//   if (analogRead(pinoSensor) > 1000){ //SE A LEITURA DO PINO FOR IGUAL A HIGH, FAZ
//       estadoSensor = digitalRead(pinoLed); //LÊ O ESTADO ATUAL DO PINO E ARMAZENA NA VARIÁVEL
//       digitalWrite(pinoLed, !estadoSensor); //MUDA O ESTADO ATUAL DO LED COMPARANDO COM O ESTADO
//       //ARMAZENADO NA VARIÁVEL estadoSensor
//       delay(500); //INTERVALO DE 500 MILISSEGUNDOS
//   }
// }