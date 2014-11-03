#include "MapManager.hpp"
#include "Dijkstra.hpp"
#include "FloydWarshall.hpp"
//#include "OrderedSet.hpp"
//#include "mainclass.hpp"

const char helpMessage[] =
        "USAGE: \n\n"
        "  shortest locations.map [source] [destination]\n\n"
        "Display this help message if no arguments are provided.\n\n"
        "This application implements two approaches to finding out the\n"
        "shortest path between two landmarks on a locations map:\n\n"
        "1) Dijkstra's shortest path algorithm:\n"
        "   This algorithm allows us to find the shortest path\n"
        "   between two landmarks: the source and the destination.\n\n"
        "   To use this approach, provide four arguments to this\n"
        "   application, as follows:\n\n"
        "       shortest locations.map 2 3\n\n"
        "   where, 2 and 3 are respectively the indices of the source\n"
        "   and the destination landmarks in locations.map. Note that\n"
        "   indexing beings at zero, and not at one).\n\n"
        "   Alternatively, the user may also specify the landmarks by name.\n"
        "   For instance,\n\n"
        "       shortest locations.map \"Edinburgh\" \"Oxford\"\n\n"
        "2) Floyd-Warshall's all-pair shortest paths algorithm:\n"
        "   This algorithm allows us to find all of the shortest paths\n"
        "   between every landmark on the locations.map. It is particularly\n"
        "   useful when we wish to generate all of the paths for display\n"
        "   at each of the landmarks.\n\n"
        "   To use this approach, invoke the application as follows:\n\n"
        "       shortest locations.map\n\n"
        ;

vector<int> runDijkstra(MapManager *map, int source, int destination) {
    Dijkstra djtra;
	vector<int> route_vec;
	//OrderedSet result;

    djtra.solve(map, source, destination);
	route_vec = djtra.displayPath(map, destination);
	//return result;
	return route_vec;
}

void runFloydWarshall(MapManager *map) {
    FloydWarshall fw;

    fw.solve(map);
    fw.displayPaths(map);
}

int getLandmarkIndex(MapManager *map, const char *str) {
    int i, landmarkIndex;
    bool flag = false;
    for (i = 0; str[i] != '\0'; ++i) {
        if (isalpha(str[i])) {
            flag = true;
            break;
        }
    }
    if (flag == true)
        landmarkIndex = map->getLandmarkIndex(str);
    else
        landmarkIndex = atoi(str);
    return landmarkIndex;
}

int main(int argc, char *argv[]) {
    MapManager map;
    int source, destination;
	vector<int> route_vec;
	vector<int>::iterator it;
	ifstream traffic_demands;
	string t_str;
	double d_traffic[4100], max_td=0,td_sum=0;
	int source_list[4100], destination_list[4100], td_num = 0, max_td_num = 0;

    source = destination = UNDEFINED_LMARK;
	traffic_demands.open("traffic/Radix/Radix88.txt");
	if (!traffic_demands){
		cout << "ERROR! : Cound not load traffic demands!" << endl;
		exit(0);
	}
	while (traffic_demands){
		traffic_demands >> t_str >> source_list[td_num] >> destination_list[td_num] >> d_traffic[td_num];
		td_num++;
		//cout << source << " " << destination << " " << d_traffic << endl;
	}

	traffic_demands.close();


	for (int i = 0; i < td_num; i++){
		if (source_list[i] != destination_list[i] && source_list[i]< 32 && destination_list[i]>=32){
			td_sum += d_traffic[i];
		}

		if (source_list[i] != destination_list[i] && source_list[i]>= 32 && destination_list[i] < 32){
			td_sum += d_traffic[i];
		}

		if (d_traffic[i]>max_td && source_list[i] != destination_list[i]){
			max_td = d_traffic[i];
			max_td_num = i;
		}
	}
	cout << "td_sum " << td_sum << endl;
    map.readInputFile("locations.map");

	route_vec = runDijkstra(&map, source_list[max_td_num], destination_list[max_td_num]);

	for (it = route_vec.begin(); it != route_vec.end(); it++){
		cout << *it << endl;
	}

	/*
	vector<Router*>::iterator it_r;
	vector<Link*>::iterator	it_l;
	vector<Link*> temp_link_vec;
	for (it_r = map.Router_list_arr.begin(); it_r != map.Router_list_arr.end(); it_r++){
		cout << "Router " << (*it_r)->get_Router_ID() << ": " << endl;
		temp_link_vec = (*it_r)->get_Link_vec();
		for (it_l = temp_link_vec.begin(); it_l != temp_link_vec.end(); it_l++){
			cout << "	Router " << (*it_l)->get_another_router(*it_r)->get_Router_ID() << "		Link " << (*it_l)->get_Link_ID() << "		type: " << (*it_l)->get_Link_type() << endl;
		}
	}
    source = 1;
    destination = 2;
	*/

    //runDijkstra(&map, source, destination);
	system("pause");
    return 0;
	
}
