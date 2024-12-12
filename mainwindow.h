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
#include "auth_inheritance.h"
#include "database.h"

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
        QVBoxLayout* forgotPLayout;
        QLabel* forgotPMainLabel;
        QLineEdit* forgotPEmailLEdit;
        QLineEdit* forgotPTokLEdit;
        QLineEdit* forgotPNewPassLEdit;
        QPushButton* forgotPEnterButton;
        QSignalMapper* forgotPSignalMapper;

        QString forgotPEmail;
        QString forgotPRecToken;
        QString forgotPNewPassword;

        //Методы для отрисовки страниц
        void AuthPageDraw();
        void EmployeePageDraw();
        void RegistrationPageDraw();
        void ForgotPassPageDraw();

        //Регулярные выражения для обработки данных
        QRegularExpression emailRegex{"\b[A-Za-z0-9]+@[A-Za-z0-9]+\.[A-Za-z]{2,}$"};
        QRegularExpression passwordRegex{"\b[A-Za-z0-9@#\"{6,}"};
        QRegularExpression lfmRegex {"\b[A-ZА-Я]{1}+[a-zа-я]"};
        QRegularExpression authCodeRegex{"\bA-Za-z0-9{6}"};

    private slots:
        void AuthPHandleItems(const int id); //Handler для главной страницы
        void EmployeePHandleItems(const int id); //Handler для страницы с сотрудниками
        void RegPHandleItems(const int id); //Handler для страницы с регистрацией
        void ForgotPassPHandleItems(const int id);
        void QueryHandler(QSqlQuery result);

};
#endif // MAINWINDOW_H
