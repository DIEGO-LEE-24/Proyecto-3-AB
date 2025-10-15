# Proyecto 3A: Compresor/Descompresor de Huffman

**Autor:** Lee Sang Cheol  
**Curso:** Estructuras de Datos y Algoritmos  
**Fecha:** Octubre 2025

---

## 📋 Descripción

Este proyecto implementa un compresor y descompresor de archivos utilizando el **algoritmo de Huffman**. El programa puede comprimir cualquier tipo de archivo (texto, imágenes, ejecutables, etc.) y restaurarlo sin pérdida de información.

### Características principales:
- ✅ Compresión sin pérdida (lossless)
- ✅ Funciona con cualquier tipo de archivo
- ✅ Restauración 100% idéntica al original
- ✅ Header con tabla de códigos y metadata
- ✅ Detección automática de archivos ya comprimidos

---

## 🎯 Objetivos del Proyecto

1. Implementar el algoritmo de Huffman para compresión de datos
2. Manejar archivos binarios en C++
3. Construir y recorrer árboles binarios
4. Implementar operaciones a nivel de bits
5. Crear un programa robusto con manejo de errores

---

## 🚀 Compilación

### Requisitos:
- Visual Studio 2019 o superior
- C++17 o superior
- Windows OS

### Pasos:
1. Abrir `Huffman.cpp.sln` en Visual Studio
2. Configurar en modo **Release** o **Debug**
3. Compilar (Ctrl + Shift + B)
4. El ejecutable se genera en `x64/Debug/` o `x64/Release/`

---

## 💻 Uso

### Sintaxis básica:
```cmd
Proyecto3A-Huffman.exe <modo> <archivo>
```

### Parámetros:
- `<modo>`: 
  - `c` = Comprimir
  - `d` = Descomprimir
- `<archivo>`: Ruta del archivo a procesar

---

## 📖 Ejemplos de Uso

### Ejemplo 1: Comprimir un archivo de texto
```cmd
Proyecto3A-Huffman.exe c prueba.txt
```
**Resultado:** Se crea `prueba.txt.huf` (archivo comprimido)

### Ejemplo 2: Descomprimir un archivo
```cmd
Proyecto3A-Huffman.exe d prueba.txt.huf
```
**Resultado:** Se crea `prueba.txt.restored` (archivo original restaurado)

### Ejemplo 3: Comprimir una imagen
```cmd
Proyecto3A-Huffman.exe c imagen.bmp
```
**Resultado:** Se crea `imagen.bmp.huf`

### Ejemplo 4: Verificar integridad
```cmd
fc /b archivo.txt archivo.txt.restored
```
**Resultado esperado:** "FC: no se encontraron diferencias"

---

## 🧪 Casos de Prueba

### Test 1: Archivos de texto
- **Archivo:** `prueba.txt` (20 caracteres)
- **Resultado esperado:** Compresión ~60-70%
- **Verificación:** ✅ Original = Restaurado

### Test 2: Imágenes BMP
- **Archivo:** `imagen.bmp` (~500 KB)
- **Resultado esperado:** Compresión ~30-50%
- **Verificación:** ✅ Imagen se ve idéntica

### Test 3: Archivos JPG
- **Archivo:** `foto.jpg` (~300 KB)
- **Resultado esperado:** Archivo comprimido MÁS GRANDE (normal)
- **Explicación:** JPG ya está comprimido, Huffman no puede mejorarlo
- **Verificación:** ✅ Original = Restaurado

### Test 4: Archivos ejecutables
- **Archivo:** `programa.exe`
- **Resultado esperado:** Compresión variable
- **Verificación:** ✅ Ejecutable funciona después de restaurar

---

## 🔬 Algoritmo de Huffman

### Pasos del algoritmo:

#### 1. **Análisis de frecuencias**
```
Leer archivo byte por byte
Contar ocurrencias de cada símbolo (0-255)
Ejemplo: 'a' → 50 veces, 'b' → 30 veces, 'c' → 20 veces
```

#### 2. **Construcción del árbol**
```
Crear nodos hoja para cada símbolo con su frecuencia
Mientras haya más de un nodo:
    1. Tomar los 2 nodos con menor frecuencia
    2. Crear nodo padre con suma de frecuencias
    3. Insertar nodo padre en la lista
```

#### 3. **Generación de códigos**
```
Recorrer el árbol desde la raíz:
    - Rama izquierda → agregar '0'
    - Rama derecha → agregar '1'
    - Al llegar a una hoja → código completo

Ejemplo:
    'a' → "0"      (más frecuente → código corto)
    'b' → "10"
    'c' → "110"
    'd' → "1110"   (menos frecuente → código largo)
```

#### 4. **Compresión**
```
Escribir header con:
    - Número de símbolos únicos
    - Tabla de equivalencias (símbolo → código)
    - Tamaño original del archivo
    
Reemplazar cada byte del original por su código Huffman
Escribir bits comprimidos al archivo .huf
```

#### 5. **Descompresión**
```
Leer header del archivo .huf
Reconstruir árbol de Huffman
Leer bits uno por uno:
    - Empezar en la raíz
    - 0 → ir a hijo izquierdo
    - 1 → ir a hijo derecho
    - Al llegar a hoja → escribir símbolo
    - Volver a la raíz
```

---

## 📊 Estructura del Archivo .huf

```
┌─────────────────────────────────────┐
│           HEADER                    │
├─────────────────────────────────────┤
│ - Número de símbolos únicos (4B)    │
│ - Tamaño original del archivo (8B)  │
│ - Tabla de códigos:                 │
│   * Símbolo (1B)                    │
│   * Longitud del código (1B)        │
│   * Código Huffman (variable)       │
│   [Repetir para cada símbolo]       │
├─────────────────────────────────────┤
│           DATOS COMPRIMIDOS         │
├─────────────────────────────────────┤
│ - Secuencia de bits Huffman         │
│ - Padding bits al final (si necesario)│
└─────────────────────────────────────┘
```

---

## 🎓 Conceptos Clave

### Propiedad Prefix-Free
- Ningún código es prefijo de otro
- Permite decodificación sin ambigüedad
- Ejemplo:
  ```
  ✅ Correcto: "0", "10", "110", "111"
  ❌ Incorrecto: "0", "01", "011" (ambiguo!)
  ```

### Compresión óptima
- Huffman genera códigos de longitud óptima
- Cumple el límite de Shannon: H(X) ≤ L < H(X) + 1
- Donde H(X) es la entropía del archivo

### Cuándo funciona bien:
- ✅ Archivos de texto (.txt, .csv, .html)
- ✅ Imágenes sin comprimir (.bmp)
- ✅ Datos con distribución desigual
- ❌ Archivos ya comprimidos (.jpg, .zip, .mp3)
- ❌ Datos aleatorios o encriptados

---

## 📈 Resultados Esperados

| Tipo de Archivo | Tamaño Original | Tamaño Comprimido | Ratio |
|----------------|-----------------|-------------------|-------|
| prueba.txt     | 20 bytes        | ~6 bytes          | 70%   |
| documento.txt  | 500 bytes       | ~200 bytes        | 60%   |
| imagen.bmp     | 500 KB          | ~300 KB           | 40%   |
| foto.jpg       | 300 KB          | ~305 KB           | -2%   |
| programa.exe   | 100 KB          | ~80 KB            | 20%   |

---

## 🐛 Manejo de Errores

El programa maneja los siguientes casos de error:

1. **Archivo no encontrado**
   ```
   ERROR: No se puede abrir el archivo [nombre]
   ```

2. **Archivo vacío**
   ```
   ERROR: Archivo vacío o no se puede leer
   ```

3. **Archivo corrupto (.huf)**
   ```
   ERROR: Archivo .huf corrupto o formato inválido
   ```

4. **Memoria insuficiente**
   ```
   ERROR: No se puede asignar memoria
   ```

---

## 🔧 Estructura del Código

```
Huffman.cpp
│
├── main()
│   ├── Validar argumentos
│   └── Llamar a comprimir() o descomprimir()
│
├── comprimir()
│   ├── calcularFrecuencias()
│   ├── construirArbol()
│   ├── generarCodigos()
│   ├── escribirHeader()
│   └── comprimirDatos()
│
├── descomprimir()
│   ├── leerHeader()
│   ├── reconstruirArbol()
│   └── descomprimirDatos()
│
└── Estructuras de datos:
    ├── struct Nodo
    ├── map<byte, string> codigosHuffman
    └── priority_queue para el árbol
```

---

## 📚 Referencias

- **Huffman, D. A.** (1952). "A Method for the Construction of Minimum-Redundancy Codes"
- **Cormen et al.** "Introduction to Algorithms" - Capítulo sobre Códigos de Huffman
- **Material del curso:** Presentaciones y ejercicios del profesor

---

## ✅ Checklist de Funcionalidades

- [x] Lectura de archivos binarios
- [x] Cálculo de frecuencias
- [x] Construcción del árbol de Huffman
- [x] Generación de códigos prefix-free
- [x] Escritura de header con metadata
- [x] Compresión bit a bit
- [x] Descompresión correcta
- [x] Validación: original = restaurado
- [x] Manejo de errores robusto
- [x] Soporte para cualquier tipo de archivo

---

## 🎥 Video Demostración

**📺 Ver video completo:** [YouTube - Proyecto 3A Huffman](https://youtu.be/S28fabMBBYM)

El video de demostración incluye:
1. ✅ Compresión de archivos de texto
2. ✅ Compresión de imágenes BMP
3. ✅ Prueba con archivos JPG (muestra que no mejora)
4. ✅ Verificación de integridad con `fc /b`
5. ✅ Explicación del código y algoritmo
6. ✅ Comparación de resultados y análisis de compresión

**Duración:** ~8 minutos  
**Idioma:** Español

---

## 📞 Contacto

**Estudiante:** Lee Sang Cheol  
**Proyecto:** 3A - Compresor de Huffman  
**Institución:** Tecnológico de Costa Rica

---

## 📄 Licencia

Este proyecto es parte del curso de Estructuras de Datos y Algoritmos.  
Uso exclusivo con fines educativos.

---

**Fecha de entrega:** Octubre 2025  
**Versión:** 1.0
