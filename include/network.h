#ifndef NETWORK_H
#define NETWORK_H

typedef struct {
    unsigned long long rx_bytes; // Bytes recebidos (Download)
    unsigned long long tx_bytes; // Bytes transmitidos (Upload)
} NetStats;

// Lê o tráfego TOTAL de todas as interfaces (exceto loopback)
int get_network_stats(NetStats *stats);

#endif