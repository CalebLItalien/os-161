#include <linked_list.h>
#include <lib.h>

Linked_List *linked_list_create(void)
{
  Linked_List * ptr = kmalloc(sizeof(Linked_List));
  ptr -> length = 0;
  ptr -> first = NULL;
  ptr -> last = NULL;

  return ptr;
}

Linked_List_Node *linked_list_create_node(int key, void *data)
{
  Linked_List_Node *newnode = kmalloc(sizeof(Linked_List_Node));
  newnode -> prev = NULL;
  newnode -> next = NULL;
  newnode -> key = key;
  newnode -> data = data;

  return newnode;
}

void linked_list_prepend(Linked_List *list, void *data)
{
  Linked_List_Node * newnode;
  Linked_List_Node * f = list -> first;

  if (list -> first == NULL) {
    newnode = linked_list_create_node(0, data);
    list -> first = newnode;
    list -> last = newnode;
  } else {
    newnode = linked_list_create_node(f -> key - 1, data);

    newnode -> next = list -> first;
    f -> prev = newnode;
    list -> first = newnode;
  }

  list -> length ++;
}

void linked_list_printlist(Linked_List *list, int which)
{
  Linked_List_Node *runner = list -> first;

  kprintf("%d: ", which);

  while (runner != NULL) {
    kprintf("%d[%c] ", runner -> key, *((int *)runner -> data));
    runner = runner -> next;
  }

  kprintf("\n");
}