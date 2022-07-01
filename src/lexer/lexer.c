/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   lexer.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: tvan-der <tvan-der@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/06/29 15:37:18 by tvan-der      #+#    #+#                 */
/*   Updated: 2022/07/01 15:48:52 by jhille        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "lexer.h"
#include "utils.h"

// lexer function: iterate through inputstring (int i)
//   ---> if whitespace is found jump into create_token function
//   ---> if single or double quote is found jump into find_close_quote function (count with int pos_open_quote)
//			---> search for the second single or double quote
//			---> return index of second single or double quote (int pos_close_quote)
//			i++;

// Info to save:
// - position of the first occurrence single and double quote.
// - position of the closing single or double quote

void	create_token(t_token **token_list, char *str, int start, int end)
{
	t_uint type;
	char *value;
	size_t len;
	t_token *new;

	len = end - start + 1;
	type = 0; //get_type(str) function
	value = ft_substr(str, start, len);
	new = lst_new(type, value);
	if (*token_list == NULL)
		*token_list = new;
	else
		lst_add_bk(token_list, new);
}

void	ft_lexer(t_token **token_list, char *input)
{
	int	i;
	int	start;

	i = 0;
	start = 0;
	while (input[i] != '\0')
	{
		if (input[i + 1] == '\0')
			create_token(token_list, input, start, i); // add start variable
		if (input[i] == ' ' || input[i] == '\t')
		{
			create_token(token_list, input, start, i);
			start = i + 1;
		}
		i++;
	}
}

void	print_token_list(t_token **token)
{
	int	i;

	i = 1;
	while (*token != NULL)
	{
		printf("Token %d:\n", i);
		printf("------------\n");
		printf("type = %d\n", (*token)->type);
		printf("value = %s\n\n", (*token)->value);
		i++;
		*token = (*token)->next;
	}
}

/*
int main()
{
	t_token *token = NULL;
	char *simple_input = "echo hello echo hi";

	ft_lexer(&token, simple_input);
	print_token_list(&token);
	//ft_lexer(input);
}
*/


























	//char *input = "echo \"hello &&\" && echo hi";
	//char *simple_input = "echo hello";


	//int pos_open_quote;
	//int pos_close_quote;


		// if (input[i] == ' ' || input[i] == '\t' || input[i+1] != '\0')
		// {	
		// 	create_token()
			
		// }
		// pos_open_quote = 0;
		// pos_close_quote = 0;

		// if (input[i] == '\'' || input[i] == '\"')
		// {
		// 	pos_open_quote = i;
		// 	printf("first single or double quote was found on index %d\n", pos_open_quote);
		// 	printf("jump into find_close quote funtion\n");
		// }