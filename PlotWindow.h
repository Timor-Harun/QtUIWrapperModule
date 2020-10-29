#pragma once
/********QT INCLUDES********/
#include <QMainWindow>
#include <QChartView>
#include <QMenuBar>
#include <QFileDialog>
#include <QApplication>
#include <QGridLayout>
#include <QDebug>
#include <QMenu>
/********STL INCLUDES********/
#include <unordered_set>

QT_CHARTS_USE_NAMESPACE

class PlotWindow :public QMainWindow
{
private:
	//�˵���ָ��
	QMenuBar*                         m_menuBar;
	//ָ��ͼ���ڵ�ָ��
	QChartView*                       m_chartView;
	//��ͼ������
	int								  m_subplot_m;
	//��ͼ������
	int								  m_subplot_n;
	std::vector<std::vector<bool>>	  m_grid;

	//�����ͼ��ռ������λ���Ƿ�����ȫ���һ����������
	bool checkRectValid(const std::vector<int>& indexes, int& xMin, int& yMin, int& xMax, int& yMax);

protected:
	//��д ���������С�¼�
	void resizeEvent(QResizeEvent* event);
public:
	//������ͼʱ��Ĺ��캯��
	//����m����ͼ������
	//����n����ͼ������
	PlotWindow(int m, int n);

	//��������ͼʱ��Ĺ��캯��
	//����chartView��ͼ�괰��ָ��
	PlotWindow(QChartView* chartView);

	//�����ͼ����
	//����index����ͼ��ռ������λ��
	//����chartWidget����ͼ�Ĵ���ָ��
	void addSubPlot(int index, QWidget* chartWidget);

	//�����ͼ����
	//����indexes����ͼ��ռ������λ������
	//����chartWidget����ͼ�Ĵ���ָ��
	void addSubPlot(std::vector<int> indexes, QWidget* chartWidget);
};