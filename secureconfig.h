#ifndef SECURECONFIG_H
#define SECURECONFIG_H

#include <QString>
#include <QSettings>
#include <QCryptographicHash>
#include <QByteArray>

class SecureConfig
{
public:
    static SecureConfig& getInstance()
    {
        static SecureConfig instance;
        return instance;
    }

    QString getEmailServiceId() const;
    QString getEmailTemplateId() const;
    QString getEmailUserId() const;
    QString getCompanyName() const;

    void setEmailServiceId(const QString& value);
    void setEmailTemplateId(const QString& value);
    void setEmailUserId(const QString& value);
    void setCompanyName(const QString& value);

private:
    SecureConfig();
    ~SecureConfig();
    SecureConfig(const SecureConfig&) = delete; //Запрещаем копированпие
    SecureConfig& operator=(const SecureConfig&) = delete; //Запрещаем присваивание

    QString encrypt(const QString& value) const;
    QString decrypt(const QString& value) const;
    
    QSettings settings;
    const QByteArray key = QByteArray::fromHex("i h4t3 pr0gr4ming.");
};

#endif // SECURECONFIG_H
