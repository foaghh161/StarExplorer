#include "searchmenubox.h"
#include <QSqlDatabase>
#include <QSqlQuery>
#include <db.h>
#include <QDebug>
#include <QThread>


SearchMenuBox::SearchMenuBox(QWidget *parent) : QWidget(parent)
{
    //Create the visual elements
//    createSearchGroupBox();
    //createFilterGroupBox();

    // Set them to the window
    setWindowTitle(tr("Star Explorer"));
}

SearchMenuBox::~SearchMenuBox(){

}

void SearchMenuBox::clearFields(){ //clears the search fields
    searchfield->clear();
    xfield->clear();
    yfield->clear();
    zfield->clear();
    hide();
}

//QSqlDatabase SearchMenuBox::OpenDB(){
//    QSqlDatabase db = QSqlDatabase::addDatabase("QPSQL");
//    db.setHostName("basen.oru.se");
//    db.setDatabaseName("grupp2basen");
//    db.setUserName("grupp2");
//    db.setPassword("strutsmatta");
//    db.setConnectOptions("connect_timeout=1");
//    bool ok = db.open();
//    if (ok){
//        cout << "DB open!" << endl;
//    }else{
//       cout << "DB failed to open." << endl;
//    }
//    return db;
//}

void SearchMenuBox::searchForPosition(QString X,QString Y,QString Z){
//    modelFilter.clear();
//    modelFilter.append("x = ");
//    modelFilter.append(X);
//    modelFilter.append(" AND y = ");
//    modelFilter.append(Y);
//    modelFilter.append(" AND z = ");
//    modelFilter.append(Z);
//    model->setFilter(modelFilter);
    int betweenSize = 1.5;
    double i;
    modelFilter.clear();
    modelFilter.append("x BETWEEN ");
    i = X.toDouble()-betweenSize;
    modelFilter.append(QString::number(i));
    modelFilter.append(" AND ");
    i = X.toDouble()+betweenSize;
    modelFilter.append(QString::number(i));

    modelFilter.append(" AND ");
    modelFilter.append("y BETWEEN ");
    i = Y.toDouble()-betweenSize;
    modelFilter.append(QString::number(i));
    modelFilter.append(" AND ");
    i = Y.toDouble()+betweenSize;
    modelFilter.append(QString::number(i));

    modelFilter.append(" AND ");
    modelFilter.append("z BETWEEN ");
    i = Z.toDouble()-betweenSize;
    modelFilter.append(QString::number(i));
    modelFilter.append(" AND ");
    i = Z.toDouble()+betweenSize;
    modelFilter.append(QString::number(i));
    model->setFilter(modelFilter);
}

void SearchMenuBox::searchForName(QString NAME){
    modelFilter.clear();
    modelFilter.append("LOWER(proper) LIKE LOWER('%");
    modelFilter.append(NAME);
    modelFilter.append("%')");
    model->setFilter(modelFilter);
}

void SearchMenuBox::searchForNameAndPos(QString NAME,QString X,QString Y,QString Z){
    modelFilter.clear();
    modelFilter.append("LOWER(proper) LIKE LOWER('%");
    modelFilter.append(NAME);
    modelFilter.append("%')");

    int betweenSize = 1.5;
    double i;
    modelFilter.append(" AND x BETWEEN ");
    i = X.toDouble()-betweenSize;
    modelFilter.append(QString::number(i));
    modelFilter.append(" AND ");
    i = X.toDouble()+betweenSize;
    modelFilter.append(QString::number(i));

    modelFilter.append(" AND ");
    modelFilter.append("y BETWEEN ");
    i = Y.toDouble()-betweenSize;
    modelFilter.append(QString::number(i));
    modelFilter.append(" AND ");
    i = Y.toDouble()+betweenSize;
    modelFilter.append(QString::number(i));

    modelFilter.append(" AND ");
    modelFilter.append("z BETWEEN ");
    i = Z.toDouble()-betweenSize;
    modelFilter.append(QString::number(i));
    modelFilter.append(" AND ");
    i = Z.toDouble()+betweenSize;
    modelFilter.append(QString::number(i));
    model->setFilter(modelFilter);
}

void SearchMenuBox::dbSearch(){ //search button pressed
    QString NAME = searchfield->text();
    QString x = xfield->text();
    QString y = yfield->text();
    QString z = zfield->text();
    if(combobox->currentText() == "Star"){ //searching for a star
        if (!(NAME.isEmpty() && x.isEmpty() && y.isEmpty() && z.isEmpty())){ //atleast one field is not empty
            if (!(NAME.isEmpty() || x.isEmpty() || y.isEmpty() || z.isEmpty())){//all of the fields have data, search for name AND position
                if(x.toFloat() && y.toFloat() && z.toFloat()){ //x,y,z are numbers
                    searchForNameAndPos(NAME,x,y,z);
                    clearFields();
                    cout << "You searched for the name and position " << NAME.toLocal8Bit().constData() << "," << x.toLocal8Bit().constData() << "," << y.toLocal8Bit().constData() << "," << z.toLocal8Bit().constData() << endl;
                }else{
                    cout << "Could not search for the given name and position." << endl;
                }
            }
            else if (NAME.isEmpty()) { //name is empty, therefore a position must have been entered
                if (x.isEmpty() || y.isEmpty() || z.isEmpty()){ //one of the fields in the position is not filled
                    QMessageBox::information(this, tr("Empty Field"),
                        tr("Please enter the position properly."));
                    return;
                }else{ // search for position
                    if(x.toFloat() && y.toFloat() && z.toFloat()){// check if x,y,z is actually floats and not strings (containing something else than a number)
                        cout << "You searched for the position " << x.toLocal8Bit().constData() << "," << y.toLocal8Bit().constData() << "," << z.toLocal8Bit().constData() << endl;
                        searchForPosition(x,y,z);
                        clearFields();
                    }else{
                        cout << "Could not search for the given position." << endl;
                    }
                }
            }
            else if(!NAME.isEmpty() && x.isEmpty() && y.isEmpty() && z.isEmpty()){ //only the name field is filled
                cout << "You searched for the name " << NAME.toLocal8Bit().constData() << endl;
                searchForName(NAME);
                clearFields();
            }
            else{ //the name and part of position entered, one of the position fields are empty
                QMessageBox::information(this, tr("Empty Field"),
                    tr("Please enter a name and/or position properly."));
                return;
            }
        }
        else{
            if(modelFilter.size() != 0){
                modelFilter.clear();
                model->setFilter(modelFilter);
            }
        }
    }
    else if (combobox->currentText() == "Planet"){ //searching for a planet

    }
}

void SearchMenuBox::menuBack(){
    emit backButtonPressed(true);
}

void SearchMenuBox::viewStar(){
    if (tableRowIdSelected >= 0 && combobox->currentText() == "Star"){
        qDebug() << "Viewing star from search menu with id " << tableRowIdSelected;
        emit viewStarButtonPressed(true);
    }else{
        qDebug() << "Could not view star from search menu...";
    }
}

void SearchMenuBox::onTableClicked(const QModelIndex &index){
    if (index.isValid()) {
        int idOfRow = index.sibling(index.row(), 0).data().toInt(); //id of the star in the clicked row
        tableRowIdSelected = idOfRow;
    }
}

int SearchMenuBox::getRowId(){
    return tableRowIdSelected;
}

void SearchMenuBox::changeDbTable(const QString&){ //change which table in DB to inspect
    qDebug() << "Changing table in search function to " << combobox->currentText();
    if(combobox->currentText() == "Star"){
        V2layout1->setEnabled(true); //show check boxes for star table (red giants etc)

        model->setTable("star"); //choose what table/view in the database to show
        model->select();

        //View
        view->setModel(model); //view the chosen model
        view->setSelectionMode(QAbstractItemView::SingleSelection);
        view->resizeColumnsToContents();
        view->setEditTriggers(QAbstractItemView::NoEditTriggers);
        view->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
        view->setSelectionBehavior(QAbstractItemView::SelectRows);

        for (int i = 0; i < 40; i++){ //hide columns from chosen table
            if (i != 6 && i != 17 && i != 18 && i != 19){
                view->hideColumn(i);
            }else{
                view->setColumnWidth(i,100); //set width of each column that is showed
            }
        }
    }else if (combobox->currentText() == "Planet"){
        V2layout1->setEnabled(false); //hide the checkboxes used for star table

        model->setTable("planets"); //choose what table/view in the database to show
        model->select();

        //View
        view->setModel(model); //view the chosen model
        view->setSelectionMode(QAbstractItemView::SingleSelection);
        view->resizeColumnsToContents();
        view->setEditTriggers(QAbstractItemView::NoEditTriggers);
        view->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
        view->setSelectionBehavior(QAbstractItemView::SelectRows);

        for (int i = 0; i < 40; i++){ //hide columns from chosen table
            if (i != 21 && i != 1 && i!= 24){
                view->hideColumn(i);
            }else{
                view->setColumnWidth(i,100); //set width of each column that is showed
            }
        }
    }
}

QGroupBox* SearchMenuBox::createSearchGroupBox()
{
    //Groupbox
    mainsearchGroupBox = new QGroupBox;
    //Search fields labels
    QLabel * searchlabel = new QLabel("Name");
    QLabel * xlabel = new QLabel ("X-axis");
    QLabel * ylabel = new QLabel ("Y-axis");
    QLabel * zlabel = new QLabel ("Z-axis");
    //Search fields
    searchfield = new QLineEdit();
    xfield = new QLineEdit();
    yfield = new QLineEdit();
    zfield = new QLineEdit();
    //Search button
    QPushButton * searchbutton = new QPushButton;
    searchbutton->setText("Search");
    searchingText = "";
    //Check boxes
    QCheckBox * redGiants = new QCheckBox;
    QCheckBox * superCool = new QCheckBox;
    //Check box labels
    QLabel * redGiantsLabel = new QLabel("Red Giants");
    QLabel * superCoolLabel = new QLabel("Super Cool");
    //Back button
    QPushButton * backbutton = new QPushButton;
    backbutton->setText("Home");
    //View star button
    QPushButton * viewStarButton = new QPushButton;
    viewStarButton->setText("View Star");
    //combo box
    combobox->addItem("Star");
    combobox->addItem("Planet");



    model = new QSqlTableModel;
    if(combobox->currentText() == "Star"){
        model->setTable("star"); //choose what table/view in the database to show
        model->select();

        //View
        view = new QTableView;
        view->setModel(model); //view the chosen model
        view->setSelectionMode(QAbstractItemView::SingleSelection);
    //    view->setSelectionBehavior(QAbstractItemView::SelectRows);
        view->resizeColumnsToContents();
        view->setEditTriggers(QAbstractItemView::NoEditTriggers);
        view->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
        view->setSelectionBehavior(QAbstractItemView::SelectRows);
    //    view->setMinimumHeight(height());


        for (int i = 0; i < 40; i++){ //hide columns from chosen table
            if (i != 6 && i != 17 && i != 18 && i != 19){
                view->hideColumn(i);
            }else{
                view->setColumnWidth(i,100); //set width of each column that is showed
            }
        }
    }else if(combobox->currentText() == "Planet"){
        model->setTable("planet"); //choose what table/view in the database to show
        model->select();

        //View
        view = new QTableView;
        view->setModel(model); //view the chosen model
        view->setSelectionMode(QAbstractItemView::SingleSelection);
        view->resizeColumnsToContents();
        view->setEditTriggers(QAbstractItemView::NoEditTriggers);
        view->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
        view->setSelectionBehavior(QAbstractItemView::SelectRows);


        for (int i = 0; i < 40; i++){ //hide columns from chosen table
            if (i != 2 && i != 1){
                view->hideColumn(i);
            }else{
                view->setColumnWidth(i,100); //set width of each column that is showed
            }
        }
    }

    view->show();

    //Layout
//    QHBoxLayout * H1layout1 = new QHBoxLayout;
//    H1layout1->addWidget(searchlabel);
//    H1layout1->addWidget(xlabel);
//    H1layout1->addWidget(ylabel);
//    H1layout1->addWidget(zlabel);

//    QHBoxLayout * H1layout2 = new QHBoxLayout;
//    H1layout2->addWidget(searchfield);
//    H1layout2->addWidget(xfield);
//    H1layout2->addWidget(yfield);
//    H1layout2->addWidget(zfield);

//    QVBoxLayout * V1layout = new QVBoxLayout;
//    V1layout->addStretch(0.2);
//    V1layout->addLayout(H1layout1);
//    V1layout->addStretch(0.2);
//    V1layout->addLayout(H1layout2);
//    V1layout->addStretch(9.5);
//    //V1layout->addWidget(searchlabel);

//    QHBoxLayout * H2layout1 = new QHBoxLayout;
//    H2layout1->addWidget(stars);
//    H2layout1->addWidget(starsLabel);
//    H2layout1->addWidget(redGiants);
//    H2layout1->addWidget(redGiantsLabel);

//    QHBoxLayout * H2layout2 = new QHBoxLayout;
//    H2layout2->addWidget(planets);
//    H2layout2->addWidget(planetsLabel);
//    H2layout2->addWidget(superCool);
//    H2layout2->addWidget(superCoolLabel);

//    QVBoxLayout * V2Layout = new QVBoxLayout;
//    V2Layout->addLayout(H2layout1);
//    V2Layout->addLayout(H2layout2);

//    QHBoxLayout * H3Layout = new QHBoxLayout;
//    H3Layout->addLayout(V1layout);
//    H3Layout->addLayout(V2Layout);
//    H3Layout->addWidget(searchbutton);
//    H3Layout->addWidget(viewStarButton);
//    H3Layout->addWidget(backbutton);

//    QVBoxLayout * V3Layout = new QVBoxLayout;
//    V3Layout->addLayout(H3Layout);
//    V3Layout->addWidget(view,1000);
//    V3Layout->addStretch(9.5);

    //Layout second attempt
    QHBoxLayout * H1layout1 = new QHBoxLayout;
    H1layout1->addWidget(searchlabel);
    H1layout1->addWidget(xlabel);
    H1layout1->addWidget(ylabel);
    H1layout1->addWidget(zlabel);

    QHBoxLayout * H1layout2 = new QHBoxLayout;
    H1layout2->addWidget(searchfield);
    H1layout2->addWidget(xfield);
    H1layout2->addWidget(yfield);
    H1layout2->addWidget(zfield);

    QVBoxLayout * V1layout = new QVBoxLayout;
    V1layout->addStretch(0.2);
    V1layout->addLayout(H1layout1);
    V1layout->addStretch(0.2);
    V1layout->addLayout(H1layout2);
    V1layout->addWidget(view,500);


    QVBoxLayout * H2layout1 = new QVBoxLayout;

    H2layout1->addWidget(viewStarButton);
    H2layout1->addWidget(backbutton);

    viewStarButton->setFixedWidth(500);
    viewStarButton->setFixedHeight(50);

    searchbutton->setFixedWidth(500);
    searchbutton->setFixedHeight(50);

    backbutton->setFixedWidth(500);
    backbutton->setFixedHeight(50);

    combobox->setFixedWidth(500);
    combobox->setFixedHeight(50);




//    QVBoxLayout * V2layout1 = new QVBoxLayout;
    V2layout1->addWidget(searchbutton);
    V2layout1->addWidget(combobox);
    V2layout1->addStretch(8);
    //checkboxes (to do?)
//    V2layout1->addWidget(redGiants);
//    V2layout1->addWidget(redGiantsLabel);
//    V2layout1->addStretch(5);
//    V2layout1->addWidget(superCool);
//    V2layout1->addWidget(superCoolLabel);
//    V2layout1->addStretch(5);


    QVBoxLayout * V2layout2 = new QVBoxLayout;
    //V2layout2->addStretch(5);
    V2layout2->addLayout(V2layout1);
    //V2layout2->addStretch(8);
    V2layout2->addLayout(H2layout1);

    QVBoxLayout * V2layout3 = new QVBoxLayout;

    //Check boxes
    V2layout3->addWidget(redGiants);
    V2layout3->addWidget(redGiantsLabel);
    V2layout3->addStretch(5);
    V2layout3->addWidget(superCool);
    V2layout3->addWidget(superCoolLabel);
    V2layout3->addStretch(5);

//    V2layout1->addLayout(V2layout3);


    QHBoxLayout * H2layout2 = new QHBoxLayout;
    H2layout2->addLayout(V1layout);
//    H2layout2->addLayout(V2layout3);
    H2layout2->addLayout(V2layout2);




    connect(searchbutton, SIGNAL(clicked()), this, SLOT(dbSearch()));
    connect(backbutton, SIGNAL(clicked()), this, SLOT(menuBack()));
    connect(viewStarButton, SIGNAL(clicked()), this, SLOT(viewStar()));
    connect(view, SIGNAL(clicked(const QModelIndex &)), this, SLOT(onTableClicked(const QModelIndex &)));
    connect(combobox, SIGNAL(currentIndexChanged(const QString&)), this, SLOT(changeDbTable(const QString&)));

    mainsearchGroupBox->setLayout(H2layout2); // for second version layout attempt only
//    mainsearchGroupBox->setLayout(V3Layout); // for first version layout only

    return mainsearchGroupBox;
}




