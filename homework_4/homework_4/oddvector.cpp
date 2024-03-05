void removeOdd(vector<int>& v) {
    for(auto it = v.begin(); it != v.end();) {
        if(*it % 2 == 1) {
            it = v.erase(it);
        } else {
            it++;
        }
    }
}
