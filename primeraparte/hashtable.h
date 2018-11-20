#ifndef BRANDAN_COSTAMAGNA_DIARTE_HASHTABLE_H_
#define BRANDAN_COSTAMAGNA_DIARTE_HASHTABLE_H_

typedef struct DataItem *ht;

ht* hash_create(u32 size);
// return SIZE si no lo encuentra.
// si lo encuentra devuelve la etiqueta (el data).
u32 search(ht *htable, u32 size, u32 key);

void insert(ht *htable, u32 size, u32 key, u32 data);

void delete_ht(ht *htable, u32 size);

void display(ht *htable, u32 size);

#endif  // BRANDAN_COSTAMAGNA_DIARTE_HASHTABLE_H_
