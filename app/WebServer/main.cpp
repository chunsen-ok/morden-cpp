#include <iostream>
#include "tcplistener.hpp"
#include "session.hpp"

int main(int argc, char* argv[])
{
	if (argc != 4) {
		std::cerr
			<< "Usage: WebServer <host> <port> <doc-root>\n"
			<< "Examples:\n"
			<< "    WebServer localhost 80 .\n";
		return EXIT_FAILURE;
	}

	const auto address = Asio::ip::make_address(argv[1]);
	const auto port = static_cast<unsigned short>(std::atoi(argv[2]));
	const auto doc_root = std::make_shared<std::string>(argv[3]);
	const auto endpoint = Tcp::endpoint{ address, port };

	Asio::io_context ctx{1};

	auto server = std::make_shared<TcpListener<Session>>(ctx, endpoint, doc_root);
	server->accept();

	ctx.run();

	return EXIT_SUCCESS;
}
