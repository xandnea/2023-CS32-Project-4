#include "Movie.h"

#include <string>
#include <vector>
#include <iostream>

using namespace std;

Movie::Movie(const string& id, const string& title,
    const string& release_year, const string& directors,
    const string& actors, const string genres, float rating)
{
    m_id = id;
    m_title = title;
    m_release_year = release_year;
    m_rating = rating;
    
    m_directors = string_to_vector(directors);
    m_actors = string_to_vector(actors);
    m_genres = string_to_vector(genres);
}

string Movie::get_id() const
{
    return m_id;
}

string Movie::get_title() const
{
    return m_title;
}

string Movie::get_release_year() const
{
    return m_release_year;
}

float Movie::get_rating() const
{
    return m_rating;
}

vector<string> Movie::get_directors() const
{
    return m_directors;
}

vector<string> Movie::get_actors() const
{
    return m_actors;
}

vector<string> Movie::get_genres() const
{
    return m_genres;
}

vector<string> Movie::string_to_vector(const string &input)
{
    string s = input;
    string temp = "";
    vector<string> output;
    
    if (s.find(',') == string::npos) // if comma not found in string
    {
        output.push_back(s);
        return output;
    }
    
    for (int i = 0; i < s.size(); i++)
    {
        if (s.at(i) != ',')
        {
            temp += s.at(i);
        }
        else
        {
            output.push_back(temp);
            temp = "";
        }
    }
    output.push_back(temp);

    return output;
}