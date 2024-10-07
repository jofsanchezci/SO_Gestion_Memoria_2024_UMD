#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SWAP_SIZE 1024  // Tamaño de cada segmento en el área de swap

typedef struct {
    int process_id;
    size_t size;
    void *memory_address;
    void *swap_area;  // Área en disco (simulada)
} Process;

// Función para mover un proceso a la memoria
void swap_in(Process *process) {
    process->memory_address = malloc(process->size);
    if (process->memory_address == NULL) {
        printf("Error: No se pudo asignar memoria para el proceso %d.\n", process->process_id);
        return;
    }
    memcpy(process->memory_address, process->swap_area, process->size);
    printf("Proceso %d movido a memoria desde el área de swap.\n", process->process_id);
}

// Función para mover un proceso al área de swap
void swap_out(Process *process) {
    process->swap_area = malloc(SWAP_SIZE);
    if (process->swap_area == NULL) {
        printf("Error: No se pudo asignar espacio en el área de swap.\n");
        return;
    }
    memcpy(process->swap_area, process->memory_address, process->size);
    free(process->memory_address);
    process->memory_address = NULL;
    printf("Proceso %d movido al área de swap.\n", process->process_id);
}

int main() {
    Process process1 = {1, SWAP_SIZE, NULL, NULL};

    // Cargar proceso en memoria
    swap_in(&process1);

    // Simular procesamiento
    printf("Accediendo a proceso 1 en la memoria en %p.\n", process1.memory_address);

    // Mover proceso al área de swap
    swap_out(&process1);

    // Liberar área de swap
    free(process1.swap_area);

    return 0;
}
