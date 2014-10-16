//
//  mainclass.h
//  GreedyTung
//
//  Created by Helen on 10/13/14.
//  Copyright (c) 2014 ___IWINLAB___. All rights reserved.
//
//  git test
#ifndef GreedyTung_mainclass_h
#define GreedyTung_mainclass_h
#include <iostream>
#include <vector>
#include <string>

using namespace std;

class Subnet;
class Router;
class Link;


class Subnet{
    int Subnet_ID;
    int Router_num;
    int* Router_ID_Arr;
public:
    void set_Subnet_ID(int ID){ Subnet_ID = ID; }
    int get_Subnet_ID(){ return Subnet_ID; }
    void increment_Router_num(){ Router_num += 1; }
    void decrement_Router_num();
};

class Router{
    int Router_ID;
    int address_x, address_y;
    Subnet* subnet;
	vector<Link*> Link_vec;
    
public:
    void set_Router_ID(int r_ID){ Router_ID = r_ID; }
    int get_Router_ID(){ return Router_ID; }
    void set_address_x(int add_x){ address_x = add_x; }
    void set_address_y(int add_y){ address_y = add_y; }
    int get_address_x(){ return address_x; }
    int get_address_y(){ return address_y; }
	void add_Link(Link *lk);
	vector<Link*> get_Link_vec(){ return Link_vec; }
	Link *get_inter_Link(int R_ID);
    
};

class Link{
	string Link_type;
    int Link_ID;
    float capacity, utilized_capacity;
	Router *router[2];
public:
	void set_Link_type(string L_type){ Link_type = L_type; }
	string get_Link_type(){ return Link_type;  }
    void set_Link_ID(int l_id){ Link_ID = l_id; }
    int get_Link_ID(){ return Link_ID; }
    float get_capacity(){ return capacity; }
    float get_utilized_capasity(){ return utilized_capacity; }
    void set_capacity(float cpt){ capacity = cpt; }
    void add_capacity_utilization(float ult);
	void minus_capacity_utilization(float ult);
	bool set_router(Router *port_router);
	Router **get_router_arr(){ return router; }
	Router *get_another_router(Router *ori_router);
};



Router *Link::get_another_router(Router *ori_router){
	if (router[0] != NULL && router[1] != NULL){
		if (router[0] == ori_router){
			return router[1];
		}
		else if (router[1] == ori_router){
			return router[0];
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
	if (router[0] == NULL){
		router[0] = port_router;
		return true;
	}
	else if (router[1] == NULL){
		router[1] = port_router;
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

#endif
