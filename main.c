#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>

int main(int argc, char **argv) {
	int i; struct stat file_info; mode_t file_mode;

	for(i=1 ; i<argc ; i++){
		if(stat(argv[i], &file_info)<0){
			perror("stat :");
			exit(1);
		}
		file_mode = file_info.st_mode;

		if(S_ISDIR(file_mode)){
			if(chmod(argv[i], S_IRUSR |S_IXUSR |S_IRGRP | S_IXGRP | S_IROTH | S_IXOTH) < 0){
				perror("chmod :");
				exit(1);
		}
		}
		if(S_ISREG(file_mode)){
			//printf("mode = %o \n",file_mode);
			if( ( (file_mode & S_IXUSR) || (file_mode & S_IXGRP) || (file_mode & S_IXOTH) ) !=0 ){ //권한 확인할때 file_mode와 권한을 각 하나씩 묶어서 표현해야 한다.
				chmod(argv[i], S_IRUSR |S_IXUSR |S_IRGRP | S_IXGRP | S_IROTH | S_IXOTH);
				//printf("execute yes \n");
			}
			else{
				chmod(argv[i], S_IRUSR | S_IRGRP | S_IROTH);
				//printf("execute no \n");
			}
		}
	}
	 return 0;
}
