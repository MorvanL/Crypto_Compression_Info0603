#ifndef _BITSTREAM
#define _BITSTREAM
#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
// #include <cstdint>

typedef signed char int8_t;
typedef unsigned char uint8_t;
typedef short int int16_t;
typedef unsigned short uint16_t;
typedef int	int32_t;
typedef unsigned int uint32_t;

namespace Bits {
	typedef unsigned char Byte;
	typedef unsigned char Bit;

	/// template pour manipulation des bits
	/// création d'un masque contenant les bits de n à n+len-1 à 1.
	template <typename T> T mask(Byte n, Byte len) { return (~((~0) << len)) << n; };
	/// retourne le mot dans lequel on a placé à la position pos dans x les len LSBs de y
	template <typename T> T set(T x, Byte pos, Byte len, T y) { return (x & (~mask<T>(pos, len))) | ((y << pos) & mask<T>(pos, len)); }
	/// retourne le bit pos de x
	template <typename T> Byte get(T x, Byte pos) { return (Byte)(x >> pos) & 0x01; }
	/// retourne le numéro du bit le plus signification dans x
	template <typename T> Byte MSB(T x) { Byte k = 0; while ((x >>= 1) != 0) k++; return k + 1; }

	/// template permettant d'afficher en binaire le contenu d'un type T, ordre LSB->MSB
	template <typename T> Byte ViewLSB(T x, Byte pack = 0, Byte maxbits = 0xff, Byte offset=0) {
		const int			nbits = std::min<int>(8 * sizeof(T), maxbits);
		for (int i = 0; i < nbits; i++) {
			if ((pack) && ((i + offset) % pack == 0)) printf(" ");
			printf("%c", (x & 0x01 ? '1' : '0'));			
			x >>= 1;
		}
		return (pack ? (nbits + offset) % pack : 0);
	}

	/// template permettant d'afficher en binaire le contenu d'un type T, ordre MSB->LSB
	template <typename T> Byte ViewMSB(T x, Byte pack = 0, Byte maxbits = 0xff, Byte offset = 0) {
		const int			nbits = std::min<int>(8 * sizeof(T), maxbits);
		for (int i = nbits-1 ; i >= 0; i--) {
			printf("%c", (get(x,i) ? '1' : '0'));
			if ((pack) && ((nbits-1 - i + offset) % pack == pack - 1)) printf(" ");
		}
		return (pack ? (nbits + offset) % pack : 0);
	}

	/// template permettant d'afficher en binaire le contenu d'un type T, défaut
	template <typename T> Byte View(T x, Byte pack = 0, Byte maxbits = 0xff, Byte offset = 0) { 
		return ViewMSB<T>(x, pack, maxbits, offset); 
	};

	/// class Bits::Block
	/// classe permettant de définir un paquet de bits de 1 à 32 bits non multiple d'un octet 
	/// les bits valides doivent être stockés dans les LSBs.
	template <typename T> class Block {
	protected:
		T		_bits;		// type utilisé pour stocker les bits (typiquement uint8_t, uint16_t, uint32_t) 
		Byte	_valid;		// nombre de bits valides dans T
	public:
		// static_assert(sizeof(T) <= 4, "la taille de stockage d'un Bits::Block est limitée à 32bits");
		inline void clear() { memset(&_bits, 0, sizeof(T)); };											///< efface les bits									
		inline void set(T bits_to_store) { memcpy(&_bits, &bits_to_store, sizeof(T)); };				///< stocke sans modifier le nombre de bits valides
		inline void set(T bits_to_store, Byte valid_bits) { set(bits_to_store); _valid = valid_bits; };	///< stocke et fixe le nombre de bits valides
		inline Block(Byte valid_bits) : _valid(valid_bits) { clear(); };								///< constructeur (fixant le nombre de bits valide)
		inline Block(T bits_to_store, Byte valid_bits) { set(bits_to_store, valid_bits); };				///< constructeur valeur + valide
		inline void view(Byte pack = 0)	{ Bits::View<T>(_bits, pack, _valid); };						///< affichage du contenu du Bits::Block
		inline T get() { return _bits; };																///< retourne le contenu du Bits::Block
		inline Byte valid() { return _valid; };															///< retourne le nombre de bits valides
		friend class Stream;
	};

	/// class Bits::Stream
	/// classe de gestions d'entrée/sortie de bits
	/// Endians proof : à vérifier sur les non-x86 en permutant éventuellement l'ordre de reconstruction des bits
	class Stream {
	protected:
		typedef uint32_t	storage_type;
		storage_type		*buff;
		uint32_t			wPos, wBit;	
		uint32_t			rPos, rBit;	
		uint32_t			storage_size;
		static const uint32_t	storage_unit_size = uint32_t(8 * sizeof(storage_type));
		static const uint32_t	alloc_unit_size = uint32_t(1024);
		void realloc(uint32_t new_size);
	public:
		Stream(const size_t base_storage_size = alloc_unit_size);
		~Stream();
		/// affichage du stream
		void viewLSB(Byte pack = 0, uint32_t maxbits = 0);
		void viewMSB(Byte pack = 0, uint32_t maxbits = 0);
		inline void view(Byte pack = 0, uint32_t maxbits = 0) { viewMSB(pack, maxbits); }
		void clear();
		/// écriture/lecture d'un bit
		void write_bit(Bit b);
		bool read_bit(Bit &b);
		/// écriture/lecture d'un paquet partiel de bits
		template <typename T> void write_bits(const Bits::Block<T> &bitblock) {
			for (int i = bitblock._valid - 1; i >= 0; i--) write_bit(Bits::get<T>(bitblock._bits, i));
		};
		template <typename T> Byte read_bits(Bits::Block<T> &bitblock)	{
			Byte	bit, count = 0;
			bitblock._bits = 0;
			for (int i = bitblock._valid - 1; i >= 0; i--) {
				if (read_bit(bit)) {
					bitblock._bits = Bits::set<T>(bitblock._bits, i, 1, bit);
					count++;
				}
			}
			return count;
		};
		/// écriture/lecture d'un bloc de bits défini par son type
		template <typename T> void write(const T &data) {
			Bits::Block<T>	bitblock(data, 8 * sizeof(T));
			write_bits(bitblock);
		};
		template <typename T> void read(T &data) {
			Bits::Block<T>	bitblock(8 * sizeof(T));
			read_bits(bitblock);
			data = bitblock.get();
		};
		/// autres fonctions utiles
		inline void status() { printf("status: Write=%d/%d Read=%d/%d\n", wPos, wBit, rPos, rBit); }	///< points de lecture
		inline void read_reset() { rPos = rBit = 0; }													///< remise à zéro du pointeur de lecture
		inline void reset() { rPos = rBit = wPos = wBit = 0; }											///< remise à zéro des pointeurs de lecture et d'écriture
		inline storage_type		*get_data() { return buff; }											///< retour du pointeur sur le buffer de données
		inline uint32_t			get_storage_size() { return storage_size; }								///< taille allouée pour le buffer
		inline uint32_t			get_size() { return wPos + (wBit ? 1 : 0); }							///< taille actuellement écrite dans le stream
		inline uint32_t			get_WBit() { return wBit; }		// nombre de bits actuellement écrit dans le dernier entier du stream
		inline bool				end_of_stream() { return (rPos == wPos) && (rBit == wBit); }			///< vrai si le pointeur de lecture a atteint la fin des données écrites
		/// pour permettre des spécialisations d'affichage ou de lecture
		template <typename T> void specialized_view(T &t);												///< template a implémenter pour afficher les données écrites
		template <typename T> void specialized_read(T &t);												///< template a implémenter pour lire les données écrites
	};
}


#endif

