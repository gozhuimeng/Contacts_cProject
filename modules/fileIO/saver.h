//
// Created by meng on 25-5-21.
// DOC 文件保存器
//

#ifndef SAVER_H
#define SAVER_H

#include <stdio.h>
#include "dataFormat.h"

FILE *openFile_write(char *filename);

Node *buildString(const Row *row);

void saveFile(char *filename, const Grid *grid);

#endif //SAVER_H
