#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h> // ����isalnum����

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
        if (isalnum(ch)) { // �������ĸ������
            if (!in_word) { // �����µ��ʵĿ�ʼ
                in_word = 1;
                count++;
            }
        } else { // ��������ĸ���֣���ǰ���ʽ���
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
        printf("�ַ���: %d\n", count);
    } else if (strcmp(option, "-w") == 0) {
        count = count_words(file);
        printf("������: %d\n", count);
    } else {
        printf("Error: Invalid option %s\n", option);
        return 1;
    }

    fclose(file);
    return 0;
}