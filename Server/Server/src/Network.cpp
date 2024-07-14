#include "Network.h"
#include <iostream>
#include <thread>
#include <chrono>

Network::Network(unsigned short port) : listen_port(port)
{
    std::cout<<"Chat Server Started\n";

    if (listener.listen(listen_port) != sf::Socket::Done)
    {
        std::cerr<<"Could not listen\n";
    }
}

void Network::ConnectClients(std::vector<std::unique_ptr<sf::TcpSocket>>& array)
{
    while (true)
    {
        std::unique_ptr<sf::TcpSocket> new_client(new sf::TcpSocket());
        if (listener.accept(*new_client) == sf::Socket::Done)
        {
            std::cerr<<"Added client " << new_client->getRemoteAddress() << ":" << new_client->getRemotePort() << " on slot " << array.size()<<"\n";
            new_client->setBlocking(false);
            array.push_back(std::move(new_client));
        }
        else
        {
            std::cerr<<"Server listener error, restart the server\n";
            break;
        }
    }
}


void Network::DisconnectClient(std::vector<std::unique_ptr<sf::TcpSocket>>& vec, std::vector<std::unique_ptr<sf::TcpSocket>>::iterator position)
{
    if (position >= vec.end()) return;
    position->get()->disconnect();
    position->release();
    vec.erase(position); //СДЕЛАТЬ ОТДЕЛЬНЫЙ LIST ГДЕ БУДУТ УКАЗАТЕЛИ НА ПУСТЫЕ МЕСТА И ТУДА БУДУТ ЗАСЕЛЯТЬСЯ НОВЫЕ КЛИЕНТЫ
}

sf::Packet Network::ReceivePacket(std::vector<std::unique_ptr<sf::TcpSocket>>& vec, std::vector<std::unique_ptr<sf::TcpSocket>>::iterator client)
{
    sf::Packet packet;

    auto state = client->get()->receive(packet);

    if (state == sf::Socket::NotReady) return {};

    if (state == sf::Socket::Disconnected)
    {
        DisconnectClient(vec, client);
        return {};
    }

    if (state == sf::Socket::Done)
    {
        std::string name;
        //std::string password;
        std::string message;
        packet>>name>>message;
        packet.clear();
        packet<<name<<message;
        return packet;
        //BroadcastPacket(client_array, packet); //ERROR
    }

    return sf::Packet();
}

void Network::BroadcastPacket(std::vector<std::unique_ptr<sf::TcpSocket>>& vec, sf::Packet & packet)
{
    for (const auto & iterator : vec)
    {
        if (iterator->send(packet) != sf::Socket::Done)
        {
            std::cerr<<"Could not send packet on broadcast\n";
        }
    }
}

[[noreturn]] void Network::ManagePackets()
{
    while (true)
    {
        for (size_t i = 0; i < client_array.size(); i++)
        {
            sf::Packet packet = ReceivePacket(client_array, client_array.begin() + i);
            if (packet.getDataSize() != 0) {
                BroadcastPacket(client_array, packet);
            }
        }

        std::cout<<"sA\n";
        std::this_thread::sleep_for(std::chrono::milliseconds(100)); //ERROR
        std::cout<<"b\n";
    }
}

void Network::Run() {
    std::thread connetion_thread([this](){
        this->ConnectClients(this->client_array);
    });

    ManagePackets();
}



