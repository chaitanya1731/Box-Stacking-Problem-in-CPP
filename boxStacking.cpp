#include <bits/stdc++.h>
using namespace std;

//Declare a structure for the Dimensions of the boxes
struct Box {
	int height;
	int width;
	int depth;
};

void title(){
	printf("----- WELCOME TO THE BOX STACKING PROBLEM -----\n");
	printf("Given a set of n cuboid boxes with height(h), width(w) and depth(d). \n"
			"Create a stack of boxes which is as tall as possible, but a box can be placed on top of another box \n"
			"only if both width and depth of the upper placed box are smaller than width and depth of the lower box respectively. \n"
			"You can rotate a box so that any side functions as its base. \n"
			"It is also allowable to use multiple instances of the same type of box \n");
	printf("-----------------------------------------------\n");
}

void displayInput(Box boxDimensions[], int n){
	printf("Given number of Boxes are %d and their dimensions are as follows - \n", n);
	for (int i = 0; i < n; i++ ) {
		printf("{%d x %d x %d}\n", boxDimensions[i].height, boxDimensions[i].width, boxDimensions[i].depth);
	}
	printf("--------------------------------\n");
}

// C library compare function for Quick Sort
int compare (const void *a, const void * b) {
	return ( (*(Box *)b).depth * (*(Box *)b).width ) -
			( (*(Box *)a).depth * (*(Box *)a).width );
}

int boxStackingHeight( Box boxDimensions[], int n ) {
	//Generate all 3 rotations of all boxes.
	//The size of rotation array becomes 3 times the size of original array

	Box rotation[3*n];
	int index = 0;
	for (int i = 0; i < n; i++) {
		// Original dimensions of box - First Rotation
		rotation[index].height = boxDimensions[i].height;
		rotation[index].depth = max(boxDimensions[i].depth, boxDimensions[i].width);
		rotation[index].width = min(boxDimensions[i].depth, boxDimensions[i].width);
		index++;

		// Second rotation of box
		rotation[index].height = boxDimensions[i].width;
		rotation[index].depth = max(boxDimensions[i].height, boxDimensions[i].depth);
		rotation[index].width = min(boxDimensions[i].height, boxDimensions[i].depth);
		index++;

		// Third rotation of box
		rotation[index].height = boxDimensions[i].depth;
		rotation[index].depth = max(boxDimensions[i].height, boxDimensions[i].width);
		rotation[index].width = min(boxDimensions[i].height, boxDimensions[i].width);
		index++;
	}

	n = 3*n;

	// Sort the array 'rotation[]' in decreasing order of base area using Quick Sort
	qsort (rotation, n, sizeof(rotation[0]), compare);

	// Printing all rotations of the Box
	printf("All Rotations of the Boxes \n");
	for (int i = 0; i < n; i++ ) {
		printf("{%d x %d x %d}\n", rotation[i].height, rotation[i].width, rotation[i].depth);
	}
	printf("--------------------------------\n");

	// Initialize maxHeightOfStack values for all indexes
	// maxHeightOfStack[i] --> Maximum possible Stack Height with box i on top
	int maxHeightOfStack[n];
	for (int i = 0; i < n; i++ ) {
		maxHeightOfStack[i] = rotation[i].height;
	}

	// Compute optimized maxHeightOfStack values in bottom up manner
	for (int i = 1; i < n; i++ ){
		for (int j = 0; j < i; j++ ){
			if ( rotation[i].width < rotation[j].width &&
					rotation[i].depth < rotation[j].depth &&
					maxHeightOfStack[i] < maxHeightOfStack[j] + rotation[i].height) {
				maxHeightOfStack[i] = maxHeightOfStack[j] + rotation[i].height;
			}
		}
	}

	// Pick up the maximum height from the stack
	int max = -1;
	for ( int i = 0; i < n; i++ ) {
		if ( max < maxHeightOfStack[i] ) {
			max = maxHeightOfStack[i];
		}
	}
	return max;
}

// Main Function
int main() {
	title();
	// Given input with 3 boxes of the height h, depth d and width w
	Box boxDimensions[] = { {10, 20, 30},
			{45, 55, 60},
			{50, 52, 72} };

	// Dynamic array size declaration
	int n = sizeof(boxDimensions)/sizeof(boxDimensions[0]);

	//Display input
	displayInput(boxDimensions, n);

	int maxHeight = boxStackingHeight(boxDimensions, n);
	printf("The MAXIMUM Possible Height of the Stack = %d\n", maxHeight);

	return 0;
}
