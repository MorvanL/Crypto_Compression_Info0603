#ifndef __CODETAILLEVARIABLE__
#define __CODETAILLEVARIABLE__

#include "class_mere.h"
 
#define NB_SYMBOLES_CTV 8

/* code : 0 pour le caractere le plus frequent, puis 10, puis 110, puis 1110, etc... */
class CTV : public class_mere {
	private :
		char symboles [NB_SYMBOLES_CTV];
		char symboles_tries [NB_SYMBOLES_CTV];
		int occurrences [NB_SYMBOLES_CTV]; // l'occurrence et le symbole correspondant dispose du meme indice dans leur tableau respectif à l'indice du symbole dans "symboles"
	public :
		CTV(); 
		void calcul_occurrence(string &msg);// Calcul le nombre d'occurrence de chaque symbole dans le msg et initialise la table des symboles
		void tri_symboles();  // tri les symboles par ordre decroissant d'occurrence => le symbole a l'indice 2 possedera ensuite le code "110"
		void encode(Bits::Stream*, string &msg);
		void decode(Bits::Stream*);
};

#endif


