//
// Created by Toksichniy_Ded on 28.03.2024.
//

#ifndef CLIENT_TFACTORY_H
#define CLIENT_TFACTORY_H

#include <string>
#include <memory>

#include <boost/unordered_map.hpp>
#include <boost/function.hpp>
#include <boost/functional/factory.hpp>

template <class Key, class Base>
class TFactory {
public:
    using function = boost::function<std::shared_ptr<Base>()>;
    using factory_map = std::unique_ptr<boost::unordered_map<Key, function>>;

protected:
    factory_map m_map;

public:
    template<class Derived> void Register(Key key);
    std::shared_ptr<Base> Create(Key key);

};

template<class Key, class Base>
std::shared_ptr<Base> TFactory<Key, Base>::Create(Key key) {
    auto it = m_map->find(key);
    if(it != m_map->end()){
        return it->second();
    }
    else
        throw (std::runtime_error("Unexpected type!;"));
}

template<class Key, class Base>
template<class Derived>
void TFactory<Key, Base>::Register(Key key) {
    (*m_map)[key] = boost::factory<std::shared_ptr<Derived>>();
}


#endif //CLIENT_TFACTORY_H
