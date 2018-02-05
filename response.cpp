#include "response.h"

Response::Response(QString type, QString data): typeCode(type), Data(data)
{

}

QString Response::getTypeCode() {
    return typeCode;
}
void Response::setType(QString type) {
    typeCode = type;
}

QString Response::getData() {
    return Data;
}
void Response::setData(QString data) {
    Data = data;
}
