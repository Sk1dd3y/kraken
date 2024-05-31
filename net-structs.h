#ifndef NET_STRUCTS_H
#define NET_STRUCTS_H

#include <stdint.h>
#include <libnet.h> // Include libnet to use its definitions

//#define ETHER_ADDR_LEN 6
//#define ETHER_HDR_LEN 14

struct ether_hdr {
  unsigned char ether_dest_addr[ETHER_ADDR_LEN]; //MAC of destionation
  unsigned char ether_src_addr[ETHER_ADDR_LEN];  //MAC of source
  unsigned short ether_type;                     //Type of Ethernet packet

};

struct ip_hdr {
  unsigned char ip_version_and_header_length; //This would usually be differentiated for Little or Big Endian, since both are only 4bits sharing 1 byte
  unsigned char ip_tos;                       //Type of Service
  unsigned short ip_len;                      //Total Length
  unsigned short ip_id;                       //Identification number
  unsigned short ip_frag_offset;              //Fragment ofset and flags
  unsigned char ip_ttl;                       //time to life
  unsigned char ip_type;                      //Protocol type
  unsigned short ip_checsums;                 //Checsum
  unsigned int ip_src_addr;                   //Source IP address
  unsigned int ip_dest_addr;                  //Destination IP address
};

struct tcp_hdr {
  unsigned short tcp_src_port;        //Source TCP Port
  unsigned short tcp_dest_port;       //Destination TCP Port
  unsigned int tcp_seq;               //TCP Sequence Number
  unsigned int tcp_ack;               //TCP Acknowledgement Number
  unsigned char reserved:4;           //4 bits from the 6 bits of reserved space
  unsigned char tcp_offset:4;         //TCP data offset for little endian host
  unsigned char tcp_flags;            //TCP flags (and 2 bits from reserved space)
#define TCP_FIN 0x01
#define TCP_SYN 0x02
#define TCP_RST 0x04
#define TCP_PUSH 0x08
#define TCP_AC 0x10
#define TCP_URG 0x20
  unsigned short tcp_window;          //TCP window size
  unsigned short tcp_checksum;        //TCP checksum
  unsigned short tcp_urgent;          //TCP urgent pointer
};

struct arp_hdr {
    uint16_t hw_type;                             // ARP Hardware Type. 1 for Ethernet        | 2 Bytes
    uint16_t protocol_type;                       // ARP Protocol Type. 0x0800 for IPv4       | 2 Bytes
    uint8_t hw_size;                              // Hardware Size - should be 6 for MAC      | 1 Bytes
    uint8_t protocol_size;                        // Protocol Size - should be 4 for IPv4     | 1 Bytes
    uint16_t opcode;                              // 1 for request, 2 for reply               | 2 Bytes
    unsigned char mac_src_addr[ETHER_ADDR_LEN];   // MAC Source Address                       | 6 Bytes
    uint32_t ip_src_addr;                         // Source IP address                        | 4 Bytes
    unsigned char mac_dest_addr[ETHER_ADDR_LEN];  // MAC Destination Address                  | 6 Bytes
    uint32_t ip_dest_addr;                        // Destination IP address                   | 4 Bytes
} __attribute__((packed));  // Packed attribute to avoid padding

#endif // NET_STRUCTS_H
