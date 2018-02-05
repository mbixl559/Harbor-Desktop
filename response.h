#ifndef RESPONSE_H
#define RESPONSE_H

// QT Library Includes
#include <QObject>
#include <QString>
#include <QStringList>

// Standard Library Includes
#include <vector>

// Custom Library includes

class Response
{
public:
    // Public Members

private:
    // Private Memebers
    QString typeCode;
    QString Data;

public:
    // Public Methods
    explicit Response(QString type, QString data);

    void setType(QString type);
    QString getTypeCode();

    void setData(QString data);
    QString getData();

private:
    // Private Methods

signals:

public slots:
};

#endif // RESPONSE_H
