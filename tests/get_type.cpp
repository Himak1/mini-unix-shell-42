/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_type.cpp                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: jhille <jhille@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/07/01 15:11:02 by jhille        #+#    #+#                 */
/*   Updated: 2022/07/01 15:25:53 by jhille        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "gtest/gtest.h"

extern "C" {
#include "lexer.h"
#include "utils.h"
}

TEST(get_type, word)
{
	ASSERT_EQ(get_type("cat"), WORD);
	ASSERT_EQ(get_type("$,"), WORD);
	ASSERT_EQ(get_type("$."), WORD);
}

TEST(get_type, environment_var)
{
	ASSERT_EQ(get_type("$s"), ENV_V);
	ASSERT_EQ(get_type("$aDa"), ENV_V);
}

TEST(get_type, environment_var)
{
	ASSERT_EQ(get_type("$s"), ENV_V);
	ASSERT_EQ(get_type("$aDa"), ENV_V);
}
