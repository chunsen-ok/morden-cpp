#ifndef CLEAN_SERVER_EVENT_RECEIVER_HPP
#define CLEAN_SERVER_EVENT_RECEIVER_HPP

template<typename T>
class DataStore;
class AppData;

class ServerEventReceiver
{
public:
    ServerEventReceiver(DataStore<AppData> *data) {}

    void run()
    {

    }
};

#endif
