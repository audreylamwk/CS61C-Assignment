/************************************************************************
**
** NAME:        gameoflife.c
**
** DESCRIPTION: CS61C Fall 2020 Project 1
**
** AUTHOR:      Justin Yokota - Starter Code
**				YOUR NAME HERE
**
**
** DATE:        2020-08-23
**
**************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include <string.h>
#include "imageloader.h"

//Determines what color the cell at the given row/col should be. This function allocates space for a new Color.
//Note that you will need to read the eight neighbors of the cell in question. The grid "wraps", so we treat the top row as adjacent to the bottom row
//and the left column as adjacent to the right column.
Color *evaluateOneCell(Image *image, int row, int col, uint32_t rule)
{
	//YOUR CODE HERE
	Color * newColor = malloc(sizeof(Color));
	if (!newColor) {
		return NULL;
	}
	// read current Colour
	Color * curColor = image->image[row * image->cols + col];
	// read all neighbour's colour

	int lftcol = (col - 1) < 0 ? (image->cols - 1) : col - 1; 
	int rgtcol = (col + 1) > (image->cols - 1) ? 0 : col + 1;
	int tprow = (row - 1) < 0 ? (image->rows - 1) : row - 1;
	int btrow = (row + 1) > (image->rows-1) ? 0: row + 1;
	// top 
	Color * nborColor1 = image->image[tprow * (image->cols) + lftcol];
	Color * nborColor2 = image->image[tprow * (image->cols) + col];
	Color * nborColor3 = image->image[tprow * (image->cols) + rgtcol];

	// middle
	Color * nborColor4 = image->image[row * (image->cols) + lftcol];
	Color * nborColor5 = image->image[row * (image->cols) + rgtcol];

	// bottom
	Color * nborColor6 = image->image[btrow * (image->cols) + lftcol];
	Color * nborColor7 = image->image[btrow * (image->cols) + col];
	Color * nborColor8 = image->image[btrow * (image->cols) + rgtcol];

	// construct an array of neighbours
	Color * nbColors[8] = {nborColor1, nborColor2, nborColor3, nborColor4, 
		nborColor5, nborColor6, nborColor7, nborColor8};
	
	// loop through each bit of 8 of red color in current cell
	uint8_t R = 0x0;
	uint8_t G = 0x0;
	uint8_t B = 0x0;
	for (int n = 0; n < 8; n ++) {
		int cR = (curColor->R) >> n & 0x1;
		int cG = (curColor->G) >> n & 0x1;
		int cB = (curColor->B) >> n & 0x1;
		int countR = 0;
		int countG = 0;
		int countB = 0;
		for (int i = 0; i < 8; i++) {
			if ((nbColors[i]->R) >> n & 0x1) {
				countR += 1;
			}
			if ((nbColors[i]->G) >> n & 0x1) {
				countG += 1;
			}
			if ((nbColors[i]->B) >> n & 0x1) {
				countB += 1;
			}
		}
		int bitIndexR = cR * 9 + countR;
		int bitIndexG = cG * 9 + countG;
		int bitIndexB = cB * 9 + countB;
		int ruleR = (rule >> bitIndexR) & 0x1;
		int ruleG = (rule >> bitIndexG) & 0x1;
		int ruleB = (rule >> bitIndexB) & 0x1;
		R |= (ruleR << n);
		G |= (ruleG << n);
		B |= (ruleB << n);
	}
	newColor->R = R;
	newColor->G = G;
	newColor->B = B;
	return newColor;
}

//The main body of Life; given an image and a rule, computes one iteration of the Game of Life.
//You should be able to copy most of this from steganography.c
Image *life(Image *image, uint32_t rule)
{
	//YOUR CODE HERE
	Image * newImage = malloc(sizeof(Image));
	Color ** nImage = malloc(image->cols * image->rows * sizeof(Color *));
	newImage->cols = image->cols;
	newImage->rows = image->rows;
	
	for (int i = 0; i < image->rows; i++) {
		for (int j = 0; j < image->cols; j++) {
			nImage[i*(image->cols)+j] = evaluateOneCell(image, i, j, rule);
		}
	}
	newImage->image = nImage;
	return newImage;
}

/*
Loads a .ppm from a file, computes the next iteration of the game of life, then prints to stdout the new image.

argc stores the number of arguments.
argv stores a list of arguments. Here is the expected input:
argv[0] will store the name of the program (this happens automatically).
argv[1] should contain a filename, containing a .ppm.
argv[2] should contain a hexadecimal number (such as 0x1808). Note that this will be a string.
You may find the function strtol useful for this conversion.
If the input is not correct, a malloc fails, or any other error occurs, you should exit with code -1.
Otherwise, you should return from main with code 0.
Make sure to free all memory before returning!

You may find it useful to copy the code from steganography.c, to start.
*/
int main(int argc, char **argv)
{
	//YOUR CODE HERE
	if (argc != 3) {
		return -1;
	}
	char * filename = malloc(strlen(argv[1]) + 1);
	strcpy(filename, argv[1]);
	Image * image = readData(filename);
	if (!image) {
		return -1;
	}
	char * endptr;
	uint32_t rule = strtol(argv[2], &endptr, 16);
	Image * newImage = life(image, rule);
	if (!newImage) {
		return -1;
	}
	writeData(newImage);
	freeImage(image);
	freeImage(newImage);
	free(filename);
	return 0;
}
