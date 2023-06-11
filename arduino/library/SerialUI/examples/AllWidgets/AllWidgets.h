
#ifndef _AllWidgets_AllWidgets_h
#define _AllWidgets_AllWidgets_h
/*
 * AllWidgets.h -- part of the AllWidgets project.
 * Declarations for everything that was generated...
 * Pat Deegan
 * Psychogenic.com 
 * 
 * Copyright (C) 2019 Pat Deegan
 * 
 * Generated by DruidBuilder [https://devicedruid.com/], 
 * as part of project "b4cf0e8f5cb24a839ec218119f68cfc0lEUPnNbYtz",
 * aka AllWidgets.
 * 
 * Druid4Arduino, Device Druid, Druid Builder, the builder 
 * code brewery and its wizards, SerialUI and supporting 
 * libraries, as well as the generated parts of this program 
 * are 
 *            Copyright (C) 2013-2018 Pat Deegan 
 * [https://psychogenic.com/ | https://inductive-kickback.com/]
 * and distributed under the terms of their respective licenses.
 * See https://devicedruid.com for details.
 * 
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. 
 * THE ENTIRE RISK AS TO THE QUALITY AND PERFORMANCE OF THE 
 * PROGRAM IS WITH YOU. SHOULD THE PROGRAM PROVE DEFECTIVE, 
 * YOU ASSUME THE COST OF ALL NECESSARY SERVICING, REPAIR OR
 * CORRECTION.
 * 
 * Keep in mind that there is no warranty and you are solely 
 * responsible for the use of all these cool tools.
 * 
 * Play safe, have fun.
 * 
 */



/* we need the SerialUI lib */
#include <SerialUI.h>


/* MySUI
 * Our SerialUI Instance, through which we can send/receive
 * data from users.
 */ 
extern SUI::SerialUI MySUI;







// "heartbeat" function, called periodically while connected
void CustomHeartbeatCode(); 

/* ********* callbacks and validation functions ********* */



/* *** Main Menu *** */
namespace MainMenu {

void ColourChanged();

void doRunMe();

void doAnotherCommand();

void OnOrOffChanged();

void HowMuchChanged();

void ShortListChanged();

void LongerListChanged();

void RandomNumberChanged();

void SomeTextChanged();

void TimeOfDayChanged();

void ADateAndTimeChanged();

void EventFieldChanged();



/* *** Main Menu -> Menu 1 *** */
namespace Menu1 {

} /* namespace Menu1 */



/* *** Main Menu -> Menu 2 *** */
namespace Menu2 {

} /* namespace Menu2 */



/* *** Main Menu -> Menu 3 *** */
namespace Menu3 {

} /* namespace Menu3 */



/* *** Main Menu -> Group A *** */
namespace GroupA {

void ASwitchChanged();

void SomeNumberChanged();

void CharsChanged();

void RangerChanged();

} /* namespace GroupA */



/* *** Main Menu -> Group B *** */
namespace GroupB {

void NumChanged();

void ATimeOfDayChanged();

void ASwitch2Changed();

void doDoit();

} /* namespace GroupB */



/* *** Main Menu -> Group C *** */
namespace GroupC {

void PiChanged();

void IntensityChanged();



/* *** Main Menu -> Group C -> Subsub *** */
namespace Subsub {

void doClickMe();

} /* namespace Subsub */

} /* namespace GroupC */



/* *** Main Menu -> Another Group *** */
namespace AnotherGroup {

void NameChanged();

void BigDateChanged();

void VetChanged();

} /* namespace AnotherGroup */

} /* namespace MainMenu */



/* MyTracked
 * A structure to hold the tracked variables, which will 
 * automatically update the druid UI when modified by this 
 * program.
 */
typedef struct MyTrackedVarsContainerStruct{
	
	SerialUI::Tracked::Toggle Lights;
	SerialUI::Tracked::Integer Integer;
	SerialUI::Tracked::Float Decimal;
	SerialUI::Tracked::Integer Members;
	SerialUI::Tracked::String ChatLog;
	SerialUI::Tracked::Toggle Heat;
	// constructor to set sane startup vals
	MyTrackedVarsContainerStruct() : 
	Lights(SUI_STR("Lights"),false),
	Integer(SUI_STR("Integer"),0),
	Decimal(SUI_STR("Decimal"),0),
	Members(SUI_STR("Members"),0),
	ChatLog(SUI_STR("Chat Log"),""),
	Heat(SUI_STR("Heat"),false)
	{}
} MyTrackedVarsContainerSt;

extern MyTrackedVarsContainerSt MyTracked;

typedef struct MyListcycleStruct {
  SerialUI::Menu::Item::Request::Toggle OnOrOff;
  SerialUI::Menu::Item::Request::String SomeText;
  SerialUI::Menu::Item::Request::Long SomeNumber;

  SerialUI::Menu::Item::Request::Color ListCol;
  MyListcycleStruct() : 
    OnOrOff(false,SUI_STR("On or Off"),SUI_STR("a toggle switch"),MainMenu::OnOrOffChanged),
    SomeText("",SUI_STR("Some Text"),SUI_STR("a text value field"),
      request_inputstring_maxlen,MainMenu::SomeTextChanged),
    SomeNumber(0,SUI_STR("Some number"),SUI_STR("a number"),MainMenu::GroupA::SomeNumberChanged),
    ListCol(0,SUI_STR("Hue"),SUI_STR("Colour of Dev"),MainMenu::ColourChanged)
    {}
} MyListcycle;

extern MyListcycle ListCycleItems[8];

typedef struct MySimpleListStruct {

  SerialUI::Menu::Item::Request::Color Col;
  MySimpleListStruct() :
  Col(0,SUI_STR("Colour"),SUI_STR("Colour of LED"),MainMenu::ColourChanged)
  {}
} MySimpleList;

extern MySimpleList SimpleListItems[5];

    




/*
 * The container for MyInputs, which
 * holds all the variables for the various inputs.
 */
typedef struct MyInputsContainerStruct {
	
	SerialUI::Menu::Item::Request::Toggle OnOrOff;
	SerialUI::Menu::Item::Request::BoundedLong HowMuch;
	SerialUI::Menu::Item::Request::OptionsList ShortList;
	SerialUI::Menu::Item::Request::OptionsList LongerList;
	SerialUI::Menu::Item::Request::Long RandomNumber;
	SerialUI::Menu::Item::Request::String SomeText;
	SerialUI::Menu::Item::Request::Time TimeOfDay;
	SerialUI::Menu::Item::Request::DateTime ADateAndTime;
	SerialUI::Menu::Item::Request::Event EventField;
	SerialUI::Menu::Item::Request::Toggle ASwitch;
	SerialUI::Menu::Item::Request::Long SomeNumber;
	SerialUI::Menu::Item::Request::String Chars;
	SerialUI::Menu::Item::Request::BoundedLong Ranger;
	SerialUI::Menu::Item::Request::Long Num;
	SerialUI::Menu::Item::Request::Time ATimeOfDay;
	SerialUI::Menu::Item::Request::Toggle ASwitch2;
	SerialUI::Menu::Item::Request::Float Pi;
	SerialUI::Menu::Item::Request::BoundedLong Intensity;
	SerialUI::Menu::Item::Request::String Name;
	SerialUI::Menu::Item::Request::DateTime BigDate;
	SerialUI::Menu::Item::Request::Event Vet;
  SerialUI::Menu::Item::Request::Color GroupCol;
	// constructor to set sane startup vals
	MyInputsContainerStruct() : 
		OnOrOff(false,SUI_STR("On or Off"),SUI_STR("a toggle switch"),MainMenu::OnOrOffChanged),
		HowMuch(0,SUI_STR("How much"),SUI_STR("A range slider"),1,50,MainMenu::HowMuchChanged),
		ShortList(1,SUI_STR("Short list"),SUI_STR("A selector with few options"),SUI_STR("One"),SUI_STR("Two"),SUI_STR("Three"),NULL,NULL,NULL,MainMenu::ShortListChanged),
		LongerList(1,SUI_STR("Longer List"),SUI_STR("A list with many options"),SUI_STR("Option 1"),SUI_STR("Option 2"),SUI_STR("Another"),SUI_STR("Yet Agai"),SUI_STR("Whoopie"),NULL,MainMenu::LongerListChanged),
		RandomNumber(0,SUI_STR("Random number"),SUI_STR("a numeric value field"),MainMenu::RandomNumberChanged),
		SomeText("",SUI_STR("Some Text"),SUI_STR("a text value field"),request_inputstring_maxlen,MainMenu::SomeTextChanged),
		TimeOfDay(16 /*hour*/, 30 /*min*/, 59 /*sec*/,SUI_STR("Time of day"),SUI_STR("enter the time"),MainMenu::TimeOfDayChanged),
		ADateAndTime(1521040146 /*epoch*/,SUI_STR("A date and time"),SUI_STR("Datetime entry field"),MainMenu::ADateAndTimeChanged),
		EventField(18 /*start hour*/, 0 /*min*/, 0 /*sec*/, 120 /*num mins*/ ,SUI_STR("Event field"),SUI_STR("An event entry form"),MainMenu::EventFieldChanged),
		ASwitch(false,SUI_STR("A switch"),SUI_STR("Some value"),MainMenu::GroupA::ASwitchChanged),
		SomeNumber(0,SUI_STR("Some number"),SUI_STR("a number"),MainMenu::GroupA::SomeNumberChanged),
		Chars("",SUI_STR("Chars"),SUI_STR("A char string"),request_inputstring_maxlen,MainMenu::GroupA::CharsChanged),
		Ranger(0,SUI_STR("Ranger"),SUI_STR("range value"),1,50,MainMenu::GroupA::RangerChanged),
		Num(0,SUI_STR("num"),SUI_STR("A number"),MainMenu::GroupB::NumChanged),
		ATimeOfDay(16 /*hour*/, 30 /*min*/, 59 /*sec*/,SUI_STR("A time of day"),SUI_STR("time value"),MainMenu::GroupB::ATimeOfDayChanged),
		ASwitch2(false,SUI_STR("A switch"),SUI_STR("some switch"),MainMenu::GroupB::ASwitch2Changed),
		Pi(0,SUI_STR("Pi"),SUI_STR("The value of pi"),MainMenu::GroupC::PiChanged),
		Intensity(0,SUI_STR("Intensity"),SUI_STR("How strong"),1,500,MainMenu::GroupC::IntensityChanged),
		Name("",SUI_STR("Name"),SUI_STR("a string field"),request_inputstring_maxlen,MainMenu::AnotherGroup::NameChanged),
		BigDate(1521040146 /*epoch*/,SUI_STR("Big Date"),SUI_STR("a datetime"),MainMenu::AnotherGroup::BigDateChanged),
		Vet(18 /*start hour*/, 0 /*min*/, 0 /*sec*/, 120 /*num mins*/ ,SUI_STR("Vet"),
		  SUI_STR("an event, going to vet"),MainMenu::AnotherGroup::VetChanged),
		GroupCol(0,SUI_STR("Colour"),SUI_STR("Colour of LED"),MainMenu::ColourChanged)
  {}
} MyInputsContainerSt;

extern MyInputsContainerSt MyInputs;



/*
 * This container holds all the tracked variable views.
 */
typedef struct MyTrackedViewsContainerStruct {
	
	SerialUI::Menu::Item::View::CurrentValue Current;
	SerialUI::Menu::Item::View::LineBasic Graph;
	SerialUI::Menu::Item::View::PieChart Portions;
	SerialUI::Menu::Item::View::HistoryLog TheLog;
	// constructor to set sane startup vals
	MyTrackedViewsContainerStruct() : 
		Current(SUI_STR("Current"),SUI_STR("Current values table")),
		Graph(SUI_STR("Graph"),SUI_STR("A linear graph")),
		Portions(SUI_STR("Portions"),SUI_STR("A pie chart view")),
		TheLog(SUI_STR("The Log"),SUI_STR("A textual log"))
	{}
} MyTrackedViewsContainerSt;
extern MyTrackedViewsContainerSt MyViews;



/* ***** SetupSerialUI: where we'll be setting up menus and such **** */
bool SetupSerialUI();


#define DIE_HORRIBLY(msg)	for(;;){ MySUI.println(msg); MySUI.checkForUser(); delay(1000); }


#endif