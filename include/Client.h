#pragma once

#include "CommandParser.h"

#include <boost/asio/co_spawn.hpp>
#include <boost/asio/detached.hpp>
#include <boost/asio/io_context.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <boost/asio/signal_set.hpp>
#include <boost/asio/write.hpp>
#include <boost/asio.hpp>
#include <boost/bind/bind.hpp>
#include <boost/asio/buffer.hpp>

using SocketPtr = std::shared_ptr<boost::asio::ip::tcp::socket>;

class Client
{
private:
	char data[512];
	SocketPtr mSocket;
	CommandParser cp;
	Database & mDB;
public:
	Client(Database & db, boost::asio::io_service &io_service);
	void read_handler(const boost::system::error_code &ec, std::size_t bytes_transferred);
	SocketPtr getSocket();
	size_t up_to_enter(const boost::system::error_code &ec, size_t bytes);
    void aread();
};