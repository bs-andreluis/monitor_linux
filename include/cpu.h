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
int read_cpu_stats(CpuStats *stats);

double calculate_cpu_usage(const CpuStats *prev, const CpuStats *curr);

#endif