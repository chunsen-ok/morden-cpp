#ifndef PLAY_ARCHITECTURE_HPP
#define PLAY_ARCHITECTURE_HPP

#include <vector>

/*
存在的问题是：
1. 编写代码重复度高（搭建新的界面、模型类型，关联两者时，代码差不多）
2. 界面和模型数据关联有些麻烦，甚至可能存在运行效率问题
3. 基础设施的数据、资源变化必须通过model来关联
3. DataRole 膨胀

参考rust druid
*/

namespace play {

struct Size {
    double width;
    double height;
};

struct EventCtx {

};

struct UpdateCtx {

};

struct LayoutCtx {

};

struct BoxConstraints {

};

struct PaintCtx {

};

struct Env {

};

template<typename T>
class Widget {
public:
    virtual void event(EventCtx &ctx, const Event &ev, T &data, const Env &env) = 0;
    virtual void update(UpdateCtx &ctx, const T &old_data, const T &data, const Env &env) = 0;
    virtual Size layout(LayoutCtx &ctx, const BoxConstraints &bc, const T &data, const Env &env) = 0;
    virtual void paint(PaintCtx &ctx, const T &data, const Env &env) = 0;
};

template<typename T>
class Label: public Widget<T> {
public:
    void event(EventCtx &ctx, const Event &ev, T &data, const Env &env) override;
    void update(UpdateCtx &ctx, const T &old_data, const T &data, const Env &env) override;
    Size layout(LayoutCtx &ctx, const BoxConstraints &bc, const T &data, const Env &env) override;
    void paint(PaintCtx &ctx, const T &data, const Env &env) override;
};

class AppData {
public:
    void load();
};

class AppView {

};

class App {
};

class SandBox {

};

}

#endif
