#ifndef PAGE_CREATOR_H
#define PAGE_CREATOR_H

#include <QObject>
#include "utils.h"
#include <memory>
#include <vector>
#include <QHash>
#include <QPair>
#include "text_editor.h"

class PageCreator : public QObject
{
    Q_OBJECT
    struct page
    {
         QVector<text_t> page_text;  //текст для отрисовки на экране
         std::unique_ptr<page>  kvs1l;
         std::unique_ptr<page>  kvs2l;
         std::unique_ptr<page>  kvs3l;
         std::unique_ptr<page>  kvs4l;
         std::unique_ptr<page>  kvs5l;
         std::unique_ptr<page>  kvs1r;
         std::unique_ptr<page>  kvs2r;
         std::unique_ptr<page>  kvs3r;
         std::unique_ptr<page>  kvs4r;
         std::unique_ptr<page>  kvs5r;
         //конструктор по умолчанию
         page()
         {
             page_text.resize(22);
             for (auto i = 0; i < 22; i++)
             {
                 page_text[i].text.push_back(" ");
                 page_text[i].colour.push_back(Colour::blue);
             }
         }
    };

    public:
        explicit PageCreator(QObject *parent = nullptr);
    public slots:
        void Text(const Type& type,const TextPosition&,const text_t&);
        void SwitchPage(const QString& kvs_clicked);
    signals:
        void TextChanged(const  QVector<text_t>&);
    private:
        std::vector<std::unique_ptr<TextEditor>> editor;    //контейнер текстовых редакторов для форматирования перед отрисовкой
        std::unique_ptr<page>   page_data;
        page* current;
};

#endif // PAGE_CREATOR_H
