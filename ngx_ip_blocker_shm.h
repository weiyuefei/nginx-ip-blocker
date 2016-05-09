#include <stdint.h>         // For int32_t
#include <semaphore.h>      // For sem_t

#define NGX_IP_BLOCKER_MAX_READERS (1 << 30)

typedef struct {
	// mutex w;                    // held if there are pending writers
	sem_t writer_sem;              // semaphore for writers to wait for completing readers
	sem_t reader_sem;              // semaphore for readers to wait for completing writers
	volatile int32_t reader_count; // number of pending readers
	volatile int32_t reader_wait;  // number of departing readers
} ngx_ip_blocker_rwlock_st;

typedef struct {
	volatile struct {
		off_t base;
		size_t len;
	} ip4, ip6;

	ngx_ip_blocker_rwlock_st lock;
} ngx_ip_blocker_shm_st;