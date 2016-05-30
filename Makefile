CXXFLAGS =	-std=c++0x -O2 -g -Wall -fno-strict-aliasing -fmessage-length=0 -static-libgcc -static-libstdc++

OBJS =		2.8284271247461900976033774484194.o \
			eight_rooty_pieces.o\
			root_classes.o\
			verifications.o\
			verifications_class.o\

LIBS =

ifeq ($(OS),Windows_NT)
	TARGET =	2.8284271247461900976033774484194.exe
else
	TARGET =	2.8284271247461900976033774484194
endif

$(TARGET):	$(OBJS)
	$(CXX) -o $(TARGET) $(OBJS) $(LIBS) $(CXXFLAGS)

verifications_class.o : root_classes.h  root_runner.h

all:	$(TARGET)

clean:
	rm -f $(OBJS) $(TARGET)

	
format:
ifeq ($(OS),Windows_NT)
	"c:\Program Files (x86)\LLVM\bin\clang-format.exe" -i eight_rooty_pieces.h eight_rooty_pieces.cpp\
														  verifications.cpp  verifications_class.cpp\
														  root_classes.cpp root_classes.h root_runner.h 
else
	clang-format-3.5 -i  *.h *.cpp *.hpp # was -style=Webkit
	git status
endif

restore:
	git checkout -- *.h *.hpp *.cpp
	git status


test:
	./$(TARGET)