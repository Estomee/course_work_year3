#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLineEdit>
#include <QSizePolicy>
#include <QVBoxLayout>
#include <QPushButton>
#include <QLabel>
#include <QSignalMapper>
#include <QMessageBox>
#include <QTimer>
#include <QPixmap>
#include <QApplication>
#include <QStackedLayout>
#include <QGridLayout>
#include <QRegularExpression>
#include <QTreeView>
#include <QSqlQueryModel>
#include <QSqlRecord>
#include <QHeaderView>
#include <QRandomGenerator>
#include "database.h"
#include "secureconfig.h"
#include <QSortFilterProxyModel>
#include <QDesktopServices>
#include <QUrl>
#include <QStandardItemModel>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QJsonDocument>
#include <QJsonObject>
#include <QDateTime>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

    public:
        MainWindow(QWidget *parent = nullptr);
        ~MainWindow();

    private:
        //Виджеты и обработка данных для приветсвенного окна
        Ui::MainWindow *ui;
        QLineEdit* loginLineEdit;
        QLineEdit* passwordLineEdit;
        QWidget *centralWidget;
        QLabel* regLabel;
        QLabel* forgotPassLabel;
        QLabel* authForEmpl;
        QLabel* logo;
        QLabel* enter;
        QPushButton* authButton;
        QGridLayout* mainWLayout;
        QVBoxLayout* logPassEditLayout;
        QVBoxLayout* forgotPassRegLayOut;
        QSignalMapper* signalMapperMainP;
        QString loginStr;
        QString passwordStr;

        ConcreteDbCConnection* myConPool;
        QStackedLayout* stackedLayout;
        QVariantMap parameters;
        QNetworkAccessManager* networkManager;

        //Виджеты и обработка данных для окна входа для сотрудников
        QVBoxLayout* emMainLayout;
        QLabel* emMainLabel;
        QLineEdit* emAuthCodeLineEdit;
        QPushButton* emEnterButton;
        QSignalMapper* signalMapperEmP;
        QString authCode;
        QPushButton* empBackButton;

        //Виджеты и обработка данных для окна регистрации

        QVBoxLayout* regMainLayout;
        QLineEdit* regLastNameLineEdit;
        QLineEdit* regFirstNameLineEdit;
        QLineEdit* regMiddleNameLineEdit;
        QLineEdit* regEmailLineEdit;
        QLineEdit* regPasswordLineEdit;
        QLabel* regMainLabel;
        QPushButton* regEnterButton;
        QSignalMapper* signalMapperReg;
        QPushButton* regBackButton;

        QString regLastName;
        QString regFirstName;
        QString regMiddleName;
        QString regEmail;
        QString regPassword;

        //Виджеты и обработка данных для окна восстановления пароля
        QLabel* forgotPMainLabel;
        QLineEdit* forgotPEmailLEdit;
        QLineEdit* forgotPTokLEdit;
        QLineEdit* forgotPNewPassLEdit;
        QPushButton* forgotPEnterButton;
        QSignalMapper* forgotPSignalMapper;

        QString forgotPEmail;
        QString forgotPRecToken;
        QString forgotPNewPassword;

        //Виджеты и обработка данных для рабочего окна сотрудников

        QLabel* emWorkPageMainLabel;
        QLineEdit* emCarModelNameLE;
        QLineEdit* emCarManufLE;
        QLineEdit* emEngineCapLE;
        QLineEdit* emMaxSpeedLE;
        QLineEdit* emGenNumLE;
        QLineEdit* emHorsePowLE;
        QLineEdit* emCostLE;
        QLineEdit* emMileAgeLE;
        QLineEdit* emNumOrderLE;
        QPushButton* emAccFindCarB;
        QPushButton*  emPactFindB;
        QTreeView* ResultView;
        QSqlQueryModel* emWPModel;

        QString eWPModelName;
        QString eWPCarManuf;
        QString eWPEngineCap;
        QString eWPMaxSpeed;
        QString eWPGenNum;
        QString eWPHorsePower;
        QString eWPCost;
        QString eWPMileAge;
        QString eWPOrderNum;
        QString eWPPactNum;

        //Виджеты и обработка данных для окна пользователя
        QLineEdit* userCarSearchLE;
        QTreeView* userResultView;
        QHeaderView* header;
        QSqlQueryModel* userWPModel;
        QPushButton* userAddShopBPB;
        QPushButton* userRefreshResultView;
        QPushButton* userToBacketPB;
        QSqlQueryModel* userPageModel;
        QSortFilterProxyModel* userProxyModel;
        QModelIndexList userViewIndexList;

        //Виджеты и обработка данных для окна корзины
        QTreeView* backetResultView;
        QPushButton* backetPlaceOfferPB;
        QPushButton* backetClearPB;
        QPushButton* backetBackPB;
        QLabel* backetMainLabel;
        QStandardItemModel* userBacketModel;
        QMap<int, QList<QStandardItem*>> userBacketData;
        QModelIndexList backetOrderedCarsIL;
        QList <QList<QVariant>> backetDataForOrder;

        //Виджеты и обработка данных для окна администратора
        QLabel* aMainLabel;

        QLineEdit* aModelNameLE;
        QLineEdit* aManufNameLE;
        QLineEdit* aManufCountryLE;
        QLineEdit* aEngineCapLE;
        QLineEdit* aMaxSpeedLE;
        QLineEdit* aGenNumLE;
        QLineEdit* aHorsePowerLE;
        QLineEdit* aCarCostLE;
        QLineEdit* aMileAgeLE;
        QPushButton* aAccompCarPB;
        QCheckBox* aCarAddCB;
        QCheckBox* aCarDeleteCB;

        QLineEdit* aJobTitleLE;
        QLineEdit* aPasspDataLE;
        QLineEdit* aBirthDateLE;
        QLineEdit* aLastNameLE;
        QLineEdit* aFirstNameLE;
        QLineEdit* aMiddleNameLE;
        QPushButton* aAccompEmplPB;
        QCheckBox* aEmplAddCB;
        QCheckBox* aEmplDeleteCB;

        QLineEdit* aJobTitleNameLE;
        QLineEdit* aJobSalaryLE;
        QPushButton* aJobAccompPB;
        QCheckBox* aJobAddCB;
        QCheckBox* aJobDeleteCB;

        QString aModelName;
        QString aManufName;
        QString aManufCountry;
        QString aEngineCap;
        QString aMaxSpeed;
        QString aGenNum;
        QString aHorseNum;
        QString aCarCost;
        QString aCarMileAge;
        int aCarStateAddCB;
        int aCarStateDeleteCB;

        QString aJobTitle;
        QString aPasspData;
        QString aBirthDate;
        QString aLastName;
        QString aMiddleName;
        QString aFirstName;
        int aEmplStateAddCB;
        int aEmpStateDeleteCB;

        QString aJobTitleName;
        QString aJobSalary;
        int aJobAddStateCB;
        int aJobDeleteStateCB;

        //Добавление выбранных записей в корзину
        void UserAddItemsBacket();
        //Обработка данных для формирования запроса для оформления заказа
        void BacketItemsParse();
        //Формирование строки для запроса БД
        QString NestedListToCsvString(const QList<QList<QVariant>>& nestedList);
        //Очистка корзины от записей
        void ClearBacket();

        //Методы для отрисовки страниц
        void AuthPageDraw();
        void EmployeePageDraw();
        void RegistrationPageDraw();
        void ForgotPassPageDraw();
        void EmployeeWorkPageDraw();
        void UserPageDraw();
        void BacketPageDraw();
        void AdminPageDraw();

        //Обработка данных
        bool ValidateQLineEdit(const QString text, const QRegularExpression regexp);
        bool ValidateQLEExact(const QString text, const QRegularExpression regexp);
        //Генерация кода для сотрудников, кода восстановления пароля и т.д
        QString GenerateRandomString();
        QString randomString;
        //Отправка письма
        void SendEmail(const QString& userEmail);
        //Хэширование пароля
        const QByteArray key = QByteArray::fromHex("i h4t3 pr0gr4ming.");
        QString EncryptPass(const QString& value);
        QString DecryptPass(const QString& value);


        //Регулярные выражения для обработки данных
        QRegularExpression emailRegex{"^[A-Za-z][A-Za-z0-9_.]*@[A-Za-z0-9]+\\.[A-Za-z]{2,}$"};
        QRegularExpression passwordRegex{"^(?=.*[@#])[A-Za-z0-9@#]{1,8}$"};
        QRegularExpression lfmRegex {"^[А-ЯЁ][а-яё]{1,19}$"};
        QRegularExpression authCodeRegex{"^[A-Za-z0-9]{6}$"};
        QRegularExpression modelNameRegex{"^[A-Za-z0-9]{1,10}$"};

        QRegularExpression latinWRegex {"^[A-Za-z]{1,20}$"};
        QRegularExpression intVRegex {"^[1-9][0-9]{0,10}$"};
        QRegularExpression floatVRegex{"^[0-9]{1,3}(\\.[0-9]{1})?$"};

        QRegularExpression dateARegex{"^\\d{4}-(0[1-9]|1[0-2])-(0[1-9]|[12][0-9]|3[01])$"};

    private slots:
        void AuthPHandleItems(const int id); //Handler для главной страницы
        void EmployeePHandleItems(const int id); //Handler для страницы с сотрудниками
        void RegPHandleItems(const int id); //Handler для страницы с регистрацией
        void ForgotPassPHandleItems(const int id); //Handler для страницы с восстановлением пароля
        void EmployeeWorkPageHandleItems(const int id); //Hanlder для рабочей страницы сотрудников
        void UserPageHandleItems(const int id); //Handler для страницы пользователей
        void QHEmWorkPageFC(QSqlQuery result); //Handler для обработки запроса по поиску машины
        void QHAuthUserAuth (QSqlQuery result); //Handler для обработки запроса на авторизацию клиента
        void QHAuthEmployeeAuth(QSqlQuery result); //Handler для обработки запроса на вход сотрудника
        void QHRegUser(QSqlQuery result); //Handler для обработки запроса на регистрацию пользователя
        void QHRecovUserPass(QSqlQuery result); //Handler для обработки запроса на восстановление пароля
        void QHUserLoadData(QSqlQuery result); //Handler для обработки запроса на загрузку данных для отображения
        void UserResultViewCD(const QItemSelection& selected, const QItemSelection& deselected); //Handler для обработки выбранных позиций в окне пользователя
        void BacketPageHandleItems(const int id); //Handler для страницы корзины
        void QHBacketAddCarItems(QSqlQuery result); //Handler для обработки запроса по добавлению позиций заказа
        void QHEmWorkPageFindOr(QSqlQuery result); //Handler для обработки запроса по поиску заказа
        void AdminPageHandleItems(const int id); //Handler для обработки виджетов страницы администратора
        void QHAdminCarAdd(QSqlQuery result); //Handler для обратбоки добавления машин
        void QHAdminCarDelete(QSqlQuery result); //Handler для обратбоки удаления машин
        void QHAdminEmpAdd(QSqlQuery result); //Handler для обработки добавления сотрудников
        void QHAdminEmpDelete(QSqlQuery result);//Handler для обработки удаления сотрудников
        void QHAdminJobTAdd(QSqlQuery result); //Handler для обработки добавления должности
        void QHAdmitJobTDelete(QSqlQuery result);//Handler для обработки удаления должности
};
#endif // MAINWINDOW_H
