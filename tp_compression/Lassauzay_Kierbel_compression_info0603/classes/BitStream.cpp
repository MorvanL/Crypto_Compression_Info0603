#include "BitStream.h"

#define FATAL(x) { printf("FATAL:" x " (%s)\n",__FUNCTION__); exit(-1); }

template <class T> void safe_new_array(T *&x, size_t n) {
	x = new T[n];
	if (x == NULL) FATAL("Not enough memory");
}

Bits::Stream::Stream(const size_t base_storage_size) : wPos(0), wBit(0), rPos(0), rBit(0), storage_size(base_storage_size) {
	safe_new_array(buff, storage_size);
};

Bits::Stream::~Stream() {
	delete[] buff;
}

void Bits::Stream::realloc(uint32_t new_size) {
	storage_type	*old_buff = buff;
	safe_new_array(buff, new_size);
	memcpy(buff, old_buff, storage_size*sizeof(storage_type));
	storage_size = new_size;
	delete[] old_buff;
}

void Bits::Stream::clear() { 
	memset(buff, 0, storage_size*sizeof(storage_type)); 
	wPos = wBit = rPos = rBit = 0; 
};

void Bits::Stream::write_bit(Bit b) {	// push one bit
	buff[wPos] = Bits::set<uint32_t>(buff[wPos], wBit, 1, b);
	wBit++;
	if (wBit == storage_unit_size) {
		wBit = 0;
		wPos++;
		if (wPos == storage_size) realloc(storage_size + alloc_unit_size);
	}
}

bool Bits::Stream::read_bit(Bit &b) {	// push one bit
	if ((rPos == wPos) && (rBit == wBit)) return false;
	b = Bits::get<storage_type>(buff[rPos], rBit);
	rBit++;
	if (rBit == storage_unit_size) { rBit = 0; rPos++; }
	return true;
}

void Bits::Stream::viewMSB(Byte pack, uint32_t maxbits) {
	if (maxbits) maxbits = maxbits / storage_size + (maxbits%storage_size ? 1 : 0);
	int nEltMax = (maxbits ? maxbits : wPos);	
	Byte offset = 0;
	for (int i = 0; i < nEltMax; i++) 
		offset = Bits::ViewLSB<storage_type>(buff[i], pack, 8 * sizeof(storage_type), offset);
	if (wBit != 0) offset = Bits::ViewLSB<storage_type>(buff[nEltMax], (pack != 0 ? pack : wBit), wBit, offset);
}

void Bits::Stream::viewLSB(Byte pack, uint32_t maxbits) {
	if (maxbits) maxbits = maxbits / storage_size + (maxbits%storage_size ? 1 : 0);
	int nEltMax = (maxbits ? maxbits : wPos);
	Byte offset = 0;
	if (wBit != 0) offset = Bits::ViewMSB<storage_type>(buff[nEltMax], (pack != 0 ? pack : wBit), wBit, offset);
	for (int i = nEltMax - 1; i >= 0; i--)
		offset = Bits::ViewMSB<storage_type>(buff[i], pack, 8*sizeof(storage_type), offset);
}
