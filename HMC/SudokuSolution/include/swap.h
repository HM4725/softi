#ifndef __SWAP_H__
#define __SWAP_H__

#define SWAP(a, b)			\
	do {					\
		Box* tmp;			\
		int tmp_idx;		\
		tmp = a;			\
		a = b;				\
		b = tmp;			\
		tmp_idx = a->idx;	\
		a->idx = b->idx;	\
		b->idx = tmp_idx;	\
	} while(0)

#endif /* SWAP_H */
