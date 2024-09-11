#include <iostream>
#include <chrono> 
#include <thread> 
#include <algorithm>

using namespace std;
using namespace std::chrono;


class general_PID{

    private:
        double Kp=0.0, Ki=0.0, Kd = 0.0;
        int MAX_Integral = 10000, MAX_Diffrential = 100;
        double sum_errors = 0.0, last_error = 0.0, Desired_value = 0.0;
        double feedback = 0.0, lastFeedback = 0.0;
        double minOut = 0 ,maxOut = 255; 

    public:

        void set_coeffs(double kp, double ki, double kd){
            Kp = kp;    Ki = ki;    Kd =kd;
        }
        
        void set_max_integral(int max_integral){MAX_Integral = max_integral; }

        void set_max_diff(int max_diff){MAX_Diffrential = max_diff; }

        void set_desired_output(double d) {Desired_value = d; last_error = d;}

        void set_output_range(double min, double max){
            minOut = min; maxOut = max;
        }
        
        void RESET(){
        Kp=0.0; Ki=0.0; Kd = 0.0;
        MAX_Integral = 10000; MAX_Diffrential = 1000;
        sum_errors = 0.0; last_error = 0.0; Desired_value = 0.0;
        feedback = 0.0; lastFeedback = 0.0;
        minOut = 0; maxOut = 255;
        }

        double apply_expon_fitler(float alpha){
            feedback = alpha*lastFeedback + (1-alpha)*feedback;
            return feedback;
        }

        double calculate_diff(double err, double time){
            if (time < 0.00001) return 0;

            double diff =  (err - last_error)/time;
            if (diff > MAX_Diffrential) diff = MAX_Diffrential;
            else if (diff < -MAX_Diffrential) diff = -MAX_Diffrential;
            return diff;
        }

        double calculate_integ(int err){
            sum_errors += err;
            if (sum_errors > MAX_Integral) sum_errors = MAX_Integral;
            else if (sum_errors < -MAX_Integral) sum_errors = -MAX_Integral;            
            
            return sum_errors;
        }
        
        double Iterate(double reading, double time){
            lastFeedback = feedback;
            
            double error = (Desired_value - reading);
            double diff = calculate_diff(error, time);
            double integ = calculate_integ(error);

            feedback = Kp*error +  Kd*diff +Ki*integ ;
            // cout <<"error: " << error << endl;
            // cout <<"diffrential : " << diff << endl;
            // cout <<"integral: " << integ << endl;
            
            last_error = error;

            if (feedback > maxOut) feedback = maxOut;
            if (feedback < minOut) feedback = minOut;

            return feedback;
        }
        
        general_PID(){};
        general_PID(double kp, double ki, double kd){
            set_coeffs(kp, ki, kd);
        };
        general_PID(double kp, double ki, double kd, double Desired_v){
            set_coeffs(kp, ki, kd);
            set_desired_output(Desired_v);
        };
        general_PID(double kp, double ki, double kd, double Desired_v, int max_integ, int max_d){
            set_coeffs(kp, ki, kd);
            set_max_integral(max_integ);
            set_max_diff(max_d);
            set_desired_output(Desired_v);
        };

        ~general_PID(){
        }
};

int main() {
    return 0;
}