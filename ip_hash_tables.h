#include <linux/rhashtable.h>

#define klen 7 
#define HASH_ELEMENT_HINT 3

struct ip_hash_table_elem {
	struct rhash_head       node;
	int			key;
	void*			data;
};

struct ip_hash_table_elem* init_ip_hash_table_elem(int key, void* data);
static int ip_hash_table_init(struct rhashtable *priv);
static int ip_hash_table_insert(struct rhashtable *table, struct ip_hash_table_elem *he);
struct ip_hash_table_elem* ip_hash_table_loockup(struct rhashtable *table, int *key);
struct ip_hash_table_elem* ip_hash_table_get(const struct rhashtable *priv, int* key);
static int ip_hash_table_mutex_is_held(void);
static void ip_hash_table_elem_destroy(struct ip_hash_table_elem *he);
static void ip_hash_table_destroy(const struct rhashtable *priv);
