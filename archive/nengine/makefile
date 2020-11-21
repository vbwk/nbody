debug: main.c vector.c manifold.c init.c ./systems/npendulum.c 
	gcc main.c vector.c manifold.c init.c ./systems/npendulum.c -I ./include -lm

gauss: main.c vector.c init.c ./systems/npendulum.c gaussseidel.c verlet.c write.c fields.c constraints.c
	gcc main.c vector.c init.c ./systems/npendulum.c gaussseidel.c verlet.c write.c fields.c constraints.c -I ./include -lm
