system = npendulum
init = n2
solver = gaussseidel
integrator = verlet
dt = 0.01
tt = 500

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

save :
	mkdir -p ../examples/$(system)/$(init)_$(solver)_$(dt)_$(tt)/
	cp ./graphics/cartposition.csv ../examples/$(system)/$(init)_$(solver)_$(dt)_$(tt)/
	cp ./graphics/permaloop.html ../examples/$(system)/$(init)_$(solver)_$(dt)_$(tt)/

w : run write 

ws : run write save
