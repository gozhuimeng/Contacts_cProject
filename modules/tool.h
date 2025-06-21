//
// Created by meng on 25-5-23.
// DOC 工具函数
//

#ifndef TOOL_H
#define TOOL_H

#include<stdbool.h>

#include "fileIO/dataFormat.h"

bool check_row_equal(const Row *row1, const Row *row2); // 检查两个数据行是否一致

bool check_grid_equal(const Grid *grid1, const Grid *grid2); // 检查两个数据表是否一致

bool check_row_existing(const Grid *grid, const Row *row); // 检查数据行是否存在于数据表中

bool check_row_name_existing(const Grid *grid, const Row *row); // 检查数据行的姓名是否已存在于数据表中

Grid *select_by_name(const Grid *grid); // 通过姓名在数据表中查询行

Row *modify_row(Row *row); // 修改数据行内容

Grid *modify_item(Grid *grid, const Row *row); // 修改数据表中的数据行

Grid *delete_item(Grid *grid, const Row *row); // 删除数据表中的数据行

void print_item(const Row *row); // 打印单行数据

#endif //TOOL_H
