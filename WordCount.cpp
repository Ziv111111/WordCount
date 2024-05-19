#include <stdio.h>
#include <stdlib.h>
#include <ctype.h> // 用于isalpha, isspace等函数
#include <cstring>
int countCharacters(const char *filename);
int countWords(const char *filename);

int main(int argc, char *argv[]) {
    if (argc != 3) {
        printf("Usage: %s [-c|-w] filename\n", argv[0]);
        return 1;
    }

    const char *param = argv[1];
    const char *filename = argv[2];

    if (strcmp(param, "-c") == 0) {
        printf("字符数:%d\n", countCharacters(filename));
    } else if (strcmp(param, "-w") == 0) {
        printf("单词数:%d\n", countWords(filename));
    } else {
        printf("错误的参数，请使用'-c'统计字符数或'-w'统计单词数。\n");
        return 1;
    }

    return 0;
}

int countCharacters(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        perror("无法打开文件");
        exit(EXIT_FAILURE);
    }

    int count = 0;
    char ch;
    while ((ch = fgetc(file)) != EOF) {
        if (!isspace(ch)) { // 统计非空白字符
            count++;
        }
    }
    fclose(file);
    return count;
}

int countWords(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        perror("无法打开文件");
        exit(EXIT_FAILURE);
    }

    int count = 0;
    int inWord = 0; // 标记是否在单词内部
    char ch;
    while ((ch = fgetc(file)) != EOF) {
        if (isalpha(ch) || ch == ',' || ch == '#') { // 字母、逗号、# 视为单词的一部分
            if (!inWord) {
                count++; // 新单词开始
                inWord = 1;
            }
        } else if (isspace(ch)) {
            inWord = 0; // 遇到空格，单词结束
        }
    }
    fclose(file);
    return count;
}
