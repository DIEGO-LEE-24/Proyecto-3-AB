# Proyectos de Estructuras de Datos

**Estudiante:** Lee Sang Cheol (Diego)  
**Carné:** 2024801079  
**Curso:** Estructuras de Datos  
**Institución:** Tecnológico de Costa Rica  
**Fecha:** Octubre 2025

---

## 📚 Contenido

Este repositorio contiene la implementación de proyectos avanzados de estructuras de datos:

- **[Proyecto 3A: Compresor de Huffman](./Proyecto-3A-Huffman/)** - Algoritmo de compresión sin pérdida
- **[Proyecto 3B: Encriptación con 5 Algoritmos](./Proyecto-3B-Encriptacion/)** - Sistema de encriptación por manipulación de bits

---

## 🎯 Proyecto 3A: Compresor de Huffman

Implementación completa del algoritmo de compresión de Huffman.

### Características:
- ✅ Compresión sin pérdida de información
- ✅ Construcción de árbol binario óptimo
- ✅ Generación de códigos prefix-free
- ✅ Funciona con cualquier tipo de archivo

### Estructuras de Datos:
- Árbol binario (Huffman Tree)
- Priority Queue (Min-Heap)
- Tabla de códigos (Array/Map)

### Complejidad:
- **Tiempo:** O(n + m log m) donde n = tamaño archivo, m = símbolos únicos
- **Espacio:** O(m) ≤ O(256)

### Videos:
- 📺 [Demostración de Uso](LINK_YOUTUBE_3A_DEMO)
- 📺 [Análisis Técnico](LINK_YOUTUBE_3A_TECNICO)

**[Ver código →](./Proyecto-3A-Huffman/)**

---

## 🔐 Proyecto 3B: Encriptación con 5 Algoritmos

Sistema completo de encriptación con 5 algoritmos diferentes basados en manipulación de bits.

### Características:
- ✅ 5 algoritmos de encriptación diferentes
- ✅ Sistema de carpetas automáticas
- ✅ Header con detección automática de algoritmo
- ✅ Encriptación y desencriptación reversible

### Algoritmos Implementados:
1. **Inversión de bit 0** - XOR simple
2. **Rotación de bits** - ROL/ROR circular
3. **XOR con máscaras alternantes** - Patrones 0xAA/0x55
4. **Swap nibbles + inversión** - Intercambio y XOR
5. **XOR secuencial con encadenamiento** - Cipher Block Chaining

### Operadores Bitwise Utilizados:
- `^` (XOR) - Inversión y máscaras
- `<<` `>>` (Shift) - Rotación y desplazamiento
- `&` (AND) - Extracción de bits
- `|` (OR) - Combinación de bits

### Videos:
- 📺 [Demostración de Uso](LINK_YOUTUBE_3B_DEMO)
- 📺 [Análisis Técnico](LINK_YOUTUBE_3B_TECNICO)

**[Ver código →](./Proyecto-3B-Encriptacion/)**

---

## 🛠️ Compilación y Uso

### Requisitos:
- Compilador C++ (Visual Studio, g++, clang++)
- Windows (para funciones de carpetas) o adaptar para Linux/Mac

### Compilar:

#### Proyecto 3A:
```bash
# Visual Studio
# Abrir Proyecto3A-Huffman.cpp en Visual Studio y compilar (F7)

# g++ (Linux/Mac)
g++ -o huffman Proyecto3A-Huffman.cpp -std=c++11
```

#### Proyecto 3B:
```bash
# Visual Studio
# Abrir Proyecto3B-Encriptacion.cpp en Visual Studio y compilar (F7)

# g++ (Windows)
g++ -o encriptador Proyecto3B-Encriptacion.cpp -std=c++11
```

---

## 📖 Documentación Completa

Cada proyecto tiene su propio README con:
- Explicación detallada del algoritmo
- Ejemplos de uso
- Análisis de complejidad
- Decisiones de diseño
- Links a videos explicativos

---

## 📊 Análisis de Complejidad

### Proyecto 3A (Huffman):
| Fase | Complejidad | Descripción |
|------|-------------|-------------|
| Calcular frecuencias | O(n) | Una pasada por archivo |
| Construir árbol | O(m log m) | Priority queue operations |
| Generar códigos | O(m) | DFS del árbol |
| Comprimir | O(n) | Escritura bit a bit |
| **Total** | **O(n)** | **En la práctica** |

### Proyecto 3B (Encriptación):
| Algoritmo | Tiempo | Espacio | Reversible |
|-----------|--------|---------|------------|
| Todos los 5 | O(n) | O(1) | ✅ Sí |

---

## 🎓 Conceptos Demostrados

### Estructuras de Datos:
- ✅ Árboles binarios
- ✅ Heaps / Priority Queues
- ✅ Hash Tables / Maps
- ✅ Arrays

### Algoritmos:
- ✅ Algoritmos greedy (Huffman)
- ✅ DFS (Depth-First Search)
- ✅ Manipulación de bits
- ✅ Procesamiento por bloques

### Análisis:
- ✅ Complejidad temporal (Big O)
- ✅ Complejidad espacial
- ✅ Trade-offs de diseño
- ✅ Optimizaciones

---

## 🔗 Links Útiles

- 📺 [Playlist Completa de Videos](LINK_PLAYLIST_YOUTUBE)
- 📄 [Especificación del Proyecto 3A](./Proyecto-3A-Huffman/docs/)
- 📄 [Especificación del Proyecto 3B](./Proyecto-3B-Encriptacion/docs/)

---

## 📝 Licencia

Este código es para propósitos educativos del curso de Estructuras de Datos.

---

## 👤 Autor

**Lee Sang Cheol (Diego)**  
Estudiante de Ingeniería en Computación  
Tecnológico de Costa Rica  
📧 [tu-email@ejemplo.com]  
🔗 [LinkedIn](tu-linkedin)

---

## ⭐ Resultados

- ✅ Proyecto 3A: Compresión exitosa de hasta 83% en archivos de texto
- ✅ Proyecto 3B: 5 algoritmos funcionando correctamente
- ✅ Todos los archivos restaurados sin pérdida de datos
- ✅ Videos completos de demostración y análisis técnico

---

**Última actualización:** Octubre 2025