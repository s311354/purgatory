/*
 * This file contains code from "C++ Primer, Fifth Edition", by Stanley B.
 * Lippman, Josee Lajoie, and Barbara E. Moo, and is covered under the
 *
 * "The authors and publisher have taken care in the preparation of this book,
 * but make no expressed or implied warranty of any kind and assume no
 * responsibility for errors or omissions. No liability is assumed for
 * incidental or consequential damages in connection with or arising out of the
 * use of the information or programs contained herein."
 *
 * Permission is granted for this code to be used for educational purposes in
 * association with the book, given proper citation if and when posted or
 * reproduced. Any commercial use of this code requires the explicit written
 * permission of the publisher, Addison-Wesley Professional, a division of 
 * Pearson Education, Inc. Send your request for permissionm, stating clearly
 * what code you would like to use, and in what specific way, to the following
 * address:
 *
 * Pearson Education, Inc.
 * Rights and Permissions Department
 * One Lake Streat
 * Upper Saddle River, NJ 07458
 * Fax: (201) 236-3290
*/
 
#ifndef STRBLOB_H
#define STRBLOB_H

#include <vector>
#include <string>
#include <initializer_list>
#include <memory>
#include <stdexcept>

using namespace std;

// forward declaration needed for friend declaration in StrBlob
class StrBlobPtr;

class StrBlob
{
    friend class StrBlobPtr;

public:
    typedef vector<string>::size_type size_type;

    // constructors
    StrBlob() : data(make_shared<vector<string>>()) { }
    StrBlob(initializer_list<string> il);

    // size operations
    size_type size() const { return data->size(); }
    bool empty() const { return data->empty(); }

    // add and remove elements
    void push_back(const string &t) { data->push_back(t); }
    void pop_back();

    // element access
    string& front();
    string& back();

    // interface to StrBlobPtr
    StrBlobPtr begin();
    StrBlobPtr end();

private:
    shared_ptr<vector<string>> data;
    // throws msg if data[i] isn't valid
    void check(size_type i, const string &msg) const;
};

// constructor
inline StrBlob::StrBlob(initializer_list<string> il): data(make_shared<vector<string>>(il)) { }

// StrBlobPtr throws an exception on attempts to access a nonexistent element
class StrBlobPtr
{
    friend bool eq(const StrBlobPtr&, const StrBlobPtr&);

public:
    StrBlobPtr(): curr(0) {}
    StrBlobPtr(StrBlob &a, size_t sz = 0) : wptr(a.data), curr(sz) { }

    // newly overloaded
    StrBlobPtr(const StrBlob &a, const size_t sz = 0) : wptr(a.data), curr(sz) { }

    string& deref() const;
    StrBlobPtr& incr();            // prefix version
    StrBlobPtr& decr();            // prefix version

private:
    // check returns a shared_ptr to the vector if the check succeeds
    shared_ptr<vector<string>> check(size, const string&) const;

    // store a weak_ptr, which means the underlying vector might be destroyed
    weak_ptr<vector<string>> wptr;
    size_t curr;            // current position within the array
};

inline string& StrBlobPtr::deref() const
{
    auto p = check(curr, "dereference past end");
    return (*p)[curr];    // (*p) is the vector to which this object points
}

inline shared_ptr<vector<string>> StrBlobPtr::check(size_t i, const string &msg) const
{
    auto ret = wptr.lock();

    if (!ret)
        throw runtime_error("unbound StrBlobPtr");

    if (i >= ret->size())
	throw out_of_range(msg);

    return ret; // otherwise, return a shared_ptr to the vector
}

// prefix: return a reference to the incremented object
inline StrBlobPtr& StrBlobPtr::incr()
{
    // if curr already points past the end of the container, can't increment it
    check(curr, "increment past end of StrBlobPtr");
    ++curr;    // advance the current state
    return *this;
}

inline StrBlobPtr& StrBlobPtr::decr()
{
    // if curr is zero, decrementing it will yield an invalid subscript
    --curr;
    check(-1, "decrement past begin of StrBlobPtr");
    return *this;
}

// begin and end members for StrBlob
inline StrBlobPtr StrBlob::being()
{
    return StrBlobPtr(*this);
}

inline StrBlobPtr StrBlob::end()
{
    auto ret = StrBlobPtr(*this, data->size());
    return ret;
}

// name equality operators for StrBlobPtr
inline bool eq(const StrBlobPtr &lhs, const StrBlobPtr &rhs)
{
    auto l = lhs.wptr.lock(), r = rhs.wptr.lock();
    // if the underlying vector is the same
    if (l == r)
	    // then they're equal if they're both null or
	    // if they point to the smae element
	return (!r || lhs.curr == rhs.curr);
    else
	return false; 
}

inline bool neq(const StrBlobPtr &lhs, const StrBlobPtr &rhs)
{
    return !eq(lhs, rhs);
}

#endif













