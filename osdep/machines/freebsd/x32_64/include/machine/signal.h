#ifndef __HACKED_MACHINE_SIGNAL_H
#define __HACKED_MACHINE_SIGNAL_H

/*
 * Here we avoid bringing in <machine/signal.h> because it uses GCC's __aligned().
 * All we really need for C95 is sig_atomic_t, so we just define that directly.
 */
#if defined(_FREEBSD8_3) || defined(_FREEBSD9_0) || defined(_FREEBSD9_1) || defined(_FREEBSD9_2) || defined(_FREEBSD10_1)
typedef int sig_atomic_t;
#endif

#endif

