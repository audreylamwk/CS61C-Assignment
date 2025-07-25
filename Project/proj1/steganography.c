/************************************************************************
**
** NAME:        steganography.c
**
** DESCRIPTION: CS61C Fall 2020 Project 1
**
** AUTHOR:      Dan Garcia  -  University of California at Berkeley
**              Copyright (C) Dan Garcia, 2020. All rights reserved.
**				Justin Yokota - Starter Code
**				YOUR NAME HERE
**
** DATE:        2020-08-23
**
**************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include <string.h>
#include "imageloader.h"

//Determines what color the cell at the given row/col should be. This should not affect Image, and should allocate space for a new Color.
Color *evaluateOnePixel(Image *image, int row, int col)
{
	int width = image->cols;
	//YOUR CODE HERE
	Color * newColor = malloc(sizeof(Color));
	uint8_t blue = image->image[width * col + row]->B;
	if (blue & 0x1) {
		// black
		newColor->R = 255;
		newColor->B = 255;
		newColor->G = 255;
	} else {
		newColor->R = 0;
		newColor->B = 0;
		newColor->G = 0;
	}
	return newColor;

}

//Given an image, creates a new image extracting the LSB of the B channel.
Image *steganography(Image *image)
{
	//YOUR CODE HERE
	Image * newImage = malloc(sizeof(Image));
	Color ** nImage = malloc(image->cols * image->rows *sizeof(Color *));
	newImage->cols = image->cols;
	newImage->rows = image->rows;
	newImage->image = nImage;
	for (int i = 0; i < image->cols; i++) {
		for (int j = 0; j < image->rows; j++) {
			nImage[i*(image->rows)+j] = evaluateOnePixel(image, i, j);
		}
	}
	return newImage;
}

/*
Loads a file of ppm P3 format from a file, and prints to stdout (e.g. with printf) a new image, 
where each pixel is black if the LSB of the B channel is 0, 
and white if the LSB of the B channel is 1.

argc stores the number of arguments.
argv stores a list of arguments. Here is the expected input:
argv[0] will store the name of the program (this happens automatically).
argv[1] should contain a filename, containing a file of ppm P3 format (not necessarily with .ppm file extension).
If the input is not correct, a malloc fails, or any other error occurs, you should exit with code -1.
Otherwise, you should return from main with code 0.
Make sure to free all memory before returning!
*/
int main(int argc, char **argv)
{
	//YOUR CODE HERE
	if (argc != 2) {
		return -1;
	}
	// + 1 for null terminator
	char * filename  = malloc(strlen(argv[1])+ 1);
	strcpy(filename, argv[1]);
	Image * image = readData(filename);
	if (!image) {
		return -1;
	}
	Image * newImage = steganography(image);
	writeData(newImage);
	freeImage(image);
	freeImage(newImage);
	free(filename);
	return 0;
}
