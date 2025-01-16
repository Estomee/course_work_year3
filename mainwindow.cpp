#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "auth_inheritance.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowTitle("Автосалон");
    QFile styles(":/styles/s");
    styles.open(QFile::ReadOnly);
    this->setWindowIcon(QIcon(":/images/ee"));
    this->setStyleSheet(QLatin1String(styles.readAll()));
    QPalette palette = this->palette();
    palette.setColor(QPalette::Window, QColor(255, 255, 255));
    this->setAutoFillBackground(true);
    this->setPalette(palette);
    setMinimumSize(800, 600);

    // Инициализируем конфигурацию
    auto& config = SecureConfig::getInstance();
    config.setEmailServiceId("service_kbj59fx");
    config.setEmailTemplateId("template_fljld19");
    config.setEmailUserId("YEWiXHmsqZFgQaD7q");
    config.setCompanyName("Автосалон E");

    // Создаем и настраиваем главный виджет
    centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);
    // Создаем QStackedLayout
    stackedLayout = new QStackedLayout(centralWidget);

    this->AuthPageDraw();      // Страница аутентификации (индекс 0)
    this->EmployeePageDraw();  // Страница сотрудника (индекс 1)
    this->RegistrationPageDraw(); // Страница регистрации (индекс 2)
    this->ForgotPassPageDraw(); //Страница восстановления пароля (индекс 3)
    this->EmployeeWorkPageDraw(); //Страница работы сотрудника (индекс 4)
    this->UserPageDraw(); //Страница пользователя (индекс 5)
    this->BacketPageDraw(); //Страница корзины (индекс 6)
    this->AdminPageDraw(); //Страница администратора (индекс 7)

    stackedLayout->setCurrentIndex(0); //Вернуть на 0

    myConPool = new ConcreteDbCConnection();


    // Инициализируем пул соединений
    QTimer::singleShot(0, this, [this]()
    {
        myConPool->initializePool();
    });

    //TODO: не забыть добавить код аутентификации для сотрудника (возможно добавить почту в таблицу)

}

void MainWindow::AuthPageDraw()
{

    QWidget* authPage = new QWidget(this);
    authPage->setFocusPolicy(Qt::StrongFocus);
    loginLineEdit = new Login(authPage);
    passwordLineEdit = new Password(authPage);
    regLabel = new RegLabel(authPage);
    authForEmpl = new AuthForEmpl(authPage);
    enter = new Enter(authPage);
    forgotPassLabel = new ForgotPassLabel(authPage);
    authButton = new AuthPushButton(authPage);
    mainWLayout = new QGridLayout(authPage);
    logPassEditLayout = new QVBoxLayout();
    forgotPassRegLayOut = new QVBoxLayout();
    QVBoxLayout* logoLayout = new QVBoxLayout();

    QPixmap pixmap(":/images/e");
    Logo* authPageLogo = new Logo(authPage, pixmap);

    logoLayout->addWidget(authPageLogo, 20, Qt::AlignCenter);
    logoLayout->addSpacing(45);
    logoLayout->addWidget(enter, 10, Qt::AlignCenter);
    logoLayout->addSpacing(15);

    mainWLayout->addLayout(logoLayout, 0, 0, Qt::AlignTop);

    forgotPassRegLayOut->addWidget(authForEmpl);
    forgotPassRegLayOut->addWidget(regLabel);
    forgotPassRegLayOut->addWidget(forgotPassLabel);

    logPassEditLayout->addWidget(loginLineEdit);
    logPassEditLayout->addSpacing(5);
    logPassEditLayout->addWidget(passwordLineEdit);
    mainWLayout->addLayout(logPassEditLayout, 1, 0);

    mainWLayout->addLayout(forgotPassRegLayOut, 2, 0, Qt::AlignRight);
    mainWLayout->addWidget(authButton, 2, 0);
    mainWLayout->setRowStretch(0, 1);
    mainWLayout->setRowStretch(3, 1);

    // Настройка Hadler'a для главной страницы
    signalMapperMainP = new QSignalMapper(this);
    signalMapperMainP->setMapping(authButton, 1);
    signalMapperMainP->setMapping(loginLineEdit, 2);
    signalMapperMainP->setMapping(passwordLineEdit, 3);
    signalMapperMainP->setMapping(forgotPassLabel, 4);
    signalMapperMainP->setMapping(regLabel, 5);
    signalMapperMainP->setMapping(authForEmpl, 6);
    connect(authButton, &QPushButton::clicked, signalMapperMainP, QOverload<>::of(&QSignalMapper::map));
    connect(forgotPassLabel, &QLabel::linkActivated, signalMapperMainP, QOverload<>::of(&QSignalMapper::map));
    connect(authForEmpl, &QLabel::linkActivated, signalMapperMainP, QOverload<>::of(&QSignalMapper::map));
    connect(regLabel, &QLabel::linkActivated, signalMapperMainP, QOverload<>::of(&QSignalMapper::map));
    connect(passwordLineEdit, &QLineEdit::editingFinished, signalMapperMainP, QOverload<>::of(&QSignalMapper::map));
    connect(loginLineEdit, &QLineEdit::editingFinished, signalMapperMainP, QOverload<>::of(&QSignalMapper::map));
    connect(signalMapperMainP, &QSignalMapper::mappedInt , this, &MainWindow::AuthPHandleItems);
    // Добавляем страницу в QStackedLayout
    stackedLayout->addWidget(authPage);
}

void MainWindow::EmployeePageDraw()
{
    QWidget* employeeAuthPage = new QWidget(this);
    employeeAuthPage->setFocusPolicy(Qt::StrongFocus);
    empBackButton = new BackButton(employeeAuthPage);
    emMainLayout = new QVBoxLayout(employeeAuthPage);
    emMainLabel = new EmMainLabel(employeeAuthPage);
    emAuthCodeLineEdit = new EmAuthCodeEnter(employeeAuthPage);
    emEnterButton = new EmEnterButton(employeeAuthPage);

    QPixmap pixmap(":/images/e");
    Logo* employeePageLogo = new Logo(employeeAuthPage, pixmap);

    emMainLayout->addStretch(1);
    emMainLayout->addWidget(employeePageLogo, 0, Qt::AlignCenter);
    emMainLayout->addSpacing(45);
    emMainLayout->addWidget(emMainLabel, 0, Qt::AlignCenter);
    emMainLayout->addSpacing(75);
    emMainLayout->addWidget(emAuthCodeLineEdit, 0, Qt::AlignCenter);
    emMainLayout->addSpacing(10);
    emMainLayout->addWidget(emEnterButton, 0, Qt::AlignCenter);
    emMainLayout->addStretch(10);
    emMainLayout->addWidget(empBackButton, 0, Qt::AlignLeft);


    // Настройка Hadler'a для страницы авторизации для сотрудника
    signalMapperEmP = new QSignalMapper(this);
    signalMapperEmP->setMapping(emAuthCodeLineEdit, 1);
    signalMapperEmP->setMapping(emEnterButton, 2);
    signalMapperEmP->setMapping(empBackButton, 3);
    connect(emAuthCodeLineEdit, &QLineEdit::editingFinished, signalMapperEmP, QOverload<>::of(&QSignalMapper::map));
    connect(emEnterButton, &QPushButton::clicked, signalMapperEmP, QOverload<>::of(&QSignalMapper::map));
    connect(empBackButton, &QPushButton::clicked, signalMapperEmP, QOverload<>::of(&QSignalMapper::map));
    connect(signalMapperEmP, &QSignalMapper::mappedInt, this, &MainWindow::EmployeePHandleItems);

    stackedLayout->addWidget(employeeAuthPage);
}

void MainWindow::RegistrationPageDraw()
{
    QWidget* regPage = new QWidget(this);
    regPage->setFocusPolicy(Qt::StrongFocus);
    regMainLayout = new QVBoxLayout(regPage);
    regMainLabel = new RegMainLabel(this);
    regEnterButton = new RegEnterButton(this);
    regLastNameLineEdit = new RegLastNameLineEdit(this);
    regFirstNameLineEdit = new RegFirstNameLineEdit(this);
    regMiddleNameLineEdit = new RegMiddleNameLineEdit(this);
    regEmailLineEdit= new RegEmailLineEdit(this);
    regPasswordLineEdit = new RegPasswordLineEdit(this);
    regBackButton = new BackButton(this);
    signalMapperReg = new QSignalMapper(this);

    QPixmap pixmap(":/images/e");
    Logo* registrationPageLogo = new Logo(regPage, pixmap);

    regMainLayout->addStretch(1);
    regMainLayout->addWidget(registrationPageLogo, 0, Qt::AlignCenter);
    regMainLayout->addSpacing(45);
    regMainLayout->addWidget(regMainLabel,0, Qt::AlignCenter);
    regMainLayout->addSpacing(75);
    regMainLayout->addWidget(regLastNameLineEdit, 0, Qt::AlignCenter );
    regMainLayout->addSpacing(5);
    regMainLayout->addWidget(regFirstNameLineEdit, 0, Qt::AlignCenter);
    regMainLayout->addSpacing(5);
    regMainLayout->addWidget(regMiddleNameLineEdit, 0, Qt::AlignCenter);
    regMainLayout->addSpacing(5);
    regMainLayout->addWidget(regEmailLineEdit, 0, Qt::AlignCenter);
    regMainLayout->addSpacing(5);
    regMainLayout->addWidget(regPasswordLineEdit, 0, Qt::AlignCenter);
    regMainLayout->addSpacing(10);
    regMainLayout->addWidget(regEnterButton, 0, Qt::AlignCenter);
    regMainLayout->addStretch(10);
    regMainLayout->addWidget(regBackButton, 0, Qt::AlignLeft);

    stackedLayout->addWidget(regPage);

    signalMapperReg->setMapping(regLastNameLineEdit , 1);
    signalMapperReg->setMapping(regFirstNameLineEdit , 2);
    signalMapperReg->setMapping(regMiddleNameLineEdit , 3);
    signalMapperReg->setMapping(regEmailLineEdit , 4);
    signalMapperReg->setMapping(regPasswordLineEdit , 5);
    signalMapperReg->setMapping(regEnterButton , 6);
    signalMapperReg->setMapping(regBackButton , 7);
    connect(regLastNameLineEdit, &QLineEdit::editingFinished, signalMapperReg,  QOverload<>::of(&QSignalMapper::map));
    connect(regFirstNameLineEdit,  &QLineEdit::editingFinished, signalMapperReg,  QOverload<>::of(&QSignalMapper::map));
    connect(regMiddleNameLineEdit,  &QLineEdit::editingFinished, signalMapperReg,  QOverload<>::of(&QSignalMapper::map));
    connect(regEmailLineEdit,  &QLineEdit::editingFinished, signalMapperReg,  QOverload<>::of(&QSignalMapper::map));
    connect(regPasswordLineEdit,  &QLineEdit::editingFinished, signalMapperReg,  QOverload<>::of(&QSignalMapper::map));
    connect(regEnterButton, &QPushButton::clicked, signalMapperReg, QOverload<>::of(&QSignalMapper::map));
    connect(regBackButton, &QPushButton::clicked, signalMapperReg, QOverload<>::of(&QSignalMapper::map));
    connect(signalMapperReg, &QSignalMapper::mappedInt, this, &MainWindow::RegPHandleItems);
}

void MainWindow::ForgotPassPageDraw()
{
    QWidget* forgotPassPage = new QWidget(this);
    forgotPassPage->setFocusPolicy(Qt::StrongFocus);
    QPixmap pixmap(":/images/e");
    QVBoxLayout* forgotPLayout = new QVBoxLayout(forgotPassPage);
    QPushButton* forgotPBackButton = new BackButton(forgotPassPage);
    Logo* forgotPPageLogo = new Logo(forgotPassPage, pixmap);
    forgotPMainLabel = new ForgotPMainLabel(forgotPassPage);
    forgotPEmailLEdit = new ForgotPEmailLEdit(forgotPassPage);
    forgotPTokLEdit = new ForgotPTokLEdit(forgotPassPage);
    forgotPNewPassLEdit =  new ForgotNewPassLEdit(forgotPassPage);
    forgotPEnterButton = new ForgotPEnterButton(forgotPassPage);
    forgotPSignalMapper = new QSignalMapper(forgotPassPage);

    forgotPLayout->addStretch(1);
    forgotPLayout->addWidget(forgotPPageLogo, 0, Qt::AlignCenter);
    forgotPLayout->addSpacing(45);
    forgotPLayout->addWidget(forgotPMainLabel, 0, Qt::AlignCenter);
    forgotPLayout->addSpacing(75);
    forgotPLayout->addWidget(forgotPEmailLEdit, 0, Qt::AlignCenter);
    forgotPLayout->addSpacing(5);
    forgotPLayout->addWidget(forgotPTokLEdit, 0, Qt::AlignCenter);
    forgotPLayout->addSpacing(5);
    forgotPLayout->addWidget(forgotPNewPassLEdit, 0, Qt::AlignCenter);
    forgotPLayout->addSpacing(20);
    forgotPLayout->addWidget(forgotPEnterButton, 0, Qt::AlignCenter);
    forgotPLayout->addStretch(5);
    forgotPLayout->addWidget(forgotPBackButton , 0, Qt::AlignLeft);

    forgotPSignalMapper->setMapping(forgotPEmailLEdit, 1);
    forgotPSignalMapper->setMapping(forgotPTokLEdit, 2);
    forgotPSignalMapper->setMapping(forgotPNewPassLEdit, 3);
    forgotPSignalMapper->setMapping(forgotPEnterButton, 4);
    forgotPSignalMapper->setMapping(forgotPBackButton, 5);

    connect(forgotPEmailLEdit, &QLineEdit::editingFinished, forgotPSignalMapper, QOverload<>::of(&QSignalMapper::map));
    connect(forgotPTokLEdit, &QLineEdit::editingFinished, forgotPSignalMapper, QOverload<>::of(&QSignalMapper::map));
    connect(forgotPNewPassLEdit, &QLineEdit::editingFinished, forgotPSignalMapper, QOverload<>::of(&QSignalMapper::map));
    connect(forgotPEnterButton, &QPushButton::clicked, forgotPSignalMapper, QOverload<>::of(&QSignalMapper::map));
    connect(forgotPBackButton, &QPushButton::clicked, forgotPSignalMapper, QOverload<>::of(&QSignalMapper::map));
    connect(forgotPSignalMapper,  &QSignalMapper::mappedInt, this, &MainWindow::ForgotPassPHandleItems);
    stackedLayout->addWidget(forgotPassPage);
}

void MainWindow::EmployeeWorkPageDraw()
{

    QWidget* employeePage = new QWidget(this);
    QWidget* HContainerBottom = new QWidget(this);
    QWidget* vContainerCarF = new QWidget(this);
    QWidget* vContainerPactF = new QWidget(this);
    QWidget* vContainerView = new QWidget(this);

    employeePage->setFocusPolicy(Qt::StrongFocus);
    QPixmap pixmap(":/images/e");

    QVBoxLayout* emWorkPageLayout =  new QVBoxLayout(employeePage);
    QHBoxLayout* emWorkPageBottonWidgets = new QHBoxLayout(HContainerBottom);
    QVBoxLayout* firstBlock = new QVBoxLayout(vContainerCarF);
    QVBoxLayout* secondBlock = new QVBoxLayout(vContainerPactF);
    QVBoxLayout* thirdBlock = new QVBoxLayout(vContainerView);
    Logo* emPageLogo = new Logo(employeePage, pixmap);
    emWPModel = new QSqlQueryModel(employeePage);
    ResultView = new ResultTreeView(employeePage);


    emWorkPageMainLabel = new EmWorkPageMainLabel(employeePage);
    emCarModelNameLE = new EmCarModelNameLE(employeePage) ;
    emCarManufLE = new EmCarManufLE(employeePage);
    emEngineCapLE = new EmEngineCapLE(employeePage);
    emMaxSpeedLE = new EmMaxSpeedLE(employeePage);
    emGenNumLE = new EmGenNumLE(employeePage);
    emHorsePowLE = new EmHorsePowLE(employeePage);
    emCostLE= new EmCostLE(employeePage);
    emMileAgeLE = new EmMileAgeLE(employeePage);
    emNumOrderLE = new EmNumOrderLE(employeePage);
    emAccFindCarB = new EmAccFindCarB(employeePage);
    emPactFindB = new  EmPactFindB (employeePage);

    emWorkPageLayout->addStretch(1);
    emWorkPageLayout->addWidget(emPageLogo, 0, Qt::AlignCenter);
    emWorkPageLayout->addStretch(1);
    emWorkPageLayout->addWidget(emWorkPageMainLabel, 0, Qt::AlignCenter);
    emWorkPageLayout->addStretch(2);

    firstBlock->addWidget(emCarModelNameLE, 0, Qt::AlignBottom);
    firstBlock->addSpacing(5);
    firstBlock->addWidget(emCarManufLE, 0,  Qt::AlignBottom);
    firstBlock->addSpacing(5);
    firstBlock->addWidget(emEngineCapLE, 0,  Qt::AlignBottom);
    firstBlock->addSpacing(5);
    firstBlock->addWidget(emMaxSpeedLE, 0);
    firstBlock->addSpacing(5);
    firstBlock->addWidget(emGenNumLE, 0,  Qt::AlignBottom);
    firstBlock->addSpacing(5);
    firstBlock->addWidget(emHorsePowLE, 0,  Qt::AlignBottom);
    firstBlock->addSpacing(5);
    firstBlock->addWidget(emHorsePowLE, 0,  Qt::AlignBottom);
    firstBlock->addSpacing(5);
    firstBlock->addWidget(emCostLE, 0,  Qt::AlignBottom);
    firstBlock->addSpacing(5);
    firstBlock->addWidget(emMileAgeLE, 0,  Qt::AlignBottom);
    firstBlock->addSpacing(5);
    firstBlock->addWidget(emAccFindCarB);

    emWorkPageBottonWidgets->addWidget(vContainerCarF);

    secondBlock->addStretch(1);
    secondBlock->addWidget(emNumOrderLE);;
    secondBlock->addSpacing(5);
    secondBlock->addWidget(emPactFindB);

    thirdBlock->addWidget(ResultView, 0);


    emWorkPageBottonWidgets->addWidget(vContainerPactF, 0, Qt::AlignBottom);
    emWorkPageBottonWidgets->addWidget(vContainerView, 1, Qt::AlignBottom);
    emWorkPageLayout->addWidget(HContainerBottom, 0, Qt::AlignBottom);
    stackedLayout->addWidget(employeePage);

     QSignalMapper* emWorkPageSM = new QSignalMapper(employeePage);
     emWorkPageSM->setMapping(emCarModelNameLE , 1);
     emWorkPageSM->setMapping(emCarManufLE, 2);
     emWorkPageSM->setMapping(emEngineCapLE , 3);
     emWorkPageSM->setMapping(emMaxSpeedLE, 4);
     emWorkPageSM->setMapping(emGenNumLE, 5);
     emWorkPageSM->setMapping(emHorsePowLE, 6);
     emWorkPageSM->setMapping(emCostLE, 7);
     emWorkPageSM->setMapping(emMileAgeLE, 8);
     emWorkPageSM->setMapping(emNumOrderLE, 9);
     emWorkPageSM->setMapping(emAccFindCarB, 10);
     emWorkPageSM->setMapping(emPactFindB, 11);

     connect(emCarModelNameLE, &QLineEdit::editingFinished, emWorkPageSM, QOverload<>::of(&QSignalMapper::map));
     connect(emCarManufLE, &QLineEdit::editingFinished, emWorkPageSM, QOverload<>::of(&QSignalMapper::map));
     connect(emEngineCapLE, &QLineEdit::editingFinished, emWorkPageSM, QOverload<>::of(&QSignalMapper::map));
     connect(emMaxSpeedLE, &QLineEdit::editingFinished, emWorkPageSM, QOverload<>::of(&QSignalMapper::map));
     connect(emGenNumLE, &QLineEdit::editingFinished, emWorkPageSM, QOverload<>::of(&QSignalMapper::map));
     connect(emHorsePowLE, &QLineEdit::editingFinished, emWorkPageSM, QOverload<>::of(&QSignalMapper::map));
     connect(emCostLE, &QLineEdit::editingFinished, emWorkPageSM, QOverload<>::of(&QSignalMapper::map));
     connect(emNumOrderLE, &QLineEdit::editingFinished, emWorkPageSM, QOverload<>::of(&QSignalMapper::map));
     connect(emMileAgeLE, &QLineEdit::editingFinished, emWorkPageSM, QOverload<>::of(&QSignalMapper::map));
     connect(emPactFindB, &QPushButton::clicked, emWorkPageSM, QOverload<>::of(&QSignalMapper::map));
     connect(emAccFindCarB, &QPushButton::clicked, emWorkPageSM, QOverload<>::of(&QSignalMapper::map));
     connect(emWorkPageSM,  &QSignalMapper::mappedInt, this, &MainWindow::EmployeeWorkPageHandleItems);
}

void MainWindow::UserPageDraw()
{
    QWidget* userPage = new QWidget(this);
    userPage->setFocusPolicy(Qt::StrongFocus);
    QPixmap pixmap(":/images/e");
    QVBoxLayout* mainVBlock = new QVBoxLayout(userPage);
    userPageModel = new QSqlQueryModel(userPage);
    userCarSearchLE = new UserCarSearchLE(userPage);
    userResultView = new UserResultView(userPage);
    userAddShopBPB = new UserAddShopBPB(userPage);
    userToBacketPB = new UserToBacketPB(userPage);
    userRefreshResultView = new UserRefreshResultView(userPage);
    Logo* userPageLogo = new Logo(userPage, pixmap);
    userProxyModel = new QSortFilterProxyModel(userPage);
    userProxyModel->setSourceModel(userPageModel);
    userResultView->setModel(userProxyModel);
    QItemSelectionModel* selectionModel = userResultView->selectionModel();


    mainVBlock->addWidget(userPageLogo, 1, Qt::AlignCenter);
    mainVBlock->addWidget(userCarSearchLE, 1, Qt::AlignLeft);
    mainVBlock->addSpacing(5);
    mainVBlock->addWidget(userResultView, 1);
    mainVBlock->addSpacing(5);
    mainVBlock->addWidget(userAddShopBPB, 1, Qt::AlignRight);
    mainVBlock->addSpacing(5);
    mainVBlock->addWidget(userToBacketPB, 1, Qt::AlignRight);
    mainVBlock->addSpacing(5);
    mainVBlock->addWidget(userRefreshResultView, 1, Qt::AlignRight);
    mainVBlock->addStretch(1);
    stackedLayout->addWidget(userPage);

    QSignalMapper* userPageMapper = new QSignalMapper(userPage);
    userPageMapper->setMapping(userCarSearchLE, 1);
    userPageMapper->setMapping(userAddShopBPB, 2);
    userPageMapper->setMapping(userRefreshResultView, 3);
    userPageMapper->setMapping(userToBacketPB, 4);

    connect(userCarSearchLE, &QLineEdit::textChanged, userPageMapper, QOverload<>::of(&QSignalMapper::map));
    connect(userAddShopBPB, &QPushButton::clicked, userPageMapper, QOverload<>::of(&QSignalMapper::map));
    connect(userRefreshResultView, &QPushButton::clicked, userPageMapper, QOverload<>::of(&QSignalMapper::map));
    connect(userToBacketPB, &QPushButton::clicked, userPageMapper,  QOverload<>::of (&QSignalMapper::map));
    connect(selectionModel, &QItemSelectionModel::selectionChanged, this,  &MainWindow::UserResultViewCD);
    connect(userPageMapper, &QSignalMapper::mappedInt, this, &MainWindow::UserPageHandleItems);

}

void MainWindow::BacketPageDraw()
{
    QWidget* backetPage = new QWidget(this);
    backetPage->setFocusPolicy(Qt::StrongFocus);
    QPixmap pixmap(":/images/e");
    Logo* backetPageLogo = new Logo(backetPage, pixmap);
    QVBoxLayout* mainVBlock = new QVBoxLayout(backetPage);
    backetResultView = new BacketResultView(backetPage);
    userBacketModel = new QStandardItemModel(backetPage);
    userBacketModel->setHorizontalHeaderLabels({"Название автомобиля", "Цена"});
    backetPlaceOfferPB = new BacketPlaceOfferPB(backetPage);
    backetClearPB = new BacketClearPB(backetPage);
    backetBackPB = new BackButton(backetPage);
    backetMainLabel = new BacketMainLabel(backetPage);

    backetResultView->header()->setSectionResizeMode(QHeaderView::Stretch);
    backetResultView->header()->setDefaultAlignment(Qt::AlignCenter);
    backetResultView->header()->setSectionsMovable(false);
    backetResultView->setItemDelegate(new CenteredItemDelegate(userResultView));
    backetResultView->setModel(userBacketModel);

    mainVBlock->addWidget(backetPageLogo, 1, Qt::AlignCenter);
    mainVBlock->addStretch(1);
    mainVBlock->addWidget(backetMainLabel, 1, Qt::AlignCenter);
    mainVBlock->addStretch(1);
    mainVBlock->addWidget(backetResultView, 1);
    mainVBlock->addSpacing(5);
    mainVBlock->addWidget(backetPlaceOfferPB, 1, Qt::AlignRight);
    mainVBlock->addSpacing(5);
    mainVBlock->addWidget(backetClearPB, 1, Qt::AlignRight);
    mainVBlock->addWidget(backetBackPB, 0, Qt::AlignLeft);
    mainVBlock->addStretch(1);

    stackedLayout->addWidget(backetPage);
    QSignalMapper* backetPageMapper = new QSignalMapper(backetPage);
    backetPageMapper->setMapping(backetPlaceOfferPB, 1);
    backetPageMapper->setMapping(backetClearPB, 2);
    backetPageMapper->setMapping(backetBackPB, 3);
    connect(backetPlaceOfferPB, &QPushButton::clicked, backetPageMapper, QOverload<>::of(&QSignalMapper::map));
    connect(backetBackPB, &QPushButton::clicked, backetPageMapper, QOverload<>::of(&QSignalMapper::map));
    connect(backetClearPB, &QPushButton::clicked, backetPageMapper, QOverload<>::of(&QSignalMapper::map));
    connect(backetPageMapper, &QSignalMapper::mappedInt, this, &MainWindow::BacketPageHandleItems);
}

void MainWindow::AdminPageDraw()
{
    QWidget* adminPage = new QWidget(this);
    QWidget* aHSubPivot = new QWidget(this);
    QWidget* aVCarPivot = new QWidget(this);
    QWidget* aCarHSubPivot = new QWidget(this);
    QWidget* aCarVSubPivot = new QWidget(this);
    QWidget* aEmlpHSubPivot = new QWidget(this);
    QWidget* aEmplVSubPivot = new QWidget(this);
    QWidget* aJobHSubPivot = new QWidget(this);
    QWidget* aJobVSubPivot = new QWidget(this);
    QWidget* aVEmplLayout = new QWidget(this);
    QWidget* aVJobLayout = new QWidget(this);
    QSignalMapper* aMapper = new QSignalMapper(adminPage);

    adminPage->setFocusPolicy(Qt::StrongFocus);
    QVBoxLayout* aMainLayout = new QVBoxLayout(adminPage);
    QHBoxLayout* aSubMainLayout = new QHBoxLayout(aHSubPivot);
    QVBoxLayout* aCarLayout = new QVBoxLayout(aVCarPivot);
    QHBoxLayout* aCarSubLayout = new QHBoxLayout(aCarHSubPivot);
    QVBoxLayout* aCarVSubLayout = new QVBoxLayout(aCarVSubPivot);
    QVBoxLayout* aEmpLayout = new QVBoxLayout(aVEmplLayout);
    QHBoxLayout* aEmplSubLayout = new QHBoxLayout(aEmlpHSubPivot);
    QVBoxLayout* aEmplVSubLayout = new QVBoxLayout(aEmplVSubPivot);
    QVBoxLayout* aJobLayout = new QVBoxLayout(aVJobLayout);
    QHBoxLayout* aJobSubLayout = new QHBoxLayout(aJobHSubPivot);
    QVBoxLayout* aJobSubVSubLayout =new QVBoxLayout(aJobVSubPivot);
    QPixmap pixmap(":/images/e");
    Logo* adminPageLogo = new Logo(adminPage, pixmap);
    aMainLabel = new AMainLabel(adminPage);

    aModelNameLE = new AModelNameLE(adminPage);
    aManufNameLE = new AManufNameLE(adminPage);
    aManufCountryLE = new AManufCountryLE(adminPage);
    aEngineCapLE = new AEngineCapLE(adminPage);
    aMaxSpeedLE = new AMaxSpeedLE(adminPage);
    aGenNumLE = new AGenNumLE(adminPage);
    aHorsePowerLE = new AHorsePowerLE(adminPage);
    aCarCostLE = new ACarCostLE(adminPage);
    aMileAgeLE = new AMileAgeLE(adminPage);
    aAccompCarPB = new AAccompCarPB(adminPage);
    aCarAddCB = new ACarAddCB(adminPage);
    aCarDeleteCB = new ACarDeleteCB(adminPage);

    aJobTitleLE = new AJobTitleLE(adminPage);
    aPasspDataLE = new APasspDataLE(adminPage);
    aBirthDateLE = new ABirthDateLE(adminPage);
    aLastNameLE = new ALastNameLE(adminPage);
    aFirstNameLE = new AFirstNameLE(adminPage);
    aMiddleNameLE = new AMiddleNameLE(adminPage);
    aAccompEmplPB = new AAccompEmplPB(adminPage);
    aEmplAddCB = new AEmplAddCB(adminPage);
    aEmplDeleteCB = new AEmplDeleteCB(adminPage);

    aJobTitleNameLE= new AJobTitleNameLE(adminPage);
    aJobSalaryLE = new AJobSalaryLE(adminPage);
    aJobAccompPB = new AJobAccompPB(adminPage);
    aJobAddCB = new AJobAddCB(adminPage);
    aJobDeleteCB = new AJobDeleteCB(adminPage);

    aMainLayout->addWidget(adminPageLogo, 1, Qt::AlignCenter);
    aMainLayout->addWidget(aMainLabel, 1, Qt::AlignCenter);
    aMainLayout->addStretch(1);

    aCarVSubLayout ->addWidget(aCarAddCB);
    aCarVSubLayout->addWidget(aCarDeleteCB);
    aCarSubLayout->addWidget(aAccompCarPB);
    aCarSubLayout->addWidget(aCarVSubPivot);
    aCarSubLayout->addStretch(1);
    aCarLayout->addWidget(aModelNameLE);
    aCarLayout->addSpacing(5);
    aCarLayout->addWidget(aManufNameLE);
    aCarLayout->addSpacing(5);
    aCarLayout->addWidget(aManufCountryLE);
    aCarLayout->addSpacing(5);
    aCarLayout->addWidget(aEngineCapLE);
    aCarLayout->addSpacing(5);
    aCarLayout->addWidget(aMaxSpeedLE);
    aCarLayout->addSpacing(5);
    aCarLayout->addWidget(aGenNumLE);
    aCarLayout->addSpacing(5);
    aCarLayout->addWidget(aHorsePowerLE);
    aCarLayout->addSpacing(5);
    aCarLayout->addWidget(aMileAgeLE);
    aCarLayout->addSpacing(5);
    aCarLayout->addWidget(aCarCostLE);
    aCarLayout->addSpacing(5);
    aCarLayout->addWidget(aCarHSubPivot);

    aEmplVSubLayout->addWidget(aEmplAddCB);
    aEmplVSubLayout->addWidget(aEmplDeleteCB);
    aEmplSubLayout->addWidget(aAccompEmplPB);
    aEmplSubLayout->addWidget(aEmplVSubPivot);
    aEmplSubLayout->addStretch(1);

    aEmpLayout->addStretch(1);
    aEmpLayout->addWidget(aJobTitleLE);
    aEmpLayout->addSpacing(5);
    aEmpLayout->addWidget(aPasspDataLE);
    aEmpLayout->addSpacing(5);
    aEmpLayout->addWidget(aBirthDateLE);
    aEmpLayout->addSpacing(5);
    aEmpLayout->addWidget(aLastNameLE);
    aEmpLayout->addSpacing(5);
    aEmpLayout->addWidget(aFirstNameLE);
    aEmpLayout->addSpacing(5);
    aEmpLayout->addWidget(aMiddleNameLE);
    aEmpLayout->addWidget(aEmlpHSubPivot);

    aJobSubVSubLayout->addWidget(aJobAddCB);
    aJobSubVSubLayout->addWidget(aJobDeleteCB);
    aJobSubLayout->addWidget(aJobAccompPB);
    aJobSubLayout->addWidget(aJobVSubPivot);

    aJobLayout->addStretch(1);
    aJobLayout->addWidget(aJobTitleNameLE);
    aJobLayout->addSpacing(5);
    aJobLayout->addWidget(aJobSalaryLE);
    aJobLayout->addWidget(aJobHSubPivot);


    aSubMainLayout->addWidget(aVCarPivot);
    aSubMainLayout->addSpacing(30);
    aSubMainLayout->addWidget(aVEmplLayout);
    aSubMainLayout->addSpacing(30);
    aSubMainLayout->addWidget(aVJobLayout);
    aSubMainLayout->addStretch(1);


    aMainLayout->addWidget(aHSubPivot);

    stackedLayout->addWidget(adminPage);

    aMapper->setMapping(aModelNameLE, 1);
    aMapper->setMapping(aManufCountryLE, 2);
    aMapper->setMapping(aManufNameLE, 3);
    aMapper->setMapping(aEngineCapLE, 4);
    aMapper->setMapping(aMaxSpeedLE, 5);
    aMapper->setMapping(aGenNumLE, 6);
    aMapper->setMapping(aHorsePowerLE, 7);
    aMapper->setMapping(aCarCostLE, 8);
    aMapper->setMapping(aMileAgeLE, 9);
    aMapper->setMapping(aCarAddCB, 10);
    aMapper->setMapping(aCarDeleteCB, 11);
    aMapper->setMapping(aAccompCarPB, 12);

    aMapper->setMapping(aJobTitleLE, 13);
    aMapper->setMapping(aPasspDataLE, 14);
    aMapper->setMapping(aBirthDateLE, 15);
    aMapper->setMapping(aLastNameLE, 16);
    aMapper->setMapping(aFirstNameLE, 17);
    aMapper->setMapping(aMiddleNameLE, 18);
    aMapper->setMapping(aAccompEmplPB, 19);
    aMapper->setMapping(aEmplAddCB, 20);
    aMapper->setMapping(aEmplDeleteCB, 21);

    aMapper->setMapping(aJobTitleNameLE, 22);
    aMapper->setMapping(aJobSalaryLE, 23);
    aMapper->setMapping(aJobAccompPB, 24);
    aMapper->setMapping(aJobAddCB, 25);
    aMapper->setMapping(aJobDeleteCB, 26);

    connect(aModelNameLE, &QLineEdit::textChanged, aMapper,QOverload<>::of(&QSignalMapper::map));
    connect(aManufCountryLE, &QLineEdit::textChanged, aMapper,QOverload<>::of(&QSignalMapper::map));
    connect(aManufNameLE, &QLineEdit::textChanged, aMapper,QOverload<>::of(&QSignalMapper::map));
    connect(aEngineCapLE, &QLineEdit::textChanged, aMapper,QOverload<>::of(&QSignalMapper::map));
    connect(aMaxSpeedLE, &QLineEdit::textChanged, aMapper,QOverload<>::of(&QSignalMapper::map));
    connect(aGenNumLE, &QLineEdit::textChanged, aMapper,QOverload<>::of(&QSignalMapper::map));
    connect(aHorsePowerLE, &QLineEdit::textChanged, aMapper,QOverload<>::of(&QSignalMapper::map));
    connect(aMileAgeLE, &QLineEdit::textChanged, aMapper,QOverload<>::of(&QSignalMapper::map));
    connect(aCarCostLE, &QLineEdit::textChanged, aMapper,QOverload<>::of(&QSignalMapper::map));
    connect(aAccompCarPB, &QPushButton::clicked, aMapper,QOverload<>::of(&QSignalMapper::map));
    connect(aCarAddCB, &QCheckBox::stateChanged, aMapper,QOverload<>::of(&QSignalMapper::map));
    connect(aCarDeleteCB, &QCheckBox::stateChanged, aMapper,QOverload<>::of(&QSignalMapper::map));

    connect(aJobTitleLE, &QLineEdit::textChanged, aMapper,QOverload<>::of(&QSignalMapper::map));
    connect(aPasspDataLE, &QLineEdit::textChanged, aMapper,QOverload<>::of(&QSignalMapper::map));
    connect(aBirthDateLE, &QLineEdit::textChanged, aMapper,QOverload<>::of(&QSignalMapper::map));
    connect(aFirstNameLE, &QLineEdit::textChanged, aMapper,QOverload<>::of(&QSignalMapper::map));
    connect(aLastNameLE, &QLineEdit::textChanged, aMapper,QOverload<>::of(&QSignalMapper::map));
    connect(aMiddleNameLE, &QLineEdit::textChanged, aMapper,QOverload<>::of(&QSignalMapper::map));
    connect(aAccompEmplPB, &QPushButton::clicked, aMapper,QOverload<>::of(&QSignalMapper::map));
    connect(aEmplAddCB, &QPushButton::clicked, aMapper,QOverload<>::of(&QSignalMapper::map));
    connect(aEmplDeleteCB, &QPushButton::clicked, aMapper,QOverload<>::of(&QSignalMapper::map));

    connect(aJobTitleNameLE, &QLineEdit::textChanged, aMapper,QOverload<>::of(&QSignalMapper::map));
    connect(aJobSalaryLE, &QLineEdit::textChanged, aMapper,QOverload<>::of(&QSignalMapper::map));
    connect(aJobAccompPB, &QPushButton::clicked, aMapper,QOverload<>::of(&QSignalMapper::map));
    connect(aJobAddCB, &QCheckBox::stateChanged, aMapper,QOverload<>::of(&QSignalMapper::map));
    connect(aJobDeleteCB, &QCheckBox::stateChanged, aMapper,QOverload<>::of(&QSignalMapper::map));

    connect(aMapper, &QSignalMapper::mappedInt, this, &MainWindow::AdminPageHandleItems);
}

void MainWindow::AdminPageHandleItems(const int id)
{
    bool ValidateData;
    switch(id)
    {
        case 1:
            aModelName = aModelNameLE->text();
        break;

        case 2:
            aManufCountry = aManufCountryLE->text();
        break;

        case 3:
            aManufName  = aManufNameLE->text();
        break;

        case 4:
           aEngineCap = aEngineCapLE->text();
        break;

        case 5:
           aMaxSpeed = aMaxSpeedLE->text();
        break;

        case 6:
          aGenNum  = aGenNumLE->text();
        break;

        case 7:
          aHorseNum  = aHorsePowerLE->text();
        break;

        case 8:
          aCarCost  = aCarCostLE->text();
        break;

        case 9:
            aCarMileAge = aMileAgeLE->text();
        break;

        case 10:
            if (aCarAddCB->checkState() == Qt::Checked)
            {
                aCarDeleteCB->setCheckState(Qt::Unchecked);
                aCarStateDeleteCB = Qt::Unchecked;
            }
             aCarStateAddCB = aCarAddCB->checkState();
        break;

        case 11:
            if (aCarDeleteCB->checkState() == Qt::Checked)
            {
                aCarAddCB->setCheckState(Qt::Unchecked);
                aCarStateAddCB = Qt::Unchecked;
            }
            aCarStateDeleteCB = aCarDeleteCB->checkState();
        break;

        case 12:
            if (aCarAddCB->checkState() == Qt::Unchecked && aCarDeleteCB->checkState() == Qt::Unchecked)
            {
                QMessageBox::warning(this, "Предупреждение", "Выберите тип действия!");
            }
            if (aCarStateAddCB == Qt::Checked)
            {
                ValidateData =
                    ValidateQLEExact(aModelName, modelNameRegex) &&
                    ValidateQLEExact(aManufName, latinWRegex) &&
                    ValidateQLEExact(aManufCountry, lfmRegex) &&
                    ValidateQLEExact(aEngineCap, floatVRegex) &&
                    ValidateQLEExact(aMaxSpeed, intVRegex) &&
                    ValidateQLEExact(aGenNum, intVRegex) &&
                    ValidateQLEExact(aHorseNum, intVRegex) &&
                    ValidateQLEExact(aCarCost,  intVRegex) &&
                    ValidateQLEExact(aCarMileAge,  intVRegex);

                if (ValidateData)
                {
                    parameters[":1"] = aModelName;
                    parameters[":2"] = aManufName;
                    parameters[":3"] = aManufCountry;
                    parameters[":4"] = aEngineCap.toFloat();
                    parameters[":5"] = aHorseNum.toInt();
                    parameters[":6"] = aMaxSpeed.toInt();
                    parameters[":7"] = aGenNum.toInt();
                    parameters[":8"] = aCarCost.toInt();
                    parameters[":9"] = aCarMileAge.toInt();
                    parameters[":10"] = 1;
                    myConPool->executeQueryAsync("SELECT * FROM course_work.cars_update(:1, :2, :3, :4, :5, :6, :7, :8, :9, :10);", this, SLOT(QHAdminCarAdd(QSqlQuery)), parameters);
                }
                else
                {
                    QMessageBox::warning(this, "Предупреждение", "Проверьте корректность введённых данных!");
                }
            }
             if (aCarStateDeleteCB == Qt::Checked)
            {
                if (aModelName.isEmpty() &&
                    aManufName.isEmpty() &&
                    aManufCountry.isEmpty() &&
                    aEngineCap.isEmpty() &&
                    aMaxSpeed.isEmpty() &&
                    aGenNum.isEmpty() &&
                    aHorseNum.isEmpty() &&
                    aCarCost.isEmpty() &&
                    aCarMileAge.isEmpty())
                {
                    QMessageBox::warning(this, "Предупреждение", "Заполните хотя бы одно поле ввода!");
                    break;
                }
                ValidateData =
                    ValidateQLineEdit(aModelName, modelNameRegex) &&
                    ValidateQLineEdit(aManufName, latinWRegex) &&
                    ValidateQLineEdit(aManufCountry, lfmRegex) &&
                    ValidateQLineEdit(aEngineCap, floatVRegex) &&
                    ValidateQLineEdit(aMaxSpeed, intVRegex) &&
                    ValidateQLineEdit(aGenNum, intVRegex) &&
                    ValidateQLineEdit(aHorseNum, intVRegex) &&
                    ValidateQLineEdit(aCarCost,  intVRegex) &&
                    ValidateQLineEdit(aCarMileAge,  intVRegex);
                if (ValidateData)
                {
                    bool convCheck;
                    parameters[":1"] = aModelName.isEmpty() ? QVariant() : aModelName;
                    parameters[":2"] = aManufName.isEmpty() ? QVariant() : aManufName;
                    parameters[":3"] = aManufCountry.isEmpty() ? QVariant() : aManufCountry;
                    parameters[":4"] = aEngineCap.isEmpty() ? QVariant() : QVariant(aEngineCap.toFloat(&convCheck));
                    parameters[":5"] = aHorseNum.isEmpty() ? QVariant() : QVariant(aHorseNum.toInt(&convCheck));
                    parameters[":6"] = aMaxSpeed.isEmpty() ? QVariant() : QVariant(aMaxSpeed.toInt(&convCheck));
                    parameters[":7"] = aGenNum.isEmpty() ? QVariant() : QVariant(aGenNum.toInt(&convCheck));
                    parameters[":8"] = aCarCost.isEmpty() ? QVariant() : QVariant(aCarCost.toInt(&convCheck));
                    parameters[":9"] = aCarMileAge.isEmpty() ? QVariant() : QVariant(aCarMileAge.toInt(&convCheck));
                    parameters[":10"] = 2;
                    myConPool->executeQueryAsync("SELECT * FROM course_work.cars_update(:1, :2, :3, :4, :5, :6, :7, :8, :9, :10);", this, SLOT(QHAdminCarDelete(QSqlQuery)), parameters);
                }
                else
                {
                    QMessageBox::warning(this, "Предупреждение", "Проверьте корректность введённых данных!");
                }
            }
        break;

        case 13:
          aJobTitle  = aJobTitleLE->text();
        break;

        case 14:
          aPasspData  = aPasspDataLE->text();
        break;

        case 15:
            aBirthDate = aBirthDateLE->text();
         break;

        case 16:
           aLastName = aLastNameLE->text();
        break;

        case 17:
            aFirstName=  aFirstNameLE->text();
        break;

        case 18:
           aMiddleName = aMiddleNameLE->text();
        break;

        case 19:

            if (aEmplStateAddCB == Qt::Checked)
            {
                ValidateData =
                    ValidateQLEExact(aJobTitle, lfmRegex) &&
                    ValidateQLEExact(aPasspData, intVRegex) &&
                    ValidateQLEExact(aBirthDate, dateARegex) &&
                    ValidateQLEExact(aLastName, lfmRegex) &&
                    ValidateQLEExact(aMiddleName, lfmRegex) &&
                    ValidateQLEExact(aFirstName, lfmRegex);
                if (ValidateData)
                {
                    parameters[":1"] = aJobTitle;
                    parameters[":2"] = aPasspData.toLongLong();
                    parameters[":3"] = QDateTime::fromString(aBirthDate, "yyyy-MM-dd");
                    parameters[":4"] = aFirstName;
                    parameters[":5"] = aMiddleName;
                    parameters[":6"] = aLastName;
                    parameters[":7"] = EncryptPass(GenerateRandomString());
                    parameters[":8"] = 1;
                    myConPool->executeQueryAsync("SELECT * FROM course_work.update_employee(:1, :2, :3, :4, :5, :6, :7, :8);", this, SLOT(QHAdminEmpAdd(QSqlQuery)), parameters);
                }
                else
                {
                    QMessageBox::warning(this, "Предупреждение", "Проверьте корректность введённых данных!");
                }
            }
            if (aEmpStateDeleteCB == Qt::Checked)
            {
                if (aJobTitle.isEmpty() &&
                    aPasspData.isEmpty() &&
                    aManufCountry.isEmpty() &&
                    aBirthDate.isEmpty() &&
                    aLastName.isEmpty() &&
                    aMiddleName.isEmpty() &&
                    aFirstName.isEmpty())
                {
                    QMessageBox::warning(this, "Предупреждение", "Заполните хотя бы одно поле ввода!");
                    break;
                }

                ValidateData =
                    ValidateQLineEdit(aJobTitle, lfmRegex) &&
                    ValidateQLineEdit(aPasspData, intVRegex) &&
                    ValidateQLineEdit(aBirthDate, dateARegex) &&
                    ValidateQLineEdit(aLastName, lfmRegex) &&
                    ValidateQLineEdit(aMiddleName, lfmRegex) &&
                    ValidateQLineEdit(aFirstName, lfmRegex);
                if (ValidateData)
                {
                    bool convCheck;
                    parameters[":1"] = aJobTitle.isEmpty() ? QVariant() : aJobTitle;
                    parameters[":2"] = aPasspData.isEmpty() ? QVariant() : QVariant(aPasspData.toLongLong(&convCheck));
                    parameters[":3"] = aBirthDate.isEmpty() ? QVariant() : QVariant(QDateTime::fromString(aBirthDate, "yyyy-MM-dd"));
                    parameters[":4"] = aFirstName.isEmpty() ? QVariant() : aFirstName;
                    parameters[":5"] = aMiddleName.isEmpty() ? QVariant() :  aMiddleName;
                    parameters[":6"] = aLastName.isEmpty() ? QVariant() : aLastName;
                    parameters[":7"] = QVariant();
                    parameters[":8"] = 2;
                    myConPool->executeQueryAsync("SELECT * FROM course_work.update_employee(:1, :2, :3, :4, :5, :6, :7, :8);", this, SLOT(QHAdminEmpDelete(QSqlQuery)), parameters);
                }
                else
                {
                    QMessageBox::warning(this, "Предупреждение", "Проверьте корректность введённых данных!");
                }
            }
            if (aEmplDeleteCB->checkState() == Qt::Unchecked && aEmplAddCB->checkState() == Qt::Unchecked)
            {
                QMessageBox::warning(this, "Предупреждение", "Выберите тип действия!");
            }

        break;

        case 20:
            if (aEmplAddCB->checkState() == Qt::Checked)
            {
                aEmplDeleteCB->setCheckState(Qt::Unchecked);
                aEmpStateDeleteCB = Qt::Unchecked;
            }
           aEmplStateAddCB= aEmplAddCB->checkState();
        break;

        case 21:
            if (aEmplDeleteCB->checkState() == Qt::Checked)
            {
                aEmplAddCB->setCheckState(Qt::Unchecked);
                aEmplStateAddCB = Qt::Unchecked;
            }
          aEmpStateDeleteCB  = aEmplDeleteCB->checkState();
        break;

        case 22:
          aJobTitleName  = aJobTitleNameLE->text();
        break;

        case 23:
          aJobSalary  = aJobSalaryLE->text();
        break;

        case 24:
            ValidateData =
                ValidateQLEExact(aJobTitleName, lfmRegex) &&
                ValidateQLEExact(aJobSalary, intVRegex);
            if (aJobAddStateCB == Qt::Checked)
            {
                if (ValidateData)
                {
                    parameters[":1"] = aJobTitleName;
                    parameters[":2"] = aJobSalary;
                    parameters[":3"] = 1;
                    myConPool->executeQueryAsync("SELECT * FROM course_work.update_job_title(:1, :2, :3);", this, SLOT(QHAdminJobTAdd(QSqlQuery)), parameters);
                }
                else
                {
                    QMessageBox::warning(this, "Предупреждение", "Проверьте корректность введённых данных!");
                }
            }
             if (aJobDeleteStateCB == Qt::Checked)
             {
                if(aJobTitleName.isEmpty() &&
                   aJobSalary.isEmpty())
                {
                     QMessageBox::warning(this, "Предупреждение", "Заполните хотя бы одно поле ввода!");
                     break;
                }
                ValidateData =
                    ValidateQLineEdit(aJobTitleName, lfmRegex) &&
                    ValidateQLineEdit(aJobSalary, intVRegex);
                if (ValidateData)
                {
                    bool convCheck;
                    parameters[":1"] = aJobTitleName.isEmpty() ? QVariant() : aJobTitleName;
                    parameters[":2"] = aJobSalary.isEmpty() ? QVariant() : QVariant(aJobSalary.toInt(&convCheck));
                    parameters[":3"] = 2;
                    myConPool->executeQueryAsync("SELECT * FROM course_work.update_job_title(:1, :2, :3);", this, SLOT(QHAdmitJobTDelete(QSqlQuery)), parameters);
                }
                else
                {
                    QMessageBox::warning(this, "Предупреждение", "Проверьте корректность введённых данных!");
                }
             }
             if (aJobAddCB->checkState() == Qt::Unchecked && aJobDeleteCB->checkState() == Qt::Unchecked)
             {
                QMessageBox::warning(this, "Предупреждение", "Выберите тип действия!");
             }

        break;

        case 25:
            if (aJobAddCB->checkState() == Qt::Checked)
            {
                aJobDeleteCB->setCheckState(Qt::Unchecked);
                aJobDeleteStateCB  = Qt::Unchecked;
            }
          aJobAddStateCB = aJobAddCB->checkState();
        break;

        case 26:
            if (aJobDeleteCB->checkState() == Qt::Checked)
            {
                aJobAddCB->setCheckState(Qt::Unchecked);
                aJobAddStateCB = Qt::Unchecked;
            }
          aJobDeleteStateCB  = aJobDeleteCB->checkState();
        break;
    }
}

void MainWindow::BacketPageHandleItems(const int id)
{
    switch(id)
    {
    case 1:
        if (userBacketData.isEmpty())
        {
            QMessageBox::warning(this,"Предупреждение", "Перед оформлением заказа добавьте машины в корзину!");
        }
        else
        {
            BacketItemsParse();
        }
        break;

    case 2:
        ClearBacket();
        break;

    case 3:
        setMinimumSize(1400, 900);
        stackedLayout->setCurrentIndex(5);
        break;
    }
}

void MainWindow::UserPageHandleItems(const int id)
{
    QString filter;
    switch(id)
    {
        case 1:
            filter = userCarSearchLE->text();
            userProxyModel->setFilterFixedString(filter);
            userProxyModel->setFilterKeyColumn(0);
        break;

        case 2:
            if (userViewIndexList.isEmpty())
            {
                QMessageBox::warning(this, "Предупреждение", "Вы ничего не выбрали для покупки!");
            }
            else
            {
                setMinimumSize(1000, 950);
                stackedLayout->setCurrentIndex(6);
                UserAddItemsBacket();
            }
        break;

        case 3:
             myConPool->executeQueryAsync("SELECT * FROM course_work.load_and_refresh_data();", this, SLOT(QHUserLoadData(QSqlQuery)), parameters);
        break;

        case 4:
            setMinimumSize(1000, 950);
            stackedLayout->setCurrentIndex(6);
        break;
    }

}

void MainWindow::UserResultViewCD(const QItemSelection& selected, const QItemSelection& deselected)
{
    QModelIndexList indexesDeselected = deselected.indexes();
    QModelIndexList indexesSelected = selected.indexes();

    // Добавляем только уникальные индексы первой колонки строки
    for (const QModelIndex& index : indexesSelected)
    {
        QModelIndex rowIndex = userPageModel->index(index.row(), 0); // Берем индекс первой колонки строки
        if (!userViewIndexList.contains(rowIndex))
        {
            userViewIndexList.append(rowIndex);
        }
    }

    // Удаляем индексы первой колонки строки
    for (const QModelIndex& index : indexesDeselected)
    {
        QModelIndex rowIndex = userPageModel->index(index.row(), 0);
        userViewIndexList.removeAll(rowIndex);
    }
}

void MainWindow::UserAddItemsBacket()
{
    QModelIndex indexCarName;
    QModelIndex indexCarCost;
    backetOrderedCarsIL.clear();
    for (const QModelIndex& index : userViewIndexList)
    {
        int row = index.row();

        // Проверяем, есть ли уже элемент в корзине
        if (userBacketData.contains(row))
        {
            QModelIndex indexCarNameBasket = userBacketModel->index(row, 0);
            QString carNameStr = userBacketModel->data(indexCarNameBasket).toString();
            carNameStr  += " уже находится в вашей корзине!";
            QMessageBox::warning(this, "Предупреждение", carNameStr);
            return;
        }
        else
        {
            backetOrderedCarsIL.append(index);
            // Получаем данные из модели
            indexCarName = userPageModel->index(row, 0);
            indexCarCost = userPageModel->index(row, 6);

            QStandardItem* carNameCol = new QStandardItem(userPageModel->data(indexCarName).toString());
            QStandardItem* carCostCol = new QStandardItem(userPageModel->data(indexCarCost).toString());

            userBacketData[row].append(carNameCol);
            userBacketData[row].append(carCostCol);
        }

    }

    // Добавляем данные в модель второго QTreeView
    for (int row : userBacketData.keys())
    {
        if (!userBacketModel->findItems(userBacketData[row][0]->text()).isEmpty())
        {
            // Пропускаем добавление, если элемент уже есть
            continue;
        }
        userBacketModel->appendRow(userBacketData[row]);
    }

    // Очищаем выбранные индексы, так как они уже обработаны
    userResultView->selectionModel()->clearSelection(); //Убираем выделение в TreeView
    userViewIndexList.clear();
}

void MainWindow::BacketItemsParse()
{
    int row;
    QModelIndex cellIndex;
    QList<QVariant> rowData;
    QString carRowsData;
    backetDataForOrder.clear();
    for (const QModelIndex& index : backetOrderedCarsIL) //Проходимся по выбранным индексам
    {
        row = index.row();
        rowData.clear();
        for (int column = 0; column < userResultView->model()->columnCount(); ++column)
        {
            cellIndex = userResultView->model()->index(row, column);
            rowData.append(cellIndex.data());
        }
        backetDataForOrder.append(rowData);
    }

    carRowsData = NestedListToCsvString(backetDataForOrder);
    parameters[":1"] = carRowsData;
    parameters[":2"] = loginStr;

    myConPool->executeQueryAsync("SELECT course_work.order_items_handle(:1, :2);", this, SLOT(QHBacketAddCarItems(QSqlQuery)), parameters);

    //Возможно клир и не нужно делать, сохранить индексы, чтобы очистить корзину
}

QString MainWindow::NestedListToCsvString(const QList<QList<QVariant>>& nestedList)
{
    QStringList outerList;
    for (const QList<QVariant>& innerList : nestedList)
    {
        QStringList innerStringList;
        for (const QVariant& item : innerList)
        {
            innerStringList.append(item.toString());
        }
        outerList.append(innerStringList.join(","));
    }
    return outerList.join(";");
}

void MainWindow::RegPHandleItems(const int id)
{
    switch(id)
    {
        case 1: //Поле для ввода фамилии
            regLastName = regLastNameLineEdit->text();
        break;

        case 2: //Поле для ввода имени
            regFirstName = regFirstNameLineEdit->text();
        break;

        case 3: //Поле для ввода отчества
            regMiddleName = regMiddleNameLineEdit->text();
        break;

        case 4: //Поле для ввода почты
            regEmail = regEmailLineEdit->text();
        break;

        case 5: //Поле для ввода пароля
            regPassword = regPasswordLineEdit->text();
        break;

        case 6: //Кнопка регистрации
            if (!regLastName.isEmpty() &&
                !regFirstName.isEmpty() &&
                !regMiddleName.isEmpty() &&
                !regEmail.isEmpty() &&
                !regPassword.isEmpty())
            {
                bool validateData =
                                    ValidateQLineEdit(regLastName, lfmRegex) &&
                                    ValidateQLineEdit(regFirstName, lfmRegex) &&
                                    ValidateQLineEdit(regMiddleName, lfmRegex) &&
                                    ValidateQLineEdit(regEmail, emailRegex) &&
                                    ValidateQLineEdit(regPassword, passwordRegex);
                if (validateData)
                {
                   //Захэшировать пароль перед добавлением
                   parameters[":1"] = regLastName;
                   parameters[":2"] = regMiddleName;
                   parameters[":3"] = regFirstName;
                   parameters[":4"] = regEmail;
                   parameters[":5"] = EncryptPass(regPassword);
                   parameters[":6"] = GenerateRandomString();
                   myConPool->executeQueryAsync("SELECT course_work.reg_user(:1, :2, :3, :4, :5, :6)", this, SLOT(QHRegUser(QSqlQuery)),parameters);

                }
                else
                {
                    QMessageBox::warning(this, "Предупреждение", "Проверьте корректность введённых данных!");
                }
            }
            else
            {
                QMessageBox::warning(this, "Предупреждение", "Несколько полей для ввода данных пусты!");
            }
        break;

        case 7: //Кнопка назад
            regLastNameLineEdit->clear();
            regFirstNameLineEdit->clear();
            regMiddleNameLineEdit->clear();
            regEmailLineEdit->clear();
            regPasswordLineEdit->clear();
            stackedLayout->setCurrentIndex(0);
        break;
    }
}

void MainWindow::AuthPHandleItems(const int id)
{
    switch(id)
    {
    case 1: //Тут нажатие на кнопку авторизации. Отправка запроса к базе данных
        if (!loginStr.isEmpty() && !passwordStr.isEmpty())
        {
            bool ValidateData =
                            ValidateQLineEdit(passwordStr, passwordRegex) &&
                            ValidateQLineEdit(loginStr, emailRegex);
            if (ValidateData)
            {
                parameters[":1"] = loginStr;
                parameters[":2"] = EncryptPass(passwordStr);
                myConPool->executeQueryAsync("SELECT * FROM course_work.auth_check(:1, :2);", this, SLOT(QHAuthUserAuth(QSqlQuery)), parameters);
                //Тут выполняем запрос с использованием parameters
            }
            else
            {
                QMessageBox::warning(this, "Предупреждение", "Проверьте корректность введённых данных!");
            }
        }
        else
        {
            QMessageBox::warning(this, "Предупреждение", "Поля логин или пароль пусты!");
        }

        break;

    case 2:     //Ввод логина
        loginStr = loginLineEdit->text();
    break;

    case 3:     //Ввод пароля
        passwordStr = passwordLineEdit->text();
    break;

    case 4:     //Нажатие на поле забыли пароль
        stackedLayout->setCurrentIndex(3); //3
    break;

    case 5:     //Нажатие на поле регистрация
        stackedLayout->setCurrentIndex(2);  // Просто переключаемся на страницу регистрации
        break;

    case 6:     //Нажатие на поле вход для сотруников
        stackedLayout->setCurrentIndex(1);
    break;

    }

}

void MainWindow::EmployeePHandleItems(const int id)
{
    switch(id)
    {
    case 1:
        authCode = emAuthCodeLineEdit->text();
        break;

    case 2:
        if (!authCode.isEmpty())
        {
            bool validateData = ValidateQLineEdit(authCode, authCodeRegex);

            if (validateData)
            {
                parameters[":1"] =  EncryptPass(authCode); //Добавить шифрование пароля
                myConPool->executeQueryAsync("SELECT * FROM course_work.auth_employee_check(:1);", this, SLOT(QHAuthEmployeeAuth(QSqlQuery)), parameters);
            }
            else
            {
                QMessageBox::warning(this, "Предупреждение", "Проверьте правильность введённых данных!");
            }
        }
        else
        {
            QMessageBox::warning(this, "Предупреждение", "Введите код авторизации сотрудника!");
        }
        break;

    case 3:
        emAuthCodeLineEdit->clear();
        stackedLayout->setCurrentIndex(0);
        break;
    }
}

void MainWindow::ForgotPassPHandleItems(const int id)
{
    switch(id)
    {
        case 1:
            forgotPEmail = forgotPEmailLEdit->text();
        break;

        case 2:
            forgotPRecToken = forgotPTokLEdit->text();
        break;

        case 3:
            forgotPNewPassword = forgotPNewPassLEdit->text();
        break;

        case 4:
            if (!forgotPEmail.isEmpty() && !forgotPNewPassword.isEmpty() && !forgotPRecToken.isEmpty())
            {
                bool validateData =
                            ValidateQLineEdit(forgotPEmail, emailRegex) &&
                            ValidateQLineEdit(forgotPNewPassword, passwordRegex) &&
                            ValidateQLineEdit(forgotPRecToken, authCodeRegex);
                if (validateData)
                {
                    parameters[":1"] = forgotPEmail;
                    parameters[":2"] = EncryptPass(forgotPNewPassword);
                    parameters[":3"] = forgotPRecToken;
                    parameters[":4"] = GenerateRandomString();
                    myConPool->executeQueryAsync("SELECT * course_work.recover_pass(:1, :2, :3, :4);", this, SLOT(QHRecovUserPass(QSqlQuery)), parameters);
                    //Тут запрос
                }
                else
                {
                    QMessageBox::warning(this, "Предупреждение", "Проверьте правильность введённых данных!");
                }
            }
            else
            {
                QMessageBox::warning(this, "Предупреждение", "Поля для ввода данных пусты!");
            }
        break;

        case 5:
            forgotPEmailLEdit->clear();
            forgotPTokLEdit->clear();
            forgotPNewPassLEdit->clear();
            stackedLayout->setCurrentIndex(0);
        break;
    }
}

void MainWindow::EmployeeWorkPageHandleItems(const int id)
{

    switch(id)
    {
        case 1:
            eWPModelName = emCarModelNameLE->text();
        break;

        case 2:
            eWPCarManuf = emCarManufLE->text();
        break;

        case 3:
            eWPEngineCap = emEngineCapLE->text();
        break;

        case 4:
            eWPMaxSpeed = emMaxSpeedLE->text();
        break;

        case 5:
            eWPGenNum = emGenNumLE->text();
        break;

        case 6:
            eWPHorsePower = emHorsePowLE->text();
        break;

        case 7:
            eWPCost = emCostLE->text();
        break;

        case 8:
            eWPMileAge = emMileAgeLE->text();
        break;

        case 9:
            eWPOrderNum = emNumOrderLE->text();
        break;

        case 10:
            if (eWPModelName.isEmpty() &&
                eWPCarManuf.isEmpty() &&
                eWPEngineCap.isEmpty() &&
                eWPMaxSpeed.isEmpty() &&
                eWPGenNum.isEmpty() &&
                eWPHorsePower.isEmpty() &&
                eWPCost.isEmpty() &&
                eWPMileAge.isEmpty())
            {
                QMessageBox::warning(this, "Предупреждение", "Введите хотя бы один параметр для поиска нужного автомобиля!");
            }
            else
            {
                bool validCarParam =
                                   ValidateQLineEdit(eWPModelName, modelNameRegex) &&
                                   ValidateQLineEdit(eWPCarManuf, latinWRegex) &&
                                   ValidateQLineEdit(eWPEngineCap, floatVRegex) &&
                                   ValidateQLineEdit(eWPMaxSpeed, intVRegex) &&
                                   ValidateQLineEdit(eWPGenNum, intVRegex) &&
                                   ValidateQLineEdit(eWPHorsePower, intVRegex) &&
                                   ValidateQLineEdit(eWPCost, intVRegex) &&
                                   ValidateQLineEdit(eWPMileAge, intVRegex);
                if (validCarParam)
                {
                    //тут запрос на поиск машины
                    bool convCheck;
                     //Заполнение параметров
                    parameters[":1"] = eWPModelName.isEmpty() ? QVariant() : eWPModelName;
                    parameters[":2"] = eWPCarManuf.isEmpty() ? QVariant() : eWPCarManuf;
                    parameters[":3"] = eWPEngineCap.isEmpty() ? QVariant() : QVariant(eWPEngineCap.toFloat(&convCheck));
                    parameters[":4"] = eWPMaxSpeed.isEmpty() ? QVariant() : QVariant(eWPMaxSpeed.toInt(&convCheck));
                    parameters[":5"] = eWPGenNum.isEmpty() ? QVariant() : QVariant(eWPGenNum.toInt(&convCheck));
                    parameters[":6"] = eWPHorsePower.isEmpty() ? QVariant() : QVariant(eWPHorsePower.toInt(&convCheck));
                    parameters[":7"] = eWPCost.isEmpty() ? QVariant() : QVariant(eWPCost.toInt(&convCheck));
                    parameters[":8"] = eWPMileAge.isEmpty() ? QVariant() : QVariant(eWPMileAge.toInt(&convCheck));
                    myConPool->executeQueryAsync("SELECT * FROM course_work.search_cars(:1, :2, :3, :4, :5, :6, :7, :8);", this, SLOT(QHEmWorkPageFC(QSqlQuery)), parameters);

                }
                else
                {
                    QMessageBox::critical(this, "Ошибка", "Введённые данные некорректны, попробуйте осущеcтвить ввод ещё раз!");
                }

            }

        break;

        case 11:
            if (eWPOrderNum.isEmpty())
            {
                 QMessageBox::warning(this, "Предупреждение", "Введите номер заказа!");
            }
            else
            {
                bool validPactParam = ValidateQLineEdit(eWPOrderNum, intVRegex);
                if (validPactParam)
                {
                    parameters[":1"] = eWPOrderNum.toInt();
                    myConPool->executeQueryAsync("SELECT * FROM course_work.search_order(:1);",this, SLOT(QHEmWorkPageFindOr(QSqlQuery)), parameters);
                }
            }
        break;
    }
}

 bool MainWindow::ValidateQLineEdit(const QString text, const QRegularExpression regexp)
{
    if (text.isEmpty())
    {
        return true;
    }
    QRegularExpressionMatch match = regexp.match(text);

    return  match.hasMatch();;
 }

bool MainWindow::ValidateQLEExact(const QString text, const QRegularExpression regexp)
{

    QRegularExpressionMatch match = regexp.match(text);
    if (match.hasMatch())
    {
        qDebug() << text << match.hasMatch();
        return true;
    }
    else
    {
        qDebug() << text << match.hasMatch();
        return false;
    }
}

void MainWindow::QHEmWorkPageFindOr(QSqlQuery result)
{
    emWPModel->setQuery(result);

    emWPModel->setHeaderData(0, Qt::Horizontal, "Номер заказа");
    emWPModel->setHeaderData(1, Qt::Horizontal, "Почта клиента");
    emWPModel->setHeaderData(2, Qt::Horizontal, "Дата \nоформления");
    emWPModel->setHeaderData(3, Qt::Horizontal, "Дата \nполучения");
    emWPModel->setHeaderData(4, Qt::Horizontal, "Статус выдачи");
    emWPModel->setHeaderData(5, Qt::Horizontal, "Товар");
    ResultView->setModel(emWPModel);
    //Выставляем отображение данные в QTreeView
    ResultView->header()->setSectionResizeMode(QHeaderView::Stretch);
    ResultView->header()->setDefaultAlignment(Qt::AlignCenter);
    ResultView->setItemDelegate(new CenteredItemDelegate(ResultView));
    for (int column = 0; column < emWPModel->columnCount(); ++column)
    {
        ResultView->resizeColumnToContents(column);
    }
    parameters.clear();
}

void MainWindow::QHEmWorkPageFC(QSqlQuery result)
{

    emWPModel->setQuery(result);

    emWPModel->setHeaderData(0, Qt::Horizontal, "Название");
    emWPModel->setHeaderData(1, Qt::Horizontal, "Производитель");
    emWPModel->setHeaderData(2, Qt::Horizontal, "ЛС");
    emWPModel->setHeaderData(3, Qt::Horizontal, "Объём \nдвигателя");
    emWPModel->setHeaderData(4, Qt::Horizontal, "Макс.\nскорость");
    emWPModel->setHeaderData(5, Qt::Horizontal, "№ поколения");
    emWPModel->setHeaderData(6, Qt::Horizontal, "Цена");
    emWPModel->setHeaderData(7, Qt::Horizontal, "Пробег");
    ResultView->setModel(emWPModel);
    //Выставляем отображение данные в QTreeView
    ResultView->header()->setSectionResizeMode(QHeaderView::Stretch);
    ResultView->header()->setDefaultAlignment(Qt::AlignCenter);
    ResultView->setItemDelegate(new CenteredItemDelegate(ResultView));
    for (int column = 0; column < emWPModel->columnCount(); ++column)
    {
        ResultView->resizeColumnToContents(column);
    }
    parameters.clear();
}

void MainWindow::QHAuthUserAuth(QSqlQuery result)
{
    if (result.next())
    {
        if (result.value(0).toInt() ==  1)
        {
            setMinimumSize(1400, 900);
            stackedLayout->setCurrentIndex(5);
            myConPool->executeQueryAsync("SELECT * FROM course_work.load_and_refresh_data();", this, SLOT(QHUserLoadData(QSqlQuery)), parameters);
        }
        else
        {
            QMessageBox::critical(this, "Ошибка", "Пользователь с такими данными не был найден. Попробуйте авторизоваться ещё раз.");
        }
    }
    parameters.clear();
}

void MainWindow::QHAuthEmployeeAuth(QSqlQuery result)
{
    if (result.next())
    {
        if (result.value(0).toString() == "Консультант")
        {
            setMinimumSize(1500, 650);
            stackedLayout->setCurrentIndex(4);
        }
        else if (result.value(0).toString() == "Администратор")
        {
            setMinimumSize(1500, 650);
            stackedLayout->setCurrentIndex(7);
        }
        else
        {
            QMessageBox::critical(this, "Ошибка", "Сотрудник не был найден. Попробуйте авторизоваться ещё раз.");
        }
    }
    parameters.clear();
}

void MainWindow::QHRegUser(QSqlQuery result)
{
    if (result.next())
    {
        if (result.value(0) == 0)
        {
            QMessageBox::critical(this, "Ошибка", "Такой пользователь уже существует!");
            randomString.clear();
        }
        else
        {
            SendEmail(regEmail);
            regLastNameLineEdit->clear();
            regFirstNameLineEdit->clear();
            regMiddleNameLineEdit->clear();
            regEmailLineEdit->clear();
            regPasswordLineEdit->clear();
            randomString.clear();
            stackedLayout->setCurrentIndex(0);
        }
    }
    parameters.clear();
}

void MainWindow::QHRecovUserPass(QSqlQuery result)
{
    if (result.next())
    {
        if (result.value(0) == 1)
        {
            SendEmail(forgotPEmail);
            forgotPEmailLEdit->clear();
            forgotPTokLEdit->clear();
            forgotPNewPassLEdit->clear();
            stackedLayout->setCurrentIndex(0);
            randomString.clear();
        }
        else
        {
            QMessageBox::critical(this, "Ошибка",  "Неудалось восстановить пароль. Проверьте корректность введённых данных. За помощью можете обратиться к администратору.");
            randomString.clear();
        }
    }
    parameters.clear();
}

void MainWindow::QHUserLoadData(QSqlQuery result)
{
    userPageModel->setQuery(result);

    userPageModel->setHeaderData(0, Qt::Horizontal, "Название");
    userPageModel->setHeaderData(1, Qt::Horizontal, "Производитель");
    userPageModel->setHeaderData(2, Qt::Horizontal, "ЛС");
    userPageModel->setHeaderData(3, Qt::Horizontal, "Объём \nдвигателя");
    userPageModel->setHeaderData(4, Qt::Horizontal, "Макс.\nскорость");
    userPageModel->setHeaderData(5, Qt::Horizontal, "№ поколения");
    userPageModel->setHeaderData(6, Qt::Horizontal, "Цена");
    userPageModel->setHeaderData(7, Qt::Horizontal, "Пробег");

    userResultView->header()->setSectionResizeMode(QHeaderView::Stretch);
    userResultView->header()->setDefaultAlignment(Qt::AlignCenter);
    userResultView->setItemDelegate(new CenteredItemDelegate(userResultView));

    for (int column = 0; column < emWPModel->columnCount(); ++column)
    {
        ResultView->resizeColumnToContents(column);
    }
}

void MainWindow::QHBacketAddCarItems(QSqlQuery result)
{
    if (result.next())
    {
        if (result.value(0) == 1)
        {
            QMessageBox::information(this, "Уведомление", "Вы успешно оформили заказ. По прибытии с вами свяжется сотрудник автосалона для уточнения деталей.");
        }
        else
        {
            QMessageBox::warning(this, "Предупреждение", "Позиции из вашей корзины были оформлены, пожалуйста пересоберите её!");
        }
    }
}

void MainWindow::QHAdminCarAdd(QSqlQuery result)
{
    if (result.next())
    {
        if (result.value(0) == 1)
        {
            QMessageBox::information(this, "Уведомление", "Машина была успешно добавлена!");
        }
    }
    parameters.clear();
}

void MainWindow::QHAdminEmpDelete(QSqlQuery result)
{
    if (result.next())
    {
        if (result.value(0) == 1)
        {
            QMessageBox::information(this, "Уведомление", "Сотрудник был успешно удалён!");
        }
        else if (result.value(0) == 0)
        {
            QMessageBox::critical(this, "Ошибка", "Сотрудник с выбранными параметрами не существует!");
        }
    }
    parameters.clear();
}

void MainWindow::QHAdminCarDelete(QSqlQuery result)
{
    if (result.next())
    {
        if (result.value(0) == 1)
        {
            QMessageBox::information(this, "Уведомление", "Машина была успешно удалена!");
        }
        else if (result.value(0) == 0)
        {
            QMessageBox::critical(this, "Ошибка", "Машина с выбранными параметрами не существует!");
        }
    }
    parameters.clear();
}

void MainWindow::QHAdminEmpAdd(QSqlQuery result)
{
    if (result.next())
    {
        if (result.value(0) == 1)
        {
            QMessageBox::information(this, "Уведомление", "Сотрудник был успешно добавлен! Его код доступа: " + randomString);
        }
        else if (result.value(0) == 0)
        {
            QMessageBox::critical(this, "Ошибка", "Указанная должность не существует!");
        }
    }
    randomString.clear();
    parameters.clear();
}

void MainWindow::QHAdminJobTAdd(QSqlQuery result)
{
    if (result.next())
    {
        if (result.value(0) == 0)
        {
            QMessageBox::critical(this, "Ошибка", "Указанная должность уже существует!");
        }
        else if (result.value(0) == 1)
        {
            QMessageBox::information(this, "Уведомление", "Должность успешно добавлена!");
        }
    }
}

void MainWindow::QHAdmitJobTDelete(QSqlQuery result)
{
    if (result.next())
    {
        if (result.value(0) == 0)
        {
            QMessageBox::critical(this, "Ошибка", "Должность с такими параметрами не найдена!");
        }
        else if (result.value(0) == 1)
        {
            QMessageBox::information(this, "Уведомление", "Должность успешно удалена!");
        }
    }
}

void MainWindow::ClearBacket()
{
    QStandardItemModel* model = qobject_cast<QStandardItemModel* > (backetResultView->model());
    model->removeRows(0, model->rowCount());
    userBacketData.clear();
}

void MainWindow::SendEmail(const QString& userEmail)
{
    networkManager = new QNetworkAccessManager(this);

    // Получаем конфиденциальные данные
    const auto& config = SecureConfig::getInstance();

    // Создаем JSON объект с данными для отправки
    QJsonObject emailData;
    emailData["service_id"] = config.getEmailServiceId();
    emailData["template_id"] = config.getEmailTemplateId();
    emailData["user_id"] = config.getEmailUserId();
    qDebug() << randomString;
    QJsonObject templateParams;
    templateParams["to_email"] = userEmail;
    templateParams["new_password"] = randomString;
    templateParams["company_name"] = config.getCompanyName();
    emailData["template_params"] = templateParams;

    QJsonDocument jsonDoc(emailData);
    QByteArray jsonData = jsonDoc.toJson();


    // Создаем запрос
    QNetworkRequest request(QUrl("https://api.emailjs.com/api/v1.0/email/send"));
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    request.setRawHeader("origin", "http://localhost");

    // Отправляем POST запрос
    QNetworkReply *reply = networkManager->post(request, jsonData);

    // Обрабатываем ответ
    connect(reply, &QNetworkReply::finished, [=]()
    {
        if (reply->error() == QNetworkReply::NoError)
        {
            QMessageBox::information(this, "Информация", "Письмо c кодом восстановления было отправлено вам на почту.");
        }
        else
        {
            QMessageBox::critical(this, "Ошибка", "Неудалось отправить письмо с кодом восстановления, повторите попытку позже!");
        }
        reply->deleteLater();
    });

    connect(reply, &QNetworkReply::errorOccurred, [=]()
    {
         QMessageBox::critical(this, "Ошибка", "Невозможно отправить письмо c кодом восстановления, проверьте своё подключение к сети!");
    });
}

QString MainWindow::GenerateRandomString()
{
    const QString possibleCharacters("ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789");

    for (int i = 0; i < 6; ++i)
    {
        int index = QRandomGenerator::global()->bounded(possibleCharacters.length());
        QChar nextChar = possibleCharacters.at(index);
        randomString.append(nextChar);
    }

    return randomString;
}

QString MainWindow::EncryptPass(const QString& value)
{
    QByteArray data = QByteArray::fromBase64(value.toLatin1());
    QByteArray decrypted;

    for(int i = 0; i < data.size(); ++i)
    {
        decrypted.append(data[i] ^ key[i % key.size()]);
    }

    return QString::fromUtf8(decrypted);
}

QString MainWindow::DecryptPass(const QString& value)
{
    QByteArray data = QByteArray::fromBase64(value.toLatin1());
    QByteArray decrypted;

    for(int i = 0; i < data.size(); ++i)
    {
        decrypted.append(data[i] ^ key[i % key.size()]);
    }

    return QString::fromUtf8(decrypted);
}

MainWindow::~MainWindow()
{
    delete stackedLayout;
    delete myConPool;
    delete ui;
}

