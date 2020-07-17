system = npendulum
init = n1
solver = gaussseidel
integrator = verlet
dt = 0.01
tt = 100

simfiles = main.c\
	   vector.c manifold.c\
	   init.c ./systems/$(system).c\
	   write.c\
	   $(solver).c $(integrator).c\
	   fields.c constraints.c 

run : $(simfiles)
	cc $(simfiles) -I ./include -lm

write : 
	./a.out $(init) -dt $(dt) -tt $(tt)
	@echo Writing data...
	Rscript ./data/data.R
	Rscript ./data/graphics.R
	@echo Done.

w : run write 
