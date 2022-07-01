#ifndef DFA_SRC_DSP_H_
#define DFA_SRC_DSP_H_


namespace dsp {

float get_average(const int arr[], const size_t N);
void integrate_deviation(const int input[], const size_t N, float output[]);

//Linear Regression using the Least Squares Method.
//Fills output array with line coordinates where output[x] = y.
//Length of output array = length of input array.
void generate_linear_regression_line_LSM(const float input[], const size_t N, float output[]);

//Performs linear regression on an array[x] = y, but on log-log scale: x = log(x), y = log(y).
//Then returns the scale factor.
float get_scale_log_log(const std::vector<float> input);

}

#endif  // DFA_SRC_DSP_H_