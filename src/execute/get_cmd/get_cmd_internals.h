#ifndef GET_CMD_INTERNALS_H
# define GET_CMD_INTERNALS_H

int	test_cmd(char **cmd, const char *str, const char *path);
int	get_pathv(char ***pathv, t_env *env);

#endif //GET_CMD_INTERNALS_H
