#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pcap.h>
#include <netinet/ip.h>
#include <netinet/udp.h>
#include <arpa/inet.h>

#define DNS_PORT 53

void dns_callback(unsigned char *args, const struct pcap_pkthdr *header, const unsigned char *packet);
void print_domain_name(const unsigned char *payload, int *offset);

void print_packet_data(const unsigned char *packet, int length) {
    printf("Packet Data (Length: %d bytes):\n", length);
    for (int i = 0; i < length; i++) {
        if (i % 16 == 0) printf("0x%04x: ", i);
        printf("%02x ", packet[i]);

        if (i % 16 == 15 || i == length - 1) {
            for (int j = 0; j < 15 - (i % 16); j++) printf("   ");
            printf("  ");
            for (int j = (i / 16) * 16; j <= i; j++) {
                if (packet[j] >= 32 && packet[j] <= 126)
                    printf("%c", packet[j]);  // Printable ASCII character
                else
                    printf(".");
            }
            printf("\n");
        }
    }
    printf("\n");
}

int main(int argc, char *argv[]) {
    char errbuf[PCAP_ERRBUF_SIZE];
    pcap_t *handle;
    
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <network interface>\n", argv[0]);
        return 1;
    }

    handle = pcap_open_live(argv[1], BUFSIZ, 1, 1000, errbuf);
    if (handle == NULL) {
        fprintf(stderr, "Could not open device %s: %s\n", argv[1], errbuf);
        return 2;
    }

    struct bpf_program fp;
    char filter_exp[] = "udp src port 53";

    if (pcap_compile(handle, &fp, filter_exp, 0, PCAP_NETMASK_UNKNOWN) == -1) {
        fprintf(stderr, "Could not parse filter %s: %s\n", filter_exp, pcap_geterr(handle));
        return 2;
    }

    if (pcap_setfilter(handle, &fp) == -1) {
        fprintf(stderr, "Could not install filter %s: %s\n", filter_exp, pcap_geterr(handle));
        return 2;
    }

    pcap_loop(handle, 0, dns_callback, NULL);

    pcap_freecode(&fp);
    pcap_close(handle);
    return 0;
}

void dns_callback(unsigned char *args, const struct pcap_pkthdr *header, const unsigned char *packet) {
    
    print_packet_data(packet, header->caplen);  // Add this line here to print the full packet

    struct ip *ip_header = (struct ip*)(packet + 14);
    int ip_header_len = ip_header->ip_hl * 4;

    printf("ip_header_len %u\n", ip_header_len);

    if (ip_header->ip_p != IPPROTO_UDP) return;

    struct udphdr *udp_header = (struct udphdr*)(packet + 14 + ip_header_len);

    if (ntohs(udp_header->uh_sport) != DNS_PORT) return;

    const unsigned char *dns_payload = packet + 14 + ip_header_len + sizeof(struct udphdr);
    int dns_size = ntohs(udp_header->uh_ulen) - sizeof(struct udphdr);

    if (dns_size < 12) return;  // DNS header is 12 bytes

    int answer_count = ntohs(*(unsigned short *)(dns_payload + 6));
    int offset = 12;  // Skip DNS header

    // Skip question section
    while (dns_payload[offset] != 0) offset++;
    offset += 5;

    printf("dns_payload_offset %lx\n", dns_payload - packet);
    printf("offset %lx\n", offset + dns_payload - packet);
    if (answer_count == 0) return;

    printf("Domain: ");
    print_domain_name(dns_payload, &offset);
    printf("\n");
    printf("answer_count: %u\n", answer_count);

    printf("offset %lx\n", offset + dns_payload - packet);
    for (int i = 0; i < answer_count; i++) {
        unsigned short type = ntohs(*(unsigned short *)(dns_payload + offset));
        unsigned short data_len = ntohs(*(unsigned short *)(dns_payload + offset + 8));

	printf("type: %lx\n", dns_payload + offset + 2 - packet);
        offset += 10;

        if (type == 1 && data_len == 4) { // A Record
            struct in_addr addr;
            memcpy(&addr, dns_payload + offset, 4);
            printf("IPv4: %s\n", inet_ntoa(addr));
        }
        else if (type == 28 && data_len == 16) { // AAAA Record
            char ipv6_addr[INET6_ADDRSTRLEN];
            inet_ntop(AF_INET6, dns_payload + offset, ipv6_addr, INET6_ADDRSTRLEN);
            printf("IPv6: %s\n", ipv6_addr);
        }
        else if (type == 5) { // CNAME Record
            printf("CNAME: ");
            print_domain_name(dns_payload, &offset);
            printf("\n");
        }

        //offset += data_len;
    }
    printf("--------------------------------------------------\n");
}

void print_domain_name(const unsigned char *payload, int *offset) {
    while (payload[*offset] != 0) {
        int label_len = payload[*offset];
        (*offset)++;
        for (int i = 0; i < label_len; i++) {
            printf("%c", payload[*offset]);
            (*offset)++;
        }
        if (payload[*offset] != 0) printf(".");
    }
    (*offset)++; // Move past the null byte
}

