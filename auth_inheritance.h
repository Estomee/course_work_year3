#ifndef AUTH_INHERITANCE_H
#define AUTH_INHERITANCE_H

#include <QPushButton>
#include <QLabel>
#include <QLineEdit>
#include <QKeyEvent>

//Виджеты приветсвенного окна
class Login: public QLineEdit
{
    public:
        explicit Login(QWidget *parent);
};

class Password: public QLineEdit
{
    public:
        explicit Password(QWidget *parent);

};

class AuthForEmpl:public QLabel
{
    public:
        explicit AuthForEmpl(QWidget* parent);
};

class Enter: public QLabel
{
    public:
    explicit Enter(QWidget* parent);
};

class RegLabel: public QLabel
{
    public:
        explicit RegLabel(QWidget* parent);

};

class Logo: public QLabel
{
    public:
        explicit Logo(QWidget* parent, QPixmap& pixmap);
};

class ForgotPassLabel: public QLabel
{
    public:
        explicit ForgotPassLabel(QWidget* parent);
};

class AuthPushButton: public QPushButton
{
    public:
        explicit AuthPushButton(QWidget* parent);
};

//Виджеты окна входа для сотрудников

class EmMainLabel: public Enter
{
    public:
        explicit EmMainLabel(QWidget* parent);
};

class EmAuthCodeEnter: public QLineEdit
{
    public:
        explicit EmAuthCodeEnter(QWidget* parent);
};

class EmEnterButton: public AuthPushButton
{
public:
    explicit EmEnterButton(QWidget* parent);
};

//Виджеты окна регистрации
class RegMainLabel: public   QLabel
{
    public:
        explicit RegMainLabel(QWidget* parent);
};

class RegEnterButton: public QPushButton
{
    public:
        RegEnterButton(QWidget* parent);
};

class  RegLastNameLineEdit: public QLineEdit
{
    public:
        explicit RegLastNameLineEdit(QWidget* parent);
};

class RegFirstNameLineEdit: public QLineEdit
{
    public:
        explicit RegFirstNameLineEdit(QWidget* parent);
};

class RegMiddleNameLineEdit: public QLineEdit
{
    public:
        explicit RegMiddleNameLineEdit(QWidget* parent);
};

class RegEmailLineEdit: public QLineEdit
{
    public:
        explicit RegEmailLineEdit(QWidget* parent);
};

class RegPasswordLineEdit: public Password
{
    public:
        explicit RegPasswordLineEdit(QWidget* parent);
};
//Виджеты окна восстановления пароля

class ForgotPMainLabel: public RegMainLabel
{
    public:
        explicit ForgotPMainLabel(QWidget* parent);
};

class ForgotPEmailLEdit: public Password
{
    public:
        explicit ForgotPEmailLEdit(QWidget* parent);
};

class ForgotPTokLEdit: public Login
{
    public:
        explicit ForgotPTokLEdit(QWidget* parent);
};

class ForgotNewPassLEdit: public Password
{
    public:
        explicit ForgotNewPassLEdit(QWidget* parent);
};

class ForgotPEnterButton: public AuthPushButton
{
    public:
        explicit ForgotPEnterButton(QWidget* parent);
};

//Виджеты окна  сотрудников

class EmWorkPageMainLabel: public RegMainLabel
{
    public:
        explicit EmWorkPageMainLabel(QWidget* parent);
};

class EmCarModelNameLE: public EmAuthCodeEnter
{
    public:
        explicit EmCarModelNameLE(QWidget* parent);
};

class EmCarManufLE: public EmAuthCodeEnter
{
    public:
        explicit EmCarManufLE(QWidget* parent);
};

class EmEngineCapLE: public EmAuthCodeEnter
{
    public:
        explicit EmEngineCapLE(QWidget* parent);
};

class EmMaxSpeedLE: public EmAuthCodeEnter
{
    public:
        explicit EmMaxSpeedLE(QWidget* parent);
};

class EmGenNumLE: public EmAuthCodeEnter
{
    public:
        explicit EmGenNumLE(QWidget* parent);
};

class EmHorsePowLE: public EmAuthCodeEnter
{
    public:
        explicit EmHorsePowLE(QWidget* parent);
};

class EmCostLE: public EmAuthCodeEnter
{
    public:
        explicit EmCostLE(QWidget* parent);
};

class EmMileAgeLE: public EmAuthCodeEnter
{
    public:
        explicit EmMileAgeLE(QWidget* parent);
};

class EmNumOrderLE: public EmAuthCodeEnter
{
    public:
        explicit EmNumOrderLE(QWidget* parent);
};

class EmNumPactLE: public EmAuthCodeEnter
{
    public:
        explicit EmNumPactLE(QWidget* parent);
};

class EmAccFindCarB: public AuthPushButton
{
    public:
        explicit EmAccFindCarB(QWidget* parent);
};

class EmPactFindB: public AuthPushButton
{
    public:
        explicit EmPactFindB(QWidget* parent);
};

//Многофункциональные виджеты
class BackButton: public AuthPushButton
{
    public:
        explicit BackButton(QWidget* parent);
};
#endif // AUTH_INHERITANCE_H
