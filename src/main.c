#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "monitor.h"
#include "cpu.h"
#include "memory.h"
#include "network.h" // Inclua o header de rede

void clear_screen() {
    printf("\033[H\033[J");
}

// Função auxiliar para desenhar barra de progresso
void print_bar(double percent) {
    printf("[");
    int bars = (int)(percent / 5);
    for(int i=0; i<20; i++) {
        if (i < bars) printf("|"); // Mudei para | para ficar mais estiloso
        else printf(" ");
    }
    printf("]");
}

int main() {
    // --- SETUP INICIAL ---
    int num_cores = get_cpu_count();
    
    // Alocação dinâmica: (Cores + 1) para incluir a média global no índice 0
    CpuStats *prev_cpu = malloc(sizeof(CpuStats) * (num_cores + 1));
    CpuStats *curr_cpu = malloc(sizeof(CpuStats) * (num_cores + 1));
    
    MemStats mem_stats;
    NetStats prev_net, curr_net;

    if (!prev_cpu || !curr_cpu) {
        fprintf(stderr, "Erro de alocação de memória!\n");
        return 1;
    }

    // Leituras iniciais
    read_all_cpus(prev_cpu, num_cores);
    get_network_stats(&prev_net);

    // --- LOOP PRINCIPAL ---
    while (1) {
        sleep(1); // Intervalo de 1 segundo

        // 1. Coleta de dados
        read_all_cpus(curr_cpu, num_cores);
        get_memory_usage(&mem_stats);
        get_network_stats(&curr_net);

        // 2. Renderização
        clear_screen();
        printf("=== SYSTEM MONITOR (Cores: %d) ===\n\n", num_cores);

        // --- SEÇÃO CPU ---
        // Calcula Global (índice 0)
        double global_usage = calculate_cpu_usage(&prev_cpu[0], &curr_cpu[0]);
        printf("CPU Global: %5.1f%% ", global_usage);
        print_bar(global_usage);
        printf("\n\n");

        // Lista Cores Individuais (índices 1 até num_cores)
        printf("--- Cores ---\n");
        for (int i = 1; i <= num_cores; i++) {
            double core_usage = calculate_cpu_usage(&prev_cpu[i], &curr_cpu[i]);
            // Formatação compacta: 2 cores por linha se tiver muitos
            printf("Core %-2d: %5.1f%% ", i-1, core_usage); // i-1 para mostrar "Core 0"
            if (i % 2 == 0 || i == num_cores) printf("\n");
            else printf("\t");
        }
        printf("\n");

        // --- SEÇÃO MEMÓRIA ---
        printf("--- Memória ---\n");
        printf("RAM: %5.1f%% ", mem_stats.used_percent);
        print_bar(mem_stats.used_percent);
        printf(" (%ld/%ld MB)\n\n", mem_stats.used_kb/1024, mem_stats.total_kb/1024);

        // --- SEÇÃO REDE ---
        // Cálculo de velocidade (Delta Bytes / 1 segundo = Bytes/s)
        double rx_speed = (double)(curr_net.rx_bytes - prev_net.rx_bytes) / 1024.0; // KB/s
        double tx_speed = (double)(curr_net.tx_bytes - prev_net.tx_bytes) / 1024.0; // KB/s

        printf("--- Rede (Total) ---\n");
        printf("Download: %8.2f KB/s\n", rx_speed);
        printf("Upload:   %8.2f KB/s\n", tx_speed);

        // --- FINALIZAÇÃO DO LOOP ---
        // Atualiza os estados anteriores
        for (int i = 0; i <= num_cores; i++) prev_cpu[i] = curr_cpu[i];
        prev_net = curr_net;

        fflush(stdout);
    }

    // Limpeza (Nunca será executada no loop infinito, mas é boa prática)
    free(prev_cpu);
    free(curr_cpu);
    return 0;
}