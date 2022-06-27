#include <iostream>
#include <ctime>
#include <string>
#include <boost/asio.hpp>
#include <boost/enable_shared_from_this.hpp>
#include <boost/bind/bind.hpp>
#include <boost/shared_ptr.hpp>

namespace Asio {
	using namespace boost::asio;
	using namespace boost::asio::ip;
}

std::string make_daytime_string()
{
	std::time_t now = time(0);
	return ctime(&now);
}

class TcpConnection : public boost::enable_shared_from_this<TcpConnection>
{
public:
	using Pointer = boost::shared_ptr<TcpConnection>;

	static Pointer create(Asio::io_context& ctx)
	{
		return Pointer(new TcpConnection(ctx));
	}

	Asio::tcp::socket& socket()
	{
		return m_socket;
	}

	void start()
	{
		m_message = make_daytime_string();
		Asio::async_write(m_socket, Asio::buffer(m_message),
			boost::bind(&TcpConnection::handle_write, shared_from_this(),
				Asio::placeholders::error,
				Asio::placeholders::bytes_transferred
			)
		);
	}

	void handle_write(const boost::system::error_code& code, size_t byte_transferred)
	{
		// ...
	}

private:
	TcpConnection(Asio::io_context& ctx)
		: m_socket(ctx)
	{}

	Asio::tcp::socket m_socket;
	std::string m_message;
};

class TcpServer
{
public:
	TcpServer(Asio::io_context& ctx, const Asio::tcp::endpoint& endpoint)
		: m_ctx(ctx)
		, m_acceptor(m_ctx, endpoint)
	{

	}

	void start()
	{
		TcpConnection::Pointer newConnection = TcpConnection::create(m_ctx);

		m_acceptor.async_accept(newConnection->socket(),
			boost::bind(&TcpServer::handle_accept, this, newConnection,
				Asio::placeholders::error
			)
		);
	}
private:
	void handle_accept(TcpConnection::Pointer newConnection, const boost::system::error_code &error)
	{
		if (!error) {
			newConnection->start();
		}
		start();
	}

	Asio::io_context& m_ctx;
	Asio::tcp::acceptor m_acceptor;
};


int main(int argc, char* argv[])
{
	if (argc != 2) {
		std::cerr << "Usage: " << argv[0] << " <host>" << std::endl;
		return 1;
	}

	try {
		Asio::io_context ctx;
		TcpServer server(ctx, Asio::tcp::endpoint(Asio::address::from_string(argv[1]), 12345));
		server.start();
		ctx.run();
	} catch (std::exception& e) {
		std::cerr << e.what() << std::endl;
	}
	
	return 0;
}
