/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   executor.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: jhille <jhille@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/07/27 14:44:47 by jhille        #+#    #+#                 */
/*   Updated: 2022/09/17 20:03:52 by jhille        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <sys/wait.h>
#include <signal.h>
#include "executor.h"
#include "builtins.h"

#include <stdio.h>
static int	count_cmds(t_ast *tree)
{
	t_ast	*iter;
	int		i;

	i = 0;
	iter = tree->child_node;
	while (iter)
	{
		if (iter->type == EXEC_BLOCK)
			i++;
		iter = iter->next_sib_node;
	}
	return (i);
}

/*
static inline t_ast	*prev_block(t_ast *exec_block)
{
	exec_block = exec_block->prev_sib_node;
	if (exec_block && exec_block->type == TERMINAL)
		exec_block = exec_block->prev_sib_node;
	return (exec_block);
}


static inline void	execute(t_exec *data, char *envv[])
{
	if (data->pid != 0)
		wait(0);
	if (data->cmd)
	{
		if (access(data->cmd[0], X_OK) != 0)
			exit(EXIT_FAILURE);
		execve(data->cmd[0], data->cmd, envv);
	}
	exit(0);
}
*/

static inline t_ast	*next_block(t_ast *exec_block)
{
	exec_block = exec_block->next_sib_node;
	if (exec_block)
		exec_block = exec_block->next_sib_node;
	return (exec_block);
}

static inline void	execute(t_exec *data, char *envv[])
{
	if (data->cmd)
	{
		if (access(data->cmd[0], X_OK) != 0)
			exit(EXIT_FAILURE);
		execve(data->cmd[0], data->cmd, envv);
		write(STDERR_FILENO, "Minishell: command not found\n", 29);
		exit(EXIT_FAILURE);
	}
	exit(EXIT_SUCCESS);
}

void	executor_loop(t_ast *exec_block, t_exec *data, char *envv[])
{
	t_uint	i;

	i = 0;
	while (i < data->cmd_count && exec_block)
	{
		choose_pipe(data, i);
		data->pid[i] = fork();
		if (data->pid[i] == 0)
		{
			extract_ast_data(exec_block, data);
			handle_redirects(data, i);
			execute(data, envv);
		}
		close_pipe(data, i);
		exec_block = next_block(exec_block);
		i++;
	}
}

int	executor(t_ast *tree, char **envv[])
{
	t_exec	data;
	t_ast	*first_cmd;
	int		status;

	status = 0;
	first_cmd = tree->child_node;
	data.pid = ft_xmalloc(data.cmd_count * sizeof(int));
	data.cmd_count = count_cmds(tree);
	init_pipes(data.pip1, data.pip2);
	if (!is_builtin(first_cmd, data.cmd_count))
	{
		executor_loop(first_cmd, &data, *envv);
		while (wait(NULL) != -1);
		// for (t_uint i = 0; i < data.cmd_count; i++)
		// {
		// 	waitpid(data.pid[i], &status, WUNTRACED);
		// 	if (WIFEXITED(status))
		// 	{
		// 		fprintf(stderr, "alive: %d\n", waitpid(data.pid[i], NULL, WNOHANG));
		// 		kill(data.pid[i], SIGKILL);
		// 		//fprintf(stderr, "%d\n", i);
		// 	}
		// }
	}
	else
		exec_builtin(first_cmd, *envv);
	return (WEXITSTATUS(status));
}

/*
void	executor_loop(t_ast *exec_block, t_exec *data, char *envv[])
{
	t_uint	i;

	i = data->cmd_count;
	while (i != 0 && exec_block)
	{
		choose_pipe(data, i);
		extract_ast_data(exec_block, data);
		handle_redirects(data, i);
		if (i != 1)
		{
			data->pid = fork();
			if (data->pid == -1)
				exit(EXIT_FAILURE);
			else if (data->pid != 0)
				break ;
		}
		else if (i == 1)
			break ;
		exec_block = prev_block(exec_block);
		i--;
	}
	close_pipe(data, i);
	execute(data, envv);
}

int	executor(t_ast *tree, char **envv[])
{
	t_exec	data;
	t_ast	*last_cmd;
	int		status;

	status = 0;
	last_cmd = tree->child_node;
	init_pipes(data.pip1, data.pip2);
	data.cmd_count = count_cmds(tree);
	if (!is_builtin(last_cmd, data.cmd_count))
	{
		while (last_cmd && last_cmd->next_sib_node)
			last_cmd = last_cmd->next_sib_node;
		data.pid = fork();
		if (data.pid == 0)
			executor_loop(last_cmd, &data, *envv);
		waitpid(data.pid, &status, 0);
	}
	else
		exec_builtin(last_cmd, *envv);
	return (WEXITSTATUS(status));
}
*/
