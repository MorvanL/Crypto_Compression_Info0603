#ifndef __LZW__
#define __LZW__

#include "class_mere.h"
 
#define NB_SYMBOLES_ALPHABET 8
#define NB_SYMBOLES_DICO 255

class LZW : public class_mere {
	private :
		string dico [NB_SYMBOLES_DICO]; // dictionnaire pour le codage : l'indice du symbole dans le dictionnaire défini son code
		string dico_decode [NB_SYMBOLES_DICO]; // dictionnaire pour le decodage : l'indice du symbole dans le dictionnaire défini son code
	public :
		LZW(); 
		void initialise_dico(string &msg); // Initialise les dictionnaires avec les différents symboles de l'alphabet
		int est_dans_dico(string s); //retourne 0 si s n'appartient pas au dico, renvoie l'indice dans le dico sinon
		void encode(Bits::Stream*, string &msg);
		void decode(Bits::Stream*);
};

#endif


