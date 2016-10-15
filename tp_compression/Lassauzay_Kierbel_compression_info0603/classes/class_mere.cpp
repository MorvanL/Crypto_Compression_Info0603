#include "class_mere.h"

#include <iostream>
#include <fstream>


// Méthodes
string class_mere::lireDonnee (char* nomFichier) {
	string msg;

        ifstream fichier(nomFichier, ios::in);  // on ouvre en lecture
        if(fichier)  // si l'ouverture a fonctionné
        {
                getline(fichier, msg);  // on met dans "msg" la ligne
                fichier.close();
        }
        else
                cerr << "Impossible d'ouvrir le fichier !" << endl;

        return msg;
}

void class_mere::recuperer_resultat (Bits::Stream* stream, string &msg, int& old_size, int& new_size) {
	old_size = msg.size() * 8;
	new_size = ((stream->get_size() - 1) * 32) + stream->get_WBit();
}

		
