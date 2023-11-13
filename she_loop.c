#include "shell.h"

/**
 * hsh - main shell loop
 * @info: parameter & return info struct
 * @av: argument vector from main()
 *
 * Return: 0 on success, 1 on error, or error code
 */
int hsh(info_t *info, char **av)
{
	ssize_t r = 0;
	int builtin_ret = 0;

	while (r != -1 && builtin_ret != -2)
	{
		init_struct(info);
		if (interact_mode(info))
			_puts("$ ");
		_eputchar(BUF_FLUSH);
		r = gets_input(info);
		if (r != -1)
		{
			set_struct(info, av);
			builtin_ret = find_built_cmd(info);
			if (builtin_ret == -1)
				find_exec(info);
		}
		else if (interact_mode(info))
			_putchar('\n');
		free_struct_fld(info, 0);
	}
	write_hist(info);
	free_struct_fld(info, 1);
	if (!interact_mode(info) && info->status)
		exit(info->status);
	if (builtin_ret == -2)
	{
		if (info->err_num == -1)
			exit(info->status);
		exit(info->err_num);
	}
	return (builtin_ret);
}

/**
 * find_built_cmd - find a builtin commnd
 * @info: parameter & return info struct
 *
 * Return: -1 if builtin not found,
 * 0 if builtin executed successfully,
 * 1 if builtin found but not successful,
 * 2 if builtin signals exit()
 */
int find_built_cmd(info_t *info)
{
	int i, built_in_ret = -1;
	builtin_table builtintbl[] = {
		{"exit", exit_sh},
		{"env", sh_env},
		{"help", help_info},
		{"history", sh_history},
		{"setenv", setup_env},
		{"unsetenv", rm_env},
		{"cd", cd_dir},
		{"alias", my_alias},
		{NULL, NULL}
	};

	for (i = 0; builtintbl[i].type; i++)
		if (comp_strgs(info->argv[0], builtintbl[i].type) == 0)
		{
			info->line_count++;
			built_in_ret = builtintbl[i].func(info);
			break;
		}
	return (built_in_ret);
}

/**
 * find_exec- find a commnd in PATH
 * @info: parameter & return info struct
 *
 * Return: void
 */
void find_exec(info_t *info)
{
	char *path = NULL;
	int i, k;

	info->path = info->argv[0];
	if (info->linecount_flag == 1)
	{
		info->line_count++;
		info->linecount_flag = 0;
	}
	for (i = 0, k = 0; info->arg[i]; i++)
		if (!is_del(info->arg[i], " \t\n"))
			k++;
	if (!k)
		return;

	path = find_cmd_pth(info, get_env(info, "PATH="), info->argv[0]);
	if (path)
	{
		info->path = path;
		fork_thread(info);
	}
	else
	{
		if ((interact_mode(info) || get_env(info, "PATH=")
					|| info->argv[0][0] == '/') && cmd_file(info, info->argv[0]))
			fork_thread(info);
		else if (*(info->arg) != '\n')
		{
			info->status = 127;
			prnt_my_err(info, "not found\n");
		}
	}
}

/**
 * fork_thread - fork an exec thread to run cmd
 * @info: parameter & return info struct
 *
 * Return: void
 */
void fork_thread(info_t *info)
{
	pid_t child_pid;

	child_pid = fork();
	if (child_pid == -1)
	{
		/* TODO: PUT ERROR FUNCTION */
		perror("Error:");
		return;
	}
	if (child_pid == 0)
	{
		if (execve(info->path, info->argv, get_env_array(info)) == -1)
		{
			free_struct_fld(info, 1);
			if (errno == EACCES)
				exit(126);
			exit(1);
		}
		/* TODO: PUT ERROR FUNCTION */
	}
	else
	{
		wait(&(info->status));
		if (WIFEXITED(info->status))
		{
			info->status = WEXITSTATUS(info->status);
			if (info->status == 126)
				prnt_my_err(info, "Permission denied\n");
		}
	}
}
