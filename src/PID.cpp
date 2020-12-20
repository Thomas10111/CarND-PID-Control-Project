#include "PID.h"

/**
 * TODO: Complete the PID class. You may add any additional desired functions.
 */

PID::PID() {}

PID::~PID() {}

void PID::Init(double Kp_, double Ki_, double Kd_) {
  /**
   * TODO: Initialize PID coefficients (and errors, if needed)
   */
	Kp = Kp_;
 	Ki = Ki_;
  	Kd = Kd_;
  	
  	i_error = 0.0;
  	d_error = 1.0;
}

void PID::UpdateError(double cte) {
  /**
   * TODO: Update PID errors based on cte.
  steering = -tau_p * cte - tau_d * diff_cte - tau_i * int_cte
  */
  i_error = i_error + cte;
  d_error = cte - d_error;
  p_error = cte;
}

double PID::TotalError() {
  /**
   * TODO: Calculate and return the total error
   */
  //return 0.0;  // TODO: Add your total error calc here!
  double total_error = -Kp * p_error - Kd * d_error - Ki * i_error;
  return total_error;
}