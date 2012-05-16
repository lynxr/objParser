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
    QVector < GLushort > masIndex;
    QVector < GLfloat > masNormals;
    bool isGood; // true - если все успешно считалось и false в обратном случае
protected:
    QString sRegExp;
    QRegExp *regExp, *indexRegExp, *normalsRegExp;
    QString fileName;
    void parserTriangle();
};

#endif // MAINCLASS_H
