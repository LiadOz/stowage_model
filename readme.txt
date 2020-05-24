The code could have trouble compiling if for some reason you have an environment variable named STOWAGE
we use this variable to differentiate between compiling on PC vs on nova
This should not be an issue unless you like having weird environment variables

We prepared two test folders with travels inside ./tests/
you can run them using : simulator -travel_path ../tests/travels_1/ and so on
we assume each output folder your create is new
