#include "db.h"
/**
 * @brief database::database
 * Default constructor
 */
database::database()
{
    this->db = QSqlDatabase::addDatabase("QPSQL");
    this->db.setHostName("basen.oru.se");
    this->db.setDatabaseName("grupp2basen");
    this->db.setUserName("grupp2");
    this->db.setPassword("strutsmatta");
    this->db.setConnectOptions("connect_timeout=2");
    if(this->db.open()){
        qDebug() << "Connected to server basen.oru.se";
    }
}

void database::insertStar(QString table, QMap<QString, QLineEdit*>* values){
    QSqlQuery q;
    QString prepareString;
    QString chosenColumns;
    chosenColumns += "hip,hd,hr,gl,bf,proper,ra,dec,dist,pmra,pmdec,rv,mag,absmag,spect,";
    chosenColumns += "ci,x,y,z,vx,vy,vz,rarad,decrad,pmrarad,pmdecrad,bayer,flam,con,comp,";
    chosenColumns += "comp_primary,base,lum,var,var_min,var_max";
    prepareString += "INSERT INTO "+table+" ("+chosenColumns+") VALUES (:hip, :hd, :hr, ";
    prepareString += ":gl, :bf, :proper, ";
    prepareString += ":ra, :dec, :dist, :pmra, :pmdec, :rv, :mag, :absmag, :spect, :ci, ";
    prepareString += ":x, :y, :z, :vx, :vy, :vz, :rarad, :decrad, :pmrarad, :pmdecrad, ";
    prepareString += ":bayer, :flam, :con, :comp, :comp_primary, :base, :lum, :var, ";
    prepareString += ":var_min, :var_max)";
    if(q.prepare(prepareString))    //Add columns here
        qDebug() << "Prepared";
    q.bindValue(":hip", values->value("hipparcosId")->text().toInt());
    q.bindValue(":hd",(values->value("henryId")->text() == "")?QVariant(QVariant::Int) : values->value("henryId")->text().toInt());
    q.bindValue(":hr",(values->value("harvardId")->text() == "")?QVariant(QVariant::Int) : values->value("harvardId")->text().toInt());
    q.bindValue(":gl",(values->value("glieseId")->text() == "")?QVariant(QVariant::Int) : values->value("glieseId")->text().toInt());
    q.bindValue(":bf", values->value("bayerFlamsteed")->text());
    q.bindValue(":proper", values->value("starName")->text());
    q.bindValue(":ra",(values->value("rightAscension")->text() == "")?QVariant(QVariant::Double) : values->value("rightAscension")->text().toDouble());
    q.bindValue(":dec",(values->value("declination")->text() == "")?QVariant(QVariant::Double) : values->value("declination")->text().toDouble());
    // TODO:
    //q.bindValue(":dist", values->value("")->text()); // Compute distance from coords
    q.bindValue(":pmra",(values->value("pmra")->text() == "")?QVariant(QVariant::Double) : values->value("pmra")->text().toDouble());
    q.bindValue(":pmdec",(values->value("pmdec")->text() == "")?QVariant(QVariant::Double) : values->value("pmdec")->text().toDouble());
    q.bindValue(":rv",(values->value("radialVelocity")->text() == "")?QVariant(QVariant::Double) : values->value("radialVelocity")->text().toDouble());
    q.bindValue(":mag",(values->value("magnitude")->text() == "")?QVariant(QVariant::Double) : values->value("magnitude")->text().toDouble());
    q.bindValue(":absmag",(values->value("absMagnitude")->text() == "")?QVariant(QVariant::Double) : values->value("absMagnitude")->text().toDouble());
    q.bindValue(":spect", values->value("spectralType")->text());
    q.bindValue(":ci",(values->value("colorIndex")->text() == "")?QVariant(QVariant::Double) : values->value("colorIndex")->text().toDouble());
    q.bindValue(":x",(values->value("xCoord")->text() == "")?QVariant(QVariant::Double) : values->value("xCoord")->text().toDouble());
    q.bindValue(":y",(values->value("yCoord")->text() == "")?QVariant(QVariant::Double) : values->value("yCoord")->text().toDouble());
    q.bindValue(":z",(values->value("zCoord")->text() == "")?QVariant(QVariant::Double) : values->value("zCoord")->text().toDouble());
    q.bindValue(":vx",(values->value("xVelocity")->text() == "")?QVariant(QVariant::Double) : values->value("xVelocity")->text().toDouble());
    q.bindValue(":vy",(values->value("yVelocity")->text() == "")?QVariant(QVariant::Double) : values->value("yVelocity")->text().toDouble());
    q.bindValue(":vz",(values->value("zVelocity")->text() == "")?QVariant(QVariant::Double) : values->value("zVelocity")->text().toDouble());
    q.bindValue(":rarad",(values->value("rarad")->text() == "")?QVariant(QVariant::Double) : values->value("rarad")->text().toDouble());
    q.bindValue(":decrad",(values->value("decrad")->text() == "")?QVariant(QVariant::Double) : values->value("decrad")->text().toDouble());
    q.bindValue(":pmrarad",(values->value("pmrarad")->text() == "")?QVariant(QVariant::Double) : values->value("pmrarad")->text().toDouble());
    q.bindValue(":pmdecrad",(values->value("pmdecrad")->text() == "")?QVariant(QVariant::Double) : values->value("pmdecrad")->text().toDouble());
    q.bindValue(":bayer", values->value("bayer")->text());
    q.bindValue(":flam", values->value("flam")->text());
    q.bindValue(":con", values->value("constellation")->text());
    q.bindValue(":comp",(values->value("companion")->text() == "")?QVariant(QVariant::Int) : values->value("companion")->text().toInt());
    q.bindValue(":comp_primary",(values->value("companionPrimary")->text() == "")?QVariant(QVariant::Int) : values->value("companionPrimary")->text().toInt());
    q.bindValue(":base", values->value("companionBase")->text());
    q.bindValue(":lum",(values->value("luminosity")->text() == "")?QVariant(QVariant::Double) : values->value("luminosity")->text().toDouble());
    q.bindValue(":var", values->value("standardVariable")->text());
    q.bindValue(":var_min",(values->value("variableMin")->text() == "")?QVariant(QVariant::Double) : values->value("variableMin")->text().toDouble());
    q.bindValue(":var_max",(values->value("variableMax")->text() == "")?QVariant(QVariant::Double) : values->value("variableMax")->text().toDouble());

    if(q.exec()){
            qDebug() << "Insert succesful";
    }
    else{
        qDebug() << q.lastError();
    }
}

void database::insertPlanet(QString table, QMap<QString, QLineEdit*>* values){

    QSqlQuery q;
    QString prepareString;
    QString chosenColumns;
    chosenColumns += "pl_hostname, pl_pnum, pl_orbper, pl_orbsmax, pl_orbeccen, pl_orbincl, pl_bmassj, pl_bmassprov, pl_radj, pl_dens,";
    chosenColumns += "ra_str ,ra ,dec_str, dec, st_dist, st_optmag, st_optband, st_teff, st_mass, st_rad, pl_name, pl_disc, hd_name, hip_name";
    prepareString += "INSERT INTO "+table+" ("+chosenColumns+") VALUES (:pl_hostname, :pl_pnum, :pl_orbper, ";
    prepareString += ":pl_orbsmax, :pl_orbeccen, :pl_orbincl, ";
    prepareString += ":pl_bmassj, :pl_bmassprov, :pl_radj, :pl_dens, ";
    prepareString += ":ra_str, :ra, :dec_str, :dec, :st_dist, :st_optmag, ";
    prepareString += ":st_optband, :st_teff, :st_mass, :st_rad, :pl_name, :pl_disc, :hd_name, :hip_name)";
    qDebug() << prepareString;
    if(q.prepare(prepareString))    //Add columns here
        qDebug() << "Prepared";
    q.bindValue(":pl_hostname", values->value("hostName")->text());
    q.bindValue(":pl_pnum",(values->value("numberOfPlanets")->text() == "")?QVariant(QVariant::Int) : values->value("numberOfPlanets")->text().toInt());
    q.bindValue(":pl_orbper",(values->value("orbitalPeriod")->text() == "")?QVariant(QVariant::Double) : values->value("orbitalPeriod")->text().toDouble());
    q.bindValue(":pl_orsbmax",(values->value("orbitSemiAxis")->text() == "")?QVariant(QVariant::Double) : values->value("orbitSemiAxis")->text().toDouble());
    q.bindValue(":pl_orbeccen",(values->value("eccentricity")->text() == "")?QVariant(QVariant::Double) : values->value("eccentricity")->text().toDouble());
    q.bindValue(":pl_orbincl",(values->value("inclination")->text() == "")?QVariant(QVariant::Double) : values->value("inclination")->text().toDouble());
    q.bindValue(":pl_bmassj",(values->value("planetMassJ")->text() == "")?QVariant(QVariant::Double) : values->value("planetMassJ")->text().toDouble());
    q.bindValue(":pl_bmassprov", values->value("planetMassProv")->text());
    q.bindValue(":pl_radj",(values->value("planetRadius")->text() == "")?QVariant(QVariant::Double) : values->value("planetRadius")->text().toDouble());
    q.bindValue(":pl_dens",(values->value("density")->text() == "")?QVariant(QVariant::Double) : values->value("density")->text().toDouble());
    q.bindValue(":ra_str", values->value("rightAscText")->text());
    q.bindValue(":ra", values->value("rightAsc")->text()); //   text?
    q.bindValue(":dec_str", values->value("decText")->text());
    q.bindValue(":dec", values->value("dec")->text());      //  text?
    q.bindValue(":st_dist",(values->value("dist")->text() == "")?QVariant(QVariant::Double) : values->value("dist")->text().toDouble());
    q.bindValue(":st_optmag",(values->value("optMag")->text() == "")?QVariant(QVariant::Double) : values->value("optMag")->text().toDouble());
    q.bindValue(":st_optband", values->value("optMagBand")->text());
    q.bindValue(":st_teff",(values->value("effectiveTempature")->text() == "")?QVariant(QVariant::Double) : values->value("effectiveTempature")->text().toDouble());
    q.bindValue(":st_mass",(values->value("stellarMass")->text() == "")?QVariant(QVariant::Double) : values->value("stellarMass")->text().toDouble());
    q.bindValue(":st_rad",(values->value("stellarRad")->text() == "")?QVariant(QVariant::Double) : values->value("stellarRad")->text().toDouble());
    q.bindValue(":pl_name", values->value("planetName")->text());
    q.bindValue(":pl_disc",(values->value("plDisc")->text() == "")?QVariant(QVariant::Int) : values->value("plDisc")->text().toInt());
    q.bindValue(":hd_name",(values->value("hdNameInt")->text() == "")?QVariant(QVariant::Int) : values->value("hdNameInt")->text().toInt());
    q.bindValue(":hip_name",(values->value("hipparcos")->text() == "")?QVariant(QVariant::Int) : values->value("hipparcos")->text().toInt());

    if(q.exec()){
            qDebug() << "Insert succesful";
    }
    else{
        qDebug() << q.lastQuery();
        qDebug() << q.lastError();
    }
}



void database::deleteRow(QString table, int id){
    QSqlQuery q;

    if(q.prepare("DELETE FROM "+table+" WHERE id = :id"))
        qDebug() << "Delete prepared";
    q.bindValue(":id",id);
    qDebug() << "Do you want to delete row Y/N?";       //Ja/Nej-ruta i UI?
    if(q.exec())
        qDebug() << "exec success";
    else {
        qDebug() << "exec failed";
    }
}

void database::updateTable(QString table, int id, QString cond){
    QSqlQuery q;
    if(q.prepare("UPDATE"+table+ "SET :c WHERE id = :id"))
        qDebug() << "update prepared";
    q.bindValue(":c",cond);
    q.bindValue(":id",id);
    if(q.exec())
        qDebug() << "update executed";
}
