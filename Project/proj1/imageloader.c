/************************************************************************
**
** NAME:        imageloader.c
**
** DESCRIPTION: CS61C Fall 2020 Project 1
**
** AUTHOR:      Dan Garcia  -  University of California at Berkeley
**              Copyright (C) Dan Garcia, 2020. All rights reserved.
**              Justin Yokota - Starter Code
**				YOUR NAME HERE
**
**
** DATE:        2020-08-15
**
**************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include <string.h>
#include "imageloader.h"

//Opens a .ppm P3 image file, and constructs an Image object. 
//You may find the function fscanf useful.
//Make sure that you close the file with fclose before returning.
Image *readData(char *filename) 
{
	//YOUR CODE HERE
	FILE *fp = fopen(filename, "r");
	Image * image = malloc(sizeof(Image));
	// read or skip type
	char* type;
	fscanf(fp, "%s", type);
	int width;
	int height;
	fscanf(fp, "%d %d",&width, &height);
	image->rows = height;
	image->cols = width;
	int colour;
	fscanf(fp, "%d",&colour);
	// a list Color*
	// each Color* store color of single pixel
	image->image = malloc(height * width * sizeof(Color *));
	for (int i=0; i< height * width; i++) {
		Color * cColor = malloc(sizeof(Color));
		fscanf(fp, "%d %d %d", &cColor->R, &cColor->G, &cColor->B);
		image->image[i] = cColor;
	}
	fclose(fp);
	return image;

}

//Given an image, prints to stdout (e.g. with printf) a .ppm P3 file with the image's data.
void writeData(Image *image)
{
	//YOUR CODE HERE
	printf("P3\n");
	int cols = image->cols;
	int rows = image->rows;
	printf("%d %d\n", cols, rows);
	printf("255");
	for (int i=0; i<rows; i++) {
		printf("\n");
		for (int j=0; j<cols; j++) {
			Color *pixel = image->image[i * cols + j];
			printf("%3d %3d %3d", pixel->R, pixel->G, pixel->B);
			if (j != cols - 1) {
				printf("   ");
			}
		}
	}
	printf("\n");
}

//Frees an image
void freeImage(Image *image)
{
	for (int i =0; i < image->rows * image->cols; i++) {
		free(image->image[i]);
	}
	free(image->image);
	free(image);
	//YOUR CODE HERE
}