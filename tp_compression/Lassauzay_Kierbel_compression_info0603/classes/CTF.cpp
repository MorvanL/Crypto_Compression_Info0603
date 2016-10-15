#include <cstdio>
#include <iostream>
#include "CTF.h"

// Constructeur
CTF::CTF (){
}

// Méthodes
void CTF::encode(Bits::Stream* stream, string &msg) {	
	const int			bitlen = BITLEN;
	Bits::Block<int8_t>		bits(bitlen);		// un entier 8 bits est suffisant pour stocker 3 bits

	// écriture dans le stream
	cout << "Write "<< msg << " with 3bits/bloc in stream\n";
	for (size_t i = 0; i < msg.size(); i++) {
		bits.set(msg[i] - 'A');		/// implique A=0, B=1, ...		
		stream->write_bits(bits);
		// trace
/*		printf("Writing %c : ", msg[i]);
		Bits::View<char>(msg[i] - 'A', bitlen, bitlen);		// ceci affiche les LSBs a gauche
		printf(" - Stream : ");
		stream->view(bitlen);
		printf("\n");
*/
	}

/*	// Affichage du stream après écriture
	printf("LSB: "); stream->viewLSB(bitlen); printf("\n");
	printf("MSB:"); stream->viewMSB(bitlen); printf("\n");
*/

	
}

void CTF::decode (Bits::Stream* stream) {
	const int			bitlen = BITLEN;
	Bits::Block<int8_t>		bits(bitlen);
	// lecture dans le stream
	printf("\nRead with 3bits/bloc in stream: ");
	while (!stream->end_of_stream()) {
		stream->read_bits(bits);
		printf("%c", bits.get() + 'A');
	}
	printf("\n");
	
/*	// deuxième lecture bit par bit
	{
		printf("\nRead bit/bit in stream: ");
		stream->read_reset();	// à ne pas oublier si plus d'une lecture est faite
		Bits::Bit	bit;
		int count = 0;
		while (!stream->end_of_stream()) {
			stream->read_bit(bit);
			printf("%d", (bit ? 1 : 0));
			count++;
			if (count % bitlen == 0) printf(" ");
		}
		printf("\n");
	}
*/
}	
