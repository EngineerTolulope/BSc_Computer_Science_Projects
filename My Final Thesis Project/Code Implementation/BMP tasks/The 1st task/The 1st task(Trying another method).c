#include <stdio.h>
#include<sys/stat.h>
#include<fcntl.h>

int main(){
int size; // to store the size
char sig[2]; // to store the signature
int f=open("proc1.bmp", O_RDONLY);
int g= open("tina.bmp",O_WRONLY|O_CREAT|O_TRUNC|O_BINARY,S_IRUSR|S_IWUSR);// (Read https://linux.die.net/man/3/open)

read(f, sig, 2); // read the first two bytes, the signature, �BM� as a string
write(g, sig, 2);
read(f,&size,4); // read the second field, the size, as integer
write(g, &size, 4);

//Then we have to reach the width and the height, but before them there are bytes which is not so important actually,
//so we just skip it (read but not use):

int temp;
int W,H;
read(f,&temp,4); // unused filed
write(g, &temp, 4);
read(f,&temp,4); // Pixel Array offset
write(g, &temp, 4);
read(f,&temp,4); // DIB header size
write(g, &temp, 4);
read(f,&W,4); // width in pixel (as binary integer)
write(g, &W, 4);
read(f,&H,4); // height in pixel (as binary integer)
write(g, &H, 4);

//Then the next two fields are just 2 bytes long, so we need �short� variables:
short int tmp;
short int Color;
short int i=2;
read(f,&tmp,2); // planes
write(g, &tmp, 2);
read(f,&Color,2); // colour depth (bits per pixel)
write(g, &Color, 2);

unsigned char R,G,B;
// read intermediate fields temporarily
read(f,&temp,4); //Compression
write(g, &temp, 4);
read(f,&temp,4); //Image Size
write(g, &temp, 4);
//printf("%d",temp); //For the image size including padding
read(f,&temp,4); //Horizontal pixel/meter
write(g, &temp, 4);
read(f,&temp,4); //Vertical pixel/meter
write(g, &temp, 4);
read(f,&temp,4); //Colors in palette
write(g, &temp, 4);
read(f,&temp,4); //Used palette colors
write(g, &temp, 4);

//
int j;//representing the column index
unsigned char pixelArray[100][300]; //Array of the elements
for (i=0;i<100;i++){
    for (j=0;j<300;j++){
     read(f,&pixelArray[i][j],1);
     pixelArray[i][j]/=2;
    }
}

for (i=0;i<100;i++){
    for (j=0;j<300;j++){
     write(g,&pixelArray[i][j],1);

    }
}

//printf(" Red: %d, Green: %d\n Blue: %d\n", R,G,B);

close(f);
close (g);

return 0;
}
