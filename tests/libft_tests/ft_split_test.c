/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_split_test.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: mynodeus <mynodeus@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/05/17 05:28:06 by mynodeus      #+#    #+#                 */
/*   Updated: 2024/08/26 16:25:39 by spenning      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../libft_tester.h"
#include <string.h>

int	g_fail_split = 0;

int	cmp_split(char **ft_result, char *test, char *delim)
{
	int		index;
	char	*alloc;
	char	*testret;

	index = 0;
	alloc = strdup(test);
	while (ft_result[index] != NULL)
	{
		testret = __strtok_r(alloc, delim, &alloc);
		if (strcmp(testret, ft_result[index]))
			return (-1);
		index++;
	}
	return (0);
}

int	split_cmp(int test_count, char *test, char *delim)
{
	if (cmp_split(ft_split(test, delim[0]), test, delim) != 0)
		g_fail_split += ft_log_str(test_count, test, delim);
	else
		printf(GRN "%d OK " RESET, test_count);
	return (0);
}

int	split_test(void)
{
	int	test_count;

	test_count = 1;
	test_count = split_cmp(test_count, "aaa;bbb,", ";");
	test_count = split_cmp(test_count, "kokokokokokokoko", "o");
	test_count = split_cmp(test_count, "hdkjsahdkjsa|hdkjsahdkjsa", "|");
	test_count = split_cmp(test_count, "aaaa////aaaa//aa///", "/");
	return (g_fail_split);
}
