#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <algorithm>

using namespace std;

struct Autor {
    int id_autor;
    string nombre;
    string nacionalidad;
};

struct Libro {
    int id_libro;
    string titulo;
    string ISBN;
    int año;
    int id_autor;
};

struct Estudiante {
    int id_estudiante;
    string nombre;
    string grado;
};

struct Prestamo {
    int id_prestamo;
    int id_libro;
    int id_estudiante;
    string fecha_prestamo;
    string fecha_devolucion; 
};


class Biblioteca {
    private:
    vector<Autor> autores;
    vector<Libro> libros;
    vector<Estudiante> estudiantes;
    vector<Prestamo> prestamos;

    void cargarAutores() {
        ifstream archivo("autores.txt");
        if (!archivo.is_open()) return;

        string linea;
        while(getline(archivo, linea)){
            stringstream ss(linea);
            Autor autor;
            string id;

            getline(ss, id, ',');
            autor.id_autor = stoi(id);
            getline(ss, autor.nombre, ',');
            getline(ss,autor.nacionalidad,',');

            autores.push_back(autor);
        }
        archivo.close();
    }

    void cargarLibros(){
        ifstream archivo("libros.txt");
        if(!archivo.is_open()) return;
        
        string linea;
        while(getline(archivo,linea)){
            stringstream ss(linea);
            Libro libro;
            string id;
            string year;

            getline(ss, id, ',');  
            libro.id_libro = stoi(id);
            getline(ss,libro.titulo,',');
            getline(ss,libro.ISBN,',');
            getline(ss,year,',');
            libro.año = stoi(year);
            getline(ss,id,',');
            libro.id_autor = stoi(id);

            libros.push_back(libro);
        }
        archivo.close();
    }

    void cargarEstudiantes() {
        ifstream archivo("estudiantes.txt");
        if (!archivo.is_open()) return;
        
        string linea;
        while (getline(archivo, linea)) {
            stringstream ss(linea);
            Estudiante estudiante;
            string id;
            
            getline(ss, id, ','); 
            estudiante.id_estudiante = stoi(id);
            getline(ss, estudiante.nombre, ',');
            getline(ss, estudiante.grado, ',');
            
            estudiantes.push_back(estudiante);
        }
        archivo.close();
    }

    void cargarPrestamos(){
        ifstream archivo("prestamos.txt");
        if(!archivo.is_open()) return;
        
        string linea;
        while(getline(archivo,linea)){
            stringstream ss(linea);
            Prestamo prestamo;
            string id;
            string year;

            getline(ss, id, ',');  
            prestamo.id_prestamo = stoi(id);
            getline(ss,id,',');
            prestamo.id_libro = stoi(id);
            getline(ss,id,',');
            prestamo.id_estudiante = stoi(id);
            getline(ss,prestamo.fecha_prestamo,',');
            getline(ss,prestamo.fecha_devolucion,',');

            prestamos.push_back(prestamo);
        }
        archivo.close();
    }
    
    void guardarAutores(){
        ofstream archivo("autores.txt");
        for (const auto& autor:autores){
            archivo << autor.id_autor<<","<<autor.nombre<<","<<autor.nacionalidad<<endl;
        }
        archivo.close();
    }

    void guardarLibros(){
        ofstream archivo("libros.txt");
        for (const auto& libro:libros){
            archivo << libro.id_libro<<","<<libro.titulo<<","<<libro.ISBN<<','<<libro.año<<","<<libro.id_autor<<endl;
        }
        archivo.close();
    }

    void guardarEstudiantes(){
        ofstream archivo("estudiantes.txt");
        for (const auto& estudiante:estudiantes){
            archivo << estudiante.id_estudiante<<","<<estudiante.nombre<<","<<estudiante.grado<<endl;
        }
        archivo.close();
    }

    void guardarPrestamos(){
        ofstream archivo("prestamos.txt");
        for (const auto& prestamo:prestamos){
            archivo << prestamo.id_prestamo<<","<<prestamo.id_libro<<","<<prestamo.id_estudiante<<','<<prestamo.fecha_prestamo<<','<<prestamo.fecha_devolucion<<endl;
        }
        archivo.close();
    }

    public:
    Biblioteca() {}

    void cargarDatos() {
        cargarAutores();
        cargarLibros();
        cargarEstudiantes();
        cargarPrestamos();
        cout << "Datos cargados"<<endl;
    }
    
    void guardarDatos() {
        guardarAutores();
        guardarLibros();
        guardarEstudiantes();
        guardarPrestamos();
        cout << "Datos guardados"<<endl;
    }

//Crear IDs sin repetir 
    int idAutor() {
        if (autores.empty()) return 1;
        int max_id = 0;
        for (const auto& autor:autores) {
            if (autor.id_autor > max_id) max_id = autor.id_autor;
        }
        return max_id + 1;
    }
    
    int idLibro() {
        if (libros.empty()) return 1;
        int max_id = 0;
        for (const auto& libro:libros) {
            if (libro.id_libro > max_id) max_id = libro.id_libro;
        }
        return max_id + 1;
    }
    
    int idEstudiante() {
        if (estudiantes.empty()) return 1;
        int max_id = 0;
        for (const auto& estudiante:estudiantes) {
            if (estudiante.id_estudiante>max_id) max_id=estudiante.id_estudiante;
        }
        return max_id + 1;
    }
    
    int idPrestamo() {
        if (prestamos.empty()) return 1;
        int max_id = 0;
        for (const auto& prestamo:prestamos) {
            if (prestamo.id_prestamo>max_id) max_id=prestamo.id_prestamo;
        }
        return max_id + 1;
    }

    //Autores
    void agregarAutor() {
        Autor autor;

        cin.ignore();
        autor.id_autor = idAutor();
        cout << "Nombre: ";
        getline(cin, autor.nombre);
        cout << "Nacionalidad: ";
        getline(cin, autor.nacionalidad);
        
        autores.push_back(autor);
        cout << "Autor agregado"<<endl;
    }

    void listarAutores() {
        if (autores.empty()) {
            cout << "No hay autores"<<endl;
            return;
        }
        
        cout << "Lista de Autores:"<<endl;
        for (const auto& autor:autores) {
            cout << autor.id_autor << " - " << autor.nombre << " ," << autor.nacionalidad <<endl;
        }
    }
    
    void actualizarAutor() {
        int id;
        cout << "ID del autor que se quiere actualziar: ";
        cin >> id;
        
        for (auto& autor:autores) {
            if (autor.id_autor == id) {
                cin.ignore();
                cout << "Nombre: ";
                getline(cin, autor.nombre);
                cout << "Nacionalidad: ";
                getline(cin, autor.nacionalidad);
                cout << "Autor actualizado"<<endl;
                return;
            }
        }
        cout<<"No se encontro al autor"<<endl;
    }
    
    void eliminarAutor() {
        int id;
        cout << "ID del autor: ";
        cin >> id;
        
        for (const auto& libro:libros) {
            if (libro.id_autor == id) {
                cout << "El autor tiene libros asociados no se puede eliminar ahora mismo"<<endl;
                return;
            }
        }
        
        for (int i = 0; i < autores.size(); i++) {
            if (autores[i].id_autor == id) {
                autores.erase(autores.begin() + i);
                cout<<"El autor ha sido eliminado";
                return;
            }
        }
        cout << "Autor no encontrado"<<endl;
    }

    //Libros
    void agregarLibro() {
        Libro libro;
        libro.id_libro = idLibro();
        
        cin.ignore();
        cout << "Titulo: ";
        getline(cin, libro.titulo);
        cout << "ISBN: ";
        getline(cin, libro.ISBN);
        cout << "Año: ";
        cin >> libro.año;
        cout << "ID del autor: ";
        cin >> libro.id_autor;
        
        bool autor_existe = false;
        for (const auto& autor:autores) {
            if (autor.id_autor == libro.id_autor) {
                autor_existe = true;
                break;
            } else{
                cout<<"El autor no existe"<<endl;
                return;
            }
        }
        
        libros.push_back(libro);
        cout << "Libro agregado"<<endl;
    }
    
    void listarLibros() {
        if (libros.empty()) {
            cout << "No hay libros"<<endl;
            return;
        }
        
        cout << "Lista de libros"<<endl;
        for (const auto& libro:libros) {
            string nombre_autor = "Anonimo";
            for (const auto& autor:autores) {
                if (autor.id_autor == libro.id_autor) {
                    nombre_autor = autor.nombre;
                    break;
                }
            }
            cout << libro.id_libro << ", " << libro.titulo << ", " << libro.año << ", " << nombre_autor <<endl;
        }
    }
    
    void actualizarLibro() {
        int id;
        cout << "ID del libro: ";
        cin >> id;
        
        for (auto& libro:libros) {
            if (libro.id_libro == id) {
                cin.ignore();
                cout << "Titulo: ";
                getline(cin, libro.titulo);
                cout << "ISBN: ";
                getline(cin, libro.ISBN);
                cout << "Año: ";
                cin >> libro.año;
                cout << "Libro actualizado"<<endl;
                return;
            }
        }
        cout << "Libro no encontrado"<<endl;
    }

    void eliminarLibro() {
        int id;
        cout << "ID del libro: ";
        cin >> id;
        
        for (int i = 0; i < prestamos.size(); i++) {
            if (prestamos[i].id_libro == id && prestamos[i].fecha_devolucion.empty()) {
                cout << "El libro tiene un prestamo activo"<<endl;
                return;
            }
        }
        
        for (int i = 0; i < libros.size(); i++) {
            if (libros[i].id_libro == id) {
                libros.erase(libros.begin() + i);
                cout << "Libro eliminado"<<endl;
                return;
            }
        }
        
        cout << "Libro no encontrado"<<endl;
    }

    //Estudiante
    void agregarEstudiante() {
        Estudiante estudiante;
        estudiante.id_estudiante = idEstudiante();
        
        cin.ignore();
        cout << "Nombre: ";
        getline(cin, estudiante.nombre);
        cout << "Grado: ";
        getline(cin, estudiante.grado);
        
        estudiantes.push_back(estudiante);
        cout << "Estudiante agregado" <<endl;
    }
    
    void listarEstudiantes(){
        if (estudiantes.empty()) {
            cout << "No hay estudiantes"<<endl;
            return;
        }
        
        cout << "Lista de Estudiante"<<endl;
        for (const auto& estudiante : estudiantes) {
            cout << estudiante.id_estudiante << ", " << estudiante.nombre << ", " << estudiante.grado << ", "<<endl;
        }
    }
    
    void actualizarEstudiante() {
        int id;
        cout << "ID del estudiante: ";
        cin >> id;
        
        for (auto& estudiante:estudiantes) {
            if (estudiante.id_estudiante == id) {
                cin.ignore();
                cout << "Nombre: ";
                getline(cin, estudiante.nombre);
                cout << "Grado: ";
                getline(cin, estudiante.grado);
                cout << "Estudiante actualizado"<<endl;
                return;
            }
        }
        cout << "Estudiante no encontrado"<<endl;
    }
    
    void eliminarEstudiante() {
    int id;
    cout << "ID del estudiante: ";
    cin >> id;
    
    for (int i = 0; i < prestamos.size(); i++) {
        if (prestamos[i].id_estudiante == id && prestamos[i].fecha_devolucion.empty()) {
            cout << "El estudiante tiene prestamos activos"<<endl;
            return;
            }
        }
        
    for (int i = 0; i < estudiantes.size(); i++) {
        if (estudiantes[i].id_estudiante == id) {
            estudiantes.erase(estudiantes.begin() + i);
            cout << "Estudiante eliminado"<<endl;
            return;
            }
        }
    cout << "Estudiante no encontrado"<<endl;
    }

    void registrarPrestamo() {
        Prestamo prestamo;
        prestamo.id_prestamo = idPrestamo();
        
        cout << "ID del libro: ";
        cin >> prestamo.id_libro;
        cout << "ID del estudiante: ";
        cin >> prestamo.id_estudiante;
        cin.ignore();
        cout << "Fecha de prestamo (Dia/Mes/Año): ";
        getline(cin, prestamo.fecha_prestamo);
        prestamo.fecha_devolucion = "";
        
        bool libro_existe = false;
        for (const auto& libro:libros) {
            if (libro.id_libro == prestamo.id_libro) {
                libro_existe = true;
                break;
            } else{
                cout<<"El libro no existe"<<endl;
                return;
            }
        }

        bool estudiante_existe = false;
        for (const auto& estudiante : estudiantes) {
            if (estudiante.id_estudiante == prestamo.id_estudiante) {
                estudiante_existe = true;
                break;
            } else {
                cout <<"El estudiante no existe"<<endl;
            }
        }
        
        for (const auto& p : prestamos) {
            if (p.id_libro == prestamo.id_libro && p.fecha_devolucion.empty()) {
                cout << "El libro ya esta prestado"<<endl;
                return;
            }
        }
        
        prestamos.push_back(prestamo);
        cout << "Prestamo registrado" <<endl;
    }
    
    void devolverLibro() {
        int id;
        cout << "ID del prestamo: ";
        cin >> id;
        
        for (auto& prestamo:prestamos) {
            if (prestamo.id_prestamo == id) {
                if (!prestamo.fecha_devolucion.empty()) {
                    cout << "Este libro ya fue devuelto"<<endl;
                    return;
                }
                cin.ignore();
                cout << "Fecha de devolucion (Dia/Mes/Año): ";
                getline(cin, prestamo.fecha_devolucion);
                cout << "Devolucion realizada"<<endl;
                return;
            }
        }
        cout << "Prestamo no encontrado"<<endl;
    }
    
    void listarPrestamos() {
        if (prestamos.empty()) {
            cout << "No hay prestamos\n";
            return;
        }
        
        cout << "Lista de prestamos";
        for (const auto& prestamo:prestamos) {
            string titulo = "Desconocido";
            string nombre = "Desconocido";
            
            for (const auto& libro:libros) {
                if (libro.id_libro == prestamo.id_libro) {
                    titulo = libro.titulo;
                    break;
                }
            }
            
            for (const auto& estudiante:estudiantes) {
                if (estudiante.id_estudiante == prestamo.id_estudiante) {
                    nombre = estudiante.nombre;
                    break;
                }
            }
            
            string estado = prestamo.fecha_devolucion.empty() ? "Activo" : prestamo.fecha_devolucion;
            cout << prestamo.id_prestamo << ", " << titulo << ", " << nombre << ", " << prestamo.fecha_prestamo << ", " << estado <<endl;
        }
    }

    void librosPorEstudiante() {
        int id;
        cout << "ID del estudiante: ";
        cin >> id;
        
        cout << "Libros prestados por el estudiante";
        bool encontrado = false;
        
        for (const auto& prestamo:prestamos) {
            if (prestamo.id_estudiante == id) {
                string titulo = "Desconocido";
                for (const auto& libro:libros) {
                    if (libro.id_libro == prestamo.id_libro) {
                        titulo = libro.titulo;
                        cout<<"- "<<titulo<<endl;
                        break;
                    }
                }
            } else {
                cout << "El estudiante no tiene prestamos"<<endl;
            }
        }
    }


};

void mostrarMenu() {
    cout << endl;
    cout << "--- BIBLIOTECA ---" << endl;
    cout << endl;
    cout << "AUTORES" << endl;
    cout << "1. Agregar autor" << endl;
    cout << "2. Listar autores" << endl;
    cout << "3. Actualizar autor" << endl;
    cout << "4. Eliminar autor" << endl;
    cout << endl;
    cout << "LIBROS" << endl;
    cout << "5. Agregar libro" << endl;
    cout << "6. Listar libros" << endl;
    cout << "7. Actualizar libro" << endl;
    cout << "8. Eliminar libro" << endl;
    cout << endl;
    cout << "ESTUDIANTES" << endl;
    cout << "9. Agregar estudiante" << endl;
    cout << "10. Listar estudiantes" << endl;
    cout << "11. Actualizar estudiante" << endl;
    cout << "12. Eliminar estudiante" << endl;
    cout << endl;
    cout << "PRESTAMOS" << endl;
    cout << "13. Registrar prestamo" << endl;
    cout << "14. Devolver libro" << endl;
    cout << "15. Listar prestamos" << endl;
    cout << endl;
    cout << "CONSULTAS" << endl;
    cout << "16. Libros por estudiante" << endl;
    cout << endl;
    cout << "17. Guardar datos" << endl;
    cout << "18. Salir" << endl;
    cout << endl;
    cout << "Opcion: ";
}

int main() {
    Biblioteca biblioteca;
    biblioteca.cargarDatos();
    
    int opcion;
    
    while (true) {
        mostrarMenu();
        cin >> opcion;
        
        switch (opcion) {
            case 1:
                biblioteca.agregarAutor();
                break;
            case 2:
                biblioteca.listarAutores();
                break;
            case 3:
                biblioteca.actualizarAutor();
                break;
            case 4:
                biblioteca.eliminarAutor();
                break;
            case 5:
                biblioteca.agregarLibro();
                break;
            case 6:
                biblioteca.listarLibros();
                break;
            case 7:
                biblioteca.actualizarLibro();
                break;
            case 8:
                biblioteca.eliminarLibro();
                break;
            case 9:
                biblioteca.agregarEstudiante();
                break;
            case 10:
                biblioteca.listarEstudiantes();
                break;
            case 11:
                biblioteca.actualizarEstudiante();
                break;
            case 12:
                biblioteca.eliminarEstudiante();
                break;
            case 13:
                biblioteca.registrarPrestamo();
                break;
            case 14:
                biblioteca.devolverLibro();
                break;
            case 15:
                biblioteca.listarPrestamos();
                break;
            case 16:
                biblioteca.librosPorEstudiante();
                break;
            case 17:
                biblioteca.guardarDatos();
                break;
            case 18:
                cout << "Guardar cambios? (s/n): ";
                char resp;
                cin >> resp;
                if (resp == 's' || resp == 'S') {
                    biblioteca.guardarDatos();
                }
                cout << "Adios" << endl;
                return 0;
            default:
                cout << "Opcion invalida" << endl;
        }
    }
    
    return 0;
}