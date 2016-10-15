#ifndef __CODERLE__
#define __CODERLE__

#include "class_mere.h"
 
#define NB_SYMBOLES_RLE 8

class CRLE : public class_mere {
	private :
		char symboles [NB_SYMBOLES_RLE];
		int occurrences [NB_SYMBOLES_RLE]; // l'occurrence et le symbole correspondant dispose du meme indice dans leur tableau respectif
		char moins_freq;
	public :
		CRLE(); 
		void trouve_minF(string &msg);// Calcul le nombre d'occurrence de chaque symbole dans le msg, initialise la table des symboles et trouve le symbole le moins frequent dans le fichier afin qu'il serve a coder les runs
		void RLEoutput(Bits::Stream* stream, int n, char p);
		void encode(Bits::Stream*, string &msg);
		void decode(Bits::Stream*);
};

#endif
