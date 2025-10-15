// ============================================================
// PROYECTO 3B - ENCRIPTADOR/DESENCRIPTADOR COMPLETO
// Estudiante: Ｌｅｅ－ｓａｎｇｃｈｅｏｌ
// Fecha: Octubre 2025
// Descripción: Sistema completo de encriptación con:
//              - 5 algoritmos diferentes
//              - Carpetas automáticas (bak/Restore)
//              - HEADER con tipo de algoritmo
// ============================================================

#include <stdio.h>
#include <iostream>
#include <string.h>
#include <direct.h>   // Para _mkdir
#include <Windows.h>  // Para CreateDirectory

using namespace std;

// Rutas de carpetas - Según especificación del profesor
const char* CARPETA_BAK = "c:\\misproyectosdelTec-bak";
const char* CARPETA_RESTORE = "c:\\misproyectosdelTec-Restore";

// ============================================================
// FUNCIONES AUXILIARES PARA MANIPULACIÓN DE BITS
// ============================================================

void InvertirBit(char& Simbolo, int cual)
{
    int Mascara = 1;
    Mascara = Mascara << cual;
    Simbolo = Simbolo ^ Mascara;
}

// ============================================================
// ALGORITMO 1: INVERSIÓN DEL BIT 0
// Descripción: Invierte únicamente el bit menos significativo
// Operadores: ^ (XOR), << (shift)
// ============================================================

void Veneno_1(char Bloque[1000], int limite)
{
    int i;
    int posicion_a_invertir = 0;

    for (i = 0; i <= limite; i++) {
        InvertirBit(Bloque[i], posicion_a_invertir);
    }
}

void Antidoto_1(char Bloque[1000], int limite)
{
    int i;
    int posicion_a_invertir = 0;

    for (i = 0; i <= limite; i++) {
        InvertirBit(Bloque[i], posicion_a_invertir);
    }
}

// ============================================================
// ALGORITMO 2: ROTACIÓN DE BITS (ROL/ROR)
// Descripción: Rota todos los bits 3 posiciones a la izquierda
// Operadores: << >> | (shifts y OR)
// ============================================================

void Veneno_2(char Bloque[1000], int limite)
{
    for (int i = 0; i <= limite; i++) {
        unsigned char temp = (unsigned char)Bloque[i];
        Bloque[i] = (temp << 3) | (temp >> 5);
    }
}

void Antidoto_2(char Bloque[1000], int limite)
{
    for (int i = 0; i <= limite; i++) {
        unsigned char temp = (unsigned char)Bloque[i];
        Bloque[i] = (temp >> 3) | (temp << 5);
    }
}

// ============================================================
// ALGORITMO 3: XOR CON MÁSCARA ALTERNANTE
// Descripción: Aplica XOR con patrones alternantes
// Operadores: ^ (XOR)
// ============================================================

void Veneno_3(char Bloque[1000], int limite)
{
    for (int i = 0; i <= limite; i++) {
        if (i % 2 == 0) {
            Bloque[i] = Bloque[i] ^ 0xAA; // 10101010
        }
        else {
            Bloque[i] = Bloque[i] ^ 0x55; // 01010101
        }
    }
}

void Antidoto_3(char Bloque[1000], int limite)
{
    Veneno_3(Bloque, limite); // XOR es autoinverso
}

// ============================================================
// ALGORITMO 4: SWAP NIBBLES + INVERSIÓN SELECTIVA
// Descripción: Intercambia nibbles e invierte bits específicos
// Operadores: & (AND), << >> (shifts), | (OR), ^ (XOR)
// ============================================================

void Veneno_4(char Bloque[1000], int limite)
{
    for (int i = 0; i <= limite; i++) {
        unsigned char temp = (unsigned char)Bloque[i];
        unsigned char swapped = ((temp & 0x0F) << 4) | ((temp & 0xF0) >> 4);
        swapped = swapped ^ 0x54;
        Bloque[i] = swapped;
    }
}

void Antidoto_4(char Bloque[1000], int limite)
{
    for (int i = 0; i <= limite; i++) {
        unsigned char temp = (unsigned char)Bloque[i];
        temp = temp ^ 0x54;
        Bloque[i] = ((temp & 0x0F) << 4) | ((temp & 0xF0) >> 4);
    }
}

// ============================================================
// ALGORITMO 5: XOR SECUENCIAL (ENCADENAMIENTO)
// Descripción: Cada byte se XORea con el anterior
// Operadores: ^ (XOR)
// ============================================================

void Veneno_5(char Bloque[1000], int limite)
{
    for (int i = limite; i > 0; i--) {
        Bloque[i] = Bloque[i] ^ Bloque[i - 1];
    }
}

void Antidoto_5(char Bloque[1000], int limite)
{
    for (int i = 1; i <= limite; i++) {
        Bloque[i] = Bloque[i] ^ Bloque[i - 1];
    }
}

// ============================================================
// FUNCIÓN PARA CREAR CARPETAS SI NO EXISTEN
// ============================================================

void CrearCarpetaSiNoExiste(const char* ruta)
{
    // Intentar crear la carpeta
    if (CreateDirectoryA(ruta, NULL) || GetLastError() == ERROR_ALREADY_EXISTS) {
        // Carpeta creada o ya existe
    }
    else {
        cout << "Advertencia: No se pudo crear/verificar carpeta: " << ruta << endl;
    }
}

// ============================================================
// FUNCIÓN PARA EXTRAER NOMBRE DE ARCHIVO DE UNA RUTA
// ============================================================

void ExtraerNombreArchivo(const char* rutaCompleta, char* nombreSalida)
{
    const char* ultimaBarra = strrchr(rutaCompleta, '\\');
    if (ultimaBarra == NULL) {
        ultimaBarra = strrchr(rutaCompleta, '/');
    }

    if (ultimaBarra != NULL) {
        strcpy_s(nombreSalida, 256, ultimaBarra + 1);
    }
    else {
        strcpy_s(nombreSalida, 256, rutaCompleta);
    }
}

// ============================================================
// FUNCIÓN PARA REMOVER EXTENSIÓN .enc
// ============================================================

void RemoverExtensionEnc(const char* nombreConEnc, char* nombreSinEnc)
{
    strcpy_s(nombreSinEnc, 256, nombreConEnc);

    // Buscar ".enc" al final
    int len = strlen(nombreSinEnc);
    if (len > 4 && strcmp(&nombreSinEnc[len - 4], ".enc") == 0) {
        nombreSinEnc[len - 4] = '\0'; // Cortar la extensión
    }
}

// ============================================================
// FUNCIÓN PRINCIPAL - ENCRIPTACIÓN/DESENCRIPTACIÓN
// ============================================================

int main(int argc, char* argv[])
{
    cout << "\n============================================\n";
    cout << "  ENCRIPTADOR/DESENCRIPTADOR - PROYECTO 3B\n";
    cout << "============================================\n\n";

    // Validar argumentos
    if (argc < 3) {
        cout << "Uso:\n";
        cout << "  ENCRIPTAR:\n";
        cout << "    " << argv[0] << " e [tipo:1-5] [archivo_origen]\n\n";
        cout << "  DESENCRIPTAR:\n";
        cout << "    " << argv[0] << " d [archivo.enc]\n\n";
        cout << "Ejemplos:\n";
        cout << "  " << argv[0] << " e 1 MiFoto.jpg\n";
        cout << "  " << argv[0] << " d c:\\misproyectosdelTec-bak\\MiFoto.jpg.enc\n\n";
        return -1;
    }

    char opcion = argv[1][0]; // 'e' o 'd'

    // ========================================================
    // MODO ENCRIPTACIÓN
    // ========================================================

    if (opcion == 'e') {

        if (argc != 4) {
            cout << "ERROR: Para encriptar se necesitan 3 parámetros\n";
            cout << "Uso: " << argv[0] << " e [tipo:1-5] [archivo_origen]\n";
            return -1;
        }

        int tipo = atoi(argv[2]);
        const char* archivoOrigen = argv[3];

        // Validar tipo de algoritmo
        if (tipo < 1 || tipo > 5) {
            cout << "ERROR: Tipo debe ser 1-5\n";
            return -1;
        }

        cout << "MODO: ENCRIPTACIÓN\n";
        cout << "Algoritmo: Tipo " << tipo << "\n";
        cout << "Archivo origen: " << archivoOrigen << "\n\n";

        // Crear carpeta de backup si no existe
        CrearCarpetaSiNoExiste(CARPETA_BAK);

        // Extraer nombre del archivo
        char nombreArchivo[256];
        ExtraerNombreArchivo(archivoOrigen, nombreArchivo);

        // Construir ruta de destino
        char archivoDestino[512];
        sprintf_s(archivoDestino, "%s\\%s.enc", CARPETA_BAK, nombreArchivo);

        cout << "Guardando en: " << archivoDestino << "\n\n";

        // Abrir archivos
        FILE* fOrigen, * fDestino;
        fopen_s(&fOrigen, archivoOrigen, "rb");
        if (fOrigen == NULL) {
            perror("ERROR al abrir archivo origen");
            return -1;
        }

        fopen_s(&fDestino, archivoDestino, "wb");
        if (fDestino == NULL) {
            perror("ERROR al crear archivo destino");
            fclose(fOrigen);
            return -1;
        }

        // ESCRIBIR HEADER (4 bytes: 'E', 'N', 'C', tipo)
        unsigned char header[4] = { 'E', 'N', 'C', (unsigned char)tipo };
        fwrite(header, 1, 4, fDestino);

        cout << "Procesando";

        // Procesar archivo
        char buffer[1000];
        int leidos;
        int totalBytes = 0;

        leidos = fread(buffer, 1, 1000, fOrigen);

        while (leidos > 0) {
            // Aplicar algoritmo según tipo
            switch (tipo) {
            case 1: Veneno_1(buffer, leidos); break;
            case 2: Veneno_2(buffer, leidos); break;
            case 3: Veneno_3(buffer, leidos); break;
            case 4: Veneno_4(buffer, leidos); break;
            case 5: Veneno_5(buffer, leidos); break;
            }

            fwrite(buffer, 1, leidos, fDestino);
            totalBytes += leidos;

            if (totalBytes % 10000 == 0) cout << ".";

            leidos = fread(buffer, 1, 1000, fOrigen);
        }

        fclose(fOrigen);
        fclose(fDestino);

        cout << " ¡COMPLETADO!\n\n";
        cout << "Bytes procesados: " << totalBytes << "\n";
        cout << "Archivo encriptado: " << archivoDestino << "\n\n";
    }

    // ========================================================
    // MODO DESENCRIPTACIÓN
    // ========================================================

    else if (opcion == 'd') {

        if (argc != 3) {
            cout << "ERROR: Para desencriptar se necesita el archivo .enc\n";
            cout << "Uso: " << argv[0] << " d [archivo.enc]\n";
            return -1;
        }

        const char* archivoEncriptado = argv[2];

        cout << "MODO: DESENCRIPTACIÓN\n";
        cout << "Archivo encriptado: " << archivoEncriptado << "\n\n";

        // Abrir archivo encriptado
        FILE* fEncriptado;
        fopen_s(&fEncriptado, archivoEncriptado, "rb");
        if (fEncriptado == NULL) {
            perror("ERROR al abrir archivo encriptado");
            return -1;
        }

        // LEER HEADER
        unsigned char header[4];
        int headerLeido = fread(header, 1, 4, fEncriptado);

        if (headerLeido != 4 || header[0] != 'E' || header[1] != 'N' || header[2] != 'C') {
            cout << "ERROR: Archivo no tiene un HEADER válido\n";
            cout << "Este archivo no fue encriptado con este programa.\n";
            fclose(fEncriptado);
            return -1;
        }

        int tipo = header[3];

        if (tipo < 1 || tipo > 5) {
            cout << "ERROR: Tipo de algoritmo desconocido: " << tipo << "\n";
            fclose(fEncriptado);
            return -1;
        }

        cout << "Algoritmo detectado: Tipo " << tipo << "\n";

        // Crear carpeta Restore si no existe
        CrearCarpetaSiNoExiste(CARPETA_RESTORE);

        // Extraer nombre del archivo y remover .enc
        char nombreArchivo[256];
        ExtraerNombreArchivo(archivoEncriptado, nombreArchivo);

        char nombreOriginal[256];
        RemoverExtensionEnc(nombreArchivo, nombreOriginal);

        // Construir ruta de destino
        char archivoRestaurado[512];
        sprintf_s(archivoRestaurado, "%s\\%s", CARPETA_RESTORE, nombreOriginal);

        cout << "Restaurando en: " << archivoRestaurado << "\n\n";

        // Abrir archivo de salida
        FILE* fRestaurado;
        fopen_s(&fRestaurado, archivoRestaurado, "wb");
        if (fRestaurado == NULL) {
            perror("ERROR al crear archivo restaurado");
            fclose(fEncriptado);
            return -1;
        }

        cout << "Procesando";

        // Procesar archivo
        char buffer[1000];
        int leidos;
        int totalBytes = 0;

        leidos = fread(buffer, 1, 1000, fEncriptado);

        while (leidos > 0) {
            // Aplicar antídoto según tipo
            switch (tipo) {
            case 1: Antidoto_1(buffer, leidos); break;
            case 2: Antidoto_2(buffer, leidos); break;
            case 3: Antidoto_3(buffer, leidos); break;
            case 4: Antidoto_4(buffer, leidos); break;
            case 5: Antidoto_5(buffer, leidos); break;
            }

            fwrite(buffer, 1, leidos, fRestaurado);
            totalBytes += leidos;

            if (totalBytes % 10000 == 0) cout << ".";

            leidos = fread(buffer, 1, 1000, fEncriptado);
        }

        fclose(fEncriptado);
        fclose(fRestaurado);

        cout << " ¡COMPLETADO!\n\n";
        cout << "Bytes procesados: " << totalBytes << "\n";
        cout << "Archivo restaurado: " << archivoRestaurado << "\n\n";
    }

    else {
        cout << "ERROR: Opción inválida. Use 'e' para encriptar o 'd' para desencriptar.\n";
        return -1;
    }

    cout << "============================================\n\n";

    return 0;
}

// ============================================================
// EJEMPLOS DE USO:
// ============================================================
/*

ENCRIPTAR (Command Arguments):
  e 1 MiFoto.jpg
  e 2 Documento.pdf
  e 3 Video.mp4
  e 4 Musica.mp3
  e 5 Datos.xlsx

  → Crea archivo en: c:\misproyectosdelTec-bak\[nombre].enc

DESENCRIPTAR (Command Arguments):
  d c:\misproyectosdelTec-bak\MiFoto.jpg.enc
  d c:\misproyectosdelTec-bak\Documento.pdf.enc

  → Restaura archivo en: c:\misproyectosdelTec-Restore\[nombre_original]

NOTA: El programa detecta automáticamente qué algoritmo usar
      leyendo el HEADER del archivo .enc

*/