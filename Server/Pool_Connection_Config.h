//
// Created by Toksichniy_Ded on 12.03.2024.
//

#include <boost/di.hpp>

#include "Modules/Business_Logic/Database/Pool/Pool_Connection.h"

#ifndef SERVER_POOL_CONNECTION_CONFIG_H
#define SERVER_POOL_CONNECTION_CONFIG_H

inline std::unique_ptr<Pool_Connection> Pool_Connection_Config(){
    auto injector = boost::di::make_injector(
            boost::di::bind<int>.to(5),
            boost::di::bind<IDatabase_Connector_Factory>.to<POSGRES_Database_Connector_Factory>());

    auto pool_connection = injector.create<std::unique_ptr<Pool_Connection>>();

    return pool_connection;
}

#endif //SERVER_POOL_CONNECTION_CONFIG_H
