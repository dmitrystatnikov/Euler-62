#include <algorithm>
#include <cstdlib>
#include <iostream>
#include <map>
#include <vector>

using namespace std;

class Collection
{
public:
    using container = map< vector<size_t>, vector< pair<unsigned long long, size_t> > >;
    using key_type = container::key_type;
    using mapped_type = container::mapped_type;
    using iterator = container::iterator;
    using const_iterator = container::const_iterator;

    void add(unsigned long long cube, size_t n)
    {
        auto key = calculate_key(cube);
        i_collection[key].push_back(make_pair(cube, n));
    }

    const_iterator begin() const {return i_collection.begin();}
    const_iterator cbegin() {return i_collection.cbegin();}
    iterator begin() {return i_collection.begin();}
    const_iterator end() const {return i_collection.end();}
    const_iterator cend() {return i_collection.cend();}
    iterator end() {return i_collection.end();}

private:
    key_type calculate_key(unsigned long long cube) const
    {
        key_type result;
        while (cube > 0)
        {
            result.push_back(cube % 10);
            cube /= 10;
        }
        make_heap(result.begin(), result.end());
        sort_heap(result.begin(), result.end());
        return result;
    }

    container i_collection;
};

ostream & operator << (ostream & os, Collection::mapped_type const & val)
{
    for (auto const & p : val)
    {
        os << " " << p.first << ", " << p.second;
    }
    return os;
}

int main(int argc, char *argv[])
{
    Collection permutations;
    for (size_t n = 5; n < 10000; ++n)
    {
        size_t cube = n * n * n;
        permutations.add(cube, n);
    }

    for (auto const & permutation : permutations)
    {
        if (permutation.second.size() > 2)
        {
            cout << permutation.second.size() << ": " << permutation.second << endl;
        }
    }
    return 0;
}