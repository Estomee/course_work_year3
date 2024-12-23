#include "mainwindow.h"
#include "auth_inheritance.h"
#include "qobjectdefs.h"
#include "ui_mainwindow.h"


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

    // Создаем и настраиваем главный виджет
    centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);
    // Создаем QStackedLayout
    stackedLayout = new QStackedLayout(centralWidget);

    this->AuthPageDraw();      // Страница аутентификации (индекс 0)
    this->EmployeePageDraw();  // Страница сотрудника (индекс 1)
    this->RegistrationPageDraw(); // Страница регистрации (индекс 2)
    this->ForgotPassPageDraw(); //Страницы восстановления пароля (индекс 3)

    stackedLayout->setCurrentIndex(0);

    // myConPool = new ConcreteDbCConnection();
    // // Инициализируем пул соединений
    //  QTimer::singleShot(0, this, [this]() {
    //     myConPool->initializePool();
    //      });
}
//Доделать QTooltip для QLineEdit (типо подсказки для ввода данных, аля шаблон для пароля)
void MainWindow::QueryHandler(QSqlQuery result)
{
    qDebug() << "Query handler called!";
    if (result.isActive()) {
        while (result.next()) {
            QString username = result.value("username").toString();
            QString password = result.value("password").toString();
            qDebug() << "Username:" << username << "Password:" << password;
        }
    } else {
        qDebug() << "Query error:" << result.lastError().text();
    }
}

void MainWindow::AuthPageDraw()
{
    // Создаем виджет для страницы авторизации
    QWidget* authPage = new QWidget(this);
    authPage->setFocusPolicy(Qt::StrongFocus);
    loginLineEdit = new Login(this);
    passwordLineEdit = new Password(this);
    regLabel = new RegLabel(this);
    authForEmpl = new AuthForEmpl(this);
    enter = new Enter(this);
    forgotPassLabel = new ForgotPassLabel(this);
    authButton = new AuthPushButton(this);
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
    setMinimumSize(800, 600);
    QWidget* employeeAuthPage = new QWidget(this);
    employeeAuthPage->setFocusPolicy(Qt::StrongFocus);
    empBackButton = new BackButton(this);
    emMainLayout = new QVBoxLayout(employeeAuthPage);
    emMainLabel = new EmMainLabel(this);
    emAuthCodeLineEdit = new EmAuthCodeEnter(this);
    emEnterButton = new EmEnterButton(this);

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
    setMinimumSize(800, 600);
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
    setMinimumSize(800, 600);
    QWidget* forgotPassPage = new QWidget(this);
    forgotPassPage->setFocusPolicy(Qt::StrongFocus);
    QPixmap pixmap(":/images/e");
    forgotPLayout = new QVBoxLayout(forgotPassPage);
    QPushButton* forgotPBackButton = new BackButton(this);
    Logo* forgotPPageLogo = new Logo(forgotPassPage, pixmap);
    forgotPMainLabel = new ForgotPMainLabel(this);
    forgotPEmailLEdit = new ForgotPEmailLEdit(this);
    forgotPTokLEdit = new ForgotPTokLEdit(this);
    forgotPNewPassLEdit =  new ForgotNewPassLEdit(this);
    forgotPEnterButton = new ForgotPEnterButton(this);
    forgotPSignalMapper = new QSignalMapper(this);

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

    stackedLayout->addWidget(forgotPassPage);

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
}

void MainWindow::EmployeeWorkPageDraw()
{
    setMinimumSize(800, 600);
    QWidget* EmployeePage = new QWidget(this);
    EmployeePage->setFocusPolicy(Qt::StrongFocus);
    QPixmap pixmap(":/images/e");
    emWorkPageLayout =  new QVBoxLayout(EmployeePage);
    Logo* emPageLogo = new Logo(EmployeePage, pixmap);

    emWorkPageMainLabel = new EmWorkPageMainLabel(EmployeePage);
    emCarModelNameLE = new EmCarModelNameLE(EmployeePage) ;
    emCarManufLE = new EmCarManufLE(EmployeePage);
    emEngineCapLE = new EmEngineCapLE(EmployeePage);
    emMaxSpeedLE = new EmMaxSpeedLE(EmployeePage);
    emGenNumLE = new EmGenNumLE(EmployeePage);
    emHorsePowLE = new EmHorsePowLE(EmployeePage);
    emCostLE= new EmCostLE(EmployeePage);
    emMileAgeLE = new EmMileAgeLE(EmployeePage);
    emNumOrderLE = new EmNumOrderLE(EmployeePage);
    emNumPactLE = new EmNumPactLE(EmployeePage);
    emAccFindCarB = new EmAccFindCarB(EmployeePage);
    emPactFindB = new  EmPactFindB (EmployeePage);

    QSignalMapper* emWorkPageSM = new QSignalMapper(EmployeePage);
    emWorkPageSM->setMapping(emCarModelNameLE , 1);
    emWorkPageSM->setMapping(emCarManufLE, 2);
    emWorkPageSM->setMapping(emEngineCapLE , 3);
    emWorkPageSM->setMapping(emMaxSpeedLE, 4);
    emWorkPageSM->setMapping(emGenNumLE, 5);
    emWorkPageSM->setMapping(emHorsePowLE, 6);
    emWorkPageSM->setMapping(emCostLE, 7);
    emWorkPageSM->setMapping(emMileAgeLE, 8);
    emWorkPageSM->setMapping(emNumOrderLE, 9);
    emWorkPageSM->setMapping(emNumPactLE, 10);
    emWorkPageSM->setMapping(emAccFindCarB, 11);
    emWorkPageSM->setMapping(emPactFindB, 12);

    connect(emCarModelNameLE, &QLineEdit::editingFinished, emWorkPageSM, QOverload<>::of(&QSignalMapper::map));
    connect(emCarManufLE, &QLineEdit::editingFinished, emWorkPageSM, QOverload<>::of(&QSignalMapper::map));
    connect(emEngineCapLE, &QLineEdit::editingFinished, emWorkPageSM, QOverload<>::of(&QSignalMapper::map));
    connect(emMaxSpeedLE, &QLineEdit::editingFinished, emWorkPageSM, QOverload<>::of(&QSignalMapper::map));
    connect(emGenNumLE, &QLineEdit::editingFinished, emWorkPageSM, QOverload<>::of(&QSignalMapper::map));
    connect(emHorsePowLE, &QLineEdit::editingFinished, emWorkPageSM, QOverload<>::of(&QSignalMapper::map));
    connect(emCostLE, &QLineEdit::editingFinished, emWorkPageSM, QOverload<>::of(&QSignalMapper::map));
    connect(emMileAgeLE, &QLineEdit::editingFinished, emWorkPageSM, QOverload<>::of(&QSignalMapper::map));
    connect(emNumPactLE, &QLineEdit::editingFinished, emWorkPageSM, QOverload<>::of(&QSignalMapper::map));
    connect(emPactFindB, &QPushButton::clicked, emWorkPageSM, QOverload<>::of(&QSignalMapper::map));






    emWorkPageLayout->addWidget(emPageLogo, 0, Qt::AlignCenter);
    forgotPLayout->addSpacing(45);
    emWorkPageLayout->addWidget(emWorkPageMainLabel, 0, Qt::AlignCenter);
    forgotPLayout->addSpacing(75);
    emWorkPageLayout->addWidget(emCarModelNameLE, 0, Qt::AlignLeft);
    forgotPLayout->addSpacing(5);
    emWorkPageLayout->addWidget(emEngineCapLE, 0, Qt::AlignLeft);
    forgotPLayout->addSpacing(5);
    emWorkPageLayout->addWidget(emMaxSpeedLE, 0, Qt::AlignLeft);
    forgotPLayout->addSpacing(5);
    emWorkPageLayout->addWidget(emGenNumLE, 0, Qt::AlignLeft);
    forgotPLayout->addSpacing(5);
    emWorkPageLayout->addWidget(emHorsePowLE, 0, Qt::AlignLeft);
    forgotPLayout->addSpacing(5);

    forgotPLayout->addSpacing(5);

    forgotPLayout->addSpacing(5);

    forgotPLayout->addSpacing(5);

    stackedLayout->addWidget(EmployeePage);
}

void MainWindow::RegPHandleItems(const int id)
{
    QRegularExpressionMatch lnameMatch;
    QRegularExpressionMatch fnameMatch;
    QRegularExpressionMatch mnameMatch;
    QRegularExpressionMatch emailMatch;
    QRegularExpressionMatch passwordMatch;
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
                lnameMatch = lfmRegex.match(regLastName);
                fnameMatch = lfmRegex.match(regFirstName);
                mnameMatch = lfmRegex.match(regMiddleName);
                emailMatch = emailRegex.match(regEmail);
                passwordMatch = passwordRegex.match(regPassword);
                if (lnameMatch.hasMatch() &&
                    fnameMatch.hasMatch() &&
                    mnameMatch.hasMatch() &&
                    emailMatch.hasMatch() &&
                    passwordMatch.hasMatch())
                {
                    //Тут запрос
                }
                else
                {
                    QMessageBox::warning(this, "Предупреждение", "Проверьте корректность введённые данных!");
                }
            }
            else
            {
                QMessageBox::warning(this, "Предупреждение", "Одно или несколько полей ввода пусты!");
            }
        break;

        case 7: //Кнопка назад
            stackedLayout->setCurrentIndex(0);
        break;
    }
}

void MainWindow::AuthPHandleItems(const int id)
{
    QRegularExpressionMatch matchLogin;
    QRegularExpressionMatch matchPassword;
    switch(id)
    {
    case 1: //Тут нажатие на кнопку авторизации. Отправка запроса к базе данных
        if (!loginStr.isEmpty() && !passwordStr.isEmpty())
        {
            matchPassword = passwordRegex.match(passwordStr);
            matchLogin = emailRegex.match(loginStr);
            if (matchLogin.hasMatch() && matchPassword.hasMatch())
            {
                //Тут выполняем запрос
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

    case 3:     //Ввода пароля
        passwordStr = passwordLineEdit->text();
    break;

    case 4:     //Нажатие на поле забыли пароль
        stackedLayout->setCurrentIndex(3);
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
    QRegularExpressionMatch match;
    switch(id)
    {
    case 1:
        authCode = emAuthCodeLineEdit->text();
        break;

    case 2:
        if (!authCode.isEmpty())
        {
            match = authCodeRegex.match(authCode);
            if (match.hasMatch())
            {
                //тут запрос на авторизацию сотрудника
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
        stackedLayout->setCurrentIndex(0);
        break;
    }
}

void MainWindow::ForgotPassPHandleItems(const int id)
{
    QRegularExpressionMatch emailMatch;
    QRegularExpressionMatch newPasswordMatch;
    QRegularExpressionMatch recTokenMatch;

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
                emailMatch = emailRegex.match(forgotPEmail);
                newPasswordMatch = passwordRegex.match(forgotPNewPassword);
                recTokenMatch = authCodeRegex.match(forgotPRecToken);

                if (emailMatch.hasMatch() && newPasswordMatch.hasMatch() && recTokenMatch.hasMatch())
                {
                    //Тут запрос
                }
                else
                {
                    QMessageBox::warning(this, "Предупреждение", "Проверьте правильность введённых данных!");
                }
            }
            else
            {
                QMessageBox::warning(this, "Предупреждение", "Одно или несколько полей для ввода пусты!");
            }
        break;

        case 5:
            stackedLayout->setCurrentIndex(0);
        break;
    }
}

MainWindow::~MainWindow()
{
    delete stackedLayout;
    delete myConPool;
    delete ui;
}
