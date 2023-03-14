#include "MovieDatabase.h"
#include "Movie.h"

#include <string>
#include <vector>
#include <fstream>
#include <iostream>

using namespace std;

string to_lower(const string& input);

MovieDatabase::MovieDatabase()
{
    
}

bool MovieDatabase::load(const string& filename)
{
    ifstream infile(filename);
    if (!infile)
    {
        cerr << "Error: Cannot open " + filename + "!" << endl;
        return false;
    }

    string id = "";
    string title = "";
    string year = "";
    string directors = "";
    string actors = "";
    string genres = "";
    float rating = -1;

    string s;
    while (getline(infile, s)) // can be optimized if needed
    {
        if (id == "") // if id
        {
            id = s;
            //cout << id << endl;
            continue; // next line
        }
        else if (title  == "") // if title
        {
            title = s;
            //cout << title << endl;
            continue; // next line
        }
        else if (year == "") // if year
        {
            year = s;
            //cout << year << endl;
            continue;
        }
        else if (directors == "") // if directors
        {
            directors = to_lower(s);
            //cout << directors << endl;
            continue;
        }
        else if (actors == "") // if actors
        {
            actors = to_lower(s);
            //cout << actors << endl;
            continue;
        }
        else if (genres == "") // if genres
        {
            genres = to_lower(s);
            //cout << genres << endl;
            continue;
        }
        else if (rating == -1)
        {
            rating = stoi(s);
            //cout << rating << endl;
            continue;
        }
        else if (s == "") // if new line
        {
            Movie* movie = new Movie(id, title, year, directors, actors, genres, rating);
            insert_to_tmm(m_movies, id, movie);
            insert_to_tmm(m_directors, directors, movie);
            insert_to_tmm(m_actors, actors, movie);
            insert_to_tmm(m_genres, genres, movie);

            id = "";
            title = "";
            year = "";
            directors = "";
            actors = "";
            genres = "";
            rating = -1;
            continue;
        }
    }

    return true;
}

Movie* MovieDatabase::get_movie_from_id(const string& id) const
{
    if ((m_movies.find(id).is_valid()))
        return m_movies.find(id).get_value();
    else
        return nullptr;
    
}

vector<Movie*> MovieDatabase::get_movies_with_director(const string& director) const
{
    string temp = director;

    for (int i = 0; i < director.size(); i++)
        temp.at(i) = tolower(temp.at(i));

    vector<Movie*> movies;
    TreeMultimap<string, Movie*>::Iterator it = m_directors.find(temp);
    while (it.is_valid())
    {
        movies.push_back(it.get_value());
        it.advance();
    }

    return movies;
}

vector<Movie*> MovieDatabase::get_movies_with_actor(const string& actor) const
{
    string temp = actor;

    for (int i = 0; i < actor.size(); i++)
        temp.at(i) = tolower(temp.at(i));

    vector<Movie*> movies;
    TreeMultimap<string, Movie*>::Iterator it = m_actors.find(temp);
    while (it.is_valid())
    {
        movies.push_back(it.get_value());
        it.advance();
    }

    return movies;
}

vector<Movie*> MovieDatabase::get_movies_with_genre(const string& genre) const
{
    string temp = genre;

    for (int i = 0; i < genre.size(); i++)
        temp.at(i) = tolower(temp.at(i));

    vector<Movie*> movies;
    TreeMultimap<string, Movie*>::Iterator it = m_genres.find(temp);
    while (it.is_valid())
    {
        movies.push_back(it.get_value());
        it.advance();
    }

    return movies;
}

void MovieDatabase::insert_to_tmm(TreeMultimap<string, Movie*>& tmm, string input, Movie* movie)
{
    string s = input;
    string temp = "";

    if (s.find(',') == string::npos) // if comma not found in string
    {
        tmm.insert(s, movie);
        return;
    }

    for (int i = 0; i < s.size(); i++)
    {
        if (s.at(i) != ',')
        {
            temp += tolower(s.at(i));
        }
        else // if comma
        {
            tmm.insert(temp, movie);
            temp = "";
        }
    }
    tmm.insert(temp, movie);
    return;
}

string MovieDatabase::to_lower(const string& input)
{
    string temp = input;
    for (int i = 0; i < input.size(); i++)
        temp.at(i) = tolower(temp.at(i));
    return temp;
}