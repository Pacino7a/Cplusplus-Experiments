#include <iostream>
#include <random> //std::mt19937 (Mersenne Twister)
#include <chrono> //std::chrono (system time for getting a random seed)
#include "random_mt.h"

// Pseudo Random Number Generator (PRNG)
int main()
{
    std::mt19937 mt_stuck{};// instantiate a 32-bit mersenne twister engine
                        // the `random` sequence will be the same if you initialize it with a same value or like this
                        // therefore, we need a 'random' seed for initializing this bussiness
                        // like system clock or system's random device
    
    // use current time(hardware time) to inintialize the seed
    std::mt19937 mt_time{static_cast<std::mt19937::result_type>(
        std::chrono::steady_clock::now().time_since_epoch().count() // nanoseconds or milliseconds
        )};

    // use random device to create a random seed, 
    // the random_device sometimes not get a deterministic result which
    // will create a same (likely same) sequence (previous compiler)
    // `best practice`
    std::mt19937 mt{std::random_device{}()};
    // Notice: keep this out of a loop or a function body (ineffcient and cause bad result)

    // imporve way, better than last one
    std::random_device rd{};
    // we can use std::seed_seq to imporve the quality of PRNG
    std::seed_seq seedsq{rd(), rd(), rd(), rd(), rd(), rd(), rd(), rd()}; // the occupation of filled value gets down
    std::mt19937 mt_seq{seedsq};

    std::cout <<"int:"<< Random::get(1, 8) << '\n';
    std::cout <<"uint:"<< Random::get(1u, 8u) << '\n';
    std::cout <<"mix:"<< Random::get<std::size_t>(1, 8u) << '\n';

    // play a dice with 6 faces
    std::uniform_int_distribution d1ce_6{1, 6};// create a reusable random number generator
                                            // that generates uniform numbers bettween 1 and 6

    for (int i = 1; i < 41; ++i)
    {
        //std::cout << mt() << '\t'; // boost the engine to creat a random number
                                   //mt() is a consise syntax for mt.operator()

        // std::cout << d1ce_6(mt_seq) << '\t';
        std::cout << d1ce_6(Random::mt) << '\t'; // make the random number distribution to be uniform distribution
             // aka. d1ce_6{1,6}(Random::mt)
        if(i%5==0)
            std::cout << '\n';

    }

    return 0;
}

