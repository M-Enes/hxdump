#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <errno.h>

#define BUFF_SIZE 1024

void print_ascii_row(char buff[BUFF_SIZE], size_t start_point, size_t end_point) {
    printf(" |");
    for (size_t j = start_point; j < end_point; j++) {
        if (buff[j] < 32 || buff[j] > 126) {
            printf(".");
        } else {
            printf("%c", buff[j]);
        }
    }
    printf("|\n");
}

void print_buffer(char buff[BUFF_SIZE], size_t read_count, uint64_t offset) {
    for (size_t i = 0; i < read_count; i += 16) {
        printf("%08llX  ", (unsigned long long)(offset + i));

        for (size_t j = 0; j < 16; j++) {
            if (i + j < read_count) {
                printf("%02X ", (unsigned char)buff[i + j]);
            } else {
                printf("   ");
            }

            if (j == 7) {
                printf(" ");
            }
        }
        size_t end_point = (i + 16 < read_count) ? i + 16 : read_count;
        print_ascii_row(buff, i, end_point);
    }
}

int main(int argc, char **argv) {
    if (argc < 2) {
        printf("You didn't give any parameters. Please use %s --help to see help.\n", argv[0]);
        exit(EXIT_SUCCESS);
    }

    if (strncmp(argv[1], "--help", 6) == 0) {
        printf("Usage: %s [OPTIONS] [FILE]\nPrints bytes of the file in hexadecimal format to standard output.\n", argv[0]);
        exit(EXIT_SUCCESS);
    }

    const char *path = argv[1];
    const char *mode = "rb";
    uint64_t offset = 0;

    FILE *file = fopen(path, mode);
    if (file == NULL) {
        fprintf(stderr, "The file %s cannot be opened. Error: %s", path, strerror(errno));
        exit(EXIT_FAILURE);
    }

    char buff[BUFF_SIZE];
    size_t read_count = 0;

    while(1) {

        read_count = fread(buff, 1, BUFF_SIZE, file);

        if (read_count > 0) {
            print_buffer(buff, read_count, offset);
            offset += read_count;
        }
        if (read_count < BUFF_SIZE) {
            if (ferror(file)) {
                fprintf(stderr, "Error while reading file %s: %s", path, strerror(errno));
                fclose(file);
                exit(EXIT_FAILURE);
            }

            printf("%08llX\n", (unsigned long long)offset);
            break;
        }

    }

    int ret = fclose(file);
    if (ret != 0) {
        fprintf(stderr, "Error while closing file %s: %s", path, strerror(errno));
        exit(EXIT_FAILURE);
    }

    return 0;
}
