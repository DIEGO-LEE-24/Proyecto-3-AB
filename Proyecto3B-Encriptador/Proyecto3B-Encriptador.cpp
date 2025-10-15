// ============================================================
// PROYECTO 3B - ENCRIPTADOR/DESENCRIPTADOR DE ARCHIVOS
// Estudiante: [TU NOMBRE]
// Fecha: Octubre 2025
// Descripción: Sistema de encriptación con 5 algoritmos
//              diferentes usando manipulación de bits
// ============================================================

#include <stdio.h>
#include <iostream>
#include <string.h>

using namespace std;

// ============================================================
// FUNCIONES AUXILIARES PARA MANIPULACIÓN DE BITS
// ============================================================

// Función para invertir un bit específico en un símbolo
// Parámetros:
//   - Simbolo: Referencia al byte a modificar
//   - cual: Posición del bit a invertir (0-7)
// Operadores usados: << (shift left), ^ (XOR)
void InvertirBit(char& Simbolo, int cual)
{
    int Mascara = 1;
    // Desplazar el bit 1 a la posición deseada
    // Ejemplo: cual=3 → Mascara = 00001000
    Mascara = Mascara << cual;

    // XOR para invertir solo ese bit
    // Si el bit era 0 → pasa a 1
    // Si el bit era 1 → pasa a 0
    Simbolo = Simbolo ^ Mascara;
}

// ============================================================
// ALGORITMO 1: INVERSIÓN DEL BIT 0 (EJEMPLO DEL PROFESOR)
// Descripción: Invierte únicamente el bit menos significativo
// Operadores: ^ (XOR), << (shift)
// Complejidad: O(n)
// ============================================================

void Veneno_1(char Bloque[1000], int limite)
{
    // Recorrer cada byte del bloque
    int i;
    int posicion_a_invertir = 0;

    for (i = 0; i <= limite; i++) {
        // Invertir el bit en posición 0 (LSB - Least Significant Bit)
        InvertirBit(Bloque[i], posicion_a_invertir);
    }
}

void Antidoto_1(char Bloque[1000], int limite)
{
    // El XOR es su propio inverso: aplicar dos veces = original
    // Por eso Antidoto_1 es idéntico a Veneno_1
    int i;
    int posicion_a_invertir = 0;

    for (i = 0; i <= limite; i++) {
        InvertirBit(Bloque[i], posicion_a_invertir);
    }
}

// ============================================================
// ALGORITMO 2: ROTACIÓN DE BITS (ROL/ROR)
// Descripción: Rota todos los bits 3 posiciones a la izquierda
// Operadores: << (shift left), >> (shift right), | (OR)
// Complejidad: O(n)
// Ejemplo: 11010110 → ROL 3 → 10110110
// ============================================================

void Veneno_2(char Bloque[1000], int limite)
{
    for (int i = 0; i <= limite; i++) {
        unsigned char temp = (unsigned char)Bloque[i];

        // ROL (Rotate Left) 3 posiciones
        // temp << 3: Desplaza 3 bits a la izquierda
        // temp >> 5: Los 3 bits que "salen" regresan por la derecha
        // | (OR): Combina ambas partes
        Bloque[i] = (temp << 3) | (temp >> 5);
    }
}

void Antidoto_2(char Bloque[1000], int limite)
{
    for (int i = 0; i <= limite; i++) {
        unsigned char temp = (unsigned char)Bloque[i];

        // ROR (Rotate Right) 3 posiciones - inverso de ROL
        Bloque[i] = (temp >> 3) | (temp << 5);
    }
}

// ============================================================
// ALGORITMO 3: XOR CON MÁSCARA ALTERNANTE
// Descripción: Aplica XOR con dos máscaras diferentes según posición
// Operadores: ^ (XOR), % (módulo)
// Complejidad: O(n)
// Máscaras:
//   - 0xAA = 10101010 (posiciones pares)
//   - 0x55 = 01010101 (posiciones impares)
// ============================================================

void Veneno_3(char Bloque[1000], int limite)
{
    for (int i = 0; i <= limite; i++) {
        if (i % 2 == 0) {
            // Posición par: XOR con 10101010
            Bloque[i] = Bloque[i] ^ 0xAA;
        }
        else {
            // Posición impar: XOR con 01010101
            Bloque[i] = Bloque[i] ^ 0x55;
        }
    }
}

void Antidoto_3(char Bloque[1000], int limite)
{
    // XOR es autoinverso: A ^ B ^ B = A
    // Por lo tanto, aplicar el mismo algoritmo desencripta
    Veneno_3(Bloque, limite);
}

// ============================================================
// ALGORITMO 4: SWAP NIBBLES + INVERSIÓN SELECTIVA
// Descripción: Intercambia nibbles (4 bits) e invierte bits específicos
// Operadores: & (AND), << >> (shifts), | (OR), ^ (XOR)
// Complejidad: O(n)
// Ejemplo: ABCD EFGH → EFGH ABCD → luego invertir bits 2,4,6
// ============================================================

void Veneno_4(char Bloque[1000], int limite)
{
    for (int i = 0; i <= limite; i++) {
        unsigned char temp = (unsigned char)Bloque[i];

        // PASO 1: Swap nibbles (intercambiar mitades del byte)
        // temp & 0x0F: Extrae nibble bajo (4 bits derechos)
        // temp & 0xF0: Extrae nibble alto (4 bits izquierdos)
        unsigned char swapped = ((temp & 0x0F) << 4) | ((temp & 0xF0) >> 4);

        // PASO 2: Invertir bits en posiciones 2, 4, 6
        // 0x54 = 01010100 (bits set en posiciones 2, 4, 6)
        swapped = swapped ^ 0x54;

        Bloque[i] = swapped;
    }
}

void Antidoto_4(char Bloque[1000], int limite)
{
    for (int i = 0; i <= limite; i++) {
        unsigned char temp = (unsigned char)Bloque[i];

        // PASO 1: Primero desinvertir los bits 2,4,6
        temp = temp ^ 0x54;

        // PASO 2: Luego swap nibbles de vuelta
        Bloque[i] = ((temp & 0x0F) << 4) | ((temp & 0xF0) >> 4);
    }
}

// ============================================================
// ALGORITMO 5: XOR SECUENCIAL (ENCADENAMIENTO)
// Descripción: Cada byte se XORea con el byte anterior
// Operadores: ^ (XOR)
// Complejidad: O(n)
// Nota: Requiere procesar en orden inverso al encriptar
// ============================================================

void Veneno_5(char Bloque[1000], int limite)
{
    // IMPORTANTE: Empezar desde el FINAL para no perder información
    for (int i = limite; i > 0; i--) {
        // Cada byte se XORea con el anterior
        // Esto crea una "cadena" de dependencias
        Bloque[i] = Bloque[i] ^ Bloque[i - 1];
    }
    // El primer byte (i=0) NO se modifica - sirve como "semilla"
}

void Antidoto_5(char Bloque[1000], int limite)
{
    // Para desencriptar, procesar desde el PRINCIPIO
    for (int i = 1; i <= limite; i++) {
        // Aplicar el mismo XOR deshace la encriptación
        Bloque[i] = Bloque[i] ^ Bloque[i - 1];
    }
}

// ============================================================
// FUNCIÓN PRINCIPAL - IGUAL QUE EL EJEMPLO DEL PROFESOR
// ============================================================

int main(int argc, char* argv[])
{
    //----------------------------------------------------------------------
    // Pintando a pantalla los argumentos que recibe el programa :  Se esperan en esta prueba 3: 
    // Ejecutable e/d FileOrigen FileDestino
    // e/d = e=encriptar   d=desencriptar

    cout << "\n============================================\n";
    cout << "  ENCRIPTADOR/DESENCRIPTADOR - PROYECTO 3B\n";
    cout << "============================================\n\n";

    for (int i = 0; i < argc; ++i) {
        cout << "argumento " << i << ": " << argv[i] << "\n";
    }
    cout << endl;

    //----------------------------------------------------------------------

    // Archivos logicos : Buffers tipo FILE
    FILE* ArchivoOrigen, * ArchivoDestino;

    //----------------------------------------------------------------------
    // APERTURA DE ARCHIVO FUENTE Y DESTINO
    /* Apertura del archivo original, para lectura en binario*/
    fopen_s(&ArchivoOrigen, argv[2], "rb");
    if (ArchivoOrigen == NULL)
    {
        perror("No se puede abrir archivo origen ");//, argv[2]
        return -1;
    }

    /* Apertura del archivo destino, para escritura en binario*/
    fopen_s(&ArchivoDestino, argv[3], "wb");
    if (ArchivoDestino == NULL)
    {
        perror("No se puede abrir archivo destino"); // , argv[2]
        return -1;
    }

    //----------------------------------------------------------------------
    // PROCESAMIENTO DE ARCHIVOS FUENTE Y DESTINO

    /* Bloque de 1000 bytes, para meter lo que vamos leyendo del archivo */
    char buffer[1000];
    /* Para guardar el número de items leidos o si ha habido error */
    int leidos;
    char opcion = argv[1][0]; // (strcmp(opcion, 'e')

    if (opcion == 'e') // Da verdadero si se quiere "e"ncriptar, cualquier otro es desencriptar
    {
        // ENCRIPTANDO
        cout << "Modo: ENCRIPTACIÓN\n";
        cout << "Procesando";

        leidos = fread(buffer, 1, 1000, ArchivoOrigen);

        /* Mientras se haya leido algo ... */
        while (leidos > 0)
        {
            // AQUÍ PUEDES CAMBIAR ENTRE Veneno_1, Veneno_2, Veneno_3, Veneno_4, Veneno_5
            // Para probar diferentes algoritmos, simplemente cambia el número

            // Veneno_1(buffer, leidos); // Algoritmo 1 (ejemplo del profesor)
            Veneno_2(buffer, leidos); // Algoritmo 2 - Rotación
            // Veneno_3(buffer, leidos); // Algoritmo 3 - XOR Alternante
            // Veneno_4(buffer, leidos); // Algoritmo 4 - Swap Nibbles
            // Veneno_5(buffer, leidos); // Algoritmo 5 - XOR Secuencial
            // Veneno_2(buffer, leidos - 1); // Algoritmo 2 - Rotación
            // Veneno_3(buffer, leidos - 1); // Algoritmo 3 - XOR Alternante
            // Veneno_4(buffer, leidos - 1); // Algoritmo 4 - Swap Nibbles
            // Veneno_5(buffer, leidos - 1); // Algoritmo 5 - XOR Secuencial

            /* ... meterlo en el fichero destino */
            fwrite(buffer, 1, leidos, ArchivoDestino);

            cout << ".";

            /* y leer siguiente bloque */
            leidos = fread(buffer, 1, 1000, ArchivoOrigen);
        }
    }
    else
    {
        // DESENCRIPTANDO
        cout << "Modo: DESENCRIPTACIÓN\n";
        cout << "Procesando";

        leidos = fread(buffer, 1, 1000, ArchivoOrigen);

        /* Mientras se haya leido algo ... */
        while (leidos > 0)
        {
            // IMPORTANTE: Usar el MISMO número de algoritmo que usaste para encriptar!

            // Antidoto_1(buffer, leidos); // Algoritmo 1 (ejemplo del profesor)
            Antidoto_2(buffer, leidos); // Algoritmo 2 - Rotación
            // Antidoto_3(buffer, leidos); // Algoritmo 3 - XOR Alternante
            // Antidoto_4(buffer, leidos); // Algoritmo 4 - Swap Nibbles
            // Antidoto_5(buffer, leidos); // Algoritmo 5 - XOR Secuencial
            // Antidoto_2(buffer, leidos - 1); // Algoritmo 2 - Rotación
            // Antidoto_3(buffer, leidos - 1); // Algoritmo 3 - XOR Alternante
            // Antidoto_4(buffer, leidos - 1); // Algoritmo 4 - Swap Nibbles
            // Antidoto_5(buffer, leidos - 1); // Algoritmo 5 - XOR Secuencial

            /* ... meterlo en el fichero destino */
            fwrite(buffer, 1, leidos, ArchivoDestino);

            cout << ".";

            /* y leer siguiente bloque */
            leidos = fread(buffer, 1, 1000, ArchivoOrigen);
        }
    }

    fclose(ArchivoOrigen);
    fclose(ArchivoDestino);

    cout << " ¡COMPLETADO!\n";
    cout << "\n============================================\n\n";

    // Terminamos .. vaya a ver como quedo el archivo Encriptado o Desencriptado.. no olvide manejar estos nombre 
    // en Proyecto->Propiedades->Depuracion->Argumentos 

    return 0;
}

// ============================================================
// EJEMPLOS DE USO (ARGUMENTOS DE COMANDOS):
// ============================================================
/*
ENCRIPTAR (Argumentos de comandos):
  e Parametros-Main.jpg Parametros-Main.enc
  e MiFoto.jpg MiFoto.enc
  e documento.txt documento.enc

DESENCRIPTAR (Argumentos de comandos):
  d Parametros-Main.enc Parametros-Main-Dup.jpg
  d MiFoto.enc MiFoto-restaurado.jpg
  d documento.enc documento-restaurado.txt

NOTA:
- Para probar diferentes algoritmos, comentar/descomentar las líneas
  en el main() donde dice Veneno_X / Antidoto_X
- Recuerda que el archivo debe estar en la carpeta del proyecto ($(ProjectDir))
*/