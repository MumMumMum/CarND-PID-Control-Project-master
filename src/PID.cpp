#include "PID.h"
#include <iostream>
#include <cmath>
#include <limits>

using namespace std;

/*
* TODO: Complete the PID class.
*/

PID::PID() {}

PID::~PID() {}

void PID::Init(double _kp, double _ki, double _kd) {
    Kp = _kp;
    Ki = _ki;
    Kd = _kd;
    best_Kp = Kp;
    best_Ki = Ki;
    best_Kd = Kd;
    prev_err = 0.0;
    i_error = 0.0;
    msg_count = 0;
    tune_param = true;
    reset_cmd  = false;
    //cte_tune = false;
    arr_param[0] = _kp;//kp
    arr_param[1] = _ki;//ki
    arr_param[2] = _kd;//kd

    /*arr_dp[0] = 1.0;//kp
    arr_dp[1] = 1.0;//ki
    arr_dp[2] = 1.0;//kd
*/

    arr_dp[0] = 0.1;//kp
    arr_dp[1] = 0.1;//ki
    arr_dp[2] = 0.1;//kd

    total_err = 1000;
    best_err = std::numeric_limits<double>::max();
    twiddle_step = 0;
    param_index = 0;
    err = 0.0;
    run_done = false;
    param_done = false;
    maxima_done = false;
    minima_done = false;


}

void PID::run(double cte){
    reset_cmd = false;
    run_done = false;
    Kp = arr_param[0];
    Ki = arr_param[1];
    Kd = arr_param[2];
    if(msg_count > twiddle_run_ref && msg_count < 2*twiddle_run_ref){
        err+= cte;
    }
    if(msg_count > 2*twiddle_run_ref){
        total_err = err/twiddle_run_ref;
        Reset();
    }


}


void PID::Reset(){

    //minima_done = false;
    //maxima_done = false;

    msg_count = 0;
    reset_cmd = true;
    err = 0.0;
    run_done = true;
    cout<<"param index"<<param_index<<endl;
}

void PID::twiddle(double cte){

    run(cte);
    if(run_done){
        if(!maxima_done){
            arr_param[param_index] += arr_dp[param_index];
            maxima_done = true;
            run_done = false;
            Reset();
        }
        else if(maxima_done && !minima_done){
            arr_param[param_index] -= 2*arr_dp[param_index];
            minima_done = true;
            run_done = false;
            Reset();

        }
        else
        {
            arr_param[param_index] += arr_dp[param_index];
            arr_dp[param_index] *= 0.9;
            param_done = true;
            Reset();

        }

        if (abs(total_err) <= abs(best_err )) {
            best_err = total_err;
            arr_dp[param_index] *= 1.1;
            /*maxima_done = true;
            minima_done = true;*/
            param_done = true;
            best_Kp = arr_param[0];
            best_Ki = arr_param[1];
            best_Kd = arr_param[2];
            cout << "best Kp"<< best_Kp<< " best Ki "<< best_Ki<< " best Kd "<< best_Kd << endl;

        }
        else{

            arr_param[param_index] -= 2*arr_dp[param_index];
            minima_done = true;
            run_done = false;
            Reset();


        }

    }
    if(run_done && param_done){
        param_index ++ ;
        param_index = (param_index)%nos_params;
        maxima_done = false;
        minima_done = false;
    }

    if(abs(total_err) < 0.02) {
        tune_param = false;
        reset_cmd = false;
    }

   /* if(abs(SumArr(arr_dp,nos_params)) < 0.2) {
        cte_tune = false;
        reset_cmd = false;
    }*/
    /*cout <<"msg count :"<< msg_count<< " cte: "<< cte<< "  err : "<< err <<"  total_err: "
         << total_err << "  best_err: " << best_err << endl;
    cout << "Kp"<< Kp<< " Ki "<< Ki<< " Kd "<< Kd << endl;*/
}



void PID::UpdateError(double cte) {

    p_error = cte;
    d_error = cte - prev_err;
    prev_err = cte;
    i_error = i_error + cte;
    msg_count++;

    if(tune_param) {
        twiddle(cte);
        Kp = best_Kp;
        Ki = best_Ki;
        Kd = best_Kd;
        if(abs(cte) > 2.5) {
            Reset();
            Kp = best_Kp;
            Ki = best_Ki;
            Kd = best_Kd;
        }
    }


    cout <<"msg count :"<< msg_count<< " cte: "<< cte<< "  err : "<< err <<"  total_err: "
         << total_err << "  best_err: " << best_err << endl;
    cout << "Kp "<< Kp<< " Ki "<< Ki<< " Kd "<< Kd << endl;

    cout << "best Kp "<< best_Kp << " bestKi "<< best_Ki<< " best Kd "<< best_Kd << endl;


    //With inital manual kp ki kd this as the best err.
    //Now start tuning
    //and check the err  with ref to this err


    //Only when twiddle is on
   /* double errThre = SumArr(arr_dp,nos_params);

    if(tune_param && (errThre >0.02)) {
        twiddle(cte);
     }
    else  if (errThre < 0.2) {
        tune_param = false;
        msg_count = 0;
        reset_cmd = true;

    }*/
}




double PID::SumArr(double *arr, int size) {
    double sum = 0.0;
    for (int i = 0; i < size; i++) {
        sum += *(arr + i);
        //cout << "elements are:" << *(arr + i) << endl;

    }
    //std::cout << "sum is : " << sum << std::endl;
    return sum;
}


double PID::TotalError() {


}

