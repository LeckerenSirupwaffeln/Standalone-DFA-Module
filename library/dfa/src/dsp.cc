#include <iostream>
#include <limits>
#include <cmath>
#include <vector>
#include <numeric>
#include <algorithm>

#include "dsp.h"

namespace dsp {
	float get_average(const int arr[], const size_t N)
	{
		float tmp = 0.0f;
		for(size_t i = 0; i < N; ++i)
		{
			tmp += arr[i];
		}
		return (tmp / N);
	}
	
	void integrate_deviation(const int input[], const size_t N, float output[])
	{
		float average = dsp::get_average(input, N);
		output[0] = input[0] - average;
		for(size_t i = 1; i < N; ++i)
		{
			output[i] = input[i] - average + output[i - 1];
		}
		return;
	}
	
	//Linear Regression using the Least Squares Method.
	//Fills output array with line coordinates where output[x] = y.
	//Length of output array = length of input array.
	void generate_linear_regression_line_LSM(const float input[], const size_t N, float output[])
	{
		if (N == 1)
		{
			output[0] = input[0];
			return;
		}
		
		float sum_x = 0.0f;
		float sum_y = 0.0f;
		float sum_xy = 0.0f;
		float sum_x_squared = 0.0f;
		for(size_t i = 0; i < N; ++i)
		{
			const float x = i + 1;
			const float y = input[i];
			sum_x += x;
			sum_y += y;
			sum_xy += x * y;
			sum_x_squared += std::pow(x, 2);
		}
		
		//y = m * x + b
		const float m = ( (N * sum_xy) - (sum_x * sum_y) ) / ( (N * sum_x_squared) - (std::pow(sum_x, 2)) );
		const float b = (sum_y - (m * sum_x)) / N;
		
		for(size_t i = 1; i <= N; ++i)
		{
			//y = m * x + b, where output[x] = y
			output[i - 1] = m * i + b;
		}
		return;
	}
	
	//Performs linear regression on an array[x] = y, but on log-log scale: x = log(x), y = log(y).
	//Then returns the scale factor.
	float get_scale_log_log(const std::vector<float> input)
	{
	    const auto N = input.size();
		float sum_x = 0.0f;
		float sum_y = 0.0f;
		float sum_xy = 0.0f;
		float sum_x_squared = 0.0f;
		for(size_t i = 0; i < N; ++i)
		{
		    //printf("variance[%d] = %f\n", i, input[i]);
		    //const float x = i + 1;
			const float x = std::log10(static_cast<float>(i + 1));
			//const float y = input[i];
		    const float y = std::log10(input[i]);
			
			sum_x += x;
			sum_y += y;
			sum_xy += x * y;
			sum_x_squared += std::pow(x, 2);
		}
		
		//y = m * x + b
		const float m = ( (N * sum_xy) - (sum_x * sum_y) ) / ( (N * sum_x_squared) - (std::pow(sum_x, 2)) );
		//const float b = (sum_y - (m * sum_x)) / N;
		return m;
	}
}

