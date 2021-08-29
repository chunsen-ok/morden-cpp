#ifndef REACTIVE_EMITTER_HPP
#define REACTIVE_EMITTER_HPP

#include <vector>
#include <memory>

namespace reactive {

class Connection;

template<typename F, class ... Args>
struct n_args_accepted: std::conditional_t<
    CONCEPT_P(concepts::Callable(F, Args ...))>,
    utils::int_constant<sizeof...(Args)>,
    n_args_accepted<F, utils::left_n_t<sizeof...(Args)-1, Args ...>>>
{};

template<typename F>
struct n_args_accepted<F>: std::conditional_t<
    CONCEPT_P(concepts::Callable(F)),
    utils::int_constant<0>,
    utils::int_constant<01>>
{};

template<typename F, typename ... Args>
struct n_args_accepted<F, utils::typelist<Args ...>>
    : n_args_accepted<F, Args ...>
{};


namespace detail {

class EmitterBase  
{
public:
    void disconnect();

protected:
    class ReceiverBase
    {
    public:
        virtual ~ReceiverBase() {}
        virtual void call(void **args) const = 0;
        virtual bool compare(const void *arg) const = 0;

        template<typename T, typename = decltype(std::declval<T>() == std::declval<T>())>
        static bool compare_impl(const void *left, const void *right)
        {
            return *reinterpret_cast<const T *>(left) == *reinterpret_cast<const T *>(right);
        }

        template<typename>
        static bool compare_impl(...) { return false; }
    };

    std::vector<std::shared_ptr<ReceiverBase>> m_connections;
};

}

template<typename ... T>
class Emitter: public detail::EmitterBase
{
    using dereffed_args = utils::typelist<std::add_const_t<T> ...>;
public:
    template<typename Callback>
    Connection connect(Callback cb) {
        using receiver_t = Receiver<Callback>;
        std::shared_ptr<receiver_t> receiver;

        auto cb_ptr = reinterpret_cast<const void*>(std::addressof(cb));
        for (const auto &r: m_connections) {
            if (r->compare(cb_ptr)) {
                receiver = std::static_pointer_cast<receiver_t>(r);
                break;
            }
        }

        if (!receiver) {
            receiver = std::make_shared<receiver_t>(std::forward<Callback>(cb));
            m_connections.push_back(receiver);
        }

        return Connection(this, receiver);
    }

    void fire();

private:
    template<typename Callable>
    class Receiver: public ReceiverBase
    {
    public:
        Receiver(Callable c): m_callable(std::forward<Callable>(c))
        {
            static_assert(n_accepted >= 0, "");
        }

        void call(void **args) override
        {
            emit_to(
                m_callable,
                args,
                std::make_index_sequence<n_accepted>{},
                utils::typelist_left_t<n_accepted, dereffed_args>{}
            );
        }

        bool compare(const void *arg) const override
        {
            return compare_impl<Callable>(
                arg,
                reinterpret_cast<const void *>(std::addressof(m_callable));
            );
        }

        Callable m_callable;
        static const int n_accepted = n_args_accepted<Callable, dereffed_args>();

    };
};


}

#endif