#ifndef TARGET_PUT_UTILS_H
# define TARGET_PUT_UTILS_H

char	get_sign(int n, t_spec *spec);
int		get_digits(unsigned long un, t_spec *spec);
void	target_putdigits(t_target *target,
			t_spec *spec, unsigned long un, int num_digits);
void	target_write_nullptr(t_target *target, t_spec *spec);
void	balance_digits_width(int *digits, t_spec *spec);

#endif //TARGET_PUT_UTILS_H
