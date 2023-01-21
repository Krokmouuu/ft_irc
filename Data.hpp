#pragma once

using namespace std;

class Data
{

    public :

        Data()
        {
            this->username = "";
            this->nickname = "";
            this->logged = 0;
            this->number = 0;
        }
        Data(const Data &params)
        {
            *this = params;
        };
        Data &operator=(const Data &params)
        {
            if (this != &params)
            {
                this->username = params.username;
                this->nickname = params.nickname;
                this->logged = params.logged;
                this->number = params.number;
            }
            return *this;
        }
        ~Data() {};
    
    string getusername() const { return this->username; };
    string getnickname() const { return this->nickname; };
    int    getlog() const { return this->logged; };
    int    getnumber() const { return this->number; };

    void    setusername(string username) { this->username = username; };
    void    setnickname(string nickname) { this->nickname = nickname; };
    void    setlog(int logged) { this->logged = logged; };
    void    setnumber(int number) { this->number = number; };

    private :

    string username;
    string nickname;
    int    logged;
    int    number;

};