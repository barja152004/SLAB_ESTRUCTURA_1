#include <iostream>
#include <queue>
#include <stack>
#include <list>
#include <string>
#include <vector>

using namespace std;

// Estructura para el historial médico de las mascotas
struct HistorialMedico {
    string resumenVisita;
    string fechaHoraLlegada;
    string diagnostico;
    string tratamiento;
    float costo;
    bool pagado;
};

// Estructura para las mascotas
struct Mascota {
    string nombreMascota;
    string tipoAnimal;
    int edad;
    string nombreDueno;
    string contactoDueno;
    vector<HistorialMedico> historial; // Historial médico como lista de registros
};

// Estructura para los clientes
struct Cliente {
    string nombreDueno;
    string contactoDueno;
    string horaLlegada;
    list<Mascota> listaMascotas;
    float costoTotal;
    bool pagado;
};

// Cola para manejo de clientes
queue<Cliente> colaClientes;

// Pila para historial de clientes atendidos
stack<Cliente> pilaHistorial;

// Funciones para gestionar la Cola                                    COLA
void agregarClienteACola(Cliente cliente) {
    colaClientes.push(cliente);
    cout << "Cliente añadido a la cola.\n";
}

//funcion para atender al cliente
void atenderCliente() {
    if (!colaClientes.empty()) {
        Cliente clienteEnTurno = colaClientes.front();
        colaClientes.pop();
        pilaHistorial.push(clienteEnTurno);
        cout << "Cliente atendido: " << clienteEnTurno.nombreDueno << "\n";
    }
    else {
        cout << "No hay clientes en la cola.\n";
    }
}

//funcion para consultar el siguiente cliente
void consultarSiguienteCliente() {
    if (!colaClientes.empty()) {
        Cliente clienteEnTurno = colaClientes.front();
        cout << "Siguiente cliente en ser atendido: " << clienteEnTurno.nombreDueno << "\n";
    }
    else {
        cout << "No hay clientes en la cola.\n";
    }
}

// Funciones para gestionar la Pila
void consultarUltimoClienteAtendido() {
    if (!pilaHistorial.empty()) {
        Cliente ultimoCliente = pilaHistorial.top();
        cout << "Ultimo cliente atendido: " << ultimoCliente.nombreDueno << "\n";
    }
    else {
        cout << "No hay historial de clientes atendidos.\n";
    }
}

// Función para deshacer la última atención
void deshacerUltimaAtencion() {
    if (!pilaHistorial.empty()) {
        Cliente clienteDeshacer = pilaHistorial.top();
        pilaHistorial.pop();
        colaClientes.push(clienteDeshacer);
        cout << "Se ha deshecho la ultima atencion y el cliente ha vuelto a la cola: " << clienteDeshacer.nombreDueno << "\n";
    }
    else {
        cout << "No hay atencion que deshacer.\n";
    }
}

// Función para agregar un registro al historial médico                  PILA
void agregarRegistroHistorial(Mascota& mascota) {
    HistorialMedico registro;
    cout << "Ingrese un resumen de la visita: ";
    cin.ignore();
    getline(cin, registro.resumenVisita);
    cout << "Ingrese la fecha y hora de llegada (dd/mm/aaaa hh:mm): ";
    getline(cin, registro.fechaHoraLlegada);
    cout << "Ingrese el diagnostico: ";
    getline(cin, registro.diagnostico);
    cout << "Ingrese el tratamiento: ";
    getline(cin, registro.tratamiento);
    cout << "Ingrese el costo: ";
    cin >> registro.costo;
    cout << "¿Esta pagado? (1 para Si, 0 para No): ";
    cin >> registro.pagado;

    mascota.historial.push_back(registro);
    cout << "Registro añadido al historial medico de la mascota.\n";
}

// Función para mostrar el historial médico de una mascota
void mostrarHistorialMedico(const Mascota& mascota) {
    if (mascota.historial.empty()) {
        cout << "El historial medico de esta mascota esta vacio.\n";
        return;
    }

    cout << "Historial medico de la mascota " << mascota.nombreMascota << ":\n";
    for (const auto& registro : mascota.historial) {
        cout << "------------------------------------------\n";
        cout << "Resumen de la visita: " << registro.resumenVisita << "\n";
        cout << "Fecha y hora de llegada: " << registro.fechaHoraLlegada << "\n";
        cout << "Diagnostico: " << registro.diagnostico << "\n";
        cout << "Tratamiento: " << registro.tratamiento << "\n";
        cout << "Costo: " << registro.costo << "\n";
        cout << "Pagado: " << (registro.pagado ? "Sí" : "No") << "\n";
    }
}

// Funciones para gestionar la Lista de mascotas                                    LISTA
void agregarMascotaALista(list<Mascota>& listaMascotas, Mascota mascota) {
    listaMascotas.push_back(mascota);
    cout << "Mascota anadida.\n";
}

//funcion para buscar una mascota por su nombre
void buscarMascota(list<Mascota>& listaMascotas, string nombreMascota) {
    for (auto& mascota : listaMascotas) {
        if (mascota.nombreMascota == nombreMascota) {
            cout << "Informacion de la mascota:\n"
                << "Nombre: " << mascota.nombreMascota << "\n"
                << "Tipo: " << mascota.tipoAnimal << "\n"
                << "Edad: " << mascota.edad << "\n"
                << "Dueno: " << mascota.nombreDueno << "\n"
                << "Contacto: " << mascota.contactoDueno << "\n";
            mostrarHistorialMedico(mascota);
            return;
        }
    }
    cout << "Mascota no encontrada.\n";
}

//funcion para actualizar los datos de una mascota
void actualizarDatosMascota(list<Mascota>& listaMascotas, const string& nombreMascota) {
    for (auto& mascota : listaMascotas) {
        if (mascota.nombreMascota == nombreMascota) {
            cout << "Mascota encontrada. Actualice los datos:\n";

            cout << "Ingrese el nuevo nombre de la mascota (actual: " << mascota.nombreMascota << "): ";
            cin.ignore();
            getline(cin, mascota.nombreMascota);

            cout << "Ingrese el nuevo tipo de animal (actual: " << mascota.tipoAnimal << "): ";
            getline(cin, mascota.tipoAnimal);

            cout << "Ingrese la nueva edad de la mascota (actual: " << mascota.edad << "): ";
            cin >> mascota.edad;
            cin.ignore();

            cout << "Ingrese el nuevo nombre del dueño (actual: " << mascota.nombreDueno << "): ";
            getline(cin, mascota.nombreDueno);

            cout << "Ingrese el nuevo contacto del dueno (actual: " << mascota.contactoDueno << "): ";
            getline(cin, mascota.contactoDueno);

            // Actualizar el estado de pago
            char opcionPago;
            cout << "¿Desea actualizar el estado de pago de los registros medicos? (S/N): ";
            cin >> opcionPago;

            if (toupper(opcionPago) == 'S') {
                for (auto& registro : mascota.historial) {
                    cout << "Registro actual:\n";
                    cout << "Resumen de la visita: " << registro.resumenVisita << "\n";
                    cout << "Pagado: " << (registro.pagado ? "Sí" : "No") << "\n";
                    cout << "¿Actualizar a pagado? (1 para Si, 0 para No): ";
                    cin >> registro.pagado;
                }
                cout << "Estado de pago actualizado en los registros medicos.\n";
            }

            cout << "Datos de la mascota actualizados correctamente.\n";
            return;
        }
    }
    cout << "Mascota no encontrada.\n";
}


//funcion para eliminar una mascota
void eliminarMascotaDeLista(list<Mascota>& listaMascotas, const string& nombreMascota) {
    for (auto it = listaMascotas.begin(); it != listaMascotas.end(); ++it) {
        if (it->nombreMascota == nombreMascota) {
            cout << "Mascota encontrada: " << it->nombreMascota << ". Eliminando...\n";
            listaMascotas.erase(it);
            cout << "Mascota eliminada correctamente.\n";
            return;
        }
    }
    cout << "Mascota no encontrada.\n";
}


// Menú de opciones 
int main() {
    int opc;
    Cliente cliente;
    Mascota mascota;

    do {
        system("cls");
        cout << "      MENU DE OPCIONES PARA LA VETERINARIA\n";
        cout << "--------------------------------------------\n";
        cout << "1. Insertar un nuevo cliente en la cola\n";
        cout << "2. Atender al cliente en turno\n";
        cout << "3. Mostrar el siguiente cliente en ser atendido\n";
        cout << "4. Consultar el historial de clientes atendidos\n";
        cout << "5. Consultar el ultimo cliente atendido\n";
        cout << "6. Deshacer la ultima atencion\n";
        cout << "7. Agregar una nueva mascota a un cliente\n";
        cout << "8. Agregar un registro al historial medico de una mascota\n";
        cout << "9. Buscar una mascota por su nombre\n";
		cout << "10. Actualizar los datos de una mascota\n";
		cout << "11. Eliminar una mascota de la lista\n";   
        cout << "12. Salir\n";
        cout << "--------------------------------------------\n";
        cout << "Ingrese una opcion: ";
        cin >> opc;

        switch (opc) {
        case 1:
            cout << "Ingrese el nombre del dueno: ";
            cin >> cliente.nombreDueno;
            cout << "Ingrese el contacto del dueno: ";
            cin >> cliente.contactoDueno;
            cout << "Ingrese la hora de llegada: ";
            cin >> cliente.horaLlegada;
            agregarClienteACola(cliente);
            break;

        case 2:
            atenderCliente();
            break;

        case 3:
            consultarSiguienteCliente();
            break;

        case 4:
            cout << "Clientes en el historial: " << pilaHistorial.size() << endl;
            break;

        case 5:
            consultarUltimoClienteAtendido();
            break;

        case 6:
            deshacerUltimaAtencion();
            break;

        case 7:
            cout << "Ingrese el nombre de la mascota: ";
            cin >> mascota.nombreMascota;
            cout << "Ingrese el tipo de animal: ";
            cin >> mascota.tipoAnimal;
            cout << "Ingrese la edad de la mascota: ";
            cin >> mascota.edad;
            cout << "Ingrese el nombre del dueno: ";
            cin >> mascota.nombreDueno;
            cout << "Ingrese el contacto del dueno: ";
            cin >> mascota.contactoDueno;
            agregarMascotaALista(cliente.listaMascotas, mascota);
            break;

        case 8:
            cout << "Ingrese el nombre de la mascota: ";
            cin >> mascota.nombreMascota;
            for (auto& m : cliente.listaMascotas) {
                if (m.nombreMascota == mascota.nombreMascota) {
                    agregarRegistroHistorial(m);
                    break;
                }
            }
            break;

        case 9:
            cout << "Ingrese el nombre de la mascota: ";
            cin >> mascota.nombreMascota;
            buscarMascota(cliente.listaMascotas, mascota.nombreMascota);
            break;

        case 10:
            cout << "Ingrese el nombre de la mascota a actualizar: ";
            cin >> mascota.nombreMascota;
            actualizarDatosMascota(cliente.listaMascotas, mascota.nombreMascota);
            break;

        case 11:
            cout << "Ingrese el nombre de la mascota a eliminar: ";
            cin >> mascota.nombreMascota;
            eliminarMascotaDeLista(cliente.listaMascotas, mascota.nombreMascota);
            break;

        case 12:
            cout << "Saliendo del programa...\n";
            break;

        default:
            cout << "Opción no valida. Intente de nuevo.\n";
        }

        if (opc != 12) {
            cout << "Presione una tecla para continuar...";
            cin.ignore();
            getchar();
        }
    } while (opc != 12);

    return 0;
}