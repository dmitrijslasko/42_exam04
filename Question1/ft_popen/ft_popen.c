# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <sys/wait.h>
# include <sys/types.h>

/**
 * The popen function in C (and other languages like Python) is used to run
 * a command in a subprocess and open a pipe to or from that process.
 * It allows your program to execute shell commands and read their output
 * or send input to them.
 * 
 * 1) Declare file descriptors for the pipe (2 fds, read and write) and PIPE
 * 2) FORK the process 
 * 3) Do the actual work in the child process (pid == 0)
 * - 'r' means the child should WRITE to the pipe
 * - 'w' means the child should READ from the pipe
 * int dup2(int oldfd, int newfd);
 * 4) Close pipe ends
 *
 */
int	ft_popen(const char *file, char *const argv[], char type)
{
	// Basic input validation
	if (!file || !argv || (type != 'r' && type != 'w'))
		return (-1);
	
	// Declare the pipe and pipe
	int fd[2];
	if (pipe(fd) == -1)
		return (-1);
	
	pid_t pid = fork();
	// Check if forking failed
	if (pid == -1)
	{
		close(fd[0]);
		close(fd[1]);
		return (-1);
	}

	// Do the actual work in the child process 
	if (pid == 0)
	{
		// 'r' → The parent wants to read → the child writes to the pipe
		if (type == 'r')
		{
			// Redirect STDOUT to the write end of the pipe
			// so the parent can read the child's output
			if (dup2(fd[1], STDOUT_FILENO) == -1)
				exit(1);
		}
		// 'w' → The parent wants to write → the child reads from the pipe
		if (type == 'w')
		{
			// Redirect STDIN to the read end of the pipe
			// so the child can read input from the parent
			if (dup2(fd[0], STDIN_FILENO) == -1)
				exit(1);
		}
		// Close pipes
		close(fd[0]);
		close(fd[1]);
		// Replace child process image with target program
		execvp(file, argv);
		// If exec fails, exit with error
		exit(1);
	}
	// Parent process
	// Close write end; parent reads from fd[0]
	if (type == 'r')
	{
		close(fd[1]);
		return (fd[0]);
	}
	// Close read end; parent writes to fd[1]
	if (type == 'w')
	{
		close(fd[0]);
		return (fd[1]);
	}
	return (-1);
}
