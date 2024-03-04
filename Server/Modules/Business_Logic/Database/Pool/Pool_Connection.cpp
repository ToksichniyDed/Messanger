//
// Created by Toksichniy_Ded on 16.02.2024.
//

#include "Pool_Connection.h"

Pool_Connection::Pool_Connection(int count_of_connections, TContainer_Queue<IDatabase_Connector *>* pool, IDatabase_Connector_Factory *factory)
:m_connector_factory(factory), m_pool_connections(pool) {
    Add_Connection(count_of_connections);
}

void Pool_Connection::Add_Connection(int count_of_connections) {
    for(int i = 0;i<count_of_connections; i++){
        IDatabase_Connector* connector = m_connector_factory->Create_Connector();
        m_pool_connections->Emplace(connector);
    }
}

void Pool_Connection::Sub_Connection(int count_of_connections) {
    for(int i = 0; i < count_of_connections && i>m_pool_connections->Size(); i++){
        int size = m_pool_connections->Size();
        m_pool_connections->Front()->Disconnect();
        delete m_pool_connections->Front();
        m_pool_connections->Pop();
    }
}

IDatabase_Connector *Pool_Connection::Take_Connector_From_Queue() {
    std::function<bool()> func = [&](){return !m_pool_connections->Empty();};
    m_pool_connections->Conditional(func);
    IDatabase_Connector* connector = m_pool_connections->Front();
    m_pool_connections->Pop();
    return connector;
}

void Pool_Connection::Emplace_Back_Connector_To_Queue(IDatabase_Connector *connector) {
    m_pool_connections->Emplace(connector);
}


