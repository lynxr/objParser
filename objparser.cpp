#include "objparser.h"

objParser::objParser(QString _fileName, QString _regExp, QWidget *parent) :
    QGLWidget(parent),
    fileName(_fileName), sRegExp(_regExp), isGood(false)
{
    masVertexes.clear();
    masIndexVer.clear();
    masIndexNorm.clear();
    masNormals.clear();
    masTexture.clear();
    masIndexTex.clear();
    if(sRegExp == "triangle") {
        parserTriangle();
    }
}

objParser::~objParser() {
    delete regExp;
    delete indexRegExp;
    delete normalsRegExp;
    qDebug() << "DEL";
}

void objParser::parserTriangle() {
        regExp = new QRegExp("v (.?[0-9]+\.[0-9]+) (.?[0-9]+\.[0-9]+) (.?[0-9]+\.[0-9]+)");
        textureRegExp = new QRegExp("vt (.?[0-9]+\.[0-9]+) (.?[0-9]+\.[0-9]+)");
        indexRegExp = new QRegExp("f ([0-9]+)\/([0-9]+)\/([0-9]+) ([0-9]+)\/([0-9]+)\/([0-9]+) ([0-9]+)\/([0-9]+)\/([0-9]+)");
        normalsRegExp = new QRegExp("vn (.?[0-9]+\.[0-9]+) (.?[0-9]+\.[0-9]+) (.?[0-9]+\.[0-9]+)");
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
        bool indexVer = indexRegExp->exactMatch(tmpText);
        bool normal = normalsRegExp->exactMatch(tmpText);
        bool texture = textureRegExp->exactMatch(tmpText);
        if(ver) {
            masVertexes.push_back(regExp->cap(1).toFloat());
            masVertexes.push_back(regExp->cap(2).toFloat());
            masVertexes.push_back(regExp->cap(3).toFloat());
        }
        if(indexVer) {
            // массив вершин
            masIndexVer.push_back(indexRegExp->cap(1).toShort());
            masIndexVer.push_back(indexRegExp->cap(4).toShort());
            masIndexVer.push_back(indexRegExp->cap(7).toShort());

            // массив текстурных индексов
            masIndexTex.push_back(indexRegExp->cap(2).toShort());
            masIndexTex.push_back(indexRegExp->cap(5).toShort());
            masIndexTex.push_back(indexRegExp->cap(8).toShort());

            // массив индексов нормалей
            masIndexNorm.push_back(indexRegExp->cap(3).toShort());
            masIndexNorm.push_back(indexRegExp->cap(6).toShort());
            masIndexNorm.push_back(indexRegExp->cap(9).toShort());
        }
        if(normal) {
            masNormals.push_back(normalsRegExp->cap(1).toFloat());
            masNormals.push_back(normalsRegExp->cap(2).toFloat());
            masNormals.push_back(normalsRegExp->cap(3).toFloat());
        }
        if(texture) {
            masTexture.push_back(textureRegExp->cap(1).toFloat());
            masTexture.push_back(textureRegExp->cap(2).toFloat());
        }
    } // while
    qDebug() << masIndexNorm;
    qDebug() << masIndexNorm.size();
    file.close();
    isGood = true;
}
