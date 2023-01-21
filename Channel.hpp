#pragma once

#include "ft_irc.hpp"
#include "Data.hpp"

class Channel
{
    public:
        Channel(string name) : name(name) {};
        Channel(const Channel &params)
        {
            this->name = params.name;
            return ;
        }
        Channel &operator=(const Channel &params)
        {
            if (this != &params)
            {
                this->name = params.name;
            }
            return *this;
        }
        ~Channel() {};

        string getname() const { return this->name; };
        vector<Data> getusers() const { return this->users; };

        void setname(string name) { this->name = name; };
        void setusers(vector<Data> users) { this->users = users; };

    private:

        string name;
        vector<Data> users;
};