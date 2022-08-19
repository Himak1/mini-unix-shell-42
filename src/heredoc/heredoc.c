/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   heredoc.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: jhille <jhille@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/17 17:05:29 by jhille        #+#    #+#                 */
/*   Updated: 2022/08/19 14:47:54 by jhille        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <readline/readline.h>
#include <fcntl.h>
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
	t_ast	*node;
	char	*tmp_file;
	int		file_fd;

	if (rd->type== RD_DE)
	{
		node = rd->child_node->next_sib_node;
		tmp_file = create_tmp_filename(tmp_filepath, i);
		file_fd = open(tmp_file, O_CREAT | O_WRONLY, 0666);
		read_write_to_tmp(node->value, \
						file_fd, envv);
		close(file_fd);
		free(node->value);
		node->value = tmp_file;
		return (i + 1);
	}
	return (i);
}

void	handle_all_heredocs(t_ast *exec_block, char *envv[])
{
	char	*tmp_filepath;
	t_ast	*rd_iter;
	int		pid;
	int		i;

	i = 0;
	pid = fork();
	if (pid == 0)
	{
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
		exit(0);
	}
	wait(0);
}

/*
void	single_heredoc(char *tmp_filepath, t_ast *rd, char *envv[], int i)
{
	t_ast	*node;
	char	*tmp_file;
	int		file_fd;

	node = rd_iter->child_node->next_sib_node;
	tmp_file = create_tmp_filename(tmp_filepath, i);
	file_fd = open(tmp_file, O_CREAT | O_WRONLY, 0666);
	read_write_to_tmp(node->value, \
					file_fd, envv);
	close(file_fd);
	free(node->value);
	node->value = tmp_file;
}
*/

/*
void	handle_all_heredocs(t_ast *exec_block, char *envv[])
{
	t_ast	*rd_iter;
	char	*tmp_filepath;
	int		i;

	i = 0;
	tmp_filepath = find_tmp_filepath();
	while (exec_block)
	{
		rd_iter = get_rd(exec_block);
		while (rd_iter)
		{
			if (rd_iter->type == RD_DE)
			{
				single_heredoc(tmp_filepath, rd_iter, envv, i);
				rd_iter = rd_iter->next_sib_node;
				i++;
			}
		}
		exec_block = next_exec_block(exec_block);
	}
	free(tmp_filepath);
}
*/
