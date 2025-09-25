#include "query.h"

namespace query {

string make_plural(size_t ctr, const string &word, const string &ending) {
    return (ctr > 1) ? word + ending : word;
}

TextQuery::TextQuery(ifstream &is): file(new vector<string>) {

    string text;
    
    while (getline(is, text)) {
        file->push_back(text);
	int n = file->size() - 1;
	istringstream line(text);
	string word;

	while ( line >> word ) {

            auto p = handlePunct(word);

	    for (auto w : *p) {

                auto &lines = wm[w];

	        if (!lines) lines.reset(new set<line_no>);
	        lines->insert(n);
	    }
	}
    }

}

QueryResult TextQuery::query(const string &sought) const {
    static shared_ptr<set<line_no>> nodata(new set<line_no>);

    auto loc = wm.find(sought);

    if (loc == wm.end()) {
        return QueryResult(sought, nodata, file);
    } else {
        return QueryResult(sought, loc->second, file);
    }
}

shared_ptr<vector<string>> TextQuery::handlePunct(const string &s) {
    shared_ptr<vector<string>> p = make_shared<vector<string>>();

    size_t first = 0, index = 0;

    while (index != s.size()) {
        if (ispunct(s[index])) {
            string word = s.substr(first, index - first);

	    if (!word.empty()) p->push_back(word);

	    p->push_back(s.substr(index, 1));

	    ++index;
	    first = index;
	} else {
	    ++index;
	}
    }

    string trail = s.substr(first);

    if (!trail.empty()) p->push_back(trail);

    return p;
}

QueryResult OrQuery::eval(const TextQuery& text) const {
    auto right = rhs.eval(text), left = lhs.eval(text);

    auto ret_lines = make_shared<set<line_no>>(left.begin(), left.end());

    ret_lines->insert(right.begin(), right.end());

    return QueryResult(rep(), ret_lines, left.get_file());
}

QueryResult NotQuery::eval(const TextQuery& text) const {
    auto result = query.eval(text);

    auto ret_lines = make_shared<set<line_no>>();

    auto beg = result.begin(), end = result.end();

    auto sz = result.get_file()->size();

    for (size_t n = 0; n != sz; ++n) {
        if (beg == end || *beg != n)
            ret_lines->insert(n);
	else if (beg != end)
	    ++beg;
    }

    return QueryResult(rep(), ret_lines, result.get_file());
}

QueryResult AndQuery::eval(const TextQuery& text) const {
    auto left = lhs.eval(text), right = rhs.eval(text);

    auto ret_lines = make_shared<set<line_no>>();

    set_intersection(left.begin(), left.end(), right.begin(), right.end(), inserter(*ret_lines, ret_lines->begin()));

    return QueryResult(rep(), ret_lines, left.get_file());
}

ostream &print(ostream& os, const QueryResult &qr) {
    os << qr.sought << " occurs " << qr.lines->size() << " "
       << make_plural(qr.lines->size(), "time", "s") << endl;

    for (const auto &num : *qr.lines) {
        os << "\t(line " << num + 1 << ") "
	   << *(qr.file->begin() + num) << endl;
    }

    return os;
}

string printToString(const QueryResult &qr) {
    ostringstream oss;
    print(oss, qr);
    return oss.str();
}

ostream &operator<<(ostream &os, const Query &query) {
    return os << query.rep();
}

}
