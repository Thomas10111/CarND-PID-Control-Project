# CarND-PID-Control-Project
Self-Driving Car Engineer Nanodegree Program
   
## Effect of the P, I, D component
P: Proportional component, error is multiplied with a constant p value   
I: Integral part, used to cope with biases or setpoints that are not equal to 0.
D: Derative part, takes the rate of change insto account by using the previous error.

### P
Pure P-controllers can reach the setpoint but are not robust to changes in the system and thus can start oscilating. The P-part usually has the biggest influence on the controller output.

### I
The I part is not of big interest interest here because the setpoint is 0 and there is no bias, like not perfectly aligned steering wheels, in the simulation.

### D
The D part can damp the system by taking the slope of the error into account.

##  Chosing initial and final hyperparameters
From past experience I know how time consuming it is to find good pid parameters, especially when the change paramter - see effect of parameter cycle is long.
The twiddle algorithm doesn't help in this case either because it needs quite good parameter to work properly. So, I searched in the study group if someone posted
parameter to start with so that the twiddle algorithm can do its work. I am curious to hear what other students think, but as far as I understand the twiddle algorithm
the car has to drive exactly the same route, e.g. one complete lap, to get comparable results. Of course the error on a curvy part of the track will be greater than
on a straight road.   




