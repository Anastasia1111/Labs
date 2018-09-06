#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main(int argc, char **argv) {
    if(argc == 1) {
        printf("Too few parameters. Type --help for help.\n");
        return EXIT_FAILURE;
    }

    if(!strcmp(argv[1], "--help")) {
        printf("Syntax:\n\t--file [filename] - set input file.\n\t--out [filename] - set output file (optional).\n");
        return EXIT_SUCCESS;
    }

    if(!strcmp(argv[1], "--file")) {
        if (argc > 2) {
            FILE *in = fopen(argv[2], "rb");
            if (in == NULL) {
                printf("Can't open file '%s'.\n", argv[2]);
                return EXIT_FAILURE;
            }

            int crc = 0xFFFFFFFF, polynom = 0x04C11DB7, ch;
            char bit;
            while ((ch = getc(in)) != EOF) {
                for (int j = 0; j < 8; ++j) {
                    bit = ((ch >> (7 - j)) & 1) ^ ((crc >> 15) & 1);
                    crc = crc << 1;
                    if (bit) {
                        crc = crc ^ polynom;
                    }
                }
            }
            fclose(in);
            if (argc >= 4) {
                if (argc == 4) {
                    if (!strcmp(argv[3], "--out")) {
                        printf("Needs output file name. Type --help for help.\n");
                    } else {
                        printf("Unknown parameter: '%s'. Type --help for help.\n", argv[1]);
                    }
                    return EXIT_FAILURE;
                }

                if (argc <= 5) {
                    FILE *out = fopen(argv[4], "wb");
                    if (out == NULL) {
                        printf("Can't open file '%s'.\n", argv[4]);
                        return EXIT_FAILURE;
                    }

                    fwrite(&crc, sizeof(int), 1, out);
                    fclose(out);
                } else {
                    printf("Too many parameters. Type --help for help.\n");
                    return EXIT_FAILURE;
                }
            }
            printf("CRC: %x\n", crc);
            return EXIT_SUCCESS;
        } else {
            printf("Needs input file name. Type --help for help.\n");
            return EXIT_FAILURE;
        }
    }

    if(!strcmp(argv[1], "--out"))
        printf("Needs input file. Type --help for help.\n");
    else
        printf("Unknown parameter: '%s'. Type --help for help.\n", argv[1]);

    return EXIT_FAILURE;
}