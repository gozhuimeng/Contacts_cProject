//
// Created by meng on 25-5-23.
// DOC 工具函数
//

#include <stdio.h>
#include <stdbool.h>

#include "fileIO/dataFormat.h"
#include "tool.h"

#include <string.h>

/**
 * 检查数据是否一致
 * @param grid1
 * @param grid2
 * @return
 */
bool check_grid_equal(const Grid *grid1, const Grid *grid2) {
    if (grid1 == NULL || grid2 == NULL) {
        return true;
    }
    if (grid1->len != grid2->len) {
        return false;
    }
    for (int i = 0; i < grid1->len; i++) {
        const Row *row1 = grid1->data[i];
        const Row *row2 = grid2->data[i];
        if (row1->len != row2->len) {
            return false;
        }
        for (int j = 0; j < row1->len; j++) {
            const Node *node1 = row1->data[j];
            const Node *node2 = row2->data[j];
            if (node1->len != node2->len||strcmp(node1->str, node2->str)!=0) {
                return false;
            }
        }
    }
    return true;
}

/**
 * 检查行是否存在于网络中
 * @param grid
 * @param row
 * @return
 */
bool check_row_existing(const Grid *grid, const Row *row) {
    for (int i = 0; i < grid->len; i++) {
        Row *row2 = grid->data[i];
        if (row2->len != row->len) {
            return false;
        }
        for (int j = 0; j < row->len; j++) {
            const Node *node1 = row2->data[j];
            const Node *node2 = row->data[j];
            if (node1->len != node2->len || strcmp(node1->str, node2->str) != 0) {
                return false;
            }
        }
    }
    return true;
}