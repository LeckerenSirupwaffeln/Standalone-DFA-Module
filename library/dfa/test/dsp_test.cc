#include <iostream>
#include <limits>
#include <cmath>
#include <vector>
#include <numeric>
#include <algorithm>

static bool AreEqual(float f1, float f2) 
{ 
  return (std::fabs(f1 - f2) <= std::numeric_limits<float>::epsilon() * std::fmax(std::fabs(f1), std::fabs(f2)));
}

void test_get_average()
{
  constexpr size_t N = 5;
	constexpr int test_arr[N] = {19, 25, 39, 2, 10};
	constexpr float factual_average = 19.0f;
	
	const float average = dsp::get_average(test_arr, N);
	if (!AreEqual(average, factual_average)) 
	{
		printf("get_average() test: %f not equal to %f\n", average, factual_average);
		exit(-1);
	}
	printf("dsp::get_average() test succeeded.\n");
	return;
}

void test_integrate_deviation()
{
	constexpr size_t N = 5;
	constexpr int test_input[N] = {19, 25, 39, 2, 10};
	constexpr float factual_output[N] = {0, 6, 26, 9, 0};
	
	float output[N];
	dsp::integrate_deviation(test_input, N, output);
	for(size_t i = 0; i < N; ++i)
	{
		if(!AreEqual(output[i], factual_output[i])) 
		{
			printf("integrate_deviation() test: %f not equal to %f\n", output[i], factual_output[i]);
			exit(-1);
		}
	}
	printf("dsp::integrate_deviation() test succeeded.\n");
	return;
}

void test_generate_linear_regression_line_LSM()
{
	constexpr size_t N = 7;
	constexpr float test_input[N] = {1.5f, 3.8f, 6.7f, 9.0f, 11.2f, 13.6f, 16.0f};
	constexpr float factual_output[N] = {1.585719f, 4.000003f, 6.414288f, 8.8285718f, 11.242855f, 13.657140f, 16.071424f};
	
	float output[N];
	dsp::generate_linear_regression_line_LSM(test_input, N, output);
	for(size_t i = 0; i < N; ++i)
	{
		if(!AreEqual(output[i], factual_output[i])) 
		{
			printf("generate_linear_regression_line_LSM() test: %f not equal to %f\n", output[i], factual_output[i]);
			exit(-1);
		}
	}
	printf("dsp::generate_linear_regression_line_LSM() test succeeded.\n");
}