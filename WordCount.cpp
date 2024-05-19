#include <stdio.h>
#include <stdlib.h>
#include <ctype.h> // ����isalpha, isspace�Ⱥ���
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
        printf("�ַ���:%d\n", countCharacters(filename));
    } else if (strcmp(param, "-w") == 0) {
        printf("������:%d\n", countWords(filename));
    } else {
        printf("����Ĳ�������ʹ��'-c'ͳ���ַ�����'-w'ͳ�Ƶ�������\n");
        return 1;
    }

    return 0;
}

int countCharacters(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        perror("�޷����ļ�");
        exit(EXIT_FAILURE);
    }

    int count = 0;
    char ch;
    while ((ch = fgetc(file)) != EOF) {
        if (!isspace(ch)) { // ͳ�Ʒǿհ��ַ�
            count++;
        }
    }
    fclose(file);
    return count;
}

int countWords(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        perror("�޷����ļ�");
        exit(EXIT_FAILURE);
    }

    int count = 0;
    int inWord = 0; // ����Ƿ��ڵ����ڲ�
    char ch;
    while ((ch = fgetc(file)) != EOF) {
        if (isalpha(ch) || ch == ',' || ch == '#') { // ��ĸ�����š�# ��Ϊ���ʵ�һ����
            if (!inWord) {
                count++; // �µ��ʿ�ʼ
                inWord = 1;
            }
        } else if (isspace(ch)) {
            inWord = 0; // �����ո񣬵��ʽ���
        }
    }
    fclose(file);
    return count;
}
