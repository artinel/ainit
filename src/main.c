#include<sys/exec.h>
#include<def.h>
#include<io/file.h>
#include<std/io.h>

void shell_list();
void exec_shell(char* shell);
void clear_screen();

int main(int argc, char** argv){

	file_t file = openf("/etc/def-shell", F_RONLY, F_IRUSR);
	if(file >= 0){
		//Reading default shell
		filestat_t stat;
		filestat(file, &stat);
		char sh[stat.st_size - 1];
		readf(file, sh, sizeof(sh));
		//Executing shell program
		exec_shell(sh);
	}else{
		clear_screen();
		prints(T_RED"Failed to load shell!!!\n"T_NORMAL);
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
		prints(T_GREEN"List of available shells\n"T_NORMAL);
		prints(T_YELLOW"%s"T_NORMAL, buffer);
		prints("Enter a shell path to execute : ");
		char sh[32];
		scans(sh, 32, 0);
		exec_shell(sh);
	}else{
		prints(T_RED"No shell found!!!\n"T_NORMAL);
	}
	closef(file);
}

void exec_shell(char* shell){
	prints(T_GREEN"Executing %s\n"T_NORMAL, shell);
	pid_t pid = fork();
	if(!pid){
		if(exec(shell, NULL, NULL) == 0){
			clear_screen();
			prints(T_RED"Failed to load shell!!!\n"T_NORMAL);
			shell_list();
		}
	}
}

void inline clear_screen(){
	prints("\033[2J\033[H");
}
