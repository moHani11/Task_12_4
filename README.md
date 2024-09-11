## This repo shows my work in the Task 12.4 

- I have made a **c++ class** that can Implement PID to control any analog output for an arduino.   
- I have made an attribute in the class that applies an exponential smoothing Filter for the output signal to avoid overshooting, undershooting and for more stability.    
- To check the integrity of the PID class and to try it practicaly i have made a tinkercad simulation that works as follows:

> The simulation works for a single motor that we can move in a straight line forward and backward, The motor poistion along that line is printed in the serial monitor through out the whole silmulation.  
> The simulation uses the PID class i have made so it takes the **Desired position for the wheel along that line** and **contorl the speed of the motor** so it can reach its goal.

> note that the PID takes the reading of the motor speed using an encoder and changes the speed by giving an analog output to the DC motor's terminal.

## Please check the [Simulation](https://www.tinkercad.com/things/l00wzgc9zWO-task124/editel?sharecode=rvrHSY2OLCj_S2QwP4gEDvTWiI93vctvOwt6TID9x2g)
