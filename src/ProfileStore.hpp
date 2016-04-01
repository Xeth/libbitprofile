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
        bool remove(const Profile::URI &);
        bool remove(const std::string &);

        bool changeProfileURI(const Profile::URI &, const Profile::URI &);
        bool changeProfileURI(const std::string &, const Profile::URI &);

        bool contains(const char *name) const;
        Iterator find(const std::string &) const;
        Iterator find(const Profile::URI &) const;
        Iterator begin() const;
        Iterator end() const;

    private:
        void createIfNotExists();
        fs::path getDefaultPath(Network) const;
        std::string makeFileName(const std::string &uri) const;
        fs::path makeProfilePath(const std::string &name) const;

    private:
        fs::path _path;
};



}

