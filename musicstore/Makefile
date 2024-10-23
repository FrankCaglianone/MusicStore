CXXFLAGS = -Wall -g

all: ms

OBJECTS = musicstore.o ms.o

ms: $(OBJECTS)
	$(CXX) $(CXXFLAGS) $(LDFLAGS) $(OBJECTS) -o $@

musicstore.o: musicstore.h
ms.o: musicstore.h

clean:
	rm -f $(OBJECTS)

veryclean: clean
	rm -f ms
