#ifndef CPU_H
#define CPU_H

// Estrutura para guardar os dados brutos lidos do /proc/stat
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

// Lê os dados atuais do /proc/stat
int read_cpu_stats(CpuStats *stats);

// Calcula a porcentagem baseada em duas leituras (anterior e atual)
double calculate_cpu_usage(const CpuStats *prev, const CpuStats *curr);

#endif