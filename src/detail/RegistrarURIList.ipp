namespace BitProfile{


class RegistrarURIListIterator : 
    public boost::iterator_facade
    <
        RegistrarURIListIterator,
        RegistrarURI,
        boost::bidirectional_traversal_tag,
        RegistrarURI
    >
{
    public:
        RegistrarURIListIterator(size_t index, size_t limit);

        void increment();
        void decrement();

        RegistrarURI dereference() const;
        bool equal(const RegistrarURIListIterator &) const;

    private:
        size_t _index;
        size_t _limit;
};


}
