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
    const UserDatabase* m_userdata; // might need to be a pointer
    const MovieDatabase* m_moviedata;

    std::vector<MovieAndRank> sortByRating(std::vector<MovieAndRank>& input);
    std::vector<MovieAndRank> sortByTitle(std::vector<MovieAndRank>& input);
};

#endif // RECOMMENDER_INCLUDED
