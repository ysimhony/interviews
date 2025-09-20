#include <glib.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *ipv4;
    char *ipv6;
    gboolean has_ipv4;
    gboolean has_ipv6;
} DNSRecord;

void free_dns_record(gpointer data) {
    DNSRecord *rec = (DNSRecord *)data;
    free(rec->ipv4);
    free(rec->ipv6);
    free(rec);
}

void handle_dns_response(GHashTable *table, const char *domain, const char *type, const char *address) {
    DNSRecord *rec = (DNSRecord *)g_hash_table_lookup(table, domain);

    if (!rec) {
        rec = calloc(1, sizeof(DNSRecord));
        g_hash_table_insert(table, g_strdup(domain), rec);
    }

    if (strcmp(type, "A") == 0) {
        rec->ipv4 = strdup(address);
        rec->has_ipv4 = TRUE;
    } else if (strcmp(type, "AAAA") == 0) {
        rec->ipv6 = strdup(address);
        rec->has_ipv6 = TRUE;
    }

    if (rec->has_ipv4 && rec->has_ipv6) {
        printf("Domain: %s\n", domain);
        printf("  IPv4: %s\n", rec->ipv4);
        printf("  IPv6: %s\n", rec->ipv6);
        printf("-----------------------------\n");

        // Optional: remove the entry if you're done with it
        g_hash_table_remove(table, domain);
    }
}

int main() {
    // Create a hash table: keys are strings (domain names), values are DNSRecord*
    GHashTable *dns_table = g_hash_table_new_full(g_str_hash, g_str_equal, g_free, free_dns_record);

    // Simulated input
    handle_dns_response(dns_table, "example.com", "A", "93.184.216.34");
    handle_dns_response(dns_table, "example.org", "AAAA", "2606:2800:220:1:248:1893:25c8:1946");
    handle_dns_response(dns_table, "example.org", "A", "93.184.216.34");
    handle_dns_response(dns_table, "example.com", "AAAA", "2606:2800:220:1:248:1893:25c8:1946");

    g_hash_table_destroy(dns_table);  // Cleanup
    return 0;
}

