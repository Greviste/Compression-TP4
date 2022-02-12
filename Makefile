CXX=g++
CXXFLAGS=-std=c++2a
CC=$(CXX)
TARGETS=huffman ondelette psnr rebuild rle unrle
OBJECTS=$(patsubst %,%.o,$(TARGETS))

all: $(TARGETS)

$(OBJECTS): common.h image_ppm.h

clean:
	rm $(TARGETS) $(OBJECTS)
