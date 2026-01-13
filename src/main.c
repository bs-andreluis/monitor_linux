#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> // Para sleep()
#include "monitor.h"
#include "cpu.h"
#include "memory.h" // Inclua o header novo

// Função auxiliar para limpar a tela
void clear_screen() {
    printf("\033[H\033[J");
}

int main() {
    CpuStats prev_cpu, curr_cpu;
    MemStats mem_stats;

    // Leitura inicial da CPU (para ter o primeiro estado)
    if (read_cpu_stats(&prev_cpu) != 0) return 1;

    while (1) {
        // 1. Espera o intervalo de atualização
        sleep(1);

        // 2. Lê o novo estado da CPU
        if (read_cpu_stats(&curr_cpu) != 0) break;
        
        // 3. Lê o estado da Memória
        get_memory_usage(&mem_stats);

        // 4. Calcula uso da CPU
        double cpu_usage = calculate_cpu_usage(&prev_cpu, &curr_cpu);

        // 5. Atualiza a tela (O Dashboard)
        clear_screen();
        printf("=== MONITOR DE RECURSOS LINUX (Ctrl+C para sair) ===\n\n");
        
        // Exibição CPU
        printf("[CPU] Uso: %.2f%%\n", cpu_usage);
        
        // Barra de progresso simples para CPU (Visual extra!)
        printf("[");
        int bars = (int)(cpu_usage / 5); // 1 barra para cada 5%
        for(int i=0; i<20; i++) printf("%c", i < bars ? '#' : ' ');
        printf("]\n\n");

        // Exibição Memória (Convertendo kB para MB para facilitar leitura)
        printf("[MEMORIA] Uso: %.2f%% \n", mem_stats.used_percent);
        printf("   Total: %ld MB\n", mem_stats.total_kb / 1024);
        printf("   Usado: %ld MB\n", mem_stats.used_kb / 1024);
        printf("   Livre: %ld MB\n", mem_stats.available_kb / 1024);

        // Atualiza o estado anterior da CPU para a próxima volta do loop
        prev_cpu = curr_cpu;
        
        // O flush garante que o texto apareça imediatamente na tela
        fflush(stdout); 
    }

    return 0;
}