#include <stdio.h>
// Add your system includes here.
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <dirent.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>


#include "ftree.h"
#include "hash.h"


// Print the values of hash_val in hex, taken from a1, used for debugging
void show_hash(char *hash_val, long block_size) {
    for(int i = 0; i < block_size; i++) {
        printf("%.2hhx ", hash_val[i]);
    }
    printf("\n");
}

/*
 * Returns the FTree rooted at the path fname.
 */
struct TreeNode *generate_ftree(const char *fname) {
    // Your implementation here.

   struct TreeNode *temp = malloc(sizeof(struct TreeNode));
   struct stat sb;

   // initialize everything in temp as NULL, to be safe. 
   temp->contents = NULL;
   temp->next = NULL;
   temp->fname = NULL;
   temp->permissions = 0;
   temp->hash = NULL;

   // error handling
   if (lstat(fname, &sb) == -1) {
        perror("lstat");
        return temp;
    }

   switch (sb.st_mode & S_IFMT) {

   	//Recursive case, if this is a directory
    case S_IFDIR:  

    	// set the name
    	temp->fname = malloc(strlen(fname));
    	strncpy(temp->fname, fname, strlen(fname));
    	temp->fname[strlen(fname)] = '\0';

    	// set the permissions
    	temp->permissions = 0777 & sb.st_mode;

    	// opening a directory and retriving each filename
    	struct dirent *dp;
    	DIR *dirp = opendir(fname); // make a directory pointer containing the directory stream

    	if (dirp == NULL) {
    		// deals with case if directory does not open / has incorrect permissions, program skips this file and continues to the next item
			return NULL;
    	}

    	int i = 0;
		while ((dp = readdir(dirp)) != NULL) {
			if (((*dp).d_name[0] != '.')) {

				// skip over anything that has a '.' in the name, so skipping current and parent directories
			 	char *child_name = (*dp).d_name;

			 	// preserve the cwd before changing, then restore.
			 	char buffer[PATH_MAX + 1];
				char *save_cwd = getcwd(buffer, PATH_MAX + 1);

			 	// change the directory
			 	chdir(fname);

			 	// retrieve each child of the directory
			 	struct TreeNode *temp_child = generate_ftree(child_name);

			 	// contents is the head of the LL, so a child will be the "contents" pointer if it is the first child in the list.
			 	if ((i == 0) && temp->contents == NULL){
			 		temp->contents = temp_child;
			 	}

			 	else if (i == 1) { 
			 		// initializing the first 'next' pointer
			 		if ( (temp->contents->next) == NULL && (temp->contents) != NULL) {
			 			temp->contents->next = temp_child;
			 		}
			 	}
			 	else {
			 		// Traverse through linked list, starting with contents as the head.
			 		struct TreeNode *current = temp->contents;
			 		int j = 0;
			 		while (current->next != NULL) {
			 			current = current->next;
			 			j++;
			 		}
			 		// now we are at the end of the linkedlist. Now append the new value.
			 		current->next = temp_child;
			 	}

			 	// restore back to previous directory to complete the recursive call
			 	chdir(save_cwd);
				i++;
			}
		}
    	break;

    default: // if a regular file or a link

    	// set the name
    	temp->fname = malloc(strlen(fname));
    	strncpy(temp->fname, fname, strlen(fname));
    	temp->fname[strlen(fname)] = '\0';

    	// set the permissions
    	temp->permissions = 0777 & sb.st_mode;

		// case where this is a regular file		
		if S_ISREG(sb.st_mode) {

			FILE *fp = fopen(fname, "r");
			if (fp == NULL) {
				// deals with case if file does not open, program skips this file and continues to the next thing item
				return NULL;
			}

			// do hash on file contents and store in a string
			char *hash_val = hash(fp);
			fclose(fp);

			temp->hash = hash_val;
			}

		// case where this is a link
		else if S_ISLNK(sb.st_mode) {
			
			// setting hash as all '\0' for a link
			char *place = malloc(BLOCK_SIZE);
			int j;
			for (j = 0; j < BLOCK_SIZE; j++) {
				place[j] = '\0';
				}

			temp->hash = place;
			}

    	break;         
     break;
    }

    return temp;
   return NULL;
}


/*
 * Prints the TreeNodes encountered on a preorder traversal of an FTree.
 */
void print_ftree(struct TreeNode *root) {
    // Here's a trick for remembering what depth (in the tree) you're at
    // and printing 2 * that many spaces at the beginning of the line.
	
	if (root->fname == NULL) {
		exit(0);
	}
    static int depth = 0;
    printf("%*s", depth * 2, "");

    // base case, links and regular files. they are characterized with a hash that is not NULL. 
    if (root->hash != NULL) {
    	printf("%s (%o)\n", root->fname, root->permissions);
    }

    // recursive case, is a directory.
    else {
    	printf("===== %s (%o) =====\n", root->fname, root->permissions);
		int k = 0;
 		struct TreeNode *curr = root->contents;

 		depth += 1; // indent for a recursive call
 		while (curr != NULL) {
 			print_ftree(curr);
 			curr = curr->next;
 			k++;
			}
		depth -= 1; // dedent when recursive call is complete
    	
    }
}
 
