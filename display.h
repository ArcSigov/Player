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
    QVector<QVector<GLfloat>> coordinates{{-14.0f, 6.61f },
                                          {-14.0f, 5.55f },
                                          {-14.0f, 4.55f },
                                          {-14.0f, 2.65f },
                                          {-14.0f, 1.45f },
                                          {-14.0f, -0.20f},
                                          {-14.0f, -1.20f},
                                          {-14.0f, -2.20f},
                                          {-14.0f, -3.20f},
                                          {-14.0f, -5.15f},
                                          {-14.0f, -6.15f},
                                          {-14.0f, -7.15f}};
public:
    LCDDisplay(QWidget* parent = nullptr);
    void readFonts(const QByteArray& fonts);
public slots:
    void read_text(const QVector<text_t>& _page_text);
    void draw_data(const mfpu_out_b_t* data);
protected:
    void initializeGL() override;
    void resizeGL(int w, int h)  override;
    void paintGL()  override;
private:
    void draw_symb(const mfpu_out_sbi_symbol_b_t& symb);
    Colour checkColour(const size_t& colour);
    mfpu_out_b_t d;
    QByteArray fnt;
    void generatePixels(const QByteArray& bytes);
    void generateTextures();
    void setTextColor(const GLuint& texture_id, const Colour& _colour, const Colour &_backcolour);
    QByteArrayList   pixels;    //пиксели символов
    size_t width = 29u;
    size_t height = 36u;
};

#endif // DISPLAY_H
