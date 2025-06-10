//
// Created by meng on 25-5-27.
// DOC 主程序函数
//

#include <stdio.h>
#include <stdlib.h>

#include "func.h"

#include <math.h>
#include <string.h>

#include "tool.h"
#include "fileIO/dataFormat.h"
#include "fileIO/importer.h"
#include "fileIO/config.h"
#include "fileIO/loader.h"
#include "fileIO/saver.h"

/**
 * 打印菜单
 */
void print_menu() {
    printf("========请选择进行的操作========\n");
    printf("\t1. 导入数据\n");
    printf("\t2. 插入数据\n");
    printf("\t3. 浏览数据\n");
    printf("\t4. 查询数据\n");
    printf("\t5. 修改数据\n");
    printf("\t6. 删除数据\n");
    // printf("\t7. 保存数据\n");
    // printf("\t8. 导出数据\n");
    printf("\t7. 导出数据\n");
    printf("\t0. 退出\n");
    printf("==============================\n");
    printf("请输入操作序号: ");
}

/**
 * 退出程序
 * @param grid
 */
void quit(Grid *grid) {
    Grid *fileGrid = loadGrid(DATA_FILE_NAME);
    if (!check_grid_equal(grid, fileGrid)) {
        printf("数据发生改动，是否保存数据？(Y/N) \n");
        char choice = getchar();
        getchar(); // 清除换行符
        while (choice != 'Y' && choice != 'N' && choice != 'n' && choice != 'y') {
            printf("非法输入，请重新输入(Y/N): ");
            while (getchar() != '\n') {
            } // 清空输入缓冲区
            choice = getchar();
        }
        if (choice == 'N' || choice == 'n') {
            exit(0);
        }
        printf("正在保存数据...\n");
        saveFile(DATA_FILE_NAME, grid);
        printf("数据保存完成，正在退出程序...\n");
    } else {
        printf("数据未发生改动，正在退出程序...\n");
    }
    exit(0);
}

/**
 * 导入数据
 * @return
 */
Grid *import_data(Grid *grid) {
    char filename[500];
    int choice = 0;
    printf("请输入要导入的文件名(相对路径和绝对路径均可): ");
    scanf("%s", filename);
    if (filename[0] == '\0') {
        printf("非法操作：文件名为空，中断操作\n");
        return grid;
    }
    // 尝试读取数据
    Grid *importedGrid = loadGrid(filename);
    if (importedGrid->len <= 0) {
        printf("无可导入数据，请确认数据文件路径及格式正确！\n");
        printf("中断导入操作\n");
        return grid;
    }
    // 选择导入方式
    printf("共读取到 %d 行数据\n", importedGrid->len);
    while (1) {
        printf("请选择导入方式:\n");
        printf("1. 覆盖导入\n");
        printf("2. 追加导入(跳过重复项，不跳过重名项)\n");
        printf("3. 追加导入(跳过重复项，跳过重名项)\n");
        printf("0. 取消导入\n");
        while (scanf("%d", &choice) != 1 && (choice == 1 || choice == 2 || choice == 3 || choice == 0)) {
            printf("非法输入，请重新输入\n");
            while (getchar() != '\n') {
            } // 清空输入缓冲区
        }
        if (choice == 0) {
            printf("取消导入操作\n");
            return grid;
        } else if (choice == 1) {
            printf("正在导入数据\n");
            return importedGrid;
        } else if (choice == 2) {
            int duplicates = 0;
            printf("正在导入数据(将跳过重复项)...\n");
            for (int i = 0; i < importedGrid->len; i++) {
                if (check_row_existing(grid, importedGrid->data[i])) {
                    duplicates++;
                    continue; // 跳过重复项
                }
                appendGrid(grid, importedGrid->data[i]);
            }
            printf("导入完成，共导入 %d 行数据，跳过 %d 行重复数据\n", importedGrid->len - duplicates, duplicates);
            return grid;
        } else if (choice == 3) {
            int duplicates = 0;
            printf("正在导入数据，将跳过重名项...\n");
            for (int i = 0; i < importedGrid->len; i++) {
                if (check_row_existing(grid, importedGrid->data[i]) || check_row_name_existing(
                        grid, importedGrid->data[i])) {
                    duplicates++;
                    continue; // 跳过重复项
                }
                appendGrid(grid, importedGrid->data[i]);
            }
            printf("导入完成，共导入 %d 行数据，跳过 %d 行重复数据\n", importedGrid->len - duplicates, duplicates);
            return grid;
        }
    }
}

Grid *insert_data(Grid *grid) {
    // 新建数据行
    Row *row = createRow();
    char name[100];
    printf("请输入姓名: ");
    scanf("%s", name);
    Node *node = createNode();
    loadData(node, name);
    appendRow(row, node);
    // 创建空间
    for (int i = 1; i < 5; i++) {
        appendRow(row, createNode());
    }
    printf("已创建空记录，请添加记录\n");
    row = modify_row(row);
    appendGrid(grid, row);
    return grid; // 返回原网格
}


void browse_data(const Grid *grid) {
    if (grid == NULL || grid->len == 0) {
        printf("没有数据可供浏览\n");
        return;
    }
    printf("%-8s %-8s %-19s %-19s %-30s\n", "姓名", "籍贯", "电话1", "电话2", "邮箱");
    for (int i = 0; i < grid->len; i++) {
        print_item(grid->data[i]);
    }
}

void query_data(const Grid *grid) {
    Grid *tempGrid = select_by_name(grid);
    if (tempGrid->len == 0) {
        printf("没有找到相关数据\n");
    } else {
        printf("查询结果:\n");
        printf("%-8s %-8s %-19s %-19s %-30s\n", "姓名", "籍贯", "电话1", "电话2", "邮箱");
        for (int i = 0; i < tempGrid->len; i++) {
            print_item(tempGrid->data[i]);
        }
    }
}

Grid *modify_data(Grid *grid) {
    Grid *tempGrid = select_by_name(grid);
    if (tempGrid->len == 0) {
        printf("没有找到相关数据，无法修改\n");
        return grid;
    } else if (tempGrid->len == 1) {
        modify_item(grid, tempGrid->data[0]);
    } else if (tempGrid->len >= 2) {
        printf("存在多条记录，请选择要修改的记录:\n");
        printf("%02s %-8s %-8s %-19s %-19s %-30s\n", "  " "姓名", "籍贯", "电话1", "电话2", "邮箱");
        for (int i = 0; i < tempGrid->len; i++) {
            printf("%02d ", i);
            print_item(tempGrid->data[i]);
        }
        printf("请选择修改项的序号(输入-1取消): ");
        int index = -1;
        while (scanf("%d", &index) != 1 || index < -1 || index >= tempGrid->len) {
            printf("非法输入，请重新输入: ");
            while (getchar() != '\n') {
            } // 清空输入缓冲区
        }
        if (index == -1) {
            printf("取消修改操作\n");
            return grid;
        }
        modify_item(grid, tempGrid->data[index]);
    }
    return grid;
}

Grid *delete_data(Grid *grid) {
    Grid *tempGrid = select_by_name(grid);
    if (tempGrid->len == 0) {
        printf("没有找到相关数据，无法删除\n");
        return grid;
    } else if (tempGrid->len == 1) {
        while (getchar()!='\n') {
        } // 清空输入缓冲区
        grid = delete_item(grid, tempGrid->data[0]);
    } else if (tempGrid->len >= 2) {
        printf("存在多条记录，请选择要删除的记录:\n");
        printf("%-8s %-10s %-10s %-19s %-19s %-30s\n", "  " "姓名", "籍贯", "电话1", "电话2", "邮箱");
        for (int i = 0; i < tempGrid->len; i++) {
            printf("%02d ", i);
            print_item(tempGrid->data[i]);
        }
        printf("请选择删除项的序号(输入-1取消): ");
        int index = -1;
        while (scanf("%d", &index) != 1 || index < -1 || index >= tempGrid->len) {
            printf("非法输入，请重新输入: ");
            while (getchar() != '\n') {
            } // 清空输入缓冲区
        }
        if (index == -1) {
            printf("取消删除操作\n");
            return grid;
        }
        while (getchar() != '\n') {
        } // 清空输入缓冲区
        grid = delete_item(grid, tempGrid->data[index]);
    }
    return grid;
}

void export_data(const Grid *grid) {
    char name[100];
    printf("请输入导出文件名(相对路径和绝对路径均可): ");
    scanf("%s", name);
    if (name[0] == '\0') {
        printf("非法操作：文件名为空，中断操作\n");
        return;
    }
    saveFile(name, grid);
    printf("数据已导出到 %s\n", name);
}
