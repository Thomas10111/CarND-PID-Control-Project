# CarND-PID-Control-Project
Self-Driving Car Engineer Nanodegree Program
   
## Effect of the P, I, D component
P: Proportional component, error is multiplied with a constant P value.   
I: Integral part, used to cope with biases or setpoints that are not equal to 0.
D: Derivative part, takes the rate of change into account by using the previous error.

### P
Pure P-controllers can reach the setpoint but are not robust to changes in the system and thus can easily start oscillating. The P-part usually has the biggest influence on the controller output.

### I
The I part is not of big interest here because the setpoint is 0 and there is no bias, e.g. not perfectly aligned steering wheels, in the simulation. 

### D
The D part can damp the system by taking the slope of the error into account. So, if the current error is smaller than the previous error the D part reduces the output to prevent the controller from overshooting. On the other hand, if the error gets bigger than the D part increases the output of the controller.

## Choosing initial and final hyperparameters
From experience I know how time consuming it is to find good pid parameters, especially when the time it takes to change a parameter is long. In the past we often used the method of Ziegler and Nichols to find parameters.
The twiddle algorithm doesn't help in this case either because it needs quite good parameter to work properly. So, I searched in the study group if someone posted parameter to start with so that the twiddle algorithm can do its work. I am curious to hear what other students think, but as far as I understand the twiddle algorithm the car must drive exactly the same route, e.g. one complete lap, to get comparable results. I expect the error on a curvy part of the track to be greater than on a straight road although the parameters might be better.
