#include "auth_inheritance.h"


//Виджеты страницы авторизации
Login::Login(QWidget *parent) : QLineEdit(parent)
{
    this->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    this->setMinimumWidth(300);
    this->setMinimumHeight(30);
    this->setPlaceholderText("Электронная почта");
}

Password::Password(QWidget *parent): QLineEdit(parent)
{
    this->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    this->setMinimumWidth(300);
    this->setMinimumHeight(30);
    this->setPlaceholderText("Пароль");
    this->setToolTip("Пароль дожен содержать до 8 символов включая @ или #");
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
    this->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
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
    this->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    this->setText("Войти");;
    this->setMinimumWidth(150);
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
    this->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    this->setMinimumWidth(300);
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
    this->setMinimumHeight(30);
    this->setObjectName("generalButton");
    this->setText("Зарегистрироваться");
}

RegLastNameLineEdit::RegLastNameLineEdit(QWidget* parent): Login(parent)
{
    this->setPlaceholderText("Фамилия");
}

RegFirstNameLineEdit::RegFirstNameLineEdit(QWidget* parent): Login(parent)
{
    this->setPlaceholderText("Имя");
}

RegMiddleNameLineEdit::RegMiddleNameLineEdit(QWidget* parent): Login(parent)
{
    this->setPlaceholderText("Отчество");
}

RegEmailLineEdit::RegEmailLineEdit(QWidget* parent):  Login(parent)
{
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
    this->setPlaceholderText("Макс. скорость");
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

EmAccFindCarB::EmAccFindCarB(QWidget *parent): AuthPushButton(parent)
{
    this->setText("Выполнить");
}

EmPactFindB::EmPactFindB(QWidget *parent): AuthPushButton(parent)
{
    this->setText("Выполнить");
}

ResultTreeView::ResultTreeView(QWidget* parent): QTreeView(parent)
{
    this->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    this->setMinimumHeight(400);
    this->setMinimumWidth(650);
}
void ResultTreeView::mousePressEvent(QMouseEvent* event)
{
    if (event->button() == Qt::LeftButton)
    {
        QModelIndex index = indexAt(event->pos());
        if (!index.isValid())
        {
            clearSelection();
            setCurrentIndex(QModelIndex());
        }
    }
    QTreeView::mousePressEvent(event);
}

//Виджеты окна пользователя
UserCarSearchLE::UserCarSearchLE(QWidget* parent): EmAuthCodeEnter(parent)
{
    this->setPlaceholderText("Поиск по названию");
    this->setMinimumWidth(400);
}

UserResultView::UserResultView(QWidget* parent): ResultTreeView(parent)
{
    this->setMinimumHeight(600);
    this->setMinimumWidth(400);
    this->setSelectionMode(QAbstractItemView::ExtendedSelection);
}

void UserResultView::mousePressEvent(QMouseEvent* event) //Убираем выделение
{
    if (event->button() == Qt::LeftButton)
    {
        QModelIndex index = indexAt(event->pos());
        if (!index.isValid())
        {
            clearSelection();
            setCurrentIndex(QModelIndex());
        }
    }
    QTreeView::mousePressEvent(event);
}

UserToBacketPB::UserToBacketPB(QWidget* parent): AuthPushButton(parent)
{
    this->setText("Корзина");
}

UserAddShopBPB::UserAddShopBPB(QWidget* parent): AuthPushButton(parent)
{
    this->setText("Добавить в корзину");
}

UserRefreshResultView::UserRefreshResultView(QWidget* parent): AuthPushButton(parent)
{
    this->setText("Обновить таблицу");
}

//Виджеты окна корзины
BacketResultView::BacketResultView(QWidget* parent):  ResultTreeView(parent)
{
    this->setMinimumHeight(600);
    this->setMinimumWidth(400);
}

void BacketResultView::mousePressEvent(QMouseEvent* event) //Убираем выделение
{
    if (event->button() == Qt::LeftButton)
    {
        QModelIndex index = indexAt(event->pos());
        if (!index.isValid())
        {
            clearSelection();
            setCurrentIndex(QModelIndex());
        }
    }
    QTreeView::mousePressEvent(event);
}

BacketPlaceOfferPB::BacketPlaceOfferPB(QWidget* parent): AuthPushButton(parent)
{
    this->setText("Оформить заказ");
}

BacketClearPB::BacketClearPB(QWidget* parent): AuthPushButton(parent)
{
    this->setText("Очистить корзину");
}

BacketMainLabel::BacketMainLabel(QWidget* parent): Enter(parent)
{
    this->setText("Корзина");
}

//Виджеты окна администратора

AModelNameLE::AModelNameLE(QWidget* parent): EmAuthCodeEnter(parent)
{
    this->setPlaceholderText("Название модели");
}

AManufNameLE::AManufNameLE(QWidget* parent): EmAuthCodeEnter(parent)
{
    this->setPlaceholderText("Производитель");
}

AManufCountryLE::AManufCountryLE(QWidget* parent): EmAuthCodeEnter(parent)
{
    this->setPlaceholderText("Страна производителя");
}

AEngineCapLE::AEngineCapLE(QWidget* parent): EmAuthCodeEnter(parent)
{
    this->setPlaceholderText("Объём двигаетля");
}

AGenNumLE::AGenNumLE(QWidget* parent): EmAuthCodeEnter(parent)
{
    this->setPlaceholderText("Номер поколения");
}

AHorsePowerLE::AHorsePowerLE(QWidget* parent): EmAuthCodeEnter(parent)
{
    this->setPlaceholderText("ЛС");
}

ACarCostLE::ACarCostLE(QWidget* parent): EmAuthCodeEnter(parent)
{
    this->setPlaceholderText("Стоимость");
}

AMaxSpeedLE::AMaxSpeedLE(QWidget* parent): EmAuthCodeEnter(parent)
{
    this->setPlaceholderText("Макс. скорость");
}

AMileAgeLE::AMileAgeLE(QWidget* parent): EmAuthCodeEnter(parent)
{
    this->setPlaceholderText("Пробег");
}

AAccompCarPB::AAccompCarPB(QWidget* parent): AuthPushButton(parent)
{
    this->setText("Выполнить");
}

ACarAddCB::ACarAddCB(QWidget* parent): QCheckBox(parent)
{
    this->setText("Добавить");
}

ACarDeleteCB::ACarDeleteCB(QWidget* parent): ACarAddCB(parent)
{
    this->setText("Удалить");
}

AJobTitleLE::AJobTitleLE(QWidget* parent): EmAuthCodeEnter(parent)
{
    this->setPlaceholderText("Должность");
}

APasspDataLE::APasspDataLE(QWidget* parent): EmAuthCodeEnter(parent)
{
    this->setPlaceholderText("Паспортные данные (серия номер)");
}

ABirthDateLE::ABirthDateLE(QWidget* parent): EmAuthCodeEnter(parent)
{
    this->setPlaceholderText("Дата рождения");
}

ALastNameLE::ALastNameLE(QWidget* parent): EmAuthCodeEnter(parent)
{
    this->setPlaceholderText("Фамилия");
}

AFirstNameLE::AFirstNameLE(QWidget* parent): EmAuthCodeEnter(parent)
{
    this->setPlaceholderText("Имя");
}

AMiddleNameLE::AMiddleNameLE(QWidget* parent): EmAuthCodeEnter(parent)
{
    this->setPlaceholderText("Отчество");
}

AAccompEmplPB::AAccompEmplPB(QWidget* parent): AuthPushButton(parent)
{
    this->setText("Выполнить");
}

AEmplDeleteCB::AEmplDeleteCB(QWidget* parent): ACarAddCB(parent)
{
    this->setText("Удалить");
}

AEmplAddCB::AEmplAddCB(QWidget* parent): ACarAddCB(parent)
{
    this->setText("Добавить");
}

AJobSalaryLE::AJobSalaryLE(QWidget* parent): EmAuthCodeEnter(parent)
{
    this->setPlaceholderText("Оклад");
}

AJobTitleNameLE::AJobTitleNameLE(QWidget* parent): EmAuthCodeEnter(parent)
{
    this->setPlaceholderText("Название должности");
}

AJobAccompPB::AJobAccompPB(QWidget* parent): AuthPushButton(parent)
{
    this->setText("Выполнить");
}

AJobAddCB::AJobAddCB(QWidget* parent): ACarAddCB(parent)
{
    this->setText("Добавить");
}

AJobDeleteCB::AJobDeleteCB(QWidget* parent): ACarAddCB(parent)
{
    this->setText("Удалить");
}

//Многофункциональные виджеты
BackButton::BackButton(QWidget* parent): AuthPushButton(parent)
{
    this->setText("Назад");
}

void CenteredItemDelegate::initStyleOption(QStyleOptionViewItem *option, const QModelIndex &index) const
{
    QStyledItemDelegate::initStyleOption(option, index);
    option->displayAlignment = Qt::AlignCenter;
}

AMainLabel::AMainLabel(QWidget* parent): RegMainLabel(parent)
{
    this->setText("Администратор");
}

void CenteredItemDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    QStyleOptionViewItem opt = option;
    initStyleOption(&opt, index);

    // Убираем пунктирное выделение
    if (opt.state & QStyle::State_Selected)
    {
        opt.state &= ~QStyle::State_HasFocus;
    }

    QStyledItemDelegate::paint(painter, opt, index);

    // Рисуем вертикальную линию между столбцами
    if (index.column() < index.model()->columnCount() - 1)
    {
        QRect rect = option.rect;
        int x = rect.right();
        painter->setPen(QPen(Qt::black, 1));
        painter->drawLine(x, 0, x, option.widget->height());
    }
};

