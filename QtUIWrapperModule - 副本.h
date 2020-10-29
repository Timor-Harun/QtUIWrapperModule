#pragma once

#ifndef wrapped_H
#define wrapped_H
#include "qtuiwrappermodule_global.h"

#include <QWidget>
#include <QPushButton>
#include <QLineEdit>
#include <QLabel>
#include <QComboBox>
#include <QGroupBox>
#include <QCheckBox>
#include <QTabWidget>
#include <QTableWidget>
#include "IPAddress.h"
#include <QMessageBox>
#include <QFileDialog>
#include <QFontDialog>
#include <QColorDialog>
#include <QLayout>
#include <QProgressBar>
#include <Qplaintextedit>
#include <QMenuBar>
#include <boost/python.hpp>
#include <python.h>
#include <boost/python/suite/indexing/vector_indexing_suite.hpp>
#include "WrappedProgressBar.h"
#include "PlotManager.h"
#include "ConsoleMessagePool.h"
#include "WrappedTableWidget.h"
#include <QSpinBox>
#include <QDoubleSpinBox>
#include <QFontComboBox>
#include <QRadioButton>
#include <QButtonGroup>

#include "DialogExecutor.h"
using namespace std;
using namespace boost::python;

typedef  void(QWidget::* PFN_setsize)(int, int);
typedef  void(QComboBox::* PFN_addItem)(const QString&,const QVariant&);
typedef  void(QLayout::* PFN_setContentMargins)(int, int, int, int);
typedef  void(PlotManager::* PFN_subPlot1)(int, int, int);
typedef  void(PlotManager::* PFN_subPlot2)(int, int, const std::vector<int> &);

class QtUtility
{
public:
	static void MessageBoxInfo(const QString &title, const QString &message)
	{
		QMessageBox::information(NULL, title, message);
	}
	static void MessageBoxError(const QString& title, const QString& message)
	{
		QMessageBox::warning(NULL, title, message);
	}
	static void MessageBoxWarning(const QString& title, const QString& message)
	{
		QMessageBox::critical(NULL, title, message);
	}

	static std::string GetOpenFilePath(const QString &title,const QString &filter,const QString &defaultPath = QString())
	{
		return QFileDialog::getOpenFileName(NULL, title, defaultPath, filter).toStdString();
	}

	static std::string GetSaveFilePath(QString title, QString filter,QString defaultPath = QString())
	{
		return QFileDialog::getSaveFileName(NULL, title, defaultPath, filter).toStdString();
	}

	static QFont AskFontInfo(const QString &title)
	{
		bool ret;
		QFont font = QFontDialog::getFont(&ret, QFont(), nullptr, title);
		return font;
	}

	static QColor AskColor(const QString& title)
	{
		return QColorDialog::getColor(Qt::white, nullptr, title);
	}
};
BOOST_PYTHON_MODULE(qt_module_wrapped)
{
	class_<QWidget, boost::noncopyable>("qwidget_class", boost::python::no_init)
		.def("setSize", (PFN_setsize)&QWidget::setFixedSize)
		.def("show", &QWidget::show)
		.def("close", &QWidget::close)
		.def("setHidden", &QWidget::setHidden)
		.def("setQss", &QWidget::setStyleSheet)
		.def("setIcon", &QWidget::setWindowIcon)
		.def("setTitle", &QWidget::setWindowTitle);

	class_<QLabel, boost::noncopyable>("qlabel_class", boost::python::no_init)
		.def("setText", &QLabel::setText)
		.def("getText", &QLabel::text)
		.def("setSize", (PFN_setsize)&QLabel::setFixedSize)
		.def("setEnabled",&QLabel::setEnabled)
		.def("setHidden", &QLabel::setHidden)
		.def("setQss", &QLabel::setStyleSheet)
		.def("setPicture",&QLabel::setPixmap);

	class_<QPushButton, boost::noncopyable>("qbutton_class", boost::python::no_init)
		.def("setSize", (PFN_setsize)&QPushButton::setFixedSize)
		.def("setEnabled", &QPushButton::setEnabled)
		.def("setHidden", &QPushButton::setHidden)
		.def("setQss", &QPushButton::setStyleSheet);

	class_<QLineEdit, boost::noncopyable>("qedit_class", boost::python::no_init)
		.def("setText", &QLineEdit::setText)
		.def("getText", &QLineEdit::text)
		.def("setSize", (PFN_setsize)&QLineEdit::setFixedSize)
		.def("setEnabled", &QLineEdit::setEnabled)
		.def("setHidden", &QLineEdit::setHidden)
		.def("setQss", &QLineEdit::setStyleSheet);

	class_<QCheckBox, boost::noncopyable>("qcheckbox_class", boost::python::no_init)
		.def("getChecked",&QCheckBox::isChecked)
		.def("setChecked", &QCheckBox::setChecked)
		.def("setSize", (PFN_setsize)&QCheckBox::setFixedSize)
		.def("setEnabled", &QCheckBox::setEnabled)
		.def("setHidden", &QCheckBox::setHidden)
		.def("setQss", &QCheckBox::setStyleSheet);

	class_<QComboBox, boost::noncopyable>("qcombobox_class", boost::python::no_init)
		.def("addItem", (PFN_addItem)&QComboBox::addItem)
		.def("removeItem", &QComboBox::removeItem)
		.def("getCount",&QComboBox::count)
		.def("getItem",&QComboBox::itemText)
		.def("currentIndex",&QComboBox::currentIndex)
		.def("setSize", (PFN_setsize)&QComboBox::setFixedSize)
		.def("setEnabled", &QComboBox::setEnabled)
		.def("setHidden", &QComboBox::setHidden)
		.def("setQss", &QComboBox::setStyleSheet);

	class_<IPAddress, boost::noncopyable>("ipaddress_class", boost::python::no_init)
		.def("getIP",&IPAddress::getIP)
		.def("setIP", &IPAddress::setIP)
		.def("setSize", (PFN_setsize)&IPAddress::setFixedSize)
		.def("setEnabled", &IPAddress::setEnabled)
		.def("setHidden", &IPAddress::setHidden)
		.def("setQss", &IPAddress::setStyleSheet);

	class_<QTabWidget, boost::noncopyable>("qtabwidget_class", boost::python::no_init)
		.def("setSize", (PFN_setsize)&QTabWidget::setFixedSize)
		.def("setEnabled", &QTabWidget::setEnabled)
		.def("setHidden", &QTabWidget::setHidden)
		.def("setQss", &QTabWidget::setStyleSheet)
		.def("currentIndex", &QTabWidget::currentIndex)
		.def("setIndex", &QTabWidget::setCurrentIndex)
		.def("setTabText", &QTabWidget::setTabText);

	class_<QHBoxLayout, boost::noncopyable>("qhboxlayout_class", boost::python::no_init)
		.def("setContentsMargins", (PFN_setContentMargins)&QHBoxLayout::setContentsMargins)
		.def("setSpacing", &QHBoxLayout::setSpacing);

	class_<QVBoxLayout, boost::noncopyable>("qvboxlayout_class", boost::python::no_init)
		.def("setContentsMargins", (PFN_setContentMargins)&QVBoxLayout::setContentsMargins)
		.def("setSpacing", &QVBoxLayout::setSpacing);

	class_<WrappedProgressBar, boost::noncopyable>("qprogressbar_class", boost::python::no_init)
		.def("setSize", (PFN_setsize)&WrappedProgressBar::setFixedSize)
		.def("setEnabled", &WrappedProgressBar::setEnabled)
		.def("setHidden", &WrappedProgressBar::setHidden)
		.def("setRange", &WrappedProgressBar::setRange)
		.def("setValue", &WrappedProgressBar::mySetValue)
		.def("getValue", &WrappedProgressBar::value)
		.def("setQss", &WrappedProgressBar::setStyleSheet);

	class_<QString>("qstr", init<const char*>()).def("stdstr",&QString::toStdString);

	class_<QPlainTextEdit, boost::noncopyable>("qpalintextedit_class")
		.def("setSize", (PFN_setsize)&QPlainTextEdit::setFixedSize)
		.def("setEnabled", &QPlainTextEdit::setEnabled)
		.def("setHidden", &QPlainTextEdit::setHidden)
		.def("setText", &QPlainTextEdit::setPlainText)
		.def("getText", &QPlainTextEdit::toPlainText)
		.def("setQss", &QPlainTextEdit::setStyleSheet);

	class_<QtUtility>("qutility_class")
		.def("messageBox", &QtUtility::MessageBoxInfo)
		.def("openFile", &QtUtility::GetOpenFilePath)
		.def("saveFile", &QtUtility::GetSaveFilePath);

	class_<PlotManager>("plotmanager_class", boost::python::no_init)
		.def("bar", &PlotManager::bar)
		.def("plot", &PlotManager::plot)
		.def("figure", &PlotManager::figure)
		.def("subplot1",(PFN_subPlot1)&PlotManager::subPlot)
		.def("subplot2", (PFN_subPlot2)&PlotManager::subPlot)
		.def("displayAll", &PlotManager::displayAll);

	class_<ConsoleMessagePool>("consolemsgpool_class", boost::python::no_init)
		.def("pushMessage", &ConsoleMessagePool::pushMessage)
		.def("isEmpty", &ConsoleMessagePool::isEmpty);

	class_<Message>("consolemsg_class", boost::python::init<QString, QString, MessageType>());

	class_<WrappedTableWidget, boost::noncopyable>("qtable_class", boost::python::no_init)
		.def("setSize", (PFN_setsize)&WrappedTableWidget::setFixedSize)
		.def("setEnabled", &WrappedTableWidget::setEnabled)
		.def("setHidden", &WrappedTableWidget::setHidden)
		.def("setQss", &WrappedTableWidget::setStyleSheet)
		.def("appendRow", &WrappedTableWidget::appendRow)
		.def("setItem", &WrappedTableWidget::setItem)
		.def("getItem", &WrappedTableWidget::getItem)
		.def("getItems", &WrappedTableWidget::getItems)
		.def("findItems", &WrappedTableWidget::findItems)
		.def("setRowItems", &WrappedTableWidget::setRowItems)
		.def("removeRow", &WrappedTableWidget::removeRow)
		.def("clear", &WrappedTableWidget::clear)
		.def("selectedRowIndex", &WrappedTableWidget::getSelectedRowIndex)
		.def("getRowCount", &WrappedTableWidget::rowCount)
		.def("updateItem",&WrappedTableWidget::updateItem);

	enum_<MessageType>("msgtype_enum")
		.value("Info", MessageType::Info)
		.value("Warning", MessageType::Warning)
		.value("Error", MessageType::Error);

	class_<std::vector<std::string>>("str_vector")
		.def(vector_indexing_suite<std::vector<std::string> >())
		;

	class_<std::vector<double>>("double_vector")
		.def(vector_indexing_suite<std::vector<double> >());

	class_<std::vector<int>>("int_vector")
		.def(vector_indexing_suite<std::vector<int> >());

	class_<QColor>("qcolor_class", boost::python::init<int, int, int>())
		.add_property("r", &QColor::red, &QColor::setRed)
		.add_property("g", &QColor::green, &QColor::setGreen)
		.add_property("b", &QColor::blue, &QColor::setBlue)
		.add_property("a", &QColor::alpha, &QColor::setAlpha);

	class_<QFont>("qfont_class", boost::python::init<>())
		.def("getSize", &QFont::pointSize)
		.def("setFamilyName", &QFont::setFamily)
		.def("getFamilyName", &QFont::family)
		.def("setSize", &QFont::setPointSize)
		.def("setBold", &QFont::setBold)
		.def("isBold", &QFont::bold)
		.def("setUnderline", &QFont::setUnderline)
		.def("isUnderline", &QFont::underline)
		.def("isItalic", &QFont::italic)
		.def("setItalic", &QFont::setItalic);

	class_<QSpinBox, boost::noncopyable>("qspinbox_class", boost::python::no_init)
		.def("setSize", (PFN_setsize)&QSpinBox::setFixedSize)
		.def("setEnabled", &QSpinBox::setEnabled)
		.def("setHidden", &QSpinBox::setHidden)
		.def("setQss", &QSpinBox::setStyleSheet)
		.def("getValue", &QSpinBox::value)
		.def("setValue", &QSpinBox::setValue);

	class_<QDoubleSpinBox, boost::noncopyable>("qdoublespinbox_class", boost::python::no_init)
		.def("setSize", (PFN_setsize)&QDoubleSpinBox::setFixedSize)
		.def("setEnabled", &QDoubleSpinBox::setEnabled)
		.def("setHidden", &QDoubleSpinBox::setHidden)
		.def("setQss", &QDoubleSpinBox::setStyleSheet)
		.def("getValue", &QDoubleSpinBox::value)
		.def("setValue", &QDoubleSpinBox::setValue);

	class_<QRadioButton, boost::noncopyable>("qradiobox_class", boost::python::no_init)
		.def("setSize", (PFN_setsize)&QRadioButton::setFixedSize)
		.def("setEnabled", &QRadioButton::setEnabled)
		.def("setHidden", &QRadioButton::setHidden)
		.def("setQss", &QRadioButton::setStyleSheet)
		.def("isChecked", &QRadioButton::isChecked)
		.def("setChecked", &QRadioButton::setChecked);

	class_<QButtonGroup, boost::noncopyable>("qbuttongroup_class", boost::python::no_init)
		.def("addButton", &QButtonGroup::addButton)
		.def("setExclusive",&QButtonGroup::setExclusive)
		.def("isExclusive", &QButtonGroup::exclusive)
		.def("clearButton", &QButtonGroup::removeButton);

	class_<DialogExecutor, boost::noncopyable>("dialogexecutor_class", boost::python::no_init)
		.def("getDialogIndex", &DialogExecutor::getDialogIndex)
		.def("exec", &DialogExecutor::exec);

	class_<QIcon>("qicon_class", boost::python::init<const QString&>());

    DECLARE_SHARED_PTR(QWidget);
	DECLARE_SHARED_PTR(QLabel);
	DECLARE_SHARED_PTR(QPushButton);
	DECLARE_SHARED_PTR(QLineEdit);
	DECLARE_SHARED_PTR(QComboBox);
	DECLARE_SHARED_PTR(QCheckBox);
	DECLARE_SHARED_PTR(QTabWidget);
	DECLARE_SHARED_PTR(IPAddress);
	DECLARE_SHARED_PTR(QHBoxLayout);
	DECLARE_SHARED_PTR(QVBoxLayout);
	DECLARE_SHARED_PTR(QString);
	DECLARE_SHARED_PTR(WrappedProgressBar);
	DECLARE_SHARED_PTR(PlotManager);
	DECLARE_SHARED_PTR(ConsoleMessagePool);
	DECLARE_SHARED_PTR(Message);
	DECLARE_SHARED_PTR(WrappedTableWidget);
	DECLARE_SHARED_PTR(QSpinBox);
	DECLARE_SHARED_PTR(QDoubleSpinBox);
	DECLARE_SHARED_PTR(QRadioButton);
	DECLARE_SHARED_PTR(DialogExecutor);
	DECLARE_SHARED_PTR(QIcon);
	DECLARE_SHARED_PTR(QColor);
	DECLARE_SHARED_PTR(QFont);
}
#endif
