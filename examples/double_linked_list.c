#include "doublelinkedlist.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *to_string(void *data, size_t dataSize) {
  char buffer[128];
  char *result = NULL;

  if (dataSize == sizeof(int)) {
    snprintf(buffer, sizeof(buffer), "%d", *(int *)data);
    result = strdup(buffer);
  } else if (dataSize == sizeof(float)) {
    snprintf(buffer, sizeof(buffer), "%g", *(float *)data);
    result = strdup(buffer);
  } else if (dataSize == sizeof(double)) {
    snprintf(buffer, sizeof(buffer), "%g", *(double *)data);
    result = strdup(buffer);
  } else {
    // fallback: assume it's already a string
    result = (char *)malloc(dataSize + 1);
    memcpy(result, data, dataSize);
    result[dataSize] = '\0';
  }

  return result; // caller frees
}

void print(DLNode *root) {
  DLNode *current = root;
  int i = 0;
  while (current) {
    char *s = to_string(current->data, current->dataSize);
    printf("Node Data: %s\nNode Index: %i\n\n", s, i);
    free(s);
    current = current->next;
    i++;
  }
}

int main(void) {
  DLNode *root = NULL;

  // root node
  char *rootStr = strdup("This is the root node.");
  dl_push_back_deep_cp_data(&root, rootStr, strlen(rootStr) + 1);

  // int node
  int *pA = malloc(sizeof(int));
  *pA = 1;
  dl_push_back_mv_data(&root, (void **)&pA, sizeof(*pA));
  // careful: pA will actually go NULL because dl_push_back_mv_data sets *pA =
  // NULL internally

  // node pushed in front
  char *pf_e = strdup("This node will be pushed in front of the root node.");
  dl_push_front_deep_cp_data(&root, pf_e, strlen(pf_e) + 1);
  free(pf_e);
  print(root);
  char *insertedStr = strdup("Inserted");
  size_t insertedSize = strlen(insertedStr) + 1;
  dl_insert_at_index_mv_data(&root, (void **)&insertedStr, insertedSize, 1);
  print(root);
  printf("Both pA and insertedStr should be NULL now since we used mv on "
         "them:\npA: %s insertedStr: %s\n",
         (char *)pA, insertedStr);
  dl_delete_by_value(&root, rootStr, strlen(rootStr) + 1);
  print(root);
  dl_free_list(&root);
  printf("root node should now be NULL\n%s\n", (char *)root);
  return 0;
}
