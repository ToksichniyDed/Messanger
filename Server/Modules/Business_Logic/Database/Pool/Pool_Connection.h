//
// Created by Toksichniy_Ded on 16.02.2024.
//

#ifndef SERVER_POOL_CONNECTION_H
#define SERVER_POOL_CONNECTION_H

#include <memory>
#include <utility>

#include "../../../Tools/Containers/TPriority_Queue.h"
#include "Database_Connector.h"

class Custom_Connector_Object{
protected:
    std::shared_ptr<IDatabase_Connector> m_ptr;

public:
    explicit Custom_Connector_Object(std::shared_ptr<IDatabase_Connector> ptr = nullptr):m_ptr(std::move(ptr)){};
    bool operator<(const Custom_Connector_Object& other_object) const {
        return m_ptr.use_count()>other_object.m_ptr.use_count();
    }
    int Get_Count(){
        return m_ptr.use_count();
    }
    std::shared_ptr<IDatabase_Connector> Get_Ptr(){
        return m_ptr;
    }
};

class Pool_Connection {
public:
    using my_multimap = TPriority_Queue<Custom_Connector_Object>;

protected:
    std::unique_ptr<my_multimap> m_pool_connections;
    std::unique_ptr<IDatabase_Connector_Factory> m_connector_factory;


public:
    explicit Pool_Connection(int count_of_connections = 5,
                             std::unique_ptr<my_multimap> pool = nullptr,
                             std::unique_ptr<IDatabase_Connector_Factory> factory = nullptr);

    void Add_Connection(int count_of_connections);

    void Sub_Connection(int count_of_connections);

    std::shared_ptr<IDatabase_Connector> Take_Connector_From_Pool();
};



#endif //SERVER_POOL_CONNECTION_H
