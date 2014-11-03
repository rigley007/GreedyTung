#include "mainclass.h"


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
