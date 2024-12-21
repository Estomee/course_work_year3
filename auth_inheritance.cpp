#include "auth_inheritance.h"

//Виджеты страницы авторизации
Login::Login(QWidget *parent) : QLineEdit(parent)
{
    this->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    this->setMaximumWidth(300);
    this->setMinimumWidth(300);
    this->setMinimumHeight(30);
    this->setPlaceholderText("Электронная почта");
}

Password::Password(QWidget *parent): QLineEdit(parent)
{
    this->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    this->setMinimumWidth(300);
    this->setMaximumWidth(300);
    this->setMinimumHeight(30);
    this->setPlaceholderText("Пароль");
    this->setToolTip("Пароль дожен содержать 6 символов и @ или #");
}

Logo::Logo(QWidget* parent, QPixmap& pixmap): QLabel(parent)
{
    this->setPixmap(pixmap);
    this->setMaximumSize(120, 90);
    this->setFixedHeight(90);
    this->setScaledContents(true);
}

Enter::Enter(QWidget* parent): QLabel(parent)
{
    this->setText("Вход");
    this->setObjectName("enterLabel");
    this->setFixedHeight(50);
}

RegLabel::RegLabel (QWidget* parent): QLabel(parent)
{
    this->setText("<a href=\"#\" style=\" color: #000000; font-size: 12px; text-decoration: none; font-family: Century Gothic,CenturyGothic,AppleGothic,sans-serif; \"> Зарегистрироваться </a>");
    this->setCursor(Qt::PointingHandCursor);
    this->setOpenExternalLinks(false);
}

ForgotPassLabel::ForgotPassLabel(QWidget* parent) : QLabel(parent)
{
    this->setText("<a href=\"#\" style=\" color: #000000; font-size: 12px; text-decoration: none;  font-family: Century Gothic,CenturyGothic,AppleGothic,sans-serif;\"> Забыли пароль? </a>");
    this->setCursor(Qt::PointingHandCursor);
    this->setOpenExternalLinks(false);
}

AuthForEmpl::AuthForEmpl(QWidget* parent): QLabel(parent)
{
    this->setText("<a href=\"#\" style=\" color: #000000; font-size: 12px; text-decoration: none;  font-family: Century Gothic,CenturyGothic,AppleGothic,sans-serif;\">Вход для сотрудников</a>");
    this->setCursor(Qt::PointingHandCursor);
    this->setOpenExternalLinks(false);

}
AuthPushButton::AuthPushButton(QWidget* parent): QPushButton(parent)
{
    this->setText("Войти");
    this->setMinimumWidth(160);
    this->setMaximumWidth(110);
    this->setMinimumHeight(30);
    this->setObjectName("generalButton");
}

//Виджеты окна входа для сотрудников
EmMainLabel::EmMainLabel(QWidget* parent): Enter(parent)
{
    this->setText("Авторизация для \n   сотрудников");
    this->setMaximumHeight(150);
}

EmAuthCodeEnter::EmAuthCodeEnter(QWidget* parent): QLineEdit(parent)
{
    this->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    this->setMinimumWidth(300);
    this->setMaximumWidth(300);
    this->setMinimumHeight(30);
    this->setPlaceholderText("Код авторизации");
}

EmEnterButton::EmEnterButton(QWidget* parent): AuthPushButton(parent)
{
    this->setText("Войти");
}

//Виджеты окна регистрации
RegMainLabel::RegMainLabel(QWidget* parent): QLabel(parent)
{
    this->setObjectName("enterLabel");
    this->setFixedHeight(50);
    this->setText("Регистрация");
}

RegEnterButton::RegEnterButton(QWidget* parent): QPushButton(parent)
{
    this->setMinimumWidth(160);
    this->setMaximumWidth(110);
    this->setMinimumHeight(30);
    this->setObjectName("generalButton");
    this->setText("Зарегистрироваться");
}

RegLastNameLineEdit::RegLastNameLineEdit(QWidget* parent): QLineEdit(parent)
{
    this->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    this->setMinimumWidth(300);
    this->setMaximumWidth(300);
    this->setMinimumHeight(30);
    this->setPlaceholderText("Фамилия");
}

RegFirstNameLineEdit::RegFirstNameLineEdit(QWidget* parent):  QLineEdit(parent)
{
    this->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    this->setMinimumWidth(300);
    this->setMaximumWidth(300);
    this->setMinimumHeight(30);
    this->setPlaceholderText("Имя");
}

RegMiddleNameLineEdit::RegMiddleNameLineEdit(QWidget* parent): QLineEdit(parent)
{
    this->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    this->setMinimumWidth(300);
    this->setMaximumWidth(300);
    this->setMinimumHeight(30);
    this->setPlaceholderText("Отчество");
}

RegEmailLineEdit::RegEmailLineEdit(QWidget* parent):  QLineEdit(parent)
{
    this->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    this->setMinimumWidth(300);
    this->setMaximumWidth(300);
    this->setMinimumHeight(30);
    this->setPlaceholderText("Электронная почта");
}

RegPasswordLineEdit::RegPasswordLineEdit(QWidget* parent): Password(parent)
{
    this->setPlaceholderText("Пароль");
}

//Виджеты окна восстановления пароля

ForgotPMainLabel::ForgotPMainLabel(QWidget* parent): RegMainLabel(parent)
{
    this->setText("Восстановить пароль");
}

ForgotPEmailLEdit::ForgotPEmailLEdit(QWidget* parent): Password(parent)
{
    this->setPlaceholderText("Электронная почта");
    this->setToolTip("Введите почту");
}

ForgotPTokLEdit::ForgotPTokLEdit(QWidget* parent): Login(parent)
{
    this->setPlaceholderText("Токен для восстановления пароля");
}

ForgotNewPassLEdit::ForgotNewPassLEdit(QWidget* parent): Password(parent)
{
    this->setPlaceholderText("Новый пароль");
}

ForgotPEnterButton::ForgotPEnterButton(QWidget* parent): AuthPushButton(parent)
{
    this->setText("Выполнить");
}

//Виджеты окна  сотрудников
EmWorkPageMainLabel::EmWorkPageMainLabel(QWidget* parent): RegMainLabel(parent)
{
    this->setText("Сотрудники");
}

EmCarModelNameLE::EmCarModelNameLE(QWidget* parent): EmAuthCodeEnter(parent)
{
    this->setPlaceholderText("Название модели");
}

EmCarManufLE::EmCarManufLE(QWidget* parent): EmAuthCodeEnter(parent)
{
    this->setPlaceholderText("Производитель");
}

EmEngineCapLE::EmEngineCapLE(QWidget* parent): EmAuthCodeEnter(parent)
{
    this->setPlaceholderText("Объём двигателя");
}

EmMaxSpeedLE::EmMaxSpeedLE(QWidget* parent): EmAuthCodeEnter(parent)
{
    this->setPlaceholderText("Максимальная скорость");
}

EmGenNumLE::EmGenNumLE(QWidget* parent): EmAuthCodeEnter(parent)
{
    this->setPlaceholderText("Номер поколения");
}

EmHorsePowLE::EmHorsePowLE(QWidget *parent): EmAuthCodeEnter(parent)
{
    this->setPlaceholderText("ЛС");
}

EmCostLE::EmCostLE(QWidget *parent): EmAuthCodeEnter(parent)
{
    this->setPlaceholderText("Стоимость");
}

EmMileAgeLE::EmMileAgeLE(QWidget *parent): EmAuthCodeEnter(parent)
{
    this->setPlaceholderText("Пробег");
}

EmNumOrderLE::EmNumOrderLE(QWidget *parent): EmAuthCodeEnter(parent)
{
    this->setPlaceholderText("Номер заказа");
}

EmNumPactLE::EmNumPactLE(QWidget *parent): EmAuthCodeEnter(parent)
{
    this->setPlaceholderText("Номер договора");
}

EmAccFindCarB::EmAccFindCarB(QWidget *parent): AuthPushButton(parent)
{
    this->setText("Выполнить");
}

EmPactFindB::EmPactFindB(QWidget *parent): AuthPushButton(parent)
{
    this->setText("Выполнить");
}
//Многофункциональные виджеты
BackButton::BackButton(QWidget* parent): AuthPushButton(parent)
{
    this->setText("Назад");
}
