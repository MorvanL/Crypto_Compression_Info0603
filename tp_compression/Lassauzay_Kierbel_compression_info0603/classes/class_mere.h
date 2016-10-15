#ifndef _CLASSMERE_
#define _CLASSMERE_

#include "BitStream.h"

#include <string>
using namespace std;

class class_mere{
	public :
		string lireDonnee (char* nomFichier);
		void recuperer_resultat (Bits::Stream* stream, string &msg, int& old_size, int& new_size); 
		virtual void encode(Bits::Stream*, string &msg) = 0;
		virtual void decode(Bits::Stream*) = 0;
};

#endif
