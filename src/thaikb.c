/* -*- Mode: C; tab-width: 2; indent-tabs-mode: nil; c-basic-offset: 2 -*- */
/*
 *  Copyright (C) 2012 Theppitak Karoonboonyanan <theppitak@gmail.com>
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2, or (at your option)
 *  any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301 USA
 */

#include "thaikb.h"

#include <thai/tis.h>

#define N_KEYCODES  54
#define N_LEVELS    3

static const unsigned char tis_keycode_map[N_KEYCODES][N_LEVELS] =
{
  /* 0x00 */
  { 0x00,                 0x00,                 0x00, },
  { 0x00,                 0x00,                 0x00, },
  { TIS_YMBOL_BAHT,       TIS_LAKKHANGYAO,      TIS_LAKKHANGYAO, },
  { '/',                  TIS_THAI_DIGIT_ONE,   TIS_THAI_DIGIT_ONE, },
  { '-',                  TIS_THAI_DIGIT_TWO,   TIS_THAI_DIGIT_TWO, },
  { TIS_PHO_SAMPHAO,      TIS_THAI_DIGIT_THREE, TIS_THAI_DIGIT_THREE, },
  { TIS_THO_THUNG,        TIS_THAI_DIGIT_FOUR,  TIS_THAI_DIGIT_FOUR, },
  { TIS_SARA_U,           TIS_SARA_UU,          TIS_SARA_UU, },
  { TIS_SARA_UE,          TIS_YAMAKKAN,         TIS_YAMAKKAN, },
  { TIS_KHO_KHWAI,        TIS_THAI_DIGIT_FIVE,  TIS_THAI_DIGIT_FIVE, },
  { TIS_TO_TAO,           TIS_THAI_DIGIT_SIX,   TIS_THAI_DIGIT_SIX, },
  { TIS_CHO_CHAN,         TIS_THAI_DIGIT_SEVEN, TIS_THAI_DIGIT_SEVEN, },
  { TIS_KHO_KHAI,         TIS_THAI_DIGIT_EIGHT, TIS_THAI_DIGIT_EIGHT, },
  { TIS_CHO_CHANG,        TIS_THAI_DIGIT_NINE,  TIS_THAI_DIGIT_NINE, },
  { 0x08,                 0x08,                 0x08, },
  { 0x09,                 0x09,                 0x09, },
  /* 0x10 */
  { TIS_MAIYAMOK,         TIS_THAI_DIGIT_ZERO,  TIS_THAI_DIGIT_ZERO, },
  { TIS_SARA_AI_MAIMALAI, '"',                  '"', },
  { TIS_SARA_AM,          TIS_DO_CHADA,         TIS_DO_CHADA, },
  { TIS_PHO_PHAN,         TIS_THO_NANGMONTHO,   TIS_THO_NANGMONTHO, },
  { TIS_SARA_A,           TIS_THO_THONG,        TIS_THO_THONG, },
  { TIS_MAI_HAN_AKAT,     TIS_NIKHAHIT,         TIS_NIKHAHIT, },
  { TIS_SARA_II,          TIS_MAI_TRI,          TIS_MAI_TRI, },
  { TIS_RO_RUA,           TIS_NO_NEN,           TIS_NO_NEN, },
  { TIS_NO_NU,            TIS_PAIYANNOI,        TIS_ANGKHANKHU, },
  { TIS_YO_YAK,           TIS_YO_YING,          TIS_YO_YING, },
  { TIS_BO_BAIMAI,        TIS_THO_THAN,         TIS_THO_THAN, },
  { TIS_LO_LING,          ',',                  ',', },
  { 0x0d,                 0x0d,                 0x0d, },
  { 0x00,                 0x00,                 0x00, },
  { TIS_FO_FAN,           TIS_RU,               TIS_RU, },
  { TIS_HO_HIP,           TIS_KHO_RAKHANG,      TIS_KHO_RAKHANG, },
  /* 0x20 */
  { TIS_KO_KAI,           TIS_TO_PATAK,         TIS_TO_PATAK, },
  { TIS_DO_DEK,           TIS_SARA_O,           TIS_SARA_O, },
  { TIS_SARA_E,           TIS_CHO_CHOE,         TIS_CHO_CHOE, },
  { TIS_MAI_THO,          TIS_MAITAIKHU,        TIS_MAITAIKHU, },
  { TIS_MAI_EK,           TIS_MAI_CHATTAWA,     TIS_MAI_CHATTAWA, },
  { TIS_SARA_AA,          TIS_SO_RUSI,          TIS_SO_RUSI, },
  { TIS_SO_SUA,           TIS_SO_SALA,          TIS_SO_SALA, },
  { TIS_WO_WAEN,          TIS_SO_SO,            TIS_SO_SO, },
  { TIS_NGO_NGU,          '.',                  '.', },
  { TIS_FONGMAN,          TIS_KHOMUT,           TIS_KHOMUT, },
  { 0x00,                 0x00,                 0x00, },
  { TIS_KHO_KHON,         TIS_KHO_KHUAT,        TIS_KHO_KHUAT, },
  { TIS_PHO_PHUNG,        '(',                  '(', },
  { TIS_PO_PLA,           ')',                  ')', },
  { TIS_SARA_AE,          TIS_CHO_CHING,        TIS_CHO_CHING, },
  { TIS_O_ANG,            TIS_HO_NOKHUK,        TIS_HO_NOKHUK, },
  /* 0x30 */
  { TIS_SARA_I,           TIS_PHINTHU,          TIS_PHINTHU, },
  { TIS_SARA_UEE,         TIS_THANTHAKHAT,      TIS_THANTHAKHAT, },
  { TIS_THO_THAHAN,       '?',                  '?', },
  { TIS_MO_MA,            TIS_THO_PHUTHAO,      TIS_THO_PHUTHAO, },
  { TIS_SARA_AI_MAIMUAN,  TIS_LO_CHULA,         TIS_LO_CHULA, },
  { TIS_FO_FA,            TIS_LU,               TIS_LU, },
};

static const unsigned char ketmanee_keycode_map[N_KEYCODES][N_LEVELS] =
{
  /* 0x00 */
  { 0x00,                 0x00,                 0x00, },
  { 0x00,                 0x00,                 0x00, },
  { TIS_LAKKHANGYAO,      '+',                  '+', },
  { '/',                  TIS_THAI_DIGIT_ONE,   TIS_THAI_DIGIT_ONE, },
  { '-',                  TIS_THAI_DIGIT_TWO,   TIS_THAI_DIGIT_TWO, },
  { TIS_PHO_SAMPHAO,      TIS_THAI_DIGIT_THREE, TIS_THAI_DIGIT_THREE, },
  { TIS_THO_THUNG,        TIS_THAI_DIGIT_FOUR,  TIS_THAI_DIGIT_FOUR, },
  { TIS_SARA_U,           TIS_SARA_UU,          TIS_SARA_UU, },
  { TIS_SARA_UE,          TIS_YMBOL_BAHT,       TIS_YMBOL_BAHT, },
  { TIS_KHO_KHWAI,        TIS_THAI_DIGIT_FIVE,  TIS_THAI_DIGIT_FIVE, },
  { TIS_TO_TAO,           TIS_THAI_DIGIT_SIX,   TIS_THAI_DIGIT_SIX, },
  { TIS_CHO_CHAN,         TIS_THAI_DIGIT_SEVEN, TIS_THAI_DIGIT_SEVEN, },
  { TIS_KHO_KHAI,         TIS_THAI_DIGIT_EIGHT, TIS_THAI_DIGIT_EIGHT, },
  { TIS_CHO_CHANG,        TIS_THAI_DIGIT_NINE,  TIS_THAI_DIGIT_NINE, },
  { 0x08,                 0x08,                 0x08, },
  { 0x09,                 0x09,                 0x09, },
  /* 0x10 */
  { TIS_MAIYAMOK,         TIS_THAI_DIGIT_ZERO,  TIS_THAI_DIGIT_ZERO, },
  { TIS_SARA_AI_MAIMALAI, '"',                  '"', },
  { TIS_SARA_AM,          TIS_DO_CHADA,         TIS_DO_CHADA, },
  { TIS_PHO_PHAN,         TIS_THO_NANGMONTHO,   TIS_THO_NANGMONTHO, },
  { TIS_SARA_A,           TIS_THO_THONG,        TIS_THO_THONG, },
  { TIS_MAI_HAN_AKAT,     TIS_NIKHAHIT,         TIS_NIKHAHIT, },
  { TIS_SARA_II,          TIS_MAI_TRI,          TIS_MAI_TRI, },
  { TIS_RO_RUA,           TIS_NO_NEN,           TIS_NO_NEN, },
  { TIS_NO_NU,            TIS_PAIYANNOI,        TIS_PAIYANNOI, },
  { TIS_YO_YAK,           TIS_YO_YING,          TIS_YO_YING, },
  { TIS_BO_BAIMAI,        TIS_THO_THAN,         TIS_THO_THAN, },
  { TIS_LO_LING,          ',',                  ',', },
  { 0x0d,                 0x0d,                 0x0d, },
  { 0x00,                 0x00,                 0x00, },
  { TIS_FO_FAN,           TIS_RU,               TIS_RU, },
  { TIS_HO_HIP,           TIS_KHO_RAKHANG,      TIS_KHO_RAKHANG, },
  /* 0x20 */
  { TIS_KO_KAI,           TIS_TO_PATAK,         TIS_TO_PATAK, },
  { TIS_DO_DEK,           TIS_SARA_O,           TIS_SARA_O, },
  { TIS_SARA_E,           TIS_CHO_CHOE,         TIS_CHO_CHOE, },
  { TIS_MAI_THO,          TIS_MAITAIKHU,        TIS_MAITAIKHU, },
  { TIS_MAI_EK,           TIS_MAI_CHATTAWA,     TIS_MAI_CHATTAWA, },
  { TIS_SARA_AA,          TIS_SO_RUSI,          TIS_SO_RUSI, },
  { TIS_SO_SUA,           TIS_SO_SALA,          TIS_SO_SALA, },
  { TIS_WO_WAEN,          TIS_SO_SO,            TIS_SO_SO, },
  { TIS_NGO_NGU,          '.',                  '.', },
  { '_',                  '%',                  '%', },
  { 0x00,                 0x00,                 0x00, },
  { TIS_KHO_KHUAT,        TIS_KHO_KHON,         TIS_KHO_KHON, },
  { TIS_PHO_PHUNG,        '(',                  '(', },
  { TIS_PO_PLA,           ')',                  ')', },
  { TIS_SARA_AE,          TIS_CHO_CHING,        TIS_CHO_CHING, },
  { TIS_O_ANG,            TIS_HO_NOKHUK,        TIS_HO_NOKHUK, },
  /* 0x30 */
  { TIS_SARA_I,            TIS_PHINTHU,         TIS_PHINTHU, },
  { TIS_SARA_UEE,          TIS_THANTHAKHAT,     TIS_THANTHAKHAT, },
  { TIS_THO_THAHAN,        '?',                 '?', },
  { TIS_MO_MA,             TIS_THO_PHUTHAO,     TIS_THO_PHUTHAO, },
  { TIS_SARA_AI_MAIMUAN,   TIS_LO_CHULA,        TIS_LO_CHULA, },
  { TIS_FO_FA,             TIS_LU,              TIS_LU, },
};

static const unsigned char pattachote_keycode_map[N_KEYCODES][N_LEVELS] =
{
  /* 0x00 */
  { 0x00,                 0x00,                 0x00, },
  { 0x00,                 0x00,                 0x00, },
  { '=',                  '+',                  '+', },
  { TIS_THAI_DIGIT_TWO,   '"',                  '"', },
  { TIS_THAI_DIGIT_THREE, '/',                  '/', },
  { TIS_THAI_DIGIT_FOUR,  ',',                  ',', },
  { TIS_THAI_DIGIT_FIVE,  '?',                  '?', },
  { TIS_SARA_UU,          TIS_SARA_U,           TIS_SARA_U, },
  { TIS_THAI_DIGIT_SEVEN, '_',                  '_', },
  { TIS_THAI_DIGIT_EIGHT, '.',                  '.', },
  { TIS_THAI_DIGIT_NINE,  '(',                  '(', },
  { TIS_THAI_DIGIT_ZERO,  ')',                  ')', },
  { TIS_THAI_DIGIT_ONE,   '-',                  '-', },
  { TIS_THAI_DIGIT_SIX,   '%',                  '%', },
  { 0x08,                 0x08,                 0x08, },
  { 0x09,                 0x09,                 0x09, },
  /* 0x10 */
  { TIS_MAITAIKHU,        TIS_MAI_TRI,          TIS_MAI_TRI, },
  { TIS_TO_TAO,           TIS_RU,               TIS_RU, },
  { TIS_YO_YAK,           TIS_MAIYAMOK,         TIS_MAIYAMOK, },
  { TIS_O_ANG,            TIS_YO_YING,          TIS_YO_YING, },
  { TIS_RO_RUA,           TIS_SO_RUSI,          TIS_SO_RUSI, },
  { TIS_MAI_EK,           TIS_SARA_UE,          TIS_SARA_UE, },
  { TIS_DO_DEK,           TIS_FO_FA,            TIS_FO_FA, },
  { TIS_MO_MA,            TIS_SO_SO,            TIS_SO_SO, },
  { TIS_WO_WAEN,          TIS_THO_THUNG,        TIS_THO_THUNG, },
  { TIS_SARA_AE,          TIS_THO_PHUTHAO,      TIS_THO_PHUTHAO, },
  { TIS_SARA_AI_MAIMUAN,  TIS_PAIYANNOI,        TIS_PAIYANNOI, },
  { TIS_CHO_CHOE,         TIS_LU,               TIS_LU, },
  { 0x0d,                 0x0d,                 0x0d, },
  { 0x00,                 0x00,                 0x00, },
  { TIS_MAI_THO,          TIS_MAI_CHATTAWA,     TIS_MAI_CHATTAWA, },
  { TIS_THO_THAHAN,       TIS_THO_THONG,        TIS_THO_THONG, },
  /* 0x20 */
  { TIS_NGO_NGU,          TIS_SARA_AM,          TIS_SARA_AM, },
  { TIS_KO_KAI,           TIS_NO_NEN,           TIS_NO_NEN, },
  { TIS_MAI_HAN_AKAT,     TIS_THANTHAKHAT,      TIS_THANTHAKHAT, },
  { TIS_SARA_II,          TIS_SARA_UEE,         TIS_SARA_UEE, },
  { TIS_SARA_AA,          TIS_PHO_PHUNG,        TIS_PHO_PHUNG, },
  { TIS_NO_NU,            TIS_CHO_CHANG,        TIS_CHO_CHANG, },
  { TIS_SARA_E,           TIS_SARA_O,           TIS_SARA_O, },
  { TIS_SARA_AI_MAIMALAI, TIS_KHO_RAKHANG,      TIS_KHO_RAKHANG, },
  { TIS_KHO_KHAI,         TIS_THO_NANGMONTHO,   TIS_THO_NANGMONTHO, },
  { '_',                  TIS_YMBOL_BAHT,       TIS_YMBOL_BAHT, },
  { 0x00,                 0x00,                 0x00, },
  { TIS_PHINTHU,          TIS_NIKHAHIT,         TIS_NIKHAHIT, },
  { TIS_BO_BAIMAI,        TIS_DO_CHADA,         TIS_DO_CHADA, },
  { TIS_PO_PLA,           TIS_TO_PATAK,         TIS_TO_PATAK, },
  { TIS_LO_LING,          TIS_THO_THAN,         TIS_THO_THAN, },
  { TIS_HO_HIP,           TIS_PHO_SAMPHAO,      TIS_PHO_SAMPHAO, },
  /* 0x30 */
  { TIS_SARA_I,           TIS_MAI_HAN_AKAT,     TIS_MAI_HAN_AKAT, },
  { TIS_KHO_KHWAI,        TIS_SO_SALA,          TIS_SO_SALA, },
  { TIS_SO_SUA,           TIS_HO_NOKHUK,        TIS_HO_NOKHUK, },
  { TIS_SARA_A,           TIS_FO_FAN,           TIS_FO_FAN, },
  { TIS_CHO_CHAN,         TIS_CHO_CHING,        TIS_CHO_CHING, },
  { TIS_PHO_PHAN,         TIS_LO_CHULA,         TIS_LO_CHULA, },
};

static const unsigned char (* const thai_keycode_map[])[N_LEVELS] =
{
  ketmanee_keycode_map,
  pattachote_keycode_map,
  tis_keycode_map
};

unsigned char
thai_map_keycode (ThaiKBMap map, int keycode, int shift_lv)
{
  if (map > THAI_KB_TIS820_2538 || shift_lv >= N_LEVELS
      || keycode >= N_KEYCODES)
    return 0;

  return thai_keycode_map[map][keycode][shift_lv];
}

/*
vi:ts=2:ai:expandtab
*/
