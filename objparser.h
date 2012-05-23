#ifndef OBJPARSER_H
#define OBJPARSER_H

#include <QGLWidget>
#include <QDebug>
#include <QFile>

class objParser : public QGLWidget
{
public:
    explicit objParser(QString _fileName, QString _regExp = "triangle", QWidget *parent = 0);
    virtual ~objParser();
    QVector < GLfloat > masVertexes;

    QVector < GLushort > masIndexVer; // массив индексов координат
    QVector < GLushort > masIndexTex; // массив индексов текстур
    QVector < GLushort > masIndexNorm; // массив индексов нормалей

    QVector < GLfloat > masNormals;
    QVector < GLfloat > masTexture; // текстурные координаты
    bool isGood; // true - если все успешно считалось и false в обратном случае
protected:
    QString sRegExp;
    QRegExp *regExp, *indexRegExp, *normalsRegExp, *textureRegExp;
    QString fileName;
    void parserTriangle();
};

#endif // MAINCLASS_H
