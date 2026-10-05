# c-memory-and-data-structures
Implementación de estructuras de datos genéricas en C con enfoque en gestión manual de memoria y seguridad

### Compilar
```
gcc -g src/main.c src/dynamic_array.c src/tests.c -o my_program
```

### Ejecuta el programa:
Desde el metodo `main` en la clase `main.c`

### Revisar fugas de memoria en macOS
Puedes ejecutar el programa con `leaks` para revisar si quedan asignaciones sin liberar:
```
leaks --atExit -- ./build/c_memory_and_data_structures
```
