//
// Created by meng on 25-5-7.
// DOC 数据加载器(将数据加载到结构体中)
//

#ifndef LOADER_H
#define LOADER_H

#include "dataFormat.h"

// 定义初始化值
#define INIT_NODE_SIZE 100  // 节点初始大小
#define INIT_ROW_SIZE 10  // 行初始长度
#define INIT_COL_SIZE 10  // 表初始行数
#define EXTEND_X 1.5  // 扩展倍数

Node *createNode(); // 创建节点

void extendNode(Node *node); // 扩展节点空间

void clearData(Node *node); // 清空节点数据

void freeNode(Node **node); // 释放节点

void loadData(Node *node, char *data); // 加载数据到节点

void appendChar(Node *node, char c); // 追加字符到节点

void overwriteData(Node *node, char *data); // 覆写节点数据

Row *createRow(); // 创建行

void extendRow(Row *row); // 扩展行空间

void clearRow(Row *row); // 清空行数据

void freeRow(Row **row); // 释放行

void appendRow(Row *row, Node *node); // 添加节点到行

void overwriteRow(Row *row, Node *node); // 覆写行数据

Grid *createGrid(); // 创建表

void extendGrid(Grid *grid); // 扩展表空间

void clearGrid(Grid *grid); // 清空表数据

void freeGrid(Grid **grid); // 释放表

void appendGrid(Grid *grid, Row *row); // 添加行到表

void overwriteGrid(Grid *grid, Row *row); // 覆写表数据

#endif //LOADER_H
