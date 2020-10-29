#pragma once

#include <QtCore/qglobal.h>

#ifndef BUILD_STATIC
# if defined(QTUIWRAPPERMODULE_LIB)
#  define QTUIWRAPPERMODULE_EXPORT Q_DECL_EXPORT
# else
#  define QTUIWRAPPERMODULE_EXPORT Q_DECL_IMPORT
# endif
#else
# define QTUIWRAPPERMODULE_EXPORT
#endif

#define DECLARE_SHARED_PTR(className) typedef boost::shared_ptr<className> className##PTR;register_ptr_to_python<className##PTR>();

enum WindowCommandType
{
	Button		  = 0x00001,
	Label		  = 0x00002,
	LineEdit	  = 0x00004,
	Spacer		  = 0x00008,
	HLayout		  = 0x00010,
	VLayout       = 0x00020,
	EndLayout     = 0x00040,
	CheckBox      = 0x00080,
	ProgressBar   = 0x00100,
	BeginGroup    = 0x00200,
	EndGroup      = 0x00400,
	IPAddressEdit = 0x00800,
	ComboBox      = 0x01000,
	TableView     = 0x02000,
	SpinBox       = 0x04000,
	DoubleSpinBox = 0x08000,
	PlainTextEdit = 0x10000,
	FontComboBox  = 0x20000
};
//事件 类型 定义
enum EventType
{
	Button_Click = 0,
	Edit_Finished = 1,
	CheckBox_State_Changed = 2,
	ComboBox_Index_Changed = 3,
	TableView_Selection_Chanced = 4,
    RadioGroup_Toggled_Index_Changed = 5
};
