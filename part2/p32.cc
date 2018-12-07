#include <iostream>
#include <mpi.h>
#include "complex.h"
#include "input_image.h"
#include "fft.h"

int main(int argc, char **argv)
{
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

    // start mpi
    int numtasks, rank, rc;
    rc = MPI_Init(&argc, &argv);
    if (rc != MPI_SUCCESS)
    {
        std::cout << "Error starting MPI program. Terminating." << std::endl;
        MPI_Abort(MPI_COMM_WORLD, rc);
    }
    MPI_Comm_size(MPI_COMM_WORLD, &numtasks);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    
    if (rank == 0) //debug
    {
        std::cout << "Image length: " << length;
        std::cout << ", total length: " << totalLength << std::endl;
    }


    printf("Number of tasks: %d My rank: %d\n", numtasks, rank);

    //output buffer of FFT
    Complex output[length];

    int m, row;
    for (m = 0; m < length/numtasks; ++m)
    {
        row = rank + m * numtasks;
        std::cout << "row: " << row << std::endl;

        //fft
        fft(image + row * length, output, length);
        for (int i = 0; i < length; ++i) {
            // std::cout << image[i + row * length] << ' ';
            std::cout << output[i] << ' ';
        }
        std::cout << std::endl;
    }

    // synchronize at end of horizontal FFT
    MPI_Barrier(MPI_COMM_WORLD);

    int n, column;
    for (n = 0; n < length/numtasks; ++n)
    {
        column = rank + n * numtasks;
        //std::cout << "column: " << row << std::endl;
    }

    std::cout << "Rank " << rank << " exiting normally" << std::endl;
    MPI_Finalize();
    return 0;
}