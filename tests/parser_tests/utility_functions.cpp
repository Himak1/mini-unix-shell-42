/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utility_functions.cpp                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: jhille <jhille@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/07/05 16:55:08 by jhille        #+#    #+#                 */
/*   Updated: 2022/07/13 14:15:16 by jhille        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "gtest/gtest.h"

extern "C" {
#include "parser.h"
#include "utils.h"
}

t_token *create_list(void)
{
	t_token *t1;
	t_token *t2;
	t_token *t3;
	t_token *t4;

	t1 = lst_new(RDR_IN, ft_strdup("<"));
	t2 = lst_new(WORD, ft_strdup("infile"));
	t3 = lst_new(WORD, ft_strdup("echo"));
	t4 = lst_new(WORD, ft_strdup("hello"));
	lst_add_bk(&t1, t2);
	lst_add_bk(&t1, t3);
	lst_add_bk(&t1, t4);
	return (t1);
}

TEST(peek_tkn, basic)
{
	t_token	*lst = create_list();

	EXPECT_EQ(peek_tkn(lst), RDR_IN);
}

TEST(next_2_tkn, basic)
{
	t_token	*lst = create_list();

	ASSERT_EQ(lst->type, RDR_IN);
	ASSERT_EQ(next_2_tkn(lst, RDR_IN, WORD), 1);
}
