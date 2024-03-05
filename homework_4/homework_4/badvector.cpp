void removeBad(vector<Movie*>& v) {
    for(auto it = v.begin(); it != v.end();) {
        if((*it)->rating() < 50) {
            delete *it;
            it = v.erase(it);
        } else {
            it++;
        }
    }
}
