#include "Recommender.h"
#include "UserDatabase.h"
#include "MovieDatabase.h"

#include "User.h"
#include "Movie.h"

#include <string>
#include <vector>
#include <map>
#include <algorithm>

using namespace std;

//vector<MovieAndRank> sortByRating(vector<MovieAndRank>& input);
//vector<MovieAndRank> sortByTitle(vector<MovieAndRank>& input);

Recommender::Recommender(const UserDatabase& user_database,
    const MovieDatabase& movie_database)
{
    m_userdata = &user_database;
    m_moviedata = &movie_database;
}

vector<MovieAndRank> Recommender::recommend_movies(const string& user_email, int movie_count)
{
    vector<MovieAndRank> ratings;
    map<string, int> compatability_scores;
    map<string, int>::iterator it;

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
                string id = movies_with_director[k]->get_id();

                if (find(movieIDs.begin(), movieIDs.end(), id) != movieIDs.end()) // if movie id is already in user's watch history, go to next movie
                    continue;

                it = compatability_scores.find(id);
                if (it == compatability_scores.end()) // if not found in map
                {
                    compatability_scores.insert({ id, 20 });
                }
                else
                {
                    compatability_scores[id] += 20;
                }
                
            }
        }

        vector<string> actors = movies[i]->get_actors(); // vector of actors
        for (int j = 0; j < actors.size(); j++) // for each actor in the movie
        {
            vector<Movie*> movies_with_actor = m_moviedata->get_movies_with_actor(actors[j]); // vector of movies w/ that actor
            for (int k = 0; k < movies_with_actor.size(); k++)
            {
                string id = movies_with_actor[k]->get_id();

                if (find(movieIDs.begin(), movieIDs.end(), id) != movieIDs.end()) // if movie id is already in user's watch history, go to next movie
                    continue;

                it = compatability_scores.find(id);
                if (it == compatability_scores.end()) // if not found in map
                {
                    compatability_scores.insert({ id, 30 });
                }
                else
                {
                    compatability_scores[id] += 30;
                }
            }
        }

        vector<string> genres = movies[i]->get_genres(); // vector of genres
        for (int j = 0; j < genres.size(); j++) // for each genre in the movie
        {
            vector<Movie*> movies_with_genre = m_moviedata->get_movies_with_genre(genres[j]); // vector of movies w/ that genre 
            for (int k = 0; k < movies_with_genre.size(); k++)
            {
                string id = movies_with_genre[k]->get_id();

                if (find(movieIDs.begin(), movieIDs.end(), id) != movieIDs.end()) // if movie id is already in user's watch history, go to next movie
                    continue;

                it = compatability_scores.find(id);
                if (it == compatability_scores.end()) // if not found in map
                {
                    compatability_scores.insert({ id, 1 });
                }
                else
                {
                    compatability_scores[id] += 1;
                }
            }
        }
    }

    it = compatability_scores.begin();
    vector<MoviePointerAndRank> moviesWPAR;

    for (; it != compatability_scores.end(); it++) // copy map to MoviePointerAndRank vector 
    {
        if (it->second >= 1)
        {
            MoviePointerAndRank moviePointerAndRank(m_moviedata->get_movie_from_id(it->first), it->second);
            moviesWPAR.push_back(moviePointerAndRank);
        }
    }

    sort(moviesWPAR.begin(), moviesWPAR.end(), compareMovies);

    int count;
    if (moviesWPAR.size() < movie_count)
        count = moviesWPAR.size();
    else
        count = movie_count;

    for (int i = 0; i < count; i++) // copy MoviePointerAndRank vector into ratings for final result
    {
        MovieAndRank movieAndRank(moviesWPAR[i].movieP->get_id(), moviesWPAR[i].rank);
        ratings.push_back(movieAndRank);
    }

    return ratings;  // Replace this line with correct code.
}

/*static*/ bool Recommender::compareMovies(const MoviePointerAndRank& m1, const MoviePointerAndRank& m2)
{
    //cout << "SORTING COMPAT" << endl;
    if (m1.rank != m2.rank)
        return m1.rank > m2.rank;
    else if (m1.movieP->get_rating() != m2.movieP->get_rating())
        return m1.movieP->get_rating() > m2.movieP->get_rating();
    else 
        return m1.movieP->get_title() < m2.movieP->get_title();
}