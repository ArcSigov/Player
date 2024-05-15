#include "display.h"
#include <QTimer>
#include <QDebug>
#include <algorithm>

LCDDisplay::LCDDisplay(QWidget* parent) : QOpenGLWidget(parent)
{
    setObjectName(QString::fromUtf8("disp"));
    setFocusPolicy(Qt::NoFocus);
    memset(&d,0,sizeof(mfpu_out_b_t));
}

void LCDDisplay::readFonts(const QByteArray& fonts)
{
   fnt = fonts;
}

void LCDDisplay::initializeGL()
{
    initializeOpenGLFunctions();
    glClearColor(0.0f,0.0f,0.0f,0.0f);
    generatePixels(fnt);
    generateTextures();
}

void LCDDisplay::resizeGL(int w, int h)
{
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-14.f,14.f,-7.5f,7.5f,-12.f,12.f);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void LCDDisplay::draw_data(const mfpu_out_b_t* data){
    memset(&d,0,sizeof(mfpu_out_b_t));
    memcpy(&d,data,sizeof(mfpu_out_b_t));
    glClear(GL_COLOR_BUFFER_BIT);
    paintGL();
    repaint();
}

void LCDDisplay::paintGL()
{    
    for (auto i = 0 ; i < 12; i++)
    {
        if (d.data.data[i].id_b.line_number > 0)
        {
            auto x = coordinates[d.data.data[i].id_b.line_number-1][0];
            auto y = coordinates[d.data.data[i].id_b.line_number-1][1];
            for (auto pos = 0 ; pos < 28; pos++)
            {
                glPushMatrix();
                glTranslatef(x,y,0.);
                draw_symb(d.data.data[i].symbols_b[pos]);
                glPopMatrix();
                x++;
            }
        }
    }
}

void LCDDisplay::draw_symb(const mfpu_out_sbi_symbol_b_t& symb)
{ 
    auto mfpu_code = ascii_to_mfpu_font_table[symb.small][symb.code];
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,mfpu_code+1);

    auto colour = checkColour(symb.forecolor);
    auto backcolour = checkColour(symb.backcolor);
    setTextColor(mfpu_code,colour,backcolour);
    glBegin(GL_QUADS);
        glTexCoord2f(0.0,0.0); glVertex2f(0.0,0.0);
        glTexCoord2f(0.0,1.0); glVertex2f(0.0,1.0);
        glTexCoord2f(1.0,1.0); glVertex2f(1.0,1.0);
        glTexCoord2f(1.0,0.0); glVertex2f(1.0,0.0);
    glEnd();
    glDisable(GL_TEXTURE_2D);
}


void LCDDisplay::generatePixels(const QByteArray& bytes)
{
    //проходим по считанному массиву
    auto x = 63u;
    GLubyte pix_image[64][width][3];
    for (auto i = 0; i < bytes.size(); i+=4)
    {
        //одно растровое изображение описывается 64 байтами
        if (i > 0 && i%256 == 0)
        {
            //создаём текстуру полученного символа
            auto pixel = QByteArray((char*)(pix_image+27),height*width*3);
            pixels.push_back(pixel);
            x = 63u;
        }
        // получаем строку символа шириной 29 пикселей (4 байт = 32 пикселя)
        auto _pixel = *(unsigned int*)(bytes.cbegin()+i);
        for (auto y = 0u; y < width; y++)
        {
            pix_image[x][y][0] = 0;
            pix_image[x][y][1] = 0;
            pix_image[x][y][2] = (_pixel >> y & 1) ? 0xff : 0;
        }
        x--;
    }  
}

void LCDDisplay::generateTextures()
{
    for (const auto& pixSymb:qAsConst(pixels))
    {
        GLuint tex_id;
        glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
        glGenTextures(1,&tex_id);
        glBindTexture(GL_TEXTURE_2D,tex_id);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S,     GL_CLAMP);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T,     GL_CLAMP);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);

        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, pixSymb.data());
        glGenerateMipmap(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D,0);
    }
}


void LCDDisplay::setTextColor(const GLuint& texture_id, const Colour& _colour, const Colour& _backcolour)
{
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    GLubyte pix_image[height][width][3];
    memset(pix_image,0,width*height*3);
    memcpy(pix_image,pixels[texture_id].data(),width*height*3);

    for (auto x = 0u; x < height; x++)
        for (auto y = 0u; y < width; y++){
            if (pix_image[x][y][2])
                memcpy(pix_image[x][y],&_colour,3);
            else
                memcpy(pix_image[x][y],&_backcolour,3);
        }
    glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, width, height, GL_RGB, GL_UNSIGNED_BYTE, pix_image);
    glGenerateMipmap(GL_TEXTURE_2D);
}


Colour LCDDisplay::checkColour(const size_t& colour)
{
     Colour c;
     switch(colour){
         case 0: c = Colour::black;       break;//черный
         case 1: c = Colour::red;         break; //красный
         case 2: c = Colour::green;       break; //зеленый
         case 3: c = Colour::lightblue;   break; //голубый
         case 4: c = Colour::blue;        break; //синий
         case 5: c = Colour::purple;      break; //пурпурный
         case 6: c = Colour::yellow;      break; //желтый
         case 7: c = Colour::white;       break; //белый
         default: c = Colour::black;       break;
     }
     return c;
}
