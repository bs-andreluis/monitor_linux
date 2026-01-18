#ifndef MEMORY_H
#define MEMORY_H

typedef struct {
    long total_kb;
    long available_kb; 
    long used_kb;      
    double used_percent;
} MemStats;

int get_memory_usage(MemStats *stats);

#endif