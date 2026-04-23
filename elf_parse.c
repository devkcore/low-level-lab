#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <elf.h>

/*
 * devkcore | low-level-lab
 *
 * ELF header parser.
 * Reads and interprets the ELF64 header structure directly
 * from disk for binary analysis purposes.
 *
 * kernel is memory._
 */

void print_class(unsigned char class) {
    switch (class) {
        case ELFCLASS32: printf("ELF32\n"); break;
        case ELFCLASS64: printf("ELF64\n"); break;
        default: printf("Unknown\n");
    }
}

void print_data(unsigned char data) {
    switch (data) {
        case ELFDATA2LSB: printf("Little Endian\n"); break;
        case ELFDATA2MSB: printf("Big Endian\n"); break;
        default: printf("Unknown\n");
    }
}

void print_type(uint16_t type) {
    switch (type) {
        case ET_EXEC: printf("Executable\n"); break;
        case ET_DYN:  printf("Shared Object\n"); break;
        case ET_REL:  printf("Relocatable\n"); break;
        default: printf("Other\n");
    }
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <ELF file>\n", argv[0]);
        return EXIT_FAILURE;
    }

    FILE *fp = fopen(argv[1], "rb");
    if (!fp) {
        perror("fopen");
        return EXIT_FAILURE;
    }

    Elf64_Ehdr header;

    if (fread(&header, 1, sizeof(header), fp) != sizeof(header)) {
        perror("fread");
        fclose(fp);
        return EXIT_FAILURE;
    }

    fclose(fp);

    // Check magic
    if (header.e_ident[EI_MAG0] != ELFMAG0 ||
        header.e_ident[EI_MAG1] != ELFMAG1 ||
        header.e_ident[EI_MAG2] != ELFMAG2 ||
        header.e_ident[EI_MAG3] != ELFMAG3) {
        fprintf(stderr, "Not a valid ELF file.\n");
        return EXIT_FAILURE;
    }

    printf("== ELF Header ==\n");

    printf("Class:      ");
    print_class(header.e_ident[EI_CLASS]);

    printf("Data:       ");
    print_data(header.e_ident[EI_DATA]);

    printf("Type:       ");
    print_type(header.e_type);

    printf("Machine:    0x%x\n", header.e_machine);
    printf("Entry:      0x%lx\n", header.e_entry);

    return EXIT_SUCCESS;
}
