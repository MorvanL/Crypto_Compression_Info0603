#include "Noeud.h"

// Constructeur
Noeud::Noeud (int freq, string ch) {
	f = freq;
	this->ch = ch;
	filsG = NULL;
	filsD = NULL;
}

Noeud* Noeud::getFG() {
	return filsG;
}

Noeud* Noeud::getFD(){
	return filsD;
}

string Noeud::getCH(){
	return ch;
}

int Noeud::getF(){
	return f;
}

void Noeud::setFG(Noeud* fg){
	filsG = fg;
}

void Noeud::setFD(Noeud* fd){
	filsD = fd;
}
