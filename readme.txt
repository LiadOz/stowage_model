There are currently two algorithms: Brute Algorithm and Reject Algorithm.
Brute Algorithm - unloads all the containers inside and then reloads all the containers
that needs to go further, then it loads all the containers it can from the port.
Reject Algorithm - loads to the ship only containers that are supposed to go to the next 
port in its route, when it reaches a port it unloads all it's containers.

When an error ouccurs it is handled and a proper error is printed to the screen.

You can see an example of the code in directories example_input_1 and example_input_2.
In each input file lines beginning with "#" are comment lines and are not parsed.
Whenever there is an error in the input of the ship plan we assume that error is critical and so the 
program will stop running.
