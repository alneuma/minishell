int	ft_atoi(const char *nptr)
{
	int	n;
	int	sign;

	n = 0;
	sign = 1;
	while (*nptr
		&& (*nptr == ' ' || *nptr == '\f' || *nptr == '\n'
			|| *nptr == '\r' || *nptr == '\t' || *nptr == '\v'))
		nptr++;
	if (!*nptr)
		return (0);
	if (*nptr == '-' || *nptr == '+')
		sign -= 2 * (*nptr++ == '-');
	while (*nptr >= '0' && *nptr <= '9')
		n = 10 * n + *nptr++ - '0';
	return (sign * n);
}
