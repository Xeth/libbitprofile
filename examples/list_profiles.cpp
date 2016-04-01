#include <iostream>
#include "bitprofile/ProfileStore.hpp"


int main()
{
    BitProfile::ProfileStore store(BitProfile::Test_Net);

    for(BitProfile::ProfileStore::Iterator it = store.begin(), end = store.end(); it!=end; ++it)
    {
        BitProfile::ProfileDescriptor profile = *it;
        std::cout<<" * "<<profile.getName()<<" ("<<profile.getContext()<<")"<<std::endl;
    }

    return 0;
}
