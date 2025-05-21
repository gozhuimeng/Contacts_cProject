//
// Created by meng on 25-5-7.
// DOC 数据加载器(将数据加载到结构体中)
//

#ifndef LOADER_H
#define LOADER_H
#include"dataFormat.h"

Node *createNode();

void extendNode(Node *node);

void clearData(Node *node);

void freeNode(Node **node);

void loadData(Node *node, char *data);

void appendChar(Node *node, char c);

void overwriteData(Node *node, char *data);

Row *createRow();

void extendRow(Row *row);

void clearRow(Row *row);

void freeRow(Row **row);

void appendRow(Row *row, Node *node);

void overwriteRow(Row *row, Node *node);

Grid *createGrid();

void extendGrid(Grid *grid);

void clearGrid(Grid *grid);

void freeGrid(Grid **grid);

void appendGrid(Grid *grid, Row *row);

void overwriteGrid(Grid *grid, Row *row);

#endif //LOADER_H
