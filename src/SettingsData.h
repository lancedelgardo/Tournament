#ifndef SETTINGSDATA_H
#define SETTINGSDATA_H

#include <QObject>

class SettingsData : public QObject
{
    Q_OBJECT
  public:
    explicit SettingsData(QObject *parent = nullptr);

    void toJson(QJsonObject &json);
    void fromJson(const QJsonObject &json);

    QString getTest() const;
    void setTest(const QString &value);

  private:
    QString test;

  signals:
};

#endif  // SETTINGSDATA_H
