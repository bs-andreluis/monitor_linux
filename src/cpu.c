#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cpu.h"

// Função para ler os dados crus do kernel
int read_cpu_stats(CpuStats *stats) {
    FILE *fp = fopen("/proc/stat", "r");
    if (!fp) {
        perror("Erro ao abrir /proc/stat");
        return -1;
    }

    char buffer[1024];
    // Pega a primeira linha, que é a "cpu" geral (soma de todos os núcleos)
    if (fgets(buffer, sizeof(buffer), fp)) {
        // O formato é: cpu  user nice system idle iowait irq softirq steal...
        // sscanf faz o "parsing" (extração) dos números
        sscanf(buffer, "cpu %llu %llu %llu %llu %llu %llu %llu %llu",
               &stats->user, &stats->nice, &stats->system,
               &stats->idle, &stats->iowait, &stats->irq,
               &stats->softirq, &stats->steal);
    }

    fclose(fp);
    return 0;
}

// A mágica matemática
double calculate_cpu_usage(const CpuStats *prev, const CpuStats *curr) {
    // 1. Somar tudo para saber o tempo total
    unsigned long long prev_idle = prev->idle + prev->iowait;
    unsigned long long curr_idle = curr->idle + curr->iowait;

    unsigned long long prev_non_idle = prev->user + prev->nice + prev->system + 
                                       prev->irq + prev->softirq + prev->steal;
    unsigned long long curr_non_idle = curr->user + curr->nice + curr->system + 
                                       curr->irq + curr->softirq + curr->steal;

    unsigned long long prev_total = prev_idle + prev_non_idle;
    unsigned long long curr_total = curr_idle + curr_non_idle;

    // 2. Calcular a diferença (Delta)
    unsigned long long total_delta = curr_total - prev_total;
    unsigned long long idle_delta = curr_idle - prev_idle;

    // Evitar divisão por zero
    if (total_delta == 0) return 0.0;

    // 3. Calcular porcentagem de uso
    // (Total - Ocioso) / Total
    return (double)(total_delta - idle_delta) / total_delta * 100.0;
}