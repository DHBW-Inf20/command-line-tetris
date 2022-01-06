ifdef includePath
    IncludeFlag = -I "$(includePath)"
endif

ifdef libraryPath
	LibraryFlag = -L "$(libraryPath)"
endif


ifndef CPPFLAGS
	CPPFLAGS = -Wall -std=c++17 $(IncludeFlag) $(LibraryFlag)
else
	CPPFLAGS = $(CPPFLAGS) $(IncludeFlag) $(LibraryFlag)
endif

ifndef CXX
	CXX = g++
endif 

all: root.exe

root.exe: root.cpp GameLogic/Input/Keylistener.cpp
	$(CXX) $(CPPFLAGS) -o root.exe GameLogic/Input/Keylistener.cpp root.cpp -lpthread
