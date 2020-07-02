system = npendulum
init = n1
solver = gaussseidel
integrator = verlet

run = main.c\
      vector.c manifold.c\
      init.c ./systems/$(system).c\
      write.c\
      $(solver).c $(integrator).c\
      fields.c constraints.c 

simulation : $(run)
	cc $(run) -I ./include -lm

w: simulation write

write : 
	./a.out $(init)
	@echo Writing data...
	Rscript ./data/data.R
	Rscript ./data/graphics.R
	@echo Done.

#r: simulation render

#render :
