/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   exit.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: tvan-der <tvan-der@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/15 10:09:22 by tvan-der      #+#    #+#                 */
/*   Updated: 2022/09/21 15:40:00 by jhille        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

//exit 2 miljoen %205 rest

#include "utils.h"
#include "parser.h"

// exit [N]     ->      terminates the current shell (or script).
// If N is given, the return code to the parent process is set to N. 
// If not, the returned status the the status of the most recently executed command (i.e. $?).
// exit status: 255, invalid (e.g. non-numeric) argument - this staus is returned to the parent

// exit (no args)
// -> prints "exit" on stderr
// -> sets exit_code to 0
// -> exits the shell

// static void exit()
// {

// }

// exit (with valid arg N)
// -> prints "exit" on stderr
// -> sets exit_code to N
// -> exits the shell 

// exit (with invalid arg N -> non numeric)
// -> prints "exit" on stderr
// -> prints error message "bash: exit: a: numeric argument required"
// -> sets exit_code to 255
// -> exits the shell

// exit (with invalid arg N -> too many args)
// -> prints "exit" on stderr
// -> prints error message "bash: exit: a: numeric argument required"
// -> sets exit_code to 1
// -> DOES NOT EXIT THE SHELL

// static void exit_with_args(t_ast *args)
// {

// }

// int exec_exit(t_ast *cmd, char **envv[])
// {
//     if (!cmd->next_sib_node)
//         exit();
//     else
//         exit_with_args(cmd->next_sib_node);
// }