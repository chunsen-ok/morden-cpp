#ifndef TCPLISTENER_HPP
#define TCPLISTENER_HPP

#include "webserver_global.hpp"
#include "session.hpp"

template<typename Session>
class TcpListener : public std::enable_shared_from_this<TcpListener<Session>>
{
public:
	TcpListener(Asio::io_context& ctx, const Tcp::endpoint& endpoint, const std::shared_ptr<const std::string> &doc_root)
		: mCtx(ctx)
		, mAcceptor(Asio::make_strand(ctx))
		, mDocRoot(doc_root)
	{
		bind(endpoint);
	}

	void accept()
	{
		mAcceptor.async_accept(Asio::make_strand(mCtx), Beast::bind_front_handler(&TcpListener<Session>::accept_incoming, shared_from_this()));
	}

private:
	void bind(const Tcp::endpoint& endpoint)
	{
		boost::system::error_code ec;
		mAcceptor.open(endpoint.protocol(), ec);
		if (ec) {
			fail(ec, "open");
			return;
		}

		mAcceptor.set_option(Asio::socket_base::reuse_address(true), ec);
		if (ec) {
			fail(ec, "set_option");
			return;
		}

		mAcceptor.bind(endpoint, ec);
		if (ec) {
			fail(ec, "bind");
			return;
		}

		mAcceptor.listen(Asio::socket_base::max_listen_connections, ec);
		if (ec) {
			fail(ec, "listen");
			return;
		}
	}

	void accept_incoming(boost::system::error_code ec, Tcp::socket socket)
	{
		if (ec) {
			fail(ec, "TcpListener: accept incoming");
			return;
		}
		else {
			auto s = std::make_shared<Session>(std::move(socket), mDocRoot);
			s->run();
		}

		accept();
	}

private:
	Asio::io_context& mCtx;
	Tcp::acceptor mAcceptor;
	std::shared_ptr<const std::string> mDocRoot;
};

#endif // TCPLISTENER_HPP