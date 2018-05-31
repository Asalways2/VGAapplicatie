gcc -c       API_draw/draw.c    -o draw.o
gcc -c       API_io/api_io.c -o api_io.o

#
# object files for shared libraries need to be compiled as position independent
# code (-fPIC) because they are mapped to any position in the address space.
#
gcc -c -fPIC API_draw/draw.c    -o draw.o
gcc -c -fPIC API_io/api_io.c -o api_io.o