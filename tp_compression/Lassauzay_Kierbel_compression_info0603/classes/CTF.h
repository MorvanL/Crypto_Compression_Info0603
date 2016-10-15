#ifndef __CODETAILLEFIXE__
#define __CODETAILLEFIXE__

#include "class_mere.h"

#define BITLEN 3 // Nombre de bits utilisés pour coder un caractère

class CTF : public class_mere {
	public :
		CTF();
		void encode(Bits::Stream* stream, string &msg);
		void decode( Bits::Stream* stream);
};

#endif



