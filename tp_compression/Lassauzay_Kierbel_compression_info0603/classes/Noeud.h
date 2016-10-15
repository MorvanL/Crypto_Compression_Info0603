#ifndef _NOEUD_
#define _NOEUD_

#include <string>
using namespace std;

class Noeud {
	private :
		Noeud* filsG;
		Noeud* filsD;
		string ch;
		int f;
	public :
		Noeud(int freq, string ch);
		Noeud* getFG();
		Noeud* getFD();
		string getCH();
		int getF();
		void setFG(Noeud* fg);
		void setFD(Noeud* fd);
};



#endif
