#include "./lib/libft/libft.h"
#include <sys/types.h>
#include <sys/wait.h>
#define N 3
int	main(void)
{
	int	pid[N];
	int	status;
	int	rval;
	int	i = -1;

	while (++i < N)
	{
		pid[i] = fork();
		if (pid[i] == 0)
		{
			printf("child[%d]\n", i);
			return (0);
		}
	}
	for (int i = 0; i < N; i++)
	{
		waitpid(pid[i], 0, 0);
	}
	i = -1;
	while (++i < N)
	{
		while (1) 
		{
			rval = waitpid(pid[i], &status, WNOHANG);

			if (rval == -1) {
				perror("waitpid failed");
				exit(1);
			} else if (rval == 0) {
				puts("sleep");
				sleep(1);
			} else {
				puts("got it");
				break;
			}
		}
	}
	if (i == N)
		printf("end\n");

	return (0);
}