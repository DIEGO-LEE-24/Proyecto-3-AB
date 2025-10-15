# Proyecto 3B: Sistema de Encriptación con 5 Algoritmos

Implementación de 5 algoritmos de encriptación diferentes basados en manipulación de bits.

---

## 🎯 Descripción

Sistema completo de encriptación que implementa 5 algoritmos diferentes utilizando operadores bitwise. Incluye:
- ✅ Detección automática del algoritmo mediante header
- ✅ Creación automática de carpetas
- ✅ Encriptación y desencriptación reversible 100%

---

## 🔐 Los 5 Algoritmos

### 1️⃣ Algoritmo 1: Inversión del Bit 0
**Operadores:** `^` (XOR), `<<` (shift)

```cpp
void Veneno_1(char Bloque[], int limite) {
    for (i = 0; i <= limite; i++) {
        InvertirBit(Bloque[i], 0);  // XOR con máscara 00000001
    }
}
```

**Cómo funciona:**
- Invierte solo el bit **menos significativo** (bit 0)
- Ejemplo: `01010110` → `01010111`

**Propiedad:** XOR es autoinverso → `A ^ B ^ B = A`

**Nivel de seguridad:** ⭐ Muy bajo (educativo)

---

### 2️⃣ Algoritmo 2: Rotación de Bits (ROL)
**Operadores:** `<<` `>>` (shifts), `|` (OR)

```cpp
void Veneno_2(char Bloque[], int limite) {
    unsigned char temp = Bloque[i];
    Bloque[i] = (temp << 3) | (temp >> 5);  // Rotar 3 bits
}
```

**Cómo funciona:**
- Rota todos los bits 3 posiciones a la **izquierda**
- Los bits que salen por la izquierda regresan por la derecha

**Ejemplo:**
```
Original:  10110011
<< 3:      10011000 (perdimos 101)
>> 5:      00000101 (recuperamos 101)
OR:        10011101 ✓
```

**Desencriptar:** Rotar en dirección opuesta (derecha)

**Nivel de seguridad:** ⭐⭐ Bajo (patrón fijo)

---

### 3️⃣ Algoritmo 3: XOR con Máscaras Alternantes
**Operadores:** `^` (XOR)

```cpp
void Veneno_3(char Bloque[], int limite) {
    if (i % 2 == 0) {
        Bloque[i] ^= 0xAA;  // 10101010
    } else {
        Bloque[i] ^= 0x55;  // 01010101
    }
}
```

**Cómo funciona:**
- Posiciones **pares**: XOR con `0xAA` (10101010)
- Posiciones **impares**: XOR con `0x55` (01010101)

**Ventaja:** Bytes idénticos se encriptan diferente según su posición

**Propiedad:** XOR es autoinverso → desencriptar = encriptar

**Nivel de seguridad:** ⭐⭐⭐ Medio (rompe patrones)

---

### 4️⃣ Algoritmo 4: Swap Nibbles + Inversión
**Operadores:** `&` (AND), `<<` `>>` (shifts), `|` (OR), `^` (XOR)

```cpp
void Veneno_4(char Bloque[], int limite) {
    unsigned char temp = Bloque[i];
    // Intercambiar nibbles
    unsigned char swapped = ((temp & 0x0F) << 4) | ((temp & 0xF0) >> 4);
    // XOR adicional
    swapped ^= 0x54;
    Bloque[i] = swapped;
}
```

**Cómo funciona:**

**Paso 1:** Swap nibbles (intercambiar mitades del byte)
```
Byte: [1011][0011] → [0011][1011]
```

**Paso 2:** XOR con `0x54` para confusión adicional

**Desencriptar:** Orden inverso (XOR primero, luego swap)

**Nivel de seguridad:** ⭐⭐⭐⭐ Medio-alto (dos transformaciones)

---

### 5️⃣ Algoritmo 5: XOR Secuencial (Encadenamiento)
**Operadores:** `^` (XOR)

```cpp
void Veneno_5(char Bloque[], int limite) {
    for (int i = limite; i > 0; i--) {
        Bloque[i] = Bloque[i] ^ Bloque[i-1];
    }
}
```

**Cómo funciona:**
- Cada byte se XORea con el **anterior**
- Procesa de **atrás hacia adelante**

**Ejemplo:**
```
Original:  [A] [B] [C] [D]
Encriptar: [A] [B^A] [C^B] [D^C]
```

**Propiedad crítica:** **Encadenamiento**
- Cambiar un byte afecta a todos los siguientes
- Similar a Cipher Block Chaining (CBC)

**Desencriptar:** Proceso inverso, de adelante hacia atrás

**Nivel de seguridad:** ⭐⭐⭐⭐⭐ Alto (para este nivel educativo)

---

## 🎯 Sistema de Header Automático

### Header (4 bytes):
```cpp
['E'] ['N'] ['C'] [tipo:1-5]
```

### ¿Por qué es importante?

**Encriptación:**
```cpp
unsigned char header[4] = {'E', 'N', 'C', tipo};
fwrite(header, 1, 4, archivo);
```
Guarda el algoritmo usado en el archivo mismo.

**Desencriptación:**
```cpp
fread(header, 1, 4, archivo);
int tipo = header[3];  // Detecta automáticamente

switch(tipo) {
    case 1: Antidoto_1(); break;
    case 2: Antidoto_2(); break;
    ...
}
```

**Ventaja:** No necesitas recordar qué algoritmo usaste. El programa lo detecta automáticamente.

---

## 📁 Sistema de Carpetas Automáticas

### Carpetas creadas:
```
c:\misproyectosdelTec-bak\       (archivos encriptados)
c:\misproyectosdelTec-Restore\   (archivos restaurados)
```

El programa crea estas carpetas automáticamente si no existen.

---

## 🚀 Uso

### Encriptar:
```bash
Proyecto3B-Encriptacion.exe e [tipo:1-5] [archivo]

# Ejemplos:
Proyecto3B-Encriptacion.exe e 1 MiFoto.jpg
Proyecto3B-Encriptacion.exe e 2 Documento.pdf
Proyecto3B-Encriptacion.exe e 5 Secreto.txt
```

**Resultado:** `c:\misproyectosdelTec-bak\MiFoto.jpg.enc`

### Desencriptar:
```bash
Proyecto3B-Encriptacion.exe d [archivo.enc]

# Ejemplo:
Proyecto3B-Encriptacion.exe d c:\misproyectosdelTec-bak\MiFoto.jpg.enc
```

**Resultado:** `c:\misproyectosdelTec-Restore\MiFoto.jpg`

---

## 🔍 Verificación

### Windows:
```cmd
fc /b archivo_original.txt c:\misproyectosdelTec-Restore\archivo_original.txt
```

### Resultado esperado:
```
FC: no se encontraron diferencias
```

✅ Archivo restaurado es **100% idéntico** al original.

---

## 📊 Análisis de Complejidad

### Todos los algoritmos:
| Aspecto | Complejidad | Detalles |
|---------|-------------|----------|
| **Tiempo** | O(n) | n = tamaño del archivo |
| **Espacio** | O(1) | Buffer fijo de 1000 bytes |
| **Reversible** | ✅ Sí | Todos son 100% reversibles |

### Procesamiento por bloques:
```cpp
char buffer[1000];
while (leidos = fread(buffer, 1, 1000, archivo)) {
    Algoritmo_X(buffer, leidos);
    fwrite(buffer, 1, leidos, salida);
}
```

**Ventajas:**
- ✅ No carga archivo completo en memoria
- ✅ Funciona con archivos de GB
- ✅ Eficiente en I/O

---

## 🎓 Conceptos Demostrados

### Operadores Bitwise:

#### XOR (`^`) - Inversión
```cpp
a ^ b      // Invierte bits donde b=1
a ^ b ^ b  // Vuelve a 'a' (autoinverso)
```

#### Shift Left/Right (`<<` `>>`) - Desplazamiento
```cpp
a << 3  // Multiplica por 8
a >> 3  // Divide por 8 (con relleno)
```

#### AND (`&`) - Extracción
```cpp
a & 0x0F  // Extrae nibble bajo
a & 0xF0  // Extrae nibble alto
```

#### OR (`|`) - Combinación
```cpp
a | b  // Combina bits de ambos
```

---

## 📈 Comparación de Algoritmos

| Algoritmo | Complejidad | Seguridad | Reversible | Operadores |
|-----------|-------------|-----------|------------|------------|
| 1. Inversión bit 0 | Muy simple | ⭐ | ✅ | `^` `<<` |
| 2. Rotación | Simple | ⭐⭐ | ✅ | `<<` `>>` `\|` |
| 3. XOR alternante | Media | ⭐⭐⭐ | ✅ | `^` |
| 4. Swap nibbles | Media-Alta | ⭐⭐⭐⭐ | ✅ | `&` `<<` `>>` `\|` `^` |
| 5. Encadenamiento | Alta | ⭐⭐⭐⭐⭐ | ✅ | `^` |

---

## ⚠️ Advertencia de Seguridad

**IMPORTANTE:** Estos algoritmos son **EDUCATIVOS**.

❌ **NO usar para:**
- Datos sensibles reales
- Contraseñas
- Información financiera
- Comunicaciones seguras

✅ **Usar para:**
- Aprender manipulación de bits
- Entender operadores bitwise
- Proyectos educativos

**Para seguridad real:** Usar AES, RSA, o librerías criptográficas probadas.

---

## 🎥 Videos

- 📺 **Demostración de Uso:** [Link YouTube]
- 📺 **Análisis Técnico:** [Link YouTube]

En los videos se explica:
- ✅ Ejecución de los 5 algoritmos
- ✅ Cómo funcionan los operadores bitwise
- ✅ Por qué cada algoritmo es reversible
- ✅ Análisis matemático de las operaciones
- ✅ Sistema de header automático

---

## 🔧 Compilación

### Visual Studio (Windows):
1. Abrir `Proyecto3B-Encriptacion.cpp`
2. Build → Build Solution (F7)
3. Ejecutar con argumentos

### g++ (Windows):
```bash
g++ -o encriptador Proyecto3B-Encriptacion.cpp -std=c++11
encriptador.exe e 1 archivo.txt
```

---

## 💡 Decisiones de Diseño

### 1. Procesamiento por bloques (1000 bytes)
- Balance entre I/O y memoria
- Escalable a archivos grandes

### 2. Header de 4 bytes
- Overhead mínimo (<0.1% para archivos >4KB)
- Detección automática del algoritmo
- Información dentro del archivo (no se pierde al renombrar)

### 3. Carpetas fijas
- Organización automática
- Evita sobrescribir archivos originales
- Facilita gestión de archivos

### 4. Todos los algoritmos reversibles
- XOR: autoinverso
- Rotación: operación inversa
- Swap: operación simétrica
- Encadenamiento: orden inverso

---

## 🏆 Características Destacadas

1. **5 algoritmos diferentes** - del más simple al más complejo
2. **Header inteligente** - detección automática
3. **100% reversible** - verificado byte por byte
4. **Escalable** - funciona con archivos de cualquier tamaño
5. **Organizado** - sistema de carpetas automático
6. **Educativo** - cada algoritmo demuestra conceptos diferentes

---

## 📚 Referencias

- "Hacker's Delight" - Henry S. Warren Jr. (manipulación de bits)
- "The Art of Computer Programming" - Donald Knuth
- Wikipedia: [Bitwise Operations](https://en.wikipedia.org/wiki/Bitwise_operation)

---

## 📝 Autor

**Lee Sang Cheol (Diego)**  
Proyecto 3B - Estructuras de Datos  
Tecnológico de Costa Rica  
Octubre 2025