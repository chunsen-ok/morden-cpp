// MVU
// View - [messages] ->
#include <iostream>
#include <string>
#include <vector>

// Model, State, Data
struct Todo {
    std::string m_title;
    std::string m_content;
    std::string m_date_time;
    bool m_checked;
};

class Todos {
public:

    void push(const Todo &todo) {
        m_todos.push_back(todo);
    }

    const std::vector<Todo> &todos() const {
        return m_todos;
    }

private:
    std::vector<Todo> m_todos;
};

class App {
public:
    App(Todos *model): m_model(model) {}

    void show() {
        for (const auto &todo: m_model->todos()) {
            std::cout << todo.m_title << std::endl;
        }
    }

protected:
    Todos *m_model;
};

void init() {}
void update() {}
void view() {}

int main() {
    Todos todos;

    App app(&todos);
    char code = 0;
    while (code != 'q') {
        std::cout << "# ";
        std::cin >> code;

        switch(code) {
        case 'q':
            goto exit;
            break;
        case 'l':
            app.show();
            break;
        case 'a':
        {
            Todo todo;
            todo.m_title = "a";
            todo.m_content = "This is content";
            todo.m_date_time = "2021-01-02";
            todo.m_checked = false;
            todos.push(todo);
        }
        break;
        }
    }

exit:
    return 0;
}
