#include "mainclass.h"
#include "MapManager.hpp"

Router *Link::get_another_router(Router *ori_router){

	if (port_router_vec.size() == 2){
		if (port_router_vec[0] == ori_router){
			return port_router_vec[1];
		}
		else if (port_router_vec[1] == ori_router){
			return port_router_vec[0];
		}
		else{
			cout << "Router: " << ori_router->get_Router_ID() << " dose not belong to Link: " << Link_ID << endl;
		}
	}
	else{
		cout << "ERROR! : Link: " << Link_ID << " has not been fully initialized!" << endl;
	}
	return NULL;
}

bool Link::set_router(Router *port_router){
	//cout << "ttt" << router[0] << router[1] << endl;
	if (port_router_vec.size() < 2){
		port_router_vec.push_back(port_router);
		return true;
	}
	else{
		cout << "ERROR! : Can not set more than 2 port Router to Link: " << Link_ID << endl;
	}
	return false;
}

void Link::add_capacity_utilization(float ult){
    if (utilized_capacity+ult>capacity) {
        cout<<"ERROR! : Beyond the capacity of this link: "<< Link_ID<<endl;
    }else{
        utilized_capacity = utilized_capacity + ult;
    }

}

void Link::minus_capacity_utilization(float ult){
	if (utilized_capacity - ult < 0){
		cout << "ERROR! : Link: " << Link_ID << " capacity utilization can not below 0!" << endl;
	}
	else{
		utilized_capacity = utilized_capacity - ult;
	}
}

void Subnet::decrement_Router_num(){
    if (Router_num - 1 < 0) {
        cout<<"ERROR! : Subnet: "<<Subnet_ID<<" can not have a negative number of Routers!"<<endl;
    }else{
        Router_num -= 1;
    }
}

void Router::add_Link(Link * lk){
	Link_vec.push_back(lk);
}

Link* Router::get_inter_Link(int R_ID){
	vector<Link*>::iterator it;
	int another_R_id;
	for (it = Link_vec.begin(); it != Link_vec.end(); it++){
		another_R_id = (*it)->get_another_router(this)->get_Router_ID();
		if (another_R_id == R_ID){
			return *it;
		}
	}
	return NULL;
}

check_result check_route(vector<int> route_vec, float t_d, vector<Router*> routers_vec){
	check_result result;
	result.unutilized_capa = 9999999;
	result.result = true;
	float capa = 0, used_capa = 0;
	Link *temp_link;
	for (int i = 1; i < route_vec.size(); i++){
		temp_link = routers_vec[(route_vec[i - 1])]->get_inter_Link((route_vec[i]));
		if (temp_link == NULL){
			cout << "Can not found inter_link!" << endl;
			return result;
		}
		capa = temp_link->get_capacity();
		used_capa = temp_link->get_utilized_capasity();
		if ((capa - used_capa) <= t_d && (capa - used_capa) < result.unutilized_capa){
			result.result = false;
			result.r_left = route_vec[i - 1];
			result.r_right = route_vec[i];
			result.unutilized_capa = capa - used_capa;
		}
	}
	return result;
}

void update_routelinks(vector<int> route_vec, float t_d, vector<Router*> routers_vec){
	Link *temp_link;
	for (int i = 1; i < route_vec.size(); i++){
		temp_link = routers_vec[(route_vec[i - 1])]->get_inter_Link((route_vec[i]));
		temp_link->add_capacity_utilization(t_d);
	}
}

void create_longlink(int source, int dest, float t_d, vector<Router*> routers_vec, vector<Link*> &links_vec){
	Link *temp_link = new Link();
	temp_link->set_capacity(LONG_LINK_CAPASITY);
	temp_link->add_capacity_utilization(t_d);
	temp_link->set_Link_ID(links_vec.size());
	temp_link->set_Link_type("long");
	temp_link->set_router(routers_vec[source]);
	temp_link->set_router(routers_vec[dest]);
	routers_vec[source]->add_Link(temp_link);
	routers_vec[dest]->add_Link(temp_link);
	links_vec.push_back(temp_link);
}