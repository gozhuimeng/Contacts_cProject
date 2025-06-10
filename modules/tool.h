//
// Created by meng on 25-5-23.
// DOC 工具函数
//

#ifndef TOOL_H
#define TOOL_H

#include<stdbool.h>

#include "fileIO/dataFormat.h"

bool check_row_equal(const Row *row1, const Row *row2);

bool check_grid_equal(const Grid *grid1, const Grid *grid2);

bool check_row_existing(const Grid *grid, const Row *row);

bool check_row_name_existing(const Grid *grid, const Row *row);

Grid *select_by_name(const Grid *grid);

Row *modify_row(Row *row);

Grid *modify_item(Grid *grid,const Row *row);

Grid *delete_item(Grid *grid, const Row *row);

void print_item(const Row *row);

#endif //TOOL_H
