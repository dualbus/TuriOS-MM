#ifndef PC_H 
#define PC_H
#define CR_N            5
#define MEM_N           (50 * 4096)

typedef struct cpu {
    int cr[CR_N];
}           cpu_t;

typedef struct pc {
    struct cpu cpu;
    char mem[MEM_N];
}           pc_t;

pc_t pc;
#endif
