#include <iostream>

int main() {

}

void startUp()
{
    Application::init();

    Application::onNeedUpgrade()
    .then([](){
        Window::showUpgrade();
    });

    Window::onAllowUpgrade()
    .then([](){
        Application::upgrade();
    });

    Application::onExit()
    .then([](){
        Window::quit();
        Session::stop(); // logout, stop received messages, persist data
        Application::stop();
    });

    Network::onError()
    .then([](){
        return Window::showError();
    })
    .then([](bool retry){
        if (retry) {
            Application::start();
        } else{
            Application::exit();
        }
    });

    Session::onLoginOk()
    .then([](){
        Session::start(); // setup LocalStorage, ...`
        // ... save some data
        Session::fetchInChats();
        Session::fetchContacts();
        Session::fetchGroups();
        Session::fetchOfflineMessages();
        Session::fetchOtherDatas();
        Session::startFetchMessages();
    })
    .then([](){
        Window::showMainWindow();
    });

    Application::check();
    GlobalStorage::init();
    Network::init();

    const auto info = GlobalStorage::data("last_login");
    if (info) {
        Window::AutoLogin().show(); // login, to qr, exit
        Window::AutoLogin()
        .onComfirm()
        .then([](){
            Api::login();
        });
    } else {
        // need network
        Window::showQR(); // refresh, allow, exit

        Window::QR()
        .onAllowed([](){
            Api::login();
        });
    }

    return Application::exec();
}
