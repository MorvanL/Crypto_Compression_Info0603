# partie du makefile à modifier
EXE=main
SRCS=main.cpp CTF.cpp BitStream.cpp class_mere.cpp CTV.cpp CRLE.cpp CHuffman.cpp Noeud.cpp LZW.cpp
LDLIBS= -lm
# partie à ne pas toucher
OBJS=$(SRCS:.cpp=.o)
$(EXE): depend $(OBJS)
	$(CXX) $(OBJS) $(LDLIBS) -o $@
depend:
	makedepend -Y $(SRCS) 2> /dev/null
clean:
	rm -f $(OBJS)
# DO NOT DELETE

main.o: CTF.h class_mere.h BitStream.h CTV.h CRLE.h CHuffman.h Noeud.h LZW.h
CTF.o: CTF.h class_mere.h BitStream.h
BitStream.o: BitStream.h
class_mere.o: class_mere.h BitStream.h
CTV.o: CTV.h class_mere.h BitStream.h
CRLE.o: CRLE.h class_mere.h BitStream.h
CHuffman.o: CHuffman.h class_mere.h BitStream.h Noeud.h
Noeud.o: Noeud.h
LZW.o: LZW.h class_mere.h BitStream.h
