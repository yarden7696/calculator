#include "symtab.h"
#include "scanner.h"
#include <iostream>     // std::cout
#include <algorithm>    // std::find
#include<stdexcept>

// return the value of the varible 
Attributes& Symbol_table::get(string name) {

std::map<string,Attributes>::iterator _it;
_it=sym_tab.find(name);

return _it->second;

}

// set the value to the varible 
void Symbol_table::set(string name, double nv) {

std::map<string,Attributes>::iterator _it;
_it=sym_tab.find(name);

if(_it->second.is_const) error("cannot change constant");
_it->second.value=nv;


}


// check if the varible has some value
bool Symbol_table::is_declared(string name) {

std::map<string,Attributes>::iterator _it;
_it=sym_tab.find(name);

if(_it!=sym_tab.end()) return true;
return false;

}


void Symbol_table::declare(string name, double nv, bool ic) {

Attributes att(nv,ic);
sym_tab.insert({name,att});

}

