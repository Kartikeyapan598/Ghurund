#pragma once

#include "Server.h"
#include "Client.h"
#include "core/application/Feature.h"

namespace Ghurund::Net {
    using namespace Ghurund::Core;

    class Networking:public Feature, public Noncopyable {
#pragma region reflection
    protected:
        static const Ghurund::Core::Type& GET_TYPE();

    public:
        inline static const Ghurund::Core::Type& TYPE = GET_TYPE();
        virtual const Ghurund::Core::Type& getType() const override { return TYPE; }
#pragma endregion

    public:
        void init();

        void uninit() {
            WSACleanup();
        };

        Server* host(uint16_t port = 0) {
            Server* server = ghnew Server();
            if (server->host(port) != Status::OK) {
                delete server;
                return nullptr;
            }
            return server;
        }

        Client* connect(const tchar* address, uint16_t port) {
            Client* client = ghnew Client();
            if (client->connect(address, port) != Status::OK) {
                delete client;
                return nullptr;
            }
            return client;
        }
    };
}