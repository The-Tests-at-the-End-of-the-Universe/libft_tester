/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_memcmp_test.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: spenning <spenning@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/05/16 15:01:27 by spenning      #+#    #+#                 */
/*   Updated: 2024/10/06 21:29:04 by mynodeus      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <libft_tester.h>
#include <string.h>

int							g_fail_memcmp = 0;

typedef struct s_memcmp_test
{
	char	*test;
	char	*test2;
	int		n;
}	t_memcmp_test;

static const t_memcmp_test	g_tests[] = {
[ZERO] = {"fnjkdvbs", "fnjkdvbs", 5},
[ONE] = {"    scnaocuw9/", "    scnaocuw9/", 20},
[TWO] = {"fnjkdvbs", "fnjkdvss", 20},
[THREE] = {"snsicnsk sjknsjanc", "snsicnsk sjknsjanc", 10},
[FOUR] = {"fnjkdvbs\n", "fnjkdvbs\n", 10},
[FIVE] = {"fnjkdvbs\n", "fnjkdvbs\n", 15},
[SIX] = {"fnjkdvb0", "fnjkdvb0", 10},
[SEVEN] = {"NULL", "NULL", 0},
};

void	memcmp_fork(int test_count, pid_t *child, \
int (*f)(const void *, const void *, size_t n))
{
	*child = fork();
	if (*child == -1)
		exit(1);
	if (*child == 0)
	{
		f(g_tests[test_count].test, g_tests[test_count].test2, g_tests[test_count].n);
		exit(0);
	}
}
int	memcmp_cmp(int test_count)
{
	pid_t	childs[2];
	int		ft;
	int		org;

	memcmp_fork(test_count, &childs[0], &memcmp);
	memcmp_fork(test_count, &childs[1], &ft_memcmp);
	if (wait_child(childs[0]) != wait_child(childs[1]))
		return (printf(RED " SEGFAULT "RESET));
	ft = ft_memcmp(g_tests[test_count].test, g_tests[test_count].test2, g_tests[test_count].n);
	org = memcmp(g_tests[test_count].test, g_tests[test_count].test2, g_tests[test_count].n);
	if (ft != org)
	{
		g_fail_memcmp += ft_log_int(test_count, org, ft);
		dprintf(2, "tcase: [1] %s [2] %s [n] %d\n", g_tests[test_count].test, \
		g_tests[test_count].test2, g_tests[test_count].n);
	}
	return (0);
}

int	memcmp_test(int test_count)
{
	if (test_count == sizeof(g_tests) / sizeof(g_tests[0]))
		return (FINISH);
	memcmp_cmp(test_count);
	return (g_fail_memcmp);
}
