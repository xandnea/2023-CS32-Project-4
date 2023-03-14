#ifndef MOVIEDATABASE_INCLUDED
#define MOVIEDATABASE_INCLUDED

#include "treemm.h"

#include <string>
#include <vector>

class Movie;

class MovieDatabase
{
public:
    MovieDatabase();
    bool load(const std::string& filename);
    Movie* get_movie_from_id(const std::string& id) const;
    std::vector<Movie*> get_movies_with_director(const std::string& director) const;
    std::vector<Movie*> get_movies_with_actor(const std::string& actor) const;
    std::vector<Movie*> get_movies_with_genre(const std::string& genre) const;

private:
    std::string m_id;
    TreeMultimap<std::string, Movie*> m_movies;
    TreeMultimap<std::string, Movie*> m_directors;
    TreeMultimap<std::string, Movie*> m_actors;
    TreeMultimap<std::string, Movie*> m_genres;

    void insert_to_tmm(TreeMultimap<std::string, Movie*>& tmm, std::string, Movie* movie);
    std::string to_lower(const std::string& input);
};

#endif // MOVIEDATABASE_INCLUDED
