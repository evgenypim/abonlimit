#define ABONLIMIT_PRIV(x) ((struct xt_abonlimit_info *)(x))

#include <linux/module.h>
#include <linux/skbuff.h>
#include <linux/version.h>
#include <linux/netfilter/x_tables.h>
#include "xt_abonlimit.h"
#include "ip_hash_tables.h"

MODULE_AUTHOR("Evgeny Pimenov <e.pimenov@carbonsoft.ru>");
MODULE_DESCRIPTION("Xtables: limit per abonent packets");
MODULE_LICENSE("GPL");

#if LINUX_VERSION_CODE <= KERNEL_VERSION(2, 6, 32)
static bool abonlimit_mt(const struct sk_buff *skb, const struct xt_match_param *par)
#else
static bool abonlimit_mt(const struct sk_buff *skb, struct xt_action_param *par)
#endif
{
	const struct xt_abonlimit_info *abonlimit_info = par->matchinfo;
	printk("--!abonlimit_mt, %p", abonlimit_info);
	return true;
}


static int abonlimit_mt_check(const struct xt_mtchk_param *par)
{
	struct xt_abonlimit_info *abonlimit_info = par->matchinfo;
	int rez = ip_hash_table_init(abonlimit_info->ip_htbl)
	printk("--!abonlimit_mt_check %p", abonlimit_info);
	printk("--!ip ht init returns %d", 
	return true;
}

static void abonlimit_mt_destroy(const struct xt_mtdtor_param *par)
{
	struct xt_abonlimit_info *abonlimit_info = ABONLIMIT_PRIV(par->matchinfo);
	printk("--!abonlimit_mt_destroy, %p", abonlimit_info);
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

static int __init abonlimit_mt_init(void) {
	printk(KERN_ERR "--!abonlimit_mt_init");
	return xt_register_matches(xt_abonlimit_mt_reg, ARRAY_SIZE(xt_abonlimit_mt_reg));
}

static void __exit abonlimit_mt_exit(void) {
	printk(KERN_ERR "--!abonlimit_mt_exit");
	xt_unregister_matches(xt_abonlimit_mt_reg, ARRAY_SIZE(xt_abonlimit_mt_reg));
}


