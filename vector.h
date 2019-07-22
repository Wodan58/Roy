/*
    module  : vector.h
    version : 1.4
    date    : 07/19/19
*/
#define vector(type)	struct { unsigned n, m; type *a; }
#define vec_init(v)	do { (v) = malloc(sizeof(*(v))); (v)->n = 0; (v)->m = 1; \
			(v)->a = malloc(sizeof(*(v)->a) * (v)->m); } while (0)
#define vec_top(v)	((v)->a + (v)->n - 1)
#define vec_push(v)	(((v)->n++ == (v)->m) ? ((v)->a = realloc((v)->a, \
			sizeof(*(v)->a) * ((v)->m <<= 1))), vec_top(v) : vec_top(v))
#define vec_add(v, w)	(*vec_push(v) = (w))
#define vec_size(v)	((v) ? (v)->n : -1)
#define vec_capacity(v)	((v)->m)
#define vec_index(v, i)	((v)->a + (i))
#define vec_at(v, i)	((v)->a[i])
#define vec_back(v)	((v)->a[(v)->n - 1])
#define vec_overtop(v)	((v)->a + (v)->n)
#define vec_subtop(v)	((v)->a + (v)->n - 2)
#define vec_pop(v)	((v)->a + --(v)->n)
#define vec_pop_back(v)	(--(v)->n)
#define vec_empty(v)	(!(v)->n)
#define vec_clear(v)	((v)->n = 0)
#define vec_equal(v, w)	((v)->n == (w)->n && !memcmp((v)->a, (w)->a, \
			sizeof(*(v)) * (v)->n))
#define vec_copy(v, w)	do { (w) = malloc(sizeof(*(w))); (w)->n = (w)->m = (v)->n; \
			(w)->a = malloc(sizeof(*(w)->a) * (w)->m); memcpy((w)->a,  \
			(v)->a, sizeof(*(w)->a) * (w)->n); } while (0)
#define vec_next(v, w)	do { (w) = malloc(sizeof(*(w))); (w)->n = (v)->n - 1; \
			(w)->m = (v)->m; (w)->a = (v)->a; } while (0)
