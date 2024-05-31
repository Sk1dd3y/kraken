#ifndef NET_AUXILLARY_H
#define NET_AUXILLARY_H


void print_arp_hdr(struct arp_hdr *arp_hdr) {
  
// Print the initialized struct values for verification
    printf("Hardware Type: %04x\n", ntohs(arp_hdr->hw_type));
    printf("Protocol Type: %04x\n", ntohs(arp_hdr->protocol_type));
    printf("Hardware Size: %d\n", arp_hdr->hw_size);
    printf("Protocol Size: %d\n", arp_hdr->protocol_size);
    printf("Opcode: %04x\n", ntohs(arp_hdr->opcode));


    printf("Source MAC");
    for(int i=1; i < ETHER_ADDR_LEN; i++) {
      printf(":%02x", arp_hdr->mac_src_addr[i]);
    }

    printf("\nDest MAC");
    
    for(int i=1; i < ETHER_ADDR_LEN; i++) {
      printf(":%02x", arp_hdr->mac_dest_addr[i]);
    }
    
  
    printf("\nSource IP: %s\n", inet_ntoa(*(struct in_addr *)&arp_hdr->ip_src_addr));
    printf("Destination IP: %s\n", inet_ntoa(*(struct in_addr *)&arp_hdr->ip_dest_addr));
}

void print_packet(const uint8_t *packet, size_t length) {
    printf("Packet contents:\n");
    for (size_t i = 0; i < length; i++) {
        printf("%02x ", packet[i]);
        if ((i + 1) % 16 == 0) {
            printf("\n");
        }
    }
    printf("\n");
}

/* Dumps raw memor in hex byte and printable split format */
void dump(const unsigned char *data_buffer, const unsigned int length) {
  unsigned char byte;
  unsigned int i, j;

  for(i=0; i < length; i++) {
    byte = data_buffer[i];
    printf("%02x ", data_buffer[i]);
    if(((i%16)==15) || (i == length-1)) {
      for(j=0; j < 15-(i%16); j++)
	printf("   ");
      printf("| ");
      for(j=(i-(i%16));j <= i; j++) {
	byte = data_buffer[j];
	//Check if within printable space
	if((byte > 31) && (byte < 127)) {
	  printf("%c", byte);
	} else {
	  printf(".");
	}
      }
      printf("\n");
    }
  }
}

#endif // NET_AUXILLARY_H
