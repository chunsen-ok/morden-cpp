#include <iostream>
#include <ctime>
#include <string>
#include <boost/asio.hpp>

namespace Asio {
	using namespace boost::asio;
	using namespace boost::asio::ip;
}

std::string make_daytime_string()
{
	std::time_t now = time(0);
	return ctime(&now);
}

int main(int argc, char* argv[])
{
	if (argc != 2) {
		std::cerr << "Usage: " << argv[0] << " <host>" << std::endl;
		return 1;
	}

	try {
		Asio::io_context ctx;
		Asio::tcp::acceptor acceptor(ctx, Asio::tcp::endpoint(Asio::address::from_string(argv[1]), 12345));

		std::cout << "Server started: " << argv[1] << ":" << 12345 << std::endl;
		for (;;) {
			Asio::tcp::socket socket(ctx);
			acceptor.accept(socket);

			std::cout << "Accept: " << socket.remote_endpoint() << std::endl;
			std::string msg = make_daytime_string();
			boost::system::error_code ignored_error;
			Asio::write(socket, Asio::buffer(msg), ignored_error);
		}
	} catch (std::exception& e) {
		std::cerr << e.what() << std::endl;
	}
	
	return 0;
}
