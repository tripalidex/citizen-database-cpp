#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <functional>
#include <chrono>

using namespace std;

struct Registro {
    string dni;
    string nombres;
    string apellidos;
    string lugarNacimiento;
    string direccion;
    string telefono;
    string email;
    string estadoCivil;
};

class CuckooHash {
private:
    vector<Registro> tabla1, tabla2, tabla3, tabla4, tabla5, tabla6, tabla7, tabla8;
    vector<bool> ocupado1, ocupado2, ocupado3, ocupado4, ocupado5, ocupado6, ocupado7, ocupado8;
    int tamano;

    int hash1(const string& key) { 
        return std::hash<string>{}(key) % tamano; 
    }
    int hash2(const string& key) { return (std::hash<string>{}(key) ^ 0x5bf03635) % tamano; }
    int hash3(const string& key) { return (std::hash<string>{}(key) ^ 0x1e35a7bd) % tamano; }
    int hash4(const string& key) { return (std::hash<string>{}(key) ^ 0x3f12b6e3) % tamano; }
    int hash5(const string& key) { return (std::hash<string>{}(key) ^ 0x7c1d9f5b) % tamano; }
    int hash6(const string& key) { return (std::hash<string>{}(key) ^ 0x9d2e6a47) % tamano; }
    int hash7(const string& key) { return (std::hash<string>{}(key) ^ 0xed19c3a9) % tamano; }
    int hash8(const string& key) { return (std::hash<string>{}(key) ^ 0xa1b2c3d4) % tamano; }


    void rehash() {
        cout << "Rehashing..." << endl;
        tamano *= 3;
        vector<Registro> oldTabla1 = move(tabla1);
        vector<Registro> oldTabla2 = move(tabla2);
        vector<Registro> oldTabla3 = move(tabla3);
        vector<Registro> oldTabla4 = move(tabla4);
        vector<Registro> oldTabla5 = move(tabla5);
        vector<Registro> oldTabla6 = move(tabla6);
        vector<Registro> oldTabla7 = move(tabla7);
        vector<Registro> oldTabla8 = move(tabla8);

        vector<bool> oldOcupado1 = move(ocupado1);
        vector<bool> oldOcupado2 = move(ocupado2);
        vector<bool> oldOcupado3 = move(ocupado3);
        vector<bool> oldOcupado4 = move(ocupado4);
        vector<bool> oldOcupado5 = move(ocupado5);
        vector<bool> oldOcupado6 = move(ocupado6);
        vector<bool> oldOcupado7 = move(ocupado7);
        vector<bool> oldOcupado8 = move(ocupado8);

        tabla1.resize(tamano, Registro{});
        tabla2.resize(tamano, Registro{});
        tabla3.resize(tamano, Registro{});
        tabla4.resize(tamano, Registro{});
        tabla5.resize(tamano, Registro{});
        tabla6.resize(tamano, Registro{});
        tabla7.resize(tamano, Registro{});
        tabla8.resize(tamano, Registro{});
        ocupado1.assign(tamano, false);
        ocupado2.assign(tamano, false);
        ocupado3.assign(tamano, false);
        ocupado4.assign(tamano, false);
        ocupado5.assign(tamano, false);
        ocupado6.assign(tamano, false);
        ocupado7.assign(tamano, false);
        ocupado8.assign(tamano, false);

        for (size_t i = 0; i < oldTabla1.size(); i++) if (oldOcupado1[i]) insertar(oldTabla1[i]);
        for (size_t i = 0; i < oldTabla2.size(); i++) if (oldOcupado2[i]) insertar(oldTabla2[i]);
        for (size_t i = 0; i < oldTabla3.size(); i++) if (oldOcupado3[i]) insertar(oldTabla3[i]);
        for (size_t i = 0; i < oldTabla4.size(); i++) if (oldOcupado4[i]) insertar(oldTabla4[i]);
        for (size_t i = 0; i < oldTabla5.size(); i++) if (oldOcupado5[i]) insertar(oldTabla5[i]);
        for (size_t i = 0; i < oldTabla6.size(); i++) if (oldOcupado6[i]) insertar(oldTabla6[i]);
        for (size_t i = 0; i < oldTabla7.size(); i++) if (oldOcupado7[i]) insertar(oldTabla7[i]);
        for (size_t i = 0; i < oldTabla8.size(); i++) if (oldOcupado8[i]) insertar(oldTabla8[i]);
    }

public:
    CuckooHash(int size) : tamano(size) {
        tabla1.resize(tamano);
        tabla2.resize(tamano);
        tabla3.resize(tamano);
        tabla4.resize(tamano);
        tabla5.resize(tamano);
        tabla6.resize(tamano);
        tabla7.resize(tamano);
        tabla8.resize(tamano);
        ocupado1.resize(tamano, false);
        ocupado2.resize(tamano, false);
        ocupado3.resize(tamano, false);
        ocupado4.resize(tamano, false);
        ocupado5.resize(tamano, false);
        ocupado6.resize(tamano, false);
        ocupado7.resize(tamano, false);
        ocupado8.resize(tamano, false);
    }

    bool insertar(const Registro& registro) {
        const int MAX_INTENTOS = 7 * tamano;
        Registro actual = registro;

        for (int intento = 0; intento < MAX_INTENTOS; intento++) {
            int idx1 = hash1(actual.dni);
            if (!ocupado1[idx1]) { tabla1[idx1] = actual; ocupado1[idx1] = true; return true; }

            swap(actual, tabla1[idx1]);
            int idx2 = hash2(actual.dni);
            if (!ocupado2[idx2]) { tabla2[idx2] = actual; ocupado2[idx2] = true; return true; }

            swap(actual, tabla2[idx2]);
            int idx3 = hash3(actual.dni);
            if (!ocupado3[idx3]) { tabla3[idx3] = actual; ocupado3[idx3] = true; return true; }

            swap(actual, tabla3[idx3]);
            int idx4 = hash4(actual.dni);
            if (!ocupado4[idx4]) { tabla4[idx4] = actual; ocupado4[idx4] = true; return true; }

            swap(actual, tabla4[idx4]);
            int idx5 = hash5(actual.dni);
            if (!ocupado5[idx5]) { tabla5[idx5] = actual; ocupado5[idx5] = true; return true; }

            swap(actual, tabla5[idx5]);
            int idx6 = hash6(actual.dni);
            if (!ocupado6[idx6]) { tabla6[idx6] = actual; ocupado6[idx6] = true; return true; }

            swap(actual, tabla6[idx6]);
            int idx7 = hash7(actual.dni);
            if (!ocupado7[idx7]) { tabla7[idx7] = actual; ocupado7[idx7] = true; return true; }

            swap(actual, tabla7[idx7]);

            int idx8 = hash8(actual.dni);
            if (!ocupado8[idx8]) { tabla8[idx8] = actual; ocupado8[idx8] = true; return true; }

            swap(actual, tabla8[idx8]);
        }

        rehash();
        return insertar(registro);
    }

    Registro buscar(const string& dni) {
        int idx1 = hash1(dni); if (ocupado1[idx1] && tabla1[idx1].dni == dni) return tabla1[idx1];
        int idx2 = hash2(dni); if (ocupado2[idx2] && tabla2[idx2].dni == dni) return tabla2[idx2];
        int idx3 = hash3(dni); if (ocupado3[idx3] && tabla3[idx3].dni == dni) return tabla3[idx3];
        int idx4 = hash4(dni); if (ocupado4[idx4] && tabla4[idx4].dni == dni) return tabla4[idx4];
        int idx5 = hash5(dni); if (ocupado5[idx5] && tabla5[idx5].dni == dni) return tabla5[idx5];
        int idx6 = hash6(dni); if (ocupado6[idx6] && tabla6[idx6].dni == dni) return tabla6[idx6];
        int idx7 = hash7(dni); if (ocupado7[idx7] && tabla7[idx7].dni == dni) return tabla7[idx7];
        int idx8 = hash8(dni); if (ocupado8[idx8] && tabla8[idx8].dni == dni) return tabla8[idx8];
        return {};
    }

    bool eliminar(const string& dni) {
        int idx1 = hash1(dni); if (ocupado1[idx1] && tabla1[idx1].dni == dni) { ocupado1[idx1] = false; return true; }
        int idx2 = hash2(dni); if (ocupado2[idx2] && tabla2[idx2].dni == dni) { ocupado2[idx2] = false; return true; }
        int idx3 = hash3(dni); if (ocupado3[idx3] && tabla3[idx3].dni == dni) { ocupado3[idx3] = false; return true; }
        int idx4 = hash4(dni); if (ocupado4[idx4] && tabla4[idx4].dni == dni) { ocupado4[idx4] = false; return true; }
        int idx5 = hash5(dni); if (ocupado5[idx5] && tabla5[idx5].dni == dni) { ocupado5[idx5] = false; return true; }
        int idx6 = hash6(dni); if (ocupado6[idx6] && tabla6[idx6].dni == dni) { ocupado6[idx6] = false; return true; }
        int idx7 = hash7(dni); if (ocupado7[idx7] && tabla7[idx7].dni == dni) { ocupado7[idx7] = false; return true; }
        int idx8 = hash8(dni); if (ocupado8[idx8] && tabla8[idx8].dni == dni) { ocupado8[idx8] = false; return true; }
        return false;
    }
};

void mostrarRegistro(const Registro& registro) {
    if (!registro.dni.empty()) {
        cout << "------------------------------" << endl;
        cout << "DNI: " << registro.dni << endl;
        cout << "Nombres: " << registro.nombres << endl;
        cout << "Apellidos: " << registro.apellidos << endl;
        cout << "Lugar de nacimiento: " << registro.lugarNacimiento << endl;
        cout << "Direccion: " << registro.direccion << endl;
        cout << "Telefono: " << registro.telefono << endl;
        cout << "Correo electronico: " << registro.email << endl;
        cout << "Estado Civil: " << registro.estadoCivil << endl;
        cout << "------------------------------" << endl;
    } else {
        cout << "Registro no encontrado.\n";
    }
}

bool cargarDesdeCSV(const string& filename, CuckooHash& tabla, int limite = 33000000) {
    ifstream archivo(filename);
    if (!archivo.is_open()) {
        cerr << "Error al abrir el archivo CSV." << endl;
        return false;
    }

    string linea;
    getline(archivo, linea); // Saltar la cabecera

    int contador = 0;
    // Opcional: reservar espacio si conoces el tama�o aproximado
    // tabla.reserveSpace(limite);  // Si implementas este metodo

    while (getline(archivo, linea) && contador < limite) {
        // Considera usar stringstream solo si es necesario
        // Para CSV simples, podr�as usar find y substr para partir
        stringstream ss(linea);
        Registro registro;

        // Metodo mas rapido de parsing
        getline(ss, registro.dni, ',');
        getline(ss, registro.nombres, ',');
        getline(ss, registro.apellidos, ',');
        getline(ss, registro.lugarNacimiento, ',');
        getline(ss, registro.direccion, ',');
        getline(ss, registro.telefono, ',');
        getline(ss, registro.email, ',');
        getline(ss, registro.estadoCivil, ',');

        tabla.insertar(registro);
        contador++;

        if (contador % 100000 == 0) { // Actualizaci�n menos frecuente
            cout << "Leyendo " << contador << " registros...\n";
        }
    }

    archivo.close();
    cout << "Total de registros leidos: " << contador << endl;
    return true;
}


int main() {
    CuckooHash tabla(7000000);

    string filename = "personas.csv";

    auto inicioCarga = chrono::steady_clock::now();
    if (!cargarDesdeCSV(filename, tabla, 33000000)) { //cambiar cant de datos a leer
        cerr << "Fallo al cargar los registros desde el archivo CSV." << endl;
        return 1;
    }
    auto finCarga = chrono::steady_clock::now();
    auto duracionCarga = chrono::duration_cast<chrono::seconds>(finCarga - inicioCarga).count();
    cout << "Registros cargados desde el archivo CSV correctamente en " << duracionCarga << " segundos.\n";

    int opcion;
    do {
        cout << "Menu:\n";
        cout << "1. Buscar registro\n";
        cout << "2. Insertar nuevo registro\n";
        cout << "3. Eliminar registro\n";
        cout << "4. Salir\n";
        cout << "Seleccione una opcion: ";
        cin >> opcion;
        cout << "------------------------------\n";

        if (opcion == 1) {
            string dni;
            cout << "Ingrese DNI: ";
            cin >> dni;

            auto inicioBusqueda = chrono::steady_clock::now();
            Registro reg = tabla.buscar(dni);
            auto finBusqueda = chrono::steady_clock::now();
            auto duracionBusqueda = chrono::duration_cast<chrono::microseconds>(finBusqueda - inicioBusqueda).count();
            cout << "Busqueda realizada en " << duracionBusqueda << " microsegundos.\n";

            mostrarRegistro(reg);

        } else if (opcion == 2) {
            Registro registro;
            cout << "Ingrese DNI: ";
            cin >> registro.dni;
            cout << "Ingrese nombres: ";
            cin >> registro.nombres;
            cout << "Ingrese apellidos: ";
            cin >> registro.apellidos;
            cout << "Ingrese lugar de nacimiento: ";
            cin >> registro.lugarNacimiento;
            cout << "Ingrese direccion: ";
            cin >> registro.direccion;
            cout << "Ingrese telefono: ";
            cin >> registro.telefono;
            cout << "Ingrese email: ";
            cin >> registro.email;
            cout << "Ingrese estado civil: ";
            cin >> registro.estadoCivil;

            auto inicioInsercion = chrono::steady_clock::now();
            tabla.insertar(registro);
            auto finInsercion = chrono::steady_clock::now();
            auto duracionInsercion = chrono::duration_cast<chrono::microseconds>(finInsercion - inicioInsercion).count();
            cout << "Registro insertado en " << duracionInsercion << " microsegundos.\n";

        } else if (opcion == 3) {
            string dni;
            cout << "Ingrese DNI para eliminar: ";
            cin >> dni;

            auto inicioEliminacion = chrono::steady_clock::now();
            if (tabla.eliminar(dni)) {
                cout << "Registro eliminado correctamente.\n";
            } else {
                cout << "Registro no encontrado.\n";
            }
            auto finEliminacion = chrono::steady_clock::now();
            auto duracionEliminacion = chrono::duration_cast<chrono::microseconds>(finEliminacion - inicioEliminacion).count();
            cout << "Eliminacion realizada en " << duracionEliminacion << " microsegundos.\n";

        } else if (opcion == 4) {
            cout << "Saliendo del programa.\n";
        } else {
            cout << "Opcion no valida. Intente de nuevo.\n";
        }
        cout << "------------------------------\n";
    } while (opcion != 4);

    return 0;
}
