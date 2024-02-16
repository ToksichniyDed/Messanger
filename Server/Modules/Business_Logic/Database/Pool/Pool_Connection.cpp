//
// Created by Toksichniy_Ded on 16.02.2024.
//

#include "Pool_Connection.h"

Pool_Connection::Pool_Connection(int count_of_connections, Container_Vector<IDatabase_Connector *>* pool, IDatabase_Connector_Factory *factory)
:m_connector_factory(factory), m_pool_connections(pool) {
    Add_Connection(count_of_connections);
}

void Pool_Connection::Add_Connection(int count_of_connections) {
    for(int i = 0;i<count_of_connections; i++){
        IDatabase_Connector* connector = m_connector_factory->Create_Connector();
        m_pool_connections->Emplace_Back(connector);
    }
}

void Pool_Connection::Sub_Connection(int count_of_connections) {
    for(int i = 0; i < count_of_connections && i>m_pool_connections->Size(); i++){
        int size = m_pool_connections->Size();
        m_pool_connections->At(size - 1 - i)->Disconnect();
        delete m_pool_connections->At(size - 1 - i);
        m_pool_connections->Erase(size - 1 - i);
    }
}
