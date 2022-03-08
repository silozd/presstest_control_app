#include "pressapp.h"
#include "ui_pressapp.h"
#include "qcustomplot.h"

void PressApp::setup_PLOT()
{
    ui->wdg_plotArea->setLayout(grid_plotArea);
    customPlot->setGeometry(0,0,ui->wdg_plotArea->width(),ui->wdg_plotArea->height());
    grid_plotArea->addWidget(customPlot,0,0);
    QFont legendFont = font();
    legendFont.setPointSize(Fontsize-1);
    customPlot->addGraph();
    customPlot->setContextMenuPolicy(Qt::CustomContextMenu);
    customPlot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectAxes |
                                QCP::iSelectLegend | QCP::iSelectPlottables);
    customPlot->legend->setSelectableParts(QCPLegend::spItems);
    customPlot->legend->setFont(legendFont);
    customPlot->legend->setSelectedFont(legendFont);
    customPlot->legend->setVisible(true);
    customPlot->graph(0)->setPen(QPen(QColor(255,60,10),2));
    //customPlot->graph(0)->setBrush(QBrush(QColor(255,60,10, 15)));
    customPlot->setBackground(QColor(255,255,255));
    customPlot->xAxis->setBasePen(QPen(Qt::black, 1));
    customPlot->yAxis->setBasePen(QPen(Qt::black, 1));
    customPlot->xAxis->setTickPen(QPen(Qt::black, 1));
    customPlot->yAxis->setTickPen(QPen(Qt::black, 1));
    customPlot->xAxis->setSubTickPen(QPen(Qt::black, 1));
    customPlot->yAxis->setSubTickPen(QPen(Qt::black, 1));
    customPlot->xAxis->setTickLabelColor(Qt::black);
    customPlot->yAxis->setTickLabelColor(Qt::black);
    customPlot->xAxis->grid()->setPen(QPen(QColor(190, 190, 190), 1, Qt::DotLine));
    customPlot->yAxis->grid()->setPen(QPen(QColor(190, 190, 190), 1, Qt::DotLine));
    customPlot->xAxis->grid()->setSubGridPen(QPen(QColor(190, 190, 190), 1, Qt::DotLine));
    customPlot->yAxis->grid()->setSubGridPen(QPen(QColor(190, 190, 190), 1, Qt::DotLine));
    customPlot->xAxis->grid()->setSubGridVisible(true);
    customPlot->yAxis->grid()->setSubGridVisible(true);
    customPlot->xAxis->grid()->setZeroLinePen(Qt::NoPen);
    customPlot->yAxis->grid()->setZeroLinePen(Qt::NoPen);
    customPlot->xAxis->setUpperEnding(QCPLineEnding::esSpikeArrow);
    customPlot->yAxis->setUpperEnding(QCPLineEnding::esSpikeArrow);
    customPlot->axisRect()->setupFullAxesBox();
    customPlot->rescaleAxes();

    connect(customPlot, SIGNAL(selectionChangedByUser()), this, SLOT(selectionChanged()));
    connect(customPlot, SIGNAL(mousePress(QMouseEvent*)), this, SLOT(mousePress()));
    connect(customPlot, SIGNAL(mouseWheel(QWheelEvent*)), this, SLOT(mouseWheel()));
    connect(customPlot, SIGNAL(axisDoubleClick(QCPAxis*,QCPAxis::SelectablePart,QMouseEvent*)), this, SLOT(axisLabelDoubleClick(QCPAxis*,QCPAxis::SelectablePart)));
    connect(customPlot, SIGNAL(legendDoubleClick(QCPLegend*,QCPAbstractLegendItem*,QMouseEvent*)), this, SLOT(legendDoubleClick(QCPLegend*,QCPAbstractLegendItem*)));
    connect(customPlot, SIGNAL(plottableClick(QCPAbstractPlottable*,int,QMouseEvent*)), this, SLOT(graphClicked(QCPAbstractPlottable*,int)));
    connect(customPlot, SIGNAL(customContextMenuRequested(QPoint)), this, SLOT(contextMenuRequest(QPoint)));
}
void PressApp::plot_graph()
{
    graph_index = 1;
    double _zero;
    double _load;
    double key = global_running_timer.elapsed()/1000.0;
    _time->setInterval(1000);

    _load = ui->spinBox_load_invisible->value();
    _zero = ui->doubleSpinBox_zero_suppression->value();

    customPlot->xAxis->setLabel("ZAMAN");
    ui->label_time->setText("Zaman : " + QString::number(key) + " s");

    graph_index = ui->comboBox_graphChoice->currentIndex();

    if(show_graph == 1){
        if(statu == 3){
            _time->stop();
            return;
        }
        else if(statu == 3) {
            customPlot->graph(0)->data().data()->clear(); // todo - delete
            //ui->label_breaking_point->setText(QString::number(real_time.load));
        }
        else if (graph_index == 0){
            customPlot->yAxis->setLabel("YÜK");
            customPlot->graph(0)->addData(key,real_time.load);
            customPlot->yAxis->setRange((real_time.load)-10, (real_time.load)+10);
        }
        else if (graph_index == 1){
            customPlot->yAxis->setLabel("GERILME");
            customPlot->graph(0)->addData(key,real_time.stress);
            customPlot->yAxis->setRange((real_time.stress)-10, (real_time.stress)+10);
        }
        customPlot->xAxis->setRange(key-10, key+10);
        customPlot->graph(0)->rescaleValueAxis(true,true);
        customPlot->replot();
    }
    if(show_graph == 0){
        if(_load > _zero){
            show_graph = 1;
            global_running_timer.restart();
        }
    }
    //ui->label_breaking_point->setText(QString::number(real_time.load));
}
void PressApp::selectionChanged()
{
    if (customPlot->xAxis->selectedParts().testFlag(QCPAxis::spAxis)  || customPlot->xAxis->selectedParts().testFlag(QCPAxis::spTickLabels) ||
        customPlot->xAxis2->selectedParts().testFlag(QCPAxis::spAxis) ||customPlot->xAxis2->selectedParts().testFlag(QCPAxis::spTickLabels)){
            customPlot->xAxis2->setSelectedParts(QCPAxis::spAxis|QCPAxis::spTickLabels);
            customPlot->xAxis->setSelectedParts(QCPAxis::spAxis|QCPAxis::spTickLabels);
    }
    if (customPlot->yAxis->selectedParts().testFlag(QCPAxis::spAxis)  || customPlot->yAxis->selectedParts().testFlag(QCPAxis::spTickLabels) ||
        customPlot->yAxis2->selectedParts().testFlag(QCPAxis::spAxis) || customPlot->yAxis2->selectedParts().testFlag(QCPAxis::spTickLabels)){
            customPlot->yAxis2->setSelectedParts(QCPAxis::spAxis|QCPAxis::spTickLabels);
            customPlot->yAxis->setSelectedParts(QCPAxis::spAxis|QCPAxis::spTickLabels);
    }
    for (int i=0; i<customPlot->graphCount(); ++i){
        QCPGraph *graph = customPlot->graph(i);
        QCPPlottableLegendItem *item = customPlot->legend->itemWithPlottable(graph);
            if (item->selected() || graph->selected()){
                item->setSelected(true);
                graph->setSelection(QCPDataSelection(graph->data()->dataRange()));
            }
    }
}
void PressApp::mousePress()
{
    if (customPlot->xAxis->selectedParts().testFlag(QCPAxis::spAxis)) customPlot->axisRect()->setRangeDrag(customPlot->xAxis->orientation());
    else if (customPlot->yAxis->selectedParts().testFlag(QCPAxis::spAxis)) customPlot->axisRect()->setRangeDrag(customPlot->yAxis->orientation());
    else customPlot->axisRect()->setRangeDrag(Qt::Horizontal|Qt::Vertical);
}
void PressApp::mouseWheel()
{
    if (customPlot->xAxis->selectedParts().testFlag(QCPAxis::spAxis)) customPlot->axisRect()->setRangeZoom(customPlot->xAxis->orientation());
    else if (customPlot->yAxis->selectedParts().testFlag(QCPAxis::spAxis)) customPlot->axisRect()->setRangeZoom(customPlot->yAxis->orientation());
    else customPlot->axisRect()->setRangeZoom(Qt::Horizontal|Qt::Vertical);
}
void PressApp::contextMenuRequest(QPoint pos)
{
    QMenu *menu = new QMenu(this);
    menu->setAttribute(Qt::WA_DeleteOnClose);

    if (customPlot->legend->selectTest(pos, false) >= 0){
        menu->addAction("Sol üste taşı", this, SLOT(moveLegend()))->setData((int)(Qt::AlignTop|Qt::AlignLeft));
        menu->addAction("Üste taşı",     this, SLOT(moveLegend()))->setData((int)(Qt::AlignTop|Qt::AlignHCenter));
        menu->addAction("Sağ üste taşı", this, SLOT(moveLegend()))->setData((int)(Qt::AlignTop|Qt::AlignRight));
        menu->addAction("Sağ alta taşı", this, SLOT(moveLegend()))->setData((int)(Qt::AlignBottom|Qt::AlignRight));
        menu->addAction("Sol alta taşı", this, SLOT(moveLegend()))->setData((int)(Qt::AlignBottom|Qt::AlignLeft));
    }
////////********  add popup context menu to graph screen :
//  else{
//     menu->addAction("Seçenek 1", this, SLOT(someslot()));
//     if (customPlot->selectedGraphs().size() > 0) menu->addAction("Seçenek 2", this, SLOT(someslot2()));
//   }
    menu->popup(customPlot->mapToGlobal(pos));
 }
void PressApp::moveLegend()
{
    if (QAction* contextAction = qobject_cast<QAction*>(sender())){
        bool ok;
        int dataInt = contextAction->data().toInt(&ok);
        if (ok){
            customPlot->axisRect()->insetLayout()->setInsetAlignment(0, (Qt::Alignment)dataInt);
            customPlot->replot();
        }
    }
}
void PressApp::graphClicked(QCPAbstractPlottable *plottable, int dataIndex)     // secili noktalara ait veriler goruntulenebilir
{
    double dataValue = plottable->interface1D()->dataMainValue(dataIndex);
    QString message = QString("  Seçilen grafik: '%1' | Veri: #%2 | Değer: %3.").arg(plottable->name()).arg(dataIndex).arg(dataValue);
}
void PressApp::axisLabelDoubleClick(QCPAxis *axis, QCPAxis::SelectablePart part)
{
    if (part == QCPAxis::spAxisLabel){
        bool ok;
        QString newLabel = QInputDialog::getText(this, "EKSEN", "Yeni eksen adı :", QLineEdit::Normal, axis->label(), &ok);
        if (ok){
            axis->setLabel(newLabel);
            customPlot->replot();
        }
    }
}
void PressApp::legendDoubleClick(QCPLegend *legend, QCPAbstractLegendItem *item)
{
    Q_UNUSED(legend)
    bool ok = false;

    if (item) plItem = qobject_cast<QCPPlottableLegendItem*> (item);
    QString newName = QInputDialog::getText(this, "GRAFİK", "Yeni grafik adı :", QLineEdit::Normal, plItem->plottable()->name(), &ok);
    if (ok){
        plItem->plottable()->setName(newName);
        customPlot->replot();
    }
}
void PressApp::renderPlot(QPrinter *printer)
{
    printer->setPageSize(QPrinter::A4);
    printer->setOutputFileName(QDir::currentPath() + QString("/graph_%1_%2").arg(test_no).arg(start_date_filename_arg));
    QCPPainter painter(printer);
    QRectF pageRect = printer->pageRect(QPrinter::DevicePixel);

    int plotWidth = customPlot->viewport().width();
    int plotHeight = customPlot->viewport().height();
    double scale = pageRect.width()/(double)plotWidth;

    painter.setMode(QCPPainter::pmVectorized);
    painter.setMode(QCPPainter::pmNoCaching);
    painter.setMode(QCPPainter::pmNonCosmetic); // comment this out if you want cosmetic thin lines (always 1 pixel thick independent of pdf zoom level)

    painter.scale(scale, scale);
    customPlot->toPainter(&painter, plotWidth, plotHeight);
}
void PressApp::on_pushButton_printPlot_clicked()
{
    QPrinter printer;
    QPrintPreviewDialog previewDialog(&printer, this);
    connect(&previewDialog, SIGNAL(paintRequested(QPrinter*)), SLOT(renderPlot(QPrinter*)));
    previewDialog.exec();
}
