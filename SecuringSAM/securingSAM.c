#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pcap.h>
#include <netinet/ip.h>
#include <netinet/udp.h>
#include <arpa/inet.h>
#include <glib.h>
#include <stdbool.h>
#include <getopt.h>

#define DNS_PORT 53

typedef struct {
    bool ipv4_received;
    GList *ipv4_list; // list of char*
    bool ipv6_received;
    GList *ipv6_list; // list of char*
} DNSRecord;


void dns_callback(unsigned char *args, const struct pcap_pkthdr *header, const unsigned char *packet);
void free_dns_record(gpointer data);
//void print_domain_name(const unsigned char *packet, const unsigned char *payload, int *offset);
char *get_domain_name(const unsigned char *payload, int *offset);


void free_dns_record(gpointer data) {
    DNSRecord *rec = (DNSRecord *)data;
    g_list_free_full(rec->ipv4_list, g_free);
    g_list_free_full(rec->ipv6_list, g_free);
    free(rec);
}

bool debug_mode = false;

// Hash table which map the domain to its record containing the ipv4 and ipv6 addresses
GHashTable *dns_table = NULL;

void print_dns_record(const char *domain, DNSRecord *rec) {
    printf("-----------------------------\n");
    printf("Domain: %s\n", domain);

    printf("  IPv4:\n");
    for (GList *l = rec->ipv4_list; l != NULL; l = l->next) {
        printf("    %s\n", (char *)l->data);
    }

    printf("  IPv6:\n");
    for (GList *l = rec->ipv6_list; l != NULL; l = l->next) {
        printf("    %s\n", (char *)l->data);
    }

    printf("-----------------------------\n");
}

gboolean ip_in_list(GList *list, const char *ip) {
    for (GList *l = list; l != NULL; l = l->next) {
        if (strcmp((char *)l->data, ip) == 0) {
            return TRUE;
        }
    }
    return FALSE;
}

// Print the raw data of the ethernet packet
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
                    printf("%c", packet[j]);
                else
                    printf(".");
            }
            printf("\n");
        }
    }
    printf("\n");
}

char *get_domain_name(const unsigned char *payload, int *offset) {
    int jumped = 0;
    int original_offset = *offset;
    int pos = 0;
    int max_len = 256;  // DNS max length
    char *domain = malloc(max_len);
    if (!domain) return NULL;

    domain[0] = '\0'; // Start with empty string

    while (1) {
        unsigned char length = payload[*offset];

        if ((length & 0xC0) == 0xC0) {  // Compressed label
            int pointer_offset = ((length & 0x3F) << 8) | payload[*offset + 1];
            if (!jumped) original_offset = *offset + 2;
            *offset = pointer_offset;
            jumped = 1;
            continue;
        }

        if (length == 0) {
            (*offset)++;
            break;
        }

        (*offset)++;
        if (pos != 0 && pos < max_len - 1) {
            domain[pos++] = '.';  // Add dot separator
        }

        for (int i = 0; i < length && pos < max_len - 1; i++) {
            domain[pos++] = payload[*offset];
            (*offset)++;
        }
    }

    domain[pos] = '\0';  // Null-terminate

    if (jumped) *offset = original_offset;

    return domain;
}


// main function handler triggered by the pcap library upong catching DNS response packets 
void dns_callback(unsigned char *args, const struct pcap_pkthdr *header, const unsigned char *packet) {

    if (debug_mode)
        print_packet_data(packet, header->len);

    struct ip *ip_header = (struct ip*)(packet + 14);
    int ip_header_len = ip_header->ip_hl * 4;

    if (ip_header->ip_p != IPPROTO_UDP) return;

    struct udphdr *udp_header = (struct udphdr*)(packet + 14 + ip_header_len);

    if (ntohs(udp_header->uh_sport) != DNS_PORT) return;

    const unsigned char *dns_payload = packet + 14 + ip_header_len + sizeof(struct udphdr);
    int dns_size = ntohs(udp_header->uh_ulen) - sizeof(struct udphdr);

    if (dns_size < 12) return;

    int answer_count = ntohs(*(unsigned short *)(dns_payload + 6));
    int offset = 12;

    char *question_domain = get_domain_name(dns_payload, &offset);
    if (debug_mode)
        printf("Domain: %s\n", question_domain);
  
    DNSRecord *rec = (DNSRecord *)g_hash_table_lookup(dns_table, question_domain);

    if (!rec) {
        rec = calloc(1, sizeof(DNSRecord));
        g_hash_table_insert(dns_table, g_strdup(question_domain), rec);
    }

    unsigned short query_type = ntohs(*(unsigned short *)(dns_payload + offset));

    if (debug_mode)
        printf("query_type: %u\n", query_type);
    
    if (query_type == 1) {
        rec->ipv4_received = true;
    }

    if (query_type == 28) {
        rec->ipv6_received = true;
    }



    offset += 4;

    if (answer_count == 0) goto print_rec;

    if (debug_mode)
        printf("Answers: %d\n", answer_count);

    for (int i = 0; i < answer_count; i++) {
        char *domain = get_domain_name(dns_payload, &offset);
	if (debug_mode) { 
	    printf("Name: %s", domain);
	}

        unsigned short type = ntohs(*(unsigned short *)(dns_payload + offset));
        unsigned short data_len = ntohs(*(unsigned short *)(dns_payload + offset + 8));
        offset += 10;

        if (type == 1 && data_len == 4) {
            struct in_addr addr;
            memcpy(&addr, dns_payload + offset, 4);
            if (debug_mode)
                printf(" IPv4 Address: %s\n", inet_ntoa(addr));
	    char s_addr[20];

	    snprintf(s_addr, 20, "%s", inet_ntoa(addr));
	    if (!ip_in_list(rec->ipv4_list, s_addr)) {
            	rec->ipv4_list = g_list_append(rec->ipv4_list, g_strdup(s_addr));
            }
            offset += data_len;
        } else if (type == 28 && data_len == 16) {
            char ipv6_addr[INET6_ADDRSTRLEN];
            inet_ntop(AF_INET6, dns_payload + offset, ipv6_addr, INET6_ADDRSTRLEN);
            if (debug_mode)
	        printf(" IPv6 Address: %s\n", ipv6_addr);

            if (!ip_in_list(rec->ipv6_list, ipv6_addr)) {
                rec->ipv6_list = g_list_append(rec->ipv6_list, g_strdup(ipv6_addr));
            }

            offset += data_len;
        } else if (type == 5) {
            char *domain = get_domain_name(dns_payload, &offset);
	    if (debug_mode) {
    	        printf(" CNAME: ");
	        printf("%s", domain);
                printf("\n");
	    }
        }

    }

print_rec:
    // Only print if we have at least one of each
    if (rec->ipv4_received && rec->ipv6_received) {
        print_dns_record(question_domain, rec);

        // Optional: remove if you're done
        g_hash_table_remove(dns_table, question_domain);
    }

    //printf("--------------------------------------------------\n");
}

void print_usage(const char *progname) {
    fprintf(stderr, "Usage: %s --interface <name> [--debug]\n", progname);
    fprintf(stderr, "Options:\n");
    fprintf(stderr, "  -i, --interface <name>   (required) Network interface to sniff\n");
    fprintf(stderr, "  -d, --debug              (optional) Enable debug mode\n");
}

int main(int argc, char *argv[]) {
    char errbuf[PCAP_ERRBUF_SIZE];
    pcap_t *handle;
    char *interface_name = NULL;

    static struct option long_options[] = {
        {"interface", required_argument, 0, 'i'},
        {"debug",     no_argument,       0, 'd'},
        {0, 0, 0, 0}
    };

    int opt;
    while ((opt = getopt_long(argc, argv, "i:d", long_options, NULL)) != -1) {
        switch (opt) {
            case 'i':
                interface_name = optarg;
                break;
            case 'd':
                debug_mode = true;
                break;
            default:
                print_usage(argv[0]);
                exit(EXIT_FAILURE);
        }
    }

    // Validate that interface was provided
    if (!interface_name) {
        fprintf(stderr, "Error: --interface (-i) is required.\n");
        print_usage(argv[0]);
        exit(EXIT_FAILURE);
    }

    // Now you can use interface_name anywhere
    printf("Sniffing on interface: %s\n", interface_name);

    if (debug_mode) {
        printf("Debug mode enabled.\n");
    }

   
    dns_table = g_hash_table_new_full(g_str_hash, g_str_equal, g_free, free_dns_record);

    handle = pcap_open_live(interface_name, BUFSIZ, 1, 1000, errbuf);
    if (handle == NULL) {
        fprintf(stderr, "Could not open device %s: %s\n", interface_name, errbuf);
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

