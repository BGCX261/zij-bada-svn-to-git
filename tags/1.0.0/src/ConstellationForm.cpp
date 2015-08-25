/*
 * StellarForm.cpp
 *
 *  Created on: 04.03.2013
 *      Author: ddreval
 */

#include "ConstellationForm.h"

using namespace Osp::Ui;
using namespace Osp::Ui::Controls;
using namespace Osp::Graphics;
using namespace Osp::Base;
using namespace Osp::App;

ConstellationForm::ConstellationForm() {

}

ConstellationForm::~ConstellationForm() {
	// TODO Auto-generated destructor stub
}

bool
ConstellationForm::Initialize(void) {
	Construct(L"STELLAR_FORM");
	return true;
}

result
ConstellationForm::OnInitializing(void) {
	__pConstelList = new List();
	__pConstelList -> Construct(
			Rectangle(0, 0, 240, 360),
			LIST_STYLE_NORMAL,
			LIST_ITEM_SINGLE_TEXT, 15, 15, 200, 0);
	__pConstelList -> AddItemEventListener(*this);
	AddControl(*__pConstelList);
	return E_SUCCESS;
}

void
ConstellationForm::Update(void) {
	__pConstelList ->RemoveAllItems();
	Osp::Base::Collection::IEnumerator* constNames = SkyCanvas::getConstellations()->GetEnumeratorN();
	String emptyString;
	__pConstelList -> AddItem(&emptyString, &emptyString, null, null, null);
	while (constNames -> MoveNext() == E_SUCCESS) {
		String* constNameAbbr = (String*) constNames -> GetCurrent();
		String constName;
		AppResource* appResource = Application::GetInstance()->GetAppResource();
		appResource->GetString(*constNameAbbr, constName);
		__pConstelList -> AddItem(&constName, &constName, null, null, null);
	}
}

void
ConstellationForm::OnItemStateChanged(const Osp::Ui::Control &source, int index, int itemId, Osp::Ui::ItemStatus status) {
	AppLog("Index = %d", index);
	AppLog("ItemId  = %d", itemId);
	SkyCanvas::SelectConstellation(index-1);
	Osp::App::Application::GetInstance() -> SendUserEvent(CONSTELLATION_SELECTED, null);
}
