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
                this->users = params.users;
                this->users_fd = params.users_fd;
            }
            return *this;
        }
        ~Channel() {};

        string getname() const { return this->name; };
        vector<Data> vgetusers() const { return this->users; };
        Data getuser(int i) const { return this->users[i]; };
        vector<int> getusers_fd() const { return this->users_fd; };
        void removeuser(int i) { this->users.erase(this->users.begin() + i); };


        void setname(string name) { this->name = name; };
        void setusers(vector<Data> users) { this->users = users; };
        void adduser(Data user) { this->users.push_back(user); };
        void setusers_fd(int users_fd) { this->users_fd.push_back(users_fd); };
    private:

        string name;
        vector<Data> users;
        vector<int> users_fd;
};