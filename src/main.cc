#include "purgatory.h"
#include "query.h"

namespace purgatory {

using namespace query;

template <typename E>
int purgatory_main(int argc, char **argv) {

    purgatory::Purgatory solutions;

    vector<int> nums = {1, 2, 3, 4, 5};

    cout << solutions.increasingTriplet(nums) << endl;

    cout << "ch 15.9 Text Queries" << endl;

    ifstream fin(argv[1]);
    TextQuery text(fin);

    Query q = ~Query("Alice");

    cout << "Executing Query for: " << q.rep() << endl;

    QueryResult result = q.eval(text);

    print(cout, result);

    cout << endl;

    q = Query("fiery") & Query("bird") | Query("wind");

    cout << "Executing Query for: " << q.rep() << endl;

    result = q.eval(text);

    print(cout, result);

    cout << endl;

    return 0;
}

using E = PURGATORY_TARGET;

template int purgatory_main<E>(int, char **);

} /* namespace purgatory */
