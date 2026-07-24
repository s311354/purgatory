#ifndef QUERY_H
#define QUERY_H

#include "purgatory.h"

namespace query {

class QueryResult;

class TextQuery {
public:
  using line_no = vector<string>::size_type;

  explicit TextQuery(ifstream &);

  QueryResult query(const string &) const;

private:
  shared_ptr<vector<string>> file;
  map<string, shared_ptr<set<line_no>>> wm;

  shared_ptr<vector<string>> handlePunct(const string &);
};

class QueryResult {
  friend ostream &print(ostream &, const QueryResult &);

public:
  QueryResult(const string &s, shared_ptr<set<TextQuery::line_no>> p,
              shared_ptr<vector<string>> f)
      : sought(s), lines(p), file(f) {}

  set<TextQuery::line_no>::iterator begin() { return lines->begin(); }

  set<TextQuery::line_no>::iterator end() { return lines->end(); }

  shared_ptr<vector<string>> get_file() const { return file; }

private:
  string sought;
  shared_ptr<set<TextQuery::line_no>> lines;
  shared_ptr<vector<string>> file;
};

/*
 * Its role is to serve as the root of our query hierarchy. It is the abstract
 * base class.
 */
class Query_base {
  friend class Query;

protected:
  using line_no = TextQuery::line_no;

  virtual ~Query_base() = default;

private:
  virtual QueryResult eval(const TextQuery &) const = 0;
  virtual std::string rep() const = 0;
};

/*
 *  An interface class hides the hierarchy. It is the handle class that users
 * interact with.
 */
class Query {
  friend Query operator~(const Query &);
  friend Query operator|(const Query &, const Query &);
  friend Query operator&(const Query &, const Query &);

public:
  explicit Query(const string &);

  // call QueryResult's default copy constructor
  QueryResult eval(const TextQuery &t) const { return q->eval(t); }
  string rep() const { return q->rep(); }

private:
  Query(shared_ptr<Query_base> query) : q(query) {}
  shared_ptr<Query_base> q;
};

// Derived classes
class WordQuery : public Query_base {
  friend class Query;

  explicit WordQuery(const string &s) : query_word(s) {}

  QueryResult eval(const TextQuery &t) const override {
    return t.query(query_word);
  }
  string rep() const override { return query_word; }

  string query_word;
};

class NotQuery : public Query_base {
  friend Query operator~(const Query &);

  explicit NotQuery(const Query &q) : query(q) {}

  QueryResult eval(const TextQuery &) const override;
  string rep() const override { return "~(" + query.rep() + ")"; }

  Query query;
};

class BinaryQuery : public Query_base {
protected:
  BinaryQuery(const Query &l, const Query &r, const string &s)
      : lhs(l), rhs(r), opSym(s) {}
  string rep() const override {
    return "(" + lhs.rep() + " " + opSym + " " + rhs.rep() + ")";
  }

  Query lhs, rhs;
  string opSym;
};

class AndQuery : public BinaryQuery {
  friend Query operator&(const Query &, const Query &);
  AndQuery(const Query &left, const Query &right)
      : BinaryQuery(left, right, "&") {}

  QueryResult eval(const TextQuery &) const override;
};

class OrQuery : public BinaryQuery {
  friend Query operator|(const Query &, const Query &);
  OrQuery(const Query &left, const Query &right)
      : BinaryQuery(left, right, "|") {}

  QueryResult eval(const TextQuery &) const override;
};

ostream &operator<<(ostream &os, const Query &query);
string printToString(const QueryResult &qr);

inline Query::Query(const string &s) : q(new WordQuery(s)) {}

inline Query operator~(const Query &operand) {
  return shared_ptr<Query_base>(new NotQuery(operand));
}

inline Query operator&(const Query &lhs, const Query &rhs) {
  return shared_ptr<Query_base>(new AndQuery(lhs, rhs));
}

inline Query operator|(const Query &lhs, const Query &rhs) {
  return shared_ptr<Query_base>(new OrQuery(lhs, rhs));
}

} // namespace query

#endif // QUERY_H
