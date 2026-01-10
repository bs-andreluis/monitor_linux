#include <stdio.h>
#include <stdlib.h>
#include "monitor.h"


int main() {
    print_hello();
    FILE *arquivo = fopen("/proc/uptime", "r");
    
    if (arquivo == NULL) {
        perror("Erro ao abrir o arquivo /proc/uptime");
        return 1;
    }

    double uptime_seconds;
    if (fscanf(arquivo, "%lf", &uptime_seconds) != 1) {
        perror("Erro ao ler o arquivo /proc/uptime");
        fclose(arquivo);
        return 1;
    }

    fclose(arquivo);

    int h = (int)(uptime_seconds / 3600);
    int m = ((int)uptime_seconds % 3600) / 60;
    int s = (int)uptime_seconds % 60;

    printf("Uptime: %02d:%02d:%02d\n", h, m, s);
    return 0;
}
