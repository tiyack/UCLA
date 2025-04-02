#include "Recommender.h"
#include "UserDatabase.h"
#include "MovieDatabase.h"

//#include "treemm.h"
#include <unordered_map>

#include <string>
#include <vector>

#include "User.h"
#include "Movie.h"
using namespace std;

Recommender::Recommender(const UserDatabase& user_database,
                         const MovieDatabase& movie_database)
{
    userDB = &user_database;
    movieDB = &movie_database;
    // Replace this line with correct code.
}

vector<MovieAndRank> Recommender::recommend_movies(const string& user_email, int movie_count) const
{
    User* user = userDB->get_user_from_email(user_email);
    vector<string> watchHistory = user->get_watch_history();

    vector<string> allDirectors;
    vector<string> allActors;
    vector<string> allGenres;
    for(int i = 0; i < watchHistory.size(); i++)
    {
        Movie* m = movieDB->get_movie_from_id(watchHistory.at(i));
        vector<string> mdirectors = m->get_directors();
        allDirectors.insert(allDirectors.end(), mdirectors.begin(), mdirectors.end());
        vector<string> mactors = m->get_actors();
        allActors.insert(allActors.end(), mactors.begin(), mactors.end());
        vector<string> mgenres = m->get_genres();
        allGenres.insert(allGenres.end(), mgenres.begin(), mgenres.end());
    }

    unordered_map<string, int> rec;
    for(const string& direc : allDirectors)
    {
        vector<Movie*> sameDirector = movieDB->get_movies_with_director(direc);
        for(int i = 0; i < sameDirector.size(); i++)
        {
            rec[sameDirector.at(i)->get_id()] += 20;
        }
    }
    for(const string& act : allActors)
    {
        vector<Movie*> sameActor = movieDB->get_movies_with_actor(act);
        for(int i = 0; i < sameActor.size(); i++)
        {
            rec[sameActor.at(i)->get_id()] += 30;
        }
    }
    for(const string& genr : allGenres)
    {
        vector<Movie*> sameGenre = movieDB->get_movies_with_genre(genr);
        for(int i = 0; i < sameGenre.size(); i++)
        {
            rec[sameGenre.at(i)->get_id()] += 1;
        }
    }
    
    vector<MovieAndRank> recs;
    for (const auto& p : rec) {
        if (p.second < 1) {
            continue;
        }

        if (addedAlready(p.first, watchHistory)) {
            continue;
        }
        recs.push_back(MovieAndRank(p.first, p.second));
    }

//    sort(recs.begin(), recs.end(), lessThan);
//    std::vector<MovieAndRank> r(recs.begin(), recs.end());
//    quickSort(recs, 0, recs.size() - 1);
    sort(recs.begin(), recs.end(), [this] (const MovieAndRank& a, const MovieAndRank& b){
                if (a.compatibility_score != b.compatibility_score)
                    return a.compatibility_score > b.compatibility_score;
                else
                    return movieDB->get_movie_from_id(a.movie_id)->get_title() < movieDB->get_movie_from_id(b.movie_id)->get_title();
            }
        );

    vector<MovieAndRank> recommmendations;
    if(recs.size() > movie_count)
        for(int i = 0; i < movie_count; i++)
            recommmendations.push_back(recs.at(i));
    else
        return recs;

    return recommmendations;  // Replace this line with correct code.
}

int Recommender::addedAlready(const string movie, const vector<MovieAndRank> vec) const
{
    for(int i = 0; i < vec.size(); i++)
    {
        if(movie == (vec.at(i)).movie_id)
            return i;
    }
    return -1;
}
bool Recommender::addedAlready(const string movie, const vector<string> vec) const
{
    for(int i = 0; i < vec.size(); i++)
    {
        if(movie == vec.at(i))
            return true;
    }
    return false;
}

//bool Recommender::lessThan(const MovieAndRank& lhs, const MovieAndRank& rhs) {
//    return lhs.compatibility_score < rhs.compatibility_score;
//}

void Recommender::quickSort(std::vector<MovieAndRank>& recList, int left, int right) const
{
    int i = left, j = right;
    int pivot = recList[(left + right) / 2].compatibility_score;
    
    // Partition
    while (i <= j) {
        while (recList[i].compatibility_score > pivot)
            i++;

        while (recList[j].compatibility_score < pivot)
            j--;

        if (i <= j) {
            std::swap(recList[i], recList[j]);
            i++;
            j--;
        }
    };
    
    // Recursion
    if (left < j)
        quickSort(recList, left, j);

    if (i < right)
        quickSort(recList, i, right);
}





//bool Recommender::addedAlready(const string movie, const vector<MovieAndRank> vec) const
//{
//    for(int i = 0; i < vec.size(); i++)
//    {
//        if(movie == (vec.at(i)).movie_id)
//            return true;
//    }
//    return false;
//}

//vector<MovieAndRank> Recommender::recommend_movies(const string& user_email, int movie_count) const
//{
//    User* user = userDB->get_user_from_email(user_email);
//    vector<string> watchHistory = user->get_watch_history();
//
//    unordered_map<string, vector<string>> directorToMovies;
//    unordered_map<string, vector<string>> actorToMovies;
//    unordered_map<string, vector<string>> genreToMovies;
//
//    // Iterate over all movies watched by the user and add their directors, actors, and genres to the corresponding maps
//    for(int i = 0; i < watchHistory.size(); i++)
//    {
//        const Movie* movie = movieDB->get_movie_from_id(watchHistory.at(i));
//        const vector<string>& directors = movie->get_directors();
//        const vector<string>& actors = movie->get_actors();
//        const vector<string>& genres = movie->get_genres();
//
//        for (const string& director : directors) {
//            vector<Movie*>& allmoviesofdirector = movieDB->get_movies_with_director(director);
//            for(const string& d : allmoviesofdirector)
//                directorToMovies[director].push_back(watchHistory.at(i));
//        }
//        for(int j = 0; j < directors.size(); j++) {
//            directorToMovies[directors.at(j)].push_back(watchHistory.at(i));
//        }
//        for (int j = 0; j < actors.size(); j++) {
//            actorToMovies[actors.at(j)].push_back(watchHistory.at(i));
//        }
//        for (int j = 0; j < genres.size(); j++) {
//            genreToMovies[genres.at(j)].push_back(watchHistory.at(i));
//        }
//    }
//
//    // Iterate over all movies with the same director, actor, or genre and add them to the recs vector
//    unordered_map<string, int> compatibilityMap;
//    for (const auto& x : directorToMovies) {
//        const vector<string>& movieIds = x.second;
//        for (const string& movieId : movieIds) {
//            compatibilityMap[movieId] += 20;
//        }
//    }
//
//    for (const auto& p : actorToMovies) {
//        const vector<string>& movieIds = p.second;
//        for (const string& movieId : movieIds) {
//            compatibilityMap[movieId] += 30;
//        }
//    }
//
//    for (const auto& p : genreToMovies) {
//        const vector<string>& movieIds = p.second;
//        for (const string& movieId : movieIds) {
//            compatibilityMap[movieId] += 1;
//        }
//    }
//
//    // Convert the compatibilityMap to a vector of MovieAndRank and sort it based on the compatibility score
//    vector<MovieAndRank> recs;
//    for (const auto& p : compatibilityMap) {
//        if (p.second < 1) {
//            continue;
//        }
//       if(addedAlready(p.first, watchHistory))
//           continue;
////        if (find(watchHistory.begin(), watchHistory.end(), p.first) != watchHistory.end()) {
////            continue;
////        }
//        recs.push_back(MovieAndRank(p.first, p.second));
//    }
//
//    // Sort the recommendations by compatibility score in descending order
//    quickSort(recs, 0, recs.size() - 1);
//
//    // Return the top movie_count recommendations or all recommendations if the number of recommendations is less than movie_count
//    vector<MovieAndRank> recommendations;
//    if (recs.size() > movie_count)
//    {
//        for (int i = 0; i < movie_count; i++)
//            recommendations.push_back(recs.at(i));
//    }
//    else
//    {
//        recommendations = recs;
//    }
//
//    return recommendations;
//
//} //175003ms


//    std::vector<MovieAndRank> recs;
////    TreeMultimap<std::string, int> m_compatibilityMap;
//    for(int i = 0; i < allDirectors.size(); i++)
//    {
//        vector<Movie*> sameDirector = movieDB->get_movies_with_director(allDirectors.at(i));
//        for(int j = 0; j < sameDirector.size(); j++)
//        {
//            Movie* m = sameDirector.at(j);
//            int k = addedAlready(m->get_id(), recs);
//            if(k < 0)
////                m_compatibilityMap.insert(m->get_id(), 20);
//                recs.push_back(MovieAndRank(m->get_id(), 20));
//            else
////                m_compatibilityMap.find(m->get_id()).
//                recs[k].compatibility_score += 20;
//        }
//    }
//
//    for(int i = 0; i < allActors.size(); i++) //for every actor
//    {
//        vector<Movie*> sameActor = movieDB->get_movies_with_actor(allActors.at(i)); //get a vector of their movies
//        for(int j = 0; j < sameActor.size(); j++) //for every movie
//        {
//            Movie* m = sameActor.at(j);
//            int k = addedAlready(m->get_id(), recs); //check if the movie has already been added to the recs vector
//            if(k < 0)
//                recs.push_back(MovieAndRank(m->get_id(), 30)); //if not then add a new Movieand Rank
//            else
//                recs[k].compatibility_score += 30; //if yes then just add 30 to its compatibility score
//        }
//    }
//
//    for(int i = 0; i < allGenres.size(); i++) //for every genre
//    {
//        vector<Movie*> sameGenre = movieDB->get_movies_with_genre(allGenres.at(i));
//        for(int j = 0; j < sameGenre.size(); j++)
//        {
//            Movie* m = sameGenre.at(j);
//            int k = addedAlready(m->get_id(), recs);
//            if(k < 0)
//                recs.push_back(MovieAndRank(m->get_id(), 1));
//            else
//                recs[k].compatibility_score += 1;
//        }
//    }
//    Recommender r;
//    vector<MovieAndRank> r = recs;

    //remove all movies seen alr / less than 1
//   for (auto it = recs.begin(); it != recs.end(); )
//    {
//        bool found = false;
//        for (int i = 0; i < watchHistory.size(); i++)
//        {
//            if ((*it).movie_id == watchHistory.at(i))
//            {
//                found = true;
//                break;
//            }
//        }
//        if (it->compatibility_score < 1) {
//            it = recs.erase(it);
//        }
//        else if (found)
//            it = recs.erase(it);
//        else
//            it++;
//    }
