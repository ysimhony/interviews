#include <glib.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    GList *ipv4_list; // list of char*
    GList *ipv6_list; // list of char*
} DNSRecord;

void free_dns_record(gpointer data) {
    DNSRecord *rec = (DNSRecord *)data;
    g_list_free_full(rec->ipv4_list, g_free);
    g_list_free_full(rec->ipv6_list, g_free);
    free(rec);
}

void print_dns_record(const char *domain, DNSRecord *rec) {
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

void handle_dns_response(GHashTable *table, const char *domain, const char *type, const char *address) {
    DNSRecord *rec = (DNSRecord *)g_hash_table_lookup(table, domain);

    if (!rec) {
        rec = calloc(1, sizeof(DNSRecord));
        g_hash_table_insert(table, g_strdup(domain), rec);
    }

    if (strcmp(type, "A") == 0) {
        if (!ip_in_list(rec->ipv4_list, address)) {
            rec->ipv4_list = g_list_append(rec->ipv4_list, g_strdup(address));
        }
    } else if (strcmp(type, "AAAA") == 0) {
        if (!ip_in_list(rec->ipv6_list, address)) {
            rec->ipv6_list = g_list_append(rec->ipv6_list, g_strdup(address));
        }
    }

    // Only print if we have at least one of each
    if (rec->ipv4_list && rec->ipv6_list) {
        print_dns_record(domain, rec);

        // Optional: remove if you're done
        g_hash_table_remove(table, domain);
    }
}

int main() {
    GHashTable *dns_table = g_hash_table_new_full(g_str_hash, g_str_equal, g_free, free_dns_record);

    // Simulated input with multiple IPs
    handle_dns_response(dns_table, "example.com", "A", "93.184.216.34");
    handle_dns_response(dns_table, "example.com", "A", "93.184.216.35");
    handle_dns_response(dns_table, "example.com", "AAAA", "2606:2800:220:1:248:1893:25c8:1946");
    handle_dns_response(dns_table, "example.com", "AAAA", "2606:2800:220:1:248:1893:25c8:1947");

    handle_dns_response(dns_table, "example.org", "AAAA", "2001:4860:4860::8888");
    handle_dns_response(dns_table, "example.org", "A", "8.8.8.8");

    g_hash_table_destroy(dns_table);
    return 0;
}

