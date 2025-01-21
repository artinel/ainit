#include<sys/exec.h>
#include<def.h>
#include<io/file.h>
#include<std/io.h>

void shell_list();

int main(int argc, char** argv){

	char sh[32];
	file_t file = openf("/etc/def-shell", F_RONLY, F_IRUSR);
	if(file >= 0){
		//Reading default shell
		readf(file, sh, 32);
		//Executing shell program
		exec(sh, NULL, NULL);
	}else{
		prints("Failed to load shell!!!\n");
		shell_list();
	}

	closef(file);

	while(1){
		//event loop
	}
	return 0;
}

void shell_list(){
	file_t file = openf("/etc/shells", F_RONLY, F_IRUSR);
	if(file >= 0){
		filestat_t stat;
		filestat(file, &stat);
		char buffer[stat.st_size];
		readf(file, buffer, sizeof(buffer));
		prints("List of available shells\n");
		prints(buffer);
		prints("Enter a shell path to execute : ");
		char sh[32];
		scans(sh, 32, 0);
		if(exec(sh, NULL, NULL) == 0){
			prints("Failed to load shell!!!\n");
			shell_list();
		}
	}else{
		prints("No shell found!!!\n");
	}
	closef(file);
}
