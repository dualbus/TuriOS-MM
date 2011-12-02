#ifndef CPU_H
#define CPU_H
#define CR_N            5
#define MEM_N           1024*1024

typedef struct cpu {
    int cr[CR_N];
}           cpu_t;

typedef struct pc {
    struct cpu cpu;
    char mem[MEM_N];
}           pc_t;

pc_t pc;
#endif
