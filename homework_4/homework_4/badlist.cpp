void removeBad(list<Movie*>& li) {
    for(auto it = li.begin(); it != li.end();) {
        if((*it)->rating() < 50) {
            delete *it;
            it = li.erase(it);
        } else {
            it++;
        }
    }
}
