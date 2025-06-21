//
// Created by meng on 25-5-21.
// DOC 主程序
//

#include <stdio.h>
#include <stdlib.h>

#include "modules/fileIO/config.h"
#include "modules/fileIO/dataFormat.h"
#include "modules/fileIO/importer.h"
#include "modules/func.h"

/**
 * 主函数
 * @return
 */
int main() {
    system("chcp 65001 > nul");

    // 数据初始化
    printf("正在加载数据...\n");
    Grid *grid = loadGrid(DATA_FILE_NAME);
    printf("数据加载完成\n");

    int choice = 0;
    while (1) {
        print_menu();
        if (scanf("%d", &choice) != 1) {
            printf("非法输入，请重新输入\n");
            while (getchar() != '\n') {
            } // 清空输入缓冲区
            continue;
        }
        getchar(); // 清除换行符
        switch (choice) {
            case 0:
                quit(grid);
                break;
            case 1:
                grid = import_data(grid);
                break;
            case 2:
                grid = insert_data(grid);
                break;
            case 3:
                browse_data(grid);
                break;
            case 4:
                query_data(grid);
                break;
            case 5:
                grid = modify_data(grid);
                break;
            case 6:
                grid = delete_data(grid);
                break;
            case 7:
                export_data(grid);
                break;
            default:
                printf("非法输入，请输入操作选项序号！\n");
        }
    }
}
