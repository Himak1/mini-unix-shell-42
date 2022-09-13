/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   heredoc.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: jhille <jhille@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/17 17:05:29 by jhille        #+#    #+#                 */
/*   Updated: 2022/09/13 17:12:07 by jhille        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <sys/wait.h>
#include <signal.h>
#include "parser.h"
#include "heredoc.h"

#include <stdio.h>
static t_ast	*next_exec_block(t_ast *exec_block)
{
	exec_block = exec_block->next_sib_node;
	if (exec_block)
		exec_block = exec_block->next_sib_node;
	return (exec_block);
}

static int	fork_for_input(t_ast *rd_de_term, char *envv[], int file_fd)
{
	int	pid;
	int	in_pipe[2];
	int	status;

	pipe(in_pipe);
	pid = fork();
	if (pid == 0)
	{
		close(file_fd);
		read_write_to_tmp(rd_de_term->value, in_pipe, file_fd, envv);
	}
	fprintf(stderr, "%d\n", file_fd);
	dup2(in_pipe[0], file_fd);
	close(in_pipe[0]);
	close(in_pipe[1]);
	waitpid(pid, &status, 0);
	return (WEXITSTATUS(status));
}

int	single_heredoc(char *tmp_filepath, t_ast *rd, char *envv[], int i)
{
	char	*tmp_file;
	int		file_fd;
	int		status;

	if (rd->type != RD_DE)
		return (i);
	tmp_file = create_tmp_filename(tmp_filepath, i);
	file_fd = open(tmp_file, O_CREAT | O_WRONLY, 0666);
	status = fork_for_input(rd->child_node->next_sib_node, envv, file_fd);
	close(file_fd);
	free(rd->child_node->next_sib_node->value);
	rd->child_node->next_sib_node->value = tmp_file;
	if (status == EXIT_FAILURE)
		return (-1);
	return (i + 1);
}

int	handle_all_heredocs(t_data *data)
{
	t_ast	*exec_block;
	char	*tmp_filepath;
	t_ast	*rd_iter;
	int		i;

	i = 0;
	exec_block = data->tree->child_node;
	signal(SIGINT, SIG_IGN);
	tmp_filepath = find_tmp_filepath();
	while (exec_block)
	{
		rd_iter = get_rd(exec_block);
		while (rd_iter)
		{
			i = single_heredoc(tmp_filepath, rd_iter, data->envv, i);
			if (i == -1)
			{
				free(tmp_filepath);
				return (-1);
			}
			rd_iter = rd_iter->next_sib_node;
		}
		exec_block = next_exec_block(exec_block);
	}
	free(tmp_filepath);
	sigaction(SIGINT, &data->sigint_h, NULL);
	return (0);
}
