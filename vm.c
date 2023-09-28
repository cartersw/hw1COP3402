#include <stdio.h>
#include <stdlib.h>
#include "machine_types.h"
#include "instruction.h"

// a s i z e f o r t h e memory ( 2 ^ 1 6 b y t e s = 64K )

#define MEMORY_SIZE_IN_BYTES (65536 - BYTES_PER_WORD)
#define MEMORY_SIZE_IN_WORDS (MEMORY_SIZE_IN_BYTES / BYTES_PER_WORD)

#define NUM_GENERAL_PURPOSE_REGISTERS 32

typedef struct {
    // General Purpose Registers
    int GPR[NUM_GENERAL_PURPOSE_REGISTERS];

    // Special Purpose Registers
    int PC;        // Program Counter
    int IR;        // Instruction Register
    int MAR;       // Memory Address Register
    int MBR;       // Memory Buffer Register
    int STATUS;    // Processor Status Register (for flags like zero, negative, overflow, etc.)
    

} RISC_Registers;

// Initialize the registers
void initialize_registers(RISC_Registers* regs) {
    for (int i = 0; i < NUM_GENERAL_PURPOSE_REGISTERS; i++) {
        regs->GPR[i] = 0;
    }
    regs->PC = 0;
    regs->IR = 0;
    regs->MAR = 0;
    regs->MBR = 0;
    regs->STATUS = 0;
}

static union mem_u {
    byte_type bytes[MEMORY_SIZE_IN_BYTES];
    word_type words[MEMORY_SIZE_IN_WORDS];
    bin_instr_t instrs[MEMORY_SIZE_IN_WORDS];
} memory;

int main(void) {
    RISC_Registers regs;
    initialize_registers(&regs);

    // Accessing a general-purpose register
    regs.GPR[5] = 100;

    // Incrementing the program counter
    regs.PC++;

    // ... your simulation code ...

    FILE *file;
    char *buffer;
    long file_size;

    // Open the file in binary read mode
    file = fopen("example.bof", "rb");
    if (!file) {
        perror("Error opening file");
        return 1;
    }

    // Get the size of the file
    fseek(file, 0, SEEK_END);
    file_size = ftell(file);
    fseek(file, 0, SEEK_SET);

    // Allocate memory for the buffer
    buffer = (char *)malloc(file_size);
    if (!buffer) {
        perror("Memory allocation failed");
        fclose(file);
        return 1;
    }

    // Read the file into the buffer
    fread(buffer, 1, file_size, file);
    fclose(file);

    // At this point, the content of the BOF is in the buffer
    // You can process it as per your RISC machine's specifications
    // ...

    // Don't forget to free the buffer after use
    free(buffer);

    return 0;
}
