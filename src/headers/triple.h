#pragma once
template<typename T1, typename T2, typename T3>
class Triple {
public:
    Triple(T1 value1, T2 value2, T3 value3) : m_first(value1), m_second(value2), m_third(value3) {}

    T1& first() { return this->m_first; }
    T2& second() { return this->m_second; }
    T3& third() { return this->m_third; }

private:
    T1 m_first;
    T2 m_second;
    T3 m_third;
};