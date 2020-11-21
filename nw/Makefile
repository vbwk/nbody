SYSTEM = npendulum
INIT = n2
SOLVER = gaussseidel
INTEGRATOR = verlet
DT = 0.01
TT = 100

SYSTEM_HEADERS = -I ./systems/$(SYSTEM)

SIMFILES = main.c\
	   ./systems/$(SYSTEM)/$(SYSTEM).c\
	   init.c

FLAGS = -lm

main : $(SIMFILES)
	cc $(SIMFILES) $(FLAGS) $(SYSTEM_HEADERS)
	

o :
	./a.out $(INIT) $(DT) $(TT)	

d : main o
