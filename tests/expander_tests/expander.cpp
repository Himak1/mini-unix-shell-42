/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   expander.cpp                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: tvan-der <tvan-der@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/07/21 15:18:48 by tvan-der      #+#    #+#                 */
/*   Updated: 2022/07/21 16:24:00 by tvan-der      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "gtest/gtest.h"

extern "C" {
#include "parser.h"
#include "utils.h"
#include "expander.h"
}

TEST(create_envp, basic_test)
{
    char **envp = NULL;

    envp = create_envp();
    EXPECT_STREQ(envp[0], "CHARSET=UTF-8");
    EXPECT_STREQ(envp[1], "HOSTNAME=a4d647f5f42a");
    EXPECT_STREQ(envp[2], "PWD=/pwd/desktop/minishell");
    EXPECT_STREQ(envp[3], "HOME=/root");
    EXPECT_STREQ(envp[4], "LANG=C.UTF-8");
    EXPECT_STREQ(envp[5], "TERM=xterm");
    EXPECT_STREQ(envp[6], "SHLVL=2");
    EXPECT_STREQ(envp[7], "LC_COLLATE=C");
    EXPECT_STREQ(envp[8], "PATH=/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin");
    EXPECT_STREQ(envp[9], "OLDPWD=/pwd/desktop/minishell/build");
    EXPECT_STREQ(envp[10], "_=/usr/bin/env");
}