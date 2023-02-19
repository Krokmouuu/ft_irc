#include "ft_irc.hpp"
#include <curl/curl.h>

string extract_text_from_response(string response) {
	size_t start = response.find("\"text\":\"");
	if (start == string::npos)
		return "";
	start += 8;
	size_t end = response.find('"', start);
	if (end == string::npos)
		return "";

	string result = response.substr(start, end - start);
	string realresult;
    for (size_t i = 0; i < result.length(); i++)
	{
        if (result[i] != '\\' || (i < result.length() - 1 && result[i + 1] != 'n')) {
            realresult += result[i];
        } else {
            i++;
        }
    }
	return realresult;
}

size_t write_callback(char *ptr, size_t size, size_t nmemb, string *userdata) {
	size_t bytes = size * nmemb;
	userdata->append(ptr, bytes);
	return bytes;
}

string gpt(string message) {
    CURL *curl;
    CURLcode res;
    curl = curl_easy_init();
    if (curl)
	{
        curl_easy_setopt(curl, CURLOPT_URL, "https://api.openai.com/v1/engines/text-davinci-001/completions");

		string json_body = "{\"prompt\":\"" + message + "\",\"temperature\":0.6,\"max_tokens\":200,\"top_p\":0.9,\"frequency_penalty\":0.5,\"presence_penalty\":0.3}";

        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, json_body.c_str());
        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0L);

        curl_slist *headers = nullptr;
        headers = curl_slist_append(headers, "Content-Type: application/json");
    	headers = curl_slist_append(headers, "Authorization: Bearer YOURKEYHERE");
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);

        string response;
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_callback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);
        res = curl_easy_perform(curl);
        if (res != CURLE_OK)
            fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));

        string generated_text = extract_text_from_response(response);
        curl_slist_free_all(headers);
        curl_easy_cleanup(curl);
		return generated_text;
    }
    return (NULL);
}

void stop_bot_command(Bot *bot, int user)
{
    if (bot->getstop() == 0)
    {
        send(user, "Bot stopped.\n", 14, 0);
        bot->setstop(1);
    }
    else
    {
        send(user, "Bot started.\n", 14, 0);
        bot->setstop(0);
    }
}

void fun_bot_command(string input, Bot *bot, int user)
{
    stringstream ss(input);
    string word;
    for (size_t i = 0; i < 2; i++)
        ss >> word;
    if (word == "on" || word == "ON")
    {
        send(user, "Bot fun mode activated.\n", 25, 0); 
        bot->setfun(1);
    }
    else if (word == "off" || word == "OFF")
    {
        send(user, "Bot fun mode deactivated.\n", 27, 0);
        bot->setfun(0);
    }
    else
        send(user, "Invalid argument.\n", 19, 0);
}

void nick_bot_command(string input, Bot *bot, int user)
{
    stringstream ss(input);
    string word;
    for (size_t i = 0; i < 2; i++)
        ss >> word;
    if (word.length() < 2)
    {
        send(user, "Bot nickname too short.\n", 25, 0);
        return ;
    }
    else if (word == "!nick")
    {
        send(user, "Invalid nickname.\n", 19, 0);
        return ;
    }
    word = word + "[BOT]";
    bot->setname(word);
    send(user, "Bot nickname changed.\n", 23, 0);
}

void join_bot_command(string input, Bot *bot, int user, vector<Channel> *chan)
{
    stringstream ss(input);
    string word;
    string tmp;
    for (size_t i = 0; i < 2; i++)
        ss >> word;
    if (bot->getchannel() == word)
    {
        send(user, "Bot already in this channel.\n", 30, 0);
        return ;
    }
    for (size_t j = 0; j < chan->size(); j++)
    {
        if (chan->at(j).getname() == word)
        {
            for (size_t k = 0; k < chan->size(); k++)
                if (chan->at(k).getname() == bot->getchannel())
                    for (size_t l = 0; l < chan->at(k).vgetusers().size(); l++)
                    {
                        tmp = "\033[38;5;120m" + bot->getname() + " has left the channel.\033[0m\n";
                        send(chan->at(k).getuser(l).getfd(), tmp.c_str(), tmp.size(), 0);
                    }
            for(size_t i = 0; i < chan->at(j).vgetusers().size(); i++)
            {
                tmp = "\033[38;5;120m" + bot->getname() + " has joined the channel.\033[0m\n";
                send(chan->at(j).getuser(i).getfd(), tmp.c_str(), tmp.size(), 0);
            }
            bot->setchannel(word);
            return ;
        }
    }
    send(user, "Channel does not exist.\n", 25, 0);
}
//! debloquer les commandes autre que !gpt hihihi
void beep_beep_boop(string input, int user, vector<Data> *data, vector<Channel> *chan, Bot *bot)
{
    string tmp;
    stringstream ss(input);
    stringstream tt(input);
    string word;
	tt >> word;
	if (word == "!gpt")
	{
		if (input.length() > 1)
		{
			string resultgpt = gpt(&input[5]);
			string result = "\033[38;5;104m" + bot->getname() + "\033[0m: ";
			result += resultgpt;
			result += "\n";
			for (size_t i = 0; i < chan->size(); i++)
					{
						if (chan->at(i).getname() == bot->getchannel())
						{
							for (size_t j = 0; j < chan->at(i).vgetusers().size(); j++)
								send(chan->at(i).getuser(j).getfd(), result.c_str(), result.size(), 0);
							break ;
						}
					}
		}
	}

    if (bot->getfun() == 1)
    {
        while (ss >> word)
        {
            if (word == "!joke")
            {
                int rand = std::rand() % 5;
                if (rand == 0)
                    tmp = "C'est l'histoire d'un pingouin qui respire par les fesses.\nUn jour il s'asseoit et il meurt.\n";
                else if (rand == 1)
                    tmp = "Pourquoi les canards sont toujours à l'heure ?\nParce qu’ils sont dans l’étang.\n";
                else if (rand == 2)
                    tmp = "Que fait un crocodile quand il rencontre une superbe femelle ?\nIl Lacoste.\n";
                else if (rand == 3)
                    tmp = "C'est l'histoire de 2 patates qui traversent la route.\nL’une d’elles se fait écraser. L’autre dit : « Oh purée ! »\n";
                else if (rand == 4)
                    tmp = "C'est l'histoire d'un zoophile qui prend son élan.\n";
                for (size_t i = 0; i < chan->size(); i++)
                {
                    if (chan->at(i).getname() == bot->getchannel())
                    {
                        for (size_t j = 0; j < chan->at(i).vgetusers().size(); j++)
                            send(chan->at(i).getuser(j).getfd(), tmp.c_str(), tmp.size(), 0);
                        break ;
                    }
                }
                return;
            }
            if (word == "quoi" || word == "QUOI" || word == "Quoi" || word == "quoi?" || word == "QUOI?" || word == "Quoi?" || word == "koi" || word == "Koi")
            {
                for (size_t i = 0; i < chan->size(); i++)
                {
                    tmp = bot->getname() + ": feur @" + data->at(user - 4).getnickname() + " XD\n";
                    for (size_t j = 0; j < chan->at(i).vgetusers().size(); j++)
                        send(chan->at(i).getuser(j).getfd(), tmp.c_str(), tmp.size(), 0);
                }
            }
            else if (word == "qui" || word == "QUI" || word == "Qui" || word == "qui?" || word == "QUI?" || word == "Qui?" || word == "ki")
            {
                for (size_t i = 0; i < chan->size(); i++)
                {
                    tmp = bot->getname() + ": qui ? quette @" + data->at(user - 4).getnickname() + " XD\n";
                    for (size_t j = 0; j < chan->at(i).vgetusers().size(); j++)
                        send(chan->at(i).getuser(j).getfd(), tmp.c_str(), tmp.size(), 0);
                }
            }
        }
    }
}