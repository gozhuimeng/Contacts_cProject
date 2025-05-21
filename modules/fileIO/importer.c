//
// Created by meng on 25-5-13.
// DOC �ļ����ݵ�����(���ļ���������)
//

#include "importer.h"
#include "dataFormat.h"
#include "loader.h"

/**
 * ���ļ�
 * @param filename
 * @return �ļ�ָ��
 */
FILE *openFile_read(char *filename) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("�޷����ļ�%s", filename);
        return NULL;
    }
    return file;
}

/**
 * ���ļ��е����ݼ��ص��ڵ���
 * @param file
 * @return
 */
Node *loadNode(FILE *file) {
    Node *node = createNode();
    int ch = 0;
    while ((ch = fgetc(file)) != EOF && ch != '\n' && ch != ',') {
        appendChar(node, ch);
    }
    if (ch != EOF) {
        ungetc(ch, file);
    }
    node->str[node->len] = '\0';
    return node;
}

/**
 * ���ļ��е����ݼ��ص�����
 * @param file
 * @return
 */
Row *loadRow(FILE *file) {
    Row *row = createRow();
    int ch = 0;
    while ((ch = fgetc(file)) != EOF && ch != '\n') {
        if (ch != ',') {
            ungetc(ch, file);
        }
        Node * node = loadNode(file);
        appendRow(row, node);
    }
    if (ch!=EOF) {
        ungetc(ch, file);
    }
    return row;
}

/**
 * ���ļ��е����ݼ��ص�������
 * @param filename
 * @return
 */
Grid *loadGrid(char *filename) {
    FILE *file = openFile_read(filename);
    Grid *grid = createGrid();
    int ch = 0;
    while ((ch = fgetc(file)) != EOF ) {
        if (ch != '\n') {
            ungetc(ch, file);
        }
        Row * row = loadRow(file);
        appendGrid(grid, row);
    }
    return grid;
}

