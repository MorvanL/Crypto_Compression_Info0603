# partie du makefile à modifier
EXE=main
SRCS= main.cpp
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

main.o: CryptoTools.h
