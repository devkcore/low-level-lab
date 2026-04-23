#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

/*
 * devkcore | low-level-lab
 *
 * Minimal ELF header validator.
 * Performs raw magic byte inspection (0x7F 'E' 'L' 'F')
 * as a preliminary step for binary analysis / memory forensics workflows.
 *
 * kernel is memory._
 */

#define ELF_MAGIC_SIZE 4

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <file>\n", argv[0]);
        return EXIT_FAILURE;
    }

    FILE *fp = fopen(argv[1], "rb");
    if (!fp) {
        perror("fopen");
        return EXIT_FAILURE;
    }

    uint8_t magic[ELF_MAGIC_SIZE];
    size_t read_bytes = fread(magic, 1, ELF_MAGIC_SIZE, fp);

    if (read_bytes != ELF_MAGIC_SIZE) {
        if (ferror(fp)) {
            perror("fread");
        } else {
            fprintf(stderr, "Error: File too small (< 4 bytes)\n");
        }
        fclose(fp);
        return EXIT_FAILURE;
    }

    fclose(fp);

    const uint8_t elf_magic[ELF_MAGIC_SIZE] = {0x7f, 'E', 'L', 'F'};

    if (memcmp(magic, elf_magic, ELF_MAGIC_SIZE) == 0) {
        printf("[+] Valid ELF header detected. Ready for analysis.\n");
        return EXIT_SUCCESS;
    }

    printf("[-] Not a valid ELF file.\n");
    return EXIT_FAILURE;
}
