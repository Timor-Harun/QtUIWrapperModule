#pragma once

/********QT INCLUDES********/
#include <QColor>
#include <QtCharts/QChartView>
#include <QtCharts/QLineSeries>
#include <QtCharts/QBarSet>
#include <QtCharts/QBarSeries>
#include <QtCharts/QBarCategoryAxis>
#include <QLayout>
#include <QDebug>
#include <QValueAxis>
#include <QResizeEvent>
/**********STL INCLUDES***********/
#include <vector>
#include <unordered_map>
/**********CUSTOMS INCLUDES***********/
#include "PlotWindow.h"

QT_CHARTS_USE_NAMESPACE

#define plt PlotManager::getInstance()

class PlotManager
{
private:
	/********Hold On ʵ����ر���********/

	//m_holdonFlag��ָʾ�Ƿ�������Hold On,��������ˣ��´λ���ͼ�񽫻�������һͼ����
	bool							  m_holdonFlag;
	//m_preChart����һͼ���ָ��
	QChart*                           m_preChart;

	/********Figure ʵ����ر���********/

	//m_preFigure��ָʾ��ǰͼ��ı�ţ�ע�ⲻ���ظ�
	int								  m_preFigure;
	//m_figureMap���ֵ䣺key����ͼ��ı�ţ���ͨ��void figure(int) ������Value�洢ͼ���Ŷ�Ӧ�Ĵ���ָ��
	std::unordered_map<int, QWidget*> m_figureMap;

	/********subplot ʵ����ر���********/

	//m_subplot_m��������ͼ��m��
	int								  m_subplot_m;
	//m_subplot_m��������ͼ��n��
	int								  m_subplot_n;

	//m_subplot_ps������ǰͼ��ռ�õ��������
	std::vector<int>				  m_subplot_ps;
	//m_subplot_flag������������subplot
	bool							  m_subplot_flag;
	//m_prePlotWindow����һ��subplotʹ�õĵ��Ĵ���ָ��
	PlotWindow*						  m_prePlotWindow;

	/********������ ʵ����ر���********/
	static PlotManager*               instance;

	//����Ĭ��ͼ��
	//����legend��Ҫ���õ�ͼ��ָ��
	void         setDefaultLegend(QLegend* legend);

	//����Ĭ��ChartView��������ָ��
	//����chart��ͼ��ָ��
	//����windowTitle�����ڱ���
	QChartView*  createDefaultChartView(QChart* chart, const std::string& windowTitle);

	//����Ĭ��Chart��������ָ��
	//����chartTitle��ͼ�����
	QChart*      createDefalutChart(const std::string& chartTitle);

	//��ͼ����õ����õ�ͼ������
	//����chartView��ͼ�괰��ָ��
	//����chart��ͼ��ָ��
	void         placePlotWindow(QChartView* chartView, QChart* chart);

public:
	//����������һ��ͼ��
	//����n��ͼ��ı��
	//ע�⣺���n����ֵ�Ѿ������ˣ�������֮ǰ���Ϊn��ͼ��
	void		 figure(int n);

	//���� ����ͬ��ͼ���ϻ���
	void		 holdOn();

	//���� ������ͬ��ͼ���ϻ���
	void		 holdOff();

	//����һ�������ͼ���ɵ�ͼ��
	//����m��ͼ����е�����
	//����n��ͼ����е�����
	//����p���ӱ���ռ��λ������
	//ע�⣺��� ��һ�� ����subplot ʱ��m��n��ͬ���������µ���ͼ
	void		 subPlot(int m, int n, int p);

	//����һ�������ͼ���ɵ�ͼ��
	//����m��ͼ����е�����
	//����n��ͼ����е�����
	//����ps���ӱ���ռ��λ�������б�
	//ע�⣺�ӱ���ռ��λ�������б� �ڶ�Ӧ�� �����в������һ������������ô��������ǰ��ͼ
	void		 subPlot(int m, int n, const std::vector<int>& ps);

	//����һ������ͼ
	//����x��x�����ݵ������
	//����y��y�����ݵ������
	//����windowTitle��ͼ��Ĵ��ڱ���
	//����seriesName����ǰ���ݼ��ϵ�����
	//����lineColor�����Ƶ�ǰ���ݼ����õ���������ɫ
	//����lineWidth�����Ƶ�ǰ���ݼ����õ����������
	//����xLabel��x��ı���
	//����yLabel��y��ı���
	//����title��ͼ��ı���
	//ע�⣺x�ᣬy�����ݵ�����鳤�ȱ�����ͬ
	void		 plot(std::vector<double> x,
				      std::vector<double> y,
					  const std::string& windowTitle = "",
				      const std::string &seriesName = "line",
				      const QColor &lineColor = QColor(),
					  std::string xLabel = "X",
				      std::string yLabel = "Y",
				      int lineWidth = 1,
				      const std::string &title = "");

	//����һ����״ͼ
	//����values�����ݵ������
	//����valueNames��ÿһ�����ݵ��Ӧ����������
	//����label��ͼ��ı���
	//����windowTitle��ͼ��Ĵ��ڱ���
	void         bar(std::vector<int> values,
					 std::vector<std::string> valueNames, 
					 std::string label,
					 std::string windowTitle);

	void		 pie();
	void		 bar3D();

	//��ʾ����ͼ��
	void		 displayAll();

	//��ȡ������ָ��
	static PlotManager* getInstance();

	/********���� �� ���� ����********/
	PlotManager();
	~PlotManager() { instance = nullptr; }
};
