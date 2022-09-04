#ifndef SESSION_HPP
#define SESSION_HPP

#include "webserver_global.hpp"
#include <sqlite3/sqlite3.h>

Beast::string_view mime_type(Beast::string_view path);
std::string path_cat(Beast::string_view base, Beast::string_view path);

class Session : public std::enable_shared_from_this<Session>
{
public:
	Session(Tcp::socket&& socket, const std::shared_ptr<const std::string> &root, sqlite3* db)
		: mStream(std::move(socket))
		, mDocRoot(root)
		, mDb(db)
	{}

	void run()
	{
		Asio::dispatch(mStream.get_executor(), Beast::bind_front_handler(&Session::read, shared_from_this()));
	}

	void read()
	{
		mReq = {};
		mStream.expires_after(std::chrono::seconds(30));
		Http::async_read(mStream, mBuffer, mReq, Beast::bind_front_handler(&Session::onRead, shared_from_this()));
	}

	template<bool isRequest, typename Body, typename Fields>
	void write(Http::message<isRequest, Body, Fields> &&msg)
	{
		auto sp = std::make_shared<Http::message<isRequest, Body, Fields>>(std::move(msg));
		mRes = sp;
		Http::async_write(mStream, *sp, Beast::bind_front_handler(&Session::onWrite, shared_from_this(), sp->need_eof()));
	}

	void close()
	{
		Beast::error_code ec;
		mStream.socket().shutdown(Tcp::socket::shutdown_send, ec);
	}

	void onRead(Beast::error_code ec, std::size_t bytes_transferred)
	{
		boost::ignore_unused(bytes_transferred);

		if (ec == Http::error::end_of_stream) {
			return close();
		}

		if (ec) {
			fail(ec, "read");
			return;
		}

		handle_request();
	}

	void onWrite(bool close, Beast::error_code ec, std::size_t bytes_tranferred)
	{
		boost::ignore_unused(bytes_tranferred);
		if (ec) {
			fail(ec, "write");
			return;
		}

		if (close) {
			Session::close();
			return;
		}

		mRes = nullptr;

		read();
	}

private:
	void handle_request();

private:
	Beast::tcp_stream mStream;
	std::shared_ptr<const std::string> mDocRoot;
	Http::request<Http::string_body> mReq;
	Beast::flat_buffer mBuffer;
	std::shared_ptr<void> mRes;

	sqlite3* mDb;
};

#endif 
