#include "startwindow.h"

StartWindow::StartWindow(QWidget *parent) : QMainWindow(parent)
{
    createMenu();
    createLoginDialog();
    createStartGroupBox();

    search = new SearchMenuBox;
    searchGroupBox_startwindow = search->createSearchGroupBox();
    connect(search, SIGNAL(backButtonPressed(bool)),
            this,SLOT(on_search_backButton_clicked()));
    connect(search, SIGNAL(viewStarButtonPressed(bool)),
            this,SLOT(on_searchGroupBox_searchRow_clicked()));

    createGalaxyGroupBox();
    createSystemGroupBox();
    createAdminGroupBox();
    createAddFormSetupDialog();
    createChangeFormSetupDialog();
    createSkyViewGroupBox();

    stackedWidgets = new QStackedWidget;
    stackedWidgets->addWidget(startGroupBox);
    stackedWidgets->addWidget(searchGroupBox_startwindow);
    stackedWidgets->addWidget(galaxyGroupBox);
    stackedWidgets->addWidget(systemGroupBox);
    stackedWidgets->addWidget(adminGroupBox);
    stackedWidgets->addWidget(skyViewGroupBox);


    setMenuBar(menuBar);
    setCentralWidget(stackedWidgets);
    setWindowTitle("Star Explorer");

}

StartWindow::~StartWindow()
{

}

void StartWindow::createMenu()
{
    menuBar = new QMenuBar;

    fileMenu = new QMenu(tr("&File"), this);
    exitAction = fileMenu->addAction(tr("E&xit"));
    menuBar->addMenu(fileMenu);

    connect(exitAction, SIGNAL(triggered()), this, SLOT(close()));
}

void StartWindow::createLoginDialog()
{
    // Maybe implement a modal dialog (prevent input to all other parts of program)?
    loginDialog = new QDialog;
    loginDialog->setWindowTitle("Log In");
    QGroupBox *loginGroupBox = new QGroupBox("Enter Password:");
    QGridLayout *layout = new QGridLayout;
    QLineEdit *passwordField = new QLineEdit;
    QPushButton *loginButton = new QPushButton("Log in");
    QPushButton *cancelButton = new QPushButton("Cancel");

    // [Connect]
    connect(cancelButton, SIGNAL(clicked(bool)), this, SLOT(on_loginDialog_cancelButton_clicked()));
    connect(cancelButton, SIGNAL(clicked(bool)), passwordField, SLOT(clear()));
    connect(cancelButton, SIGNAL(clicked(bool)), passwordField, SLOT(setFocus()));
    connect(loginButton, SIGNAL(clicked(bool)), this, SLOT(on_loginDialog_loginButton_clicked()));
    connect(loginButton, SIGNAL(clicked(bool)), passwordField, SLOT(clear()));
    connect(loginButton, SIGNAL(clicked(bool)), passwordField, SLOT(setFocus()));
    // [Layout]
    layout->addWidget(passwordField, 0,0,1,3);
    layout->addWidget(loginButton, 1,1,1,1);
    layout->addWidget(cancelButton, 1,2,1,1);
    loginGroupBox->setLayout(layout);
    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addWidget(loginGroupBox);
    loginDialog->setLayout(mainLayout);
}

void StartWindow::createStartGroupBox()
{
    startGroupBox = new QGroupBox;
    QHBoxLayout *positionLayout = new QHBoxLayout;
    QVBoxLayout *layout = new QVBoxLayout;

    QPushButton *searchButton = new QPushButton("Search");
    QPushButton *exploreButton = new QPushButton("Explore");
    QPushButton *exitButton = new QPushButton("Exit");
    QPushButton *adminButton = new QPushButton("Admin Mode");

    searchButton->setMinimumSize(QSize(160,40));
    exploreButton->setMinimumSize(QSize(160,40));
    exitButton->setMinimumSize(QSize(160,40));

    // [Connect]
    connect(searchButton, SIGNAL(clicked(bool)), this, SLOT(on_searchButton_clicked()));
    connect(exploreButton, SIGNAL(clicked(bool)), this, SLOT(on_exploreButton_clicked()));
    connect(exitButton, SIGNAL(clicked(bool)), this, SLOT(close()));
    connect(adminButton, SIGNAL(clicked(bool)), this, SLOT(on_adminButton_clicked()));

    // [Layout]
    layout->addStretch(5);
    layout->addWidget(searchButton);
    layout->addWidget(exploreButton);
    layout->addWidget(exitButton);
    layout->addStretch(5);
    layout->addWidget(adminButton);
    layout->addStretch(2);
    positionLayout->addStretch();
    positionLayout->addLayout(layout);
    positionLayout->addStretch();

    startGroupBox->setLayout(positionLayout);
}

void StartWindow::createGalaxyGroupBox()
{
    galaxyGroupBox = new QGroupBox;
    QGridLayout *layout = new QGridLayout;
    galaxyRenderArea = new GalaxyRenderArea;
    galaxyInformationLabel = new QLabel;
    galaxyInformationLabel->setText("Shortcuts:\n"
                                    "Use arrow keys to move viewpoint.\n"
                                    "Use + to zoom in and - to zoom out.\n");
    galaxyInformationLabel->setFrameStyle(QFrame::Panel | QFrame::Sunken);
    galaxyInformationLabel->setWordWrap(true);

    QPushButton *backButton = new QPushButton("Back");
    backButton->setMinimumSize(QSize(160,40));
    QPushButton *systemButton = new QPushButton("View System");
    systemButton->setMinimumSize(QSize(160,40));

    // [Connect]
    connect(backButton, SIGNAL(clicked(bool)), this,
            SLOT(on_galaxyGroupBox_backButton_clicked()));
    connect(systemButton, SIGNAL(clicked(bool)), this,
            SLOT(on_galaxyGroupBox_systemButton_clicked()));
    connect(galaxyRenderArea, SIGNAL(idChanged(bool)), this,
            SLOT(on_galaxyGroupBox_idUpdated()));

    // [Layout]
    layout->addWidget(galaxyRenderArea,0,0,3,3);
    layout->addWidget(galaxyInformationLabel,0,3,3,1);
    layout->addWidget(backButton,3,3,1,1);
    layout->addWidget(systemButton,3,2,1,1);
    galaxyGroupBox->setLayout(layout);
}

void StartWindow::createSystemGroupBox(int id)
{
    currentSystemIdFromGalaxy = id;
    //QPushButton *InformationClick = new QPushButton("Info");
    //InformationClick->setMinimumSize(QSize(160,40));

    systemGroupBox = new QGroupBox;
    QGridLayout *layout = new QGridLayout;

    starRender = new SystemRenderArea;


    informationLabel = new QLabel;
    informationLabel->setText("Click something!");
    informationLabel->setFrameStyle(QFrame::Panel | QFrame::Sunken);
    informationLabel->setWordWrap(true);



    QPushButton *backButton = new QPushButton("Back");
    backButton->setMinimumSize(QSize(160,40));
    QPushButton *homeButton = new QPushButton();
    homeButton->setMinimumSize((QSize(160,40)));

    QPixmap homemap("/home/EDUNET.ORU.SE/marnyh161/QtProjects/actual/starExplorer/home.png");
    QIcon homeIcon(homemap);
    homeButton->setIcon(homeIcon);
    homeButton->setIconSize(QSize(65,30));


    QPushButton *skyViewButton = new QPushButton("Sky View");
    skyViewButton->setMinimumSize(QSize(160,40));

    // [Connect]
    connect(backButton, SIGNAL(clicked(bool)), this,
            SLOT(on_systemGroupBox_backButton_clicked()));
    connect(homeButton, SIGNAL(clicked(bool)), this,SLOT(on_systemGroupBox_homeButton_clicked()));
    //connect(InformationClick,SIGNAL(clicked(bool)),this,SLOT(on_systemGroupBox_InformationClick_clicked()));
    connect(skyViewButton, SIGNAL(clicked(bool)), this,
            SLOT(on_systemGroupBox_skyViewButton_clicked()));

    connect(starRender,SIGNAL(systemLabelChanged(bool)),this,SLOT(on_body_clicked()));

    // [Layout]
    layout->addWidget(skyViewButton,3,2,1,1);
    layout->addWidget(informationLabel,0,3,3,1);
    layout->addWidget(starRender,0,0,3,3);
    //layout->addWidget(InformationClick,0,1,1,1);
    layout->addWidget(backButton,3,3,1,1);
    layout->addWidget(homeButton, 0,3,1,1);
    systemGroupBox->setLayout(layout);
}

void StartWindow::createSkyViewGroupBox(double x, double y, double z)
{
   skyViewGroupBox = new QGroupBox;
   QGridLayout *layout = new QGridLayout;
   skyRenderArea = new SkyRenderArea;
   skyRenderArea->setCenterX(x);
   skyRenderArea->setCenterY(y);
   skyRenderArea->setCenterZ(z);
   QPushButton *homeButton = new QPushButton("Home");
   homeButton->setMinimumSize((QSize(160,40)));
   QPushButton *backButton = new QPushButton("Back");
   backButton->setMinimumSize(QSize(160,40));
   skyInfoLabel = new QLabel;
   skyInfoLabel->setFrameStyle(QFrame::Panel | QFrame::Sunken);
   skyInfoLabel->setWordWrap(true);
   this->initSkyInfo();


   // [Connect]

   connect(backButton, SIGNAL(clicked(bool)), this,
           SLOT(on_skyViewGroupBox_backButton_clicked()));
   connect(homeButton, SIGNAL(clicked(bool)), this,SLOT(on_skyViewGroupBox_homeButton_clicked()));
   connect(skyRenderArea, SIGNAL(idChanged(bool)), this,
           SLOT(on_skyViewGroupBox_idUpdated()));

   // [Layout]
   layout->addWidget(skyRenderArea,0,0,3,3);
   layout->addWidget(backButton,3,3,1,1);
   layout->addWidget(skyInfoLabel,0,3,3,1);
   layout->addWidget(homeButton, 0,3,1,1);
   skyViewGroupBox->setLayout(layout);
}

void StartWindow::createAdminGroupBox()
{
    adminGroupBox = new QGroupBox;
    QHBoxLayout *positionLayout = new QHBoxLayout;
    QVBoxLayout *layout = new QVBoxLayout;

    QPushButton *addButton = new QPushButton("Add New");
    QPushButton *changeButton = new QPushButton("Change Existing");
    QPushButton *logoutButton = new QPushButton("Log Out");

    addButton->setMinimumSize(QSize(160,40));
    changeButton->setMinimumSize(QSize(160,40));
    logoutButton->setMinimumSize(QSize(160,40));

    // [Connect]
    connect(addButton, SIGNAL(clicked(bool)), this, SLOT(on_adminGroupBox_addButton_clicked()));
    connect(changeButton, SIGNAL(clicked(bool)), this, SLOT(on_adminGroupBox_changeButton_clicked()));
    connect(logoutButton, SIGNAL(clicked(bool)), this, SLOT(on_adminGroupBox_logoutButton_clicked()));

    // [Layout]
    layout->addStretch();
    layout->addWidget(addButton);
    layout->addWidget(changeButton);
    layout->addWidget(logoutButton);
    layout->addStretch();
    positionLayout->addStretch();
    positionLayout->addLayout(layout);
    positionLayout->addStretch();
    adminGroupBox->setLayout(positionLayout);
}

void StartWindow::createAddFormSetupDialog()
{
    addFormSetupDialog = new QDialog;
    addFormSetupDialog->setWindowTitle("Choose what to add");
    addFormSetupDialog->setMinimumWidth(265);
    QGridLayout *layout = new QGridLayout;
    QPushButton *addSystemButton = new QPushButton("Add System");
    QPushButton *addPlanetButton = new QPushButton("Add Planet");
    QPushButton *cancelButton = new QPushButton("Cancel");
    // [Connect]
    connect(addSystemButton, SIGNAL(clicked(bool)), this,
            SLOT(on_addFormSetupDialog_addSystemButton_clicked()));
    connect(addPlanetButton, SIGNAL(clicked(bool)), this,
            SLOT(on_addFormSetupDialog_addSearchSystemButton_clicked()));
    connect(cancelButton, SIGNAL(clicked(bool)), this,
            SLOT(on_addFormSetupDialog_cancelButton_clicked()));

    // [Layout]
    layout->addWidget(addPlanetButton, 0,0,1,2);
    layout->addWidget(addSystemButton, 1,0,1,1);
    layout->addWidget(cancelButton, 1,1,1,1);
    addFormSetupDialog->setLayout(layout);
}

void StartWindow::createAddSystemFormGroupBox()
{
    addSystemFormGroupBox = new QGroupBox("Add new system");
    QVBoxLayout *layout = new QVBoxLayout;
    QFormLayout *formLayout = new QFormLayout;

    QLineEdit *hipparcosIdField = new QLineEdit;
    QLineEdit *henryIdField = new QLineEdit;
    QLineEdit *harvardIdField = new QLineEdit;
    QLineEdit *glieseIdField = new QLineEdit;
    QLineEdit *bayerFlamsteedField = new QLineEdit;
    QLineEdit *rightAcensionField = new QLineEdit;
    QLineEdit *declinationField = new QLineEdit;
    QLineEdit *starNameField = new QLineEdit; //proper
    //QLineEdit *distanceField = new QLineEdit;
    QLineEdit *pmraField = new QLineEdit;
    QLineEdit *pmdecField = new QLineEdit;
    QLineEdit *radialVelocity = new QLineEdit;
    QLineEdit *magnitudeField = new QLineEdit;
    QLineEdit *absMagnitudeField = new QLineEdit;
    QLineEdit *spectralTypeField = new QLineEdit;
    QLineEdit *colorIndexField = new QLineEdit;
    QLineEdit *xCoordField = new QLineEdit;
    QLineEdit *yCoordField = new QLineEdit;
    QLineEdit *zCoordField = new QLineEdit;
    QLineEdit *xVelocityField = new QLineEdit;
    QLineEdit *yVelocityField = new QLineEdit;
    QLineEdit *zVelocityField = new QLineEdit;
    QLineEdit *raradField = new QLineEdit;
    QLineEdit *decradField = new QLineEdit;
    QLineEdit *pmraradField = new QLineEdit;
    QLineEdit *pmdecradField = new QLineEdit;
    QLineEdit *bayerField = new QLineEdit;
    QLineEdit *flamField = new QLineEdit;
    QLineEdit *constellationField = new QLineEdit;
    QLineEdit *companionField = new QLineEdit;
    QLineEdit *companionPrimaryField = new QLineEdit;
    QLineEdit *companionBaseField = new QLineEdit;
    QLineEdit *luminosityField = new QLineEdit;
    QLineEdit *standardVariableField = new QLineEdit;
    QLineEdit *variableMinField = new QLineEdit;
    QLineEdit *variableMaxField = new QLineEdit;

    QScrollArea *scrollArea =  new QScrollArea;
    scrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    scrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    scrollArea->setWidgetResizable(true);
    QWidget *scrollWidget = new QWidget;


    // Add LineEdits to map for later access:
    addFormMap.insert("hipparcosId", hipparcosIdField);
    addFormMap.insert("henryId", henryIdField);
    addFormMap.insert("harvardId", harvardIdField);
    addFormMap.insert("glieseId", glieseIdField);
    addFormMap.insert("bayerFlamsteed", bayerFlamsteedField);
    addFormMap.insert("starName", starNameField);
    addFormMap.insert("rightAscension", rightAcensionField);
    addFormMap.insert("declination", declinationField);
    // Distance would go here
    addFormMap.insert("pmra", pmraField);
    addFormMap.insert("pmdec", pmdecField);
    addFormMap.insert("radialVelocity", radialVelocity);
    addFormMap.insert("magnitude", magnitudeField);
    addFormMap.insert("absMagnitude", absMagnitudeField);
    addFormMap.insert("spectralType", spectralTypeField);
    addFormMap.insert("colorIndex", colorIndexField);
    addFormMap.insert("xCoord", xCoordField);
    addFormMap.insert("yCoord", yCoordField);
    addFormMap.insert("zCoord", zCoordField);
    addFormMap.insert("xVelocity", xVelocityField);
    addFormMap.insert("yVelocity", yVelocityField);
    addFormMap.insert("zVelocity", zVelocityField);
    addFormMap.insert("rarad", raradField);
    addFormMap.insert("decrad", decradField);
    addFormMap.insert("pmrarad", pmraradField);
    addFormMap.insert("pmdecrad", pmdecradField);
    addFormMap.insert("bayer", bayerField);
    addFormMap.insert("flam", flamField);
    addFormMap.insert("constellation", constellationField);
    addFormMap.insert("companion", companionField);
    addFormMap.insert("companionPrimary", companionPrimaryField);
    addFormMap.insert("companionBase", companionBaseField);
    addFormMap.insert("luminosity", luminosityField);
    addFormMap.insert("standardVariable", standardVariableField);
    addFormMap.insert("variableMin", variableMinField);
    addFormMap.insert("variableMax", variableMaxField);

    QPushButton *confirmButton = new QPushButton("Confirm");
    QPushButton *cancelButton = new QPushButton("Cancel");
    QHBoxLayout *buttonLayout = new QHBoxLayout;

    // [Form]
    formLayout->addRow("Hipparcos ID", hipparcosIdField);
    formLayout->addRow("Henry Draper ID", henryIdField);
    formLayout->addRow("Harvard Revised ID", harvardIdField);
    formLayout->addRow("Gliese ID", glieseIdField);
    formLayout->addRow("Bayer Flamsteed", bayerFlamsteedField);
    formLayout->addRow("Star Name", starNameField);
    formLayout->addRow("Right Acension", rightAcensionField);
    formLayout->addRow("Declination", declinationField);
    formLayout->addRow("Proper Motion Right Acension", pmraField);
    formLayout->addRow("Proper Motion Declination", pmdecField);
    formLayout->addRow("Radial Velocity", radialVelocity);
    formLayout->addRow("Magnitude", magnitudeField);
    formLayout->addRow("Absolute Magnitude", absMagnitudeField);
    formLayout->addRow("Spectral Type", spectralTypeField);
    formLayout->addRow("Color Index", colorIndexField);
    formLayout->addRow("X-coordinate", xCoordField);
    formLayout->addRow("Y-coordinate", yCoordField);
    formLayout->addRow("Z-coordinate", zCoordField);
    formLayout->addRow("X-Velocity", xVelocityField);
    formLayout->addRow("Y-Velocity", yVelocityField);
    formLayout->addRow("Z-Velocity", zVelocityField);
    formLayout->addRow("Right Ascension Radians", raradField);
    formLayout->addRow("Declination Radians", decradField);
    formLayout->addRow("Proper Motion Right Ascention in Radians", pmraradField);
    formLayout->addRow("Proper Motion Declination in Radians", pmdecradField);
    formLayout->addRow("Bayer Designation", bayerField);
    formLayout->addRow("Flamsteed Number", flamField);
    formLayout->addRow("Constellation Abbrevation", constellationField);
    formLayout->addRow("Companion Star", companionField);
    formLayout->addRow("Companion Primary Star", companionPrimaryField);
    formLayout->addRow("Companion Base System", companionBaseField);
    formLayout->addRow("Luminosity", luminosityField);
    formLayout->addRow("Standard Variable", standardVariableField);
    formLayout->addRow("Variable Min", variableMinField);
    formLayout->addRow("Variable Max", variableMaxField);


    // [Connect]
    connect(confirmButton, SIGNAL(clicked(bool)), this,
            SLOT(on_addFormGroupBox_addSystemConfirmButton_clicked()));
    connect(cancelButton, SIGNAL(clicked(bool)), this,
            SLOT(on_addSystemFormGroupBox_cancelButton_clicked()));

    // [Layout]
    scrollWidget->setLayout(formLayout);
    scrollArea->setWidget(scrollWidget);
    //layout->addLayout(formLayout);
    layout->addWidget(scrollArea);
    buttonLayout->addWidget(confirmButton);
    buttonLayout->addWidget(cancelButton);
    layout->addLayout(buttonLayout);
    addSystemFormGroupBox->setLayout(layout);

}

void StartWindow::createAddPlanetFormGroupBox()
{
    QPushButton *confirmButton = new QPushButton("Confirm");
    QPushButton *cancelButton = new QPushButton("Cancel");
    QHBoxLayout *buttonLayout = new QHBoxLayout;


    addPlanetFormGroupBox = new QGroupBox("Add new Planet");
    QVBoxLayout *layout = new QVBoxLayout;
    QFormLayout *formLayout = new QFormLayout;

    QLineEdit *hostName = new QLineEdit;
    QLineEdit *numberOfPlanetsInSystems = new QLineEdit;
    QLineEdit *orbitalPeriod = new QLineEdit;
    QLineEdit *orbitSemiAxis = new QLineEdit;
    QLineEdit *eccentricity = new QLineEdit;
    QLineEdit *inclination= new QLineEdit;
    QLineEdit *planetMassJupiter = new QLineEdit;
    QLineEdit *planetMassProv = new QLineEdit;
    QLineEdit *planetRadius = new QLineEdit;
    QLineEdit *density = new QLineEdit;
    QLineEdit *rightAscText = new QLineEdit;
    QLineEdit *rightAsc = new QLineEdit;
    QLineEdit *decText = new QLineEdit;
    QLineEdit *dec = new QLineEdit;
    QLineEdit *dist = new QLineEdit;
    QLineEdit *optMag = new QLineEdit;
    QLineEdit *optMagBand = new QLineEdit;
    QLineEdit *effectiveTempature = new QLineEdit;
    QLineEdit *stellarMass = new QLineEdit;
    QLineEdit *stellarRad = new QLineEdit;
    QLineEdit *planetName = new QLineEdit;
    QLineEdit *plDisc = new QLineEdit;
    QLineEdit *hdNameInt = new QLineEdit;
    QLineEdit *hipparcos = new QLineEdit;


    addFormPlanetMap.insert("hostName",hostName);
    addFormPlanetMap.insert("numberOfPlanets",numberOfPlanetsInSystems);
    addFormPlanetMap.insert("orbitalPeriod",orbitalPeriod);
    addFormPlanetMap.insert("orbitSemiAxis",orbitSemiAxis);
    addFormPlanetMap.insert("eccentricity",eccentricity);
    addFormPlanetMap.insert("inclination",inclination);
    addFormPlanetMap.insert("planetMassJ",planetMassJupiter);
    addFormPlanetMap.insert("planetMassProv",planetMassProv);
    addFormPlanetMap.insert("planetRadius",planetRadius);
    addFormPlanetMap.insert("density",density);
    addFormPlanetMap.insert("rightAscText",rightAscText);
    addFormPlanetMap.insert("rightAsc",rightAsc);
    addFormPlanetMap.insert("decText",decText);
    addFormPlanetMap.insert("dec",dec);
    addFormPlanetMap.insert("dist",dist);
    addFormPlanetMap.insert("optMag",optMag);
    addFormPlanetMap.insert("optMagBand",optMagBand);
    addFormPlanetMap.insert("effectiveTempature",effectiveTempature);
    addFormPlanetMap.insert("stellarMass",stellarMass);
    addFormPlanetMap.insert("stellarRad",stellarRad);
    addFormPlanetMap.insert("planetName",planetName);
    addFormPlanetMap.insert("plDisc",plDisc);
    addFormPlanetMap.insert("hdNameInt",hdNameInt);
    addFormPlanetMap.insert("hipparcos",hipparcos);


    //formLayout->addRow("Star name",hostName);
    // formLayout->addRow("Henry Draper ID",hdNameInt);
    // formLayout->addRow("Hipparcos ID",hipparcos);
    // formLayout->addRow("Number of planets",numberOfPlanetsInSystems);
    formLayout->addRow("Orbital period",orbitalPeriod);
    formLayout->addRow("Orbital semi-major axis",orbitSemiAxis);
    formLayout->addRow("Eccentricity",eccentricity);
    formLayout->addRow("Inclination",inclination);
    formLayout->addRow("Planet mass calculated from Jupiter",planetMassJupiter);
    formLayout->addRow("Planet mass calculated from Providence",planetMassProv);
    formLayout->addRow("Planet radius",planetRadius);
    formLayout->addRow("Density",density);
    formLayout->addRow("Right ascension DD:MM:SS",rightAscText);
    formLayout->addRow("Right ascension",rightAsc);
    formLayout->addRow("Declination DD:MM:SS",decText);
    formLayout->addRow("Declination",dec);
    //formLayout->addRow("Distance",dist);
    //formLayout->addRow("Optical magnitude",optMag);
    //formLayout->addRow("Optical magnitude band",optMagBand);
    //formLayout->addRow("Effective tempature",effectiveTempature);
    //formLayout->addRow("Stellar mass [M☉]",stellarMass);
    //formLayout->addRow("Stellar radius [R☉]",stellarRad);
    formLayout->addRow("Planet name",planetName);
    formLayout->addRow("Planet discovery year",plDisc);


    connect(confirmButton, SIGNAL(clicked(bool)), this,
            SLOT(on_addFormGroupBox_addPlanetConfirmButton_clicked()));
    connect(cancelButton, SIGNAL(clicked(bool)), this,
            SLOT(on_addSystemFormGroupBox_cancelButton_clicked()));


    QScrollArea *scrollArea =  new QScrollArea;
    scrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    scrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    scrollArea->setWidgetResizable(true);
    QWidget *scrollWidget = new QWidget;

    scrollWidget->setLayout(formLayout);
    scrollArea->setWidget(scrollWidget);
    layout->addLayout(formLayout);
    layout->addWidget(scrollArea);
    buttonLayout->addWidget(confirmButton);
    buttonLayout->addWidget(cancelButton);
    layout->addLayout(buttonLayout);
    addPlanetFormGroupBox->setLayout(layout);
}

void StartWindow::createChangeFormSetupDialog(){
    changeFormSetupDialog = new QDialog;
    changeFormSetupDialog->setWindowTitle("Choose what to change");
    changeFormSetupDialog->setMinimumWidth(265);
    QGridLayout *layout = new QGridLayout;
    QPushButton *changeSystemButton = new QPushButton("Change System");
    QPushButton *changePlanetButton= new QPushButton("Change Planet");
    QPushButton *cancelButton = new QPushButton("Cancel");

    connect(changeSystemButton, SIGNAL(clicked(bool)), this,
            SLOT(on_changeFormSetupDialog_changeSystem_clicked()));
    connect(cancelButton, SIGNAL(clicked(bool)), this,
            SLOT(on_changeFormSetupDialog_cancelButton_clicked()));
    connect(changePlanetButton, SIGNAL(clicked(bool)), this,
            SLOT(on_changeFormSetupDialog_changePlanet_clicked()));

    layout->addWidget(changeSystemButton, 0,0,1,2);
    layout->addWidget(changePlanetButton, 1,0,1,1);
    layout->addWidget(cancelButton, 1,1,1,1);
    changeFormSetupDialog->setLayout(layout);
}

void StartWindow::createChangeSystemFormGroupBox()
{
    changeSystemFormGroupBox = new QGroupBox("Add new system");
    QVBoxLayout *layout = new QVBoxLayout;
    QFormLayout *formLayout = new QFormLayout;
    QLineEdit *hipparcosIdField = new QLineEdit;
    hipparcosIdField->setText((model->record(0).value("hip").isNull())? "" :model->record(0).value("hip").toString());
    QLineEdit *henryIdField = new QLineEdit;
    henryIdField->setText((model->record(0).value("hd").isNull())? "" :model->record(0).value("hd").toString());
    QLineEdit *harvardIdField = new QLineEdit;
    harvardIdField->setText((model->record(0).value("hr").isNull())? "" :model->record(0).value("hr").toString());
    QLineEdit *glieseIdField = new QLineEdit;
    glieseIdField->setText((model->record(0).value("gl").isNull())? "" :model->record(0).value("gl").toString());
    QLineEdit *bayerFlamsteedField = new QLineEdit;
    bayerFlamsteedField->setText((model->record(0).value("bf").isNull())? "" :model->record(0).value("bf").toString());
    QLineEdit *rightAcensionField = new QLineEdit;
    rightAcensionField->setText((model->record(0).value("ra").isNull())? "" :model->record(0).value("ra").toString());
    QLineEdit *declinationField = new QLineEdit;
    declinationField->setText((model->record(0).value("dec").isNull())? "" :model->record(0).value("dec").toString());
    QLineEdit *starNameField = new QLineEdit; //proper
    starNameField->setText((model->record(0).value("proper").isNull())? "" :model->record(0).value("proper").toString());
    //QLineEdit *distanceField = new QLineEdit;
    QLineEdit *pmraField = new QLineEdit;
    pmraField->setText((model->record(0).value("pmra").isNull())? "" :model->record(0).value("pmra").toString());
    QLineEdit *pmdecField = new QLineEdit;
    pmdecField->setText((model->record(0).value("pmdec").isNull())? "" :model->record(0).value("pmdec").toString());
    QLineEdit *radialVelocity = new QLineEdit;
    radialVelocity->setText((model->record(0).value("rv").isNull())? "" :model->record(0).value("rv").toString());
    QLineEdit *magnitudeField = new QLineEdit;
    magnitudeField->setText((model->record(0).value("mag").isNull())? "" :model->record(0).value("mag").toString());
    QLineEdit *absMagnitudeField = new QLineEdit;
    absMagnitudeField->setText((model->record(0).value("absmag").isNull())? "" :model->record(0).value("absmag").toString());
    QLineEdit *spectralTypeField = new QLineEdit;
    spectralTypeField->setText((model->record(0).value("spect").isNull())? "" :model->record(0).value("spect").toString());
    QLineEdit *colorIndexField = new QLineEdit;
    colorIndexField->setText((model->record(0).value("ci").isNull())? "" :model->record(0).value("ci").toString());
    QLineEdit *xCoordField = new QLineEdit;
    xCoordField->setText(model->record(0).value("x").toString());
    QLineEdit *yCoordField = new QLineEdit;
    yCoordField->setText(model->record(0).value("y").toString());
    QLineEdit *zCoordField = new QLineEdit;
    zCoordField->setText(model->record(0).value("z").toString());
    QLineEdit *xVelocityField = new QLineEdit;
    xVelocityField->setText((model->record(0).value("vx").isNull())? "" :model->record(0).value("vx").toString());
    QLineEdit *yVelocityField = new QLineEdit;
    yVelocityField->setText((model->record(0).value("vy").isNull())? "" :model->record(0).value("vy").toString());
    QLineEdit *zVelocityField = new QLineEdit;
    zVelocityField->setText((model->record(0).value("vz").isNull())? "" :model->record(0).value("vz").toString());
    QLineEdit *raradField = new QLineEdit;
    raradField->setText((model->record(0).value("rarad").isNull())? "" :model->record(0).value("rarad").toString());
    QLineEdit *decradField = new QLineEdit;
    decradField->setText((model->record(0).value("decrad").isNull())? "" :model->record(0).value("decrad").toString());
    QLineEdit *pmraradField = new QLineEdit;
    pmraradField->setText((model->record(0).value("pmrarad").isNull())? "" :model->record(0).value("pmrarad").toString());
    QLineEdit *pmdecradField = new QLineEdit;
    pmdecradField->setText((model->record(0).value("pmdecrad").isNull())? "" :model->record(0).value("pmdecrad").toString());
    QLineEdit *bayerField = new QLineEdit;
    bayerField->setText((model->record(0).value("bayer").isNull())? "" :model->record(0).value("bayer").toString());
    QLineEdit *flamField = new QLineEdit;
    flamField->setText((model->record(0).value("flam").isNull())? "" :model->record(0).value("flam").toString());
    QLineEdit *constellationField = new QLineEdit;
    constellationField->setText((model->record(0).value("con").isNull())? "" :model->record(0).value("con").toString());
    QLineEdit *companionField = new QLineEdit;
    companionField->setText((model->record(0).value("comp").isNull())? "" :model->record(0).value("comp").toString());
    QLineEdit *companionPrimaryField = new QLineEdit;
    companionPrimaryField->setText((model->record(0).value("comp_primary").isNull())? "" :model->record(0).value("comp_primary").toString());
    QLineEdit *companionBaseField = new QLineEdit;
    companionBaseField->setText((model->record(0).value("base").isNull())? "" :model->record(0).value("base").toString());
    QLineEdit *luminosityField = new QLineEdit;
    luminosityField->setText((model->record(0).value("lum").isNull())? "" :model->record(0).value("lum").toString());
    QLineEdit *standardVariableField = new QLineEdit;
    standardVariableField->setText((model->record(0).value("var").isNull())? "" :model->record(0).value("var").toString());
    QLineEdit *variableMinField = new QLineEdit;
    variableMinField->setText((model->record(0).value("var_min").isNull())? "" :model->record(0).value("var_min").toString());
    QLineEdit *variableMaxField = new QLineEdit;
    variableMaxField->setText((model->record(0).value("var_max").isNull())? "" :model->record(0).value("var_max").toString());

    QScrollArea *scrollArea =  new QScrollArea;
    scrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    scrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    scrollArea->setWidgetResizable(true);
    QWidget *scrollWidget = new QWidget;


    // Add LineEdits to map for later access:
    addFormMap.insert("hipparcosId", hipparcosIdField);
    addFormMap.insert("henryId", henryIdField);
    addFormMap.insert("harvardId", harvardIdField);
    addFormMap.insert("glieseId", glieseIdField);
    addFormMap.insert("bayerFlamsteed", bayerFlamsteedField);
    addFormMap.insert("starName", starNameField);
    addFormMap.insert("rightAscension", rightAcensionField);
    addFormMap.insert("declination", declinationField);
    // Distance would go here
    addFormMap.insert("pmra", pmraField);
    addFormMap.insert("pmdec", pmdecField);
    addFormMap.insert("radialVelocity", radialVelocity);
    addFormMap.insert("magnitude", magnitudeField);
    addFormMap.insert("absMagnitude", absMagnitudeField);
    addFormMap.insert("spectralType", spectralTypeField);
    addFormMap.insert("colorIndex", colorIndexField);
    addFormMap.insert("xCoord", xCoordField);
    addFormMap.insert("yCoord", yCoordField);
    addFormMap.insert("zCoord", zCoordField);
    addFormMap.insert("xVelocity", xVelocityField);
    addFormMap.insert("yVelocity", yVelocityField);
    addFormMap.insert("zVelocity", zVelocityField);
    addFormMap.insert("rarad", raradField);
    addFormMap.insert("decrad", decradField);
    addFormMap.insert("pmrarad", pmraradField);
    addFormMap.insert("pmdecrad", pmdecradField);
    addFormMap.insert("bayer", bayerField);
    addFormMap.insert("flam", flamField);
    addFormMap.insert("constellation", constellationField);
    addFormMap.insert("companion", companionField);
    addFormMap.insert("companionPrimary", companionPrimaryField);
    addFormMap.insert("companionBase", companionBaseField);
    addFormMap.insert("luminosity", luminosityField);
    addFormMap.insert("standardVariable", standardVariableField);
    addFormMap.insert("variableMin", variableMinField);
    addFormMap.insert("variableMax", variableMaxField);

    QPushButton *confirmButton = new QPushButton("Confirm");
    QPushButton *cancelButton = new QPushButton("Cancel");
    QHBoxLayout *buttonLayout = new QHBoxLayout;

    // [Form]
    formLayout->addRow("Hipparcos ID", hipparcosIdField);
    formLayout->addRow("Henry Draper ID", henryIdField);
    formLayout->addRow("Harvard Revised ID", harvardIdField);
    formLayout->addRow("Gliese ID", glieseIdField);
    formLayout->addRow("Bayer Flamsteed", bayerFlamsteedField);
    formLayout->addRow("Star Name", starNameField);
    formLayout->addRow("Right Acension", rightAcensionField);
    formLayout->addRow("Declination", declinationField);
    formLayout->addRow("Proper Motion Right Acension", pmraField);
    formLayout->addRow("Proper Motion Declination", pmdecField);
    formLayout->addRow("Radial Velocity", radialVelocity);
    formLayout->addRow("Magnitude", magnitudeField);
    formLayout->addRow("Absolute Magnitude", absMagnitudeField);
    formLayout->addRow("Spectral Type", spectralTypeField);
    formLayout->addRow("Color Index", colorIndexField);
    formLayout->addRow("X-coordinate", xCoordField);
    formLayout->addRow("Y-coordinate", yCoordField);
    formLayout->addRow("Z-coordinate", zCoordField);
    formLayout->addRow("X-Velocity", xVelocityField);
    formLayout->addRow("Y-Velocity", yVelocityField);
    formLayout->addRow("Z-Velocity", zVelocityField);
    formLayout->addRow("Right Ascension Radians", raradField);
    formLayout->addRow("Declination Radians", decradField);
    formLayout->addRow("Proper Motion Right Ascention in Radians", pmraradField);
    formLayout->addRow("Proper Motion Declination in Radians", pmdecradField);
    formLayout->addRow("Bayer Designation", bayerField);
    formLayout->addRow("Flamsteed Number", flamField);
    formLayout->addRow("Constellation Abbrevation", constellationField);
    formLayout->addRow("Companion Star", companionField);
    formLayout->addRow("Companion Primary Star", companionPrimaryField);
    formLayout->addRow("Companion Base System", companionBaseField);
    formLayout->addRow("Luminosity", luminosityField);
    formLayout->addRow("Standard Variable", standardVariableField);
    formLayout->addRow("Variable Min", variableMinField);
    formLayout->addRow("Variable Max", variableMaxField);


    // [Connect]
//    connect(confirmButton, SIGNAL(clicked(bool)), this,
//            SLOT(()));
//    connect(cancelButton, SIGNAL(clicked(bool)), this,
//            SLOT(()));

    // [Layout]
    scrollWidget->setLayout(formLayout);
    scrollArea->setWidget(scrollWidget);
    //layout->addLayout(formLayout);
    layout->addWidget(scrollArea);
    buttonLayout->addWidget(confirmButton);
    buttonLayout->addWidget(cancelButton);
    layout->addLayout(buttonLayout);
    changeSystemFormGroupBox->setLayout(layout);

}

void StartWindow::createChangeSearchSystemGroupBox(){

    changeSearchSystemGroupBox = new QGroupBox("Search for Star");
    QVBoxLayout *layout = new QVBoxLayout;

    model = new QSqlTableModel;
    QTableView *view = new QTableView();

    QHBoxLayout *searchLayout = new QHBoxLayout;
    searchField = new QLineEdit();
    QPushButton *searchButton = new QPushButton("Search");
    searchLayout->addWidget(searchField);
    searchLayout->addWidget(searchButton);

    QPushButton *confirmButton = new QPushButton("Change current star");
    QPushButton *cancelButton = new QPushButton("Cancel");
    QHBoxLayout *buttonLayout = new QHBoxLayout;
    //CONNECT
    connect(searchButton, SIGNAL(clicked(bool)), this,
            SLOT(on_systemSearch_searchButton_clicked()));
    connect(cancelButton, SIGNAL(clicked(bool)), this,
            SLOT(on_addSystemFormGroupBox_cancelButton_clicked()));
    connect(confirmButton, SIGNAL(clicked(bool)), this,
            SLOT(on_changeFormGroupBox_changeSysstemButton_clicked()));
    buttonLayout->addWidget(confirmButton);
    buttonLayout->addWidget(searchButton);
    buttonLayout->addWidget(cancelButton);
    layout->addLayout(searchLayout);
    layout->addLayout(buttonLayout);
    view->setModel(model);
    layout->addWidget(view);
    changeSearchSystemGroupBox->setLayout(layout);
}

void StartWindow::createChangeSearchPlanetGroupBox(){

    changeSearchPlanetGroupBox = new QGroupBox("Search for Star");
    QVBoxLayout *layout = new QVBoxLayout;

    model = new QSqlTableModel;
    QTableView *view = new QTableView();

    QHBoxLayout *searchLayout = new QHBoxLayout;
    searchField = new QLineEdit();
    QPushButton *searchButton = new QPushButton("Search");
    searchLayout->addWidget(searchField);
    searchLayout->addWidget(searchButton);

    QPushButton *confirmButton = new QPushButton("Confirm");
    QPushButton *cancelButton = new QPushButton("Cancel");
    QHBoxLayout *buttonLayout = new QHBoxLayout;
    //CONNECT
    connect(searchButton, SIGNAL(clicked(bool)), this,
            SLOT(on_systemSearch_searchButton_clicked()));
    connect(cancelButton, SIGNAL(clicked(bool)), this,
            SLOT(on_addSystemFormGroupBox_cancelButton_clicked()));
    connect(confirmButton, SIGNAL(clicked(bool)), this,
            SLOT(on_addSystemFormGroupBox_addPlanetButton_clicked()));
    buttonLayout->addWidget(confirmButton);
    buttonLayout->addWidget(searchButton);
    buttonLayout->addWidget(cancelButton);
    layout->addLayout(searchLayout);
    layout->addLayout(buttonLayout);
    view->setModel(model);
    layout->addWidget(view);
    changeSearchPlanetGroupBox->setLayout(layout);
}


void StartWindow::createAddSystemSearchFormGroupBox(){

    addSystemSearchFormGroupBox = new QGroupBox("Search for Star");
    QVBoxLayout *layout = new QVBoxLayout;

    model = new QSqlTableModel;
    QTableView *view = new QTableView();

    QHBoxLayout *searchLayout = new QHBoxLayout;
    searchField = new QLineEdit();
    QPushButton *searchButton = new QPushButton("Search");
    searchLayout->addWidget(searchField);
    searchLayout->addWidget(searchButton);

    QPushButton *confirmButton = new QPushButton("Confirm");
    QPushButton *cancelButton = new QPushButton("Cancel");
    QHBoxLayout *buttonLayout = new QHBoxLayout;
    //CONNECT
    connect(searchButton, SIGNAL(clicked(bool)), this,
            SLOT(on_systemSearch_searchButton_clicked()));
    connect(cancelButton, SIGNAL(clicked(bool)), this,
            SLOT(on_addSystemFormGroupBox_cancelButton_clicked()));
    connect(confirmButton, SIGNAL(clicked(bool)), this,
            SLOT(on_addFormGroupBox_addPlanetButton_clicked()));
    buttonLayout->addWidget(confirmButton);
    buttonLayout->addWidget(searchButton);
    buttonLayout->addWidget(cancelButton);
    layout->addLayout(searchLayout);
    layout->addLayout(buttonLayout);
    view->setModel(model);
    layout->addWidget(view);
    addSystemSearchFormGroupBox->setLayout(layout);
}

// [Slots]

// ----[startGroupBox]
void StartWindow::on_searchButton_clicked()
{
    stackedWidgets->setCurrentWidget(searchGroupBox_startwindow);
}

void StartWindow::on_exploreButton_clicked()
{
    stackedWidgets->setCurrentWidget(galaxyGroupBox);
}

void StartWindow::on_adminButton_clicked()
{
    stackedWidgets->currentWidget()->hide();
    loginDialog->show();
}

// -----[searchGroupBox]
void StartWindow::on_search_backButton_clicked() //search menu back button
{
    stackedWidgets->setCurrentWidget(startGroupBox);
}

void StartWindow::on_searchGroupBox_searchRow_clicked() //search menu row in table clicked
{
//    qDebug() << "going from star to systemview with id " << search->getRowId();
    createSystemGroupBox(search->getRowId());
    stackedWidgets->addWidget(systemGroupBox);
    stackedWidgets->setCurrentWidget(systemGroupBox);
}

// ----[galaxyGroupBox]
void StartWindow::on_galaxyGroupBox_backButton_clicked()
{
    stackedWidgets->setCurrentWidget(startGroupBox);
}

void StartWindow::on_galaxyGroupBox_systemButton_clicked()
{
    createSystemGroupBox(galaxyRenderArea->getClosestId());
    stackedWidgets->addWidget(systemGroupBox);
    currentStar->findStarById(galaxyRenderArea->getClosestId());
    //currentStar->findStarById(50742);     //Has planets
    currentStar->findPlanets();
    starRender->setPlanetIds(currentStar->getCurrentPlanetIds());
    starRender->setStarType(currentStar->getVar("spect"));
    starRender->update();
    stackedWidgets->setCurrentWidget(systemGroupBox);
}

void StartWindow::on_galaxyGroupBox_idUpdated()
{
    QSqlQuery q;
    q.prepare("select proper,bf,x,y,z,dist,spect,ci,lum from star where id = :id");
    q.bindValue(":id", galaxyRenderArea->getClosestId());
    QString displayString;
    if(q.exec())
    {
        q.next();
        displayString.append("Name: ");
        if(q.value(0).toString() == ""){
            displayString.append("No Record");
        } else {
            displayString.append(q.value(0).toString());
        }
        displayString.append("\nBayer / Flamsteed designation: ");
        if(q.value(1).toString() == ""){
            displayString.append("No Record");
        } else {
            displayString.append(q.value(1).toString());
        }
        displayString.append("\nCartesian Coordinate(X): ");
        if(q.value(2).toString() == ""){
            displayString.append("No Record");
        } else {
            displayString.append(q.value(2).toString());
        }
        displayString.append("\nCartesian Coordinate(Y): ");
        if(q.value(3).toString() == ""){
            displayString.append("No Record");
        } else {
            displayString.append(q.value(3).toString());
        }
        displayString.append("\nCartesian Coordinate(Z): ");
        if(q.value(4).toString() == ""){
            displayString.append("No Record");
        } else {
            displayString.append(q.value(4).toString());
        }
        displayString.append("\nDistance to Sol: ");
        if(q.value(5).toString() == ""){
            displayString.append("No Record");
        } else {
            displayString.append(q.value(5).toString());
        }
        displayString.append("\nSpectral Type: ");
        if(q.value(6).toString() == ""){
            displayString.append("No Record");
        } else {
            displayString.append(q.value(6).toString());
        }
        displayString.append("\nColor Index: ");
        if(q.value(7).toString() == ""){
            displayString.append("No Record");
        } else {
            displayString.append(q.value(7).toString());
        }
        displayString.append("\nLuminosity: ");
        if(q.value(8).toString() == ""){
            displayString.append("No Record");
        } else {
            displayString.append(q.value(8).toString());
        }
    }
    galaxyInformationLabel->setText(displayString);
}

// ----[systemGroupBox]
void StartWindow::on_systemGroupBox_backButton_clicked()
{
    stackedWidgets->setCurrentWidget(galaxyGroupBox);
}
void StartWindow::on_systemGroupBox_homeButton_clicked()
{
    stackedWidgets->setCurrentWidget(startGroupBox);
}

void StartWindow::on_systemGroupBox_skyViewButton_clicked(){
    createSkyViewGroupBox(currentStar->getVar("x").toDouble(),
                          currentStar->getVar("y").toDouble(),
                          currentStar->getVar("z").toDouble());
    stackedWidgets->addWidget(skyViewGroupBox);
    stackedWidgets->setCurrentWidget(skyViewGroupBox);
    skyRenderArea->resetSlot();
}
void StartWindow::on_body_clicked(){
    informationLabel->clear();
    qDebug() << "current plane id: " << starRender->getPlanetId();
    if(starRender->getPlanetId() == -1)
        informationLabel->setText("Name: " + currentStar->getVar("proper") + "\n"
                              +"Standard Variable Star Designation: "+ currentStar->getVar("var") + "\n"
                              +"Bayer / Flamsteed designation: "+ currentStar->getVar("bf") + "\n"
                              +"Right Ascension: "+ currentStar->getVar("ra") + "\n"
                              +"Declination: "+ currentStar->getVar("dec") + "\n"
                              +"Spectral Type: "+ currentStar->getVar("spect") + "\n"
                              +"Color Index: "+ currentStar->getVar("ci") + "\n"
                              +"Luminosity: "+ currentStar->getVar("lum") + "\n"
                              +"Visual Magnitude: "+ currentStar->getVar("mag") + "\n"
                              +"Absolute Visual Magnitude: "+ currentStar->getVar("absmag") + "\n"
                              +"Distance(parsecs): "+ currentStar->getVar("dist") + "\n"
                              +"Proper Motion in Right Ascension: "+ currentStar->getVar("pmra") + "\n"
                              +"Proper Motion in Declinatio: "+ currentStar->getVar("pmdec") + "\n"
                              +"Radial Velocity: "+ currentStar->getVar("rv") + "\n"
                              +"Cartesian Coordinate(X): "+ currentStar->getVar("x") + "\n"
                              +"Cartesian Coordinate(Y): "+ currentStar->getVar("y") + "\n"
                              +"Cartesian Coordinate(Z): "+ currentStar->getVar("z") + "\n"
                              +"Cartesian velocity components(VX): "+ currentStar->getVar("vx") + "\n"
                              +"Cartesian velocity components(VY): "+ currentStar->getVar("vy") + "\n"
                              +"Cartesian velocity components(VZ): "+ currentStar->getVar("vz") + "\n"
                              +"Standard Constellation Abbreviation: "+ currentStar->getVar("con") + "\n"
                              +"Hipparcos catalog: "+ currentStar->getVar("hip") + "\n"
                              +"Henry Draper catalog: "+ currentStar->getVar("hd") + "\n"
                              +"Harvard Revised catalog: "+ currentStar->getVar("hr") + "\n"
                              +"Gliese Catalog of Nearby Stars: "+ currentStar->getVar("gl") + "\n"
                              +"Maximum Approximate Magnitude Range: "+ currentStar->getVar("var_max") + "\n"
                              +"Minimum Approximate Magnitude Range: "+ currentStar->getVar("var_min") + "\n"
                              +"ID of companion star: "+ currentStar->getVar("comp") + "\n"
                              +"ID of primary star for this component: "+ currentStar->getVar("comp_primary") + "\n"
                              +"Catalog ID or Name for this multi-star system: "+ currentStar->getVar("base") + "\n"
                              +"");
    else if(starRender->getPlanetId() == -2)
        informationLabel->clear();
    else{
       informationLabel->setText(currentStar->getPlanetLabelString(starRender->getPlanetId()));


    }
}
// ----[skyViewGroupBox]
void StartWindow::on_skyViewGroupBox_backButton_clicked()
{
    stackedWidgets->setCurrentWidget(systemGroupBox);

}

void StartWindow::on_skyViewGroupBox_homeButton_clicked()
{

    stackedWidgets->setCurrentWidget(startGroupBox);
}
void StartWindow::initSkyInfo(){
    skyInfoLabel->setText(QString("Name: \n")
                              + "Standard Variable Star Designation: " + "\n"
                              +"Bayer / Flamsteed designation: " + "\n"
                              +"Right Ascension: " + "\n"
                              +"Declination: " + "\n"
                              +"Spectral Type: " + "\n"
                              +"Color Index: " + "\n"
                              +"Luminosity: " + "\n"
                              +"Visual Magnitude: " + "\n"
                              +"Absolute Visual Magnitude: " + "\n"
                              +"Distance(parsecs): " + "\n"
                              +"");
}
void StartWindow::on_skyViewGroupBox_idUpdated()
{
    QSqlQuery q;
    q.prepare("select proper,bf,x,y,z,dist,spect,ci,lum from star where id = :id");
    q.bindValue(":id", skyRenderArea->getClosestId());
    QString displayString;
    if(q.exec())
    {
        q.next();
        displayString.append("Name: ");
        if(q.value(0).toString() == ""){
            displayString.append("No Record");
        } else {
            displayString.append(q.value(0).toString());
        }
        displayString.append("\nBayer / Flamsteed designation: ");
        if(q.value(1).toString() == ""){
            displayString.append("No Record");
        } else {
            displayString.append(q.value(1).toString());
        }
        displayString.append("\nCartesian Coordinate(X): ");
        if(q.value(2).toString() == ""){
            displayString.append("No Record");
        } else {
            displayString.append(q.value(2).toString());
        }
        displayString.append("\nCartesian Coordinate(Y): ");
        if(q.value(3).toString() == ""){
            displayString.append("No Record");
        } else {
            displayString.append(q.value(3).toString());
        }
        displayString.append("\nCartesian Coordinate(Z): ");
        if(q.value(4).toString() == ""){
            displayString.append("No Record");
        } else {
            displayString.append(q.value(4).toString());
        }
        displayString.append("\nDistance to Sol: ");
        if(q.value(5).toString() == ""){
            displayString.append("No Record");
        } else {
            displayString.append(q.value(5).toString());
        }
        displayString.append("\nSpectral Type: ");
        if(q.value(6).toString() == ""){
            displayString.append("No Record");
        } else {
            displayString.append(q.value(6).toString());
        }
        displayString.append("\nColor Index: ");
        if(q.value(7).toString() == ""){
            displayString.append("No Record");
        } else {
            displayString.append(q.value(7).toString());
        }
        displayString.append("\nLuminosity: ");
        if(q.value(8).toString() == ""){
            displayString.append("No Record");
        } else {
            displayString.append(q.value(8).toString());
        }
    }
    skyInfoLabel->setText(displayString);
}
// ----[loginDialog]
void StartWindow::on_loginDialog_cancelButton_clicked()
{
    loginDialog->close();
    stackedWidgets->setCurrentWidget(startGroupBox);
    stackedWidgets->currentWidget()->show();

}

void StartWindow::on_loginDialog_loginButton_clicked()
{
    loginDialog->close();
    stackedWidgets->setCurrentWidget(adminGroupBox);
}

// ----[adminGroupBox]
void StartWindow::on_adminGroupBox_addButton_clicked()
{
    addFormSetupDialog->show();
    //stackedWidgets->setCurrentWidget(addSystemFormGroupBox);
}

void StartWindow::on_adminGroupBox_changeButton_clicked()
{
    changeFormSetupDialog->show();
}
void StartWindow::on_changeFormSetupDialog_changePlanet_clicked()
{
    createChangeSearchPlanetGroupBox();
    stackedWidgets->addWidget(changeSearchPlanetGroupBox);
    stackedWidgets->setCurrentWidget(changeSearchPlanetGroupBox);
    changeFormSetupDialog->close();
}
void StartWindow::on_changeFormSetupDialog_changeSystem_clicked(){
    createChangeSearchSystemGroupBox();
    stackedWidgets->addWidget(changeSearchSystemGroupBox);
    stackedWidgets->setCurrentWidget(changeSearchSystemGroupBox);
    changeFormSetupDialog->close();
}


void StartWindow::on_changeFormSetupDialog_cancelButton_clicked()
{
    changeFormSetupDialog->close();
}


void StartWindow::on_adminGroupBox_logoutButton_clicked()
{
    stackedWidgets->setCurrentWidget(startGroupBox);
}

// ----[addFormSetupDialog]
void StartWindow::on_addFormSetupDialog_addSystemButton_clicked()
{
    createAddSystemFormGroupBox();
    stackedWidgets->addWidget(addSystemFormGroupBox);
    stackedWidgets->setCurrentWidget(addSystemFormGroupBox);
    addFormSetupDialog->close();
}
void StartWindow::on_addFormSetupDialog_addSearchSystemButton_clicked(){
    createAddSystemSearchFormGroupBox();
    systemSearchConfirm = false;
    stackedWidgets->addWidget(addSystemSearchFormGroupBox);
    stackedWidgets->setCurrentWidget(addSystemSearchFormGroupBox);
    addFormSetupDialog->close();
}

void StartWindow::on_changeFormGroupBox_changeSysstemButton_clicked(){
    if(systemSearchConfirm){
        createChangeSystemFormGroupBox();
        stackedWidgets->addWidget(changeSystemFormGroupBox);
        stackedWidgets->setCurrentWidget(changeSystemFormGroupBox);
    }
}

void StartWindow::on_addFormGroupBox_addPlanetButton_clicked(){
    if(systemSearchConfirm){
        QLineEdit *a1 = new QLineEdit();
        QLineEdit *a2 = new QLineEdit();
        QLineEdit *a3 = new QLineEdit();
        QLineEdit *a4 = new QLineEdit();

        a1->setText(model->record().value("hip").toString());
        a2->setText(model->record().value("proper").toString());
        a3->setText(model->record().value("mag").toString());
        a4->setText(model->record().value("hd").toString());
        addFormPlanetMap.insert("hipparcos",a1);
        addFormPlanetMap.insert("hostName",a2);
        addFormPlanetMap.insert("optMag",a3);
        addFormPlanetMap.insert("hdNameInt",a4);

        createAddPlanetFormGroupBox();
        stackedWidgets->addWidget(addPlanetFormGroupBox);
        stackedWidgets->setCurrentWidget(addPlanetFormGroupBox);
        addFormSetupDialog->close();
    }
}


void StartWindow::on_addFormSetupDialog_cancelButton_clicked()
{
    addFormSetupDialog->close();
}

// ----[addSystemFormGroupBox]
void StartWindow::on_addFormGroupBox_addSystemConfirmButton_clicked()
{

    int check = 0;
    check += checkDataTypeStar("xCoord", "double");
    check +=checkDataTypeStar("yCoord", "double");
    check +=checkDataTypeStar("zCoord", "double");
    check +=checkDataTypeStar("hipparcosId", "int");
    check +=checkDataTypeStar("henryId", "int");
    check +=checkDataTypeStar("harvardId", "int");
    check +=checkDataTypeStar("glieseId", "int");
    check +=checkDataTypeStar("rightAscension", "double");
    check +=checkDataTypeStar("declination", "double");
    // checkDataTypeStar("dist", "double");
    check += checkDataTypeStar("pmra", "double");
    check += checkDataTypeStar("pmdec", "double");
    check += checkDataTypeStar("radialVelocity", "double");
    check += checkDataTypeStar("magnitude", "double");
    check += checkDataTypeStar("absMagnitude", "double");
    check += checkDataTypeStar("colorIndex", "double");
    check += checkDataTypeStar("xVelocity", "double");
    check += checkDataTypeStar("yVelocity", "double");
    check += checkDataTypeStar("zVelocity", "double");
    check += checkDataTypeStar("rarad", "double");
    check += checkDataTypeStar("decrad", "double");
    check += checkDataTypeStar("pmrarad", "double");
    check += checkDataTypeStar("pmdecrad", "double");
    check += checkDataTypeStar("companion", "int");
    check += checkDataTypeStar("companionPrimary", "int");
    check += checkDataTypeStar("luminosity", "double");
    check += checkDataTypeStar("variableMin", "int");
    check += checkDataTypeStar("variableMax", "int");
    if(check==0){
        if(addFormMap.value("xCoord")->text() != "" &&
                addFormMap.value("yCoord")->text() != "" &&
                addFormMap.value("zCoord")->text() != "" &&
                addFormMap.value("hipparcosId")->text() != ""){
            qDebug() << tr("Star Name: %1").arg(addFormMap.value("starName")->text());
            dbMain.insertStar("star", &addFormMap);
            stackedWidgets->setCurrentWidget(adminGroupBox);
            stackedWidgets->removeWidget(addSystemFormGroupBox);
        }else{
            if(addFormMap.value("hipparcosId")->text() == ""){
                addFormMap.value("hipparcosId")->setText("This can not be left empty");
            }
            if(addFormMap.value("xCoord")->text() == ""){
                addFormMap.value("xCoord")->setText("This can not be left empty");
            }
            if(addFormMap.value("yCoord")->text() == ""){
                addFormMap.value("yCoord")->setText("This can not be left empty");
            }
            if(addFormMap.value("zCoord")->text() == ""){
                addFormMap.value("zCoord")->setText("This can not be left empty");
            }
        }
    }
}

void StartWindow::on_addSystemFormGroupBox_cancelButton_clicked()
{
    stackedWidgets->setCurrentWidget(adminGroupBox);
    stackedWidgets->removeWidget(addSystemFormGroupBox);
}

void StartWindow::on_systemSearch_searchButton_clicked(){
    searchSystem(searchField->text());
}
void StartWindow::on_addFormGroupBox_addPlanetConfirmButton_clicked(){
    int check = 0;

    check+=checkDataTypePlanet("orbitalPeriod", "double");
    check+=checkDataTypePlanet("orbitSemiAxis", "double");
    check+=checkDataTypePlanet("eccentricity", "double");
    check+=checkDataTypePlanet("inclination", "double");
    check+=checkDataTypePlanet("planetMassJ", "double");
    check+=checkDataTypePlanet("planetRadius", "double");
    check+=checkDataTypePlanet("density", "double");
    check+=checkDataTypePlanet("rightAsc", "double");
    check+=checkDataTypePlanet("dec", "double");
    check+=checkDataTypePlanet("dist", "double");
    check+=checkDataTypePlanet("optMag", "double");
    check+=checkDataTypePlanet("plDisc", "int");

    if(addFormPlanetMap.value("planetName")->text().isEmpty()){
        addFormPlanetMap.value("planetName")->setText("This field needs to be filled in");
    }else{
        if(check == 0){
            dbMain.insertPlanet("planets", &addFormPlanetMap);
            stackedWidgets->setCurrentWidget(adminGroupBox);
            stackedWidgets->removeWidget(addSystemFormGroupBox);
        }
    }
}


void StartWindow::searchSystem(QString s){
    qDebug() << "You searched for: " << s;
    bool check = false;
    searchField->text().toInt(&check);
    if(!s.isEmpty()){
        QString filter = "hip = ";
        filter.append(s);
        qDebug() << filter;
        model->setTable("star");
        model->setFilter(filter);
        model->select();
    }
    if(check){
        systemSearchConfirm = true;
    }
    else{
        systemSearchConfirm = false;
    }


}

int StartWindow::checkDataTypeStar(QString name, QString type)
{
    bool check = false;
    if(!addFormMap.value(name)->text().isEmpty()){
        if(type.toLower() == "int"){
            addFormMap.value(name)->text().toInt(&check);
        }
        else if(type.toLower() == "double"){
            addFormMap.value(name)->text().toDouble(&check);
        }

        if(!check){
            addFormMap.value(name)->setText("This field is invalid datatype");
            return 1;
        }
    }
    return 0;
}

int StartWindow::checkDataTypePlanet(QString name, QString type)
{
    bool check = false;
    if(!addFormPlanetMap.value(name)->text().isEmpty()){
        if(type.toLower() == "int"){
            addFormPlanetMap.value(name)->text().toInt(&check);
        }
        else if(type.toLower() == "double"){
            addFormPlanetMap.value(name)->text().toDouble(&check);
        }

        if(!check){
            addFormPlanetMap.value(name)->setText("This field is invalid datatype");
            return 1;
        }
    }
    return 0;
}
