#include "objparser.h"

objParser::objParser(QString _fileName, QString _regExp, QWidget *parent) :
    QGLWidget(parent),
    fileName(_fileName), sRegExp(_regExp), isGood(false)
{
    masVertexes.clear();
    masIndex.clear();
    masNormals.clear();
    parserTriangle();
}

objParser::~objParser() {
    delete regExp;
    delete indexRegExp;
    delete normalsRegExp;
    qDebug() << "DEL";
}

void objParser::parserTriangle() {
    if(sRegExp == "triangle") {
        regExp = new QRegExp("v (.?[0-9]+\.[0-9]+) (.?[0-9]+\.[0-9]+) (.?[0-9]+\.[0-9]+)");
        indexRegExp = new QRegExp("f ([0-9]+)\/\/[0-9]+ ([0-9]+)\/\/[0-9]+ ([0-9]+)\/\/[0-9]+");
        normalsRegExp = new QRegExp("vn (.?[0-9]+\.[0-9]+) (.?[0-9]+\.[0-9]+) (.?[0-9]+\.[0-9]+)");
    }
    QFile file(fileName);
    file.open(QIODevice::ReadOnly | QIODevice::Text);
    if(!file.exists()) {
        qDebug() << "FAIL";
        isGood = false;
        return;
    }
    else {
        qDebug() << "SUPER";
    }
    QTextStream in(&file);
    while(!in.atEnd()) {
        QString tmpText = in.readLine();
        bool ver = regExp->exactMatch(tmpText);
        bool index = indexRegExp->exactMatch(tmpText);
        bool normal = normalsRegExp->exactMatch(tmpText);
        if(ver) {
            masVertexes.push_back(regExp->cap(1).toFloat());
            masVertexes.push_back(regExp->cap(2).toFloat());
            masVertexes.push_back(regExp->cap(3).toFloat());
        }
        if(index) {
            masIndex.push_back(indexRegExp->cap(1).toShort());
            masIndex.push_back(indexRegExp->cap(2).toShort());
            masIndex.push_back(indexRegExp->cap(3).toShort());
        }
        if(normal) {
            masNormals.push_back(normalsRegExp->cap(1).toFloat());
            masNormals.push_back(normalsRegExp->cap(2).toFloat());
            masNormals.push_back(normalsRegExp->cap(3).toFloat());
        }
    }
    qDebug() << masNormals;
    qDebug() << masNormals.size();
    file.close();
    isGood = true;
}
