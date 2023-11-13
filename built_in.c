#include "shell.h"

/**
 * exit_sh - Exit the shell.
 * @info: Structure containing potential arguments.
 *
 * Return: Exits with a given exit status (0) if info->argv[0] != "exit".
 */
int exit_sh(info_t *info)
{
	int exit_check;

	if (info->argv[1]) /* If there is an exit argument */
	{
		exit_check = conv_str_int(info->argv[1]);
		if (exit_check == -1)
		{
			info->status = 2;
			prnt_my_err(info, "Illegal number: ");
			_eputs(info->argv[1]);
			_eputchar('\n');
			return (1);
		}
		info->err_num = conv_str_int(info->argv[1]);
		return (-2);
	}
	info->err_num = -1;
	return (-2);
}

/**
 * cd_dir - Change the current directory.
 * @info: Structure containing potential arguments.
 *
 * Return: Always 0.
 */
int cd_dir(info_t *info)
{
	char *s, *dir, buffer[1024];
	int chdir_ret;

	s = getcwd(buffer, 1024);
	if (!s)
		_puts("TODO: >>getcwd failure emsg here<<\n");
	if (!info->argv[1])
	{
		dir = get_env(info, "HOME=");
		if (!dir)
			chdir_ret = /* TODO: what should this be? */
				chdir((dir = get_env(info, "PWD=")) ? dir : "/");
		else
			chdir_ret = chdir(dir);
	}
	else if (comp_strgs(info->argv[1], "-") == 0)
	{
		if (!get_env(info, "OLDPWD="))
		{
			_puts(s);
			_putchar('\n');
			return (1);
		}
		_puts(get_env(info, "OLDPWD=")), _putchar('\n');
		chdir_ret = /* TODO: what should this be? */
			chdir((dir = get_env(info, "OLDPWD=")) ? dir : "/");
	}
	else
		chdir_ret = chdir(info->argv[1]);
	if (chdir_ret == -1)
	{
		prnt_my_err(info, "can't cd to ");
		_eputs(info->argv[1]), _eputchar('\n');
	}
	else
	{
		init_n_env(info, "OLDPWD", get_env(info, "PWD="));
		init_n_env(info, "PWD", getcwd(buffer, 1024));
	}
	return (0);
}

/**
 * help_info - Display help information.
 * @info: Structure containing potential arguments.
 *
 * Return: Always 0.
 */
int help_info(info_t *info)
{
	char **arg_array;

	arg_array = info->argv;
	_puts("help call works. Function not yet implemented \n");
	if (0)
		_puts(*arg_array); /* Temporarily unused workaround */
	return (0);
}
