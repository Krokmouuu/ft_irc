#pragma once

#include "headers.hpp"

class Data
{

    public :

        Data() {};
        Data(const Data &params)
        {
            *this = params;
        };
        Data &operator=(const Data &params)
        {
            if (this != &params)
            {
                this->username = params.username;
                this->password = params.password;
                this->nickname = params.nickname;
                this->number = params.number;
            }
            return *this;
        }
        ~Data() {};

    private :

    string username;
    string password;
    string nickname;
    int    number;

};