#include <iostream>
#include "bitprofile/ProfileStore.hpp"


int main()
{
    BitProfile::ProfileStore store;

    for(BitProfile::ProfileStore::Iterator it = store.begin(), end = store.end(); it!=end; ++it)
    {
        BitProfile::ProfileDescriptor profile = *it;
        std::cout<<" * "<<profile.getName()<<" ("<<profile.getContext()<<")"<<std::endl;
    }

    return 0;
}
