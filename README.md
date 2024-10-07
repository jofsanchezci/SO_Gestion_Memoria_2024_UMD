
# Implementaciones en C para la Gestión de Memoria en Sistemas Operativos

Este proyecto incluye ejemplos de implementación en C de los principales conceptos de gestión de memoria en sistemas operativos: paginación, segmentación y swapping (intercambio). Estos ejemplos están diseñados para ilustrar cómo se gestionan diferentes áreas de la memoria en un entorno simulado.

## 1. Paginación

En paginación, la memoria se divide en bloques de tamaño fijo llamados **páginas**. Estas páginas pueden cargarse en cualquier marco de la memoria física. 

```c
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
```




### Archivos relevantes:
- **pagination.c**

### Conceptos cubiertos:
- Tabla de páginas
- Carga de páginas en memoria
- Liberación de páginas

### Ejemplo de uso:

```c
PageTableEntry page_table[NUM_PAGES];
load_page(0, page_table);  // Cargar página 0
free_page(0, page_table);  // Liberar página 0
```

---

## 2. Segmentación

En segmentación, la memoria se divide en segmentos de tamaño variable que representan diferentes partes lógicas del programa, como el código, los datos y la pila.

### Archivos relevantes:
- **segmentation.c**

### Conceptos cubiertos:
- Tabla de segmentos
- Asignación de segmentos en la memoria
- Liberación de segmentos


```c
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

```

### Ejemplo de uso:

```c
SegmentTableEntry segment_table[3];
load_segment(0, 1024, segment_table);  // Asignar segmento de código
free_segment(0, segment_table);        // Liberar segmento de código
```

---

## 3. Swapping (Intercambio)

Swapping es una técnica mediante la cual el sistema operativo intercambia procesos entre la **memoria principal** (RAM) y el **almacenamiento secundario** (disco). En este ejemplo, el proceso se mueve desde la memoria a un área de swap simulada y viceversa.

### Archivos relevantes:
- **swapping.c**

### Conceptos cubiertos:
- Carga de procesos desde el área de swap a la memoria
- Mover procesos de la memoria al área de swap
```c
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

```


### Ejemplo de uso:

```c
Process process1 = {1, SWAP_SIZE, NULL, NULL};
swap_in(&process1);  // Cargar proceso a la memoria
swap_out(&process1); // Mover proceso al área de swap
```

---

## Compilación

Puedes compilar cualquiera de los ejemplos usando un compilador como `gcc`. Por ejemplo, para compilar el archivo `pagination.c`:

```bash
gcc -o pagination pagination.c
```

---

## Ejecución

Para ejecutar cualquier archivo compilado, simplemente utiliza el comando:

```bash
./pagination
```

Repite esto para los otros archivos según sea necesario.

---

## Requisitos

- Compilador C (gcc u otro)
- Sistema Linux, MacOS o Windows con soporte para compilación de código en C

---


