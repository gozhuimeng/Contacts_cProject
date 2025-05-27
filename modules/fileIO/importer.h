//
// Created by meng on 25-5-13.
// DOC 文件数据导入器(从文件导入数据)
//

#ifndef IMPORTER_H
#define IMPORTER_H

#include <stdio.h>
#include "dataFormat.h"

FILE *openFile_read(char *filename);

Node *loadNode(FILE *file);

Row *loadRow(FILE *file);

Grid *loadGrid(char *filename);

Grid *loadGrid_append(Grid *grid, char *filename);

#endif //IMPORTER_H
