//
// Created by meng on 25-5-27.
// DOC 主程序函数
//

#ifndef FUNC_H
#define FUNC_H

#include "fileIO/dataFormat.h"

void print_menu();  // 打印菜单

void quit(Grid *grid);  // 退出程序

Grid *import_data(Grid *grid);  // 导入数据

#endif //FUNC_H
