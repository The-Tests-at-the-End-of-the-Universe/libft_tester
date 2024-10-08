#include <libft_tester.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>

// Our memory buffer will be readable and writable:
// The buffer will be shared (meaning other processes can access it), but
// anonymous (meaning third-party processes cannot obtain an address for it),
// so only this process and its children will be able to use it:
// The remaining parameters to `mmap()` are not important for this use case,
// but the manpage for `mmap` explains their purpose.
void	*create_shared_memory(size_t size)
{
	int protection = PROT_READ | PROT_WRITE;
	int visibility = MAP_SHARED | MAP_ANONYMOUS;
	return mmap(NULL, size, protection, visibility, -1, 0);
}
