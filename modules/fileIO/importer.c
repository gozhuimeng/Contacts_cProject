//
// Created by meng on 25-5-13.
// DOC 文件数据导入器(从文件导入数据)
//

#include "importer.h"

#include "dataFormat.h"
#include "loader.h"

/**
 * 打开文件
 * @param filename
 * @return 文件指针
 */
FILE *openFile_read(char *filename) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("无法找到数据文件%s\n", filename);
        return NULL;
    }
    return file;
}

/**
 * 将文件中的数据加载到节点中
 * @param file
 * @return
 */
Node *loadNode(FILE *file) {
    Node *node = createNode(); // 创建新节点
    int ch = 0;
    while ((ch = fgetc(file)) != EOF && ch != '\n' && ch != ',') {
        // 读取字符直到换行或逗号
        appendChar(node, ch);
    }
    if (ch != EOF) {
        ungetc(ch, file); // 如果不是文件结束，回退一个字符
    }
    node->str[node->len] = '\0'; // 确保字符串以 '\0' 结尾
    return node;
}

/**
 * 将文件中的数据加载到行中
 * @param file
 * @return
 */
Row *loadRow(FILE *file) {
    Row *row = createRow(); // 创建新行
    int ch = 0;
    while ((ch = fgetc(file)) != EOF && ch != '\n') {
        // 读取字符直到换行
        if (ch != ',') {
            ungetc(ch, file); // 如果不是逗号，回退一个字符
        }
        Node *node = loadNode(file); // 调用 loadNode
        appendRow(row, node); // 将节点添加到行中
    }
    if (ch != EOF) {
        ungetc(ch, file); // 如果不是文件结束，回退一个字符
    }
    return row;
}

/**
 * 向数据表中追加数据
 * @param grid
 * @param filename
 * @return
 */
Grid *loadGrid_append(Grid *grid, char *filename) {
    FILE *file = openFile_read(filename); // 调用函数打开文件并返回文件指针
    if (file == NULL) {
        printf("文件读取异常，无法加载数据\n");
        return grid; // 如果文件打开失败，返回原网格
    }
    int ch = 0;
    while ((ch = fgetc(file)) != EOF) {
        // 读取文件直到结束
        if (ch != '\n') {
            ungetc(ch, file); // 如果不是换行符，回退一个字符
        }
        Row *row = loadRow(file); // 调用 loadRow
        appendGrid(grid, row); // 将行添加到表格中
    }
    return grid;
}

/**
 * 将文件中的数据加载到数据表中
 * @param filename
 * @return
 */
Grid *loadGrid(char *filename) {
    Grid *grid = createGrid(); // 创建新数据表
    return loadGrid_append(grid, filename); // 调用 loadGrid_append 来追加数据
}
