#ifndef PID_H
#define PID_H

class PID {
public:
    /*
    * Errors
    */
    double p_error;
    double i_error;
    double d_error;
    double prev_err;

    int msg_count;
    bool tune_param ;// if true runs twiddle
    bool reset_cmd;// if true rests all variables and sends rest to sim
    //bool cte_tune;
    //const int nos_msg = 400;
    const double threshold = 2.0;
    const int nos_params = 3;
    double arr_param[3];
    double arr_dp[3];
    double total_err;
    double best_err;
    const int twiddle_run_ref = 400;//run for 200 acc err for 200
    //const int twiddle_acc_ref = 00;//run for 200 acc err for 200
    double err = 0.0;
    bool run_done;// 400 steps done
    bool param_done;//if maxima and minima done
    bool maxima_done;//+ is done
    bool minima_done;//- is done
    int param_index ;

    int twiddle_step;
    /*
    * Coefficients
    */
    double Kp;
    double Ki;
    double Kd;
    double best_Kp;
    double best_Ki;
    double best_Kd;

    /*
    * Constructor
    */
    PID();

    /*
    * Destructor.
    */
    virtual ~PID();

    /*
    * Initialize PID.
    */
    void Init(double Kp, double Ki, double Kd);

    /*
    * Update the PID error variables given cross track error.
    */
    void UpdateError(double cte);

    /*
    * Calculate the total PID error.
    */
    double TotalError();
    //FInds sum of given arr
    double SumArr(double* arr,int size);
    void run(double cte);
    void twiddle(double cte);
    void Reset();
};

#endif /* PID_H */
