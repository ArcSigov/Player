#include "text_editor.h"
#include <QDebug>


void ButtonTextEditor::edit(const TextPosition& pos,text_t &text)
{
    if (!text.text.first().isEmpty())
    {
        if (pos < KVS1R_1)
        {
            text.text.first().push_front("<");
        }
        else
        {
            std::reverse(text.text.first().begin(),text.text.first().end());
            text.text.first().push_front(">");
        }
    }
    text.colour.push_back(Colour::blue);
}


void StringTextEditor::edit(const TextPosition& pos,text_t &text)
{
    if (pos >= KVS1R_1)
    {
        for (auto& text: text.text)
            std::reverse(text.begin(),text.end());

        std::reverse(text.text.begin(),text.text.begin()+3);
        std::reverse(text.colour.begin(),text.colour.begin()+3);

        std::reverse(text.text.begin()+3,text.text.end());
        std::reverse(text.colour.begin()+3,text.colour.end());
    }
}

void SwitcherTextEditor::edit(const TextPosition& pos,text_t &text)
{
    text.colour.push_back(Colour::white);
    auto splitted = text.text.at(1).split("/");
    text.text.pop_back();
    for (auto i = 0; i < 2 ; i++)
    {
        text.text.push_back(" ");
        text.colour.push_back(Colour::white);
    }

    for (auto params  = splitted.begin(); params!=splitted.end() ; params++)
    {
        if (params!=splitted.begin())
        {
            text.text.push_back("/");
            text.colour.push_back(Colour::blue);
        }
        text.text.push_back(*params);

        if (params->isUpper()) text.colour.push_back(Colour::green);
        else                   text.colour.push_back(Colour::white);
    }

    if (pos >= KVS1R_1)
    {
        for (auto& text: text.text)
            std::reverse(text.begin(),text.end());

        std::reverse(text.text.begin()+3,text.text.end());
        std::reverse(text.colour.begin()+3,text.colour.end());

    }
}



void HeaderTextEditor::edit(const TextPosition &pos, text_t &text)
{
    Q_UNUSED(pos)
    auto cur_size = 0u;
    for (auto i = 0 ; i < text.text.size();i++)
    {
        if (!i)
            text.colour.push_back(Colour::blue);
        else
            text.colour.push_back(Colour::green);

          cur_size+=text.text[i].size();
    }

    if (cur_size < 28)
    {
        auto fact_size = 28 - cur_size;
        text.text.push_front(QString(fact_size/2,' '));
        text.text.push_back(QString(fact_size-fact_size/2,' '));
        text.colour.push_front(Colour::blue);
        text.colour.push_back(Colour::blue);
    }
}
