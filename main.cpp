#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

class FechaError : public runtime_error {
public:
    FechaError() : runtime_error("Error: Fecha invalida.") {}
};

class MateriaError : public runtime_error {
public:
    MateriaError() : runtime_error("Error: Materia invalida.") {}
};

struct Asistencia {
    string fecha;
    string materia;
    string estado; //El estado sobre si asistió, faltó o tiene tardanza.
};

struct Estudiante {
    string nombre;
    int edad;
    float promedio;
    vector<string> materias;
    vector<Asistencia> asistencias;
};

void mostrarEstudiante(const Estudiante& estudiante) {
    cout << "Nombre: " << estudiante.nombre << endl;
    cout << "Edad: " << estudiante.edad << endl;
    cout << "Promedio: " << estudiante.promedio << endl;
}

void mostrarMaterias(const Estudiante& estudiante) {
    cout << "Materias: " << endl;
    for (const auto& materia : estudiante.materias) {
        cout << materia << endl;
    }
    cout << endl;
}

void agregarMateria(Estudiante& estudiante, const string& nuevaMateria) {
    estudiante.materias.push_back(nuevaMateria);
}

void eliminarMateria(Estudiante& estudiante, const string& deshechaMateria) {
    auto it = find(estudiante.materias.begin(), estudiante.materias.end(), deshechaMateria);
    if (it != estudiante.materias.end()) {
        estudiante.materias.erase(it);
        cout << "Materia eliminada: " << deshechaMateria << endl;
    } else {
        cout << "No se encontro la materia." << endl;
    }
}

void mostrarAsistencias(const Estudiante& estudiante) {
    cout << "Asistencias: " << endl;
    for (const auto& asistencia : estudiante.asistencias) {
        cout << "Fecha: " << asistencia.fecha << " | Materia: " << asistencia.materia << " | Estado: " << asistencia.estado << endl;
    }
    cout << endl;
}

void registrarAsistencia(Estudiante& estudiante, const string& fecha, const string& materia, const string& estado) {
    try {
        if (fecha.length() != 10 || fecha[2] != '/' || fecha[5] != '/') {
            throw FechaError();
        }
        if (find(estudiante.materias.begin(), estudiante.materias.end(), materia) == estudiante.materias.end()) {
            throw MateriaError();
        }
        Asistencia nuevaAsistencia = {fecha, materia, estado};
        estudiante.asistencias.push_back(nuevaAsistencia);
        cout << "Assitencia registrada correctamente. " << endl;
    } catch (const exception& e) {
        cout << "Error al registrar asistencia: " << e.what() << endl;
    }
}

int main() {

    Estudiante estudiante1;
    estudiante1.nombre = "Joseph";
    estudiante1.edad = 21;
    estudiante1.promedio = 8.5;

    agregarMateria(estudiante1, "Programacion");
    agregarMateria(estudiante1, "Matematicas");
    agregarMateria(estudiante1, "Ingles");

    mostrarEstudiante(estudiante1);
    mostrarMaterias(estudiante1);

    eliminarMateria(estudiante1, "Ingles");

    mostrarMaterias(estudiante1);

    registrarAsistencia(estudiante1, "05/12/2023", "Programacion", "Asistio");
    registrarAsistencia(estudiante1, "06/12/2023", "Matematicas", "Tardanza");
    registrarAsistencia(estudiante1, "07/12/2023", "Ingles", "Falto");

    mostrarAsistencias(estudiante1);

    return 0;
}
