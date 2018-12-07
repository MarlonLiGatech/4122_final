building project:

mkdir build

cd build

cmake ..

make

./p31 forward/reverse [INPUTFILE] [OUTPUTFILE]
mpirun -np 8 ./p32 forward/reverse [INPUTFILE] [OUTPUTFILE]
./p33 forward/reverse [INPUTFILE] [OUTPUTFILE]