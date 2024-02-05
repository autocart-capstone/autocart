#include "pffft.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <assert.h>

#define SIZE 100

void cmplx_multiply(float r1, float i1, float r2, float i2, float *result_r, float *result_i)
{
    *result_r = r1*r2 - i1*i2;
    *result_i = r1*i2 + i1*r2;
}

int main(int argc, char const *argv[])
{
    float_t y[SIZE] = {0};
    float_t y2[SIZE] = {0};
    for (int i = 0; i < SIZE; i++) {
        float t1 = (float)i/16000.0;

        y[i] = sin(t1 * 2 * M_PI * 1000.0);
    }

    for (int i = 0; i < SIZE/4; i++)
    {
        float t2 = ((float)i) / 16000.0;
        y2[i] = sin(t2 * 2 * M_PI * 1000.0);
    }

    PFFFT_Setup* setup = pffft_new_setup(SIZE, PFFFT_REAL);
    assert(setup);

    float_t out1[SIZE+2] = {0};
    pffft_transform_ordered(setup, y, out1, NULL, PFFFT_FORWARD);
    out1[SIZE] = out1[1];
    out1[1] = 0;
    float_t out2[SIZE+2] = {0};
    pffft_transform_ordered(setup, y2, out2, NULL, PFFFT_FORWARD);
    out2[SIZE] = out2[1];
    out2[1] = 0;

    for (int i = 1; i < SIZE+2; i += 2) {
        // Take the complex conj of out2
        out2[i] = -out2[i];
    }

    float_t out_mult[SIZE + 2] = {0};
    for (int i = 0; i < SIZE+2; i += 2)
    {
        // complex multiplication
        int r_ind = i;
        int i_ind = i+1;
        out_mult[r_ind] = out1[r_ind] * out2[r_ind] - out1[i_ind] * out2[i_ind];
        out_mult[i_ind] = out1[r_ind] * out2[i_ind] + out1[i_ind] * out2[r_ind];
    }
    out_mult[1] = out_mult[SIZE];

    float_t correlation[SIZE] = {0};
    pffft_transform_ordered(setup, out_mult, correlation, NULL, PFFFT_BACKWARD);
    int valid_len = SIZE - SIZE/4 + 1;
    for (int i = 0; i < valid_len; i++)
    {
        correlation[i] = fabsf(correlation[i]);
        printf("%.16f\n", correlation[i]);
    }
    int max_ind = 0;
    float max_val = correlation[0];
    
    for (int i = 1; i < valid_len; i++)
    {
        if (correlation[i] > max_val) {
            max_val = correlation[i];
            max_ind = i;
        }
    }
    printf("\n");
    printf("max ind: %i\n", max_ind);
    pffft_destroy_setup(setup);
    return 0;
    }
