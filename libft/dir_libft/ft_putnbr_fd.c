#include <unistd.h>

static void	putnbr_rec(unsigned int nu, int fd);

void	ft_putnbr_fd(int n, int fd)
{
	unsigned int	nu;

	if (n < 0)
	{
		nu = 1 + (unsigned int)(-(n + 1));
		write(fd, "-", 1);
	}
	else
		nu = (unsigned int)n;
	putnbr_rec(nu, fd);
}

static void	putnbr_rec(unsigned int nu, int fd)
{
	if (nu > 9)
		putnbr_rec(nu / 10, fd);
	nu = nu % 10 + '0';
	write(fd, &nu, 1);
}
