#include <stdio.h>
#include <string.h>
#include "memory.h"

int get_memory_usage(MemStats *stats) {
    FILE *fp = fopen("/proc/meminfo", "r");
    if (!fp) return -1;

    char buffer[256];
    long mem_total = 0;
    long mem_available = 0;
    
    while (fgets(buffer, sizeof(buffer), fp)) {
        if (strncmp(buffer, "MemTotal:", 9) == 0) {
            sscanf(buffer, "MemTotal: %ld kB", &mem_total);
        }
        
        else if (strncmp(buffer, "MemAvailable:", 13) == 0) {
            sscanf(buffer, "MemAvailable: %ld kB", &mem_available);
        }
        
    
        if (mem_total > 0 && mem_available > 0) break;
    }

    fclose(fp);

    stats->total_kb = mem_total;
    stats->available_kb = mem_available;
    stats->used_kb = mem_total - mem_available;
    
    if (mem_total > 0)
        stats->used_percent = (double)stats->used_kb / mem_total * 100.0;
    else
        stats->used_percent = 0.0;

    return 0;
}