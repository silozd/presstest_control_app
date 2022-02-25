#include "pressapp.h"

u32 PressApp::IIR_Filter(u32* raw_signal,u8 filter_coefficient){
    static u32 running_average[32];
    static u32 last_output[32];
    u32 processed_value;
    u32 iir_output;
    u8 j;

    if(filter_coefficient < 1) filter_coefficient = 1;
    if(filter_coefficient > 32) filter_coefficient = 32;

    running_average[filter_coefficient-1] = *raw_signal;
    processed_value = *raw_signal;
    for (j = 0; j < (filter_coefficient-1); j++){
        processed_value += running_average[j];
        running_average[j] = running_average[j+1];
    }
    processed_value = (processed_value)/(filter_coefficient);

    last_output[filter_coefficient-1] = processed_value;
    iir_output = processed_value;
    for (j = 0; j < filter_coefficient-1; j++){
        iir_output += last_output[j];
        last_output[j] = last_output[j+1];
    }
    iir_output = (iir_output)/(filter_coefficient);

    return iir_output;
}
u32 PressApp::FIR_Filter(u32* raw_signal,u8 filter_coefficient){
    static u32 running_average[32];
    u32 processed_value;
    u8 j;

    if(filter_coefficient < 1) filter_coefficient = 1;
    if(filter_coefficient > 32) filter_coefficient = 32;

    running_average[filter_coefficient-1] = *raw_signal;
    processed_value = *raw_signal;
    for (j = 0; j < (filter_coefficient-1); j++){
        processed_value += running_average[j];
        running_average[j] = running_average[j+1];
    }
    processed_value = (processed_value)/(filter_coefficient);

    return processed_value;
}
u32 PressApp::BIQUAD_Filter(u32* raw_signal,u8 filter_coefficient){
    static u32 running_average[32];
    static u32 last_output[32];
    u32 processed_value;
    u32 iir_output;
    u8 j;
    double biquad_total = 0;

    if(filter_coefficient < 1) filter_coefficient = 1;
    if(filter_coefficient > 32) filter_coefficient = 32;

    running_average[filter_coefficient-1] = *raw_signal;
    processed_value = *raw_signal;
    biquad_total = *raw_signal;
    for (j = 0; j < (filter_coefficient-1); j++){
        biquad_total += running_average[j];
        processed_value += running_average[j];
        running_average[j] = running_average[j+1];
    }
    processed_value = (processed_value)/(filter_coefficient);

    last_output[filter_coefficient-1] = processed_value;
    iir_output = processed_value;
    biquad_total += processed_value;

    for (j = 0; j < filter_coefficient-1; j++){
        biquad_total += last_output[j];
        iir_output += last_output[j];
        last_output[j] = last_output[j+1];
    }
    iir_output = (iir_output)/(filter_coefficient);
    biquad_total = (1.0*biquad_total)/(2.0*filter_coefficient);

    return (u32)biquad_total;
}
u32 PressApp::BIQUAD_Filter_1(u32* raw_signal,u8 filter_coefficient){
    static u32 running_average[32];
    static u32 last_output[32];
    u32 processed_value;
    u32 iir_output;
    u8 j;
    double biquad_total = 0;

    if(filter_coefficient < 1) filter_coefficient = 1;
    if(filter_coefficient > 32) filter_coefficient = 32;

    running_average[filter_coefficient-1] = *raw_signal;
    processed_value = *raw_signal;
    biquad_total = *raw_signal;
    for (j = 0; j < (filter_coefficient-1); j++){
        biquad_total += running_average[j];
        processed_value += running_average[j];
        running_average[j] = running_average[j+1];
    }
    processed_value = (processed_value)/(filter_coefficient);

    last_output[filter_coefficient-1] = processed_value;
    iir_output = processed_value;
    biquad_total += processed_value;

    for (j = 0; j < filter_coefficient-1; j++){
        biquad_total += last_output[j];
        iir_output += last_output[j];
        last_output[j] = last_output[j+1];
    }
    iir_output = (iir_output)/(filter_coefficient);
    biquad_total = (1.0*biquad_total)/(2.0*filter_coefficient);

    return (u32)biquad_total;
}
double aux_thread::IIR_Filter_double_pace_rate(double* raw_signal){
    static double running_average[65];
    static double last_output[65];
    double processed_value = *raw_signal;
    double iir_output;
    u8 j;
    u8 filter_coefficient = 32;

    running_average[filter_coefficient-1] = *raw_signal;
    for (j = 0; j < (filter_coefficient-1); j++){
        processed_value += running_average[j];
        running_average[j] = running_average[j+1];
    }
    processed_value = processed_value/filter_coefficient;

    last_output[filter_coefficient-1] = processed_value;
    iir_output = processed_value;
    for (j = 0; j < filter_coefficient-1; j++){
        iir_output += last_output[j];
        last_output[j] = last_output[j+1];
    }
    iir_output = (iir_output)/(filter_coefficient);

    return iir_output;
}
float aux_thread::IIR_Filter_double_load(float* raw_signal){
    static float running_average[32];
    static float last_output[32];
    float processed_value = *raw_signal;
    float iir_output;
    u8 j;
    u8 filter_coefficient = 16;

    running_average[filter_coefficient-1] = *raw_signal;
    for (j = 0; j < (filter_coefficient-1); j++){
        processed_value += running_average[j];
        running_average[j] = running_average[j+1];
    }
    processed_value = processed_value/filter_coefficient;

    last_output[filter_coefficient-1] = processed_value;
    iir_output = processed_value;
    for (j = 0; j < filter_coefficient-1; j++){
        iir_output += last_output[j];
        last_output[j] = last_output[j+1];
    }
    iir_output = (iir_output)/(filter_coefficient);

    return iir_output;
}
