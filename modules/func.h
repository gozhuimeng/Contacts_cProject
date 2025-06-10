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

Grid *insert_data(Grid *grid);  // 插入数据

void browse_data(const Grid *grid);  // 浏览数据

void query_data(const Grid *grid);  // 查询数据

Grid *modify_data(Grid *grid);  // 修改数据

Grid *delete_data(Grid *grid);  // 删除数据

void export_data(const Grid *grid);

#endif //FUNC_H
