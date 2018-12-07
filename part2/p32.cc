#include <iostream>
#include <mpi.h>
#include "complex.h"
#include "input_image.h"

int main(int argc, char **argv)
{
    if (argc != 4)
    {
        std::cout << "Incorrect usage" << std::endl;
        return -1;
    }

    // declare vars
    InputImage imageObj(argv[2]);
    int width, height;
    Complex *image = nullptr;

    // values from input file
    width = imageObj.get_width();
    height = imageObj.get_height();
    image = imageObj.get_image_data();

    // Complex ans(0, 0);

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
    printf("Number of tasks: %d My rank: %d\n", numtasks, rank);

    int row;
    for (row = 0; row < height; ++row)
    {
        std::cout << "row: " << row << std::endl;




    }

    // synchronize at end of horizontal FFT
    MPI_Barrier(MPI_COMM_WORLD);

    int column;
    for (column = 0; column < height; ++column)
    {
        std::cout << "column: " << row << std::endl;




    }

    std::cout << "Rank " << rank << " exiting normally" << std::endl;
    MPI_Finalize();
    return 0;
}