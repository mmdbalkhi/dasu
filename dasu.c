#include <stdio.h>
#include <stdlib.h>
#include <termios.h>
#include <unistd.h>

#include <sys/types.h>
#include <sys/wait.h>

#define PROJECT_NAME "dasu"

#include <security/pam_appl.h>
#include <security/pam_misc.h>

int verify_with_pam(const char *user) {
	pam_handle_t *pamh = NULL;
	struct pam_conv conv = {misc_conv, NULL};
	int retval;

	retval = pam_start("login", user, &conv, &pamh);
	if (retval != PAM_SUCCESS) {
		fprintf(stderr, "PAM initialization failed: %s\n",
				pam_strerror(pamh, retval));
		return 0;
	}

	retval = pam_authenticate(pamh, 0);
	if (retval == PAM_SUCCESS) {
		printf("PAM authentication successful!\n");
		pam_end(pamh, retval);
		return 1;
	} else {
		printf("PAM authentication failed: %s\n", pam_strerror(pamh, retval));
		pam_end(pamh, retval);
		return 0;
	}
}

int dasu(const char *user, char **argv) {
	if (!verify_with_pam(user))
		return -1;

	pid_t pid = fork();
	if (pid < 0) {
		perror("fork");
		exit - 1;
	}

	if (pid == 0) {
		execvp(argv[1], &argv[1]);
		perror("execvp");
		return 0;
	} else {
		int _status;
		waitpid(pid, &_status, 0);
		return WIFEXITED(_status) ? WEXITSTATUS(_status) : 1;
	}
}

int main(int argc, char **argv) {
	if (geteuid() != 0) {
		fprintf(stderr,
				"Permission denied! `%s` must have setuid root (chmod 6755)\n",
				argv[0]);
		return 1;
	}
	if (argc < 2) {
		fprintf(stderr, "You need to run a program with %s\n", argv[0]);
		return -1;
	}
	char *user = getlogin();
	return dasu(user, argv);
}
