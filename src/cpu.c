#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cpu.h"


int read_cpu_stats(CpuStats *stats) {
    FILE *fp = fopen("/proc/stat", "r");
    if (!fp) {
        perror("Erro ao abrir /proc/stat");
        return -1;
    }

    char buffer[1024];
    if (fgets(buffer, sizeof(buffer), fp)) {  
        sscanf(buffer, "cpu %llu %llu %llu %llu %llu %llu %llu %llu",
               &stats->user, &stats->nice, &stats->system,
               &stats->idle, &stats->iowait, &stats->irq,
               &stats->softirq, &stats->steal);
    }

    fclose(fp);
    return 0;
}


double calculate_cpu_usage(const CpuStats *prev, const CpuStats *curr) {
    unsigned long long prev_idle = prev->idle + prev->iowait;
    unsigned long long curr_idle = curr->idle + curr->iowait;

    unsigned long long prev_non_idle = prev->user + prev->nice + prev->system + 
                                       prev->irq + prev->softirq + prev->steal;
    unsigned long long curr_non_idle = curr->user + curr->nice + curr->system + 
                                       curr->irq + curr->softirq + curr->steal;

    unsigned long long prev_total = prev_idle + prev_non_idle;
    unsigned long long curr_total = curr_idle + curr_non_idle;

    unsigned long long total_delta = curr_total - prev_total;
    unsigned long long idle_delta = curr_idle - prev_idle;

    if (total_delta == 0) return 0.0;

    return (double)(total_delta - idle_delta) / total_delta * 100.0;
}