#include "Ventana.h"
using namespace candy;

#include <vector>
#include <cstdlib>
using namespace std;

int main(int argc, char **argv) {
	Ventana v(400,400, "Consola");

	int num_rotar = 0;
	int num_trasladar = 0;
	int num_escalar = 0;
	int num_desconocidos = 0;

	bool mostrado = false;

	/*
	 * La aplicacion, lee de la consola comandos de la forma:
	 * rotar|escalar|trasladar valor
	 *
	 * Despues, una vez cerramos la consola, imprimimos ese valor actual para cada operacion.
	 * Si no tiene 2 componentes el vector del comando ya troceado, o si el formato no coincide,
	 * aumentamos la variable num_desconocidos.
	 */

	while(!v.isClosing()){
		v.Update();

		string segundo_param = "";
/*
		if(v.isConsoleActive()){ //Comprobamos que la consola este activa
			if(v.isCommandCompleted()){ //Comprobamos que el comando este completo
				vector<string> comando = v.getCommandSplitted(); //Cogemos el comando ya troceado

				if(comando.size() == 2){ //Comprobamos que el vector tenga dos componentes (siguiendo el formato de arriba)
					if(comando[0] == "rotar"){
						num_rotar = atoi(comando[1].c_str());
						segundo_param = comando[1];
					}else if(comando[0] == "trasladar"){
						num_trasladar = atoi(comando[1].c_str());
					}else if(comando[0] == "escalar"){
						num_escalar = atoi(comando[1].c_str());
					}else{
						num_desconocidos++;
					}
				}else{
					num_desconocidos++;
				}
			}

			mostrado = false;
		}else if(!mostrado){
			cout << "rotar: " << num_rotar << endl;
			cout << "trasladar: " << num_trasladar << endl;
			cout << "escalar: " << num_escalar << endl;
			cout << "desconocidos: " << num_desconocidos << endl;

			cout << "ROTAR: " << segundo_param << endl;

			mostrado = true;
		}
		*/

		v.Display();
	}
}
