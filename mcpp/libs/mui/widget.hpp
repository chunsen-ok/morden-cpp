#ifndef WIDGET_HPP
#define WIDGET_HPP

#include "object.hpp"
#include "point.hpp"
#include "size.hpp"
#include "size_policy.hpp"

// Widget 表示可绘制类型的基本类型
// 天然地支持2D、3D
// 支持direct ui和rasterization
class Widget: public Object
{
public:
    explicit Widget(Widget *parent = nullptr);

    virtual void draw();
    virtual Size<double> sizeHint() const;
    virtual SizePolicy sizePolicy() const;

    // Property<Point<double>> position;
    // Property<Size<double>> size;
};

/*
整体控制、程序运行生命周期控制
界面 - 单纯的界面描述，独立于任何逻辑
界面间逻辑，无其他数据介入情况下，界面间如何跳转、改变
业务逻辑
数据、数据访问、操作逻辑
底层设施
*/


#endif