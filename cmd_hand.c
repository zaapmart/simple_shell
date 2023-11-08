#include "shell.h"

/**
 * _my_exit - Exit the shell.
 * @sh_info: Structure containing potential arguments.
 *
 * Return: Exits with a given exit status (0) if sh_info->argv[0] != "exit".
 */
int _my_exit(info_t *sh_info)
{
	int exitCode;

	if (sh_info->argv[1]) /* If there is an exit argument */
	{
		exitCode = _erratoi(sh_info->argv[1]);
		if (exitCode == -1)
		{
			sh_info->status = 2;
			print_error(sh_info, "Illegal number: ");
			_eputs(sh_info->argv[1]);
			_eputchar('\n');
			return (1);
		}
		sh_info->err_num = _erratoi(sh_info->argv[1]);
		return (-2);
	}
	sh_info->err_num = -1;
	return (-2);
}

/**
 * _mycd - Change the current directory.
 * @sh_info: Structure containing potential arguments.
 *
 * Return: Always 0.
 */
int _mycd(info_t *sh_info)
{
	char *curr_dir, *trgt_dir, pth_buffer[1024];
	int chdir_ret;

	curr_dir = getcwd(pth_buffer, 1024);
	if (!curr_dir)
		_puts("TODO: >>getcwd failure emsg here<<\n");
	if (!sh_info->argv[1])
	{
		trgt_dir = _getenv(sh_info, "HOME=");
		if (!trgt_dir)
			chdir_ret = /* TODO: what should this be? */
				chdir((trgt_dir = _getenv(sh_info, "PWD=")) ? trgt_dir : "/");
		else
			chdir_ret = chdir(trgt_dir);
	}
	else if (_strcmp(sh_info->argv[1], "-") == 0)
	{
		if (!_getenv(sh_info, "OLDPWD="))
		{
			_puts(curr_dir);
			_putchar('\n');
			return (1);
		}
		_puts(_getenv(sh_info, "OLDPWD=")), _putchar('\n');
		chdir_ret = /* TODO: what should this be? */
			chdir((trgt_dir = _getenv(sh_info, "OLDPWD=")) ? trgt_dir : "/");
	}
	else
		chdir_ret = chdir(info->argv[1]);
	if (chdir_ret == -1)
	{
		print_error(sh_info, "can't cd to ");
		_eputs(sh_info->argv[1]), _eputchar('\n');
	}
	else
	{
		_setenv(sh_info, "OLDPWD", _getenv(sh_info, "PWD="));
		_setenv(sh_info, "PWD", getcwd(pth_buffer, 1024));
	}
	return (0);
}

/**
 * _myhelp - Display help information.
 * @sh_info: Structure containing potential arguments.
 *
 * Return: Always 0.
 */
int _myhelp(info_t *sh_info)
{
	char **argumt_array;

	argumt_array = sh_info->argv;
	_puts("help call works. Function not yet implemented \n");
	if (0)
		_puts(*argumt_array); /* Temporarily unused workaround */
	return (0);
}
