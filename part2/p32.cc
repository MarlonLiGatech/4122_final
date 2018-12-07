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

    // forward/reverse [INPUTFILE] [OUTPUTFILE]
    InputImage imageObj(argv[2]);
    int width, height;
    Complex *image;

    width = imageObj.get_width();
    height = imageObj.get_height();
    image = imageObj.get_image_data();

    // Complex ans(0, 0);

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

    std::cout << "Rank " << rank << " exiting normally" << std::endl;
    MPI_Finalize();
    return 0;
}