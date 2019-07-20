/******************************************************************************
 *  LineMonitor.cpp (for LEGO Mindstorms EV3)
 *  Created on: 2015/01/25
 *  Definition of the Class LineMonitor
 *  Author: Kazuhiro Kawachi
 *  Copyright (c) 2015 Embedded Technology Software Design Robot Contest
 *****************************************************************************/

#include "LineMonitor.h"

// 定数宣言
const int8_t LineMonitor::INITIAL_THRESHOLD = 10;  // 黒色の光センサ値

/**
 * コンストラクタ
 * @param colorSensor カラーセンサ
 */
LineMonitor::LineMonitor(const ev3api::ColorSensor& colorSensor)
    : mColorSensor(colorSensor),
      mThreshold(INITIAL_THRESHOLD) {
}

//      光センサからの取得値を見て差を計算する
int LineMonitor::diff() const{
    return mColorSensor.getBrightness() - mThreshold;
}

/**
 * ライン閾値を設定する
 * @param threshold ライン閾値
 */
void LineMonitor::setThreshold(int8_t threshold) {
    mThreshold = threshold;
}
