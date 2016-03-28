#include "ProfileIterator.hpp"


namespace BitProfile{


ProfileIterator::ProfileIterator()
{}


ProfileIterator::ProfileIterator(fs::directory_iterator it) : 
    Base(it)
{}


fs::path ProfileIterator::path() const
{
    return base()->path();
}


ProfileDescriptor ProfileIterator::dereference() const
{
    Json::Value data;
    Json::Reader reader;
    std::ifstream stream(base()->path().string().c_str());
    if(!stream)
    {
        throw std::runtime_error("failed to read file");
    }
    std::string content;
    stream.seekg(0, std::ios::end);
    content.resize(stream.tellg());
    stream.seekg(0, std::ios::beg);
    stream.read(&content[0], content.size());
    stream.close();
    if(!reader.parse(content, data, false))
    {
        throw std::runtime_error("invalid file format");
    }
    
    return ProfileDescriptor(data);
}


}
