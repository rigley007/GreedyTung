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
	vector<Router*> port_router_vec;
public:
	void set_Link_type(string L_type){ Link_type = L_type; }
	string get_Link_type(){ return Link_type;  }
    void set_Link_ID(int l_id){ Link_ID = l_id; }
    int get_Link_ID(){ return Link_ID; }
    float get_capacity(){ return capacity; }
    float get_utilized_capasity(){ return utilized_capacity; }
	void set_capacity(float cpt){ capacity = cpt; utilized_capacity = 0; }
    void add_capacity_utilization(float ult);
	void minus_capacity_utilization(float ult);
	bool set_router(Router *port_router);
	vector<Router*> get_router_arr(){ return port_router_vec; }
	Router *get_another_router(Router *ori_router);
};



#endif
