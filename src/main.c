#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> 
#include "monitor.h"
#include "cpu.h"
#include "memory.h"


void clear_screen() {
    printf("\033[H\033[J");
}

int main() {
    CpuStats prev_cpu, curr_cpu;
    MemStats mem_stats;
    
    if (read_cpu_stats(&prev_cpu) != 0) return 1;

    while (1) {
        sleep(1);

        
        if (read_cpu_stats(&curr_cpu) != 0) break;
        
        get_memory_usage(&mem_stats);

        double cpu_usage = calculate_cpu_usage(&prev_cpu, &curr_cpu);

        clear_screen();
        printf("=== MONITOR DE RECURSOS LINUX (Ctrl+C para sair) ===\n\n");
        
        
        printf("[CPU] Uso: %.2f%%\n", cpu_usage);
        
        printf("[");
        int bars = (int)(cpu_usage / 5); 
        for(int i=0; i<20; i++) printf("%c", i < bars ? '#' : ' ');
        printf("]\n\n");

        printf("[MEMORIA] Uso: %.2f%% \n", mem_stats.used_percent);
        printf("   Total: %ld MB\n", mem_stats.total_kb / 1024);
        printf("   Usado: %ld MB\n", mem_stats.used_kb / 1024);
        printf("   Livre: %ld MB\n", mem_stats.available_kb / 1024);

        
        prev_cpu = curr_cpu;

        // O flushzin pro texto aparecer direto na tela
        fflush(stdout);
    }

    return 0;
}