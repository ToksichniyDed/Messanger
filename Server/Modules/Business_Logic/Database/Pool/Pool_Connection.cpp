//
// Created by Toksichniy_Ded on 16.02.2024.
//

#include "Pool_Connection.h"

Pool_Connection::Pool_Connection(int count_of_connections,
                                 std::unique_ptr<my_multimap> pool,
                                 std::unique_ptr<IDatabase_Connector_Factory> factory){
    if(pool)
        m_pool_connections = std::move(pool);
    else
        m_pool_connections = std::make_unique<my_multimap>();

    if(factory)
        m_connector_factory = std::move(factory);
    else
        m_connector_factory = std::make_unique<POSGRES_Database_Connector_Factory>();

    Add_Connection(count_of_connections);
}

void Pool_Connection::Add_Connection(int count_of_connections) {
    for(int i = 0;i<count_of_connections; i++){
        std::shared_ptr<IDatabase_Connector> connector = m_connector_factory->Create_Connector();
        connector->Connect("Plotniy_Messanger", DB_USER, DB_PASSWORD, DB_HOST, DB_PORT);
        m_pool_connections->Push(Custom_Connector_Object(std::move(connector)));
    }
}

//По ощущению, здесь может быть баг, что пока будет проверка shared_ptr, место пустогго указателя займет другой, указатель на объект
// и либо Pop() удалит не пустой указатель, либо в else вернет обратно temp_connector не на место nullptr указателя, а на место заполненого указаетля
void Pool_Connection::Sub_Connection(int count_of_connections) {
    for(int i = 0; i < count_of_connections && i>m_pool_connections->Size(); i++){
        m_pool_connections->Top().Get_Ptr()->Disconnect();
        m_pool_connections->Pop();
        count_of_connections--;
    }
}

std::shared_ptr<IDatabase_Connector> Pool_Connection::Take_Connector_From_Pool() {
    while(true)
    for(int i = 0; i < m_pool_connections->Size(); i++){
        auto temp = std::move(m_pool_connections->Top());
        if(temp.Get_Count() == 1){
            m_pool_connections->Pop();
            m_pool_connections->Push(temp);
            return temp.Get_Ptr();
        }
    }
}


