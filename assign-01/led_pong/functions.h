
#ifndef __DEF

// Definizione dei pin
#define __DEF
#define L_FLASH 9      // Led rosso
#define LR 10          // Led destra
#define LM 11          // Led centrale
#define LL 12          // Led sinistra
#define T_START 2      // Bottone di start
#define TR 3           // Bottone di destra
#define TL 4           // Botton di sinistra
#define POT A0         // Potenziometro


// settagio delle variabili
void settingVariable();

//azione prima che il gioco inizi, ovvero lampeggio del led
void waitingForStart();

// cambiamento dello stato del GAME
void gameStart();

// gestisco i bottoni e i LED
void ledRandomMove();

// scelta del LED per iniziare il gioco
void turnOnRandomLed();

// definizione stato iniziale del gioco
void startGame();

#endif
