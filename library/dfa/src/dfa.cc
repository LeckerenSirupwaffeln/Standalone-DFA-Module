#include <iostream>
#include <limits>
#include <cmath>
#include <vector>
#include <numeric>
#include <algorithm>

#include "dsp.h"
#include "dfa.h"

static float get_detrended_variance(const float arr[], const size_t N)
{
  float line_coords[N];
  dsp::generate_linear_regression_line_LSM(arr, N, line_coords);
  
  float sum = 0.0f;
  for(size_t i = 0; i < N; ++i)
  {
    sum += std::pow(arr[i] - line_coords[i], 2);
  }
  
  return std::sqrt(sum / N);
}

float dfa::get_alpha1(const int arr[], const size_t N)
{
  float integrated_deviation[N];
  dsp::integrate_deviation(arr, N, integrated_deviation);
  
  std::vector<float> mean_fluctuations;
  for(size_t i = 4; i <= N; ++i)
  {
    std::vector<float> n_window_fluctuations;
    size_t current_pos = 0;
    while((current_pos + i - 1) < N)
    {
      float interval[i];
      for(size_t j = 0; j < i; ++j)
      {
        interval[j] = integrated_deviation[current_pos + j];
      }
      n_window_fluctuations.push_back(get_detrended_variance(interval, i));
      current_pos += i;
      
    }
    float mean_fluctuation = std::accumulate(n_window_fluctuations.begin(), n_window_fluctuations.end(), 0.0f) / n_window_fluctuations.size();
    mean_fluctuations.push_back(mean_fluctuation);
  }
  return dsp::get_scale_log_log(mean_fluctuations);
}