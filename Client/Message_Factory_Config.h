//
// Created by Toksichniy_Ded on 02.04.2024.
//

#ifndef CLIENT_MESSAGE_FACTORY_CONFIG_H
#define CLIENT_MESSAGE_FACTORY_CONFIG_H

#include <boost/di.hpp>

#include "Modules/Model/Networking/Socket/Message_Type/IMessage.h"
#include "Modules/Tools/TFactory.h"


namespace Message_Factory_Config {

    using Factory = TFactory<std::string, IMessage>;

    inline Factory Message_Factory_Config() {
        auto injector = boost::di::make_injector(
                boost::di::bind<Factory>.to([]() {
                    auto map = std::make_unique<boost::unordered_map<std::string, Factory::function>>();
                    return TFactory<std::string, IMessage>{std::move(map)};
                })
        );
        auto factory = injector.create<Factory>();

        return factory;
    }
}
#endif //CLIENT_MESSAGE_FACTORY_CONFIG_H
