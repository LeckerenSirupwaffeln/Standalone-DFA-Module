#include <iostream>
#include <limits>
#include <cmath>
#include <vector>
#include <numeric>
#include <algorithm>

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

namespace dsp {
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
    
}

namespace dfa {
    float get_detrended_variance(const float arr[], const size_t N)
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
  
  float get_alpha1(const int arr[], const size_t N)
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
}

int main()
{
    //dsp::test_get_average();
    //dsp::test_integrate_deviation();
    //dsp::test_generate_linear_regression_line_LSM();
    
    constexpr size_t N = 300;
    const int test_array[N] = {1023,1047,1094,1078,1055,1070,1102,1062,1070,1110,1078,1101,1071,1078,1062,1102,1078,1047,1070,1055,1031,1063,1047,1015,1078,1063,1047,1078,1078,1062,1079,1062,1063,1054,1063,1086,1039,1070,1039,1031,1071,1023,1039,1086,1070,1071,1086,1078,1094,1093,1063,1054,1079,1070,1062,1079,1039,1078,1054,1063,1094,1070,1055,1093,1047,1071,1086,1085,1102,1109,1055,1109,1133,1094,1102,1125,1078,1093,1071,1054,1102,1055,1101,1055,1047,1039,984,946,961,851,820,782,789,1211,1047,1093,1180,1148,1141,1125,1047,1093,1094,1102,1054,1118,1078,1070,1117,1055,1125,1078,1094,1078,1125,1117,1055,1125,1093,1133,1086,1078,1110,1148,1125,1110,1070,1117,1078,1094,1039,1086,1023,1063,1062,1016,1070,1047,1078,1094,1094,1054,1110,1117,1117,1117,1086,1094,1063,1093,1078,1102,1078,1101,1102,1055,1093,1133,1102,1109,1125,1156,1125,1141,1141,1109,1141,1101,1070,1110,1062,1086,1039,1094,1063,1086,1070,1062,1078,1102,1070,1118,1078,1070,1047,1086,1047,1070,1086,1062,1039,1102,1086,1062,1102,1078,1110,1070,1117,1094,1125,1117,1109,1055,1055,1078,1047,1039,1015,1055,1047,1047,1070,1094,1078,1094,1094,1086,1054,1055,1062,1032,1086,1046,1055,1063,1047,984,914,898,883,930,875,851,907,922,914,1125,1187,1070,1110,1078,1047,1109,1031,1063,1062,1016,1070,1039,1024,1039,1031,1016,1055,1031,1008,1062,1031,1086,1078,1125,1109,1164,1125,1008,1196,1109,1086,1133,1117,1125,1101,1071,1133,1085,1063,1047,1086,1062,1055,1117,1117,1118,1085,1141,1094,1094,1125,1093,1102,1039,1109,1086,1047,1063,1062,1070,1125,1110};
    float alpha1 = dfa::get_alpha1(test_array, N);
    printf("alpha1 = %f\n", alpha1);
    
    return 0;
}