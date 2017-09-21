#include <stdio.h>
#include <stdlib.h>
#include "hash.h"

// Complete these two functions according to the assignment specifications

// MODIFIED

char * hash(FILE *f) {
    
	int i = 0;
	char *hash_val = malloc(BLOCK_SIZE);
	
	// assign everything to '\0'
	for (int j = 0; j < BLOCK_SIZE;) {
		hash_val[j] = '\0';
		j++;
		}
		
	char c[0];
 	// using fread instead of scanf
	while (fread(&c, 1, 1, f) != 0){ 
		if (i < BLOCK_SIZE){
			hash_val[i] = (*c ^ hash_val[i]);
			i++;
		} else {
			i = 0;
			hash_val[i] = (*c ^ hash_val[i]);
			i++;

		}
	}
	return hash_val;
}

