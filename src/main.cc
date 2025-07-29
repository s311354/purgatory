#include "purgatory.h"

namespace purgatory {

template <typename E>
int purgatory_main(int argc, char **argv) {

    purgatory::Purgatory solutions;

    vector<int> nums = {1, 2, 3, 4, 5};

    cout << solutions.increasingTriplet(nums) << endl;

    return 0;
}

using E = PURGATORY_TARGET;

template int purgatory_main<E>(int, char **);

} /* namespace purgatory */
