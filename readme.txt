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
Instructions folder: (the algorithm will make it's outputs there)
	- [integer] file: the output instructions for the i-th port in the route (files are in the suggested format)
portsCargo folder: data for the cargo for each port (files are in the suggested format)

When an error occurs it is logged in the travel folder under the file simulation.errors.
we have a title stating the part of the program in which errors may occur (it will display even if no errors had occured)

results are printed in a results.txt file in the root folder.

we assume there are the relevant folders in each travel: Instructions and portsCargo.

You can see an example of the code in directories Simulation/example_input_1 and Simulation/example_input_2.
In each input file lines beginning with "#" are comment lines and are not parsed.
Whenever there is an error in the input of the ship plan we assume that error is critical and so the 
program will stop running.
