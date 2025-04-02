#include "MovieDatabase.h"
#include "Movie.h"

#include <string>
#include <vector>
#include <cctype>

#include <iostream>
#include <sstream>
#include <fstream>
#include "treemm.h"
using namespace std;

MovieDatabase::MovieDatabase()
{
    // Replace this line with correct code.
}

bool MovieDatabase::load(const string& filename)
{
    ifstream infile(filename);
    if (!infile) {
        cerr << "Failed to open file " << filename << endl;
        return false;
    }
    while(infile){
        //cerr << "Getiing in\n";
        string id;
        getline(infile, id);
        
        string title;
        getline(infile, title);
        
        string year;
        getline(infile, year);
        
        string directors_line;
        getline(infile, directors_line);
        vector<string> directors;
        istringstream directors_ss(directors_line);
        string director;
        while (getline(directors_ss, director, ',')) {
                directors.push_back(director);
        }
//        
        string actors_line;
        getline(infile, actors_line);
        vector<string> actors;
        istringstream actors_ss(actors_line);
        string actor;
        while (getline(actors_ss, actor, ',')) {
                actors.push_back(actor);
        }
//        
        string genres_line;
        getline(infile, genres_line);
        vector<string> genres;
        istringstream genres_ss(genres_line);
        string genre;
        while (getline(genres_ss, genre, ',')) {
                genres.push_back(genre);
        }
        
        float rating;
        infile >> rating;
        infile.ignore(10000, '\n');
        string allLower = id;
        transform(allLower.begin(), allLower.end(), allLower.begin(), ::toupper);
        m_idTree.insert(allLower, Movie(id, title, year, directors, actors, genres, rating));

        for(int i = 0; i < directors.size(); i++)
        {
            allLower = directors.at(i);
            transform(allLower.begin(), allLower.end(), allLower.begin(), ::toupper);
            m_directorTree.insert(allLower, Movie(id, title, year, directors, actors, genres, rating));
        }
        for(int i = 0; i < actors.size(); i++)
        {
            allLower = actors.at(i);
            transform(allLower.begin(), allLower.end(), allLower.begin(), ::toupper);
            m_actorTree.insert(allLower, Movie(id, title, year, directors, actors, genres, rating));
        }
        for(int i = 0; i < genres.size(); i++)
        {
            allLower = genres.at(i);
            transform(allLower.begin(), allLower.end(), allLower.begin(), ::toupper);
            m_genreTree.insert(allLower, Movie(id, title, year, directors, actors, genres, rating));
        }
    
        if(infile)
            infile.ignore(10000, '\n');
    }
    return true;  // Replace this line with correct code.
}

Movie* MovieDatabase::get_movie_from_id(const string& id) const
{
    string lower = id;
    transform(lower.begin(), lower.end(), lower.begin(), ::toupper);
    TreeMultimap<string, Movie>::Iterator it = m_idTree.find(lower);
//    cerr << "Ret\n";
    if (it.is_valid())
        return &(it.get_value());
    else
        return nullptr;   // Replace this line with correct code.
}

vector<Movie*> MovieDatabase::get_movies_with_director(const string& director) const
{
    string lower = director;
    transform(lower.begin(), lower.end(), lower.begin(), ::toupper);
    TreeMultimap<string, Movie>::Iterator it = m_directorTree.find(lower);
//    cerr << "Ret\n";
    vector<Movie*> vect;

    while (it.is_valid())
    {
        vect.push_back(&(it.get_value()));
        it.advance();
    }
    return vect;
//    else
//        return nullptr;
//    return vector<Movie*>();  // Replace this line with correct code.
}

vector<Movie*> MovieDatabase::get_movies_with_actor(const string& actor) const
{
    string lower = actor;
    transform(lower.begin(), lower.end(), lower.begin(), ::toupper);
    TreeMultimap<string, Movie>::Iterator it = m_actorTree.find(lower);
//    cerr << "Ret\n";
    vector<Movie*> vect;

    while (it.is_valid())
    {
        vect.push_back(&(it.get_value()));
        it.advance();
    }
    return vect;  // Replace this line with correct code.
}

vector<Movie*> MovieDatabase::get_movies_with_genre(const string& genre) const
{
    string lower = genre;
    transform(lower.begin(), lower.end(), lower.begin(), ::toupper);
    TreeMultimap<string, Movie>::Iterator it = m_genreTree.find(lower);
//    cerr << "Ret\n";
    vector<Movie*> vect;

    while (it.is_valid())
    {
        vect.push_back(&(it.get_value()));
        it.advance();
    }
    return vect;
//    return vector<Movie*>();  // Replace this line with correct code.
}
