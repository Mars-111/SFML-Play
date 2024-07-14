#pragma once
#include <SFML/Network.hpp>
#include <vector>
#include <memory>


class Network
{
    sf::TcpListener listener;
//    std::vector<sf::TcpSocket *> guests_array;
    std::vector<std::unique_ptr<sf::TcpSocket>> client_array;
    unsigned short listen_port;

public:

    Network(unsigned short port);

    void ConnectClients(std::vector<std::unique_ptr<sf::TcpSocket>>&);
    static void DisconnectClient(std::vector<std::unique_ptr<sf::TcpSocket>>& vec, std::vector<std::unique_ptr<sf::TcpSocket>>::iterator position);

    sf::Packet ReceivePacket(std::vector<std::unique_ptr<sf::TcpSocket>>& vec, std::vector<std::unique_ptr<sf::TcpSocket>>::iterator client);
    static void BroadcastPacket(std::vector<std::unique_ptr<sf::TcpSocket>>& vec, sf::Packet & packet);

    [[noreturn]] void ManagePackets();


    void Run();

};
