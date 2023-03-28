#ifndef TRIPLE_H
#define TRIPLE_H

template<typename T1, typename T2, typename T3>
class Triple {
public:

    /**
     * @brief Create a new Triple, a class to handle three differents unknowned types
     * 
     * @param value1 - The first value of the triple
     * @param value2 - The second value of the triple
     * @param value3 - The third value of the triple
    */
    Triple(T1 value1, T2 value2, T3 value3) : m_first(value1), m_second(value2), m_third(value3) {}

    /**
     * @brief Return the first value of the triple
    */
    T1& first() { return this->m_first; }

    /**
     * @brief Return the second value of the triple
    */
    T2& second() { return this->m_second; }

    /**
     * @brief Return the third value of the triple
    */
    T3& third() { return this->m_third; }

private:
    T1 m_first;
    T2 m_second;
    T3 m_third;
};

#endif