#pragma once
#include <boost/asio/co_spawn.hpp>
#include <boost/asio/detached.hpp>
#include <boost/asio/io_context.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <boost/asio/signal_set.hpp>
#include <boost/asio/write.hpp>
#include <boost/asio.hpp>
#include <boost/bind/bind.hpp>
#include <boost/asio/buffer.hpp>
#include <list>

#include "CommandParser.h"
#include "Client.h"

class Server
{
public:
	Server(Database & db, int port);

	void start();
private:
    boost::asio::io_service ioservice;
	boost::asio::ip::tcp::endpoint ep;
	std::list<Client> mClients;
	int mCommonHandler;
	Database & mDB;
	void accept_handler(boost::asio::ip::tcp::acceptor &tcp_acceptor, Client &client, const boost::system::error_code &ec);
};