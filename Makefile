CPP = g++
STD = -std=c++17
OPTIMIZER = -O3
WFLAGS = -Wall -W
OPENMP = -fopenmp
PTHREAD = -pthread
FSWITCH = -flto -ffunction-sections -fdata-sections
###################################################
## 1. Don't use LEVEL 2 or 1 huge amount of logs will
## be generated.
## 2. After changing this always do "make clean"
DBGFLAG = D_LEVEL3
###################################################
RM  = rm -fr
EXEC = a.out

CRDIR = createdir
DBGDIR = debug
INCLUDEDIRS = include src $(DBGDIR)
SRCDIR = src
OBJDIR = build
FLAGS := $(STD) $(OPTIMIZER) $(WFLAGS) $(addprefix -D, $(DBGFLAG)) $(OPENMP) $(PTHREAD)
INCLUDES = $(addprefix -I, $(INCLUDEDIRS))

SOURCES = timer.o run_info.o \
		  mult_args.o mat_mult.o \
		  gauss_elim_args.o gauss_elim.o \
		  mat_inv_ret.o mat_inv_args.o mat_inv.o \

MAIN = test.o global.o function.o main.o \

OBJECTS = \
	 $(addprefix $(OBJDIR)/$(SRCDIR)/, $(SOURCES)) \
	 $(addprefix $(OBJDIR)/, $(MAIN)) \

all: $(OBJECTS) compile touch

$(OBJDIR)/$(SRCDIR)/%.o: $(SRCDIR)/%.cpp | $(CRDIR)/$(OBJDIR)/$(SRCDIR)
					 $(CPP) $(FLAGS) $(INCLUDES) -c $< -o $@
$(OBJDIR)/%.o: %.cpp | $(CRDIR)/$(OBJDIR)
					 $(CPP) $(FLAGS) $(INCLUDES) -c $< -o $@
$(CRDIR)/%:
					 mkdir -p $*
run: | all
					 ./$(EXEC)
clean: 
					 $(RM) $(OBJDIR) $(EXEC) $(PROF_EXEC)
compile:
					 $(CPP) $(FLAGS) $(INCLUDES) $(OBJECTS) -o $(EXEC)
touch:
					 @echo " "
					 @echo "Compilation done successfully..................."
					 @echo " "