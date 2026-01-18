#include <stdio.h>
#include <string.h>
#include "network.h"

int get_network_stats(NetStats *stats) {
    FILE *fp = fopen("/proc/net/dev", "r");
    if (!fp) return -1;

    char buffer[1024];
    stats->rx_bytes = 0;
    stats->tx_bytes = 0;

    fgets(buffer, sizeof(buffer), fp);
    fgets(buffer, sizeof(buffer), fp);

    while (fgets(buffer, sizeof(buffer), fp)) {
        char *iface_name = buffer;
        
        while (*iface_name == ' ') iface_name++;

        if (strncmp(iface_name, "lo:", 3) == 0) continue;

        unsigned long long rx, tx, junk;
        
    
        char *data_start = strchr(iface_name, ':');
        if (data_start) {
            data_start++; // Pula o ':'
            
        
            sscanf(data_start, "%llu %llu %llu %llu %llu %llu %llu %llu %llu",
                   &rx, &junk, &junk, &junk, &junk, &junk, &junk, &junk, &tx);
            
            stats->rx_bytes += rx;
            stats->tx_bytes += tx;
        }
    }

    fclose(fp);
    return 0;
}