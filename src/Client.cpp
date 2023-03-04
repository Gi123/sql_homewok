#include "Client.h"

Client::Client(Database & db, boost::asio::io_service &io_service) : 
    mDB(db), mSocket{std::make_shared<boost::asio::ip::tcp::socket>(io_service)} {};
void Client::read_handler(const boost::system::error_code &ec, std::size_t bytes_transferred) {
    if (!ec) {
        std::string str(data, bytes_transferred-1);
        std::string result = cp.parse(str)->execute(mDB).append("\n");
        mSocket->write_some( boost::asio::buffer(result.c_str(), result.size()));
    }
    boost::asio::async_read(*mSocket, boost::asio::buffer(data, 512), boost::bind(&Client::up_to_enter, this,
        boost::asio::placeholders::error, boost::asio::placeholders::bytes_transferred), 
        boost::bind(&Client::read_handler, this, boost::asio::placeholders::error, boost::asio::placeholders::bytes_transferred));
}
SocketPtr Client::getSocket() {return mSocket;}
size_t Client::up_to_enter(const boost::system::error_code &ec, size_t bytes) {
    if (!ec) {
        for (size_t i = 0; i < bytes; ++i)
            if (data[i] == '\n')
                return 0;
    }
    return 1;
}

void Client::aread() { boost::asio::async_read(*mSocket, boost::asio::buffer(data, 512), 
    boost::bind(&Client::up_to_enter, this, boost::asio::placeholders::error, boost::asio::placeholders::bytes_transferred),
    boost::bind(&Client::read_handler, this, boost::asio::placeholders::error, boost::asio::placeholders::bytes_transferred));}
                                                                    