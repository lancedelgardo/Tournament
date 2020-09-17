#include "SettingsData.h"

#include <QJsonObject>

SettingsData::SettingsData(QObject *parent) : QObject(parent) { test = "BLABLABLA"; }

void SettingsData::toJson(QJsonObject &json)
{
    json["Test"] = test;
    //
}

void SettingsData::fromJson(const QJsonObject &json)
{
    if (json.contains("Test")) test = json["Test"].toString();
    //
}

QString SettingsData::getTest() const { return test; }

void SettingsData::setTest(const QString &value) { test = value; }
