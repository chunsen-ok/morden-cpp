#include "widget.hpp"

Widget::Widget(Widget *parent)
    : Object(parent)
{

}

void Widget::draw()
{
    // ...
}

void Widget::show()
{
    // ...
}

Size<double> Widget::sizeHint() const
{
    return *size;
}

SizePolicy Widget::sizePolicy() const
{
    return SizePolicy{SizePolicy::Stretch, SizePolicy::Stretch};
}
