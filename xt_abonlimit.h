#ifndef _XT_ABONLIMIT_H
#define _XT_ABONLIMIT_H

#include <linux/types.h>
#include "ip_hash_tables.h"
// Тут надо объявить структуру абонента, лимиты, и прочее, что надо для STB
//

#define ABONLIMIT_PRIV(x) ((struct xt_abonlimit_info *)(x))

struct xt_abonlimit_info {
	const struct rhashtable *ip_htbl;
	int period;
	int limit;
};

#endif

