// ============================================================
// PROYECTO 3A - COMPRESOR/DESCOMPRESOR DE HUFFMAN
// Estudiante: Lee Sang Cheol (Diego)
// Carné: 2024801079
// Fecha: Octubre 2025
// Descripción: Implementación del algoritmo de Huffman
//              para compresión y descompresión de archivos
// ============================================================

#include <stdio.h>
#include <iostream>
#include <string>
#include <queue>
#include <map>
#include <fstream>

using namespace std;

// ============================================================
// ESTRUCTURAS DE DATOS
// ============================================================

// Nodo del árbol de Huffman
struct HuffmanNode {
    unsigned char simbolo;      // Carácter (0-255)
    int frecuencia;             // Frecuencia de aparición
    HuffmanNode* izquierda;     // Hijo izquierdo (0)
    HuffmanNode* derecha;       // Hijo derecho (1)

    // Constructor para nodos hoja (símbolos)
    HuffmanNode(unsigned char s, int f) {
        simbolo = s;
        frecuencia = f;
        izquierda = derecha = NULL;
    }

    // Constructor para nodos internos
    HuffmanNode(int f, HuffmanNode* izq, HuffmanNode* der) {
        simbolo = '\0';  // No representa ningún símbolo
        frecuencia = f;
        izquierda = izq;
        derecha = der;
    }
};

// Comparador para la cola de prioridad (min-heap)
struct CompararNodos {
    bool operator()(HuffmanNode* a, HuffmanNode* b) {
        // Menor frecuencia = mayor prioridad
        return a->frecuencia > b->frecuencia;
    }
};

// ============================================================
// VARIABLES GLOBALES
// ============================================================

int tablaFrecuencias[256] = { 0 };           // Frecuencia de cada byte
string tablaCodigos[256];                   // Código Huffman de cada byte
map<string, unsigned char> tablaDecode;     // Para decodificar: código -> símbolo

// ============================================================
// PASO 1: CALCULAR FRECUENCIAS
// ============================================================

int CalcularFrecuencias(const char* nombreArchivo) {
    FILE* archivo;
    fopen_s(&archivo, nombreArchivo, "rb");

    if (archivo == NULL) {
        printf("ERROR: No se puede abrir el archivo %s\n", nombreArchivo);
        return -1;
    }

    // Inicializar tabla de frecuencias
    for (int i = 0; i < 256; i++) {
        tablaFrecuencias[i] = 0;
    }

    // Contar frecuencias
    unsigned char byte;
    int totalBytes = 0;

    while (fread(&byte, 1, 1, archivo) == 1) {
        tablaFrecuencias[byte]++;
        totalBytes++;
    }

    fclose(archivo);

    printf("\n=== TABLA DE FRECUENCIAS ===\n");
    printf("Símbolo  | Cantidad | Probabilidad\n");
    printf("---------|----------|-------------\n");

    for (int i = 0; i < 256; i++) {
        if (tablaFrecuencias[i] > 0) {
            char simbolo = (i >= 32 && i <= 126) ? i : '?';
            double prob = (double)tablaFrecuencias[i] / totalBytes;
            printf("  '%c' (%d) |   %5d   |   %.4f\n",
                simbolo, i, tablaFrecuencias[i], prob);
        }
    }
    printf("TOTAL: %d bytes\n\n", totalBytes);

    return totalBytes;
}

// ============================================================
// PASO 2: CONSTRUIR ÁRBOL DE HUFFMAN
// ============================================================

HuffmanNode* ConstruirArbolHuffman() {
    // Cola de prioridad (min-heap) para construir el árbol
    priority_queue<HuffmanNode*, vector<HuffmanNode*>, CompararNodos> cola;

    // Agregar todos los símbolos con frecuencia > 0
    for (int i = 0; i < 256; i++) {
        if (tablaFrecuencias[i] > 0) {
            cola.push(new HuffmanNode((unsigned char)i, tablaFrecuencias[i]));
        }
    }

    printf("=== CONSTRUCCIÓN DEL ÁRBOL ===\n");
    printf("Símbolos únicos: %d\n\n", (int)cola.size());

    // Construir árbol de Huffman
    while (cola.size() > 1) {
        // Tomar los 2 nodos con menor frecuencia
        HuffmanNode* izq = cola.top();
        cola.pop();

        HuffmanNode* der = cola.top();
        cola.pop();

        // Crear nodo padre
        int frecuenciaPadre = izq->frecuencia + der->frecuencia;
        HuffmanNode* padre = new HuffmanNode(frecuenciaPadre, izq, der);

        // Insertar padre de vuelta en la cola
        cola.push(padre);
    }

    // El último nodo es la raíz
    HuffmanNode* raiz = cola.top();
    printf("Árbol construido. Frecuencia total: %d\n\n", raiz->frecuencia);

    return raiz;
}

// ============================================================
// PASO 3: GENERAR CÓDIGOS HUFFMAN
// ============================================================

void GenerarCodigos(HuffmanNode* nodo, string codigoActual) {
    if (nodo == NULL) return;

    // Si es nodo hoja (símbolo)
    if (nodo->izquierda == NULL && nodo->derecha == NULL) {
        tablaCodigos[nodo->simbolo] = codigoActual;
        tablaDecode[codigoActual] = nodo->simbolo;
        return;
    }

    // Recursión: izquierda = 0, derecha = 1
    GenerarCodigos(nodo->izquierda, codigoActual + "0");
    GenerarCodigos(nodo->derecha, codigoActual + "1");
}

void MostrarCodigos() {
    printf("=== TABLA DE CÓDIGOS HUFFMAN ===\n");
    printf("Símbolo | ASCII | Código Huffman | Bits\n");
    printf("--------|-------|----------------|-----\n");

    for (int i = 0; i < 256; i++) {
        if (tablaFrecuencias[i] > 0) {
            char simbolo = (i >= 32 && i <= 126) ? i : '?';
            printf("  '%c'    |  %3d  | %-14s | %2d\n",
                simbolo, i, tablaCodigos[i].c_str(),
                (int)tablaCodigos[i].length());
        }
    }
    printf("\n");
}

// ============================================================
// PASO 4: COMPRIMIR ARCHIVO
// ============================================================

void ComprimirArchivo(const char* archivoOrigen, const char* archivoDestino) {
    // Abrir archivos
    FILE* origen, * destino;
    fopen_s(&origen, archivoOrigen, "rb");
    fopen_s(&destino, archivoDestino, "wb");

    if (origen == NULL || destino == NULL) {
        printf("ERROR: No se pueden abrir los archivos\n");
        return;
    }

    printf("=== COMPRIMIENDO ===\n");

    // PARTE 1: ESCRIBIR HEADER
    // Formato: [NUM_SIMBOLOS] [SIMBOLO CODIGO]... [SIZE]

    // Contar símbolos únicos
    int numSimbolos = 0;
    for (int i = 0; i < 256; i++) {
        if (tablaFrecuencias[i] > 0) numSimbolos++;
    }

    // Escribir número de símbolos
    fwrite(&numSimbolos, sizeof(int), 1, destino);

    // Escribir tabla de códigos
    for (int i = 0; i < 256; i++) {
        if (tablaFrecuencias[i] > 0) {
            unsigned char simbolo = (unsigned char)i;
            int longitudCodigo = tablaCodigos[i].length();

            fwrite(&simbolo, sizeof(unsigned char), 1, destino);
            fwrite(&longitudCodigo, sizeof(int), 1, destino);
            fwrite(tablaCodigos[i].c_str(), sizeof(char), longitudCodigo, destino);
        }
    }

    // Calcular SIZE (bytes del archivo original)
    fseek(origen, 0, SEEK_END);
    int SIZE = ftell(origen);
    fseek(origen, 0, SEEK_SET);

    // Escribir SIZE
    fwrite(&SIZE, sizeof(int), 1, destino);

    printf("Header escrito: %d símbolos, SIZE=%d bytes\n", numSimbolos, SIZE);

    // PARTE 2: ESCRIBIR DATOS COMPRIMIDOS

    string bufferBits = "";  // Buffer para acumular bits
    unsigned char byte;
    int bitsEscritos = 0;
    int bytesOriginales = 0;

    // Leer archivo byte por byte y convertir a códigos Huffman
    while (fread(&byte, 1, 1, origen) == 1) {
        bufferBits += tablaCodigos[byte];
        bytesOriginales++;

        // Cuando tengamos 8 o más bits, escribir bytes completos
        while (bufferBits.length() >= 8) {
            unsigned char byteComprimido = 0;

            // Convertir primeros 8 bits a byte
            for (int i = 0; i < 8; i++) {
                if (bufferBits[i] == '1') {
                    byteComprimido |= (1 << (7 - i));
                }
            }

            fwrite(&byteComprimido, 1, 1, destino);
            bufferBits = bufferBits.substr(8);  // Remover bits escritos
            bitsEscritos += 8;
        }
    }

    // Escribir bits restantes (padding con ceros)
    if (bufferBits.length() > 0) {
        unsigned char byteComprimido = 0;
        for (int i = 0; i < bufferBits.length(); i++) {
            if (bufferBits[i] == '1') {
                byteComprimido |= (1 << (7 - i));
            }
        }
        fwrite(&byteComprimido, 1, 1, destino);
        bitsEscritos += bufferBits.length();
    }

    fclose(origen);
    fclose(destino);

    // Calcular estadísticas
    int bytesComprimidos = (bitsEscritos + 7) / 8;  // Redondear hacia arriba
    double ratio = 100.0 * (bytesOriginales - bytesComprimidos) / bytesOriginales;

    printf("\nCompresión completada:\n");
    printf("  Bytes originales:   %d\n", bytesOriginales);
    printf("  Bits comprimidos:   %d\n", bitsEscritos);
    printf("  Bytes comprimidos:  %d\n", bytesComprimidos);
    printf("  Compresión lograda: %.2f%%\n\n", ratio);
}

// ============================================================
// PASO 5: DESCOMPRIMIR ARCHIVO
// ============================================================

void DescomprimirArchivo(const char* archivoComprimido, const char* archivoSalida) {
    FILE* origen, * destino;
    fopen_s(&origen, archivoComprimido, "rb");
    fopen_s(&destino, archivoSalida, "wb");

    if (origen == NULL || destino == NULL) {
        printf("ERROR: No se pueden abrir los archivos\n");
        return;
    }

    printf("=== DESCOMPRIMIENDO ===\n");

    // PARTE 1: LEER HEADER

    // Limpiar tabla de decodificación
    tablaDecode.clear();

    // Leer número de símbolos
    int numSimbolos;
    fread(&numSimbolos, sizeof(int), 1, origen);

    printf("Leyendo header: %d símbolos\n", numSimbolos);

    // Leer tabla de códigos
    for (int i = 0; i < numSimbolos; i++) {
        unsigned char simbolo;
        int longitudCodigo;
        char codigo[256];

        fread(&simbolo, sizeof(unsigned char), 1, origen);
        fread(&longitudCodigo, sizeof(int), 1, origen);
        fread(codigo, sizeof(char), longitudCodigo, origen);
        codigo[longitudCodigo] = '\0';

        tablaDecode[string(codigo)] = simbolo;
    }

    // Leer SIZE
    int SIZE;
    fread(&SIZE, sizeof(int), 1, origen);

    printf("SIZE original: %d bytes\n", SIZE);
    printf("Tabla de decodificación cargada\n\n");

    // PARTE 2: LEER Y DECODIFICAR DATOS

    string codigoActual = "";
    int bytesDescomprimidos = 0;
    unsigned char byte;

    printf("Descomprimiendo");

    while (bytesDescomprimidos < SIZE && fread(&byte, 1, 1, origen) == 1) {
        // Leer byte bit por bit
        for (int i = 7; i >= 0 && bytesDescomprimidos < SIZE; i--) {
            // Extraer bit
            int bit = (byte >> i) & 1;
            codigoActual += (bit ? '1' : '0');

            // Buscar en tabla de decodificación
            if (tablaDecode.find(codigoActual) != tablaDecode.end()) {
                unsigned char simbolo = tablaDecode[codigoActual];
                fwrite(&simbolo, 1, 1, destino);
                bytesDescomprimidos++;
                codigoActual = "";

                if (bytesDescomprimidos % 1000 == 0) {
                    printf(".");
                }
            }
        }
    }

    fclose(origen);
    fclose(destino);

    printf(" ¡COMPLETADO!\n");
    printf("Bytes descomprimidos: %d\n\n", bytesDescomprimidos);
}

// ============================================================
// FUNCIÓN PRINCIPAL
// ============================================================

int main(int argc, char* argv[]) {
    cout << "\n";
    cout << "========================================\n";
    cout << "  COMPRESOR/DESCOMPRESOR DE HUFFMAN\n";
    cout << "  Proyecto 3A - Lee Sang Cheol\n";
    cout << "========================================\n\n";

    // Validar argumentos
    if (argc < 3) {
        cout << "Uso:\n";
        cout << "  COMPRIMIR:\n";
        cout << "    " << argv[0] << " c [archivo_origen]\n\n";
        cout << "  DESCOMPRIMIR:\n";
        cout << "    " << argv[0] << " d [archivo_comprimido]\n\n";
        cout << "Ejemplos:\n";
        cout << "  " << argv[0] << " c documento.txt\n";
        cout << "  " << argv[0] << " d documento.txt.huf\n\n";
        return -1;
    }

    char opcion = argv[1][0];

    // ========================================
    // MODO COMPRESIÓN
    // ========================================

    if (opcion == 'c') {
        const char* archivoOrigen = argv[2];

        // Generar nombre del archivo comprimido
        string archivoDestino = string(archivoOrigen) + ".huf";

        printf("Archivo origen: %s\n", archivoOrigen);
        printf("Archivo destino: %s\n\n", archivoDestino.c_str());

        // PASO 1: Calcular frecuencias
        int totalBytes = CalcularFrecuencias(archivoOrigen);
        if (totalBytes <= 0) {
            printf("ERROR: Archivo vacío o no se puede leer\n");
            return -1;
        }

        // PASO 2: Construir árbol de Huffman
        HuffmanNode* raiz = ConstruirArbolHuffman();

        // PASO 3: Generar códigos
        GenerarCodigos(raiz, "");
        MostrarCodigos();

        // PASO 4: Comprimir archivo
        ComprimirArchivo(archivoOrigen, archivoDestino.c_str());

        printf("Compresión exitosa!\n");
        printf("Archivo comprimido: %s\n\n", archivoDestino.c_str());
    }

    // ========================================
    // MODO DESCOMPRESIÓN
    // ========================================

    else if (opcion == 'd') {
        const char* archivoComprimido = argv[2];

        // Generar nombre del archivo descomprimido
        string archivoSalida = string(archivoComprimido);

        // Remover extensión .huf si existe
        size_t pos = archivoSalida.rfind(".huf");
        if (pos != string::npos) {
            archivoSalida = archivoSalida.substr(0, pos);
        }
        archivoSalida += ".restored";

        printf("Archivo comprimido: %s\n", archivoComprimido);
        printf("Archivo restaurado: %s\n\n", archivoSalida.c_str());

        // Descomprimir
        DescomprimirArchivo(archivoComprimido, archivoSalida.c_str());

        printf("Descompresión exitosa!\n");
        printf("Archivo restaurado: %s\n\n", archivoSalida.c_str());
    }

    else {
        printf("ERROR: Opción inválida. Use 'c' para comprimir o 'd' para descomprimir.\n");
        return -1;
    }

    cout << "========================================\n\n";

    return 0;
}

// ============================================================
// EJEMPLOS DE USO:
// ============================================================
/*

COMPRIMIR (Command Arguments):
  c documento.txt
  c foto.bmp
  c archivo.exe

  → Genera: documento.txt.huf, foto.bmp.huf, archivo.exe.huf

DESCOMPRIMIR (Command Arguments):
  d documento.txt.huf
  d foto.bmp.huf
  d archivo.exe.huf

  → Genera: documento.txt.restored, foto.bmp.restored, archivo.exe.restored

NOTA:
- El archivo restaurado debe ser IDÉNTICO al original
- Verificar byte por byte que son iguales
- La compresión funciona mejor con archivos de texto que tienen
  mucha repetición de caracteres

*/