#include <iostream>
#include <map>
#include <random>

enum Personality
{
    SMART = 0,
    POLITE,
    GENEROUS,
    SOCIABLE
};

constexpr std::initializer_list<Personality> Personalities = {
    SMART, POLITE, GENEROUS, SOCIABLE 
};

std::string personality_to_string(Personality);

class Poll
{
private:
    Personality target;
    int FOR = 0;
    int AGAINST = 0;

public:
    Poll(Personality target)
    {
        this->target = target;
    }

    Personality get_target() { return target; }
    void vote_for() { FOR++; };
    void vote_against() { AGAINST++; };
    std::pair<std::string, int> get_result()
    {
        if (FOR > AGAINST)
            return std::make_pair("FOR", FOR);
        else
            return std::make_pair("AGAINST", AGAINST);
    };
};

class Person
{
private:
    bool isImpostor;
    Personality personality;

public:
    Person(bool isImpostor, Personality personality)
    {
        this->isImpostor = isImpostor;
        this->personality = personality;
    }

    std::string get_personality() { return personality_to_string(personality); }
    bool get_impostor() { return isImpostor; }

    void vote(Poll* poll)
    {
        if (personality == poll->get_target() && !isImpostor)
            poll->vote_for();
        else if (personality == poll->get_target() && isImpostor)
            poll->vote_against();
        else if (personality != poll->get_target() && !isImpostor)
            poll->vote_against();
        else
            poll->vote_for();
    }
};

int get_random_range(int, int);
Personality compute_personality(std::map<Personality, int>);
Person generate_person();

/* ---------- */

int main()
{
    Poll poll((Personality)(get_random_range(0, Personalities.size() - 1)));

    std::vector<Person> people;
    int impostors = 0;
    for (int i = 0; i < 100; i++)
    {
        people.push_back(generate_person());
        people.at(i).vote(&poll);
        if (people.at(i).get_impostor()) impostors++;
    }
    std::pair<std::string, int> poll_result = poll.get_result();
    std::cout << "Poll target: " << personality_to_string(poll.get_target()) << "\n" 
        << poll_result.first << " won with " << poll_result.second << " votes!" 
        << "\nThere were " << impostors << " impostors."
        << std::endl;
    return 0;
}

/* ---------- */

std::string personality_to_string(Personality p)
{
    switch (p)
    {
        case SMART:     return "SMART";
        case POLITE:    return "POLITE";
        case GENEROUS:  return "GENEROUS";
        case SOCIABLE:  return "SOCIABLE";
        default:        return std::to_string((int)p);
    }
}

int get_random_range(int a, int b)
{
    std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_int_distribution<std::mt19937::result_type> dist(a, b);
    return dist(rng);
}

Personality compute_personality(std::map<Personality, int> stats)
{
    std::map<Personality, int>::iterator it;
    std::pair<Personality, int> best;
    for (it = stats.begin(); it != stats.end(); it++)
        if (best.second < it->second)
            best = std::make_pair(it->first, it->second);
    return best.first;
}

Person generate_person()
{
    std::map<Personality, int> stats;
    for (Personality p : Personalities)
        stats.insert({p, get_random_range(-100, 100)});
   
    bool rand_impostor = [] {
        int rand = get_random_range(0, 10);
        if (rand == 0)      return true;
        else                return false;
    }();

    return Person(
            rand_impostor,
            compute_personality(stats)
            );
}
