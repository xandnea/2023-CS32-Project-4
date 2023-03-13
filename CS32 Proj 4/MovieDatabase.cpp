#include "MovieDatabase.h"
#include "Movie.h"

#include <string>
#include <vector>
#include <fstream>
#include <iostream>

using namespace std;

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
    float rating = 0;

    string s;
    while (getline(infile, s)) // can be optimized if needed
    {
        if (s.at(0) == 'I' && s.at(1) == 'D' && id == "") // if id
        {
            id = s;
            continue; // next line
        }
        else if (title  == "") // if title
        {
            title = s;
            continue; // next line
        }
        else if (isdigit(s.at(0)) && s.at(1) != '.' && year == "") // if year
        {
            year = s;
            continue;
        }
        else if (directors == "") // if directors
        {
            directors = s;
            continue;
        }
        else if (actors == "") // if actors
        {
            actors = s;
            continue;
        }
        else if (genres == "") // if genres
        {
            genres = s;
            continue;
        }
        else if (isdigit(s.at(0)) && rating == 0)
        {
            rating = stoi(s);
            continue;
        }
        else if (s == "\n") // if new line
        {
            Movie* movie = new Movie(id, title, year, directors, actors, genres, rating);
            insert_to_tmm(m_directors, directors, movie);
            insert_to_tmm(m_actors, actors, movie);
            insert_to_tmm(m_genres, genres, movie);

            id = "";
            title = "";
            year = "";
            directors = "";
            actors = "";
            genres = "";
            rating = 0;
            continue;
        }
    }

    return true;
}

Movie* MovieDatabase::get_movie_from_id(const string& id) const
{
    return m_movies.find(id).get_value();
}

vector<Movie*> MovieDatabase::get_movies_with_director(const string& director) const
{
    string temp = director;
    for (int i = 1; i < temp.size(); i++)
        tolower(temp.at(i));

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
    for (int i = 1; i < temp.size(); i++)
        tolower(temp.at(i));

    vector<Movie*> movies;
    TreeMultimap<string, Movie*>::Iterator it = m_directors.find(temp);
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
    for (int i = 1; i < temp.size(); i++)
        tolower(temp.at(i));

    vector<Movie*> movies;
    TreeMultimap<string, Movie*>::Iterator it = m_directors.find(temp);
    while (it.is_valid())
    {
        movies.push_back(it.get_value());
        it.advance();
    }

    return movies;
}

void MovieDatabase::insert_to_tmm(TreeMultimap<string, Movie*> tmm, string input, Movie* movie)
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
    return;
}