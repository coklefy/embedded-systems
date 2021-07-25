#ifndef __POTENZIOMETRO_
#define __POTENZIOMETRO_

/* Potenziometro interface */
class Potenziometro {
	
	public:
		Potenziometro(int);
		int getValue();
	
	private:
		int pin;
};

#endif
