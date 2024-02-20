//
// Created by Toksichniy_Ded on 16.02.2024.
//

#ifndef SERVER_POOL_CONNECTION_H
#define SERVER_POOL_CONNECTION_H

#include "../../../Tools/Containers/Container_Vector.h"
#include "Database_Connector.h"

class Pool_Connection {
protected:
    Container_Vector<IDatabase_Connector *> *m_pool_connections;
    IDatabase_Connector_Factory *m_connector_factory;

public:
    Pool_Connection(int count_of_connections, Container_Vector<IDatabase_Connector *> *pool,
                    IDatabase_Connector_Factory *factory);

    void Add_Connection(int count_of_connections);

    void Sub_Connection(int count_of_connections);
};


#endif //SERVER_POOL_CONNECTION_H
