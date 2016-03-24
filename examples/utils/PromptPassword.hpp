#pragma once

#include <iostream>

#include "SetStdinEcho.hpp"


inline std::string PromptPassword()
{
    SetStdinEcho(false);
    std::string password;
    std::cout<<"password : "<<std::flush;
    std::cin>>password;
    std::cout<<std::endl;
    SetStdinEcho(true);
    return password;
}
