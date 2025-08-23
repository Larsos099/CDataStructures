#include "linkedlist.h"

static inline void print_list(Node *root) {
  Node *tmp = root;
  while (tmp != NULL) {
    printf("%s\n", (char *)tmp->data);
    tmp = tmp->next;
  }
}

int main(void) {
  printf("---------------\n");
  printf("Creating Nodes\n");
  printf("---------------\n");

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
  printf("Push back\n");
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
  printf("Push front\n");
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

  printf("---------------\n");
  printf("Get data\n");
  printf("---------------\n");

  char *data = sl_get_at_index(root, 5);
  printf("Data at index 5: %s\n", data); // prints "Fourth"

  Node *nodeByValue = sl_get_by_value(root, "Second", 7);
  printf("Data from node: %s\n", (char *)nodeByValue->data); // prints "Second"
  printf("Data from node->next: %s\n",
         (char *)nodeByValue->next->data); // prints "First"

  Node *nodeByIndex = sl_get_by_index(root, 5);
  printf("Data at index 5: %s\n", (char *)nodeByIndex->data); // prints "Fourth"

  print_list(root);

  printf("---------------\n");
  printf("Delete data\n");
  printf("---------------\n");

  sl_delete_by_value(&root, "Fourth", 7);
  sl_delete_at_index(&root, 4);
  // Fourth and Fifth are now missing in the list
  print_list(root);

  printf("---------------\n");
  printf("insert data\n");
  printf("---------------\n");

  dataFo = strdup("Fourth");
  Node *nodeToInsert = sl_create_node_deep_cp(dataFo, 7, root);
  sl_insert_at_index_mv_node(&root, &nodeToInsert, 4);
  dataFi = strdup("Fifth");
  nodeToInsert = sl_create_node_deep_cp(dataFi, 6, root);
  sl_insert_at_index_mv_node(&root, &nodeToInsert, 4);
  dataFi = strdup("Fifth.1");
  nodeToInsert = sl_create_node_deep_cp(dataFi, 8, root);
  sl_insert_at_index_cp_node(&root, nodeToInsert, 4);
  dataFi = strdup("Fifth.2");
  nodeToInsert = sl_create_node_deep_cp(dataFi, 8, root);
  sl_insert_at_index_deep_cp_node(&root, nodeToInsert, 4);
  free(nodeToInsert->data);
  free(nodeToInsert);
  dataFi = strdup("Fifth.3");
  sl_insert_at_index_mv_data(&root, &dataFi, 8, 4);
  dataFi = strdup("Fifth.4");
  sl_insert_at_index_cp_data(&root, dataFi, 8, 4);
  dataFi = strdup("Fifth.5");
  sl_insert_at_index_deep_cp_data(&root, dataFi, 8, 4);
  free(dataFi);
  print_list(root);
  sl_free_list(&root);
}
