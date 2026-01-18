#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "cpu.h"

// Função para pegar o número de núcleos (NOVA)
int get_cpu_count() {
    // Sysconf é a forma POSIX de pegar config do sistema
    return (int)sysconf(_SC_NPROCESSORS_ONLN);
}

// Função para ler todos os núcleos (NOVA)
int read_all_cpus(CpuStats *stats, int num_cores) {
    FILE *fp = fopen("/proc/stat", "r");
    if (!fp) return -1;

    char buffer[1024];
    
    // Vamos ler (num_cores + 1) linhas. 
    // A primeira linha é "cpu" (global), as próximas são "cpu0", "cpu1"...
    for (int i = 0; i <= num_cores; i++) {
        if (!fgets(buffer, sizeof(buffer), fp)) break;

        // Verifica se a linha começa com "cpu"
        if (strncmp(buffer, "cpu", 3) == 0) {
            sscanf(buffer, "%*s %llu %llu %llu %llu %llu %llu %llu %llu",
                   &stats[i].user, &stats[i].nice, &stats[i].system,
                   &stats[i].idle, &stats[i].iowait, &stats[i].irq,
                   &stats[i].softirq, &stats[i].steal);
        }
    }

    fclose(fp);
    return 0;
}

// Essa função se mantém igual, mas é necessária para o cálculo
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