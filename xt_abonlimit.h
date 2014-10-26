#ifndef _XT_ABONLIMIT_H
#define _XT_ABONLIMIT_H

#include <linux/types.h>
// Тут надо объявить структуру абонента, лимиты, и прочее, что надо для STB
//

#define ABONLIMIT_PRIV(x) ((struct xt_abonlimit_info *)(x))

struct xt_abonlimit_info {
	int period;
	int limit;
};

#endif

