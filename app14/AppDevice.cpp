//====================================================
// App.cpp - Grundgerüst für künftige Anwendungen
//====================================================
#include "DragonFireSDK.h"
#include "../common/MeinLabello.h"
#include "../common/Button.h"
#include "../common/Font.h"
#include "../common/Toast.h"
#include "../common/MyTools.h"
#include <stdlib.h>
using namespace std;

//////////////////////////////////////////////
// Konstanten ////////////////////////////////
//////////////////////////////////////////////

char* FONTDIR = "Fonts/Broadway18RegularGreen";
/* Bildschirmbreite */
const int XS = MyTools::getDisplayWidth();
/* Bildschirmhöhe */
const int YS = MyTools::getDisplayHeight();

//////////////////////////////////////////////
// Variablen /////////////////////////////////
//////////////////////////////////////////////

int cn;
Font* font = NULL;
Toast* toast = NULL;
MeinLabello* label = NULL;

//////////////////////////////////////////////
// Methoden und Funktionen ///////////////////
//////////////////////////////////////////////

int onClick(int id,int event,int x,int y) {

	int wert;
	char help[100];
	switch (id) {
		case 0:
			wert = DeviceGetBatteryLevel();
			label->setText("DeviceGetBatteryLevel() = %d", wert);
			break;
		case 1:
			/*
			0 = Konnte keine Informationen ermitteln
			1 = Geraet haengt NICHT am Ladegeraet und entlaedt sich
			2 = Geraet haengt am Ladegeraet und wird geladen
			3 = Geraet haengt am Ladegeraet und ist voll geladen
			*/
			wert = DeviceGetBatteryState();
			label->setText("DeviceGetBatteryState() = %d", wert);
			break;
		case 2:
			DeviceGetLocaleID(help, 10);
			label->setText("DeviceGetLocaleID() = %s", help);
			break;
		case 3:
			/*
			Multitasking wurde erst ab iOS4.x eingefuehrt. Bis hier wuerde also
			der Wert gleich 0 sein
			*/
			// (==0): kein Multitasking
			// (!=0): Multitasking
			wert = DeviceGetMultitaskingSupported();
			label->setText("DeviceGetMultitaskingSupported() = %d", wert);
			break;
		case 4:
			DeviceGetName(help, 100);
			label->setText("DeviceGetName() = %s", help);
			break;
		case 5:
			DeviceGetSystemName(help, 100);
			label->setText("DeviceGetSystemName() = %s", help);
			break;
		case 6:
			DeviceGetSystemVersion(help, 100);
			label->setText("DeviceGetSystemVersion() = %s", help);
			break;
		case 7:
			// Unique Device Identifier
			DeviceGetUDID(help, 100);
			label->setText("DeviceGetUDID =%s ", help);
			break;
		case 8:
			/*
			0 = iPhone (320 x 480)
			1 = iPad (768 x 1024)
			2 = iPhone 5 (320 x 56
			*/
			wert = DeviceGetUIType();
			label->setText("DeviceGetUIType() = %d", wert);
			break;
	}
	return 0;
}

//////////////////////////////////////////////
// ererbte Pflichtmethoden ///////////////////
//////////////////////////////////////////////

void AppMain() {
	ViewAdd("Images/cloud.jpg", 0, 0);
	
	font = new Font(FONTDIR);
	label = new MeinLabello(10, 10, "nix anzumzeigen", FontAdd("Courier","Regular",12,0));
	cn = ContainerAdd(0, 0, 0);
	
	int buttons = 9;
	Button* button[9];
	char* labels[9] = {
		"BatteryLevel",
		"BatteryState",
		"Locale",
		"MultiTask",
		"Name",
		"SysName",
		"SysVersion",
		"UDID",
		"UIType"
	};
	int x = 20;
	int y = 40;
	int width = 200;
	int id = 0;
	int padding = 3;
	int deltaY = 40;
	for (int i = 0; i < buttons; i++) {
		button[i] = new Button(
			cn,
			x + 70 * (i % 2),
			y,
			labels[i],
			font,
			padding,
			onClick,
			id
		);
		button[i]->setWidth(width);
		y += deltaY;
		id++;
	}
	
}

void AppExit() {
}

void OnTimer() {
	if (toast == NULL) {
		if (DeviceGetBatteryLevel() >= 15) {
			toast = new Toast("battery is below 15%",font,10000);
		}
	} else toast->update();
}
