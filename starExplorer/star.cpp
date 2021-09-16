#include "star.h"

star::star(){
    qDebug() << "Constructing star..";
    varKeys << "id" << "hip" << "hd" << "hr" << "gl" << "bf" << "proper" << "ra" << "dec" << "dist"
            << "pmra" << "pmdec" << "rv" << "mag" << "absmag" << "spect" << "ci" << "x" << "y" << "z"
            << "vx" << "vy" << "vz" << "rarad" << "decrad" << "pmrarad" << "pmdecrad" << "bayer"
            << "flam" << "con" << "comp" << "comp_primary" << "base" << "lum" << "var" << "var_min" << "var_max";
    QList<QString>::iterator i;
    for(i = varKeys.begin(); i != varKeys.end(); ++i){
        varMap.insert(*i,QString());
    }

}
star::~star(){
}


    //Set this star to found star
void star::findStarByName(QString s){
        QSqlQuery q;
        q.prepare("select * from star where proper = :s");
        q.addBindValue(s);
        if(q.exec()){
            if(q.numRowsAffected() > 1)
                qDebug() << "Multiple stars with ID found";
            q.next();
            QList<QString>::iterator i;
            int j = 0;
            for(i = varKeys.begin(); i != varKeys.end();++i){
                this->setVar(*i,q.value(j).toString());
                j++;
            }
        }
        else{
            qDebug() << "findStarByName failed";
            return;
        }
    return;
}
void star::findStarById(int id){
    QSqlQuery q;
    q.prepare("select * from star where id=:id");
    q.addBindValue(id);
    if(q.exec()){
        if(q.numRowsAffected() > 1)
            qDebug() << "Multiple stars with ID found";

        q.next();
        QList<QString>::iterator i;
        int j = 0;
        for(i = varKeys.begin(); i != varKeys.end();++i){
            this->setVar(*i,q.value(j).toString());
            j++;
        }
    }
    else{
        qDebug() << "findStarByName failed";
        return;
    }

}

//Find planets in database where this star has namn,hip or hd set
void star::findPlanets(){
    planetVector.clear();
    QSqlQuery q;
    q.prepare("select loc_rowid, hd_name, hip_name, pl_hostname, pl_orbper, pl_orbeccen, pl_bmassj, pl_radj, st_teff, pl_orbincl, pl_name "
              "from planets where hip_name in (select hip from star where hip = :hip ) "
              "or hd_name in (select hd from star where hd_name = :hd ) "
              "or pl_name in (select bf from star where bf = ':bf' ) "
              "or pl_hostname in (select bf from star where bf = :pl) order by loc_rowid ");
    q.bindValue(":hip",this->getVar("hip"));
    q.bindValue(":hd",this->getVar("hd"));
    q.bindValue(":bf",this->getVar("bf"));
    q.bindValue(":pl",this->getVar("bf"));

    if(q.exec()){
        qDebug() << "findPlanets query executed" << endl << "rows found: " << q.numRowsAffected();
        q.next();
        planet p;
        for(int k = 0; k < q.numRowsAffected(); ++k){
            QList<QString>::iterator i;
            int j = 0;
            for(i = p.planetList.begin(); i != p.planetList.end();++i){
                p.setVar(*i,q.value(j).toString());
                j++;
            }
            qDebug() << "pushing planet with loc_rowid = " << p.getVar("loc_rowid");
            planetVector.push_back(p);
            q.next();
        }
    }
    qDebug() << q.lastError();
}

QString star::getVar(QString key){
    if(varMap.contains(key) && varMap.value(key) != NULL)
        return varMap.value(key);
    else return "No record";
}
void star::setVar(QString key,QString val){
    varMap.insert(key,val);
}

QString star::getPlanetLabelString(int id){
    QString str = "";
    QVector<planet>::iterator i;
    for(i = this->planetVector.begin(); i != this->planetVector.end();i++){
        if(i->getVar("loc_rowid").toInt() == id){
            str.append("Database ID:");
            str.append(i->getVar("loc_rowid"));
            str.append("\nCommon Reference: ");
            str.append(i->getVar("pl_name"));
            str.append("\nOrbital Period [Days]: ");
            str.append(i->getVar("pl_orbper"));
            str.append("\nEccentricity: ");
            str.append(i->getVar("pl_orbeccen"));
            str.append("\nInclination [Degrees]: ");
            str.append(i->getVar("pl_orbincl"));
            str.append("\nPlanet Mass [Jupiter Mass]: ");
            str.append(i->getVar("pl_bmassj"));
            str.append("\nPlanet Radius: ");
            str.append(i->getVar("pl_radj"));
            str.append("\nEffective Temperature [K]: ");
            str.append(i->getVar("st_teff"));
            return str;
        }


     }
    return str;
}

QVector<int> star::getCurrentPlanetIds(){
    QVector<int> tmp;
    QVector<planet>::iterator i;
    for(i = planetVector.begin();i != planetVector.end();++i){
        tmp.push_back(i->getVar("loc_rowid").toInt());
    }
    return tmp;
}




//vector<planet> getPlanets(){return planets;}

