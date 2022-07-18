#include "session.hpp"

Beast::string_view mime_type(Beast::string_view path)
{
	using Beast::iequals;

	auto const ext = [&path] {
		auto const pos = path.rfind(".");
		if (pos == Beast::string_view::npos) {
			return Beast::string_view{};
		}
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
	if (base.empty())
		return std::string(path);
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

void Session::handle_request()
{
	// Returns a bad request response
	auto const bad_request = [](const Http::request<Http::string_body>& req, Beast::string_view why)
	{
		Http::response<Http::string_body> res{ Http::status::bad_request, req.version() };
		res.set(Http::field::server, BOOST_BEAST_VERSION_STRING);
		res.set(Http::field::content_type, "text/html");
		res.keep_alive(req.keep_alive());
		res.body() = std::string(why);
		res.prepare_payload();
		return res;
	};

	// Returns a not found response
	auto const not_found = [](const Http::request<Http::string_body>& req, Beast::string_view target)
	{
		Http::response<Http::string_body> res{ Http::status::not_found, req.version() };
		res.set(Http::field::server, BOOST_BEAST_VERSION_STRING);
		res.set(Http::field::content_type, "text/html");
		res.keep_alive(req.keep_alive());
		res.body() = "The resource '" + std::string(target) + "' was not found.";
		res.prepare_payload();
		return res;
	};

	// Returns a server error response
	auto const server_error = [](const Http::request<Http::string_body>& req, Beast::string_view what)
	{
		Http::response<Http::string_body> res{ Http::status::internal_server_error, req.version() };
		res.set(Http::field::server, BOOST_BEAST_VERSION_STRING);
		res.set(Http::field::content_type, "text/html");
		res.keep_alive(req.keep_alive());
		res.body() = "An error occurred: '" + std::string(what) + "'";
		res.prepare_payload();
		return res;
	};

	// Make sure we can handle the method
	if (mReq.method() != Http::verb::get && mReq.method() != Http::verb::head) {
		return write(bad_request(mReq, "Unknown HTTP-method"));
	}

	// Request path must be absolute and not contain "..".
	if (mReq.target().empty() || mReq.target()[0] != '/' || mReq.target().find("..") != Beast::string_view::npos) {
		return write(bad_request(mReq, "Illegal request-target"));
	}

	// Build the path to the requested file
	std::string path = path_cat(*mDocRoot, mReq.target());
	if (mReq.target().back() == '/') {
		path.append("index.html");
	}

	// Attempt to open the file
	Beast::error_code ec;
	Http::file_body::value_type body;
	body.open(path.c_str(), Beast::file_mode::scan, ec);

	// Handle the case where the file doesn't exist
	if (ec == Beast::errc::no_such_file_or_directory) {
		return write(not_found(mReq, mReq.target()));
	}

	// Handle an unknown error
	if (ec) {
		return write(server_error(mReq, ec.message()));
	}

	// Cache the size since we need it after the move
	auto const size = body.size();

	// Respond to HEAD request
	if (mReq.method() == Http::verb::head) {
		Http::response<Http::empty_body> res{ Http::status::ok, mReq.version() };
		res.set(Http::field::server, BOOST_BEAST_VERSION_STRING);
		res.set(Http::field::content_type, mime_type(path));
		res.content_length(size);
		res.keep_alive(mReq.keep_alive());
		return write(std::move(res));
	}

	// Respond to GET request
	Http::response<Http::file_body> res{
		std::piecewise_construct,
		std::make_tuple(std::move(body)),
		std::make_tuple(Http::status::ok, mReq.version())
	};
	res.set(Http::field::server, BOOST_BEAST_VERSION_STRING);
	res.set(Http::field::content_type, mime_type(path));
	res.content_length(size);
	res.keep_alive(mReq.keep_alive());
	return write(std::move(res));
}