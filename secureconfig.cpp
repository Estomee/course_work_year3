#include "secureconfig.h"
#include <QCryptographicHash>
#include <QDateTime>
#include <QRandomGenerator>
#include <QDataStream>

SecureConfig::SecureConfig()
    : settings("config/settings.ini", QSettings::IniFormat) {}

SecureConfig::~SecureConfig()
{
    settings.sync();
}

QString SecureConfig::encrypt(const QString& value) const
{
    QByteArray data = value.toUtf8();
    QByteArray encrypted;
    
    for(int i = 0; i < data.size(); ++i)
    {
        encrypted.append(data[i] ^ key[i % key.size()]);
    }
    
    return QString::fromLatin1(encrypted.toBase64());
}

QString SecureConfig::decrypt(const QString& value) const
{
    QByteArray data = QByteArray::fromBase64(value.toLatin1());
    QByteArray decrypted;
    
    for(int i = 0; i < data.size(); ++i)
    {
        decrypted.append(data[i] ^ key[i % key.size()]);
    }
    
    return QString::fromUtf8(decrypted);
}

QString SecureConfig::getEmailServiceId() const
{
    return decrypt(settings.value("Email/ServiceId").toString());
}

QString SecureConfig::getEmailTemplateId() const
{
    return decrypt(settings.value("Email/TemplateId").toString());
}

QString SecureConfig::getEmailUserId() const
{
    return decrypt(settings.value("Email/UserId").toString());
}

QString SecureConfig::getCompanyName() const
{
    return decrypt(settings.value("Company/Name").toString());
}

void SecureConfig::setEmailServiceId(const QString& value)
{
    settings.setValue("Email/ServiceId", encrypt(value));
}

void SecureConfig::setEmailTemplateId(const QString& value)
{
    settings.setValue("Email/TemplateId", encrypt(value));
}

void SecureConfig::setEmailUserId(const QString& value)
{
    settings.setValue("Email/UserId", encrypt(value));
}

void SecureConfig::setCompanyName(const QString& value)
{
    settings.setValue("Company/Name", encrypt(value));
}
