#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <cstdlib>
#include <random>
#include <ctime>
#include <algorithm>
#include <chrono>
#include <sstream>

using namespace std;

struct Persona {
    string dni;
    string nombres;
    string apellidos;
    string lugarNacimiento;
    string direccion;
    string telefono;
    string email;
    string estadoCivil;
};

struct Departamento {
    int id;
    string nombre;
};

struct Provincia {
    int id;
    string nombre;
    int departamento_id;
};

struct Distrito {
    int id;
    string nombre;
    int provincia_id;
    int departamento_id;
};

vector<Departamento> leerDepartamentos(const string& nombreArchivo) {
    vector<Departamento> departamentos;
    ifstream archivo(nombreArchivo);
    string linea, campo;

    if (archivo.is_open()) {
        getline(archivo, linea);  // Leer encabezado
        while (getline(archivo, linea)) {
            stringstream s(linea);
            Departamento departamento;
            getline(s, campo, ',');
            departamento.id = stoi(campo);
            getline(s, campo, ',');
            departamento.nombre = campo;
            departamentos.push_back(departamento);
        }
        archivo.close();
    } else {
        cerr << "No se pudo abrir el archivo de departamentos\n";
    }
    return departamentos;
}

vector<Provincia> leerProvincias(const string& nombreArchivo) {
    vector<Provincia> provincias;
    ifstream archivo(nombreArchivo);
    string linea, campo;

    if (archivo.is_open()) {
        getline(archivo, linea);  // Leer encabezado
        while (getline(archivo, linea)) {
            stringstream s(linea);
            Provincia provincia;
            getline(s, campo, ',');
            provincia.id = stoi(campo);
            getline(s, campo, ',');
            provincia.nombre = campo;
            getline(s, campo, ',');
            provincia.departamento_id = stoi(campo);
            provincias.push_back(provincia);
        }
        archivo.close();
    } else {
        cerr << "No se pudo abrir el archivo de provincias\n";
    }
    return provincias;
}

vector<Distrito> leerDistritos(const string& nombreArchivo) {
    vector<Distrito> distritos;
    ifstream archivo(nombreArchivo);
    string linea, campo;

    if (archivo.is_open()) {
        getline(archivo, linea);  // Leer encabezado
        while (getline(archivo, linea)) {
            stringstream s(linea);
            Distrito distrito;
            getline(s, campo, ',');
            distrito.id = stoi(campo);
            getline(s, campo, ',');
            distrito.nombre = campo;
            getline(s, campo, ',');
            distrito.provincia_id = stoi(campo);
            getline(s, campo, ',');
            distrito.departamento_id = stoi(campo);
            distritos.push_back(distrito);
        }
        archivo.close();
    } else {
        cerr << "No se pudo abrir el archivo de distritos\n";
    }
    return distritos;
}

vector<string> generarDNIsUnicos(int cantidad) {
    vector<string> dnis;
    
    for (int i = 10000000; i <= 99999999 && dnis.size() < cantidad; ++i) {
        dnis.push_back(to_string(i));
    }

    // Mezclar el vector para hacer que los DNIs sean aleatorios
    random_device rd;
    mt19937 g(rd());
    shuffle(dnis.begin(), dnis.end(), g);

    return dnis;
}

string generarNombre() {
    string nombres[] = {"Juan", "Maria", "Pedro", "Luis", "Ana", "Carmen", "Jose", "Carlos", "Rosa", "Lucia"};
    return nombres[rand() % 10];
}

string generarApellido() {
    string apellidos[] = {"Perez", "Gonzalez", "Rodriguez", "Lopez", "Garcia", "Martinez", "Fernandez", "Torres", "Rivera", "Sanchez"};
    return apellidos[rand() % 10];
}

string generarLugarNacimiento() {
    string lugares[] = {
        "Amazonas", "Ancash", "Apurimac", "Arequipa", "Ayacucho", "Cajamarca", "Callao", "Cusco",
        "Huancavelica", "Huanuco", "Ica", "Junin", "La Libertad", "Lambayeque", "Lima", "Loreto",
        "Madre de Dios", "Moquegua", "Pasco", "Piura", "Puno", "San Martin", "Tacna", "Tumbes", "Ucayali"};
    return lugares[rand() % 25];
}

vector<string> generarUbigeosAleatorios(const vector<Distrito>& distritos, int cantidad) {
    vector<string> ubigeos;

    for (int i = 0; i < cantidad; ++i) {
        const Distrito& distrito = distritos[rand() % distritos.size()];
        string ubigeo = to_string(distrito.id) + to_string(distrito.provincia_id) + to_string(distrito.departamento_id);
        ubigeos.push_back(ubigeo);
    }

    return ubigeos;
}

string generarTelefono() {
    string telefono = "9";
    for (int i = 0; i < 8; ++i)
        telefono += '0' + rand() % 10;
    return telefono;
}

string generarEmail(const string& nombres, const string& apellidos) {
    string email = nombres + apellidos + "@hotmail.com";
    transform(email.begin(), email.end(), email.begin(), ::tolower);
    return email;
}

string generarEstadoCivil() {
    return (rand() % 2 == 0) ? "Soltero" : "Casado";
}

void generarPersonasCSV(int cantidadPersonas, const vector<Distrito>& distritos) {
    ofstream archivo("personas.csv");
    archivo << "DNI,Nombres,Apellidos,LugarNacimiento,Direccion,Telefono,Email,EstadoCivil\n";

    vector<string> dnis = generarDNIsUnicos(cantidadPersonas);
    vector<string> ubigeos = generarUbigeosAleatorios(distritos, cantidadPersonas);

    for (int i = 0; i < cantidadPersonas; ++i) {
        Persona persona;
        persona.dni = dnis[i];
        persona.nombres = generarNombre();
        persona.apellidos = generarApellido();
        persona.lugarNacimiento = generarLugarNacimiento();
        persona.direccion = ubigeos[i];
        persona.telefono = generarTelefono();
        persona.email = generarEmail(persona.nombres, persona.apellidos);
        persona.estadoCivil = generarEstadoCivil();

        archivo << persona.dni << "," << persona.nombres << "," << persona.apellidos << ","
                << persona.lugarNacimiento << "," << persona.direccion << ","
                << persona.telefono << "," << persona.email << "," << persona.estadoCivil << "\n";

        if ((i + 1) % 1000000 == 0) {
            cout << "Progreso: " << (i + 1) << " de " << cantidadPersonas << " personas generadas." << endl;
        }
    }

    archivo.close();
    cout << "Generación de personas completada y guardada en 'personas.csv'." << endl;
}

int main() {
    srand(static_cast<unsigned>(time(0)));

    vector<Departamento> departamentos = leerDepartamentos("departamentos.csv");
    vector<Provincia> provincias = leerProvincias("provincias.csv");
    vector<Distrito> distritos = leerDistritos("distritos.csv");

    // Verificar que los vectores no estén vacíos
    if (departamentos.empty() || provincias.empty() || distritos.empty()) {
        cerr << "Error: uno o más archivos CSV no cargaron correctamente." << endl;
        return 1;
    }
    auto inicio = chrono::steady_clock::now();
    
    int cantidadPersonas = 33000000; // Cambiado a un número pequeño para prueba
    generarPersonasCSV(cantidadPersonas, distritos);
    
    auto fin = chrono::steady_clock::now();
    auto duracion = chrono::duration_cast<chrono::seconds>(fin - inicio).count(); cout << "La generación de personas tomó " << duracion << " segundos." << endl;
    return 0;
}