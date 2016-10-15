#include <cstdio>
#include <iostream>
#include <string>
#include <math.h>

#include "LZW.h"

// Constructeur
LZW::LZW (){
	int i;
	for(i=0; i < NB_SYMBOLES_DICO; i++) {
		dico[i] = string(" ");
		dico_decode[i] = string(" ");
	}
}

// Methodes

void LZW::initialise_dico(string &msg) {
	int i = 0, j = 0, k = 0;
	while(i < NB_SYMBOLES_ALPHABET) {
		j = 0;
		while((j < i) && (dico[j] != string(1,msg[k]))) {
			j++;
		}
		if(j == i) {
			dico[i] = string(1,msg[k]);
			dico_decode[i] = string(1,msg[k]);
			i++;
			
		}
		k++;
	}
}

int LZW::est_dans_dico(string s) {
	int i = 0;
	while((dico[i] != " ") && (dico[i] != s) ){
		i++;
	}
	if(dico[i] == " ") {
		return 0;
	}
	return i+1;
}

void LZW::encode(Bits::Stream* stream, string &msg) {
	Bits::Block<int32_t>  bits(log2(NB_SYMBOLES_DICO)+1);
	int i = 0, k = NB_SYMBOLES_ALPHABET;
	int code;
	string wn;
	
	// écriture dans le stream
	cout << "Write "<< msg << " in stream\n";
	for(i=0; i < msg.size(); i++) {
		if(est_dans_dico(wn + msg[i]) != 0) {
			wn = wn + msg[i];
		}
		else {
			if(k < NB_SYMBOLES_DICO-1) {
				dico[k] = wn + msg[i];
				k++;
			}
			code = est_dans_dico(wn) - 1;
			bits.set(code);
			stream->write_bits(bits);
			wn = msg[i];
		}
	}
	code = est_dans_dico(wn) - 1;
	bits.set(code);
	stream->write_bits(bits);
}

void LZW::decode(Bits::Stream* stream) {
	Bits::Block<int32_t>		bits(log2(NB_SYMBOLES_DICO)+1);
	string w;
	string en;
	int k = NB_SYMBOLES_ALPHABET;
	int c;
	
	// lecture dans le stream
	printf("\nRead with in stream: ");
	stream->read_bits(bits);
	c = bits.get();
	en = dico_decode[c];
	cout<<en;
	while (!stream->end_of_stream()) {
		stream->read_bits(bits);
		c = bits.get();
		if(dico_decode[c] == " ") {
			w = en + en[0];
			en = w;
		}
		else {
			w = en + (dico_decode[c])[0];
			en = dico_decode[c];
		}
		if(k < NB_SYMBOLES_DICO-1) {
			dico_decode[k] = w;
			k++;
		}
		cout<<en;
	}
	printf("\n");
}














