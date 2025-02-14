#include <stdio.h>
#include<sys/stat.h>
#include<fcntl.h>

int main(){
/*Before you start them I think better to do a 0th task.
Create a program which can tell some properties of a bmp picture.
These properties are the size of bmp file (in bytes), the resolution of the picture (pixel x pixel), color depth (in bits).
What does it mean? First see the size. The second bmp header field is the size,
so this 4 bytes (from the 3rd to the 6th byte) in little-endian byteorder stores this information.
This is a binary integer (int) value, what we can read in.
�*/
int size; // to store the size
char sig[2]; // to store the signature
int f=open("proc1.bmp", O_RDONLY);
read(f, sig, 2); // read the first two bytes, the signature, �BM� as a string
read(f,&size,4); // read the second field, the size, as integer
//printf("The size of BMP is %d. \n", size); // print it to the screen in normal (decimal) form

//Then we have to reach the width and the height, but before them there are bytes which is not so important actually,
//so we just skip it (read but not use):
int temp;
int W,H;
read(f,&temp,4); // unused filed
read(f,&temp,4); // Pixel Array offset
read(f,&temp,4); // DIB header size
read(f,&W,4); // width in pixel (as binary integer)
read(f,&H,4); // height in pixel (as binary integer)
//printf("The resolution is %d x %d. \n",W, H );

//Then the next two fields are just 2 bytes long, so we need �short� variables:
short int tmp;
short int Color;
read(f,&tmp,2); // planes
read(f,&Color,2); // colour depth (bits per pixel)
//printf("The color of each pixel is encoded in %d bit.\n",Color);

/*
So we are ready with 0th task.
Next task before the original 3: How much red, green and blue colors are in the bottom left pixel?
Solution: the first 3 bytes of the Pixel Array (green part in bmp.pdf).
They are independent 1 byte long values, so you have to use one-byte-long unsigned integer variables (unsigned char).
*/

unsigned char R,G,B;
// read intermediate fields temporarily
read(f,&temp,4); //Compression
read(f,&temp,4); //Image Size
read(f,&temp,4); //Horizontal pixel/meter
read(f,&temp,4); //Vertical pixel/meter
read(f,&temp,4); //Colors in palette
read(f,&temp,4); //Used palette colors
//
read(f,&B,1);
read(f,&G,1);
read(f,&R,1);

printf(" Red: %d, Green: %d\n Blue: %d\n", R,G,B);
close(f);

return 0;
}
