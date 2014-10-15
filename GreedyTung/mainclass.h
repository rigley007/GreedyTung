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

using namespace std;

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
    
public:
    void set_Router_ID(int r_ID){ Router_ID = r_ID; }
    int get_Router_ID(){ return Router_ID; }
    void set_address_x(int add_x){ address_x = add_x; }
    void set_address_y(int add_y){ address_y = add_y; }
    int get_address_x(){ return address_x; }
    int get_address_y(){ return address_y; }
    
};

class Link{
    int Link_ID;
    float capacity, utilized_capacity;
    Router *router_A, *router_B;
public:
    void set_Link_ID(int l_id){ Link_ID = l_id; }
    int get_Link_ID(){ return Link_ID; }
    float get_capacity(){ return capacity; }
    float get_utilized_capasity(){ return utilized_capacity; }
    void set_capacity(float cpt){ capacity = cpt; }
    void add_capacity_utilization(float ult);
    bool set
};

void Link::add_capacity_utilization(float ult){
    if (utilized_capacity+ult>capacity) {
        cout<<"Beyond the capacity of this link: "<< Link_ID<<endl;
    }else{
        utilized_capacity = utilized_capacity + ult;
    }

}

void Subnet::decrement_Router_num(){
    if (Router_num - 1 < 0) {
        cout<<"Subnet: "<<Subnet_ID<<" can not have a negative number of Routers!"<<endl;
    }else{
        Router_num -= 1;
    }
}


#endif
