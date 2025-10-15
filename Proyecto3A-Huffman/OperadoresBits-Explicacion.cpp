// ============================================================
// EXPLICACIÓN DETALLADA: OPERADORES DE BITS
// Proyecto 3A - Lee Sang Cheol
// Demostrando uso de: & | ^ ~ << >>
// ============================================================

#include <iostream>
#include <bitset>
#include <iomanip>
using namespace std;

// ============================================================
// FUNCIÓN AUXILIAR: Mostrar byte en formato binario
// ============================================================
void mostrarByte(const string& nombre, unsigned char byte) {
    cout << nombre << ": "
        << bitset<8>(byte) << " (0x"
        << hex << setw(2) << setfill('0') << (int)byte
        << ", " << dec << (int)byte << ")" << endl;
}

// ============================================================
// DEMOSTRACIÓN 1: Operador & (AND)
// Uso: Leer/verificar bits específicos (MÁSCARAS)
// ============================================================
void demo_AND() {
    cout << "\n========================================\n";
    cout << "OPERADOR & (AND) - MÁSCARAS DE BITS\n";
    cout << "========================================\n";

    unsigned char byte = 0b10110101;
    mostrarByte("Byte original", byte);

    cout << "\n--- Leer bit en posición específica ---\n";

    // Leer bit 0 (LSB - Least Significant Bit)
    unsigned char bit0 = byte & 0x01;  // 0x01 = 0b00000001
    cout << "Bit 0: " << (int)bit0 << " (máscara: 0x01 = 0b00000001)" << endl;

    // Leer bit 7 (MSB - Most Significant Bit)
    unsigned char bit7 = byte & 0x80;  // 0x80 = 0b10000000
    cout << "Bit 7: " << (bit7 ? "1" : "0") << " (máscara: 0x80 = 0b10000000)" << endl;

    // Leer bit 3
    unsigned char bit3 = byte & 0x08;  // 0x08 = 0b00001000
    cout << "Bit 3: " << (bit3 ? "1" : "0") << " (máscara: 0x08 = 0b00001000)" << endl;

    cout << "\n--- Verificar si bit está activo ---\n";
    if (byte & 0x80) {
        cout << "✓ Bit 7 está ACTIVO (1)" << endl;
    }

    cout << "\n--- USO EN HUFFMAN ---\n";
    cout << "// Leer bit de un byte comprimido:\n";
    cout << "int bit = (byteActual >> bitPos) & 1;\n";
    cout << "// La máscara 0x01 (1) extrae solo el bit menos significativo\n";
}

// ============================================================
// DEMOSTRACIÓN 2: Operador | (OR)
// Uso: Activar/escribir bits específicos
// ============================================================
void demo_OR() {
    cout << "\n========================================\n";
    cout << "OPERADOR | (OR) - ACTIVAR BITS\n";
    cout << "========================================\n";

    unsigned char byte = 0b00000000;
    mostrarByte("Byte inicial", byte);

    cout << "\n--- Activar bits individuales ---\n";

    byte = byte | 0x01;  // Activar bit 0
    mostrarByte("Después de |= 0x01", byte);

    byte = byte | 0x80;  // Activar bit 7
    mostrarByte("Después de |= 0x80", byte);

    byte = byte | 0x08;  // Activar bit 3
    mostrarByte("Después de |= 0x08", byte);

    cout << "\n--- USO EN HUFFMAN ---\n";
    cout << "// Escribir bit en buffer:\n";
    cout << "buffer = (buffer << 1) | bit;\n";
    cout << "// Desplaza buffer a la izquierda y añade nuevo bit con OR\n";
}

// ============================================================
// DEMOSTRACIÓN 3: Operador ^ (XOR)
// Uso: Invertir bits específicos, encriptación simple
// ============================================================
void demo_XOR() {
    cout << "\n========================================\n";
    cout << "OPERADOR ^ (XOR) - INVERTIR BITS\n";
    cout << "========================================\n";

    unsigned char byte = 0b10110101;
    mostrarByte("Byte original", byte);

    cout << "\n--- Invertir bits específicos ---\n";

    unsigned char resultado = byte ^ 0xFF;  // Invertir todos los bits
    mostrarByte("byte ^ 0xFF", resultado);

    resultado = byte ^ 0x0F;  // Invertir solo los 4 bits bajos
    mostrarByte("byte ^ 0x0F", resultado);

    cout << "\n--- Propiedad de XOR: A ^ B ^ B = A ---\n";
    unsigned char original = 0b10101010;
    unsigned char clave = 0b11001100;
    mostrarByte("Original", original);
    mostrarByte("Clave", clave);

    unsigned char encriptado = original ^ clave;
    mostrarByte("Encriptado", encriptado);

    unsigned char desencriptado = encriptado ^ clave;
    mostrarByte("Desencriptado", desencriptado);
    cout << "✓ Recuperamos el valor original!" << endl;

    cout << "\n--- USO EN ENCRIPTACIÓN (Proyecto 3B) ---\n";
    cout << "// Encriptar/Desencriptar con XOR:\n";
    cout << "byteEncriptado = byteOriginal ^ CLAVE;\n";
    cout << "byteOriginal = byteEncriptado ^ CLAVE;\n";
}

// ============================================================
// DEMOSTRACIÓN 4: Operador ~ (NOT)
// Uso: Invertir todos los bits
// ============================================================
void demo_NOT() {
    cout << "\n========================================\n";
    cout << "OPERADOR ~ (NOT) - COMPLEMENTO\n";
    cout << "========================================\n";

    unsigned char byte = 0b10110101;
    mostrarByte("Byte original", byte);

    unsigned char complemento = ~byte;
    mostrarByte("~byte", complemento);

    cout << "\n--- Verificación: byte + ~byte = 0xFF ---\n";
    unsigned char suma = byte + complemento;
    mostrarByte("byte + ~byte", suma);

    cout << "\n--- USO EN ENCRIPTACIÓN ---\n";
    cout << "// Invertir todos los bits (Tipo 1):\n";
    cout << "byteEncriptado = ~byteOriginal;\n";
    cout << "byteOriginal = ~byteEncriptado;\n";
}

// ============================================================
// DEMOSTRACIÓN 5: Operador << (Left Shift)
// Uso: Desplazar bits a la izquierda, multiplicar por 2^n
// ============================================================
void demo_LeftShift() {
    cout << "\n========================================\n";
    cout << "OPERADOR << (LEFT SHIFT)\n";
    cout << "========================================\n";

    unsigned char byte = 0b00000011;
    mostrarByte("Byte original", byte);

    cout << "\n--- Desplazar bits a la izquierda ---\n";
    for (int i = 1; i <= 3; i++) {
        unsigned char resultado = byte << i;
        cout << "byte << " << i << ": ";
        mostrarByte("", resultado);
        cout << "   (equivale a multiplicar por " << (1 << i) << ")" << endl;
    }

    cout << "\n--- USO EN HUFFMAN ---\n";
    cout << "// Construir byte bit a bit:\n";
    cout << "buffer = 0;\n";
    cout << "buffer = (buffer << 1) | bit0;  // 0b00000000 → 0b00000000\n";
    cout << "buffer = (buffer << 1) | bit1;  // 0b00000000 → 0b00000001\n";
    cout << "buffer = (buffer << 1) | bit2;  // 0b00000001 → 0b00000011\n";
    cout << "// etc...\n";
}

// ============================================================
// DEMOSTRACIÓN 6: Operador >> (Right Shift)
// Uso: Desplazar bits a la derecha, dividir por 2^n
// ============================================================
void demo_RightShift() {
    cout << "\n========================================\n";
    cout << "OPERADOR >> (RIGHT SHIFT)\n";
    cout << "========================================\n";

    unsigned char byte = 0b11000000;
    mostrarByte("Byte original", byte);

    cout << "\n--- Desplazar bits a la derecha ---\n";
    for (int i = 1; i <= 3; i++) {
        unsigned char resultado = byte >> i;
        cout << "byte >> " << i << ": ";
        mostrarByte("", resultado);
        cout << "   (equivale a dividir por " << (1 << i) << ")" << endl;
    }

    cout << "\n--- USO EN HUFFMAN ---\n";
    cout << "// Leer bits de un byte:\n";
    cout << "for (int i = 7; i >= 0; i--) {\n";
    cout << "    int bit = (byte >> i) & 1;  // Leer bit en posición i\n";
    cout << "    // Procesar bit...\n";
    cout << "}\n";
}

// ============================================================
// DEMOSTRACIÓN 7: APLICACIÓN PRÁCTICA EN HUFFMAN
// ============================================================
void demo_HuffmanPractico() {
    cout << "\n========================================\n";
    cout << "APLICACIÓN PRÁCTICA EN HUFFMAN\n";
    cout << "========================================\n";

    cout << "\n--- ESCRITURA DE BITS ---\n";
    cout << "Código Huffman a escribir: \"1011\" (4 bits)\n\n";

    unsigned char buffer = 0;
    int contadorBits = 0;
    string codigo = "1011";

    for (char c : codigo) {
        int bit = (c == '1') ? 1 : 0;

        cout << "Paso " << (contadorBits + 1) << ": ";
        cout << "buffer << 1 = ";
        mostrarByte("", buffer << 1);

        buffer = (buffer << 1) | bit;  // ← USO DE << y |
        contadorBits++;

        cout << "         buffer |= " << bit << " = ";
        mostrarByte("", buffer);
        cout << endl;
    }

    cout << "\n--- LECTURA DE BITS ---\n";
    cout << "Byte a leer: ";
    mostrarByte("", buffer);
    cout << "\nLeyendo bit a bit:\n\n";

    for (int i = 7; i >= 4; i--) {  // Solo primeros 4 bits
        int bit = (buffer >> i) & 1;  // ← USO DE >> y &
        cout << "Bit posición " << i << ": ";
        cout << "(buffer >> " << i << ") & 1 = " << bit << endl;
    }
}

// ============================================================
// DEMOSTRACIÓN 8: MÁSCARA DE BITS AVANZADA
// ============================================================
void demo_MascarasAvanzadas() {
    cout << "\n========================================\n";
    cout << "MÁSCARAS DE BITS AVANZADAS\n";
    cout << "========================================\n";

    unsigned char byte = 0b10110101;
    mostrarByte("Byte original", byte);

    cout << "\n--- Extraer nibbles (4 bits) ---\n";
    unsigned char nibbleAlto = (byte >> 4) & 0x0F;
    unsigned char nibbleBajo = byte & 0x0F;

    cout << "Nibble alto (bits 7-4): " << bitset<4>(nibbleAlto) << " (" << (int)nibbleAlto << ")" << endl;
    cout << "Nibble bajo (bits 3-0): " << bitset<4>(nibbleBajo) << " (" << (int)nibbleBajo << ")" << endl;

    cout << "\n--- Activar/desactivar bit específico ---\n";
    unsigned char bit5Activo = byte | (1 << 5);
    mostrarByte("Activar bit 5", bit5Activo);

    unsigned char bit5Inactivo = byte & ~(1 << 5);
    mostrarByte("Desactivar bit 5", bit5Inactivo);

    cout << "\n--- Alternar (toggle) bit ---\n";
    unsigned char bit2Toggle = byte ^ (1 << 2);
    mostrarByte("Toggle bit 2", bit2Toggle);
}

// ============================================================
// MAIN
// ============================================================
int main() {
    cout << "============================================================\n";
    cout << "  EXPLICACIÓN COMPLETA: OPERADORES DE BITS\n";
    cout << "  Proyecto 3A - Lee Sang Cheol\n";
    cout << "  Referencia: http://www.zator.com/Cpp/E4_9_3.htm\n";
    cout << "============================================================\n";

    demo_AND();
    demo_OR();
    demo_XOR();
    demo_NOT();
    demo_LeftShift();
    demo_RightShift();
    demo_HuffmanPractico();
    demo_MascarasAvanzadas();

    cout << "\n\n============================================================\n";
    cout << "RESUMEN DE OPERADORES:\n";
    cout << "============================================================\n";
    cout << "&   (AND)        → Leer/verificar bits (máscaras)\n";
    cout << "|   (OR)         → Activar/escribir bits\n";
    cout << "^   (XOR)        → Invertir bits, encriptación\n";
    cout << "~   (NOT)        → Invertir todos los bits\n";
    cout << "<<  (Left Shift) → Desplazar izquierda, multiplicar x2\n";
    cout << ">>  (Right Shift)→ Desplazar derecha, dividir /2\n";
    cout << "============================================================\n";

    cout << "\n\nPresione Enter para salir...";
    cin.get();

    return 0;
}

// ============================================================
// INSTRUCCIONES:
// ============================================================
/*

1. Compila y ejecuta este programa:
   > g++ OperadoresBits-Explicacion.cpp -o OperadoresBits.exe
   > OperadoresBits.exe

2. Estudia cada operador y su uso

3. Busca en tu código Huffman.cpp dónde usas cada operador

4. Documenta en tu informe técnico:
   - Qué operador usas
   - Dónde lo usas (línea de código)
   - Para qué lo usas (explicación)

EJEMPLO PARA TU DOCUMENTO:

"En la línea 245 del código Huffman.cpp, uso el operador << (left shift)
junto con | (OR) para construir el buffer de bits:

    buffer = (buffer << 1) | bit;

Este código desplaza el buffer un bit a la izquierda (<<) y luego
añade el nuevo bit usando OR (|). Esto permite escribir bits uno por uno
en el byte que será escrito al archivo comprimido."

*/