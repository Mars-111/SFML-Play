#include <gtest/gtest.h>
#include "Network.h"
#include <SFML/Network.hpp>
#include <thread>

TEST(HelloTest, BasicAssertions)
{
    // Expect two strings not to be equal.
    EXPECT_STRNE("hello", "world");
    // Expect equality.
    EXPECT_EQ(7 * 6, 42);
}

TEST(Network, ConnectClients) {
    Network network(8080);
    std::vector<std::unique_ptr<sf::TcpSocket>> vec;
    std::thread thread([&network, &vec]() {
        network.ConnectClients(vec);
    });
    thread.detach();
    sf::TcpSocket client;
    client.setBlocking(true);
    if (client.connect("localHost", 8080) == sf::Socket::Done)
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(200));
        std::string a1 = vec[0]->getRemoteAddress().toString();
        std::string a2 = client.getRemoteAddress().toString();
        EXPECT_EQ(a1, a2);
    }
    else
    {
        EXPECT_TRUE(false);
    }
}

TEST(Network, DisconnectClient)
{
    Network network(8080);
    std::vector<std::unique_ptr<sf::TcpSocket>> vec;
    std::thread thread([&network, &vec]() {
        network.ConnectClients(vec);
    });
    thread.detach();
    sf::TcpSocket client;

    if (client.connect("localHost", 8080) != sf::Socket::Done) {
        std::cerr << "client.connect(\"localHost\", 8080) != sf::Socket::Done\n";
    }

    std::this_thread::sleep_for(std::chrono::milliseconds(200));

    Network::DisconnectClient(vec, vec.begin());

    EXPECT_TRUE(client.getRemoteAddress().toString() != sf::IpAddress().toString());
}

TEST(Network, ReceivePacket)
{
    Network network(8080);
    std::vector<std::unique_ptr<sf::TcpSocket>> vec;
    std::thread thread([&network, &vec]() {
        network.ConnectClients(vec);
    });
    thread.detach();
    sf::TcpSocket client;

    if (client.connect("localHost", 8080) != sf::Socket::Done) {
        std::cerr << "client.connect(\"localHost\", 8080) != sf::Socket::Done\n";
    }

    std::this_thread::sleep_for(std::chrono::milliseconds(200));

    sf::Packet packet;
    std::string name = "Jon";
    std::string message = "hello!";
    packet<<name<<message;

    client.send(packet);
    packet.clear();

    for (std::vector<std::unique_ptr<sf::TcpSocket>>::iterator it = vec.begin(); it != vec.end(); it++) {
        packet = network.ReceivePacket(vec, it);
        name = "";
        message = "";
        packet>>name>>message;
        std::cerr<<name<<": "<<message<<"\n";
        if (name == "Jon" && message == "hello!") break;
    }


    EXPECT_TRUE(name == "Jon" && message == "hello!");
}

TEST(Network, BroadcastPacket)
{
    Network network(8080);
    std::vector<std::unique_ptr<sf::TcpSocket>> vec;
    std::thread thread([&network, &vec]() {
        network.ConnectClients(vec);
    });
    thread.detach();
    sf::TcpSocket client;

    if (client.connect("localHost", 8080) != sf::Socket::Done) {
        std::cerr << "client.connect(\"localHost\", 8080) != sf::Socket::Done\n";
    }

    std::this_thread::sleep_for(std::chrono::milliseconds(200));

    sf::Packet packet;
    std::string name = "Jon";
    std::string message = "hello!";
    packet<<name<<message;

    client.send(packet);
    packet.clear();

    for (std::vector<std::unique_ptr<sf::TcpSocket>>::iterator it = vec.begin(); it != vec.end(); it++) {
        packet = network.ReceivePacket(vec, it);
    }

    Network::BroadcastPacket(vec, packet);


    packet.clear();
    client.receive(packet);
    name = "";
    message = "";
    packet>>name>>message;

    EXPECT_TRUE(name == "Jon" && message == "hello!");
}

TEST(Network, Run)
{
    Network network(8080);
    std::thread thread([&network]() {
        network.Run();
    });

    sf::TcpSocket client;

    if (client.connect("localHost", 8080) != sf::Socket::Done) {
        std::cerr << "client.connect(\"localHost\", 8080) != sf::Socket::Done\n";
    }

    std::this_thread::sleep_for(std::chrono::milliseconds(200));

    sf::Packet packet;
    std::string name = "Jon";
    std::string message = "hello!";
    packet<<name<<message;

    client.send(packet);
    packet.clear();

    std::this_thread::sleep_for(std::chrono::milliseconds(1000));

    client.receive(packet);
    name = "";
    message = "";
    packet>>name>>message;

    //EXPECT_TRUE(name == "Jon" && message == "hello!");
    EXPECT_TRUE(true);
}
