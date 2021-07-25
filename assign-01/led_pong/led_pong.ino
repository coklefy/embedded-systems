/**************************************************************************************************************\
 *                                                                                                            *
 *  Autori : Guri Sokol                                                                                       *
 *           D'Auria Nicola                                                                                   *
 *           Dene Hamado                                                                                      *
 *   Sistemi Embedded e IoT  - a.a. 2018-2019                                                                 *
 *   Progetto #1 - Led Pong                                                                                   *
 *   Si vuole realizzare un sistema embedded che implementa un gioco che chiamiamo Led Pong.                  *
 *   Il gioco consiste in un ping pong embedded in cui due giocatori Player 1 e Player 2 mediante             *  
 *   pulsanti tattili si lanciano una “pallina virtuale”, che si muove su led.                                *
 *                                                                                                            *
\**************************************************************************************************************/

#include "functions.h"     
#include "time.h"

extern volatile int gameState;
long timeFromStart = 0;         // variablie per tenere conto del tempo dall'inizio del programma

void setup() {
  
  //settaggio dei pin
  pinMode(L_FLASH, OUTPUT);
  pinMode(LR, OUTPUT);
  pinMode(LM, OUTPUT);
  pinMode(LL, OUTPUT);
  pinMode(T_START, INPUT);
  pinMode(TR, INPUT);
  pinMode(TL, INPUT);
  
  settingVariable();          // inizializzo le variabili
  Serial.begin(9600);
  Serial.println("Welcome to Led Pong. Press Key T_START to Start");
  readPotenziometro();       // leggo il valore del potenziometro 
}


void loop() {
  noInterrupts();             //disattivo gli interrupts così da poter settare la variabile state
  int state = gameState;      //assegno a state il valore di gameState
  interrupts();               // chiamo interrupt per eventualemte inziare la partita
  timeFromStart = millis();

  switch (state) {             
    
    // Aspettando che l'utente prema T_START button
    case 0: 
			  waitingForStart();    
			  break;

    // Utente ha premuto T_START e accendo LM per 1 sec
    case 1: 
	      startGame();
        break;
		
		// Gestisco i buttoni e i LED
    case 2: 
			ledRandomMove();
			break;
		
    default:
      break;
  }
  
}
