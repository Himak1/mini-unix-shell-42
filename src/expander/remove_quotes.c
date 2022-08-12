/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   remove_quotes.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: tvan-der <tvan-der@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/10 14:29:27 by tvan-der      #+#    #+#                 */
/*   Updated: 2022/08/11 15:24:45 by tvan-der      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "expander.h"
#include "lexer.h"

int len_filtered_quotes(char *value)
{
    int count;
    int quote_type;

    count = 0;
    quote_type = 0;
    while (*value)
    {
        if (*value == '\'' || *value == '\"')
        {
            if (quote_type && *value != quote_type)
              count++;
            else if (quote_type && *value == quote_type)
              quote_type = 0;
            else
              quote_type = *value;
            value++;
        }
        while (*value && *value != '\'' && *value != '\"')
        {
            count++;
            value++;
        }
    }
    return (count);
}


void    copy_filtered_quotes(char *new_value, char *old_value, size_t size)
{
    size_t i;
    size_t j;
    int quote_type;

    i = 0;
    j = 0;
    quote_type = 0;
    while (old_value[i] && j < (size + 1))
    {
        if (old_value[i] == '\'' || old_value[i] == '\"')
        {
            if (quote_type && old_value[i] != quote_type)
            {
              new_value[j] = old_value[i];
              j++;
            }
            else if (quote_type && old_value[i] == quote_type)
              quote_type = 0;
            else
              quote_type = old_value[i];
            i++;
        }
        while (old_value[i] && old_value[i] != '\'' && old_value[i] != '\"' && j < (size + 1))
        {
            new_value[j] = old_value[i];
            i++;
            j++;
        }
    }
    new_value[j] = '\0';
}

char	*remove_quotes(char *value)
{
	size_t		count;
	char	*new_value;

	count = len_filtered_quotes(value);
	if (count == ft_strlen(value))
	{
		new_value = ft_strdup(value);
		free(value);
		return (new_value);
	}
	new_value = (char *)malloc(sizeof(char) * (count + 1));
	if (!new_value)
		return (NULL);
	copy_filtered_quotes(new_value, value, (count + 1));
	return (new_value);
}