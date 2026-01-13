#ifndef MEMORY_H
#define MEMORY_H

typedef struct {
    long total_kb;
    long available_kb; // A memória realmente disponível para uso
    long used_kb;      // Calculado como: total - available
    double used_percent;
} MemStats;

int get_memory_usage(MemStats *stats);

#endif