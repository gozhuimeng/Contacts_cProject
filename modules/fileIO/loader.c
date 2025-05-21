//
// Created by meng on 25-5-7.
// DOC 数据加载器(将数据加载到结构体中)
//

#include "loader.h"
#include "dataFormat.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define INIT_NODE_SIZE 100
#define INIT_ROW_SIZE 10
#define INIT_COL_SIZE 10
#define EXTEND_X 1.5


/**
 * 创建节点
 * @return
 */
Node *createNode() {
    Node *node = (Node *) malloc(sizeof(Node));
    node->len = 0;
    node->size = INIT_NODE_SIZE;
    node->str = (char *) malloc(node->size * sizeof(char));
    return node;
}

/**
 * 扩展节点空间
 * @param node
 */
void extendNode(Node *node) {
    char *temp = realloc(node->str, ((int) node->size * EXTEND_X) * sizeof(char));
    if (temp == NULL) {
        printf("节点空间拓展失败\n");
        return;
    }
    node->str = temp;
    node->size = (int) node->size * EXTEND_X;
}

/**
 * 清空节点数据
 * @param node
 */
void clearData(Node *node) {
    node->len = 0;
    free(node->str);
    node->size = INIT_NODE_SIZE;
    node->str = (char *) malloc(node->size * sizeof(char));
}

/**
 * 释放节点
 * @param node
 */
void freeNode(Node **node) {
    if (*node == NULL) {
        return;
    }
    free((*node)->str);
    free(*node);
}

/**
 * 追加载入数据
 * @param node
 * @param data
 */
void loadData(Node *node, char *data) {
    int data_len = strlen(data);
    if (data_len == 0) {
        return;
    }
    while (node->len + data_len >= node->size) {
        extendNode(node);
    }
    strcpy(node->str + node->len, data);
    node->len += data_len;
}

/**
 * 追加字符
 * @param node
 * @param c
 */
void appendChar(Node *node, char c) {
    if (node->len == node->size) {
        extendNode(node);
    }
    node->str[node->len] = c;
    node->len++;
}

/**
 * 覆写数据
 * @param node
 * @param data
 */
void overwriteData(Node *node, char *data) {
    int data_len = strlen(data);
    if (data_len == 0) {
        clearData(node);
        return;
    }
    if (node->len > (int) node->size * EXTEND_X) {
        clearData(node);
    } else {
        node->len = 0;
    }
    loadData(node, data);
}

/**
 * 创建行
 * @return
 */
Row *createRow() {
    Row *row = (Row *) malloc(sizeof(Row));
    row->len = 0;
    row->size = INIT_ROW_SIZE;
    row->data = (Node **) malloc(row->size * sizeof(Node *));
    return row;
}

/**
 * 拓展行空间
 * @param row
 */
void extendRow(Row *row) {
    Node **temp = realloc(row->data, ((int) row->size * EXTEND_X) * sizeof(Node *));
    if (temp == NULL) {
        printf("行空间拓展失败\n");
        return;
    }
    row->data = temp;
    row->size = (int) row->size * EXTEND_X;
}

/**
 * 清空行数据
 * @param row
 */
void clearRow(Row *row) {
    row->len = 0;
    for (int i = 0; i < row->size; i++) {
        freeNode(&row->data[i]);
    }
    free(row->data);
    row->size = INIT_ROW_SIZE;
    row->data = (Node **) malloc(row->size * sizeof(Node *));
}

/**
 * 释放行
 * @param row
 */
void freeRow(Row **row) {
    if (*row == NULL) {
        return;
    }
    for (int i = 0; i < (*row)->len; i++) {
        free((*row)->data[i]->str);
    }
    free((*row)->data);
    free(*row);
}

/**
 * 添加行
 * @param row
 * @param node
 */
void appendRow(Row *row, Node *node) {
    if (node == NULL) {
        return;
    }
    if (row->len >= row->size) {
        extendRow(row);
    }
    row->data[row->len] = node;
    row->len++;
}

/**
 * 覆写行
 * @param row
 * @param node
 */
void overwriteRow(Row *row, Node *node) {
    clearRow(row);
    if (node == NULL) {
        return;
    }
    appendRow(row, node);
}

/**
 * 创建列
 * @return
 */
Grid *createGrid() {
    Grid *grid = (Grid *) malloc(sizeof(Grid));
    grid->len = 0;
    grid->size = INIT_COL_SIZE;
    grid->data = (Row **) malloc(grid->size * sizeof(Row *));
    return grid;
}

/**
 * 拓展列空间
 * @param grid
 */
void extendGrid(Grid *grid) {
    Row **temp = realloc(grid->data, ((int) grid->size * EXTEND_X) * sizeof(Row *));
    if (temp == NULL) {
        printf("列空间拓展失败\n");
        return;
    }
    grid->data = temp;
    grid->size = (int) grid->size * EXTEND_X;
}

/**
 * 清空列
 * @param grid
 */
void clearGrid(Grid *grid) {
    grid->len = 0;
    for (int i = 0; i < grid->size; i++) {
        freeRow(&grid->data[i]);
    }
    free(grid->data);
    grid->size = INIT_COL_SIZE;
    grid->data = (Row **) malloc(grid->size * sizeof(Row *));
}

/**
 * 释放列
 * @param grid
 */
void freeGrid(Grid **grid) {
    if (*grid == NULL) {
        return;
    }
    for (int i = 0; i < (*grid)->len; i++) {
        freeRow(&(*grid)->data[i]);
    }
    free((*grid)->data);
    free(*grid);
}

/**
 * 添加列
 * @param grid
 * @param row
 */
void appendGrid(Grid *grid, Row *row) {
    if (row == NULL) {
        return;
    }
    if (grid->len >= grid->size) {
        extendGrid(grid);
    }
    grid->data[grid->len] = row;
    grid->len++;
}

/**
 * 覆写列
 * @param grid
 * @param row
 */
void overwriteGrid(Grid *grid, Row *row) {
    clearGrid(grid);
    if (row == NULL) {
        return;
    }
    appendGrid(grid, row);
}
