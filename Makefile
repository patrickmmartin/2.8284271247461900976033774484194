CXXFLAGS =	-std=c++0x -O2 -g -Wall -fno-strict-aliasing -fmessage-length=0 -static-libgcc -static-libstdc++

TESTSMAIN = 2.8284271247461900976033774484194.o

DUMPMAIN = dumpruns.o

TESTSOBJS = eight_rooty_pieces.o\
			root_classes.o\
			verifications.o\
			verifications_class.o\

DUMPOBJS =

LIBS =

ifeq ($(OS),Windows_NT)
	TESTS =	2.8284271247461900976033774484194.exe
	DUMPRUNS = dumpruns.exe
else
	TESTS =	2.8284271247461900976033774484194
	DUMPRUNS = dumpruns
endif

TARGETS = $(TESTS) $(DUMPRUNS)

$(TESTS): $(TESTSMAIN) $(TESTSOBJS)
	$(CXX) -o $(TESTS) $(TESTSMAIN) $(TESTSOBJS) $(LIBS) $(CXXFLAGS)

$(DUMPRUNS): $(DUMPMAIN) $(DUMPOBJS)
	$(CXX) -o $(DUMPRUNS) $(DUMPMAIN) $(DUMPOBJS) $(LIBS) $(CXXFLAGS)



verifications_class.o : root_classes.h root_runner.h
verifications.o : eight_rooty_pieces.c  eight_rooty_pieces.h
dumpruns.o : root_classes.h root_runner.h 

all:	$(TARGETS)

clean:
	rm -f $(DUMPRUNS) $(DUMPMAIN) $(OBJS) $(TARGETS)

	
format:
ifeq ($(OS),Windows_NT)
	"c:\Program Files (x86)\LLVM\bin\clang-format.exe" -i dumpruns.cpp 2.8284271247461900976033774484194.cpp\
														  eight_rooty_pieces.h eight_rooty_pieces.cpp\
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
	./$(TESTS)

dump:
	./$(DUMPRUNS)	