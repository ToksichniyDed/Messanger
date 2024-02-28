//
// Created by Toksichniy_Ded on 16.02.2024.
//

#ifndef SERVER_POOL_CONNECTION_H
#define SERVER_POOL_CONNECTION_H

#include "../../../Tools/Containers/TContainer_Queue.h"
#include "Database_Connector.h"

class Pool_Connection {
protected:
    TContainer_Queue<IDatabase_Connector *> *m_pool_connections;
    IDatabase_Connector_Factory *m_connector_factory;

public:
    Pool_Connection(int count_of_connections, TContainer_Queue<IDatabase_Connector *> *pool,
                    IDatabase_Connector_Factory *factory);

    void Add_Connection(int count_of_connections);

    void Sub_Connection(int count_of_connections);

    IDatabase_Connector *Take_Connector_From_Queue();

    void Emplace_Back_Connector_To_Queue(IDatabase_Connector *connector);
};


#endif //SERVER_POOL_CONNECTION_H
