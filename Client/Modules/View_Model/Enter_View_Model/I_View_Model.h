//
// Created by Toksichniy_Ded on 02.05.2024.
//

#ifndef CLIENT_I_VIEW_MODEL_H
#define CLIENT_I_VIEW_MODEL_H

#include <memory>

#include "../../Model/Networking/Socket/Socket.h"

class I_View_Model {
public:
    using Socket_Ptr = std::shared_ptr<Socket>;

protected:
    Socket_Ptr m_socket;

public:
    explicit I_View_Model():m_socket(Socket::Instance()){};
    virtual ~I_View_Model() = default;
};

#endif //CLIENT_I_VIEW_MODEL_H
