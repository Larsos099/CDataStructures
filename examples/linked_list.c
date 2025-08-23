#include "linkedlist.h"

static inline void print_list(Node *root) {
    Node *tmp = root;
    while (tmp != NULL) {
        printf("%s\n", (char *)tmp->data);
        tmp = tmp->next;
    }
}

int main(void) {
    char *dataF = strdup("First");
    Node *root = sl_create_node_mv(&dataF, 6, NULL);
    char *dataS = strdup("Second");
    root = sl_create_node_deep_mv(&dataS, 7, &root);
    char *dataT = strdup("Third");
    root = sl_create_node_cp(dataT, 6, root);
    char *dataFo = strdup("Fourth");
    root = sl_create_node_deep_cp(dataFo, 7, root);
    free(dataFo); // data was copied



    print_list(root);




}