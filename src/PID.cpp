#include "PID.h"
#include <iostream>

/**
 * TODO: Complete the PID class. You may add any additional desired functions.
 */

PID::PID() {}

PID::~PID() {}

void PID::Init(double Kp_, double Ki_, double Kd_) 
{
  /**
   * TODO: Initialize PID coefficients (and errors, if needed)
   */
  //std::cout << "Setting Kp: " << Kp << "  Ki: " << Ki << "  Kd: " << Kd << std::endl;
  Kp = Kp_;
  Ki = Ki_;
  Kd = Kd_;
  
  i_error = 0.0;
  d_error = 0.0;	//car in the middle of the lane, i.e. d_error = 0?
  
  std::cout << "init Kp: " << Kp << "  Ki: " << Ki << "  Kd: " << Kd << std::endl;
}

void PID::UpdateError(double cte) {
  /**
   * TODO: Update PID errors based on cte.
  steering = -tau_p * cte - tau_d * diff_cte - tau_i * int_cte
  */
  i_error = i_error + cte;
  d_error = cte - prev_diff;
  prev_diff = cte;
  p_error = cte;
  //std::cout<<"p_error: " << p_error <<"  d_error: " << d_error <<"  i_error: " << i_error << std::endl;
}

double PID::TotalError() {
  /**
   * TODO: Calculate and return the total error
   */
  //return 0.0;  // TODO: Add your total error calc here!
  //std::cout << "Kp: " << Kp << "  Kd: " << Kd << "  Ki: " << Ki << std::endl;
  double total_error = -Kp * p_error - Kd * d_error - Ki * i_error;
  //std::cout << "total_error: "<< total_error << std::endl;
  return total_error;
}