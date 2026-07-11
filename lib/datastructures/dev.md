# t_darray

A dynamic array of `void *`, backed by the gc. It grows automatically.

## Basic usage

```c
#include "datastructures.h"
#include "gc.h"

t_gc		*gc = new_gc();
t_darray	*arr = new_darray(gc);             // []

arr->push(arr, "hello");                       // ["hello"]
arr->push(arr, "world");                       // ["hello", "world"]
arr->insert(arr, 1, "there");                  // ["hello", "there", "world"]

arr->len;                                      // 3

char	*last = arr->pop(arr);                 // last = "world" -> ["hello", "there"]
char	*mid  = arr->pop_i(arr, 0);            // mid  = "hello" -> ["there"]

dest_darray(arr, NULL);
dest_gc(gc);
```

**IMPORTANT 1:** a `t_darray` instance must hold **either** all heap-allocated
items **or** all stack / data-segment items (string literals, stack addresses) —
never a mix. `gc_free` can only release memory the gc owns; if a heap item and a
stack/literal item share one array, `free_str` will free memory it must not
touch.

```c
void	free_str(void *p, t_gc *gc) { gc_free(p, gc); }

// RIGHT: all heap -> free_str is correct for every item
t_darray *h = new_darray(gc);
h->push(h, gc_strdup("a", gc));
h->push(h, gc_strdup("b", gc));
dest_darray(h, free_str);            // frees "a" and "b"

// RIGHT: all literals / stack -> never pass a dest
t_darray *s = new_darray(gc);
s->push(s, "a");
s->push(s, "b");
dest_darray(s, NULL);               // frees only the array buffer

// WRONG: mixed heap + literal -> free_str calls gc_free on string literal "b"
t_darray *m = new_darray(gc);
m->push(m, gc_strdup("a", gc));      // heap
m->push(m, "b");                     // string literal
dest_darray(m, free_str);            // invalid free on "b"

```

**IMPORTANT 2:** whether to pass a `dest` (e.g. `gc_free`) depends on **ownership**.
Figure out who owns each item before freeing to avoid double-free.

```c
void	free_str(void *p, t_gc *gc) { gc_free(p, gc); }

t_darray *a = new_darray(gc);
a->push(a, gc_strdup("x", gc));


// WRONG: shallow copy, both freed -> "x" is freed twice (double free)
t_darray *b = copy(a, NULL);          // shallow: a and b share the same pointer
dest_darray(a, free_str);
dest_darray(b, free_str);

// RIGHT: deep copy, each array owns its own items
t_darray *b = copy(a, gc_strdup_wrap); // makes a fresh copy of each item
dest_darray(a, free_str);             // frees a's "x"
dest_darray(b, free_str);             // frees b's own "x"

// RIGHT: shallow copy, free the items exactly once
t_darray *b = copy(a, NULL);          // a and b share the same pointer
dest_darray(a, free_str);             // frees "x" once
dest_darray(b, NULL);                 // just frees b's buffer, not the items
```

## Construct / copy / destroy

```c
t_darray	*new_darray(t_gc *gc);
// Constructor
t_darray *arr = new_darray(gc);      // []
```

```c
t_darray	*new_darray_from_arr(const void **arr, t_gc *gc);
// Constructor
const char *src[] = {"a", "b", NULL};
t_darray *arr = new_darray_from_arr((const void **)src, gc);   // ["a", "b"]
```

```c
t_darray	*copy(const t_darray *original, void *(*copy)(const void *, t_gc *));
// Copy constructor
t_darray *cp = copy(arr, NULL);              // ["a", "b"] -> ["a", "b"], shares the same pointers
t_darray *cp = copy(arr, gc_strdup_wrap);    // ["a", "b"] -> ["a", "b"], holds fresh copies
```

```c
void	dest_darray(t_darray *darray, void (*dest)(void *, t_gc *));
// Destructor
void	free_str(void *p, t_gc *gc) { gc_free(p, gc); }

dest_darray(arr, NULL);              // frees the array
dest_darray(arr, free_str);          // frees the array and its items
```

## Functions

```c
void	push(t_darray *self, const void *item);
// Append item to the end.
arr->push(arr, "c");                 // ["a", "b"] -> ["a", "b", "c"]
```

```c
void	insert(t_darray *self, size_t i, const void *item);
// Insert item at index i.
arr->insert(arr, 1, "x");            // ["a", "b"] -> ["a", "x", "b"]
```

```c
void	*pop(t_darray *self);
// Remove and return the last item (NULL if empty).
char *str = arr->pop(arr);           // ["a", "b"] -> ["a"], str = "b"
```

```c
void	*pop_i(t_darray *self, size_t i);
// Remove and return the item at index i (NULL if out of range).
char *str = arr->pop_i(arr, 0);      // ["a", "b"] -> ["b"], str = "a"
```

```c
const void	*peek(const t_darray *self);
// Return the last item without removing it (NULL if empty).
const char *str = arr->peek(arr);    // ["a", "b"] -> ["a", "b"], str = "b"
```

```c
const void	*peek_i(const t_darray *self, size_t i);
// Return the item at index i without removing it (NULL if out of range).
const char *str = arr->peek_i(arr, 0);   // ["a", "b"] -> ["a", "b"], str = "a"
```

```c
void	set(t_darray *self,
			size_t i,
			const void *item,
			void (*dest)(void *, t_gc *));
// Overwrite index i. Pass a dest to free the replaced item, or NULL.
void	free_str(void *p, t_gc *gc) { gc_free(p, gc); }

arr->set(arr, 1, gc_strdup("B", arr->gc), NULL);   // ["a", "b"] -> ["a", "B"], "b" will not be freed
arr->set(arr, 1, "C", free_str);                   // ["a", "B"] -> ["a", "C"], "B" will be freed
```

```c
void	sort(t_darray *self, bool (*cmp)(const void *, const void *));
// In-place sort. cmp(a, b) returns true when a should come before b.
bool	str_smaller_than(const void *a, const void *b) { return (ft_strcmp((char *)a, (char *)b) < 0); }

arr->sort(arr, str_smaller_than);    // ["b", "a", "c"] -> ["a", "b", "c"]
```

```c
void	repr(const t_darray *self, void (*repr_item)(const void *));
// Print the array using repr_item for each element.
void	repr_str(const void *s) { ft_printf("%s", (char *)s); }

arr->repr(arr, repr_str);            // ["a", "b"] -> prints: [a, b]
```

```c
size_t	find_i(const t_darray *self,
			bool (*f)(const void *, const void *),
			const void *e);
// Index of the first item where f(item, e) is true, else len.
bool	eq(const void *a, const void *b) { return (ft_strcmp((char *)a, (char *)b) == 0); }

size_t i = arr->find_i(arr, eq, "b");    // ["a", "b"] -> i = 1
```

```c
const void	*find(const t_darray *self,
			bool (*f)(const void *, const void *),
			const void *e);
// First item where f(item, e) is true, else NULL.
bool	eq(const void *a, const void *b) { return (ft_strcmp((char *)a, (char *)b) == 0); }

const char *str = arr->find(arr, eq, "b");   // ["a", "b"] -> str = "b"
```

```c
bool	any(const t_darray *self,
			bool (*f)(const void *, const void *),
			const void *e);
// true if any item satisfies f(item, e).
bool	eq(const void *a, const void *b) { return (ft_strcmp((char *)a, (char *)b) == 0); }

bool found = arr->any(arr, eq, "z");     // ["a", "b"] -> found = false
```

```c
void	for_each(t_darray *self,
			void *(*f)(void *, t_gc *),
			void (*dest)(void *, t_gc *));
// Map in place: replace each item with f(item, gc).
void	*to_upper(void *s, t_gc *gc)
{
	char	*up;
	size_t	i;

	up = gc_strdup(s, gc);
	i = 0;
	while (up[i])
	{
		up[i] = ft_toupper(up[i]);
		i++;
	}
	return (up);
}

void	free_str(void *p, t_gc *gc) { gc_free(p, gc); }

arr->for_each(arr, to_upper, NULL);      // ["a", "b"] -> ["A", "B"], old "a", "b" will not be freed
arr->for_each(arr, to_upper, free_str);  // ["a", "b"] -> ["A", "B"], old "a", "b" will be freed
```

```c
void	*reduce(const t_darray *self,
			void *(*f)(const void *, const void *, t_gc *),
			void *acc,
			void (*dest)(void *, t_gc *));
// Fold: acc = f(acc, item, gc) over every item. arr is unchanged.
void	*join(const void *a, const void *b, t_gc *gc) { return (gc_strjoin(a, b, gc)); }
void	free_str(void *p, t_gc *gc) { gc_free(p, gc); }

char *empty = gc_strdup("a", gc);
char *joined = arr->reduce(arr, join, empty, free_str);  // [b", "c", "d"] -> joined = "abcd"
```

**IMPORTANT:** `dest` is mandatory and the initial `acc` must be heap allocated —
`dest` frees each intermediate `acc`, including the first one you passed in.

```c
// RIGHT: acc is heap allocated
char *empty = gc_strdup("", gc);
char *joined = arr->reduce(arr, join, empty, free_str);

// WRONG: acc is a literal -> free_str calls gc_free on a string literal
char *joined = arr->reduce(arr, join, "", free_str);

// WRONG: acc is a stack buffer
char acc[] = "";
char *joined = arr->reduce(arr, join, acc, free_str);
```

```c
t_darray	*filter(const t_darray *self,
				bool (*f)(const void *, const void *),
				void *(*copy)(const void *, t_gc *),
				const void *e);
// New array with the items where f(item, e) is true.
bool	starts_with(const void *s, const void *prefix) { return (ft_strncmp((char *)s, (char *)prefix, ft_strlen((char *)prefix)) == 0); }

t_darray *hits = arr->filter(arr, starts_with, NULL, "a");            // ["ant", "bee", "ape"] -> ["ant", "ape"], shares the same pointers
t_darray *hits = arr->filter(arr, starts_with, gc_strdup_wrap, "a");  // ["ant", "bee", "ape"] -> ["ant", "ape"], holds fresh copies
```
