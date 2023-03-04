#include "Server.h"

Server::Server(Database & db, int port) : mDB(db) {
    ep = boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(), port); // listen on 2001
}
void Server::start() {
    boost::asio::ip::tcp::acceptor tcp_acceptor{ioservice, ep};
    tcp_acceptor.listen();
    mClients.push_back(Client(mDB, ioservice));
    tcp_acceptor.async_accept(*mClients.back().getSocket(), boost::bind(&Server::accept_handler, this, std::ref(tcp_acceptor), std::ref(mClients.back()), boost::placeholders::_1));
    ioservice.run();
}
void Server::accept_handler(boost::asio::ip::tcp::acceptor &tcp_acceptor, Client &client, const boost::system::error_code &ec){
    if (!ec)
        client.aread();
    mClients.push_back(Client(mDB, ioservice));
    tcp_acceptor.async_accept(*mClients.back().getSocket(), boost::bind(&Server::accept_handler, this, std::ref(tcp_acceptor), std::ref(mClients.back()), boost::placeholders::_1));
}