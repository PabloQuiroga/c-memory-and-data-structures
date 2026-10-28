# C Memory and Data Structures

Implementación de estructuras de datos genéricas en C, con foco en gestión manual de memoria, manipulación de punteros, reutilización de componentes y validación mediante pruebas automatizadas.

El proyecto reúne implementaciones de estructuras de datos fundamentales y documenta sus requisitos, decisiones de diseño y características técnicas. Forma parte de un portfolio orientado a demostrar conocimientos de programación en C y prácticas de ingeniería de software.

## Objetivos

- Implementar estructuras de datos reutilizables mediante interfaces en C.
- Trabajar con memoria dinámica, punteros y manejo de errores.
- Analizar la complejidad temporal y espacial de las operaciones.
- Reutilizar componentes existentes para construir estructuras de mayor nivel.
- Documentar especificaciones, diseños y decisiones técnicas.
- Automatizar la compilación y ejecución de pruebas mediante GitHub Actions.

## Estructuras implementadas

### Dynamic Array — Arreglo dinámico

Arreglo de elementos genéricos almacenados mediante punteros, con administración de tamaño y capacidad.

Operaciones principales:
- Creación y destrucción.
- Inserción al final y crecimiento dinámico.
- Acceso por índice.
- Eliminación por índice.
- Consulta de tamaño y capacidad.

Documentación: [Especificación](docs/specification.md) · [Diseño](docs/architecture.md)

### Singly Linked List — Lista simplemente enlazada

Estructura basada en nodos enlazados mediante punteros, que permite administrar elementos sin requerir un bloque contiguo de memoria.

Operaciones principales:
- Creación y destrucción.
- Inserción al inicio y al final.
- Acceso por índice.
- Eliminación por índice.
- Consulta de tamaño.

Documentación: [Especificación](docs/specification_II.md) · [Diseño](docs/architecture_II.md)

### Stack — Pila LIFO

Estructura que sigue el principio *Last In, First Out*: el último elemento agregado es el primero en salir.

La implementación reutiliza la lista enlazada como almacenamiento interno.

Operaciones principales:
- `push`: agrega un elemento.
- `pop`: extrae el elemento superior.
- `peek`: consulta el elemento superior.
- `is_empty`: comprueba si la pila está vacía.

Documentación: [Especificación](docs/specification_stack.md) · [Diseño](docs/architecture_stack.md)

### Hash Table — Tabla hash

Estructura que asocia claves con valores y resuelve las colisiones mediante encadenamiento separado, utilizando listas enlazadas.

Operaciones principales:
- Creación y destrucción.
- Inserción de pares clave-valor.
- Búsqueda por clave.
- Eliminación por clave.

Documentación: [Especificación](docs/specification_ht.md) · [Diseño](docs/architecture_ht.md)

## Tecnologías y conceptos

- **Lenguaje:** C.
- **Estándar configurado:** C11.
- **Construcción:** CMake.
- **Pruebas:** framework de pruebas propio.
- **Integración continua:** GitHub Actions.
- **Conceptos:** memoria dinámica, punteros, `void*`, estructuras genéricas, manejo de errores, complejidad algorítmica y reutilización de componentes.

## Estructura del repositorio

```text
.
├── .github/
│   └── workflows/
│       └── ci.yml
├── docs/
│   ├── decisions/
│   │   ├── ADR-001.md
│   │   └── ADR-002.md
│   ├── specification.md
│   ├── specification_II.md
│   ├── specification_stack.md
│   ├── specification_ht.md
│   ├── architecture.md
│   ├── architecture_II.md
│   ├── architecture_stack.md
│   └── architecture_ht.md
├── src/
│   ├── dynamic_array.c
│   ├── dynamic_array.h
│   ├── linked_list.c
│   ├── linked_list.h
│   ├── stack.c
│   ├── stack.h
│   ├── hash_table.c
│   ├── hash_table.h
│   ├── main.c
│   ├── tests.c
│   └── test_framework.h
├── CMakeLists.txt
└── README.md
```

## Compilación y ejecución

Requisitos:
- Un compilador de C compatible con C11.
- CMake 3.20 o superior.
- Una herramienta de construcción compatible, como Make.

Desde la raíz del repositorio, ejecutar:

```bash
cmake -S . -B build
cmake --build build
```

Para ejecutar el programa y las pruebas incluidas:

```bash
./build/c_memory_and_data_structures
```

El ejecutable agrupa las pruebas de las distintas estructuras de datos. El resultado de la ejecución permite revisar qué casos pasan o fallan.

## Análisis de memoria en macOS

En macOS, se puede utilizar la herramienta `leaks` para investigar posibles fugas de memoria:

```bash
leaks --atExit -- ./build/c_memory_and_data_structures
```

Esta herramienta complementa las pruebas funcionales, pero no sustituye una verificación exhaustiva de la seguridad de memoria.

## Integración continua

El workflow de GitHub Actions está configurado para ejecutarse en eventos `push` y `pull_request` dirigidos a `main`.

El proceso automatizado:
1. Obtiene el código del repositorio.
2. Instala las dependencias necesarias.
3. Configura y compila el proyecto con CMake.
4. Ejecuta el programa de pruebas.

La ejecución de CI permite comprobar automáticamente la compilación y los casos de prueba incluidos en el proyecto.

## Decisiones de diseño

Las decisiones técnicas documentadas incluyen:

- [ADR-001: uso de `void**` para almacenamiento genérico](docs/decisions/ADR-001.md).
- [ADR-002: selección de una lista simplemente enlazada](docs/decisions/ADR-002.md).

Estos documentos registran el contexto, las alternativas consideradas y las consecuencias de las decisiones adoptadas.

## Alcance

Este repositorio se centra en estructuras de datos fundamentales y en los conceptos de programación de bajo nivel necesarios para implementarlas en C.

El proyecto no pretende ser una biblioteca de producción ni garantiza por sí solo la ausencia de errores de memoria. La conformidad con los requisitos y la robustez de las implementaciones deben evaluarse mediante revisión de código y pruebas.

## Autor

Pablo Quiroga

[GitHub](https://github.com/PabloQuiroga)

