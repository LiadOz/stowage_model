There are currently two algorithms: Brute Algorithm and Reject Algorithm.
Brute Algorithm - unloads all the containers inside and then reloads all the containers
that needs to go further, then it loads all the containers it can from the port.
Reject Algorithm - loads to the ship only containers that are supposed to go to the next 
port in its route, when it reaches a port it unloads all it's containers.

new Algorithms must implement the base Algorithm class.

algorithms are loaded in the main function - declare new ones there and add new simulations instances with the new algorithm in the loop.

in the root folder of the program there msut be a folder named Simulation.
in the Simulation folder, you may have folders for every "travel" (as defined in the pdf), named however you want.
in each travel folder, we have the following:
Instructions folder: (the algorithm will make its outputs there)
	- [integer] file: the output instructions for the i-th port in the route
portsCargo folder: data for the cargo for each port 
	-[portID]_[integer].cargo_data: the cargo file
ports: a file containing the ports for the shiproute
sample.plan: the plan of the ship. Whenever there is an error in the input of the ship plan,
we assume that error is critical and so the program will stop running.
results.txt: the results of the travel 
simulation.errors: the errors that occured in the travel,
we have a title stating the part of the program in which errors may occur (it will display even if no errors had occured)

we assume there are the relevant folders in each travel: Instructions and portsCargo.
we used similar formats to the suggested ones (not always the same), you can check our files to see the format we've used.

In each input file lines beginning with "#" are comment lines and are not parsed.

