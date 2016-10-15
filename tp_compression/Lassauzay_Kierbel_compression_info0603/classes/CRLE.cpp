#include <cstdio>
#include <iostream>
#include "CRLE.h"

// Constructeur
CRLE::CRLE (){
	int i;
	for(i = 0; i<NB_SYMBOLES_RLE; i++) {
		occurrences[i] = 0;
	}
}

// Methodes

// Calcul le nombre d'occurrence de chaque symbole dans le msg, initialise la table des symboles et trouve le symbole le moins frequent dans le fichier afin qu'il serve a coder les runs
void CRLE::trouve_minF(string &msg) {
	int i = 0, j = 0, k = 0;
	int indiceMin = 0;
	//calcule les occurrences
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
	// recupere le symbole le moins frequent
	for(i=1; i < NB_SYMBOLES_RLE; i++) {
		if( occurrences[i] < occurrences[indiceMin] ){
			indiceMin = i;
		}
	}
	moins_freq = symboles[indiceMin];
}

void CRLE::RLEoutput(Bits::Stream* stream, int n, char p) {
	int i;
	int8_t k;
	Bits::Block<int8_t>		bits(8);
	
	if(n <= 3) {
		for(i=0; i<n; i++) {
			if(p != moins_freq) {
				bits.set(p);
				stream->write_bits(bits);
			}
			else {
				bits.set(p);
				stream->write_bits(bits);
				bits.set(0);
				stream->write_bits(bits);
			}
		}
	}
	else {
		while(n > 0) {
			if(n > 255){
				k = 255;	
			}
			else {
				k = n;
			}
			bits.set(moins_freq);
			stream->write_bits(bits);
			bits.set(k);
			stream->write(k);
			bits.set(p);
			stream->write_bits(bits);
			n = n-255;
			
		}
	}
}



void CRLE::encode(Bits::Stream* stream, string &msg) {	
	int i, n = 1; 
	char p;
	
	// écriture dans le stream
	cout << "Write "<< msg << " in stream\n";
	p = msg[0];
	for (size_t i = 1; i < msg.size(); i++) {
		if(msg[i] != p){
			RLEoutput(stream, n, p);
			n = 1;
		}
		else {
			n++;
		}
		p = msg[i];
	}
	RLEoutput(stream, n, p);
}

void CRLE::decode (Bits::Stream* stream) {
	Bits::Block<int8_t>		bits(8);
	int i, j;
	char p; 
	int8_t q;
	
	// Deuxieme lecture dans le stream : le code decode
	stream->read_reset();
	printf("\nRead with in stream: ");
	while (!stream->end_of_stream()) {
		stream->read_bits(bits);
		p = bits.get();
		if(p == moins_freq) {
			stream->read_bits(bits);
			q = bits.get();
			if(q != 0) {
				stream->read_bits(bits);
				p = bits.get();
				for(j=0; j<q; j++) {
					printf("%c", p);
				}
			}
			else {
				printf("%c", p);
			}
		}
		else {
			printf("%c", p);
		}
	}
	printf("\n");
}	

