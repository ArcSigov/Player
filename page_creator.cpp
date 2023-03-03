#include "page_creator.h"
#include <QDebug>
PageCreator::PageCreator(QObject *parent) : QObject(parent)
{
    page_data = std::make_unique<page>();
    current = page_data.get();
    editor.emplace_back(std::make_unique<ButtonTextEditor>());
    editor.emplace_back(std::make_unique<StringTextEditor>());
    editor.emplace_back(std::make_unique<SwitcherTextEditor>());
    editor.emplace_back(std::make_unique<HeaderTextEditor>());
}


void PageCreator::Text(const Type& type,const TextPosition& pos,const text_t& text)
{
    current->page_text[pos].text = text.text;
    current->page_text[pos].colour = text.colour;
    editor[type]->edit(pos,current->page_text[pos]);
    emit TextChanged(current->page_text);
}


void PageCreator::SwitchPage(const QString& kvs_clicked)
{
    if(kvs_clicked == "КВС1Л")
    {
        qDebug() << "+++";
        if (!current->kvs1l)
            current->kvs1l = std::make_unique<page>();
        current = current->kvs1l.get();
    }
    emit TextChanged(current->page_text);
}
