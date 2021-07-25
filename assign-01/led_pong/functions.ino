#include <stdlib.h>     // libreria del random
#include "functions.h"

volatile int gameState;    // stato del gioco


int ledCorrente;                // scelgo il random LED per iniziare
int next;                       // variabile per saltare gli step
int ledTurn;                    // variablie per gestire i turni dei LED ( dal led centrale )
unsigned long previousMillis;   // 
int puntiTL = 0;
int puntiTR = 0;
long interval = 2000;
long intervalSpeed = 2000;
int speedPotenziometro = 0;

    int brightness;
    int fadeAmount = 5;
    int currIntensity = 0;
    

//settagio delle variabili
void settingVariable() {
    gameState = 0;
  ledCorrente = 0;

  
}

void turnOnRandomLed(){
	// Funzione random che mi retorna 1 o 0 
	srand(time(NULL));
	ledCorrente = rand()%2;
	Serial.println(ledCorrente);
	// Assegno i versi dei LED
	if(ledCorrente == 0) {
		next = 1;
	}
	if(ledCorrente == 1) {
		next = 2;
	}
}

void startGame(){
	
  if (L_FLASH == HIGH) {
      analogWrite(L_FLASH, 0);
  }
  digitalWrite(LM, HIGH);
  Serial.println("LM ON, game started");
  delay(1000);
  digitalWrite(LM, LOW);
    previousMillis = timeFromStart;               // tengo traccia di quanto tempo quello è stato acceso
  gameState++;

  
}

void ledRandomMove() {
  unsigned long currentMillis = 0;
  int noMoreTR = 0;
  int noMoreTL = 0;
  int currentPuntiTL = 0, currentPuntiTR = 0; // Ho aggiunto O dopo la variabile globale che avevi creato perchè non volevo usare una variabile globale nel ciclo while, per motivi di atomiticità
  
  turnOnRandomLed();
        
  while(1){
    
    // Se next == 1, vuol dire che nextO == 1 ed dobbiamo accendere LLeft
    if (next == 1) {
			  Serial.println("Entro next 1");
			  digitalWrite(LL, HIGH);
        currentMillis = millis();

			if (digitalRead(TL) == HIGH && noMoreTL == 0) {
				  Serial.println("Add point to TL");
				  noMoreTL = 1;
				  puntiTL ++;
			}else {
            if(digitalRead(TR) == HIGH ){
              Serial.println("PERSO LR -- TR SBAGLIATO");
              finish(LL,LR);
              delay(1000);    // Tempo di attesa per fare le stampe
              exit (0);
            }
			}

	    Serial.print("\nPunti TL: ");
      Serial.println(puntiTL);
	    Serial.println(currentMillis);
      Serial.println(previousMillis);

      if (currentMillis - previousMillis  >= interval) {
		      previousMillis = currentMillis;
          if (noMoreTL == 0) {
			        Serial.println("Game over for TL");
			        finish(LR,LL);
              delay(1000);    // Tempo di attesa per fare le stampe
			        exit (0);
          }
          Serial.println("TURN OF LL");
          digitalWrite(LL, LOW);
          noMoreTL = 0;
          ledTurn = 1;  // se ledTurn ==, LMiddle mi deve passare da led a destra
          next = 3; 
      }
    } else {
      // per step next == 2, gestisco il LED a destra
		    if (next == 2 ) {
              Serial.println("Entro next 2");
              currentMillis = millis();
			        digitalWrite(LR, HIGH);
			
			      if ( digitalRead(TR) == HIGH && noMoreTR == 0) {
					      noMoreTR = 1;
					      puntiTR ++;
            }else {
                if(digitalRead(TL) == HIGH ){
                   Serial.println("PERSO LL -- TL SBAGLIATO");
                    finish(LR,LL);
                    delay(1000);    // Tempo di attesa per fare le stampe
                    exit (0);
                  }
             }
			  
			      Serial.print("\nPunti TR: ");
			      Serial.println(puntiTR);
			      Serial.println(currentMillis);
            Serial.println(previousMillis);
            
			    if (currentMillis - previousMillis  >= interval) {
					      previousMillis = currentMillis;
			          if (noMoreTR == 0) {
				            Serial.println("Game over for TR");
				            finish(LL,LR);
                    delay(1000);    // Tempo di attesa per fare le stampe
				            exit (0);
			        } 
  			      digitalWrite(LR, LOW);
			        noMoreTR = 0;
			        ledTurn = 2;
			        next = 3;
         }
      } else {
        // Se next == 3 è il caso di accendere LM, quello nel mezzo
			      if ( next == 3 ) {
				        Serial.println("Entro next 3");    
				        digitalWrite(LM, HIGH);
                currentMillis = millis();
                
			        	if (currentMillis - previousMillis  >= intervalSpeed) {
                      interval = (interval - (interval/8));
                      intervalSpeed = (intervalSpeed/speedPotenziometro);
				            	previousMillis = currentMillis;
                      Serial.println(intervalSpeed);
                      Serial.println(currentMillis);
                      Serial.println(previousMillis);
                     
					            digitalWrite(LM, LOW);
					            if (ledTurn == 1) {              // si deve accendere Ldestra
						              next = 2;
					            } else {
					              	if (ledTurn == 2) {             // si deve accendere Lsinistra
							                next = 1;
						              }
					            }
               }
            }
        }
      }
    }
  
}


// Pulse L_Flash ( Check if T_START IS ON )
void waitingForStart() {
  do{
    analogWrite(L_FLASH, currIntensity);
    currIntensity = currIntensity + fadeAmount;
    if (currIntensity == 0 || currIntensity == 255) {
       fadeAmount = -fadeAmount ;
    }
     delay(20); 

  if(digitalRead(T_START) == HIGH ){
        gameState++;
        analogWrite(L_FLASH, 0);
  }
  }while(gameState ==0 );
}
//interrupt legato al button T_START per far partire il gioco
//void gameStart() {
//  if (!gameState) { //se gameState è uguale a 0 allora incremento gameState e passo allo stato successivo
//    gameState++;
//  }
//}

int readPotenziometro(){
  Serial.println("Did I read");
  int newValue = analogRead(POT);
      if (newValue != speedPotenziometro){
          speedPotenziometro = newValue;
      }   
     // fix the speed of Potentiometer : divide for 100
   Serial.println(speedPotenziometro/100);
   delay(1000);
   return  (speedPotenziometro/100);


}

void finish(int ledwin,int ledlose){
  digitalWrite(ledlose, LOW);
  digitalWrite(LM, LOW);
  int i =0;
  while(i<2){
    digitalWrite(ledwin, HIGH);
    delay(500);
    digitalWrite(ledwin, LOW);
    delay(500);
    i++;
  }

  if( ledwin == 10 ){
      Serial.print("\nGame Over The Winner is Player: RIGHT with "); 
      Serial.print(puntiTR);
      Serial.print(" shots.");
  }else {
      Serial.print("\nGame Over The Winner is Player: LEFT with "); 
      Serial.print(puntiTL);
      Serial.print(" shots.");
  }

  digitalWrite(ledwin, LOW);
  
}
//metodo gestione azione dell'utente sui bottoni
void userAction() {

}
