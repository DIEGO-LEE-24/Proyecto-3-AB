// ============================================================
// GENERADOR DE PRUEBAS AUTOMÁTICAS
// Proyecto 3A - Lee Sang Cheol
// Prueba múltiples archivos y genera tabla de resultados
// ============================================================

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <iomanip>
#include <filesystem>
using namespace std;
namespace fs = std::filesystem;

// Estructura para almacenar resultados
struct ResultadoPrueba {
    string nombreArchivo;
    string tipoArchivo;
    long bytesOriginales;
    long bytesComprimidos;
    float porcentajeCompresion;
    bool exito;
    string observaciones;
};

// ============================================================
// FUNCIÓN: Obtener tamaño de archivo
// ============================================================
long obtenerTamano(const string& nombreArchivo) {
    ifstream file(nombreArchivo, ios::binary | ios::ate);
    if (!file) return -1;
    return file.tellg();
}

// ============================================================
// FUNCIÓN: Ejecutar comando y capturar resultado
// ============================================================
bool ejecutarComando(const string& comando) {
    int resultado = system(comando.c_str());
    return (resultado == 0);
}

// ============================================================
// FUNCIÓN: Verificar si archivos son idénticos
// ============================================================
bool verificarIdenticos(const string& archivo1, const string& archivo2) {
    ifstream f1(archivo1, ios::binary);
    ifstream f2(archivo2, ios::binary);

    if (!f1 || !f2) return false;

    char byte1, byte2;
    while (f1.get(byte1) && f2.get(byte2)) {
        if (byte1 != byte2) return false;
    }

    // Verificar que ambos llegaron al final
    return f1.eof() && f2.eof();
}

// ============================================================
// FUNCIÓN: Probar compresión/descompresión de un archivo
// ============================================================
ResultadoPrueba probarArchivo(const string& nombreArchivo, const string& ejecutable) {
    ResultadoPrueba resultado;
    resultado.nombreArchivo = nombreArchivo;

    // Determinar tipo de archivo
    size_t pos = nombreArchivo.find_last_of(".");
    resultado.tipoArchivo = (pos != string::npos) ? nombreArchivo.substr(pos) : "???";

    // Obtener tamaño original
    resultado.bytesOriginales = obtenerTamano(nombreArchivo);
    if (resultado.bytesOriginales < 0) {
        resultado.exito = false;
        resultado.observaciones = "Error: No se pudo leer el archivo";
        return resultado;
    }

    cout << "\n[PROBANDO] " << nombreArchivo << " (" << resultado.bytesOriginales << " bytes)" << endl;

    // PASO 1: Comprimir
    string archivoHuf = nombreArchivo + ".huf";
    string comandoComprimir = ejecutable + " c " + nombreArchivo + " > nul 2>&1";

    cout << "  Comprimiendo... ";
    bool comprimioOK = ejecutarComando(comandoComprimir);

    if (!comprimioOK || !fs::exists(archivoHuf)) {
        cout << "FALLO" << endl;
        resultado.exito = false;
        resultado.observaciones = "Error en compresión";
        return resultado;
    }
    cout << "OK" << endl;

    // Obtener tamaño comprimido
    resultado.bytesComprimidos = obtenerTamano(archivoHuf);
    resultado.porcentajeCompresion = 100.0 * (1.0 - (float)resultado.bytesComprimidos / resultado.bytesOriginales);

    // PASO 2: Descomprimir
    string archivoRestored = nombreArchivo + ".restored";
    string comandoDescomprimir = ejecutable + " d " + archivoHuf + " > nul 2>&1";

    cout << "  Descomprimiendo... ";
    bool descomprimioOK = ejecutarComando(comandoDescomprimir);

    if (!descomprimioOK || !fs::exists(archivoRestored)) {
        cout << "FALLO" << endl;
        resultado.exito = false;
        resultado.observaciones = "Error en descompresión";
        return resultado;
    }
    cout << "OK" << endl;

    // PASO 3: Verificar integridad
    cout << "  Verificando integridad... ";
    bool sonIdenticos = verificarIdenticos(nombreArchivo, archivoRestored);

    if (!sonIdenticos) {
        cout << "FALLO (archivos diferentes)" << endl;
        resultado.exito = false;
        resultado.observaciones = "Archivos no son idénticos";
        return resultado;
    }
    cout << "OK" << endl;

    resultado.exito = true;

    // Observaciones según tipo y compresión
    if (resultado.porcentajeCompresion > 50) {
        resultado.observaciones = "Excelente compresión";
    }
    else if (resultado.porcentajeCompresion > 20) {
        resultado.observaciones = "Buena compresión";
    }
    else if (resultado.porcentajeCompresion > 0) {
        resultado.observaciones = "Poca compresión";
    }
    else {
        resultado.observaciones = "Sin compresión (archivo ya optimizado)";
    }

    // Limpiar archivos temporales
    fs::remove(archivoHuf);
    fs::remove(archivoRestored);

    return resultado;
}

// ============================================================
// FUNCIÓN: Imprimir tabla de resultados
// ============================================================
void imprimirTabla(const vector<ResultadoPrueba>& resultados) {
    cout << "\n\n";
    cout << "========================================================================================================\n";
    cout << "                                    RESULTADOS DE PRUEBAS\n";
    cout << "========================================================================================================\n";
    cout << left << setw(25) << "ARCHIVO"
        << setw(8) << "TIPO"
        << right << setw(12) << "ORIGINAL"
        << setw(12) << "COMPRIM."
        << setw(12) << "REDUCC.%"
        << "  "
        << left << setw(30) << "OBSERVACIONES" << endl;
    cout << "--------------------------------------------------------------------------------------------------------\n";

    for (const auto& r : resultados) {
        cout << left << setw(25) << r.nombreArchivo
            << setw(8) << r.tipoArchivo
            << right << setw(12) << r.bytesOriginales
            << setw(12) << r.bytesComprimidos
            << setw(11) << fixed << setprecision(2) << r.porcentajeCompresion << "%"
            << "  "
            << left << setw(30) << r.observaciones << endl;
    }

    cout << "========================================================================================================\n";

    // Resumen
    int exitosos = 0;
    int fallidos = 0;
    for (const auto& r : resultados) {
        if (r.exito) exitosos++;
        else fallidos++;
    }

    cout << "\nRESUMEN: " << exitosos << " exitosos, " << fallidos << " fallidos" << endl;
}

// ============================================================
// FUNCIÓN: Guardar resultados en archivo
// ============================================================
void guardarResultados(const vector<ResultadoPrueba>& resultados, const string& nombreArchivo) {
    ofstream file(nombreArchivo);

    file << "========================================================================================================\n";
    file << "                                    RESULTADOS DE PRUEBAS - HUFFMAN\n";
    file << "                                    Proyecto 3A - Lee Sang Cheol\n";
    file << "========================================================================================================\n\n";

    file << left << setw(25) << "ARCHIVO"
        << setw(8) << "TIPO"
        << right << setw(12) << "ORIGINAL"
        << setw(12) << "COMPRIM."
        << setw(12) << "REDUCC.%"
        << "  "
        << left << setw(30) << "OBSERVACIONES" << endl;
    file << "--------------------------------------------------------------------------------------------------------\n";

    for (const auto& r : resultados) {
        file << left << setw(25) << r.nombreArchivo
            << setw(8) << r.tipoArchivo
            << right << setw(12) << r.bytesOriginales
            << setw(12) << r.bytesComprimidos
            << setw(11) << fixed << setprecision(2) << r.porcentajeCompresion << "%"
            << "  "
            << left << setw(30) << r.observaciones << endl;
    }

    file << "========================================================================================================\n";
    file.close();

    cout << "\nResultados guardados en: " << nombreArchivo << endl;
}

// ============================================================
// MAIN
// ============================================================
int main() {
    cout << "========================================\n";
    cout << "  PROBADOR AUTOMÁTICO HUFFMAN\n";
    cout << "  Proyecto 3A - Lee Sang Cheol\n";
    cout << "========================================\n\n";

    // Ejecutable del compresor
    string ejecutable = "Proyecto3A-Huffman.exe";

    // Lista de archivos a probar
    vector<string> archivos = {
        "prueba.txt",
        "documento.txt",
        "codigo.cpp",
        "imagen.bmp",
        "foto.jpg",
        "programa.exe",
        "audio.mp3",
        "comprimido.zip"
    };

    vector<ResultadoPrueba> resultados;

    // Probar cada archivo
    for (const string& archivo : archivos) {
        if (fs::exists(archivo)) {
            ResultadoPrueba r = probarArchivo(archivo, ejecutable);
            resultados.push_back(r);
        }
        else {
            cout << "[OMITIDO] " << archivo << " (no existe)" << endl;
        }
    }

    // Mostrar tabla de resultados
    imprimirTabla(resultados);

    // Guardar en archivo
    guardarResultados(resultados, "ResultadosPruebas.txt");

    cout << "\n\nPresione cualquier tecla para salir...";
    cin.get();

    return 0;
}

// ============================================================
// INSTRUCCIONES DE USO:
// ============================================================
/*

1. Coloca este archivo en la misma carpeta que tu Proyecto3A-Huffman.exe

2. Crea archivos de prueba:
   - prueba.txt (ya lo tienes)
   - documento.txt (cualquier texto)
   - codigo.cpp (tu código fuente)
   - imagen.bmp (cualquier imagen BMP)
   - foto.jpg (cualquier foto JPG)
   - programa.exe (cualquier ejecutable pequeño)
   - audio.mp3 (opcional)
   - comprimido.zip (opcional)

3. Compila este código:
   > g++ GeneradorPruebas.cpp -o GeneradorPruebas.exe -std=c++17

4. Ejecuta:
   > GeneradorPruebas.exe

5. Obtendrás:
   - Tabla en pantalla con resultados
   - Archivo "ResultadosPruebas.txt" con el reporte

*/