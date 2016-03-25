#include "RegistrarURIList.hpp"


namespace BitProfile{


RegistrarURIList::RegistrarURIList(size_t size) :
    _size(size)
{}


RegistrarURIList::Iterator RegistrarURIList::begin() const
{
    return Iterator(0, _size);
}


RegistrarURIList::Iterator RegistrarURIList::end() const
{
    return Iterator(_size, _size);
}


RegistrarURIList::Iterator RegistrarURIList::at(size_t index) const
{
    return Iterator(index>_size?_size:index, _size);
}


RegistrarURIListIterator::RegistrarURIListIterator(size_t index, size_t limit) :
    _index(index),
    _limit(limit)
{}


void RegistrarURIListIterator::increment()
{
    _index++;
}


void RegistrarURIListIterator::decrement()
{
    _index--;
}


bool RegistrarURIListIterator::equal(const RegistrarURIListIterator &it) const
{
    return _index==it._index;
}


RegistrarURI RegistrarURIListIterator::dereference() const
{
    return RegistrarURI(_index);
}


}
