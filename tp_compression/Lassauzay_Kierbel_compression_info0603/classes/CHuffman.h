#ifndef _CHUFFMAN_
#define _CHUFFMAN_

#include "class_mere.h"
#include "Noeud.h"

#define NB_SYMBOLES_HUFF 8

class CHuffman : public class_mere {
	private :
		char symboles [NB_SYMBOLES_HUFF]; // Sert à stocker les codes et les symboles (sera trié par ordre de fréquence par la suite)
		int occurrences [NB_SYMBOLES_HUFF]; // l'occurrence et le symbole correspondant dispose du meme indice dans leur tableau respectif
		Noeud* arbre[NB_SYMBOLES_HUFF];
		int codes [NB_SYMBOLES_HUFF][2]; // Sert à stocker le code de chaque symbole ainsi que le nombre de bits valides. l'indice du code correspond à l'indice du symbole dans "symboles"
	public :
		CHuffman(); 
		Noeud* getArbre();
		void calcul_occurrence(string &msg);// Calcul le nombre d'occurrence de chaque symbole dans le msg et initialise la table des symboles
		void tri_symboles();  // tri les symboles par ordre decroissant d'occurrence
		void etabli_code(); //Construit l'abre de Huffman à partir des fréquences et établi le code de chaque caractère
		Noeud* fusionner_noeuds(Noeud* n1, Noeud* n2); // n1 etant le plus frequent et n2 le moins frequent
		void definir_code(Noeud* n, int code, int bits_valides); // Parcours l'arbre pour definir le code de chaque caractère
		void encode(Bits::Stream*, string &msg);
		void decode(Bits::Stream*);
		void detruit_ressources(Noeud* n);
		int calcul_entete();
};

#endif


