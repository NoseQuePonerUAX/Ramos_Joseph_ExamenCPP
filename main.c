#include <stdio.h>
#include <string.h>

#define MAX_MATERIAS 10
#define MAX_NOMBRE 50

struct Asistencia {
    char fecha[11]; // +1 para el carácter nulo
    char materia[MAX_NOMBRE];
    char estado[MAX_NOMBRE];
};

struct Estudiante {
    char nombre[MAX_NOMBRE];
    int edad;
    float promedio;
    char materias[MAX_MATERIAS][MAX_NOMBRE];
    struct Asistencia asistencias[MAX_MATERIAS];
    int numMaterias;
    int numAsistencias;
};

void mostrarEstudiante(const struct Estudiante *estudiante) {
    printf("Nombre: %s\n", estudiante->nombre);
    printf("Edad: %d\n", estudiante->edad);
    printf("Promedio: %.2f\n", estudiante->promedio);
}

void mostrarMaterias(const struct Estudiante* estudiante) {
    printf("Materias: \n");
    for (int i = 0; i < estudiante->numMaterias; ++i) {
        printf("%s\n", estudiante->materias[i]);
    }
    printf("\n");
}

void agregarMateria(struct Estudiante* estudiante, const char* nuevaMateria) {
    if (estudiante->numMaterias < MAX_MATERIAS) {
        strcpy(estudiante->materias[estudiante->numMaterias], nuevaMateria);
        estudiante->numMaterias++;
    } else {
        printf("No se pueden agregar más materias.\n");
    }
}

void eliminarMateria(struct Estudiante* estudiante, const char* deshechaMateria) {
    for (int i = 0; i < estudiante->numMaterias; ++i) {
        if (strcmp(estudiante->materias[i], deshechaMateria) == 0) {
            for (int j = i; j < estudiante->numMaterias - 1; ++j) {
                strcpy(estudiante->materias[j], estudiante->materias[j + 1]);
            }
            estudiante->numMaterias--;
            printf("Materia eliminada: %s\n", deshechaMateria);
            return;
        }
    }
    printf("No se encontro la materia.\n");
}

void mostrarAsistencias(const struct Estudiante* estudiante) {
    printf("Asistencias: \n");
    for (int i = 0; i < estudiante->numAsistencias; ++i) {
        printf("Fecha: %s | Materia: %s | Estado: %s\n", estudiante->asistencias[i].fecha,
               estudiante->asistencias[i].materia, estudiante->asistencias[i].estado);
    }
    printf("\n");
}

void registrarAsistencia(struct Estudiante* estudiante, const char* fecha, const char* materia, const char* estado) {
    // Validar el formato de fecha (solo para demostración, puedes ajustarlo según tus necesidades)
    if (strlen(fecha) != 10 || fecha[2] != '/' || fecha[5] != '/') {
        printf("Error: Formato de fecha no válido.\n");
        return;
    }
    int materiaEncontrada = 0;
    for (int i = 0; i < estudiante->numMaterias; ++i) {
        if (strcmp(estudiante->materias[i], materia) == 0) {
            materiaEncontrada = 1;
            break;
        }
    }
    if (!materiaEncontrada) {
        printf("Error: Materia no registrada.\n");
        return;
    }

    // Registrar la asistencia
    if (estudiante->numAsistencias < MAX_MATERIAS) {
        strcpy(estudiante->asistencias[estudiante->numAsistencias].fecha, fecha);
        strcpy(estudiante->asistencias[estudiante->numAsistencias].materia, materia);
        strcpy(estudiante->asistencias[estudiante->numAsistencias].estado, estado);
        estudiante->numAsistencias++;
        printf("Asistencia registrada correctamente.\n");
    } else {
        printf("Error: No se pueden registrar más asistencias.\n");
    }
}
int main() {
    struct Estudiante estudiante1;
    strcpy(estudiante1.nombre, "Joseph");
    estudiante1.edad = 21;
    estudiante1.promedio = 8.5;
    estudiante1.numMaterias = 0;
    estudiante1.numAsistencias = 0;

    agregarMateria(&estudiante1, "Programacion");
    agregarMateria(&estudiante1, "Matematicas");
    agregarMateria(&estudiante1, "Ingles");

    mostrarEstudiante(&estudiante1);
    mostrarMaterias(&estudiante1);

    eliminarMateria(&estudiante1, "Ingles");

    mostrarMaterias(&estudiante1);
    registrarAsistencia(&estudiante1, "05/12/2023", "Programacion", "Asistio");
    registrarAsistencia(&estudiante1, "06/12/2023", "Matematicas", "Tardanza");
    registrarAsistencia(&estudiante1, "07/12/2023", "Ingles", "Falto");

    mostrarAsistencias(&estudiante1);

    return 0;
}