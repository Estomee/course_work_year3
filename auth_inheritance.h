#ifndef AUTH_INHERITANCE_H
#define AUTH_INHERITANCE_H

#include <QTreeView>
#include <QPushButton>
#include <QLabel>
#include <QLineEdit>
#include <QKeyEvent>
#include <QScrollBar>
#include <QStyledItemDelegate>
#include <QPainter>
#include <QStyleOptionViewItem>
#include <QCheckBox>
#include <qheaderview.h>

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

class  RegLastNameLineEdit: public Login
{
    public:
        explicit RegLastNameLineEdit(QWidget* parent);
};

class RegFirstNameLineEdit: public Login
{
    public:
        explicit RegFirstNameLineEdit(QWidget* parent);
};

class RegMiddleNameLineEdit: public Login
{
    public:
        explicit RegMiddleNameLineEdit(QWidget* parent);
};

class RegEmailLineEdit: public Login
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

class ResultTreeView: public QTreeView
{
    public:
        explicit ResultTreeView(QWidget* parent);

    protected:
        void mousePressEvent(QMouseEvent *event) override;
};
//Виджеты окна пользователя

class UserCarSearchLE: public EmAuthCodeEnter
{
    public:
        explicit UserCarSearchLE(QWidget* parent);
};

class UserResultView: public ResultTreeView
{
    public:
        explicit UserResultView(QWidget* parent);
    protected:
        void mousePressEvent(QMouseEvent *event) override;
};

class UserToBacketPB: public AuthPushButton
{
    public:
        explicit UserToBacketPB(QWidget* parent);
};

class UserAddShopBPB: public AuthPushButton
{
    public:
        explicit UserAddShopBPB(QWidget* parent);
};

class UserRefreshResultView: public AuthPushButton
{
    public:
        explicit UserRefreshResultView(QWidget* parent);
};

//Виджеты окна корзины
class BacketResultView: public ResultTreeView
{
    public:
        explicit BacketResultView(QWidget* parent);
    protected:
        void mousePressEvent(QMouseEvent *event) override;
};

class BacketPlaceOfferPB: public AuthPushButton
{
    public:
        explicit BacketPlaceOfferPB(QWidget* parent);
};

class BacketClearPB: public AuthPushButton
{
    public:
        explicit BacketClearPB(QWidget* parent);
};

//Виджеты окна администрации
class AModelNameLE: public EmAuthCodeEnter
{
    public:
        explicit AModelNameLE(QWidget* parent);
};

class AManufNameLE: public EmAuthCodeEnter
{
    public:
        explicit AManufNameLE(QWidget* parent);
};

class AManufCountryLE: public EmAuthCodeEnter
{
    public:
        explicit AManufCountryLE(QWidget* parent);
};

class AEngineCapLE: public EmAuthCodeEnter
{
    public:
        explicit AEngineCapLE(QWidget* parent);
};

class AMaxSpeedLE: public EmAuthCodeEnter
{
    public:
        explicit AMaxSpeedLE(QWidget* parent);
};

class AGenNumLE: public EmAuthCodeEnter
{
    public:
        explicit AGenNumLE(QWidget* parent);
};

class AHorsePowerLE: public EmAuthCodeEnter
{
    public:
        explicit AHorsePowerLE(QWidget* parent);
};

class AMileAgeLE: public EmAuthCodeEnter
{
public:
    explicit AMileAgeLE(QWidget* parent);
};

class ACarCostLE: public EmAuthCodeEnter
{
    public:
        explicit ACarCostLE(QWidget* parent);
};

class AAccompCarPB: public AuthPushButton
{
    public:
        explicit AAccompCarPB(QWidget* parent);
};

class ACarAddCB: public QCheckBox
{
    public:
        explicit ACarAddCB(QWidget* parent);
};

class ACarDeleteCB: public ACarAddCB
{
    public:
        explicit ACarDeleteCB(QWidget* parent);
};

class AJobTitleLE: public EmAuthCodeEnter
{
    public:
        explicit AJobTitleLE(QWidget* parent);
};

class APasspDataLE: public EmAuthCodeEnter
{
    public:
        explicit APasspDataLE(QWidget* parent);
};

class ABirthDateLE: public EmAuthCodeEnter
{
    public:
        explicit ABirthDateLE(QWidget* parent);
};

class ALastNameLE: public EmAuthCodeEnter
{
    public:
        explicit ALastNameLE(QWidget* parent);
};

class AFirstNameLE: public EmAuthCodeEnter
{
    public:
        explicit AFirstNameLE(QWidget* parent);
};

class AMiddleNameLE: public EmAuthCodeEnter
{
    public:
        explicit AMiddleNameLE(QWidget* parent);
};

class AAccompEmplPB: public AuthPushButton
{
    public:
        explicit AAccompEmplPB(QWidget* parent);
};

class AEmplAddCB: public ACarAddCB
{
    public:
        explicit AEmplAddCB(QWidget* parent);
};

class AEmplDeleteCB: public ACarAddCB
{
    public:
        explicit AEmplDeleteCB(QWidget* parent);
};

class AJobSalaryLE: public EmAuthCodeEnter
{
    public:
        explicit AJobSalaryLE(QWidget* parent);
};

class AJobTitleNameLE: public EmAuthCodeEnter
{
    public:
        explicit AJobTitleNameLE(QWidget* parent);
};

class AJobAccompPB: public AuthPushButton
{
    public:
        explicit AJobAccompPB(QWidget* parent);
};

class AJobAddCB: public ACarAddCB
{
    public:
        explicit AJobAddCB(QWidget* parent);
};

class AJobDeleteCB: public ACarAddCB
{
    public:
        explicit AJobDeleteCB(QWidget* parent);
};

class AMainLabel: public RegMainLabel
{
    public:
        explicit AMainLabel(QWidget* parent);
};

//Многофункциональные виджеты
class BackButton: public AuthPushButton
{
    public:
        explicit BackButton(QWidget* parent);
};

class BacketMainLabel: public Enter
{
    public:
        explicit BacketMainLabel(QWidget* parent);
};

class CenteredItemDelegate : public QStyledItemDelegate //
{
    public:
        using QStyledItemDelegate::QStyledItemDelegate;

        void initStyleOption(QStyleOptionViewItem *option, const QModelIndex &index) const override; //Выравнивание текста

        void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const override; //Работа с выделением
};

#endif // AUTH_INHERITANCE_H
