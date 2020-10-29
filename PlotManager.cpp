#include "PlotManager.h"

PlotManager* PlotManager::instance = nullptr;

void PlotManager::setDefaultLegend(QLegend* legend)
{
	legend->setAlignment(Qt::AlignBottom);//�ײ�����
										  //legend->detachFromChart();
	legend->setBackgroundVisible(true);//���ñ����Ƿ����
									   //legend->setAutoFillBackground(true);//���ñ����Զ����
									   //legend->setColor(QColor(255,128,128,128));//������ɫ
									   //legend->setContentsMargins(10,10,10,10);//���ñ߾�left,top,right,bottom
	legend->setLabelColor(QColor(0, 0, 0));//���ñ�ǩ��ɫ
	legend->setVisible(false);//�����Ƿ����
							  //legend->setMaximumHeight(50);
							  //legend->setMaximumWidth(120);
							  //legend->setMaximumSize(10000);
							  //legend->setGeometry(50,50,120,50);//���ü���λ��x,y,w,h
							  //legend->setBrush(QBrush(QColor(128,128,128,128)));
							  //legend->setPen(QPen(QColor(192,192, 192,192)));
	legend->setBorderColor(QColor(0, 0, 0, 0));//���ñ߿���ɫ
	QFont font = legend->font();
	font.setItalic(!font.italic());
	legend->setFont(font);//��������Ϊб��
	font.setPointSizeF(12);
	legend->setFont(font);//���������С
	legend->setFont(QFont("΢���ź�"));//������������
}

QChartView* PlotManager::createDefaultChartView(QChart* chart, const std::string& windowTitle)
{
	QChartView* chartView = new QChartView(chart);
	chartView->setWindowTitle(QString::fromStdString(windowTitle));
	chartView->setRenderHint(QPainter::Antialiasing);
	chartView->setMinimumSize(50, 50);
	chartView->setAttribute(Qt::WA_DeleteOnClose);
	return chartView;
}

QChart* PlotManager::createDefalutChart(const std::string& chartTitle)
{
	QChart* chart = new QChart();
	chart->setLocalizeNumbers(true);//�����Ƿ񱾵ػ�
	chart->setTitle(QString::fromStdString(chartTitle));
	chart->setTitleBrush(QBrush(QColor(0, 0, 0)));//���ñ���Brush
	chart->setTitleFont(QFont("΢���ź�"));//���ñ�������
	return chart;
}

void PlotManager::figure(int n)
{
	m_preFigure = n;
	m_holdonFlag = false;
}

void PlotManager::holdOn()
{
	m_holdonFlag = true;
}

void PlotManager::holdOff()
{
	m_holdonFlag = false;
}

void PlotManager::subPlot(int m, int n, int p)
{
	if (!m_subplot_flag)
	{
		m_subplot_flag = true;
		m_subplot_m = m;
		m_subplot_n = n;

	}
	else
	{
		if (m_subplot_m != n || m_subplot_n != n)
		{
			m_subplot_m = m;
			m_subplot_n = n;
		}
	}
	m_subplot_ps = { p };
}

void PlotManager::subPlot(int m, int n, const std::vector<int>& ps)
{
	if (!m_subplot_flag)
	{
		m_subplot_flag = true;
		m_subplot_m = m;
		m_subplot_n = n;

	}
	else
	{
		if (m_subplot_m != n || m_subplot_n != n)
		{
			m_subplot_m = m;
			m_subplot_n = n;
		}
	}
	m_subplot_ps = ps;
}

void PlotManager::plot(std::vector<double> x, std::vector<double> y, const std::string& windowTitle, const std::string& seriesName, const QColor& lineColor, std::string xLabel, std::string yLabel, int lineWidth, const std::string& title)
{
	//ʵ����һ��QLineSeries����
	QLineSeries* series = new QLineSeries();
	//���������ֵ
	for (int i = 0; i < x.size(); i++)
	{
		*series << QPointF((int)x[i], y[i]);
	}
	series->setName(QString::fromStdString(seriesName));
	series->setPen(QPen(QBrush(lineColor), lineWidth, Qt::SolidLine));
	series->setUseOpenGL(true);
	if (!m_holdonFlag || !m_preChart)
	{
		if (!m_preFigure) m_preFigure = rand();
		QChart* chart = createDefalutChart(title);
		chart->addSeries(series);//���ϵ�е�QChart��
		setDefaultLegend(chart->legend());
		QChartView* chartView = createDefaultChartView(chart, windowTitle);
		placePlotWindow(chartView, chart);
	}
	else
	{
		m_preChart->addSeries(series);
	}
	double xMin, xMax, yMin, yMax;
	xMin = *std::min_element(x.begin(), x.end());
	xMax = *std::max_element(x.begin(), x.end());
	yMin = *std::min_element(y.begin(), y.end());
	yMax = *std::max_element(y.begin(), y.end());
	//��������
	QValueAxis* axisX = new QValueAxis;//X��
	axisX->setRange(xMin, xMax);//���������᷶Χ
	axisX->setTitleText(QString::fromStdString(xLabel));//����
	axisX->setLabelFormat("%.0f"); //��ǩ��ʽ��ÿ����λ������λС��
	axisX->setTickCount(std::min((size_t)10, x.size())); //���ָ�������0��10�ֳ�20����λ

	QValueAxis* axisY = new QValueAxis; //Y ��
	axisY->setRange(yMin, yMax);
	axisY->setTitleText(QString::fromStdString(yLabel));//����
	axisY->setLabelFormat("%.2f"); //��ǩ��ʽ
	axisY->setTickCount((std::min((size_t)10, y.size())));

	for (int i = 0; i < m_preChart->series().size(); i++)
	{
		QValueAxis* old_axisX = (QValueAxis*)(m_preChart->axisX(m_preChart->series()[i]));
		QValueAxis* old_axisY = (QValueAxis*)(m_preChart->axisY(m_preChart->series()[i]));

		if (old_axisX && old_axisY)
		{
			axisX->setRange(std::min(old_axisX->min(), xMin), std::max(old_axisX->max(), xMax));
			axisY->setRange(std::min(old_axisY->min(), yMin), std::max(old_axisY->max(), yMax));
		}
		//Ϊ��������������
		m_preChart->setAxisX(axisX, m_preChart->series()[i]);
		m_preChart->setAxisY(axisY, m_preChart->series()[i]);
	}
}

void PlotManager::placePlotWindow(QChartView* chartView, QChart* chart)
{
	if (!m_subplot_flag)
	{
		PlotWindow* window = new PlotWindow(chartView);
		m_figureMap[m_preFigure] = window;
		m_preChart = chart;
		m_preFigure = -1;
		m_prePlotWindow = window;
	}
	else
	{
		if (!m_prePlotWindow)
		{
			m_prePlotWindow = new PlotWindow(m_subplot_m, m_subplot_n);
			m_figureMap[m_preFigure] = m_prePlotWindow;
			m_preFigure = -1;
		}
		m_preChart = chart;
		m_prePlotWindow->addSubPlot(m_subplot_ps, chartView);
	}
}

void PlotManager::bar(std::vector<int> values, std::vector<std::string> valueNames, std::string label, std::string windowTitle)
{
	QBarSet* set = new QBarSet(QString::fromStdString(label));
	QStringList categories;
	for (int i = 0; i < values.size(); i++)
	{
		(*set) << values[i];
		categories << QString::fromStdString(valueNames[i]);
	}
	if (!m_holdonFlag || !m_preChart)
	{
		if (!m_preFigure) m_preFigure = rand();
		QBarSeries* series = new QBarSeries();
		series->append(set);
		QChart* chart = createDefalutChart(windowTitle);
		chart->addSeries(series);
		setDefaultLegend(chart->legend());
		QBarCategoryAxis* axis = new QBarCategoryAxis();
		axis->append(categories);
		chart->createDefaultAxes();//����Ĭ�ϵ����������ᣨ���� QBarSet ���õ�ֵ��
		chart->setAxisX(axis, series);//����������
		QChartView* chartView = createDefaultChartView(chart, windowTitle);
		placePlotWindow(chartView, chart);
	}
	else
	{
		auto axis = qobject_cast<QBarCategoryAxis*>(m_preChart->axisX());
		axis->append(categories);

		auto series = qobject_cast<QBarSeries*>(m_preChart->series()[0]);
		series->append(set);
	}
}

void PlotManager::pie()
{

}

void PlotManager::bar3D()
{

}

void PlotManager::displayAll()
{
	for (auto p : m_figureMap)
	{
		if (!(p).second->windowTitle().size())
		{
			p.second->setWindowTitle(QString("Figure %1").arg(p.first));
		}
		p.second->show();
	}
	m_figureMap.clear();
}

PlotManager* PlotManager::getInstance()
{
	if (instance == nullptr)
		instance = new PlotManager;
	return instance;
}

PlotManager::PlotManager() :m_preChart(nullptr),
m_prePlotWindow(nullptr),
m_holdonFlag(false),
m_preFigure(-1),
m_subplot_flag(false) {
	srand((unsigned)(time(NULL)));
}
