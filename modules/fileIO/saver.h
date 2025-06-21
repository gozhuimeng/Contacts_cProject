//
// Created by meng on 25-5-21.
// DOC 文件保存器
//

#ifndef SAVER_H
#define SAVER_H

#include <stdio.h>
#include "dataFormat.h"

FILE *openFile_write(char *filename); // 打开文件并返回文件指针

Node *buildString(const Row *row); // 将一行数据转换为字符串

void saveFile(char *filename, const Grid *grid); // 将表格数据写入文件

#endif //SAVER_H
