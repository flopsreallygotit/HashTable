# Configure compiler

CXX ?= g++

#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

# Configure compile flags

CXXFLAGS ?= -ggdb3 -std=c++17 -O0 -Wall -Wextra 							\
			-Wmissing-declarations -Wcast-align -Wcast-qual 			   	\
			-Wchar-subscripts -Wconditionally-supported 				   	\
			-Wconversion -Wempty-body 				   						\
			-Wfloat-equal -Wformat-nonliteral -Wformat-security 		   	\
			-Wformat-signedness -Wformat=2 -Winline -Wlogical-op 		   	\
			-Wopenmp-simd -Woverloaded-virtual 		   						\
			-Wpacked -Wpointer-arith -Winit-self -Wredundant-decls		   	\
			-Wshadow -Wsign-conversion -Wsign-promo -Wstrict-null-sentinel	\
			-Wstrict-overflow=2 -Wsuggest-attribute=noreturn			   	\
			-Wsuggest-final-methods -Wsuggest-final-types				   	\
			-Wsuggest-override -Wswitch-default -Wswitch-enum -Wsync-nand  	\
			-Wundef -Wunreachable-code -Wunused -Wuseless-cast 			   	\
			-Wvariadic-macros -Wno-literal-suffix 						   	\
			-Wno-missing-field-initializers -Wno-narrowing 				   	\
			-Wno-old-style-cast -Wno-varargs -Wstack-protector -fcheck-new 	\
			-fsized-deallocation -fstack-protector -fstrict-overflow 	   	\
			-flto-odr-type-merging -fno-omit-frame-pointer -pie -fPIE 	   	\

# Configure linker flags

LINKFLAGS ?= # -lasan

# Configure program perfomance boost flags

FASTFLAGS ?= -O2 -mavx512dq

#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

# Configure directory flags

DIRFLAGS ?= -IUniversal -IList -IHashTable

# Configure sources you need to compile

SOURCES  ?= Optimizations/main.cpp Optimizations/optimizations.cpp Optimizations/optimizationUtils.cpp	\
			HashTable/hashFuncs.cpp HashTable/hashTable.cpp												\
			Universal/universalUtils.cpp Universal/textUtils.cpp										\
			List/list.cpp List/listUtils.cpp	

# Configure assember objects to link with			

ASMOBJECTS ?= Optimizations/hashFunctions.o

#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

# Configure object directory name

OBJDIR ?= ./Objects/

#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

# Pick executable name

EXECUTABLE ?= main

#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

# WARNING: Don't change values and commands below

# Making objects names from sources names

OBJECTS = $(patsubst %.cpp, $(OBJDIR)%.o, $(SOURCES)) 

# Adding directory flags to compiler flags

CXXFLAGS += $(DIRFLAGS)
CXXFLAGS += $(FASTFLAGS)

#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

.PHONY: all
all: $(ASSEMBLER) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	@echo "Making executable from objects;"
	@$(CXX) $(CXXFLAGS) $(OBJECTS) $(ASMOBJECTS) -o $@ $(LINKFLAGS)
	@echo "Done;"

$(OBJDIR)%.o: %.cpp
	@mkdir -p $(@D)
	@echo "Making object file from $<;"
	@$(CXX) -c $(CXXFLAGS) $^ -o $@

#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

.PHONY: clear
clear:
	@echo "Clearing object files and executables;";
	@rm -rf $(OBJDIR) $(EXECUTABLE)

#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
