#include "planet.h"

planet::planet()
{
    planetList << "loc_rowid" <<  "hd_name" << "hip_name" << "pl_hostname"
               << "pl_orbper" << "pl_orbeccen" << "pl_bmassj" << "pl_radj"
               << "st_teff" << "pl_orbincl" << "pl_name";
    QList<QString>::iterator i;
    for(i = planetList.begin(); i != planetList.end(); ++i){
        planetMap.insert(*i,QString());
    }
}


QString planet::getVar(QString key) const{
    if(planetMap.contains(key) && planetMap.value(key) != NULL){
        return planetMap.value(key);
    }
    else{
        return "No record";
    }
}
void planet::setVar(QString key,QString val){
    planetMap.insert(key,val);
}





