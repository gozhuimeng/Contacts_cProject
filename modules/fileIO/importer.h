//
// Created by meng on 25-5-13.
// DOC 文件数据导入器(从文件导入数据)
//

#ifndef IMPORTER_H
#define IMPORTER_H

#include "dataFormat.h"

#include <stdio.h>

FILE *openFile_read(char *filename); // 打开文件

Node *loadNode(FILE *file); // 将文件中的数据加载到节点中

Row *loadRow(FILE *file); // 将文件中的数据加载到行中

Grid *loadGrid(char *filename); // 将文件中的数据加载到数据表中

Grid *loadGrid_append(Grid *grid, char *filename); // 追加载入数据到数据表中

#endif //IMPORTER_H
