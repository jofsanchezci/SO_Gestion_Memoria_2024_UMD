#include <stdio.h>
#include <stdlib.h>

#define PAGE_SIZE 1024  // Tamaño de la página en bytes
#define NUM_PAGES 4     // Número de páginas

typedef struct {
    int page_number;
    void *frame_address;  // Dirección de marco en la memoria física
} PageTableEntry;

// Función para cargar una página en memoria
void load_page(int page_number, PageTableEntry *page_table) {
    page_table[page_number].frame_address = malloc(PAGE_SIZE);  // Simular la carga de la página en memoria
    if (page_table[page_number].frame_address == NULL) {
        printf("Error: No se pudo cargar la página en memoria.\n");
        return;
    }
    printf("Página %d cargada en la dirección %p.\n", page_number, page_table[page_number].frame_address);
}

// Función para liberar una página
void free_page(int page_number, PageTableEntry *page_table) {
    free(page_table[page_number].frame_address);
    page_table[page_number].frame_address = NULL;
    printf("Página %d liberada de la memoria.\n", page_number);
}

int main() {
    PageTableEntry page_table[NUM_PAGES];

    // Inicializar la tabla de páginas
    for (int i = 0; i < NUM_PAGES; i++) {
        page_table[i].page_number = i;
        page_table[i].frame_address = NULL;
    }

    // Cargar las páginas 0 y 1 en memoria
    load_page(0, page_table);
    load_page(1, page_table);

    // Simular acceso a los datos en las páginas
    printf("Accediendo a datos en la página 0 en %p.\n", page_table[0].frame_address);
    printf("Accediendo a datos en la página 1 en %p.\n", page_table[1].frame_address);

    // Liberar las páginas cuando ya no se necesitan
    free_page(0, page_table);
    free_page(1, page_table);

    return 0;
}
