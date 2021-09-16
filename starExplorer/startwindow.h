#ifndef STARTWINDOW_H
#define STARTWINDOW_H

#include <QMainWindow>
#include <QMap>
#include <QtWidgets>
#include <QSqlTableModel>
#include <QSqlQueryModel>
#include <QSqlRecord>
#include <QTableView>
#include <QPaintEvent>
#include <QPainter>

#include "searchmenubox.h"
#include "db.h"
#include "star.h"
#include "galaxyrenderarea.h"
#include "systemrenderarea.h"
#include "planet.h"
#include "skyrenderarea.h"

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
class QStackedWidget;
QT_END_NAMESPACE

class StartWindow : public QMainWindow
{
    Q_OBJECT

public:
    /**
     * @brief StartWindow
     * Constructor sets up all QGroupBoxes used for different views and adds them to
     * a QStackedWidget that handles the views. Also sets up menu bar and
     * dialog windows.
     * @param parent
     */
    StartWindow(QWidget *parent = 0);
    ~StartWindow();

protected:

private:
    void createMenu();
    void createSearchGroupBox_startwindow();
    void createLoginDialog();
    void createStartGroupBox();
    void createGalaxyGroupBox();
    /**
     * @brief createSystemGroupBox
     * @param id, the database id for the star to be displayed.
     */
    void createSystemGroupBox(int id = 0);
    void createAdminGroupBox();
    void createAddFormSetupDialog();
    void createAddSystemFormGroupBox();
    void createAddPlanetFormGroupBox();
    void createChangeFormGroupBox();
    void createChangeFormSetupDialog();
    void createAddSystemSearchFormGroupBox();
    void createChangeSearchPlanetGroupBox();
    void createChangeSearchSystemGroupBox();
    void createChangeSystemFormGroupBox();
    void initInfo();
    void initSkyInfo();
    /**
     * @brief createSkyViewGroupBox
     * @param x, x-coordinate for the star to view the sky from.
     * @param y, y-coordinate for the star to view the sky from.
     * @param z, z-coordinate for the star to view the sky from.
     */
    void createSkyViewGroupBox(double x = 0, double y = 0, double z = 0);
    void searchSystem(QString s);
    int checkDataTypeStar(QString name, QString Datatype);
    int checkDataTypePlanet(QString name, QString Datatype);

    QMenuBar *menuBar;
    QDialogButtonBox *numberOfPlanets;
    QMap<QString, QLineEdit*> addFormMap;
    QMap<QString, QLineEdit*> addFormPlanetMap;
    QLabel *informationLabel;
    QLabel *skyInfoLabel;
    database dbMain;

    GalaxyRenderArea *galaxyRenderArea;
    QLabel *galaxyInformationLabel;
    int currentSystemIdFromGalaxy;

    SearchMenuBox *search;

    QDialog *loginDialog;
    QGroupBox *searchGroupBox_startwindow;
    QGroupBox *searchGroupBox;
    QGroupBox *startGroupBox;
    QGroupBox *galaxyGroupBox;
    QGroupBox *systemGroupBox;
    QGroupBox *adminGroupBox;
    QDialog *addFormSetupDialog;
    QDialog *changeFormSetupDialog;
    QGroupBox *changeSearchSystemGroupBox;
    QGroupBox *changeSearchPlanetGroupBox;
    QGroupBox *changeSystemFormGroupBox;
    QGroupBox *changePlanetFormGroupBox;

    QGroupBox *addSystemFormGroupBox;

    QGroupBox *addPlanetFormGroupBox;
    QGroupBox *addSystemSearchFormGroupBox;
    SystemRenderArea *starRender;

    QGroupBox *skyViewGroupBox;
    SkyRenderArea *skyRenderArea;
    QStackedWidget *stackedWidgets;

    QMenu *fileMenu;
    QAction *exitAction;

    star *currentStar = new star;
    planet currentPlanet;
    bool runPaintEvent = false;

    QLineEdit *searchField;
    bool systemSearchConfirm = false;

    QSqlTableModel *model;


signals:


public slots:
    void on_body_clicked();

    void on_searchButton_clicked();
    void on_search_backButton_clicked();
    void on_searchGroupBox_searchRow_clicked();

    void on_exploreButton_clicked();
    void on_adminButton_clicked();

    void on_galaxyGroupBox_backButton_clicked();
    void on_galaxyGroupBox_systemButton_clicked();
    void on_galaxyGroupBox_idUpdated();

    void on_systemGroupBox_backButton_clicked();
    void on_systemGroupBox_homeButton_clicked();
    void on_systemGroupBox_skyViewButton_clicked();

    void on_loginDialog_loginButton_clicked();
    void on_loginDialog_cancelButton_clicked();

    void on_adminGroupBox_addButton_clicked();
    void on_adminGroupBox_changeButton_clicked();
    void on_adminGroupBox_logoutButton_clicked();

    void on_changeFormSetupDialog_changePlanet_clicked(); // In popup
    void on_changeFormSetupDialog_changeSystem_clicked(); // In popup
    void on_changeFormSetupDialog_cancelButton_clicked();    // In popup

    void on_addFormSetupDialog_addSystemButton_clicked(); // In popup
    void on_addFormSetupDialog_addSearchSystemButton_clicked(); // In popup
    void on_addFormSetupDialog_cancelButton_clicked();    // In popup

    void on_addFormGroupBox_addPlanetButton_clicked(); // in search
    void on_addFormGroupBox_addPlanetConfirmButton_clicked();
    void on_systemSearch_searchButton_clicked();
    void on_changeFormGroupBox_changeSysstemButton_clicked();

    void on_addFormGroupBox_addSystemConfirmButton_clicked();    // In form
    void on_addSystemFormGroupBox_cancelButton_clicked();     // In form

    void on_skyViewGroupBox_homeButton_clicked();
    void on_skyViewGroupBox_backButton_clicked();
    void on_skyViewGroupBox_idUpdated();

    //Test
   // void on_systemGroupBox_InformationClick_clicked();


};

#endif // STARTWINDOW_H
