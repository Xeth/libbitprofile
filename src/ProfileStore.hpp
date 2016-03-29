#pragma once

#include <boost/filesystem.hpp>
#include "detail/ProfileIterator.hpp"
#include "Network.hpp"
#include "ProfileDescriptor.hpp"


namespace BitProfile{


namespace fs = boost::filesystem;



class ProfileStore
{
    public:
        typedef ProfileIterator Iterator;

    public:
        ProfileStore();
        ProfileStore(Network );
        ProfileStore(const char *path);
        ProfileStore(const fs::path &);

        bool insert(const ProfileDescriptor &);

        bool contains(const char *name) const;
        Iterator find(const char *name) const;
        Iterator begin() const;
        Iterator end() const;

    private:
        void createIfNotExists();
        fs::path getDefaultPath(Network) const;
        fs::path makeProfilePath(const std::string &name) const;

    private:
        fs::path _path;
};



}

