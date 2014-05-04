#ifndef MEM_BARRIER_H
#define MEM_BARRIER_H
#if defined (__i386__) || defined (__amd64__)
#define MEM_BARRIER() asm volatile ("" : : : "memory")
#else
#error "Architecture not supported. Need to define MEM_BARRIER."
#endif
#endif
