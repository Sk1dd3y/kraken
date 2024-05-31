#include <stdlib.h>
#include <string.h>
#include <netinet/ether.h> 
#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <libnet.h>
#include <pcap.h>
#include "net-structs.h"
#include "net-funcs.h"
#include "auxillary-funcs.h"
#include <netpacket/packet.h>

int main(int argc, char *argv[]) {

  static u_int8_t *packet;
  size_t packet_size;
  int help = 1;

  if(strcmp(argv[1], "arp") == 0) {
    help = 0;
    // Allocate memory for the packet
    packet_size = sizeof(struct ether_hdr) + sizeof(struct arp_hdr);

    packet = (uint8_t *)malloc(packet_size);
    if (!packet) {
      perror("[ERROR] Could not allocate packet memory\n");
      return -1;
    }
    // Craft Packet
    craft_arp(packet, argv); 
  }
  
  if(help) {
    printf("######### How to use Kraken: #########\n");
    printf("Usage: %s <mode> <src_ip> <src_mac> <dst_ip> <dst_mac>\n", argv[0]);
    return 1;
    }

  printf("\n[RAW] Packet Size: %d\n", packet_size);
  dump(packet, packet_size);

  send_raw_packet(packet, packet_size);
 
  free(packet);

  return 0;
  
}
