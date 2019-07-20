/******************************************************************************
 *  LineTracer.cpp (for LEGO Mindstorms EV3)
 *  Created on: 2015/01/26
 *  Implementation of the Class LineTracer
 *  Author: Kazuhiro Kawachi
 *  Copyright (c) 2015 Embedded Technology Software Design Robot Contest
 *****************************************************************************/

#include "LineTracer.h"

/**
 * コンストラクタ
 * @param lineMonitor     ライン判定
 * @param balancingWalker 倒立走行
 */
LineTracer::LineTracer(const LineMonitor* lineMonitor,
                       BalancingWalker* balancingWalker)
    : mLineMonitor(lineMonitor),
      mBalancingWalker(balancingWalker),
      mIsInitialized(false) {
}

/**
 * ライントレースする
 */
void LineTracer::run() {
    if (mIsInitialized == false) {
        mBalancingWalker->init();
        mIsInitialized = true;
    }

    // bool isOnLine = mLineMonitor->isOnLine();
    int diff = mLineMonitor->diff();
    // 走行体の向きを計算する
    int direction = calcDirection(diff);

    mBalancingWalker->setCommand(BalancingWalker::LOW, direction);

    // 倒立走行を行う
    mBalancingWalker->run();
}

/**
 * 走行体の向きを計算する
 * @param diff float:ライン上にいる割合を計算して方向を決める
 * チューニングパラメータ Kp, bias
 * @retval direction  ライン上の比例制御値
 */
int LineTracer::calcDirection(int diff) {
    const float Kp = 0.83;        // ライントレースの機敏さ 1:最大 
    const int bias = 0;            //　速度限界上昇：pi制御

    return Kp * diff + bias;
}
