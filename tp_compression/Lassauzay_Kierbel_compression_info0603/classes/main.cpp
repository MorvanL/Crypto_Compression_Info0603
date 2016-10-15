#include "CTF.h"
#include "CTV.h"
#include "CRLE.h"
#include "CHuffman.h"
#include "LZW.h"
#include <cstdio>
#include <iostream>

int main(int argc, char* argv[]) {
	
	Bits::Stream stream;
	int old_size, new_size;
	
/*	CTF ctf;				/////// Taille fixe (ne pas oublier d'indiquer le nombre de symbole dans .h) ///////
	string msg = ctf.lireDonnee(argv[1]);
	ctf.encode(&stream, msg);
	ctf.recuperer_resultat(&stream, msg, old_size, new_size);
	ctf.decode(&stream);
	cout << "Taille des donnees avant codage : " << old_size << endl;
	cout << "Taille des donnees après codage : " << new_size << endl;
	cout << "Taille des donnees après codage avec entete : " << new_size + 8 << endl;
*/	

/*	CTV ctv;				/////// Taille variable (ne pas oublier d'indiquer le nombre de symbole dans .h) ///////
	string msg = ctv.lireDonnee(argv[1]);
	ctv.calcul_occurrence(msg);
	ctv.tri_symboles();
	ctv.encode(&stream, msg);
	ctv.recuperer_resultat(&stream, msg, old_size, new_size);
	ctv.decode(&stream);
	cout << "Taille des donnees avant codage : " << old_size << endl;
	cout << "Taille des donnees après codage : " << new_size << endl;
	cout << "Taille des donnees après codage avec entete : " << new_size + 8*(NB_SYMBOLES_CTV+1) << endl;
*/

/*	CRLE crle;				/////// RLE (ne pas oublier d'indiquer le nombre de symbole dans .h) ///////
	string msg = crle.lireDonnee(argv[1]);
	crle.encode(&stream, msg);
	crle.recuperer_resultat(&stream, msg, old_size, new_size);
	crle.decode(&stream);
	cout << "Taille des donnees avant codage : " << old_size << endl;
	cout << "Taille des donnees après codage : " << new_size << endl;
	cout << "Taille des donnees après codage avec entete : " << new_size + 8 << endl;
*/

/*	CHuffman cHuff;				/////// Huffman (ne pas oublier d'indiquer le nombre de symbole dans .h) ///////
	string msg = cHuff.lireDonnee(argv[1]);
	cHuff.calcul_occurrence(msg);
	cHuff.tri_symboles();
	cHuff.etabli_code();
	cHuff.encode(&stream, msg);
	cHuff.recuperer_resultat(&stream, msg, old_size, new_size);
	cHuff.decode(&stream);
	cHuff.detruit_ressources(cHuff.getArbre());
	cout << "Taille des donnees avant codage : " << old_size << endl;
	cout << "Taille des donnees après codage : " << new_size << endl;
	new_size += cHuff.calcul_entete();
	cout << "Taille des donnees après codage avec entete : " << new_size << endl;
*/

/*	LZW lzw;				/////// LZW (ne pas oublier d'indiquer le nombre de symbole dans .h)///////
	string msg = lzw.lireDonnee(argv[1]);
	lzw.initialise_dico(msg);
	lzw.encode(&stream, msg);
	lzw.recuperer_resultat(&stream, msg, old_size, new_size);
	lzw.decode(&stream);
	cout << "Taille des donnees avant codage : " << old_size << endl;
	cout << "Taille des donnees après codage : " << new_size << endl;
	cout << "Taille des donnees après codage avec entete : " << new_size + 8*(NB_SYMBOLES_ALPHABET+1) << endl;
*/
	return 0;
}

