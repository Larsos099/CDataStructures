#include "doublelinkedlist.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static inline void print_list(DLNode *root) {
  DLNode *tmp = root;
  DLNode *last = root;
  while (tmp != NULL) {
    printf("%s\n", (char *)tmp->data);
    tmp = tmp->next;
    if (tmp != NULL) {
      last = tmp;
    }
  }
  printf("<<REVERSE PRINT>>\n");
  tmp = last;
  while (tmp != NULL) {
    printf("%s\n", (char *)tmp->data);
    tmp = tmp->previous;
  }
}

int main(void) {
    printf("---------------\n");
    printf("Creating DLNodes\n");
    printf("---------------\n");

    // testing functions that create a DLNode
    char *dataF = strdup("Second");
    DLNode *root = dl_create_node_mv(&dataF, 7, NULL, NULL);
    char *dataS = strdup("First");
    dl_create_node_cp(dataS, 6, NULL ,root);
    char *dataFo = strdup("Third");
    root = dl_create_node_deep_cp(dataFo, 6, root, NULL);
    dataFo = strdup("Fourth");
    root = dl_create_node_deep_cp(dataFo, 7, root, NULL);
    free(dataFo); // data was copied
    print_list(root);

    // push back to end
    printf("---------------\n");
    printf("Push back\n");
    printf("---------------\n");

    // create a DLNode
    char *dataZ = strdup("Zero");
    DLNode *createdNode = dl_create_node_mv(&dataZ, 5, NULL, NULL);
    // add DLNode to end
    dl_push_back_mv_node(&root, &createdNode);
    char *dataMF = strdup("-First");
    dl_push_back_mv_data(&root, &dataMF, 7);

    char *dataMS = strdup("-Second");
    createdNode = dl_create_node_mv(&dataMS, 8, NULL, NULL);
    dl_push_back_cp_node(&root, createdNode);

    char *dataMT = strdup("-Third");
    dl_push_back_cp_data(&root, dataMT, 7);

    char *dataMFo = strdup("-Fourth");
    dl_push_back_cp_data_deep(&root, dataMFo, 8);
    free(dataMFo); // data was copied

    print_list(root);

    // push front
    printf("---------------\n");
    printf("Push front\n");
    printf("---------------\n");

    char *dataFi = strdup("Fifth");
    createdNode = dl_create_node_mv(&dataFi, 6, NULL, NULL);
    dl_push_front_mv_node(&root, &createdNode);

    char *dataSi = strdup("Sixth");
    dl_push_front_mv_data(&root, &dataSi, 7);

    char *dataSev = strdup("Seventh");
    createdNode = dl_create_node_mv(&dataSev, 8, NULL, NULL);
    dl_push_front_cp_node(&root, createdNode);

    char *dataEi = strdup("Eighth");
    dl_push_front_cp_data(&root, dataEi, 7);

    char *dataNi = strdup("Ninth");
    dl_push_front_cp_data_deep(&root, dataNi, 7);
    free(dataNi); // data was copied

    print_list(root);

    printf("---------------\n");
    printf("Get data\n");
    printf("---------------\n");

    char *data = dl_get_at_index(root, 5);
    printf("Data at index 5: %s\n", data); // prints "Fourth"

    DLNode *nodeByValue = dl_get_by_value(root, "Second", 7);
    printf("Data from DLNode: %s\n", (char *)nodeByValue->data); // prints "Second"
    printf("Data from DLNode->next: %s\n", (char *)nodeByValue->next->data); // prints "First"

    DLNode *nodeByIndex = dl_get_by_index(root, 5);
    printf("Data at index 5: %s\n", (char *)nodeByIndex->data); // prints "Fourth"


    printf("---------------\n");
    printf("Delete data\n");
    printf("---------------\n");

    dl_delete_by_value(&root, "Fourth", 7);
    dl_delete_at_index(&root, 4);
    // Fourth and Fifth are now missing in the list
    print_list(root);
    
    printf("---------------\n");
    printf("insert data\n");
    printf("---------------\n");
    
    dataFo = strdup("Fourth");
    DLNode *nodeToInsert = dl_create_node_deep_cp(dataFo, 7, NULL, NULL);
    dl_insert_at_index_mv_node(&root, &nodeToInsert, 4);
    dataFi = strdup("Fifth");
    nodeToInsert = dl_create_node_deep_cp(dataFi, 6, NULL, NULL);
    dl_insert_at_index_mv_node(&root, &nodeToInsert, 4);
    dataFi = strdup("Fifth.1");
    nodeToInsert = dl_create_node_deep_cp(dataFi, 8, NULL, NULL);
    dl_insert_at_index_cp_node(&root, nodeToInsert, 4);
    dataFi = strdup("Fifth.2");
    nodeToInsert = dl_create_node_deep_cp(dataFi, 8, NULL, NULL);
    dl_insert_at_index_deep_cp_node(&root, nodeToInsert, 4);
    free(nodeToInsert->data);
    free(nodeToInsert);
    dataFi = strdup("Fifth.3");
    dl_insert_at_index_mv_data(&root, &dataFi, 8, 4);
    dataFi = strdup("Fifth.4");
    dl_insert_at_index_cp_data(&root, dataFi, 8, 4);
    dataFi = strdup("Fifth.5");
    dl_insert_at_index_deep_cp_data(&root, dataFi, 8, 4);
    free(dataFi);

    print_list(root);
    dl_free_list(&root);
  return 0;
}
