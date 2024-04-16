//
// Created by Toksichniy_Ded on 23.03.2024.
//

#ifndef CLIENT_IMESSAGE_H
#define CLIENT_IMESSAGE_H


class IMessage {
public:
    IMessage() = default;
    virtual ~IMessage() = default;
    virtual void Prepare_Data() = 0;
    [[nodiscard]] virtual std::string Get_Prepared_Data() const = 0;
};


#endif //CLIENT_IMESSAGE_H
