#include "CryptoTools.h"
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

#define NB_SYMBOLES 26


// Charge un fichier dans une variable de type string 
string lireDonnee (char* nomFichier) {
	string msg;
	string ligne;

        ifstream fichier(nomFichier, ios::in);  // on ouvre en lecture
        if(fichier)
	{
		while(getline(fichier, ligne))  // tant que l'on peut mettre la ligne dans "contenu"
		{
		        msg += ligne;
		}
	}
	else
                cerr << "Impossible d'ouvrir le fichier !" << endl;
	fichier.close();

        return msg;
}

/* Supprime tout les caracteres speciaux
   Transforme toutes les minuscules en majuscules
   Transforme tout les caracteres acccentues en caractere non accentues
*/
int filtreText(string& msg) {
	int i, j = 0;

	for (int i = 0; i < msg.size(); i++) {
		if (('A' <= msg[i]) && (msg[i] <= 'Z')) msg[j++] = msg[i];
		else if (('a' <= msg[i]) && (msg[i] <= 'z')) msg[j++] = msg[i] - 'a' + 'A';
		if (CryptoTools::CharInSet(msg[i], CryptoTools::Accent::e)) msg[j++] = 'E';
		else if (CryptoTools::CharInSet(msg[i], CryptoTools::Accent::a)) msg[j++] = 'A';
		else if (CryptoTools::CharInSet(msg[i], CryptoTools::Accent::c)) msg[j++] = 'C';
		else if (CryptoTools::CharInSet(msg[i], CryptoTools::Accent::i)) msg[j++] = 'I';
		else if (CryptoTools::CharInSet(msg[i], CryptoTools::Accent::n)) msg[j++] = 'N';
		else if (CryptoTools::CharInSet(msg[i], CryptoTools::Accent::o)) msg[j++] = 'O';
		else if (CryptoTools::CharInSet(msg[i], CryptoTools::Accent::u)) msg[j++] = 'U';
		else if (CryptoTools::CharInSet(msg[i], CryptoTools::Accent::y)) msg[j++] = 'Y';
		else if (CryptoTools::CharInSet(msg[i], CryptoTools::Accent::ae)) {msg[j++] = 'A'; msg[j++] = 'E';}
		else if (CryptoTools::CharInSet(msg[i], CryptoTools::Accent::oe)) {msg[j++] = 'O'; msg[j++] = 'E';}
	}

	return j;
}

// Calcul la frequence de chaque lettre dans le texte
void calcul_frequences(string &msg, double freq [], int nbSymboles, int pas, int debut) {
	int i;
	// Calcul du nombre d'occurences de chaque lettre
	for(i = debut; i < msg.size(); i += pas) {
		freq[msg[i] - 'A']++;
	}
        // Calcul de la frequence de chaque lettre à partir du nombre d'occurences
	for(i=0; i < nbSymboles; i++) {
		freq[i] = freq[i] / (msg.size() / pas);
	}
}

// Retourne de l'index de coincidence pour le tableau de frequence fourni en parametre
double index_coincidence(double freq [], int nbSymboles) {
	int i;
	double index = 0;
	for(i=0; i < nbSymboles; i++) {
		index += freq[i] * freq[i];
	}
	
	return index; 
}

// Codage d'un chiffre monoalphabétique par decalage
void code_mono_decalage(string& msg, int k, int nbSymboles) {
	int i;
	for(i=0; i < msg.size(); i++) {
		msg[i] = ((msg[i] - 'A' + k) % nbSymboles) + 'A';
	}
}

// Decodage d'un chiffre monoalphabetique par decalage
void decode_mono_decalage(string& msg, int k, int nbSymboles) {
	int i;
	for(i=0; i < msg.size(); i++) {
		msg[i] = ((msg[i] + 'A' - k) % nbSymboles) + 'A';
	}
}

// Calcul l'indice de coïncidence de Friedman pour tous les décalages possibles, et renvoi le decalage qui donne l'indice maximum
int decalage_ind_max (double freq_francais [], double freq_chiffre [], int nbSymboles) {
	int i, k;
	int decalage_ind_max = 0;
	double indiceMax = 0, indice = 0;

	for(k=0; k < nbSymboles; k++) {
		for(i=0; i < nbSymboles; i++) {
			indice += freq_francais[i] * freq_chiffre[(i+k) % nbSymboles];
		}
		if(indice > indiceMax) {
			indiceMax = indice;
			decalage_ind_max = k;		
		}
		indice = 0;
	}
	
	return decalage_ind_max;
}

// Codage de vigenere
void code_vigenere (string& msg, string k, int nbSymboles) {
	int i;

	for(i=0; i < msg.size(); i++) {
		msg[i] = ((msg[i] - 'A' + (k[i % k.size()] - 'A')) % nbSymboles) + 'A';
	}
} 

// Decodage d'un chiffre de vigenere
void decode_vigenere (string& msg, string k, int nbSymboles) {
	int i;
	
	for(i=0; i < msg.size(); i++) {
		msg[i] = ((msg[i] + 'A' - (k[i % k.size()] - 'A')) % nbSymboles) + 'A';
	}
} 

// methode calculant le pgcd de 2 nombres
int pgcd(int a, int b) {
	int r;

	if(b > a) {
		r = a;
		a = b;
		b = r;
	}
	while (b > 0) {
		r = a % b;
		a = b;
		b = r;
	}
	  
	return a;
}

// Test de Kasiski : Retourne la longueur suposee de la clef
int Kasiski (string& msg) {
	int taille_motifs = 4+1;  // Taille+1 des motifs que l'on recherche (diminue si resultat non satisfaisant)
	int i = 0, j, k, l = 0;
	int nbDistances = 10, distances [nbDistances];	// Distances entre 2 motifs identiques
	int longueurCle;
		
	// Recherche des motifs identiques jusqu'a obtenir au moins 3 distances
	while(l < 3) {
		taille_motifs--;
		while((i < msg.size()-(taille_motifs)) && (l < nbDistances)) {
			for(j=i+1; j < msg.size()-(taille_motifs-1); j++) {
				k = 0;
				while((msg[i+k] == msg[j+k]) && (k < 4)){
					k++;
				}
				if(k == 4) {
					distances[l] = j-i;
					l++;
				}
			}
			i++;
		}
	}
	// Calcul de la longueur de la cle (soit le pgcd des distances trouvees)
	longueurCle = pgcd(distances[0], distances[1]);
	for(i=2; i < l; i++){
		longueurCle = pgcd(longueurCle, distances[i]);
	}

	return longueurCle;
}	


int main(int argc, char* argv[]) {
	int choixCryptage = 0;
	char c;
	int i;
	string msg;
	int tailleValide;
	double freq_francais [26] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
	double freq_chiffre [26] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
	double index_coin_fr;
	int kMono = 9, kTrouvee;
	string kVigenere = "CLETEST", kVigTrouvee;
	int longueurCle;

	// Choix du cryptage a effectuer
	printf("Entrer 1 pour un cryptage par decalage, 2 pour un cryptage par Vigenere : \n");
	while( (choixCryptage != 1) && (choixCryptage != 2) ) {
		if(scanf("%d", &choixCryptage) != 1) {
			printf("Vous devez entrer 1 ou 2 : \n");
		}
		while ((c = getchar ()) != '\n' && c != EOF);
	}

	// Chargement du texte
	msg = lireDonnee (argv[1]);
	
	// filtrage des caracteres ne faisant pas parti de l'alphabet {A-Z}
	tailleValide = filtreText(msg);
	msg = msg.substr(0,tailleValide); // Troncature du msg pour ne concerver que le texte filtre (la taille du texte filtre etant plus petite que la taille du texte de base.

	// Calcul des frequences et de l'index de coincidence pour le français
	calcul_frequences(msg, freq_francais, 26, 1, 0);
	index_coin_fr = index_coincidence(freq_francais, 26);
	cout<< "Index de coincidence français : "<< index_coin_fr <<endl <<endl;
	
	msg = msg.substr(0,500); // Troncature du texte filtre aux nombre de caracteres que l'on souhaite crypter.
	cout<< "message original :"<<endl << msg <<endl <<endl;


	if(choixCryptage == 1) {
		///////////////////////////////// CODAGE MONO PAR DECALAGE ////////////////////////////////////////
		// Codage monoalphabétique par decalage
		code_mono_decalage(msg, kMono, NB_SYMBOLES);
		cout<< "codage mono decalage:"<<endl << msg <<endl <<endl;
		// Calcul de la frequences des lettres dans le chiffre
		calcul_frequences(msg, freq_chiffre, NB_SYMBOLES, 1, 0);
		// Calcul de la cle a partir de l'indice de coincidence de tout les decalages possible
		kTrouvee = decalage_ind_max(freq_francais, freq_chiffre, NB_SYMBOLES);
		cout<< "Decalage k trouve = "<< kTrouvee <<endl<<endl;
		// Decodage monoalphabétique par decalage avec la cle trouvee
		decode_mono_decalage(msg, kTrouvee, NB_SYMBOLES);
		cout<< "decodage mono decalage :"<<endl << msg <<endl <<endl;
	}
	else {
		///////////////////////////////// CODAGE DE VIGENERE ////////////////////////////////////////
		// Codage de Vigenere
		code_vigenere(msg, kVigenere, NB_SYMBOLES);
		cout<< "codage Vigenere :"<<endl << msg <<endl <<endl;
		// Calcul de la longueur de la cle avec le test de Kasiski
		longueurCle = Kasiski(msg);
		cout<< "longueur suposee de la cle : "<< longueurCle <<endl;
		// Calcul de chaque lettre de la cle grace a l'indice de Friedman 
		for(i = 0; i < longueurCle; i++) {
			calcul_frequences(msg, freq_chiffre, NB_SYMBOLES, longueurCle, i); // On calcul les frequences des lettres espacees de la longueur de la cle pour obtenir le decalage propre a chaque lettre de la cle
			kVigTrouvee.push_back(decalage_ind_max(freq_francais, freq_chiffre, NB_SYMBOLES) + 'A'); // On cherche chaque lettre de la cle en calculant le decalage pour lequel l'indice de friedman est le plus grand
		}
		cout<< "Cle trouvee : "<< kVigTrouvee <<endl<< endl;
		// Decodage de Vigenere
		decode_vigenere(msg, kVigTrouvee, NB_SYMBOLES);
		cout<< "decodage Vigenere :"<<endl << msg <<endl <<endl;
	}

	return 0;
}



















