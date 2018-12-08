#include <stdio.h>
#include <algorithm>
#include <iostream>
#include <fstream>
#include <cstring>
#include <string>
#include <sstream>
#include <thrust/host_vector.h>
#define T_P_B 1024

__global__ void heat2D(float *in, float *out, float *d_candles, int cells, float k, int width) {
    int idx = threadIdx.x + blockIdx.x * blockDim.x;
    if(idx < cells) {
        float top = in[idx];
        float bot = in[idx];
        float left = in[idx];
        float right = in[idx];

        if (idx >= width)    //top row
            top = in[idx - width];
        if (idx < (cells - width)) //bottom row
            bot = in[idx + width];
        if (idx % width != 0)  //left column
            left = in[idx - 1];
        if ((idx + 1) % width != 0)  //right column
            right = in[idx + 1];
        if (d_candles[idx] >= 0)
            out[idx] = d_candles[idx];
        else
            out[idx] = in[idx] + k * (top + bot + right + left - 4 * in[idx]);
    }
}

int main(int argc, char *argv[]) {
    if (argc != 4)
    {
        std::cout << "Incorrect usage" << std::endl;
        return -1;
    }

    // declare vars
    InputImage imageObj(argv[2]);
    int length, totalLength;
    Complex *image = nullptr;

    // values from input file
    length = imageObj.get_width();
    totalLength = length * length;
    image = imageObj.get_image_data();



    
    //create stationary heating source grid
    int cells = width * height * depth;
    float candles[cells] = {};
    for(int i = 0; i < cells; ++i) {
        candles[i] = -1;
    }

    //input candle information
    int location_x, location_y, candle_width, candle_height;
    int location_z = 0, candle_depth = 1;
    float fixed_temperature;
    int ind;
    for (int i = 0; i < static_heat.size()/info_size; i++) {
        ind = i * info_size;
        location_x = static_heat[0 + ind];
        location_y = static_heat[1 + ind];
        if (!mode) {
            candle_width = static_heat[2 + ind];
            candle_height = static_heat[3 + ind];
            fixed_temperature = static_heat[4 + ind];
        } else {
            location_z = static_heat[2 + ind];
            candle_width = static_heat[3 + ind];
            candle_height = static_heat[4 + ind];
            candle_depth = static_heat[5 + ind];
            fixed_temperature = static_heat[6 + ind];
        }
        for (int z = location_z; z < location_z + candle_depth; z++) {
            for (int y = location_y; y < location_y + candle_height; y++) {
                for (int x = location_x; x < location_x + candle_width; x++) {
                    candles[x + y * width + z * width * height] = fixed_temperature;
                }
            }
        }
    }

    //cuda code
    float *d_gridA, *d_gridB, *d_candles;
    cudaMalloc((void**)&d_gridA, cells * sizeof(float));
    cudaMalloc((void**)&d_gridB, cells * sizeof(float));
    cudaMalloc((void**)&d_candles, cells * sizeof(float));

    float gridA[cells], gridB[cells];

    //initialize starting grid
    for(int i = 0; i < cells; ++i)
        gridA[i] = starting_temp;

    //copy candles
    for (int i = 0; i < cells; i++) {
        if (candles[i] >= 0)
            gridA[i] = candles[i];
    }

    cudaMemcpy(d_gridA, gridA, cells * sizeof(float), cudaMemcpyHostToDevice);
    cudaMemcpy(d_candles, candles, cells * sizeof(float), cudaMemcpyHostToDevice);

    float *in, *out;
    int i;
    for (i = 0; i < timestep; i++) {
        if (i % 2) {
            in = d_gridB;
            out = d_gridA;
        } else {
            in = d_gridA;
            out = d_gridB;
        }

        if (mode == 0)
            heat2D<<<(cells + T_P_B-1) / T_P_B, T_P_B>>>(in, out, d_candles, cells, k, width);
        else
            heat3D<<<(cells + T_P_B-1) / T_P_B, T_P_B>>>(in, out, d_candles, cells, k, width, height);
    }

    //set up answer
    float *answer;
    if (i % 2) {
        cudaMemcpy(gridB, d_gridB, cells*sizeof(float), cudaMemcpyDeviceToHost);
        answer = gridB;
    } else {
        cudaMemcpy(gridA, d_gridA, cells*sizeof(float), cudaMemcpyDeviceToHost);
        answer = gridA;
    }
    cudaFree(d_gridA);
    cudaFree(d_gridB);
    cudaFree(d_candles);

    //print answers
    std::ofstream myfile;
    myfile.open("heatOutput.csv");
    for(int i = 0; i < cells; ++i) {
        myfile << answer[i];
        if ((((i + 1) % width) == 0) && i > 0 && i < (cells - 1))
            myfile << std::endl;
        else
            myfile << ",";
        if ((((i + 1) % (width * height)) == 0) && i < (cells - 1))
            myfile << std::endl;
    }
    myfile.close();

    return 0;
}