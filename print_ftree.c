// #include <stdio.h>
// #include "ftree.h"

#include <stdio.h>
#include "ftree.h"

#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <dirent.h>

int main(int argc, char **argv) {
    if (argc != 2) {
        printf("Usage:\n\tftree DIRECTORY\n");
        return 0;
    }

    struct TreeNode *root = generate_ftree(argv[1]);
    print_ftree(root);

    return 0;
}



// PRISTINE MAIN IS UP THERE DONT TOUCH IT 

// int main(int argc, char **argv) {

//    struct stat sb;

//    if (argc != 2) {
//         fprintf(stderr, "Usage: %s <pathname>\n", argv[0]);
//         return 0;
//     }

//    if (lstat(argv[1], &sb) == -1) {
//         perror("stat");
//         return 0;
//     }

//    printf("File type:                ");

//    switch (sb.st_mode & S_IFMT) {
//     case S_IFDIR:  
//     	printf("directory\n");
//     	struct dirent dirs[100]; // assuming this is MAXDIRS from ex6
//     	struct dirent *dp;
//     	DIR dirp = *opendir(argv[1]); // make a directory pointer containing the directory stream
//     	int i = 0;
// 		while ((dp = readdir(&dirp)) != NULL) {
// 			if (((*dp).d_name[0] != '.')) {
// 			 	printf("i:%d name: %s\n", i, (*dp).d_name);
// 				 dirs[i] = *dp;
// 				 i++;
// 			}
// 		}

//     	break;

//     case S_IFREG:  
//     	printf("regular file\n"); 

//     	// KJGHKLDFGHKSJGDFHAKDJHGSLDFJHGL;FGJLHKDGFSL;JNSDKFXGJWR T;G DO THE HASH FUNCTION PROPERLY DO THE HASH DO THE HASHHHH
//     	// for now i will keep hash in the tree struct null

//     	// NOW
//     	// open the file
//     	// set up a char pointer and do the hash because it has to return in hash val
//     	// close the file
//   //   	FILE *fp;
// 		// fp = fopen(argv[1], "r");
// 		// char *hash_val = hash(fp);
// 		// fclose(fp);



//     	break;


//     case S_IFLNK:  printf("is a link \n");				break;
//     default:       printf("unknown?\n");                break;
//     }

//    printf("here is the permissions i think %o\n", 0777 & sb.st_mode);
//    printf("File size:                %lld bytes\n",
//             (long long) sb.st_size);

//    return 0;
//    // IS THERE ANY DIFFERENCE BETWEEN ISDIR AND IFDIR!??!!?!? OR SWHATEVER?!?!? IDKkkk
// }
