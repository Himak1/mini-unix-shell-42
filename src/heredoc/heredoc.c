/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   heredoc.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: jhille <jhille@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/17 17:05:29 by jhille        #+#    #+#                 */
/*   Updated: 2022/09/12 17:20:03 by jhille        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <sys/wait.h>
#include <signal.h>
#include "parser.h"
#include "heredoc.h"

static t_ast	*next_exec_block(t_ast *exec_block)
{
	exec_block = exec_block->next_sib_node;
	if (exec_block)
		exec_block = exec_block->next_sib_node;
	return (exec_block);
}

int	single_heredoc(char *tmp_filepath, t_ast *rd, char *envv[], int i)
{
	char	*tmp_file;
	int		file_fd;
	int		input_pipe[2];
	int		pid;

	if (rd->type == RD_DE)
	{
		tmp_file = create_tmp_filename(tmp_filepath, i);
		file_fd = open(tmp_file, O_CREAT | O_WRONLY, 0666);
		signal(SIGINT, SIG_IGN);
		pipe(input_pipe);
		pid = fork();
		if (pid == 0)
			read_write_to_tmp(rd->child_node->next_sib_node->value, \
							file_fd, envv);
		dup2(input_pipe[0], file_fd);
		close(input_pipe[0]);
		close(input_pipe[1]);
		wait(0);
		close(file_fd);
		free(rd->child_node->next_sib_node->value);
		rd->child_node->next_sib_node->value = tmp_file;
		return (i + 1);
	}
	return (i);
}

/*
int	single_heredoc(char *tmp_filepath, t_ast *rd, char *envv[], int i)
{
	char	*tmp_file;
	int		file_fd;

	if (rd->type == RD_DE)
	{
		tmp_file = create_tmp_filename(tmp_filepath, i);
		file_fd = open(tmp_file, O_CREAT | O_WRONLY, 0666);
		read_write_to_tmp(rd->child_node->next_sib_node->value, \
						file_fd, envv);
		close(file_fd);
		free(rd->child_node->next_sib_node->value);
		rd->child_node->next_sib_node->value = tmp_file;
		return (i + 1);
	}
	return (i);
}
*/

void	handle_all_heredocs(t_ast *exec_block, char *envv[])
{
	char	*tmp_filepath;
	t_ast	*rd_iter;
	int		i;

	i = 0;
	tmp_filepath = find_tmp_filepath();
	while (exec_block)
	{
		rd_iter = get_rd(exec_block);
		while (rd_iter)
		{
			i = single_heredoc(tmp_filepath, rd_iter, envv, i);
			rd_iter = rd_iter->next_sib_node;
		}
		exec_block = next_exec_block(exec_block);
	}
}
