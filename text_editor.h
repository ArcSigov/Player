#ifndef TEXT_EDITOR_H
#define TEXT_EDITOR_H

#include "utils.h"

class TextEditor
{
public:
    TextEditor() = default;
    virtual ~TextEditor() = default;
    virtual void edit(const TextPosition& pos,text_t& text) = 0;
};



class ButtonTextEditor : public TextEditor
{
public:
    ButtonTextEditor() = default;
    ~ButtonTextEditor()  = default;
    void edit(const TextPosition& pos,text_t& text) override;
};

class SwitcherTextEditor : public TextEditor
{
public:
    SwitcherTextEditor() = default;
    ~SwitcherTextEditor()  = default;
    void edit(const TextPosition& pos,text_t& text) override;
};

class HeaderTextEditor : public TextEditor
{
public:
    HeaderTextEditor() = default;
    ~HeaderTextEditor()  = default;
    void edit(const TextPosition& pos,text_t& text) override;
};


class StringTextEditor : public TextEditor
{
public:
    StringTextEditor() = default;
    ~StringTextEditor()  = default;
    void edit(const TextPosition& pos,text_t& text) override;
};


#endif // TEXT_EDITOR_H
