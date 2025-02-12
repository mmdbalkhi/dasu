#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include <sys/types.h>
#include <sys/wait.h>

#define PROJECT_NAME "dasu"

int main(int argc, char **argv) {
	if (geteuid() != 0) {
		fprintf(stderr, "Permission denied! `%s` must\
have setuid root (chmod 6755)\n", argv[0]);
		return 1;
	}
	if(argc < 2){
		fprintf(stderr, "You need to run a program with %s\n", argv[0]);
		return -1;
	}

	pid_t pid = fork();
	if(pid < 0){
		perror("fork");
		return -1;
	}


	if(pid == 0){
		execvp(argv[1], &argv[1]);
		perror("execvp");
		return 0;
	} else {
		int _status;
		waitpid(pid, &_status, 0);
		return WIFEXITED(_status) ?
			WEXITSTATUS(_status) : 1;
	}
}
