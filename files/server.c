#include "minitalk.h"

static void	itsworking(int signal)
{
	static int	count = 0;
	static char	str[100];
	static int	symbol = 0;

	count++;
	if (signal == SIGINT)
		error_case("\n\033[0;37m~*'.+Process finished with exit code 0+.'*~\n", 0);
	else
	{
		symbol <<= 1;
		symbol = symbol | (signal == SIGUSR1);
	}
	if (!(count % 8) && count)
	{
		str[count / 8 - 1] = symbol;
		symbol = 0;
	}
	if (count % 800 == 0 || (str[count / 8 - 1] == '\0' && ft_strlen(str) > 0))
	{
		write(1, str, ft_strlen(str));
		ft_memset(&str, '\0', 100);
		count = 0;
	}
}

int	main(void)
{
	struct sigaction	sigredirect;
	sigset_t			my_signals;
	char				*pid;

	pid = ft_itoa(getpid());
	write(1, "\033[0;37mProcess id: {\033[1;32m", 27);
	write(1, pid, ft_strlen(pid));
	free(pid);
	write(1, "\033[0;37m}\033[0m\n", 13);
	ft_memset(&sigredirect, '\0', sizeof(sigredirect));
	sigredirect.sa_handler = itsworking;
	sigemptyset(&my_signals);
	sigaddset(&my_signals, SIGINT);
	sigaddset(&my_signals, SIGUSR1);
	sigaddset(&my_signals, SIGUSR2);
	sigredirect.sa_mask = my_signals;
	if (sigaction(SIGINT, &sigredirect, 0) == -1 || \
		sigaction(SIGUSR1, &sigredirect, 0) == -1 || \
		sigaction(SIGUSR2, &sigredirect, 0) == -1)
		error_case("\033[0;33mSigaction failed\033[0m\n", -2);
	while (1)
		;
}
