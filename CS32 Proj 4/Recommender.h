#ifndef RECOMMENDER_INCLUDED
#define RECOMMENDER_INCLUDED

#include <string>
#include <vector>
#include <map>

class UserDatabase;
class MovieDatabase;
class Movie;

struct MovieAndRank
{
    MovieAndRank(const std::string& id, int score)
        : movie_id(id), compatibility_score(score)
    {}

    std::string movie_id;
    int compatibility_score;
};

class Recommender
{
public:
    Recommender(const UserDatabase& user_database,
        const MovieDatabase& movie_database);
    std::vector<MovieAndRank> recommend_movies(const std::string& user_email,
        int movie_count);

private:
    struct MoviePointerAndRank
    {
        MoviePointerAndRank(Movie* movie, int score)
            : movieP(movie), rank(score)
        {}

        Movie* movieP;
        int rank;
    };

    const UserDatabase* m_userdata;
    const MovieDatabase* m_moviedata;

    //const UserDatabase* getUDB() { return m_userdata; }
    //const MovieDatabase* getMDB() { return m_moviedata; }

    static bool compareMovies(const MoviePointerAndRank& m1, const MoviePointerAndRank& m2);
};

#endif // RECOMMENDER_INCLUDED
