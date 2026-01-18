#ifndef CPU_H
#define CPU_H

typedef struct {
    unsigned long long user;
    unsigned long long nice;
    unsigned long long system;
    unsigned long long idle;
    unsigned long long iowait;
    unsigned long long irq;
    unsigned long long softirq;
    unsigned long long steal;
} CpuStats;

// Retorna o número de núcleos lógicos
int get_cpu_count();

// Lê todos os núcleos. O array 'stats' deve ter tamanho (num_cores + 1)
// O índice 0 será a média global, 1 será cpu0, 2 será cpu1...
int read_all_cpus(CpuStats *stats, int num_cores);

double calculate_cpu_usage(const CpuStats *prev, const CpuStats *curr);

#endif