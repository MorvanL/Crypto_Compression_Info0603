#include <cstdio>
#include <iostream>
#include "CHuffman.h"

// Constructeur
CHuffman::CHuffman (){
	int i;
	for(i = 0; i<NB_SYMBOLES_HUFF; i++) {
		occurrences[i] = 0;
	}
}

// Retourne le premier element du tableau de noeud servant au codage 
Noeud* CHuffman::getArbre() {
	return arbre[0];
}

// Calcul le nombre d'occurrence de chaque symbole dans le msg et initialise la table des symboles
void CHuffman::calcul_occurrence(string &msg) {
	int i = 0, j = 0, k = 0;
	while(i < msg.size()) {
		j = 0;
		while((j < k)  &&  (msg[i] != symboles[j])) {
			j++;
		}
		if(j == k) {
			symboles[k] = msg[i];
			occurrences[k] += 1;
			k++;	
		}
		else{
			occurrences[j] += 1;
		}
		i++;
	}
}

// tri les symboles par ordre decroissant d'occurrence
void CHuffman::tri_symboles() {
	int i, j;
	int indiceMax = 0;
	char tmp;
	int tmp2;
	for(i=0; i < NB_SYMBOLES_HUFF; i++) {
		indiceMax = i;
		for(j=0+i; j < NB_SYMBOLES_HUFF; j++) {
			if( occurrences[j] >= occurrences[indiceMax] ){
				indiceMax = j;
			}
		}
		tmp = symboles[i];
		symboles[i] = symboles[indiceMax];
		symboles[indiceMax] = tmp;
		tmp2 = occurrences[i];
		occurrences[i] = occurrences[indiceMax];
		occurrences[indiceMax] = tmp2;
	}
}

//Construit l'abre de Huffman à partir des fréquences et établi le code de chaque caractère
void CHuffman::etabli_code() {
	int i, j = NB_SYMBOLES_HUFF-1, k;
	int insere = -1;
	int code = 0; //Contient le code des symboles
	int bits_valides = 0;
	// Creer les noeuds correspondants à chaque symboles
	for(i=0; i < NB_SYMBOLES_HUFF; i++) {
		arbre[i] = new Noeud(occurrences[i], string(1,symboles[i]));
	}
	// Creer l'arbre
	for(i=0; i < NB_SYMBOLES_HUFF-2; i++) {
		insere = -1;
		// On créer le nouveau noeud à partir des deux noeuds disposant de la plus petite clé
		arbre[j] = fusionner_noeuds(arbre[j-1], arbre[j]);
		k = j-2;
		// On place le nouveau Noeud à la bonne place
		while((insere != 0) && (k >= 0)) {
			if(arbre[k]->getF() <= arbre[j]->getF()) {
				arbre[k+1] = arbre[k];
				k--;
			}
			else {
				arbre[k+1] = arbre[j];
				insere = 0;
			}
		}
		if(k < 0){
			arbre[k+1] = arbre[j];
		}
		j--;
	}
	//On effectue la dernière étape
	arbre[j] = fusionner_noeuds(arbre[j-1], arbre[j]);
	arbre[j-1] = arbre[j];
	// Etabli le code de chaque caractère
	definir_code(arbre[0], code, bits_valides);
}

// n1 etant le plus frequent et n2 le moins frequent
Noeud* CHuffman::fusionner_noeuds(Noeud* n1, Noeud* n2) {
	Noeud* n3  = new Noeud(n1->getF() + n2->getF(), n1->getCH() + n2->getCH());
	n3->setFG(n1);
	n3->setFD(n2);
	return n3;
}

// Parcours l'arbre pour definir le code de chaque caractère
void CHuffman::definir_code(Noeud* n, int code, int bits_valides) {
	int j = 0;
	if((n->getFG() == NULL) && (n->getFD() == NULL)) {
		while(n->getCH() != string(1, symboles[j])) {
			j++;
		}
		codes[j][0] = code;
		codes[j][1] = bits_valides;
	}
	else {
		code = code*2;
		if(n->getFG() != NULL) {
			definir_code(n->getFG(), code, bits_valides+1);
		}
		if(n->getFD() != NULL) {
			definir_code(n->getFD(), code+1, bits_valides+1);
		}
	}
}

void CHuffman::encode(Bits::Stream* stream, string &msg) {
	Bits::Block<int32_t>		bits(1); // int_32 permet d'avoir un arbre sur 33 étages (le code serait alors certainement peu efficace)
	int j = 0; 

	// écriture dans le stream
	cout << "Write "<< msg << " in stream\n";
	for (size_t i = 0; i < msg.size(); i++) {
		j = 0;
		while( msg[i] != symboles[j] ) {
			j++;
		}
		bits.set(codes[j][0], codes[j][1]);	
		stream->write_bits(bits);
	}
}

void CHuffman::decode(Bits::Stream* stream){
	Bits::Block<int8_t>		bits(1);
	int i;
	Noeud* n;
	int continu = 0;
	// lecture dans le stream
	printf("\nRead with in stream: ");
	while (!stream->end_of_stream()) {
		n = arbre[0];
		continu = 0;
		while(continu == 0) {
			stream->read_bits(bits);
			if(bits.get() != 0) {
				n = n->getFD();
			}
			else {
				n = n->getFG();
			}
			if((n->getCH()).size() == 1) {
				cout<<n->getCH();
				continu = -1;
			}
		}
	}
	cout<<"\n";
}

void CHuffman::detruit_ressources(Noeud* n) {
	if(n->getFG() != NULL)
		detruit_ressources(n->getFG());
	if(n->getFD() != NULL)
		detruit_ressources(n->getFD());
	delete n;
}

int CHuffman::calcul_entete() {
	int entete, i;

	entete = ((8*NB_SYMBOLES_HUFF) * 2) + 8; // Taille de la table des symboles + nb de bits valide pour chaque symbole + nb de symboles
	for(i=0; i < NB_SYMBOLES_HUFF; i++) {	// On ajoute le code de chaque symbole
		entete += codes[i][1];
	}

	return entete;
}





