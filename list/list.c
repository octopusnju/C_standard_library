/* list.c */

#include <stdlib.h>
#include <string.h>

#include "list.h"

void list_init(List *list, void (*destroy)(void *data))
{
    list->size = 0;
    list->destroy = destroy;
    list->head = NULL;
    list->tail = NULL;
    return;
}

///@brief   销毁list中的所有节点，并重置list。如果有destroy函数，用其销毁data
void list_destroy(List *list)
{
    void *data;
    while (list_size(list) > 0) {
        if (list_rem_next(list, NULL, (void **)&data) == 0 && list->destroy != NULL) {
            list->destroy(data);
        }
    }
    memset(list, 0, sizeof(List));
    return;
}

///@brief   将data指向的数据插入list中，插入位置在element之后
int list_ins_next(List *list, ListElmt *element, const void *data)
{
    ///创建存放data的节点
    ListElmt *new_element = (ListElmt *)malloc(sizeof(ListElmt));
    if (new_element == NULL) {
        return -1;
    }
    ///存放data
    new_element->data = (void *)data;

    ///插入头部的情况
    if (element == NULL) {
        ///可能需要更新tail指针
        if (list_size(list) == 0) {
            list->tail = new_element;
        }
        ///插入头部，更新头部指针
        new_element->next = list->head;
        list->head = new_element;
    } else { ///其它情况
        ///可能需要更新tail指针
        if (element->next == NULL) {
            list->tail = new_element;
        }
        ///插入节点
        new_element->next = element->next;
        element->next = new_element;
    }
    ///更新长度
    list->size++;
    return 0;
}

///@brief   将list中位于element之后的节点删除，并将data存放到二重指针中
int list_rem_next(List *list, ListElmt *element, void **data) {
    if (list_size(list) == 0) {
        return -1;
    }
    ListElmt *old_element;
    ///删除头部情况
    if (element == NULL) {
        ///删除头部
        old_element = list->head;
        list->head = list->head->next;
        ///可能需要更新tail指针
        if (list_size(list) == 1) {
            list->tail = NULL;
        }
    } else { ///其它情况
        if (element->next == NULL) {
            return -1;
        }
        ///删除节点
        old_element = element->next;
        element->next = element->next->next;
        ///可能需要更新tail指针
        if (element->next == NULL) {
            list->tail = element;
        }
    }
    ///获取节点data
    *data = old_element->data;
    ///销毁节点
    free(old_element);
    ///更新长度
    list->size--;
    return 0;
}
