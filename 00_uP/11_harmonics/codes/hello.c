#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define F 200       //Sampling Frequency(Speed)
#define T 1/F       //Sampling Period
#define A 5.0       //Amplitude
#define N 200       //Number of sample Depth
#define H 32        //Number of harmonics
#define PI 3.14

int main(void){
    
    FILE* file_out;
    file_out = fopen("out.txt", "w");
   
    float polynomial[400];
    
    //signal generation (sum of harmonics)
    for(int i = 0; i <N; i++)           //time advance 
    {                  
        int hi = 1;     //Harmonics 1 Hz
        polynomial[i] = 0;
        
        for(int j=0; j<H; j++)     //frequency
        {
            float signal = (float)(A/hi)*sin(2*PI*hi*T*i);
            polynomial[i] += signal;
            hi = hi + 2;                                //1,3,5,7,9
        }
    }

    //plot!
    for(int i=0; i<N; i++)
    {
        fprintf(file_out, "%d \t %.2f \n", i, polynomial[i]);
        //printf("%f\n", polynomial[i]);
    }

    // fourier analysis
    //int probe_freq = 2;

    for (int j=0; j<H; j++)     //fourier analysis H time (H frequency)
    {
        float freq_component = 0;
        int probe_freq = j;
        for (int i=0; i<N; i++) //fourier analysis one time
        {
            float probe = (float)(A)*sin(2*PI*probe_freq*T*i);
            freq_component += probe * polynomial[i];    //polynomial get ADCvalue 
        }
    printf("%d Hz component strength is %.1f\n", probe_freq, freq_component);
    }
    return 0;
}
