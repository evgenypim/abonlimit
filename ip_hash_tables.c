#include "ip_hash_tables.h"
//#include <linux/jhash.h>
//#include <linux/slab.h>

struct ip_hash_table_elem* init_ip_hash_table_elem(int key, void* data){
	struct ip_hash_table_elem* he;
	he = kmalloc(sizeof(struct ip_hash_table_elem), GFP_KERNEL);
	he->key = key;
	he->data = data;

	return he;
}

struct ip_hash_table_elem* ip_hash_table_loockup(struct rhashtable *table, int *key) {
	// Поиск ключа key в хештаблице priv, вернет ip_hash_table_elem
	struct ip_hash_table_elem* he = rhashtable_lookup(table, key);
	return he;
}

static int ip_hash_table_insert(struct rhashtable *table, struct ip_hash_table_elem *he) {
	// Вставить he в таблицу priv
	rhashtable_insert(table, &he->node, GFP_KERNEL);
	return 0;
}

struct ip_hash_table_elem* ip_hash_table_get(const struct rhashtable *priv, int* key)
{
	const struct bucket_table *tbl = rht_dereference_rcu(priv->tbl, priv);
	struct rhash_head __rcu * const *pprev;
	struct ip_hash_table_elem *he;
	u32 h;

	h = rhashtable_hashfn(priv, key, klen);
	pprev = &tbl->buckets[h];
	rht_for_each_entry_rcu(he, tbl->buckets[h], node) {
		if (&he->key != key) {
			pprev = &he->node.next;
			continue;
		}

		return he;
	}
	return NULL;
}

static int ip_hash_table_mutex_is_held(void){
	return 1;
}

static int ip_hash_table_init(struct rhashtable *priv)
{
	struct rhashtable_params params = {
		.nelem_hint = HASH_ELEMENT_HINT,
		.head_offset = offsetof(struct ip_hash_table_elem, node),
		.key_offset = offsetof(struct ip_hash_table_elem, key),
		.key_len = klen,
		.hashfn = jhash,
		.grow_decision = rht_grow_above_75,
		.shrink_decision = rht_shrink_below_30,
		.mutex_is_held = ip_mutex_is_held,
	};

	return rhashtable_init(priv, &params);
}

static void ip_hash_table_elem_destroy(struct ip_hash_table_elem *he)
{
	kfree(he);
}

static void ip_hash_table_destroy(const struct rhashtable *priv)
{
	const struct bucket_table *tbl = priv->tbl;
	struct ip_hash_table_elem *he, *next;
	unsigned int i;

	for (i = 0; i < tbl->size; i++) {
		for (he = rht_entry(tbl->buckets[i], struct ip_hash_table_elem, node); he != NULL; he = next) {
			next = rht_entry(he->node.next, struct ip_hash_table_elem, node);
			ip_hash_table_elem_destroy(he);
		}
	}
	rhashtable_destroy(priv);
}
