/*
 * EntityManager.h
 *
 *  Created on: Nov 9, 2011
 *      Author: carrillo
 */

#ifndef ENTITYMANAGER_H_
#define ENTITYMANAGER_H_

#include <iostream>
#include <map>
#include <list>
using namespace std;

#include "GameEntity.h"
#include "GEDynamic.h"
#include "GEStatic.h"
#include "Player.h"
#include "Enemy.h"
#include "Obstaculo.h"
#include "Objetos.h"
#include "IPathfinding.h"

namespace candy {
/**
 * \addtogroup CandyEngine
 * @{
 */

	/**
	 * @class EntityManager
	 * @brief Gestor de entidades
	 * Representa a un "contenedor" de entidades. En el guardaremos el estado del juego (el estado de todas
	 * las entidades del juego). Lo almacenamos mediante un map de la STL indexado por el tipo de entidad.
	 * Los tipos de entidades disponibles son los que hay en el enum Tipo. En cada posicion del map tendremos una
	 * lista de la STL, ordenado por ID.
	 *
	 * Es decir, cada identidad la identificaremos con un Tipo y un ID dentro de ese tipo.
	 */
	class EntityManager {
	public:


		/**
		 * @brief Constructor
		 *  Para crearla es necesario pasarle los parametros del player (tipo 0, id 0).
		 *
		 */
		EntityManager();

		/**
		 * Constructor de copia
		 * @param em Origen de la copia
		 */
		EntityManager(const EntityManager& em);

		/**
		 * Operador asignación.
		 * @param em Origen de la asignación.
		 * @return Referencia al resultado de la asignación
		 */
		EntityManager& operator=(const EntityManager& em);


		/**
		 * Destructor por defecto
		 */
		~EntityManager();

		/**
		 * Anyade una nueva entidad al map.
		 * @param tipo Debe ser uno de los tipos del Enum.
		 * @param id ID de la entidad (dentro de ese tipo)
		 * @param posicion Posicion de la entidad
		 */
		//GameEntity* addEntity(GameEntity::Tipo tipo, int id, Vector3 posicion);

		/**
		 * Anyade una entidad ya creada a partir de un puntero
		 * @param entidad Puntero a entidad
		 */
		GameEntity* addEntity(GameEntity* entidad);

		/**
		 *	Anyade un player a la escena
		 * @param posicion Posicion del player
		 * @return Puntero al player anyadido
		 */
		Player* addPlayer(Vector3 posicion);

		/**
		 * Anyade un enemigo en una posicion y con un determinado tipo
		 * @param posicion Posicion del enemigo
		 * @param tipo_enem Tipo del enemigo
		 * @return Puntero al Enemy recien creado
		 */
		Enemy* addEnemy(Vector3 posicion, Enemy::TipoEnemigo tipo_enem);

		/**
		 * Anyade un obstaculo en una determinada posicion
		 * @param posicion Posicion del obstaculo
		 * @return Puntero a GEStatic
		 */
		Obstaculo* addObstacle(Vector3 posicion, Obstaculo::TipoObstaculo tipo_sta);

		Objetos* addObjeto(Vector3 posicion, Objetos::TiposObjetos tipo_objeto);

		/**
		 * Getter de la entidad.
		 * @param tipo Tipo de entidad.
		 * @param id ID de la entidad.
		 * @return Puntero a la entidad si existe, y NULL sino.
		 */
		GameEntity* getEntity(GameEntity::TipoEntidad tipo, int id);

		/**
		 * Busca en la lista una entidad dinamica
		 * @param id ID que buscamos
		 * @return Puntero a la entidad o NULL
		 */
		GEDynamic* getEnemy(int id);

		/**
		 * Busca en la lista una entidad statica
		 * @param id ID que buscamos
		 * @return Puntero a la entidad o NULL
		 */
		GEStatic* getStatic(int id);

		/**
		 * Getter del player
		 * @return Devuelve un puntero al player (no podra nunca ser NULL)
		 */
		Player* getPlayer();

		/**
		 * Borra una entidad de un cierto Tipo e ID.
		 * @param tipo Tipo de la entidad
		 * @param id ID de la entidad
		 */
		void deleteEntity(GameEntity::TipoEntidad tipo, int id);

		/**
		 * Borrar todas las entidades de un determinado tipo.
		 * @param tipo Tipo que queremos borrar.
		 */
		void deleteType(GameEntity::TipoEntidad tipo);

		/**
		 * Elimina el player del entitymanager
		 */
		void deletePlayer();

		/**
		 * Devuelve una lista con todas las Entidades dinamicas. Es el propio EntityManager el que debe
		 * hacer la distincion entre Tipos de entidad dinamicos y estaticos.
		 * @return Lista de entidades dinamicas
		 */
		list<GEDynamic*> getDynamics();

		/**
		 * Devuelve la lista de enemigos
		 * @return Lista de enemigos
		 */
		list<GEDynamic*> getEnemys();

		/**
		 * Devuelve una lista con todas las Entidades estaticas. Es el propio EntityManager el que debe
		 * hacer la distincion entre Tipos de entidad dinamicos y estaticos.
		 * @return Lista de entidades estaticas
		 */
		list<GEStatic*> getStatics();

		/**
		 * Actualiza todas las entidades, llamando a su metodo Update.
		 */
		void Update();

		/**
		 * Indica si estamos en game over o no (el player ha muerto)
		 * @return TRUE si el player ha muerto
		 */
		bool isGameOver();

		/**
		 * Limpia el em
		 */
		void Init();
	private:

		/**
		 * Funcion auxiliar que copia un objeto en otro. (Llamada en el constructor de copia y el operador
		 * asignaci�n). Copiamos el EntityManager tal cual (con punteros incluidos).
		 * @param em Origen de la copia.
		 */
		void copiarDesde(const EntityManager& em);

		/**
		 * Anyade una entidad estatica a la lista de manera ordenada
		 * @param ent_sta Entidad estatica
		 */
		void addOrderedStatic(GEStatic* ent_sta);

		/**
		 * Anyade una entidad dinamica a la lista de manera ordenada
		 * @param ent_din Entidad dinamica
		 */
		void addOrderedDynamic(GEDynamic* ent_din);

		/**
		 * Indica si un Tipo pertenece a las entidades dinamicas.
		 * @param tipo Tipo a consultar
		 * @return True si es un tipo de entidad dinamico
		 */
		bool isDynamic(GameEntity::TipoEntidad tipo);

		/**
		 * Indica si un Tipo es estatico
		 * @param tipo Tipo a consultar
		 * @return True si es estatico
		 */
		bool isStatic(GameEntity::TipoEntidad tipo);

		/**
		 * Lista que almacena las entidades dinamicas
		 */
		list<GEDynamic*> _dinamicas;

		/**
		 * Lista de entidades estaticas
		 */
		list<GEStatic*> _staticas;

		/**
		 * Puntero al player
		 */
		Player* _player;

		/**
		 * Indica si el juego ha terminado (gameover = true)
		 */
		bool _gameover;

	};

} /* namespace candy */
#endif /* ENTITYMANAGER_H_ */
