#ifndef LIBHBP_CPP_RNG_H
#define LIBHBP_CPP_RNG_H

#include <random>
#include <limits>

namespace traits
{
template <typename T>
struct DistributionTrait
{
    using type = std::uniform_int_distribution<T>;
};

template <>
struct DistributionTrait<float>
{
    using type = std::uniform_real_distribution<float>;
};

template <>
struct DistributionTrait<double>
{
    using type = std::uniform_real_distribution<double>;
};

}

template <typename T, typename Distribution=typename traits::DistributionTrait<T>::type>
class Rng
{
    std::mt19937 generator;
    Distribution distribution;
public:
    const static T min = std::numeric_limits<T>::min();
    const static T max = std::numeric_limits<T>::max();

    explicit Rng(T = min, T = max);
    Rng(T, T, T);

    T roll();
};

template<typename T, typename Distribution>
Rng<T, Distribution>::Rng(T min, T max)
    : generator(std::random_device()()), distribution(min, max) {}

template<typename T, typename Distribution>
Rng<T, Distribution>::Rng(T min, T max, T seed)
    : generator(seed), distribution(min, max)
{}

template<typename T, typename Distribution>
T Rng<T, Distribution>::roll()
{
    return distribution(generator);
}


#endif //LIBHBP_CPP_RNG_H
