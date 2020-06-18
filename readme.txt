The code could have trouble compiling if for some reason you have an environment variable named STOWAGE
or STOWAGE_MATAN
we use these variables to differentiate between compiling on PC vs on nova
This should not be an issue unless you like having weird environment variables

We prepared multiple test folders with travels inside ./tests/
you can run them using : simulator -travel_path ../tests/travels_1/ and so on
we assume each output folder your create is new

We use a cache mechanism to load the files for each simulation, due to the simulations starting on multiple threads
sometimes (most likely at the start of the program) a file will be loaded multiple times, we don't have the time to 
make it perfect, but as the program continues to run and the threads fall out of sync the files are loaded mostly once.

In concept we had two algorithms with different approaces yet by the end when we tested a lot of cases we found that
one is always superior and so we use a slight variation of the superior algorithm for the two algorithms.
the other algorithm is pretty interesting if you want to read about it its name is _208643270_d.
