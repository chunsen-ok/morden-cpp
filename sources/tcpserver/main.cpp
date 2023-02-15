#include <iostream>
#include <boost/asio.hpp>

namespace Sys {
	using namespace boost::system;
}

namespace Asio {
	using namespace boost::asio;
}

namespace Ip {
	using namespace Asio::ip;
}

using Tcp = Ip::tcp;

int main(int argc, char *argv[])
{
	if (argc != 3) {
		std::cerr << "Usage: " << argv[0] << " <host> <port>\n";
		return 1;
	}

	Sys::error_code ecc;
	const auto host = Ip::make_address(argv[1], ecc);
	if (ecc) {
		std::cerr << ecc << std::endl;
		return 1;
	}
	const auto port = static_cast<Ip::port_type>(std::atoi(argv[2]));
	const auto endpoint = Tcp::endpoint{host, port};

	Asio::io_context ctx;
	Tcp::acceptor acceptor{ctx, endpoint};
	for (;;) {
		Tcp::socket socket{ ctx };
		acceptor.accept(socket);
		std::cout << "Start: " << socket.remote_endpoint() << std::endl; 
		Asio::write(socket, Asio::buffer("Hello"), ecc);
	}

	return 0;
}
