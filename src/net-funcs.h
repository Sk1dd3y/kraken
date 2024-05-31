#ifndef NET_FUNCS_H
#define NET_FUNCS_H

#include <netpacket/packet.h>
#include "auxillary-funcs.h"

int init_arp_hdr(struct arp_hdr *arp_hdr) {
  arp_hdr->hw_type = htons(1);
  arp_hdr->protocol_type = htons(0x0800);                       
  arp_hdr->hw_size = ETHER_ADDR_LEN;                              
  arp_hdr->protocol_size = 4;                     
  arp_hdr->opcode = htons(ARPOP_REPLY);                             
  memset(arp_hdr->mac_src_addr, 0, ETHER_ADDR_LEN);   
  arp_hdr->ip_src_addr = 0;
  memset(arp_hdr->mac_dest_addr, 0, ETHER_ADDR_LEN);  
  arp_hdr->ip_dest_addr = 0;                     
}

void craft_arp(uint8_t *packet, char *argv[]) {
  // Init needed structures
  struct arp_hdr arp_hdr;
  struct ether_hdr ether_hdr;
  
  // Set up ether frame
  memcpy(&ether_hdr.ether_src_addr, ether_aton(argv[3]), ETHER_ADDR_LEN);
  memcpy(&ether_hdr.ether_dest_addr, ether_aton(argv[5]), ETHER_ADDR_LEN);
  ether_hdr.ether_type = htons(0x0806);
  
  // Init Arp Hdr
  init_arp_hdr(&arp_hdr);

  // Write Addresses into arp_hdr section  
  inet_pton(AF_INET, argv[2], &arp_hdr.ip_src_addr);
  inet_pton(AF_INET, argv[4], &arp_hdr.ip_dest_addr);
  
  memcpy(&arp_hdr.mac_src_addr, ether_aton(argv[3]), ETHER_ADDR_LEN);
  memcpy(&arp_hdr.mac_dest_addr, ether_aton(argv[5]), ETHER_ADDR_LEN);

  print_arp_hdr(&arp_hdr);

  // Write Crafted Segments into Package Memory
  memcpy(packet, &ether_hdr, sizeof(struct ether_hdr));
  memcpy(packet+sizeof(struct ether_hdr), &arp_hdr, sizeof(struct arp_hdr));
}

int send_raw_packet(uint8_t *packet, size_t packet_size) {

  pcap_if_t *alldevs;
  int sockfd;
  char errbuf[PCAP_ERRBUF_SIZE];
  struct sockaddr_ll device;
  
  // Try to open Socket
  
  if((sockfd = socket(PF_PACKET, SOCK_RAW, htons(ETH_P_ALL))) == -1) {
    perror("[ERROR] Could not open raw socket\n");
    pcap_freealldevs(alldevs);
    close(sockfd);
    return -1;
  }


  // Get Device to send on with pcap lib

  pcap_findalldevs(&alldevs, errbuf);
  if(alldevs->name == NULL) {
    printf("[ERROR] findalldevs %s", errbuf);
    pcap_freealldevs(alldevs);
    close(sockfd);
    return -1;
  }
  // Write main device into dev_name
  const char *dev_name = alldevs->name;


  /* Send packet */
  // Set up the device structure
  

  memset(&device, 0, sizeof(device));
  device.sll_family = AF_PACKET;
  device.sll_protocol = htons(ETH_P_ALL);
  device.sll_ifindex = if_nametoindex(alldevs->name);
  device.sll_halen = ETHER_ADDR_LEN;
  memcpy(device.sll_addr, packet, ETHER_ADDR_LEN);

  // Send the packet
  if (sendto(sockfd, packet, packet_size, 0, (struct sockaddr *)&device, sizeof(device)) < 0) {
    perror("[ERROR] Send failed");
  }
  pcap_freealldevs(alldevs);
  close(sockfd);
  return 1;
}




#endif // NET_FUNCS_H
