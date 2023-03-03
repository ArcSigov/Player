#include "display.h"
#include <QTimer>
#include <QDebug>
#include <algorithm>

LCDDisplay::LCDDisplay(const QByteArray &_non_formatted_pixels, QWidget* parent) : QOpenGLWidget(parent)
{
    setObjectName(QString::fromUtf8("disp"));
    setGeometry(QRect(290, 135, 342, 222));
    setFocusPolicy(Qt::NoFocus);

    non_formatted_pixels = new QByteArray(_non_formatted_pixels);

    GLfloat header_x{-14.0f};
    GLfloat header_y{6.65f};

    GLfloat kvs1l_x{-14.0f};
    GLfloat kvs1l_y{5.5f};

    GLfloat kvs2l_x{-14.0f};
    GLfloat kvs2l_y{2.8f};

    GLfloat kvs3l_x{-14.0f};
    GLfloat kvs3l_y{-0.2f};

    GLfloat kvs4l_x{-14.0f};
    GLfloat kvs4l_y{-3.2f};

    GLfloat kvs5l_x{-14.0f};
    GLfloat kvs5l_y{-6.2f};

    GLfloat kvs1r_x{13.0f};
    GLfloat kvs1r_y{5.5f};

    GLfloat kvs2r_x{13.0f};
    GLfloat kvs2r_y{2.8f};

    GLfloat kvs3r_x{13.0f};
    GLfloat kvs3r_y{-0.2f};

    GLfloat kvs4r_x{13.0f};
    GLfloat kvs4r_y{-3.2f};

    GLfloat kvs5r_x{13.0f};
    GLfloat kvs5r_y{-6.2f};

    coordinates.push_back(header_x);
    coordinates.push_back(header_y);
    coordinates.push_back(kvs1l_x);
    coordinates.push_back(kvs1l_y);
    coordinates.push_back(kvs2l_x);
    coordinates.push_back(kvs2l_y);
    coordinates.push_back(kvs3l_x);
    coordinates.push_back(kvs3l_y);
    coordinates.push_back(kvs4l_x);
    coordinates.push_back(kvs4l_y);
    coordinates.push_back(kvs5l_x);
    coordinates.push_back(kvs5l_y);
    coordinates.push_back(kvs1r_x);
    coordinates.push_back(kvs1r_y);
    coordinates.push_back(kvs2r_x);
    coordinates.push_back(kvs2r_y);
    coordinates.push_back(kvs3r_x);
    coordinates.push_back(kvs3r_y);
    coordinates.push_back(kvs4r_x);
    coordinates.push_back(kvs4r_y);
    coordinates.push_back(kvs5r_x);
    coordinates.push_back(kvs5r_y);

    page_text.resize(22);
}

void LCDDisplay::initializeGL()
{
    initializeOpenGLFunctions();
    glClearColor(0.0f,0.0f,0.0f,0.0f);
    GenerateSymbols();
}

void LCDDisplay::resizeGL(int w, int h)
{
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-14,14,-7.5,7.5,-12.,12.);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}


void LCDDisplay::read_text(const QVector<text_t>& _page_text)
{
    page_text = _page_text;
    qDebug() << "read";
    qDebug() << page_text[KVS1L_1].text;
    paintGL();
}

void LCDDisplay::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT);
    //проход по линиям дисплея
    for (auto line = 0; line < 22; line+=2)
    {
        auto x = coordinates[line];
        auto y = coordinates[line+1];
        //проход по тектсу линий дисплея
        for (auto j = line; j < line+2;j++)
        {
            x = coordinates[line];
            // если лист текстов не пустой
            if (!page_text[j].text.isEmpty())
            {
                //полистовой проход
                for (auto i = 0 ; i < page_text[j].text.size();i++)
                {
                    if (i == 3)
                    {
                        x = coordinates[line];
                        y = coordinates[line+1]-1;
                    }
                    //проход по тексту и его отрисовка
                    for (auto& symb: page_text[j].text[i])
                    {
                        glPushMatrix();
                        auto tex_id = tex_symbols[symb.toUpper()][high];
                        auto y_offset = 0.0f;
                        if (symb.isLower())
                        {
                           tex_id = tex_symbols[symb.toUpper()][medium];
                           y_offset = 0.07f;
                        }
                        else if (symb.isDigit())
                            y_offset = -0.04f;

                        glTranslatef(x,y+y_offset,0.);
                        draw_symb(tex_id,page_text[j].colour[i]);
                        glPopMatrix();
                        x = line < 12 ? x + 1 : x - 1;
                    }
                }
            }
        }
    }
}

void LCDDisplay::GenerateSymbols()
{
    //проходим по считанному массиву
    auto x = 63u;
    QVector<GLuint>  textures;
    for (auto i = 0; i < non_formatted_pixels->size(); i+=4)
    {
        GLubyte pix_image[64][width][3];
        //одно растровое изображение описывается 64 байтами
        if (i > 0 && i%256 == 0)
        {
            //создаём текстуру полученного символа
            auto pixel = QByteArray((char*)(pix_image+27),height*width*3);
            pixels.push_back(pixel);
            textures.push_back(gen_texture(pixel));
            x = 63u;
        }
        // получаем строку символа шириной 29 пикселей (4 байт = 32 пикселя)
        auto _pixel = *(unsigned int*)(non_formatted_pixels->begin()+i);
        for (auto y = 0u; y < width; y++)
        {
            pix_image[x][y][0] = 0;
            pix_image[x][y][1] = 0;
            pix_image[x][y][2] = (_pixel >> y & 1) ? 0xff : 0;
        }
        x--;
    }

        tex_symbols[" "].push_back(textures[0]);
        tex_symbols[" "].push_back(textures[0]);
        tex_symbols[" "].push_back(textures[0]);

        tex_symbols["A"].push_back(textures[65]);
        tex_symbols["A"].push_back(textures[16]);
        tex_symbols["A"].push_back(textures[97]);

        tex_symbols["B"].push_back(textures[66]);
        tex_symbols["B"].push_back(textures[154]);
        tex_symbols["B"].push_back(textures[98]);

        tex_symbols["C"].push_back(textures[67]);
        tex_symbols["C"].push_back(textures[1]);
        tex_symbols["C"].push_back(textures[99]);

        tex_symbols["D"].push_back(textures[68]);
        tex_symbols["D"].push_back(textures[2]);
        tex_symbols["D"].push_back(textures[100]);

        tex_symbols["E"].push_back(textures[69]);
        tex_symbols["E"].push_back(textures[3]);
        tex_symbols["E"].push_back(textures[101]);

        tex_symbols["F"].push_back(textures[70]);
        tex_symbols["F"].push_back(textures[4]);
        tex_symbols["F"].push_back(textures[102]);

        tex_symbols["G"].push_back(textures[71]);
        tex_symbols["G"].push_back(textures[5]);
        tex_symbols["G"].push_back(textures[103]);

        tex_symbols["H"].push_back(textures[72]);
        tex_symbols["H"].push_back(textures[6]);
        tex_symbols["H"].push_back(textures[104]);

        tex_symbols["I"].push_back(textures[73]);
        tex_symbols["I"].push_back(textures[7]);
        tex_symbols["I"].push_back(textures[105]);

        tex_symbols["J"].push_back(textures[74]);
        tex_symbols["J"].push_back(textures[8]);
        tex_symbols["J"].push_back(textures[106]);

        tex_symbols["K"].push_back(textures[75]);
        tex_symbols["K"].push_back(textures[9]);
        tex_symbols["K"].push_back(textures[107]);

        tex_symbols["L"].push_back(textures[76]);
        tex_symbols["L"].push_back(textures[10]);
        tex_symbols["L"].push_back(textures[108]);

        tex_symbols["M"].push_back(textures[77]);
        tex_symbols["M"].push_back(textures[11]);
        tex_symbols["M"].push_back(textures[109]);

        tex_symbols["N"].push_back(textures[78]);
        tex_symbols["N"].push_back(textures[12]);
        tex_symbols["N"].push_back(textures[110]);

        tex_symbols["O"].push_back(textures[79]);
        tex_symbols["O"].push_back(textures[13]);
        tex_symbols["O"].push_back(textures[111]);

        tex_symbols["P"].push_back(textures[80]);
        tex_symbols["P"].push_back(textures[14]);
        tex_symbols["P"].push_back(textures[112]);

        tex_symbols["Q"].push_back(textures[81]);
        tex_symbols["Q"].push_back(textures[15]);
        tex_symbols["Q"].push_back(textures[113]);

        tex_symbols["R"].push_back(textures[82]);
        tex_symbols["R"].push_back(textures[17]);
        tex_symbols["R"].push_back(textures[114]);

        tex_symbols["S"].push_back(textures[83]);
        tex_symbols["S"].push_back(textures[18]);
        tex_symbols["S"].push_back(textures[115]);

        tex_symbols["T"].push_back(textures[84]);
        tex_symbols["T"].push_back(textures[19]);
        tex_symbols["T"].push_back(textures[116]);

        tex_symbols["U"].push_back(textures[85]);
        tex_symbols["U"].push_back(textures[20]);
        tex_symbols["U"].push_back(textures[117]);

        tex_symbols["V"].push_back(textures[86]);
        tex_symbols["V"].push_back(textures[21]);
        tex_symbols["V"].push_back(textures[118]);

        tex_symbols["W"].push_back(textures[87]);
        tex_symbols["W"].push_back(textures[22]);
        tex_symbols["W"].push_back(textures[119]);

        tex_symbols["X"].push_back(textures[88]);
        tex_symbols["X"].push_back(textures[23]);
        tex_symbols["X"].push_back(textures[120]);

        tex_symbols["Y"].push_back(textures[89]);
        tex_symbols["Y"].push_back(textures[24]);
        tex_symbols["Y"].push_back(textures[121]);

        tex_symbols["Z"].push_back(textures[90]);
        tex_symbols["Z"].push_back(textures[25]);
        tex_symbols["Z"].push_back(textures[122]);

        //!< Русский алфавит

        tex_symbols["А"].push_back(textures[65]);
        tex_symbols["А"].push_back(textures[16]);
        tex_symbols["А"].push_back(textures[97]);

        tex_symbols["Б"].push_back(textures[193]);
        tex_symbols["Б"].push_back(textures[26]);
        tex_symbols["Б"].push_back(textures[225]);

        tex_symbols["В"].push_back(textures[66]);
        tex_symbols["В"].push_back(textures[154]);
        tex_symbols["В"].push_back(textures[226]);

        tex_symbols["Г"].push_back(textures[195]);
        tex_symbols["Г"].push_back(textures[27]);
        tex_symbols["Г"].push_back(textures[227]);

        tex_symbols["Д"].push_back(textures[196]);
        tex_symbols["Д"].push_back(textures[28]);
        tex_symbols["Д"].push_back(textures[228]);

        tex_symbols["Е"].push_back(textures[69]);
        tex_symbols["Е"].push_back(textures[3]);
        tex_symbols["Е"].push_back(textures[101]);

        tex_symbols["Ё"].push_back(textures[69]);
        tex_symbols["Ё"].push_back(textures[3]);
        tex_symbols["Ё"].push_back(textures[101]);

        tex_symbols["Ж"].push_back(textures[198]);
        tex_symbols["Ж"].push_back(textures[29]);
        tex_symbols["Ж"].push_back(textures[230]);

        tex_symbols["З"].push_back(textures[199]);
        tex_symbols["З"].push_back(textures[30]);
        tex_symbols["З"].push_back(textures[231]);

        tex_symbols["И"].push_back(textures[200]);
        tex_symbols["И"].push_back(textures[31]);
        tex_symbols["И"].push_back(textures[232]);

        tex_symbols["Й"].push_back(textures[201]);
        tex_symbols["Й"].push_back(textures[35]);
        tex_symbols["Й"].push_back(textures[233]);

        tex_symbols["К"].push_back(textures[75]);
        tex_symbols["К"].push_back(textures[9]);
        tex_symbols["К"].push_back(textures[234]);

        tex_symbols["Л"].push_back(textures[203]);
        tex_symbols["Л"].push_back(textures[36]);
        tex_symbols["Л"].push_back(textures[235]);

        tex_symbols["М"].push_back(textures[204]);
        tex_symbols["М"].push_back(textures[11]);
        tex_symbols["М"].push_back(textures[236]);

        tex_symbols["Н"].push_back(textures[72]);
        tex_symbols["Н"].push_back(textures[6]);
        tex_symbols["Н"].push_back(textures[237]);

        tex_symbols["О"].push_back(textures[79]);
        tex_symbols["О"].push_back(textures[13]);
        tex_symbols["О"].push_back(textures[111]);

        tex_symbols["П"].push_back(textures[207]);
        tex_symbols["П"].push_back(textures[38]);
        tex_symbols["П"].push_back(textures[239]);

        tex_symbols["Р"].push_back(textures[80]);
        tex_symbols["Р"].push_back(textures[14]);
        tex_symbols["Р"].push_back(textures[112]);

        tex_symbols["С"].push_back(textures[67]);
        tex_symbols["С"].push_back(textures[1]);
        tex_symbols["С"].push_back(textures[99]);

        tex_symbols["Т"].push_back(textures[84]);
        tex_symbols["Т"].push_back(textures[19]);
        tex_symbols["Т"].push_back(textures[242]);

        tex_symbols["У"].push_back(textures[211]);
        tex_symbols["У"].push_back(textures[64]);
        tex_symbols["У"].push_back(textures[121]);

        tex_symbols["Ф"].push_back(textures[212]);
        tex_symbols["Ф"].push_back(textures[91]);
        tex_symbols["Ф"].push_back(textures[244]);

        tex_symbols["Х"].push_back(textures[88]);
        tex_symbols["Х"].push_back(textures[23]);
        tex_symbols["Х"].push_back(textures[120]);

        tex_symbols["Ц"].push_back(textures[214]);
        tex_symbols["Ц"].push_back(textures[92]);
        tex_symbols["Ц"].push_back(textures[246]);

        tex_symbols["Ч"].push_back(textures[215]);
        tex_symbols["Ч"].push_back(textures[93]);
        tex_symbols["Ч"].push_back(textures[247]);

        tex_symbols["Ш"].push_back(textures[216]);
        tex_symbols["Ш"].push_back(textures[94]);
        tex_symbols["Ш"].push_back(textures[248]);

        tex_symbols["Щ"].push_back(textures[217]);
        tex_symbols["Щ"].push_back(textures[95]);
        tex_symbols["Щ"].push_back(textures[249]);

        tex_symbols["Ъ"].push_back(textures[218]);
        tex_symbols["Ъ"].push_back(textures[96]);
        tex_symbols["Ъ"].push_back(textures[250]);

        tex_symbols["Ы"].push_back(textures[219]);
        tex_symbols["Ы"].push_back(textures[123]);
        tex_symbols["Ы"].push_back(textures[251]);

        tex_symbols["Ь"].push_back(textures[220]);
        tex_symbols["Ь"].push_back(textures[124]);
        tex_symbols["Ь"].push_back(textures[252]);

        tex_symbols["Э"].push_back(textures[221]);
        tex_symbols["Э"].push_back(textures[125]);
        tex_symbols["Э"].push_back(textures[253]);

        tex_symbols["Ю"].push_back(textures[222]);
        tex_symbols["Ю"].push_back(textures[126]);
        tex_symbols["Ю"].push_back(textures[254]);

        tex_symbols["Я"].push_back(textures[223]);
        tex_symbols["Я"].push_back(textures[127]);
        tex_symbols["Я"].push_back(textures[255]);

        tex_symbols["0"].push_back(textures[48]);
        tex_symbols["0"].push_back(textures[48]);
        tex_symbols["0"].push_back(textures[192]);

        tex_symbols["1"].push_back(textures[49]);
        tex_symbols["1"].push_back(textures[49]);
        tex_symbols["1"].push_back(textures[194]);


        tex_symbols["2"].push_back(textures[50]);
        tex_symbols["2"].push_back(textures[50]);
        tex_symbols["2"].push_back(textures[197]);


        tex_symbols["3"].push_back(textures[51]);
        tex_symbols["3"].push_back(textures[51]);
        tex_symbols["3"].push_back(textures[202]);


        tex_symbols["4"].push_back(textures[52]);
        tex_symbols["4"].push_back(textures[52]);
        tex_symbols["4"].push_back(textures[205]);

        tex_symbols["5"].push_back(textures[53]);
        tex_symbols["5"].push_back(textures[53]);
        tex_symbols["5"].push_back(textures[206]);

        tex_symbols["6"].push_back(textures[54]);
        tex_symbols["6"].push_back(textures[54]);
        tex_symbols["6"].push_back(textures[208]);

        tex_symbols["7"].push_back(textures[55]);
        tex_symbols["7"].push_back(textures[55]);
        tex_symbols["7"].push_back(textures[209]);

        tex_symbols["8"].push_back(textures[56]);
        tex_symbols["8"].push_back(textures[56]);
        tex_symbols["8"].push_back(textures[210]);

        tex_symbols["9"].push_back(textures[57]);
        tex_symbols["9"].push_back(textures[57]);
        tex_symbols["9"].push_back(textures[213]);


        tex_symbols["-"].push_back(textures[45]);
        tex_symbols["-"].push_back(1);
        tex_symbols["-"].push_back(textures[45]);

        tex_symbols[":"].push_back(textures[58]);
        tex_symbols[":"].push_back(1);
        tex_symbols[":"].push_back(textures[187]);

        tex_symbols["+"].push_back(textures[43]);
        tex_symbols["+"].push_back(1);
        tex_symbols["+"].push_back(textures[240]);

        tex_symbols[","].push_back(textures[44]);
        tex_symbols[","].push_back(1);
        tex_symbols[","].push_back(textures[186]);

        tex_symbols["."].push_back(textures[46]);
        tex_symbols["."].push_back(1);
        tex_symbols["."].push_back(textures[184]);

        tex_symbols["/"].push_back(textures[47]);
        tex_symbols["/"].push_back(textures[238]);
        tex_symbols["/"].push_back(textures[238]);

        tex_symbols[";"].push_back(textures[59]);
        tex_symbols[";"].push_back(1);
        tex_symbols[";"].push_back(textures[188]);

        tex_symbols["<"].push_back(textures[60]);
        tex_symbols["<"].push_back(textures[60]);
        tex_symbols["<"].push_back(textures[243]);

        tex_symbols["="].push_back(textures[61]);
        tex_symbols["="].push_back(1);
        tex_symbols["="].push_back(textures[189]);

        tex_symbols[">"].push_back(textures[62]);
        tex_symbols[">"].push_back(textures[62]);
        tex_symbols[">"].push_back(textures[245]);

        tex_symbols["?"].push_back(textures[63]);
        tex_symbols["?"].push_back(1);
        tex_symbols["?"].push_back(textures[190]);

        tex_symbols["("].push_back(textures[40]);
        tex_symbols["("].push_back(1);
        tex_symbols["("].push_back(textures[180]);

        tex_symbols[")"].push_back(textures[41]);
        tex_symbols[")"].push_back(1);
        tex_symbols[")"].push_back(textures[181]);

        tex_symbols["*"].push_back(textures[42]);
        tex_symbols["*"].push_back(1);
        tex_symbols["*"].push_back(textures[183]);

        tex_symbols["!"].push_back(textures[33]);
        tex_symbols["!"].push_back(1);
        tex_symbols["!"].push_back(textures[155]);

        tex_symbols["'"].push_back(textures[39]);
        tex_symbols["'"].push_back(1);
        tex_symbols["'"].push_back(textures[182]);

        tex_symbols["\""].push_back(textures[34]);
        tex_symbols["\""].push_back(1);
        tex_symbols["\""].push_back(textures[159]);

        tex_symbols["%"].push_back(textures[37]);
        tex_symbols["%"].push_back(1);
        tex_symbols["%"].push_back(textures[156]);

        tex_symbols["⪻"].push_back(textures[157]);
        tex_symbols["⪻"].push_back(1);
        tex_symbols["⪻"].push_back(textures[178]);

        tex_symbols["⪼"].push_back(textures[158]);
        tex_symbols["⪼"].push_back(1);
        tex_symbols["⪼"].push_back(textures[179]);

        tex_symbols["Α"].push_back(textures[128]);
        tex_symbols["Α"].push_back(textures[144]);
        tex_symbols["Α"].push_back(textures[144]);

        tex_symbols["Β"].push_back(textures[129]);
        tex_symbols["Β"].push_back(textures[145]);
        tex_symbols["Β"].push_back(textures[145]);

        tex_symbols["Ɣ"].push_back(textures[130]);
        tex_symbols["Ɣ"].push_back(textures[146]);
        tex_symbols["Ɣ"].push_back(textures[146]);

        tex_symbols["Δ"].push_back(textures[131]);
        tex_symbols["Δ"].push_back(textures[147]);
        tex_symbols["Δ"].push_back(textures[147]);

        tex_symbols["Λ"].push_back(textures[132]);
        tex_symbols["Λ"].push_back(1);
        tex_symbols["Λ"].push_back(textures[148]);

        tex_symbols["Θ"].push_back(textures[133]);
        tex_symbols["Θ"].push_back(textures[149]);
        tex_symbols["Θ"].push_back(textures[149]);

        tex_symbols["Μ"].push_back(textures[134]);
        tex_symbols["Μ"].push_back(textures[150]);
        tex_symbols["Μ"].push_back(textures[150]);

        tex_symbols["Φ"].push_back(textures[135]);
        tex_symbols["Φ"].push_back(textures[151]);
        tex_symbols["Φ"].push_back(textures[151]);

        tex_symbols["Ψ"].push_back(textures[136]);
        tex_symbols["Ψ"].push_back(textures[152]);
        tex_symbols["Ψ"].push_back(textures[152]);

        tex_symbols["Ω"].push_back(textures[137]);
        tex_symbols["Ω"].push_back(textures[153]);
        tex_symbols["Ω"].push_back(textures[153]);

        tex_symbols["↑"].push_back(textures[138]);
        tex_symbols["↓"].push_back(textures[139]);
        tex_symbols["↕"].push_back(textures[140]);
        tex_symbols["←"].push_back(textures[141]);
        tex_symbols["→"].push_back(textures[142]);
        tex_symbols["↔"].push_back(textures[143]);

        tex_symbols["₂"].push_back(textures[160]);
        tex_symbols["³"].push_back(textures[161]);
        tex_symbols["²"].push_back(textures[224]);
        tex_symbols["₃"].push_back(textures[162]);

        tex_symbols["№"].push_back(textures[185]);
        tex_symbols["№"].push_back(textures[163]);
        tex_symbols["_"].push_back(textures[164]);
        tex_symbols["_"].push_back(textures[165]);
        tex_symbols["_"].push_back(textures[241]);

        tex_symbols["Ρ"].push_back(textures[166]);
        tex_symbols["Ρ"].push_back(textures[167]);
        tex_symbols["Ρ"].push_back(textures[167]);

        tex_symbols["°"].push_back(textures[176]);
        tex_symbols["°"].push_back(1);
        tex_symbols["°"].push_back(textures[191]);

        tex_symbols["±"].push_back(textures[177]);
        tex_symbols["±"].push_back(1);
        tex_symbols["±"].push_back(textures[229]);


    delete non_formatted_pixels;
}

GLuint LCDDisplay::gen_texture(const QByteArray& pixels)
{
    GLuint tex_id;
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    glGenTextures(1,&tex_id);
    glBindTexture(GL_TEXTURE_2D,tex_id);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S,     GL_CLAMP);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T,     GL_CLAMP);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, pixels.data());
    glGenerateMipmap(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,0);
    return tex_id;
}



void LCDDisplay::set_text_colour(const GLuint& texture_id, const Colour& _colour)
{
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    GLubyte pix_image[height][width][3];
    memset(pix_image,0,width*height*3);
    memcpy(pix_image,pixels[texture_id-1].data(),width*height*3);

    for (auto x = 0u; x < height; x++)
        for (auto y = 0u; y < width; y++)
            if (pix_image[x][y][2])
                memcpy(pix_image[x][y],&_colour,3);

    glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, width, height, GL_RGB, GL_UNSIGNED_BYTE, pix_image);
    glGenerateMipmap(GL_TEXTURE_2D);

}

void LCDDisplay::draw_symb(const GLuint& tex_id, const Colour &_colour)
{
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,tex_id);
    set_text_colour(tex_id,_colour);
    glBegin(GL_QUADS);
        glTexCoord2f(0.0,0.0); glVertex2f(0.0,0.0);
        glTexCoord2f(0.0,1.0); glVertex2f(0.0,1.0);
        glTexCoord2f(1.0,1.0); glVertex2f(1.0,1.0);
        glTexCoord2f(1.0,0.0); glVertex2f(1.0,0.0);
    glEnd();
    glDisable(GL_TEXTURE_2D);
}
