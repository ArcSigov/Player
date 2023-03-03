#ifndef DISPLAY_H
#define DISPLAY_H

#include <QOpenGLWidget>
#include <QOpenGLContext>
#include <QOpenGLFunctions>
#include <QObject>
#include "utils.h"

class LCDDisplay : public QOpenGLWidget, QOpenGLFunctions
{
    Q_OBJECT
    QVector<GLfloat> coordinates;
public:
    LCDDisplay(const QByteArray& _non_formatted_pixels,QWidget* parent = nullptr);
public slots:
    void read_text(const QVector<text_t>& _page_text);
protected:
    void initializeGL() override;
    void resizeGL(int w, int h)  override;
    void paintGL()  override;
private:
    GLuint gen_texture(const QByteArray& pixels);
    void GenerateSymbols();
    void set_text_colour(const GLuint& texture_id, const Colour& _colour);
    void draw_symb(const GLuint &tex_id, const Colour& _colour);
    QByteArray*       non_formatted_pixels;
    QByteArrayList   pixels;    //пиксели символов
    QHash<QString,QVector<GLuint>> tex_symbols;
    QVector<text_t> page_text;
    size_t width = 29u;
    size_t height = 36u;
};

#endif // DISPLAY_H
