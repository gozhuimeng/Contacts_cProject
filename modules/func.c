//
// Created by meng on 25-5-27.
// DOC 主程序函数
//

#include <stdio.h>
#include <stdlib.h>

#include "func.h"
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
    printf("\t7. 保存数据\n");
    printf("\t8. 导出数据\n");
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
    if (check_grid_equal(grid, fileGrid)) {
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
        saveFile(DATA_FILE_NAME_OUT, grid);
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
        printf("无可导入数据，请确认数据文件格式及内容正确！\n");
        printf("中断导入操作\n");
        return grid;
    }
    // 选择导入方式
    printf("共读取到 %d 行数据\n", importedGrid->len);
    while (1) {
        printf("请选择导入方式:\n");
        printf("1. 覆盖导入\n");
        printf("2. 追加导入\n");
        printf("0. 取消导入\n");
        while (scanf("%d", &choice) != 1 && (choice == 1 || choice == 2 || choice == 0)) {
            printf("非法输入，请重新输入\n");
            while (getchar() != '\n') {
            } // 清空输入缓冲区
        }
        if (choice == 0) {
            printf("取消导入操作\n");
            return grid;
        }else if (choice == 1) {
            printf("正在导入数据\n");
            return importedGrid;
        }else if (choice == 2) {
            int duplicates = 0;
            printf("正在导入数据，将跳过重复项...\n");
            for (int i = 0; i < importedGrid->len; i++) {
                if (check_row_existing(grid,importedGrid->data[i])) {
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
