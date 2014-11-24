#include "MapManager.hpp"
#include "Dijkstra.hpp"
#include "FloydWarshall.hpp"
//#include "OrderedSet.hpp"
//#include "mainclass.h"

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

search_result runDijkstra(MapManager *map, int source, int destination) {
    Dijkstra djtra;
	search_result result;
	//OrderedSet result;

    djtra.solve(map, source, destination);
	result = djtra.displayPath(map, destination);
	//return result;
	return result;
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
	int source, destination, l_num = 0;
	vector<int> route_vec;
	vector<int>::iterator it;
	search_result s_result;
	check_result c_result;
	ifstream traffic_demands;
	ofstream fout;
	string t_str, d_str, filename;
	double d_traffic[4100], max_td=0,td_sum=0;
	vector<traffic_demand> traffic_vec;
	traffic_demand td_temp(-1,-1,0);
	//int source_list[4100], destination_list[4100], td_num = 0, max_td_num = 0;
	fout.open("results/heuristic_result.txt");

	for (int inj = 1; inj < 10; inj++){
		source = destination = UNDEFINED_LMARK;
		filename = "traffic/synthetic/44-UniformRandom-0.0" + to_string(inj) + ".txt";
		traffic_demands.open(filename.c_str());

		if (!traffic_demands){
			cout << "ERROR! : Cound not load traffic demands!" << endl;
			exit(0);
		}
		while (traffic_demands){
			traffic_demands >> t_str >> td_temp.source >> d_str >> td_temp.destination >> td_temp.t_d;
			//cout << td_temp.source << " " << td_temp.destination << " " << td_temp.t_d << endl;
			if (td_temp.source != td_temp.destination && td_temp.t_d != 0)
				traffic_vec.push_back(td_temp);
			td_temp.source = -1;
			td_temp.destination = -1;
			td_temp.t_d = 0;
		}

		traffic_demands.close();

		sort(traffic_vec.begin(), traffic_vec.end());

		map.readInputFile("locations.map");

		//route_vec = runDijkstra(&map, traffic_vec[0].source, traffic_vec[0].destination);


		

		for (int i = 0; i < traffic_vec.size(); i++){
			route_vec.clear();
			s_result = runDijkstra(&map, traffic_vec[i].source, traffic_vec[i].destination);
			route_vec = s_result.route_vec;
			if (route_vec.size() != 0){
				if (s_result.total_cost > LONG_LINK_COST){
					create_longlink(traffic_vec[i].source, traffic_vec[i].destination, traffic_vec[i].t_d, map.Router_list_arr, map.Link_list_arr);
					l_num++;
					map.setWeight(traffic_vec[i].source, traffic_vec[i].destination, 1);
					map.setWeight(traffic_vec[i].destination, traffic_vec[i].source, 1);
				}
				else{
					c_result = check_route(route_vec, traffic_vec[i].t_d, map.Router_list_arr);
					if (c_result.result){
						update_routelinks(route_vec, traffic_vec[i].t_d, map.Router_list_arr);
					}
					else{
						update_routelinks(route_vec, c_result.unutilized_capa, map.Router_list_arr);
						map.setWeight(c_result.r_left, c_result.r_right, LINK_CONGESTION);
						map.setWeight(c_result.r_right, c_result.r_left, LINK_CONGESTION);
						traffic_vec[i].t_d = traffic_vec[i].t_d - c_result.unutilized_capa;
						i--;

					}
				}

			}
			else{
				create_longlink(traffic_vec[i].source, traffic_vec[i].destination, traffic_vec[i].t_d, map.Router_list_arr, map.Link_list_arr);
				l_num++;
				map.setWeight(traffic_vec[i].source, traffic_vec[i].destination, 1);
				map.setWeight(traffic_vec[i].destination, traffic_vec[i].source, 1);
				//cout << route_vec[0] << " " << route_vec[1] << endl;
			}
		}

		fout << "Injection Rate: 0.0" << inj << "\t Number of long links: " << l_num << endl;
		for (int i = 0; i < map.Link_list_arr.size(); i++){
			
			fout << "Link ID: " << map.Link_list_arr[i]->get_Link_ID() << " Link Type: " << map.Link_list_arr[i]->get_Link_type() << " Src: " << map.Link_list_arr[i]->get_router_arr()[0]->get_Router_ID() << " Dst: " << map.Link_list_arr[i]->get_router_arr()[1
			]->get_Router_ID() << " Capacity: " << map.Link_list_arr[i]->get_capacity() << " Utilized Capacity: " << map.Link_list_arr[i]->get_utilized_capasity() << " Utilization: " << map.Link_list_arr[i]->get_utilized_capasity() * 100 / map.Link_list_arr[i]->get_capacity() << "%\n";
		}
		fout << "\n\n";

		l_num = 0;
		traffic_vec.clear();
		map = MapManager();
	}
    
	fout.close();
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
