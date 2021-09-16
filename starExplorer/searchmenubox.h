#ifndef SEARCHMENUBOX_H
#define SEARCHMENUBOX_H

#include <QWidget>

#include <QDialog>
#include <QString>
#include <QSqlQuery>
#include <QSqlError>
#include <QSqlDatabase>
#include <QSqlTableModel>
#include <QtWidgets>
#include <QTableView>
#include <stdlib.h>
#include <QSqlRelationalTableModel>
#include <iostream>
using namespace std;
#include <QModelIndexList>
#include <QMouseEvent>
#include <QPushButton>



QT_BEGIN_NAMESPACE
class QAction;
class QDialogButtonBox;
class QGroupBox;
class QLabel;
class QLineEdit;
class QMenu;
class QMenuBar;
class QPushButton;
class QTextEdit;
QT_END_NAMESPACE

class SearchMenuBox : public QWidget
{
    Q_OBJECT
public:
    explicit SearchMenuBox(QWidget *parent = nullptr);
    ~SearchMenuBox();
    // Functions to create visual elements
    void createMenu();
    QGroupBox* createSearchGroupBox();
    void createFilterGroupBox();

    QString getSearchResult();
    QSqlDatabase OpenDB();

    void searchForPosition(QString X,QString Y,QString Z);
    void searchForName(QString NAME);
    void searchForNameAndPos(QString NAME,QString X,QString Y,QString Z);
    void clearFields();

    QTableView * view;
    int getRowId();




private:

    // Objects
    QMenuBar *menuBar;
    QGroupBox *mainsearchGroupBox;

    QMenu *fileMenu;
    QAction *exitAction;

    QLineEdit * searchfield;
    QLineEdit * xfield;
    QLineEdit * yfield;
    QLineEdit * zfield;

    QString searchingText; //variable to store the searched name
    QString searchingPosx;
    QString searchingPosy;
    QString searchingPosz;
    QSqlQuery searchSQL;
    QPushButton * searchbutton;
    QPushButton * backbutton;
    QString modelFilter = "";
    QSqlTableModel *model;


    QVBoxLayout * V2layout1 = new QVBoxLayout;
    QComboBox * combobox = new QComboBox;


//    QSqlTableModel *model = new QSqlTableModel;

    int tableRowIdSelected = -1;





signals:
    void backButtonPressed(bool isPressed);
    void viewStarButtonPressed(bool isPressed);
public slots:
    void dbSearch();
    void menuBack();
    void viewStar();
    void onTableClicked(const QModelIndex &index);
    void changeDbTable(const QString&);
};

#endif // SEARCHMENUBOX_H
