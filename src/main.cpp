#include <math.h>
#include <uWS/uWS.h>
#include <fstream>
#include <iostream>
#include <string>
#include "json.hpp"
#include "PID.h"
#include <vector>

// for convenience
using nlohmann::json;
using std::string;

// For converting back and forth between radians and degrees.
constexpr double pi() { return M_PI; }
double deg2rad(double x) { return x * pi() / 180; }
double rad2deg(double x) { return x * 180 / pi(); }

// Checks if the SocketIO event has JSON data.
// If there is data the JSON object in string format will be returned,
// else the empty string "" will be returned.
string hasData(string s) {
  auto found_null = s.find("null");
  auto b1 = s.find_first_of("[");
  auto b2 = s.find_last_of("]");
  if (found_null != string::npos) {
    return "";
  }
  else if (b1 != string::npos && b2 != string::npos) {
    return s.substr(b1, b2 - b1 + 1);
  }
  return "";
}

int main() {
  uWS::Hub h;

  PID pid;
  int count = 0;
  double cumm_error = 0;
  
  // twiddle parameters
  int state = 0;  
  std::vector<double> p{0.225, 0.0004, 4.0};
  std::vector<double> dp{0.1, 0.0001, 0.1};
  unsigned int i = 0;
  double best_err = 99999.0;
  
  //write to file
  std::freopen( "output.txt", "w", stdout );
  
  /**
   * TODO: Initialize the pid variable.
   */
  pid.Init(p[0],p[1],p[2]);
  
  
  h.onMessage([&pid, &count, &cumm_error, &state, &dp, &p, &i, &best_err](uWS::WebSocket<uWS::SERVER> ws, char *data, size_t length, 
                     uWS::OpCode opCode) {
    // "42" at the start of the message means there's a websocket message event.
    // The 4 signifies a websocket message
    // The 2 signifies a websocket event
    if (length && length > 2 && data[0] == '4' && data[1] == '2') 
    {
      auto s = hasData(string(data).substr(0, length));

      if (s != "") 
      {
        auto j = json::parse(s);

        string event = j[0].get<string>();

        if (event == "telemetry") 
        {
          // j[1] is the data JSON object
          double cte = std::stod(j[1]["cte"].get<string>());
          double speed = std::stod(j[1]["speed"].get<string>());
          double angle = std::stod(j[1]["steering_angle"].get<string>());
          double steer_value;
          /**
           * TODO: Calculate steering value here, remember the steering value is
           *   [-1, 1].
           * NOTE: Feel free to play around with the throttle and speed.
           *   Maybe use another PID controller to control the speed!
           */
          if(speed > 6.0)
          {
            pid.UpdateError(cte);
          }
          
          steer_value = pid.TotalError();
          if(steer_value > 1.0) steer_value = 1.0;
          if(steer_value < -1.0) steer_value = -1.0;
         
          if(count > 100)
          {
            cumm_error =+ cte * cte;
            
            if(count > 200)
            {
              std::cout << "cumm_error: " << cumm_error << "  state: " << state << std::endl;
              for(double &p: p) std::cout << p << ", ";
              std::cout << std::endl;
              
              // evaluate current parameters
              if(state == 0)
              {
                p[i] += dp[i];
                state = 1;
                count = 0;
                pid.Init(p[0], p[1], p[2]);
              }
              else if(state == 1)
              {
                if(cumm_error < best_err)
                {
                  best_err = cumm_error;
                  dp[i] *= 1.1;
                  state = 0;   // improved
                  i += 1;
                  if(i == p.size())
                  {
                    i = 0;
                    //return 1;
                   }
                   else
                   {
                    //return 2;
                     ;
                   }
                 }
                 else
                 {
                   p[i] -= 2 * dp[i];
                   pid.Init(p[0], p[1], p[2]);
                   state = 2;
                   count = 0;
                 }
               }
               else if(state ==2)
               {
                 if(cumm_error < best_err)
                 {
                   best_err = cumm_error;
                   dp[i] *= 1.1;
                   state = 0;   // improved
                   i += 1;
                   if(i == p.size())
                   {
                     i = 0;
                     //return 1;
                   }
                   else
                   {
                     ;//return 2;    // start again without trying p
                   }
                 }
               }
               else
               {
                 p[i] += dp[i];
                 pid.Init(p[0], p[1], p[2]);
                 dp[i] *= 0.9;
                 state = 0;
                 i += 1;
                 if(i == p.size())
                 {
                    i = 0;
                    //return 1;
                 }
                 else
                 {
                    ;//return 2; // start again without trying p
                 }
               }
            }
            std::cout << "count: " << count << "  state: " << state << std::endl;
            for(double &p: p) std::cout << p << ", ";
            std::cout << std::endl;
          }    
          
          
          // DEBUG
          std::cout << "count: " << count << "  CTE: " << cte << " Steering Value: " << steer_value 
                    << "  speed: " << speed << std::endl;

         count+=1;
          
          json msgJson;
          msgJson["steering_angle"] = steer_value;
          msgJson["throttle"] = 0.3;
          auto msg = "42[\"steer\"," + msgJson.dump() + "]";
          std::cout << msg << std::endl;
          ws.send(msg.data(), msg.length(), uWS::OpCode::TEXT);          
        }  // end "telemetry" if
      } else {
        // Manual driving
        string msg = "42[\"manual\",{}]";
        ws.send(msg.data(), msg.length(), uWS::OpCode::TEXT);
      }
    }  // end websocket message if
  }); // end h.onMessage

  h.onConnection([&h](uWS::WebSocket<uWS::SERVER> ws, uWS::HttpRequest req) {
    std::cout << "Connected!!!" << std::endl;
  });

  h.onDisconnection([&h](uWS::WebSocket<uWS::SERVER> ws, int code, 
                         char *message, size_t length) {
    ws.close();
    std::cout << "Disconnected" << std::endl;
  });

  int port = 4567;
  if (h.listen(port)) {
    std::cout << "Listening to port " << port << std::endl;
  } else {
    std::cerr << "Failed to listen to port" << std::endl;
    return -1;
  }
  
  h.run();
}