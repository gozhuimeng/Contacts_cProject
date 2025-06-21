//
// Created by meng on 25-5-7.
// DOC 数据加载器(将数据加载到结构体中)
//

#include "loader.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "dataFormat.h"


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
    char *temp = realloc(node->str, ((int) node->size * EXTEND_X) * sizeof(char)); // 使用realloc扩展空间
    if (temp == NULL) {
        printf("节点空间拓展失败\n");
        return;
    }
    node->str = temp;
    node->size = (int) node->size * EXTEND_X; // 更新节点大小
}

/**
 * 清空节点数据
 * @param node
 */
void clearData(Node *node) {
    node->len = 0;
    free(node->str); // 释放原有字符串空间
    node->size = INIT_NODE_SIZE;
    node->str = (char *) malloc(node->size * sizeof(char)); // 重新分配初始大小的空间
}

/**
 * 释放节点
 * @param node
 */
void freeNode(Node **node) {
    if (*node == NULL) {
        // 检查指针是否为NULL
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
    int data_len = strlen(data); // 获取数据长度
    if (data_len == 0) {
        // 如果数据长度为0，结束函数
        return;
    }
    while (node->len + data_len >= node->size) {
        extendNode(node); // 如果当前长度加上数据长度超过当前大小，扩展节点空间
    }
    strcpy(node->str + node->len, data); // 将数据复制到节点字符串的末尾
    node->len += data_len; // 修改长度
}

/**
 * 追加字符
 * @param node
 * @param c
 */
void appendChar(Node *node, char c) {
    if (node->len == node->size) {   // 如果当前长度等于节点大小，扩展节点空间
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
    int data_len = strlen(data);  // 获取数据长度
    if (data_len == 0) {  // 如果数据长度为0，清空节点数据
        clearData(node);
        return;
    }
    if (node->len > (int) node->size * EXTEND_X) {  // 如果当前长度大于扩展倍数的节点大小，清空节点数据
        clearData(node);
    } else {
        node->len = 0;
    }
    loadData(node, data);  // 加载数据到节点
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
    if (row->len >= row->size) {  // 如果当前行长度等于或超过行大小，扩展行空间
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
 * 创建表格
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
 * 拓展表格空间
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
 * 清空表格
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
 * 释放表格
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
 * 添加行到表格
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
 * 覆写表格
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
