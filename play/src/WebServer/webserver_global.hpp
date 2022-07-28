#ifndef WEBSERVER_GLOBAL_HPP
#define WEBSERVER_GLOBAL_HPP

#include <iostream>
#include <boost/asio.hpp>
#include <boost/bind/bind.hpp>
#include <boost/beast.hpp>

namespace Asio {
	using namespace boost::asio;
}

namespace Ip {
	using namespace boost::asio::ip;
}

namespace Beast {
	using namespace boost::beast;
}

namespace Http {
	using namespace boost::beast::http;
}

using Tcp = boost::asio::ip::tcp;

inline void fail(boost::system::error_code ec, const char* what)
{
	std::cerr << what << ": " << ec.message() << "\n";
}

#endif // WEBSERVER_GLOBAL_HPP