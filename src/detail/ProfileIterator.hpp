#pragma once


#include <boost/iterator/iterator_adaptor.hpp>
#include <boost/filesystem.hpp>

#include <json/value.h>
#include <json/reader.h>
#include <string>
#include <fstream>


#include "../ProfileDescriptor.hpp"


namespace BitProfile{


namespace fs = boost::filesystem;


class ProfileIterator : 
        public boost::iterator_adaptor
        <
            ProfileIterator,
            fs::directory_iterator,
            ProfileDescriptor,
            boost::bidirectional_traversal_tag,
            ProfileDescriptor
        >
{
    public:
        typedef boost::iterator_adaptor
            <
                ProfileIterator,
                fs::directory_iterator,
                ProfileDescriptor,
                boost::bidirectional_traversal_tag,
                ProfileDescriptor
            > Base;

    public:
        ProfileIterator();
        ProfileIterator(fs::directory_iterator );

        ProfileDescriptor dereference() const;
        fs::path path() const;
};


}
