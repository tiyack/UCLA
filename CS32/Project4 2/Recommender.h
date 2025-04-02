#ifndef RECOMMENDER_INCLUDED
#define RECOMMENDER_INCLUDED

#include <string>
#include <vector>
//#include "treemm.h"

class UserDatabase;
class MovieDatabase;

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
                                               int movie_count) const;

  private:
    const UserDatabase* userDB;
    const MovieDatabase* movieDB;
//    bool addedAlready(const std::string movie, const std::vector<MovieAndRank> vec) const;
    int addedAlready(const std::string movie, const std::vector<MovieAndRank> vec) const;
    void quickSort(std::vector<MovieAndRank>& recList, int left, int right) const;
    bool addedAlready(const std::string movie, const std::vector<std::string> vec) const;
//    static bool lessThan(const MovieAndRank& lhs, const MovieAndRank& rhs) ;
};

#endif // RECOMMENDER_INCLUDED
