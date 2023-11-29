#include <iostream>
#include <boost/asio.hpp>
#include <boost/beast.hpp>

namespace Asio {
	using namespace boost::asio;
	using namespace boost::asio::ip;
}

namespace Beast {
	using namespace boost::beast;
}

static void do_session(Asio::tcp::socket& socket, const std::shared_ptr<const std::string>& root);

int main(int argc, char *argv[])
{
	try {
		if (argc != 4) {
			std::cerr << "Usage: HttpServer <host> <port> <root>\n"
				<< "Example:\n"
				<< "    HttpServer localhost:8088 ./\n";
			return 1;
		}

		const auto host = Asio::ip::make_address(argv[1]);
		const auto port = static_cast<unsigned short>(std::atoi(argv[2]));
		const auto root = std::make_shared<std::string>(argv[3]);

		Asio::io_context ctx{ 1 };
		Asio::tcp::acceptor acceptor{ ctx, {host, port} };
		for (;;) {
			Asio::tcp::socket socket{ ctx };
			acceptor.accept(socket);

			std::thread(std::bind(&do_session, std::move(socket), root)).detach();
		}
	}
	catch (const std::exception &e) {
		std::cerr << "Error: " << e.what() << std::endl;
		return 1;
	}

	return 0;
}

Beast::string_view mime_type(Beast::string_view path)
{
	using Beast::iequals;
	auto const ext = [&path]
	{
		auto const pos = path.rfind(".");
		if (pos == Beast::string_view::npos)
			return Beast::string_view{};
		return path.substr(pos);
	}();
	if (iequals(ext, ".htm"))  return "text/html";
	if (iequals(ext, ".html")) return "text/html";
	if (iequals(ext, ".php"))  return "text/html";
	if (iequals(ext, ".css"))  return "text/css";
	if (iequals(ext, ".txt"))  return "text/plain";
	if (iequals(ext, ".js"))   return "application/javascript";
	if (iequals(ext, ".json")) return "application/json";
	if (iequals(ext, ".xml"))  return "application/xml";
	if (iequals(ext, ".swf"))  return "application/x-shockwave-flash";
	if (iequals(ext, ".flv"))  return "video/x-flv";
	if (iequals(ext, ".png"))  return "image/png";
	if (iequals(ext, ".jpe"))  return "image/jpeg";
	if (iequals(ext, ".jpeg")) return "image/jpeg";
	if (iequals(ext, ".jpg"))  return "image/jpeg";
	if (iequals(ext, ".gif"))  return "image/gif";
	if (iequals(ext, ".bmp"))  return "image/bmp";
	if (iequals(ext, ".ico"))  return "image/vnd.microsoft.icon";
	if (iequals(ext, ".tiff")) return "image/tiff";
	if (iequals(ext, ".tif"))  return "image/tiff";
	if (iequals(ext, ".svg"))  return "image/svg+xml";
	if (iequals(ext, ".svgz")) return "image/svg+xml";
	return "application/text";
}

std::string path_cat(Beast::string_view base, Beast::string_view path)
{
	if (base.empty()) {
		return std::string(path);
	}
	std::string result(base);
#ifdef BOOST_MSVC
	char constexpr path_separator = '\\';
	if (result.back() == path_separator)
		result.resize(result.size() - 1);
	result.append(path.data(), path.size());
	for (auto& c : result)
		if (c == '/')
			c = path_separator;
#else
	char constexpr path_separator = '/';
	if (result.back() == path_separator)
		result.resize(result.size() - 1);
	result.append(path.data(), path.size());
#endif
	return result;
}

template<typename Body, typename Allocator, typename Send>
void handle_request(Beast::string_view root, Beast::http::request<Body, Beast::http::basic_fields<Allocator>> &&req, Send &&send)
{
	const auto bad_request = [&req](Beast::string_view why) {
		Beast::http::response<Beast::http::string_body> res{Beast::http::status::bad_request, req.version()};
		res.set(Beast::http::field::server, BOOST_BEAST_VERSION_STRING);
		res.set(Beast::http::field::content_type, "text/html");
		res.keep_alive(req.keep_alive());
		res.body() = std::string(why);
		res.prepare_payload();
		return res;
	};

	auto const not_found = [&req](Beast::string_view target)
	{
		Beast::http::response<Beast::http::string_body> res{ Beast::http::status::not_found, req.version() };
		res.set(Beast::http::field::server, BOOST_BEAST_VERSION_STRING);
		res.set(Beast::http::field::content_type, "text/html");
		res.keep_alive(req.keep_alive());
		res.body() = "The resource '" + std::string(target) + "' was not found.";
		res.prepare_payload();
		return res;
	};

	auto const server_error =
		[&req](Beast::string_view what)
	{
		Beast::http::response<Beast::http::string_body> res{ Beast::http::status::internal_server_error, req.version() };
		res.set(Beast::http::field::server, BOOST_BEAST_VERSION_STRING);
		res.set(Beast::http::field::content_type, "text/html");
		res.keep_alive(req.keep_alive());
		res.body() = "An error occurred: '" + std::string(what) + "'";
		res.prepare_payload();
		return res;
	};

	if (req.method() != Beast::http::verb::get && req.method() != Beast::http::verb::head) {
		return send(bad_request("Unknown HTTP-method"));
	}

	if (req.target().empty() || req.target()[0] != '/' || req.target().find("..") != Beast::string_view::npos) {
		return send(bad_request("Illegal request-target"));
	}

	std::string path = path_cat(root, req.target());
	if (req.target().back() == '/') {
		path.append("index.html");
	}

	Beast::error_code ec;
	Beast::http::file_body::value_type body;
	body.open(path.c_str(), Beast::file_mode::scan, ec);

	if (ec == Beast::errc::no_such_file_or_directory) {
		return send(not_found(req.target()));
	}

	if (ec) {
		return send(server_error(ec.message()));
	}

	const auto size = body.size();
	if (req.method() == Beast::http::verb::head) {
		Beast::http::response<Beast::http::empty_body> res{Beast::http::status::ok, req.version()};
		res.set(Beast::http::field::server, BOOST_BEAST_VERSION_STRING);
		res.set(Beast::http::field::content_type, mime_type(path));
		res.content_length(size);
		res.keep_alive(req.keep_alive());
		return send(std::move(res));
	}
	
	Beast::http::response<Beast::http::file_body> res{
		std::piecewise_construct,
		std::make_tuple(std::move(body)),
		std::make_tuple(Beast::http::status::ok, req.version()) };
	res.set(Beast::http::field::server, BOOST_BEAST_VERSION_STRING);
	res.set(Beast::http::field::content_type, mime_type(path));
	res.content_length(size);
	res.keep_alive(req.keep_alive());
	return send(std::move(res));
}

void fail(Beast::error_code ec, const char *what)
{
	std::cerr << what << ": " << ec << std::endl;
}

template<typename Stream>
struct send_lambda
{
	Stream& stream;
	bool& close;
	Beast::error_code& ec;

	explicit send_lambda(Stream& stream, bool& close, Beast::error_code& ec)
		: stream(stream), close(close), ec(ec)
	{}


	template<bool IsRequest, typename Body, typename Fields>
	void operator()(Beast::http::message<IsRequest, Body, Fields> &&msg) const
	{
		close = msg.need_eof();

		Beast::http::serializer<IsRequest, Body, Fields> ser{ msg };
		Beast::http::write(stream, ser, ec);
	}
};

void do_session(Asio::tcp::socket& socket, const std::shared_ptr<const std::string>& root)
{
	bool close = false;
	Beast::error_code ec;
	Beast::flat_buffer buffer;
	send_lambda<Asio::tcp::socket> lambda{socket, close, ec};

	for (;;) {
		Beast::http::request<Beast::http::string_body> req;
		Beast::http::read(socket, buffer, req, ec);
		if (ec == Beast::http::error::end_of_stream) {
			break;
		}
		if (ec) {
			fail(ec, "read");
			return;
		}

		// response
		handle_request(*root, std::move(req), lambda);
		if (ec) {
			fail(ec, "write");
			return;
		}
		if (close) {
			break;
		}
	}

	socket.shutdown(Asio::tcp::socket::shutdown_send, ec);
}
