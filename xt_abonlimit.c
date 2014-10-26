#define ABONLIMIT_PRIV(x) ((struct xt_abonlimit_info *)(x))

#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/skbuff.h>
#include <linux/netfilter/x_tables.h>

MODULE_AUTHOR("Evgeny Pimenov <e.pimenov@carbonsoft.ru>");
MODULE_DESCRIPTION("Xtables: limit per abonent packets");
MODULE_LICENSE("GPL");


static bool abonlimit_mt(const struct sk_buff *skb, const struct xt_match_param *par)
{
	const struct xt_abonlimit_info *abonlimit_info = ABONLIMIT_PRIV(par->matchinfo);
	printk("--!abonlimit_mt");
	return true;
}


static bool abonlimit_mt_check(const struct xt_mtchk_param *par)
{
	struct xt_abonlimit_info *abonlimit_info = ABONLIMIT_PRIV(par->matchinfo);
	printk("--!abonlimit_mt_check");
	return true;
}

static void abonlimit_mt_destroy(const struct xt_mtdtor_param *par)
{
	printk("--!abonlimit_mt_destroy")
	struct xt_abonlimit_info *abonlimit_info = ABONLIMIT_PRIV(par->matchinfo);
}

static struct xt_match xt_abonlimit_mt_reg[] __read_mostly = {
	{
		.name = "abonlimit",
		.revision = 0,
		.family = NFPROTO_UNSPEC,
		.checkentry = abonlimit_mt_check,
		.match = abonlimit_mt,
		.destroy = abonlimit_mt_destroy,
		.matchsize = sizeof(struct xt_abonlimit_info),
		.me = THIS_MODULE
	}
};

static int __init abonlimit_mt_init(void)
{
	printk("--!abonlimit_mt_init");
	return xt_register_matches(xt_abonlimit_mt_reg,
			ARRAY_SIZE(xt_abonlimit_mt_reg));
}

static void __exit abonlimit_mt_exit(void)
{
	xt_unregister_matches(xt_abonlimit_mt_reg,
			ARRAY_SIZE(xt_abonlimit_mt_reg));
}
