#ifndef UTILS_H
#define UTILS_H

#include <QStringList>
#include <QVector>

enum class Colour
{
    black     = 0x000000,
    white     = 0xf8fcf8,
    lightblue = 0x20c0e0,
    blue      = 0x0858f8,
    green     = 0x00e000,
    red       = 0xf83018,
    yellow    = 0xf8e020,
    purple    = 0xf800f8
};

//! Слово-идентификатор сообщения (для СБИ)
typedef struct mfpu_out_sbi_id_b_t {
   uint16_t message_number : 12; //!< Номер сообщения (изменяется после передачи всех строк в СБИ) //(min:1 max:4095)
   uint16_t line_number    : 4;  //!< Номер строки на экране МФПУ, передаваемой в СБИ //(min:1 max:12)
} mfpu_out_sbi_id_b_t;

//! Слово 1 состояния сигнализаторов и кода нажатой кнопки (для СБИ)
typedef struct mfpu_out_sbi_button_fires_1_b_t {
   uint16_t pressed_button : 8; //!< Код нажатой кнопки //(min:0 max:107)
   uint16_t plan           : 1; //!< Включение сигнализатора у кнопки "ПЛАН ПОЛ"
   uint16_t active_route   : 1; //!< Включение сигнализатора у кнопки "ВЫП ПОЛ"
   uint16_t comb           : 1; //!< Включение сигнализатора у кнопки "ПРЯМО НА"
   uint16_t u19            : 1; //!< Включение сигнализатора у кнопки "19"
   uint16_t suo            : 1; //!< Включение сигнализатора у кнопки "СУО"
   uint16_t basu           : 1; //!< Включение сигнализатора у кнопки "БАСУ"
   uint16_t flight_data    : 1; //!< Включение сигнализатора у кнопки "ПОЛ.ДАНН"
   uint16_t nav            : 1; //!< Включение сигнализатора у кнопки "НАВ"
} mfpu_out_sbi_button_fires_1_b_t;

//! Слово 2 состояния сигнализаторов и кода нажатой кнопки (для СБИ)
typedef struct mfpu_out_sbi_button_fires_2_b_t {
   uint16_t selected_time : 1; //!< Включение сигнализатора у кнопки "Тз"
   uint16_t rts           : 1; //!< Включение сигнализатора у кнопки "РТС"
   uint16_t maneuver      : 1; //!< Включение сигнализатора у кнопки "МАНЕВР"
   uint16_t arv_arp       : 1; //!< Включение сигнализатора у кнопки "АРВ АРП"
   uint16_t corr          : 1; //!< Включение сигнализатора у кнопки "КОРР"
   uint16_t isp           : 1; //!< Включение сигнализатора у кнопки "ИСП"
   uint16_t mfpu_control  : 1; //!< Включение сигнализатора у кнопки "УПР МФПУ"
   uint16_t bks           : 1; //!< Включение сигнализатора у кнопки "ИНФ БКС"
   uint16_t eng           : 1; //!< Включение сигнализатора у кнопки "ENG"
   uint16_t iipa          : 1; //!< Включение сигнализатора у кнопки "ИИПЭ"
   uint16_t reserve       : 1; //!< Включение сигнализатора у кнопки режимной (второй в 4-м ряду)
   uint16_t digits        : 1; //!< Включение сигнализатора у кнопки "ЦИФР"
   uint16_t               : 4; //!< Резерв
} mfpu_out_sbi_button_fires_2_b_t;

//! Слово состояния символа на экране МФПУ (для СБИ)
typedef struct mfpu_out_sbi_symbol_b_t {
   uint16_t code      : 8; //!< Код символа (модифицированная кодировка Win-1251 со спецсимволами МФПУ с кодами от 0x80 до 0x9a) //(min:0 max:255)
   uint16_t small     : 1; //!< Размер символа (0-крупный, 1-мелкий)
   uint16_t forecolor : 3; //!< Цвет символа //(min:0 max:7)
   uint16_t backcolor : 3; //!< Цвет фона //(min:0 max:7)
   uint16_t           : 1; //!< Резерв
} mfpu_out_sbi_symbol_b_t;

//! Выходные данные МФПУ об индицируемом тексте, сигнализаторах и кнопках, МКИО-1.1 (данные для СБИ)
typedef struct mfpu_out_sbi_sa_b_t {
   mfpu_out_sbi_id_b_t             id_b;             //!< Слово-идентификатор сообщения
   mfpu_out_sbi_button_fires_1_b_t button_fires_1_b; //!< Слово 1 состояния сигнализаторов и кода нажатой кнопки
   mfpu_out_sbi_button_fires_2_b_t button_fires_2_b; //!< Слово 2 состояния сигнализаторов и кода нажатой кнопки
   mfpu_out_sbi_symbol_b_t         symbols_b[28];    //!< Слова состояния символов одной строки на экране МФПУ
} mfpu_out_sbi_sa_b_t;

typedef struct mfpu_out_data_b_t{
    mfpu_out_sbi_sa_b_t data[12];
}mfpu_out_data_b_t;

typedef struct mfpu_out_b_t{
    size_t time;
    mfpu_out_data_b_t data; //! Выходные данные МФПУ об индицируемом тексте, сигнализаторах и кнопках, МКИО-1.1 (данные для СБИ)
}mfpu_out_b_t;

typedef struct frame_info{
    QString name;
    QString time;
    mfpu_out_data_b_t info;
}frame_info;

//! Таблица конвертирования ASCII в код шрифтов МФПУ
const uchar ascii_to_mfpu_font_table[2][0x100] = {
    {
      0x00, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20,
      0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20,
      0x20, 0x21, 0x22, 0xb9, 0x20, 0x25, 0x20, 0x27, 0x28, 0x29, 0x2a, 0x2b, 0x2c, 0x2d, 0x2e, 0x2f,
      0x30, 0x31, 0x32, 0x33, 0x34, 0x35, 0x36, 0x37, 0x38, 0x39, 0x3a, 0x3b, 0x3c, 0x3d, 0x3e, 0x3f,
      0x20, 0x41, 0x42, 0x43, 0x44, 0x45, 0x46, 0x47, 0x48, 0x49, 0x4a, 0x4b, 0x4c, 0x4d, 0x4e, 0x4f,
      0x50, 0x51, 0x52, 0x53, 0x54, 0x55, 0x56, 0x57, 0x58, 0x59, 0x5a, 0x28, 0x2f, 0x29, 0x20, 0xa4,
      0x27, 0x61, 0x62, 0x63, 0x64, 0x65, 0x66, 0x67, 0x68, 0x69, 0x6a, 0x6b, 0x6c, 0x6d, 0x6e, 0x6f,
      0x70, 0x71, 0x72, 0x73, 0x74, 0x75, 0x76, 0x77, 0x78, 0x79, 0x7a, 0x28, 0x2f, 0x29, 0x20, 0x20,
      0x80, 0x81, 0x82, 0x83, 0x84, 0x85, 0x86, 0x87, 0x88, 0x89, 0x8a, 0x8b, 0x8c, 0x8d, 0x8e, 0x8f,
      0xe0, 0xa1, 0xa6, 0xa8, 0xa9, 0x2d, 0x2d, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20,
      0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x45, 0x20, 0x20, 0x9d, 0x20, 0x20, 0x20, 0x20,
      0xb0, 0xb1, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x65, 0xb9, 0x20, 0x9e, 0x20, 0x20, 0x20, 0x20,
      0x41, 0xc1, 0x42, 0xc3, 0xc4, 0x45, 0xc6, 0xc7, 0xc8, 0xc9, 0x4b, 0xcb, 0xcc, 0x48, 0x4f, 0xcf,
      0x50, 0x43, 0x54, 0xd3, 0xd4, 0x58, 0xd6, 0xd7, 0xd8, 0xd9, 0xda, 0xdb, 0xdc, 0xdd, 0xde, 0xdf,
      0x61, 0xe1, 0xe2, 0xe3, 0xe4, 0x65, 0xe6, 0xe7, 0xe8, 0xe9, 0xea, 0xeb, 0xec, 0xed, 0x6f, 0xef,
      0x70, 0x63, 0xf2, 0x79, 0xf4, 0x78, 0xf6, 0xf7, 0xf8, 0xf9, 0xfa, 0xfb, 0xfc, 0xfd, 0xfe, 0xff
    }, {
      0x00, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20,
      0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20,
      0x20, 0x9b, 0x9f, 0xa3, 0x20, 0x9c, 0x20, 0xb6, 0xb4, 0xb5, 0xb7, 0xf0, 0xba, 0xf1, 0xb8, 0xee,
      0xc0, 0xc2, 0xc5, 0xca, 0xcd, 0xce, 0xd0, 0xd1, 0xd2, 0xd5, 0xbb, 0xbc, 0xf3, 0xbd, 0xf5, 0xbe,
      0x20, 0x10, 0x9a, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0a, 0x0b, 0x0c, 0x0d,
      0x0e, 0x0f, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17, 0x18, 0x19, 0xb4, 0xee, 0xb5, 0x20, 0xa5,
      0xb6, 0x10, 0x9a, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0a, 0x0b, 0x0c, 0x0d,
      0x0e, 0x0f, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17, 0x18, 0x19, 0xb4, 0xee, 0xb5, 0x20, 0x20,
      0x90, 0x91, 0x92, 0x93, 0x94, 0x95, 0x96, 0x97, 0x98, 0x99, 0x8a, 0x8b, 0x8c, 0x8d, 0x8e, 0x8f,
      0xa0, 0xa2, 0xa7, 0xa8, 0xa9, 0xf1, 0xf1, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20,
      0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x03, 0x20, 0x20, 0xb2, 0x20, 0x20, 0x20, 0x20,
      0xbf, 0xe5, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0xa3, 0x20, 0xb3, 0x20, 0x20, 0x20, 0x20,
      0x10, 0x1a, 0x9a, 0x1b, 0x1c, 0x03, 0x1d, 0x1e, 0x1f, 0x23, 0x09, 0x24, 0x0b, 0x06, 0x0d, 0x26,
      0x0e, 0x01, 0x13, 0x40, 0x5b, 0x17, 0x5c, 0x5d, 0x5e, 0x5f, 0x60, 0x7b, 0x7c, 0x7d, 0x7e, 0x7f,
      0x10, 0x1a, 0x9a, 0x1b, 0x1c, 0x03, 0x1d, 0x1e, 0x1f, 0x23, 0x09, 0x24, 0x0b, 0x06, 0x0d, 0x26,
      0x0e, 0x01, 0x13, 0x40, 0x5b, 0x17, 0x5c, 0x5d, 0x5e, 0x5f, 0x60, 0x7b, 0x7c, 0x7d, 0x7e, 0x7f
    }
};



#endif // UTILS_H
