#include "linkedlist.h"

static inline void print_list(Node *root) {
    Node *tmp = root;
    while (tmp != NULL) {
        printf("%s\n", (char *)tmp->data);
        tmp = tmp->next;
    }
}

int main(void) {
  // testing functions that create a node
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

  // push back to end
  printf("---------------\n");

  // create a node
  char *dataZ = strdup("Zero");
  Node *createdNode = sl_create_node_mv(&dataZ, 5, NULL);
  // add node to end
  sl_push_back_mv_node(&root, &createdNode);
  char *dataMF = strdup("-First");
  sl_push_back_mv_data(&root, &dataMF, 7);

  char *dataMS = strdup("-Second");
  createdNode = sl_create_node_mv(&dataMS, 8, NULL);
  sl_push_back_cp_node(&root, createdNode);

  char *dataMT = strdup("-Third");
  sl_push_back_cp_data(&root, dataMT, 7);

  char *dataMFo = strdup("-Fourth");
  sl_push_back_cp_data_deep(&root, dataMFo, 8);
  free(dataMFo); // data was copied

  print_list(root);

    // push front
    printf("---------------\n");

    char *dataFi = strdup("Fifth");
    createdNode = sl_create_node_mv(&dataFi, 6, NULL);
    sl_push_front_mv_node(&root, &createdNode);

    char *dataSi = strdup("Sixth");
    sl_push_front_mv_data(&root, &dataSi, 7);

    char *dataSev = strdup("Seventh");
    createdNode = sl_create_node_mv(&dataSev, 8, NULL);
    sl_push_front_cp_node(&root, createdNode);

    char *dataEi = strdup("Eighth");
    sl_push_front_cp_data(&root, dataEi, 7);

    char *dataNi = strdup("Ninth");
    sl_push_front_cp_data_deep(&root, dataNi, 7);
    free(dataNi); // data was copied

    print_list(root);

    char *data = sl_get_at_index(root, 5);
    printf("Data at index 5: %s\n", data); // prints "Fourth"

    Node *nodeByValue = sl_get_by_value(root, "Second", 7);
    printf("Data from node: %s\n", (char *)nodeByValue->data); // prints "Second"
    printf("Data from node->next: %s\n", (char *)nodeByValue->next->data); // prints "First"


    Node *nodeByIndex = sl_get_by_index(root, 5);
    printf("Data at index 5: %s\n", (char *)nodeByIndex->data); // prints "Fourth"
}
