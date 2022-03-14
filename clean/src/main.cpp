//! https://my.oschina.net/u/5447363/blog/5460840
//!
//! core
//! ui
//! |- cli
//! |- gui
//! |- ...
//! infras
//! |- db
//! |- disk
//! |- web service
//! tests
//!
//! 不同 data 中存在相同 role 时，如何处理？（实现时应当避免这种情况出现，即使真的需要相同的role，也应该近一步区分它们（比如通过数据中携带ID），使之唯一。）
//! 

#include <iostream>
#include "actions.hpp"

const Action* dispatch(const Action &action)
{
    if (action.action() == Action::Update) {
        const auto a = static_cast<const UpdateAction &>(action);
        std::cout << "Update: " << a.data() << std::endl;
        return new UpdateAction{action.role(), a.data()};
    } else if (action.action() == Action::Add) {
        const auto a = static_cast<const AddAction &>(action);
        std::cout << "Add: " << a.data() << std::endl;
    } else if (action.action() == Action::Delete) {
        const auto a = static_cast<const DeleteAction &>(action);
        std::cout << "remove role: " << a.role() << std::endl;
    }
    return nullptr;
}

class ViewState {};
class AppStore {};
struct MID {};
class MessageContentFetcher
{
public:
    MessageContentFetcher(AppStore *store, const MID &mid);

    void progress_changed(int progress)
    {
        ViewState *state;
        // state->set_value(mid, RFetchProgress, progress);
    }

    void finished() {
        // mStore->set_value(mid, RResourceSavePath, path);
    }

private:
    AppStore *mStore;
};

int main(int argc, char *argv[])
{
    UpdateAction update(RChatText, 2343);
    AddAction add(RChatText, 2223);
    DeleteAction del(RChatText);

    const auto updater = dispatch(update);
    dispatch(add);
    dispatch(del);

    if (updater) { delete updater; }
    
    return 0;
}
