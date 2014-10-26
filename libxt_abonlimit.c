#define _GNU_SOURCE 1
#include <stdio.h>
#include <netdb.h>
#include <string.h>
#include <stdlib.h>
#include <getopt.h>
#include <ctype.h>
#include <xtables.h>
#include <stddef.h>
#include <linux/netfilter/xt_abonlimit.h>

// #define ABONLIMIT_PRIV(x) ((struct xt_abonlimit_info *)(x))

static void abonlimit_help(void)
{
	printf("abonlimit match options:\n"
			"comming soon\n");
}

static const struct option abonlimit_opts[] = {
	{.name = NULL}
};

static void abonlimit_init(struct xt_entry_match *m)
{
	struct xt_abonlimit_info *abonlimit_info = ABONLIMIT_PRIV(m->data);
}

static int abonlimit_parse(int c, char **argv, int invert, unsigned int *flags, const void *entry, struct xt_entry_match **match)
{
	struct xt_abonlimit_info *stringinfo = ABONLIMIT_PRIV((*match)->data);
	return 1;
}

static void abonlimit_check(unsigned int flags)
{
	xtables_error(PARAMETER_PROBLEM,
				"abonlimit match: problem ");
}

static void abonlimit_print(const void *ip, const struct xt_entry_match *match, int numeric)
{
	const struct xt_abonlimit_info *info =	ABONLIMIT_PRIV(match->data);
	printf("abonlimit print");
}

static void abonlimit_save(const void *ip, const struct xt_entry_match *match)
{
	const struct xt_abonlimit_info *info = ABONLIMIT_PRIV(match->data);
	printf("abonlimit_save");
}

static struct xtables_match abonlimit_mt_reg[] = {
	{
		.name = "abonlimit",
		.revision = 0,
		.family = NFPROTO_UNSPEC,
		.version = XTABLES_VERSION,
		.size = XT_ALIGN(sizeof(struct xt_abonlimit_info)),
		.userspacesize = offsetof(struct xt_abonlimit_info, info_string),
		.help = abonlimit_help,
		.init = abonlimit_init,
		.parse = abonlimit_parse,
		.final_check = abonlimit_check,
		.print = abonlimit_print,
		.save = abonlimit_save,
		.extra_opts = abonlimit_opts,
	},
};

void _init(void)
{
	xtables_register_matches(abonlimit_mt_reg, ARRAY_SIZE(abonlimit_mt_reg));
}

