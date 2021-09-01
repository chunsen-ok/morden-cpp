#ifndef SIZE_POLICY_HPP
#define SIZE_POLICY_HPP

class SizePolicy
{
public:

    enum Policy {
        FixedSize = 0x00,
        Stretch = 0x01,
        Shrink = 0x02,
    };

    SizePolicy(Policy hor, Policy ver)
        : m_horizontal(hor), m_vertical(ver)
    {}

    Policy horizontal() const { return m_horizontal; }
    Policy vertical() const { return m_vertical; }

private:
    Policy m_horizontal;
    Policy m_vertical;
};

#endif
