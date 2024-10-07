#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int segment_number;
    size_t size;         // Tamaño del segmento
    void *base_address;  // Dirección base del segmento en la memoria
} SegmentTableEntry;

// Función para asignar un segmento en la memoria
void load_segment(int segment_number, size_t size, SegmentTableEntry *segment_table) {
    segment_table[segment_number].base_address = malloc(size);
    segment_table[segment_number].size = size;
    if (segment_table[segment_number].base_address == NULL) {
        printf("Error: No se pudo asignar el segmento.\n");
        return;
    }
    printf("Segmento %d asignado con tamaño %lu bytes en la dirección %p.\n", segment_number, size, segment_table[segment_number].base_address);
}

// Función para liberar un segmento de memoria
void free_segment(int segment_number, SegmentTableEntry *segment_table) {
    free(segment_table[segment_number].base_address);
    segment_table[segment_number].base_address = NULL;
    printf("Segmento %d liberado de la memoria.\n", segment_number);
}

int main() {
    SegmentTableEntry segment_table[3];  // Simular 3 segmentos

    // Asignar segmentos
    load_segment(0, 1024, segment_table);  // Código
    load_segment(1, 2048, segment_table);  // Datos
    load_segment(2, 512, segment_table);   // Pila

    // Simular acceso a los segmentos
    printf("Accediendo a segmento de código en %p.\n", segment_table[0].base_address);
    printf("Accediendo a segmento de datos en %p.\n", segment_table[1].base_address);

    // Liberar los segmentos
    free_segment(0, segment_table);
    free_segment(1, segment_table);
    free_segment(2, segment_table);

    return 0;
}
