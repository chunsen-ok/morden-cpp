// MVC 模式
// Model - 业务逻辑与程序状态相关逻辑
// View - 用户界面、内容展示；逻辑最小化，任何逻辑都应与内容展示相关
// Controller - 处理用户输入和交互，负责选择模型和视图；控制应用如何响应请求
#include <iostream>

class Note
{
public:
};

class NoteModel
{
public:
    NoteModel();

    int createNote();
    void removeNote(int uid);
    Note note(int uid) const;
    void update(const Note &note);
};

class View
{
public:

};

// controller，处理view和model之间数据的转换
class Controller
{
public:
    Controller(NoteModel *model, View *view);
    
    void newNote()
    {
        const auto uid = mModel->createNote();
        mView.setCurrentUid(uid);
    }

private:
    NoteModel *mModel;
    View *mView;
};

int main() {
    NoteModel model;
    View view;

    Controller controller(&model, &view);
    controller.newNote();

    return 0;
}
