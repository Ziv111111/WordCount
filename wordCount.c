#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h> // 用于isalnum函数

int count_characters(FILE *file) {
    int count = 0;
    char ch;
    while ((ch = fgetc(file)) != EOF) {
        count++;
    }
    return count;
}

int count_words(FILE *file) {
    int count = 0;
    int in_word = 0;
    char ch;
    while ((ch = fgetc(file)) != EOF) {
        if (isalnum(ch)) { // 如果是字母或数字
            if (!in_word) { // 遇到新单词的开始
                in_word = 1;
                count++;
            }
        } else { // 遇到非字母数字，当前单词结束
            in_word = 0;
        }
    }
    return count;
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        printf("Usage: %s [-c | -w] [input_file]\n", argv[0]);
        return 1;
    }

    char *option = argv[1];
    char *filename = argv[2];

    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("Error: Unable to open file %s\n", filename);
        return 1;
    }

    int count;
    if (strcmp(option, "-c") == 0) {
        count = count_characters(file);
        printf("字符数: %d\n", count);
    } else if (strcmp(option, "-w") == 0) {
        count = count_words(file);
        printf("单词数: %d\n", count);
    } else {
        printf("Error: Invalid option %s\n", option);
        return 1;
    }

    fclose(file);
    return 0;
}