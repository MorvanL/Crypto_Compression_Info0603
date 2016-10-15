#include <cstdio>
#include <iostream>
#include <fstream>
#include "CTV.h"

// Constructeur
CTV::CTV (){
	int i;
	for(i = 0; i<NB_SYMBOLES_CTV; i++) {
		occurrences[i] = 0;
	}
}

// Methodes

// Calcul le nombre d'occurrence de chaque symbole dans le msg et initialise la table des symboles
void CTV::calcul_occurrence(string &msg) {
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

// tri les symboles par ordre decroissant d'occurrence => le symbole a l'indice 2 possedera ensuite le code "110"
void CTV::tri_symboles() {
	int i, j;
	int indiceMax = 0;
	for(i=0; i < NB_SYMBOLES_CTV; i++) {
		for(j=0; j < NB_SYMBOLES_CTV; j++) {
			if( occurrences[j] >= occurrences[indiceMax] ){
				indiceMax = j;
			}
		}
		symboles_tries[i] = symboles[indiceMax];
		occurrences[indiceMax] = -1;
	}
}

void CTV::encode(Bits::Stream* stream, string &msg) {	
	Bits::Block<int32_t>		bits(1); 
	int j = 0; 

	// écriture dans le stream
	cout << "Write "<< msg << " in stream\n";
	for (size_t i = 0; i < msg.size(); i++) {
		j = 0;
		while( msg[i] != symboles_tries[j] ) {
			bits.set(1);
			stream->write_bits(bits);	
			j++;
		}
		bits.set(0);	
		stream->write_bits(bits);
	}
}

void CTV::decode (Bits::Stream* stream) {
	Bits::Block<int8_t>		bits(1);
	int i;
	
	// lecture dans le stream
	printf("\nRead with in stream: ");
	while (!stream->end_of_stream()) {
		i = 0;
		stream->read_bits(bits);
		while(bits.get() != 0) {
			i++;
			stream->read_bits(bits);
		}
		printf("%c", symboles_tries[i]);
	}
	printf("\n");
}	

