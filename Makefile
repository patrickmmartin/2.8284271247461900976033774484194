CXXFLAGS =	-O2 -g -Wall -fmessage-length=0

OBJS =		2.8284271247461900976033774484194.o eight_rooty_pieces.o

LIBS =

TARGET =	2.8284271247461900976033774484194.exe

$(TARGET):	$(OBJS)
	$(CXX) -o $(TARGET) $(OBJS) $(LIBS)

all:	$(TARGET)

clean:
	rm -f $(OBJS) $(TARGET)
