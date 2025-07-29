
#ifndef PURGATORY_H
#define PURGATORY_H

#include <iostream>
using namespace std;

// STL Containers
#include <vector>

#include <string_view>
#include <climits>


namespace purgatory {


struct X86_64 {
    static constexpr std::string_view name = "x86_64";
};

struct I386 {
    static constexpr std::string_view name = "i386";
};

struct ARM64LE {
    static constexpr std::string_view name = "arm64";
};

class Purgatory {


public:

    Purgatory();
    Purgatory(istream& s);

    virtual ~Purgatory();

    bool increasingTriplet(vector<int>& nums);

};

template <typename E>
int purgatory_main(int argc, char **argv);

} /* namespace purgatory */


#endif /* PURGATORY_H */
