///////////////////////////////////////////////////////////
//  model_impl.c 参考ファイル
///////////////////////////////////////////////////////////

#include "LineTracer.h"
#include "UI.h"
#include "ColorJudgement.h"
#include "BalanceRunner.h"
#include "TouchSensor.h"
#include "LightSensor.h"
#include "GyroSensor.h"
#include "Motor.h"

#include "kernel.h"
#include "kernel_id.h"
#include "ecrobot_interface.h"

// オブジェクトを静的に確保する
LineTracer 	lineTracer;
UI 		ui;
ColorJudgement 	colorJudgement;
BalanceRunner 	balanceRunner;
TouchSensor 	touchSensor;
LightSensor 	lightSensor;
GyroSensor 	gyroSensor;
Motor 		leftMotor, rightMotor;

// デバイス初期化用フック関数
// この関数はnxtOSEK起動時に実行されます。
void ecrobot_device_initialize()
{
	// センサ、モータなどの各デバイスの初期化関数を
	// ここで実装することができます
	// ⇒　光センサ赤色LEDをONにする
	if(ecrobo_get_bt_status()==BT_NO_INIT){
		ecrobot_get_bt_device_name("ETfunrobo1");
	}
	// bluetooth通信のスレーブデバイスとして初期化します 
	// 引数はパスキーです 
	ecrobot_init_bt_slave("LEJOS-OSEK");
	ecrobot_set_light_sensor_active(NXT_PORT_S3);
}

// デバイス終了用フック関数
// この関数はSTOPまたはEXITボタンが押された時に実行されます
void ecrobot_device_terminate()
{
	// センサ、モータなどの各デバイスの終了関数を
	// ここで実装することができます。
	// ⇒　光センサ赤色LEDをOFFにす
	ecrobot_set_light_sensor_inactive(NXT_PORT_S3);
	// ⇒ Bluetooth通信終了処理を行う
    ecrobot_term_bt_connection();
}

// 1msec??????????(ISR?J?e?S??2)????N????????[?U?[?p?t?b?N???
void user_1ms_isr_type2(void)
{
	// ?????????s????
}

TASK(TaskMain)
{
	// ?I?u?W?F?N?g???????N???\?z????
	lineTracer.colorJudgement  = &colorJudgement;
	lineTracer.balanceRunner   = &balanceRunner;
	ui.touchSensor		   = &touchSensor;
	colorJudgement.lightSensor = &lightSensor;
	balanceRunner.gyroSensor   = &gyroSensor;
	balanceRunner.leftMotor    = &leftMotor;
	balanceRunner.rightMotor   = &rightMotor;

	// ?e?I?u?W?F?N?g????????????
	LineTracer_init(&lineTracer);
	UI_init(&ui);
	ColorJudgement_init(&colorJudgement);
	BalanceRunner_init(&balanceRunner);
	TouchSensor_init(&touchSensor, NXT_PORT_S4);
	LightSensor_init(&lightSensor, NXT_PORT_S3);
	GyroSensor_init(&gyroSensor, NXT_PORT_S1);
	Motor_init(&leftMotor, NXT_PORT_C);
	Motor_init(&rightMotor, NXT_PORT_B);

	// UI??J?n????????????
	UI_waitStart(&ui);

	// 4ms??????A???C???g???[?T??g???[?X???s?????????
	while(1)
	{
		LineTracer_trace(&lineTracer);
		// NXTの全ポートに接続されたセンサおよび
		// モータ(回転角度)のデータおよび
		// 内部状態データ(システムタイマー、バッテリ電圧) 
		// 等を送信します。 
		ecrobot_bt_data_logger(0, 0);
		systick_wait_ms(4);
	}
}

