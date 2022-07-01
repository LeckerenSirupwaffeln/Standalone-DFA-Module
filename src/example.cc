#include <iostream>
#include <limits>
#include <cmath>
#include <vector>
#include <numeric>
#include <algorithm>

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