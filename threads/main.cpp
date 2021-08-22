#include <iostream>
#include <map>
#include <memory>
#include <thread>
#include <mutex>
#include <random>

std::string random_text() {
    std::random_device r;
    std::default_random_engine e(r());
    std::uniform_int_distribution<int> dist(1, 1000);
    std::string key;
    for (int i = 0; i < 6; ++i) {
        const int n = dist(e) % 36;
        if (n < 10) {
            key.push_back('0' + static_cast<char>(n));
        } else {
            key.push_back('A' + static_cast<char>(n - 10));
        }
    }
    return key;
}

class LocalStorage
{
public:
    ~LocalStorage() {
        std::cout << "~LocalStorage" << std::endl;
    }

    void insert(const std::string &k, const std::string &val) {
        std::lock_guard<std::mutex> lock(mtx);
        datas[k] = val;
    }

    void print() {
        for (const auto &item: datas) {
            std::cout << item.first << ": " << item.second << std::endl;
        }
    }

private:
    std::map<std::string, std::string> datas;
    std::mutex mtx;
};

void query(std::shared_ptr<LocalStorage> storage) {
    storage->insert(random_text(), random_text());
}

int main() {
    auto db = std::make_shared<LocalStorage>();

    std::thread t1(query, db);
    std::thread t2(query, db);
    std::thread t3(query, db);

    t1.join();
    t2.join();
    t3.join();

    db->print();

    return 0;
}
