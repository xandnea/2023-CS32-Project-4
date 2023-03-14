#include "Recommender.h"
#include "UserDatabase.h"
#include "MovieDatabase.h"

#include "User.h"
#include "Movie.h"

#include <string>
#include <vector>
#include <map>

using namespace std;

vector<MovieAndRank> sortByRating(vector<MovieAndRank>& input);
vector<MovieAndRank> sortByTitle(vector<MovieAndRank>& input);

Recommender::Recommender(const UserDatabase& user_database,
    const MovieDatabase& movie_database)
{
    m_userdata = &user_database;
    m_moviedata = &movie_database;
}

vector<MovieAndRank> Recommender::recommend_movies(const string& user_email, int movie_count)
{
    vector<MovieAndRank> ratings;
    vector<string> ids;
    vector<string>::iterator it = ids.begin();

    User* user = m_userdata->get_user_from_email(user_email);
    vector<string> movieIDs = user->get_watch_history();

    vector<Movie*> movies;
    for (int i = 0; i < movieIDs.size(); i++)
        movies.push_back(m_moviedata->get_movie_from_id(movieIDs[i]));
    
    for (int i = 0; i < movies.size(); i++) // for each movie the user has watched
    {
        vector<string> directors = movies[i]->get_directors(); // vector of directors
        for (int j = 0; j < directors.size(); j++) // for each director in the movie
        {
            vector<Movie*> movies_with_director = m_moviedata->get_movies_with_director(directors[j]); // vector of movies w/ that director 
            for (int k = 0; k < movies_with_director.size(); k++) // for each movie that director has made
            {
                MovieAndRank movieWithScore(movies_with_director[i]->get_id(), 20);
                it = find(ids.begin(), ids.end(), movieWithScore.movie_id);
                if (it == ids.end())
                {
                    ratings.push_back(movieWithScore);
                    ids.push_back(movieWithScore.movie_id);
                }
                else
                {
                    ratings[it - ids.begin()].compatibility_score += 20;
                }
                
            }
        }

        vector<string> actors = movies[i]->get_actors(); // vector of actors
        for (int j = 0; j < actors.size(); j++) // for each actor in the movie
        {
            vector<Movie*> movies_with_actor = m_moviedata->get_movies_with_actor(actors[j]); // vector of movies w/ that actor
            for (int k = 0; k < movies_with_actor.size(); k++)
            {
                MovieAndRank movieWithScore(movies_with_actor[i]->get_id(), 30);
                it = find(ids.begin(), ids.end(), movieWithScore.movie_id);
                if (it == ids.end())
                {
                    ratings.push_back(movieWithScore);
                    ids.push_back(movieWithScore.movie_id);
                }
                else
                {
                    ratings[it - ids.begin()].compatibility_score += 30;
                }
            }
        }

        vector<string> genres = movies[i]->get_genres(); // vector of genres
        for (int j = 0; j < genres.size(); j++) // for each genre in the movie
        {
            vector<Movie*> movies_with_genre = m_moviedata->get_movies_with_genre(genres[j]); // vector of movies w/ that genre 
            for (int k = 0; k < movies_with_genre.size(); k++)
            {
                MovieAndRank movieWithScore(movies_with_genre[i]->get_id(), 1);
                it = find(ids.begin(), ids.end(), movieWithScore.movie_id);
                if (it == ids.end())
                {
                    ratings.push_back(movieWithScore);
                    ids.push_back(movieWithScore.movie_id);
                }
                else
                {
                    ratings[it - ids.begin()].compatibility_score += 1;
                }
            }
        }
    }


    multimap<int, MovieAndRank> sortedMovies;
    multimap<int, MovieAndRank>::iterator itr = sortedMovies.begin();

    for (int i = 0; i < ratings.size(); i++)
    {
        sortedMovies.insert({ ratings[i].compatibility_score, ratings[i] });
    }

    ratings.clear();

    for (itr; itr != sortedMovies.end(); itr++)
    {
        // if id of movieandrank is not found in vector of users' watched movies and compatibility score is greater than 1
        if (find(movieIDs.begin(), movieIDs.end(), itr->second.movie_id) == movieIDs.end() && itr->second.compatibility_score > 1) 
        {
            ratings.push_back(itr->second);
        }
    }

    /*cout << "Ratings: " << endl;
    for (int i = 0; i < ratings.size(); i++)
        cout << ratings[i].movie_id << ", " << ratings[i].compatibility_score << endl;*/

    vector<MovieAndRank> output;
    vector<MovieAndRank> temp;

    for (int i = 1; i < ratings.size(); i++)
    {   
        // if comp score of i is greater than comp score of i + 1
        if ((ratings[i - 1].compatibility_score > ratings[i].compatibility_score))
        {
            if (!temp.empty())
            {
                temp.push_back(ratings[i - 1]);
                
                /*for (int i = 0; i < temp.size(); i++)
                {
                    cout << temp[i].movie_id << endl;
                }*/

                temp = sortByRating(temp);
                for (int i = 0; i < temp.size(); i++)
                {
                    output.push_back(temp[i]);
                }
                temp.clear();
            }
            else
                output.push_back(ratings[i - 1]); // push id of movie to output
        }
        else // if equal (can't be less than because it should be sorted) or there's a movie in the temp vector
            temp.push_back(ratings[i - 1]);
    }

    vector<MovieAndRank> result;
    int resultCount;
    if (movie_count > output.size())
        resultCount = output.size();
    else
        resultCount = movie_count;

    for (int i = 0; i < resultCount; i++)
        result.push_back(output[i]);

    return result;  // Replace this line with correct code.
}

vector<MovieAndRank> Recommender::sortByRating(vector<MovieAndRank>& input)
{
    vector<MovieAndRank> output;
    vector<MovieAndRank> temp;
    vector<Movie*> movies;

    multimap<float, MovieAndRank> sortedRating;
    multimap<float, MovieAndRank>::iterator itr1 = sortedRating.begin();
    multimap<float, MovieAndRank>::iterator itr2 = sortedRating.begin();
    itr2++;

    for (int i = 0; i < input.size(); i++)
        movies.push_back(m_moviedata->get_movie_from_id(input[i].movie_id));

    for (int i = 0; i < movies.size(); i++) // insert into multimap to sort
        sortedRating.insert({ movies[i]->get_rating(), input[i] });

    for ( ; itr2 != sortedRating.end(); itr1++, itr2++)
    {
        if (itr1->first == itr2->first) 
            temp.push_back(itr1->second);
        else
        {
            if (!temp.empty())
            {
                temp.push_back(itr1->second);
                temp = sortByTitle(temp);
                for (int i = 0; i < temp.size(); i++)
                {
                    output.push_back(temp[i]);
                }
                temp.clear();
            }
            else
                output.push_back(itr1->second);
        }
    }

    if (!temp.empty())
    {
        temp.push_back(itr1->second);
        temp = sortByTitle(temp);
        for (int i = 0; i < temp.size(); i++)
        {
            output.push_back(temp[i]);
        }
        temp.clear();
    }

    return output;
}

vector<MovieAndRank> Recommender::sortByTitle(vector<MovieAndRank>& input)
{
    vector<MovieAndRank> output;
    vector<MovieAndRank> temp;
    vector<Movie*> movies;

    multimap<string, MovieAndRank> sortedTitles;
    multimap<string, MovieAndRank>::iterator itr = sortedTitles.begin();

    for (int i = 0; i < input.size(); i++)
        movies.push_back(m_moviedata->get_movie_from_id(input[i].movie_id));

    for (int i = 0; i < movies.size(); i++) // insert into multimap to sort
        sortedTitles.insert({ movies[i]->get_title(), input[i] });

    for (; itr != sortedTitles.end(); itr++)
    {
        output.push_back(itr->second);
    }

    return output;
}