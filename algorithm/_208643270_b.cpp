#include "./_208643270_b.h"

REGISTER_ALGORITHM(_208643270_b)

using std::get;

pair<int, int> _208643270_b::getBestStack(const string& port, int x, int y){
    pair<int, int> ret;
    // a mapping of coordinate with sorted flag and top port
    vector<std::tuple<pair<int, int>, bool, string>> mapping;
    auto d = s.getStorageDimensions();
    // calculating the mapping
    for (size_t i = 0; i < d.first; ++i){
        for (size_t j = 0; j < d.second; ++j){
            if (x == (int)i && y == (int)j) continue;
            if (s.fullCoordinate(i, j)) continue;
            if (s.emptyCoordinate(i, j)){
                mapping.push_back({ {i, j}, true, routes.back()});
                continue;
            }

            bool flag = true;
            vector<Container> vc = s.getCoordinateContainers(i, j);
            string topPort = vc.back().getDestination();
            for (auto it = vc.begin(); it != vc.end() -1; ++it){
                if (placeOn((*it).getDestination(), (*(it + 1)).getDestination())) flag = false;
            }
            mapping.push_back({ {i, j}, flag, topPort});
        }
    }

    if (mapping.size() == 0) return {-1, -1};

    // trying to find best sorted stack
    int m = routes.size() * 100; // just to make sure its the max

    for (auto s : mapping) {
        if (get<1>(s)) continue;
        int val = placeOn(port, get<2>(s));
        if (val > -1 && val < m){
            m = val;
            ret = {get<0>(s).first, get<0>(s).second};
        }
        if (m != (int)routes.size() * 100) return ret;
    }

    for (auto s : mapping) {
        if (!get<1>(s)) continue;
        int val = placeOn(port, get<2>(s));
        if (val > -1 && val < m){
            m = val;
            ret = {get<0>(s).first, get<0>(s).second};
        }
        if (m != (int)routes.size() * 100) return ret;
    }

    // if nothing good found just return the first
    return {get<0>(mapping[0])};
}
