#include <iostream>
#include <boost/asio.hpp>
#include <boost/array.hpp>

namespace Asio {
	using namespace boost::asio;
	using namespace boost::asio::ip;
}

int main(int argc, char* argv[])
{
	if (argc != 2) {
		std::cerr << "Usage: " << argv[0] << " <HOST>" << std::endl;
		return 1;
	}

	Asio::io_context ctx;
	Asio::tcp::resolver resolver(ctx);
	Asio::tcp::endpoint server(Asio::address::from_string(argv[1]), 12345);
	Asio::tcp::resolver::results_type results = resolver.resolve(server);
	Asio::tcp::socket socket(ctx);
	Asio::connect(socket, results);

	for (;;) {
		boost::array<char, 128> buf;
		boost::system::error_code error;

		size_t len = socket.read_some(Asio::buffer(buf), error);
		if (error == Asio::error::eof) {
			break;
		} else if (error) {
			std::cerr << error << std::endl;
			return 1;
		}

		std::cout.write(buf.data(), len);
	}

	return 0;
}
