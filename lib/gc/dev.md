# gc

A tiny garbage collector. Centralise memory allocation in a single instance

## Basic usage

```c
#include "gc.h"

int	main(void)
{
	t_gc	*gc = new_gc();

	char	*buf  = gc_malloc(64, gc);
	int		*nums = gc_calloc(10, sizeof(int), gc);

	// ... use them ...

	gc_free(buf, gc);   // free a gc allocated pointer early

	dest_gc(gc);   // frees nums and gc
	return (0);
}
```

`gc_malloc` / `gc_calloc` never return `NULL` — on failure they free everything
and `exit`. Use `gc_free(ptr, gc)` to free a single pointer early.

## Functions

```c
// Create a new gc instance. Exits on failure.
t_gc	*new_gc(void);

// malloc() tracked by the gc. Never returns NULL: on failure it
// destroys the gc (freeing everything) and exits.
void	*gc_malloc(size_t size, t_gc *gc);

// calloc() tracked by the gc. Same failure behaviour as gc_malloc.
void	*gc_calloc(size_t nmemb, size_t size, t_gc *gc);

// Free a single tracked pointer early and remove it from the gc.
// Pass only pointers returned by gc_malloc / gc_calloc.
void	gc_free(void *ptr, t_gc *gc);

// Free every tracked pointer, then the gc itself. Call once at the end.
void	dest_gc(t_gc *gc);
```
