#include <cmath>

#include <functional>
#include <limits>

#include <QBrush>
#include <QColor>
#include <QFont>
#include <QLocale>
#include <QMainWindow>
#include <QMouseEvent>
#include <QPen>
#include <QString>
#include <QVector>
#include <QWheelEvent>
#include <QWidget>

#include "qcustomplot/qcustomplot.h"

#include "ui_mainwindow.h"

#include "mainwindow.hxx"
#include "../config.hxx"
#include "../math/functions.hxx"
#include "../math/mathutils.hxx"
#include "../math/numerictypes.hxx"
#include "../math/rungerule.hxx"
#include "../math/simpsonintegral.hxx"


#pragma region init/destroy

MainWindow::MainWindow (QWidget* parent) :
  QMainWindow (parent),
  ui_ (new Ui::MainWindow)
{
  ui_->setupUi (this);
//  initSignalsAndSlots ();
  setDefaults ();
  initCustomPlot (ui_->plot_functions_CustomPlot);
}


MainWindow::~MainWindow (void)
{
  delete ui_;
}

#pragma endregion // init/destroy


#pragma region private slots

void
MainWindow::on_funcParam_alpha_DoubleSpinBox_valueChanged (double arg1)
{
  funcParam_alpha_ = arg1;

  qDebug () << "funcParam_alpha_ ==" << funcParam_alpha_;

  setDirty (true);
}


void
MainWindow::on_funcParam_beta_DoubleSpinBox_valueChanged (double arg1)
{
  funcParam_beta_ = arg1;

  qDebug () << "funcParam_beta_ ==" << funcParam_beta_;

  setDirty (true);
}


void
MainWindow::on_funcParam_gamma_DoubleSpinBox_valueChanged (double arg1)
{
  funcParam_gamma_ = arg1;

  qDebug () << "funcParam_gamma_ ==" << funcParam_gamma_;

  setDirty (true);
}


void
MainWindow::on_funcParam_delta_DoubleSpinBox_valueChanged (double arg1)
{
  funcParam_delta_ = arg1;

  qDebug () << "funcParam_delta_ ==" << funcParam_delta_;

  setDirty (true);
}


void
MainWindow::on_funcParam_epsilon_DoubleSpinBox_valueChanged (double arg1)
{
  funcParam_epsilon_ = arg1;

  qDebug () << "funcParam_epsilon_ ==" << funcParam_epsilon_;

  setDirty (true);
}


void
MainWindow::on_funcParam_mu_DoubleSpinBox_valueChanged (double arg1)
{
  funcParam_mu_ = arg1;

  qDebug () << "funcParam_mu_ ==" << funcParam_mu_;

  setDirty (true);
}


void
MainWindow::on_plotParam_A_DoubleSpinBox_valueChanged (double arg1)
{
  using namespace Config::Gui::InputLimits;


  if (arg1 >= ABCD_Min && arg1 <= ABCD_Max)
  {
    if (arg1 >= ui_->plotParam_B_DoubleSpinBox->value ())
    {
      ui_->plotParam_B_DoubleSpinBox->setValue (arg1 + Step);
    }

    plotParam_A_ = arg1;

    qDebug () << "plotParam_A_ ==" << plotParam_A_;

    setDirty (true);
  }
}


void
MainWindow::on_plotParam_B_DoubleSpinBox_valueChanged (double arg1)
{
  using namespace Config::Gui::InputLimits;


  if (arg1 >= ABCD_Min && arg1 <= ABCD_Max)
  {
    if (arg1 <= ui_->plotParam_A_DoubleSpinBox->value ())
    {
      ui_->plotParam_A_DoubleSpinBox->setValue (arg1 - Step);
    }

    plotParam_B_ = arg1;

    qDebug () << "plotParam_B_ ==" << plotParam_B_;

    setDirty (true);
  }
}


void
MainWindow::on_plotParam_C_DoubleSpinBox_valueChanged (double arg1)
{
  using namespace Config::Gui::InputLimits;


  if (arg1 >= ABCD_Min && arg1 <= ABCD_Max)
  {
    if (arg1 >= ui_->plotParam_D_DoubleSpinBox->value ())
    {
      ui_->plotParam_D_DoubleSpinBox->setValue (arg1 + Step);
    }

    plotParam_C_ = arg1;

    qDebug () << "plotParam_C_ ==" << plotParam_C_;

    setDirty (true);
  }
}


void
MainWindow::on_plotParam_D_DoubleSpinBox_valueChanged (double arg1)
{
  using namespace Config::Gui::InputLimits;


  if (arg1 >= ABCD_Min && arg1 <= ABCD_Max)
  {
    if (arg1 <= ui_->plotParam_C_DoubleSpinBox->value ())
    {
      ui_->plotParam_C_DoubleSpinBox->setValue (arg1 - Step);
    }

    plotParam_D_ = arg1;

    qDebug () << "plotParam_D_ ==" << plotParam_D_;

    setDirty (true);
  }
}


void
MainWindow::on_integrParam_n_0_SpinBox_valueChanged (int arg1)
{
  integrParam_n_0_ = arg1;

  qDebug () << "integrParam_n_0_ ==" << integrParam_n_0_;

  setDirty (true);
}


void
MainWindow::on_integrParam_delta_SpinBox_valueChanged (int arg1)
{
  integrParam_delta_ = std::pow (10., double (arg1));

  qDebug () << "integrParam_delta_ ==" << integrParam_delta_;

  setDirty (true);
}


void
MainWindow::on_integrParam_a_DoubleSpinBox_valueChanged (double arg1)
{
  using namespace Config::Gui::InputLimits;


  if (arg1 >= ABCD_Min && arg1 <= ABCD_Max)
  {
    if (arg1 >= ui_->integrParam_b_DoubleSpinBox->value ())
    {
      ui_->integrParam_b_DoubleSpinBox->setValue (arg1 + Step);
    }

    integrParam_a_ = arg1;

    qDebug () << "integrParam_a_ ==" << integrParam_a_;

    setDirty (true);
  }
}


void
MainWindow::on_integrParam_b_DoubleSpinBox_valueChanged (double arg1)
{
  using namespace Config::Gui::InputLimits;


  if (arg1 >= ABCD_Min && arg1 <= ABCD_Max)
  {
    if (arg1 <= ui_->integrParam_a_DoubleSpinBox->value ())
    {
      ui_->integrParam_a_DoubleSpinBox->setValue (arg1 - Step);
    }

    integrParam_b_ = arg1;

    qDebug () << "integrParam_b_ ==" << integrParam_b_;

    setDirty (true);
  }
}


void
MainWindow::on_ctrl_plot_PushButton_clicked (void)
{
  qDebug() << "on_ctrl_plot_PushButton_clicked";

  updateCustomPlot (ui_->plot_functions_CustomPlot);
}


void
MainWindow::on_ctrl_reset_PushButton_clicked (void)
{
  qDebug() << "on_ctrl_reset_PushButton_clicked";

  clearCustomPlot (ui_->plot_functions_CustomPlot);
}


void
MainWindow::on_ctrl_liveUpdate_CheckBox_toggled (bool checked)
{
  liveUpdateEnabled_ = checked;

  qDebug () << "liveUpdateEnabled_ ==" << liveUpdateEnabled_;

  setDirty (true);
}


void
MainWindow::on_plot_functions_CustomPlot_selectionChangedByUser (void)
{
  QCustomPlot* const customPlot (qobject_cast<QCustomPlot*> (sender ()));

  if (
    customPlot->xAxis->selectedParts ().testFlag (QCPAxis::spAxis) ||
    customPlot->xAxis->selectedParts ().testFlag (QCPAxis::spTickLabels) ||
    customPlot->xAxis2->selectedParts ().testFlag (QCPAxis::spAxis) ||
    customPlot->xAxis2->selectedParts ().testFlag (QCPAxis::spTickLabels)
  )
  {
    customPlot->xAxis2->setSelectedParts (
      QCPAxis::spAxis | QCPAxis::spTickLabels
    );
    customPlot->xAxis->setSelectedParts (
      QCPAxis::spAxis | QCPAxis::spTickLabels
    );
  }

  if (
    customPlot->yAxis->selectedParts ().testFlag (QCPAxis::spAxis) ||
    customPlot->yAxis->selectedParts ().testFlag (QCPAxis::spTickLabels) ||
    customPlot->yAxis2->selectedParts ().testFlag (QCPAxis::spAxis) ||
    customPlot->yAxis2->selectedParts ().testFlag (QCPAxis::spTickLabels)
  )
  {
    customPlot->yAxis2->setSelectedParts (
      QCPAxis::spAxis | QCPAxis::spTickLabels
    );
    customPlot->yAxis->setSelectedParts (
      QCPAxis::spAxis | QCPAxis::spTickLabels
    );
  }

  for (int i (0); i < customPlot->plottableCount (); ++i)
  {
    QCPAbstractPlottable* const plottable (customPlot->plottable (i));
    QCPPlottableLegendItem* const item (
      customPlot->legend->itemWithPlottable (plottable)
    );

    if (item->selected () || plottable->selected ())
    {
      item->setSelected (true);
      plottable->setSelected (true);
    }
  }
}


void
MainWindow::on_plot_functions_CustomPlot_mousePress (QMouseEvent* ev)
{
  QCustomPlot* const customPlot (qobject_cast<QCustomPlot*> (sender ()));

  if (
    customPlot->xAxis->selectedParts ().testFlag (QCPAxis::spAxis)
  )
  {
    customPlot->axisRect ()->setRangeDrag (customPlot->xAxis->orientation ());
  }
  else
  {
    if (
      customPlot->yAxis->selectedParts ().testFlag (QCPAxis::spAxis)
    )
    {
      customPlot->axisRect ()->setRangeDrag (customPlot->yAxis->orientation ());
    }
    else
    {
      customPlot->axisRect ()->setRangeDrag (Qt::Horizontal | Qt::Vertical);
    }
  }
}


void
MainWindow::on_plot_functions_CustomPlot_mouseWheel (QWheelEvent* ev)
{
  QCustomPlot* const customPlot (qobject_cast<QCustomPlot*> (sender ()));

  if (
    customPlot->xAxis->selectedParts ().testFlag (QCPAxis::spAxis)
  )
  {
    customPlot->axisRect ()->setRangeZoom (customPlot->xAxis->orientation ());
  }
  else
  {
    if (
      customPlot->yAxis->selectedParts ().testFlag (QCPAxis::spAxis))
    {
      customPlot->axisRect ()->setRangeZoom (customPlot->yAxis->orientation ());
    }
    else
    {
      customPlot->axisRect ()->setRangeZoom (Qt::Horizontal | Qt::Vertical);
    }
  }
}


void
MainWindow::on_plot_functions_CustomPlot_mouseMove (QMouseEvent* ev)
{
  QCustomPlot* const customPlot (qobject_cast<QCustomPlot*> (sender ()));

  const double x (customPlot->xAxis->pixelToCoord (ev->pos ().x ()));
  const double y (customPlot->yAxis->pixelToCoord (ev->pos ().y ()));

  customPlot->setToolTip (QString ("(%1; %2)").arg (x).arg (y));
}


void
MainWindow::on_integrParam_alpha_RadioButton_toggled (bool checked)
{
  paramType_ = ParamType::Alpha;

  qDebug () << "paramType_ == Alpha";

  ui_->funcParam_alpha_DoubleSpinBox->setEnabled (!checked);

  setDirty (true);
}


void
MainWindow::on_integrParam_beta_RadioButton_toggled (bool checked)
{
  paramType_ = ParamType::Beta;

  qDebug () << "paramType_ == Beta";

  ui_->funcParam_beta_DoubleSpinBox->setEnabled (!checked);

  setDirty (true);
}


void
MainWindow::on_integrParam_gamma_RadioButton_toggled (bool checked)
{
  paramType_ = ParamType::Gamma;

  qDebug () << "paramType_ == Gamma";

  ui_->funcParam_gamma_DoubleSpinBox->setEnabled (!checked);

  setDirty (true);
}


void
MainWindow::on_integrParam_delta_RadioButton_toggled (bool checked)
{
  paramType_ = ParamType::Delta;

  qDebug () << "paramType_ == Delta";

  ui_->funcParam_delta_DoubleSpinBox->setEnabled (!checked);

  setDirty (true);
}


void
MainWindow::on_integrParam_epsilon_RadioButton_toggled (bool checked)
{
  paramType_ = ParamType::Epsilon;

  qDebug () << "paramType_ == Epsilon";

  ui_->funcParam_epsilon_DoubleSpinBox->setEnabled (!checked);

  setDirty (true);
}


void
MainWindow::on_integrParam_mu_RadioButton_toggled (bool checked)
{
  paramType_ = ParamType::Mu;

  qDebug () << "paramType_ == Mu";

  ui_->funcParam_mu_DoubleSpinBox->setEnabled (!checked);

  setDirty (true);
}

#pragma endregion // private slots


#pragma region private methods

[[deprecated("This is a workaround for strange autoconnection issues.")]]
void
MainWindow::initSignalsAndSlots (void)
{
  connect (
    ui_->funcParam_alpha_DoubleSpinBox, SIGNAL (valueChanged (double)),
    this, SLOT (on_funcParam_alpha_DoubleSpinBox_valueChanged (double))
  );

  connect (
    ui_->funcParam_beta_DoubleSpinBox, SIGNAL (valueChanged (double)),
    this, SLOT (on_funcParam_beta_DoubleSpinBox_valueChanged (double))
  );

  connect (
    ui_->funcParam_gamma_DoubleSpinBox, SIGNAL (valueChanged (double)),
    this, SLOT (on_funcParam_gamma_DoubleSpinBox_valueChanged (double))
  );

  connect (
    ui_->funcParam_delta_DoubleSpinBox, SIGNAL (valueChanged (double)),
    this, SLOT (on_funcParam_delta_DoubleSpinBox_valueChanged (double))
  );

  connect (
    ui_->funcParam_epsilon_DoubleSpinBox, SIGNAL (valueChanged (double)),
    this, SLOT (on_funcParam_epsilon_DoubleSpinBox_valueChanged (double))
  );

  connect (
    ui_->funcParam_mu_DoubleSpinBox, SIGNAL (valueChanged (double)),
    this, SLOT (on_funcParam_mu_DoubleSpinBox_valueChanged (double))
  );


  connect (
    ui_->plotParam_A_DoubleSpinBox, SIGNAL (valueChanged (double)),
    this, SLOT (on_plotParam_A_DoubleSpinBox_valueChanged (double))
  );

  connect (
    ui_->plotParam_B_DoubleSpinBox, SIGNAL (valueChanged (double)),
    this, SLOT (on_plotParam_B_DoubleSpinBox_valueChanged (double))
  );

  connect (
    ui_->plotParam_C_DoubleSpinBox, SIGNAL (valueChanged (double)),
    this, SLOT (on_plotParam_C_DoubleSpinBox_valueChanged (double))
  );

  connect (
    ui_->plotParam_D_DoubleSpinBox, SIGNAL (valueChanged (double)),
    this, SLOT (on_plotParam_D_DoubleSpinBox_valueChanged (double))
  );


  connect (
    ui_->integrParam_n_0_SpinBox, SIGNAL (valueChanged (int)),
    this, SLOT (on_integrParam_n_0_SpinBox_valueChanged (int))
  );

  connect (
    ui_->integrParam_delta_SpinBox, SIGNAL (valueChanged (int)),
    this, SLOT (on_integrParam_delta_SpinBox_valueChanged (int))
  );

  connect (
    ui_->integrParam_a_DoubleSpinBox, SIGNAL (valueChanged (double)),
    this, SLOT (on_integrParam_a_DoubleSpinBox_valueChanged (double))
  );

  connect (
    ui_->integrParam_b_DoubleSpinBox, SIGNAL (valueChanged (double)),
    this, SLOT (on_integrParam_b_DoubleSpinBox_valueChanged (double))
  );


  connect (
    ui_->ctrl_plot_PushButton, SIGNAL (clicked (void)),
    this, SLOT (on_ctrl_plot_PushButton_clicked (void))
  );

  connect (
    ui_->ctrl_reset_PushButton, SIGNAL (clicked (void)),
    this, SLOT (on_ctrl_reset_PushButton_clicked (void))
  );

  connect (
    ui_->ctrl_liveUpdate_CheckBox, SIGNAL (toggled (bool)),
    this, SLOT (on_ctrl_liveUpdate_CheckBox_toggled (bool))
  );


  connect (
    ui_->integrParam_alpha_RadioButton, SIGNAL (toggled (bool)),
    this, SLOT (on_integrParam_alpha_RadioButton_toggled (bool))
  );

  connect (
    ui_->integrParam_beta_RadioButton, SIGNAL (toggled (bool)),
    this, SLOT (on_integrParam_beta_RadioButton_toggled (bool))
  );

  connect (
    ui_->integrParam_gamma_RadioButton, SIGNAL (toggled (bool)),
    this, SLOT (on_integrParam_gamma_RadioButton_toggled (bool))
  );

  connect (
    ui_->integrParam_delta_RadioButton, SIGNAL (toggled (bool)),
    this, SLOT (on_integrParam_delta_RadioButton_toggled (bool))
  );

  connect (
    ui_->integrParam_epsilon_RadioButton, SIGNAL (toggled (bool)),
    this, SLOT (on_integrParam_epsilon_RadioButton_toggled (bool))
  );

  connect (
    ui_->integrParam_mu_RadioButton, SIGNAL (toggled (bool)),
    this, SLOT (on_integrParam_mu_RadioButton_toggled (bool))
  );
}


void
MainWindow::setDefaults (void)
{
  using namespace Config::Gui::Defaults;
  using Config::Gui::InputLimits::Step;


  ui_->funcParam_alpha_DoubleSpinBox->setValue (Alpha);
  ui_->funcParam_beta_DoubleSpinBox->setValue (Beta);
  ui_->funcParam_gamma_DoubleSpinBox->setValue (Gamma);
  ui_->funcParam_delta_DoubleSpinBox->setValue (Delta);
  ui_->funcParam_epsilon_DoubleSpinBox->setValue (Epsilon);
  ui_->funcParam_mu_DoubleSpinBox->setValue (Mu);

  ui_->plotParam_A_DoubleSpinBox->setValue (A);
  ui_->plotParam_A_DoubleSpinBox->setSingleStep (Step);
  ui_->plotParam_B_DoubleSpinBox->setValue (B);
  ui_->plotParam_B_DoubleSpinBox->setSingleStep (Step);
  ui_->plotParam_C_DoubleSpinBox->setValue (C);
  ui_->plotParam_C_DoubleSpinBox->setSingleStep (Step);
  ui_->plotParam_D_DoubleSpinBox->setValue (D);
  ui_->plotParam_D_DoubleSpinBox->setSingleStep (Step);

  ui_->integrParam_n_0_SpinBox->setValue (N);
  ui_->integrParam_delta_SpinBox->setValue (DeltaExponent);
  ui_->integrParam_a_DoubleSpinBox->setValue (IntegrParam_A);
  ui_->integrParam_b_DoubleSpinBox->setValue (IntegrParam_B);

  ui_->integrParam_mu_RadioButton->setChecked (true);

  ui_->ctrl_liveUpdate_CheckBox->setChecked (LiveUpdateEnabled);
}


void
MainWindow::setDirty (bool isDirty)
{
  isDirty_ = isDirty;

  qDebug () << "isDirty_ ==" << isDirty_;

  if (isDirty_ && liveUpdateEnabled_)
  {
    // TODO: [~~] Update only parts of the plot that were modified.
    updateCustomPlot (ui_->plot_functions_CustomPlot);
  }
}


void
MainWindow::initCustomPlot (QCustomPlot* customPlot)
{
  using namespace Config::Gui::PlotParams;


  const QFont normalFont (font ().family (), FontSize);
  const QFont boldFont (font ().family (), FontSize, QFont::Bold);

  customPlot->setInteractions (
    QCP::iRangeDrag | QCP::iRangeZoom |
    QCP::iSelectPlottables | QCP::iSelectAxes |
    QCP::iSelectLegend | QCP::iSelectItems
  );

  customPlot->setLocale (
    QLocale (QLocale::English, QLocale::UnitedStates)
  );

  customPlot->setAntialiasedElements (QCP::aeAll);

  customPlot->legend->setVisible (true);
  customPlot->legend->setFont (normalFont);
  customPlot->legend->setSelectedFont (boldFont);
  customPlot->legend->setSelectableParts (QCPLegend::spItems);

  customPlot->setAutoAddPlottableToLegend (true);

  customPlot->setBackgroundScaled (true);
  customPlot->setBackgroundScaledMode (Qt::IgnoreAspectRatio);

  customPlot->setPlottingHints (QCP::phForceRepaint | QCP::phCacheLabels);

  customPlot->xAxis2->setVisible (true);
  customPlot->xAxis2->setTickLabels (false);

  customPlot->yAxis2->setVisible (true);
  customPlot->yAxis2->setTickLabels (false);

  customPlot->xAxis->setSelectableParts (
    QCPAxis::spAxis | QCPAxis::spTickLabels
  );

  customPlot->yAxis->setSelectableParts (
    QCPAxis::spAxis | QCPAxis::spTickLabels
  );

  customPlot->xAxis->setRange (-1., 1.);
  customPlot->yAxis->setRange (-1., 1.);

  customPlot->xAxis->setLabel (QStringLiteral ("x"));
  customPlot->yAxis->setLabel (QStringLiteral ("y"));

  QCPPlotTitle* const plotTitle (new QCPPlotTitle (customPlot));
  plotTitle->setText (
    QStringLiteral ("#2 // Численное интегрирование // Алексей Горишный // группа ИТ-32БО")
  );
  plotTitle->setFont (normalFont);
  customPlot->plotLayout ()->insertRow (0);
  customPlot->plotLayout ()->addElement (0, 0, plotTitle);

  connect (
    customPlot, SIGNAL (selectionChangedByUser (void)),
    this, SLOT (on_plot_functions_CustomPlot_selectionChangedByUser (void))
  );

  connect (
    customPlot, SIGNAL (mousePress (QMouseEvent*)),
    this, SLOT (on_plot_functions_CustomPlot_mousePress (QMouseEvent*))
  );

  connect (
    customPlot, SIGNAL (mouseWheel (QWheelEvent*)),
    this, SLOT (on_plot_functions_CustomPlot_mouseWheel (QWheelEvent*))
  );

  connect (
    customPlot->xAxis, SIGNAL (rangeChanged (QCPRange)),
    customPlot->xAxis2, SLOT (setRange (QCPRange))
  );

  connect (
    customPlot->yAxis, SIGNAL (rangeChanged (QCPRange)),
    customPlot->yAxis2, SLOT (setRange (QCPRange))
  );

  connect (
    customPlot, SIGNAL (mouseMove (QMouseEvent*)),
    this, SLOT (on_plot_functions_CustomPlot_mouseMove (QMouseEvent*))
  );
}


void
MainWindow::enableCustomPlot (QCustomPlot* customPlot, bool enabled)
{
  if (enabled)
  {
    customPlot->setBackground (Qt::white);
  }
  else
  {
    customPlot->setBackground (Qt::lightGray);
  }

  customPlot->setEnabled (enabled);
}


void
MainWindow::clearCustomPlot (QCustomPlot* customPlot)
{
  customPlot->clearFocus ();
  customPlot->clearGraphs ();
  customPlot->clearItems ();
  customPlot->clearMask ();
  customPlot->clearPlottables ();

//  customPlot->plotLayout ()->remove (customPlot->plotLayout ()->element (0, 0));
//  customPlot->plotLayout ()->simplify ();

  customPlot->replot ();
}


void
MainWindow::updateCustomPlot (QCustomPlot* customPlot)
{
  using namespace Config::Gui::PlotParams;
  using Config::Gui::Colors;
  using std::function;
  using std::placeholders::_1;
  using std::placeholders::_2;


  qDebug () << "updateCustomPlot";

  const int samplesCount (
    std::round (
      ResolutionMultiplier * customPlot->axisRect ()->size ().width () + 1
    )
  );

  function<Math::real_t (Math::real_t, Math::real_t)> f;

  switch (paramType_)
  {
    case ParamType::Alpha:
      f = std::bind (
        Math::f, _1, _2, funcParam_beta_, funcParam_gamma_,
        funcParam_delta_, funcParam_epsilon_, funcParam_mu_
      );
      break;

    case ParamType::Beta:
      f = std::bind (
        Math::f, _1, funcParam_alpha_, _2, funcParam_gamma_,
        funcParam_delta_, funcParam_epsilon_, funcParam_mu_
      );
      break;

    case ParamType::Gamma:
      f = std::bind (
        Math::f, _1, funcParam_alpha_, funcParam_beta_, _2,
        funcParam_delta_, funcParam_epsilon_, funcParam_mu_
      );
      break;

    case ParamType::Delta:
      f = std::bind (
        Math::f, _1, funcParam_alpha_, funcParam_beta_, funcParam_gamma_,
        _2, funcParam_epsilon_, funcParam_mu_
      );
      break;

    case ParamType::Epsilon:
      f = std::bind (
        Math::f, _1, funcParam_alpha_, funcParam_beta_, funcParam_gamma_,
        funcParam_delta_, _2, funcParam_mu_
      );
      break;

    case ParamType::Mu:
      f = std::bind (
        Math::f, _1, funcParam_alpha_, funcParam_beta_, funcParam_gamma_,
        funcParam_delta_, funcParam_epsilon_, _2
      );
      break;

    default:
      break;
  }

  const Math::SimpsonIntegral I (
    f, integrParam_a_, integrParam_b_, integrParam_n_0_
  );

  Math::RungeRule<Math::SimpsonIntegral> rungeRule (I, integrParam_delta_);

  clearCustomPlot (customPlot);

//  plotFunction (
//    I, samplesCount, plotParam_A_, plotParam_B_, plotParam_C_, plotParam_D_,
//    Colors[QStringLiteral ("Red")], customPlot, QStringLiteral ("Iₙ(p)")
//  );

  plotFunction (
    std::ref (rungeRule), samplesCount,
    plotParam_A_, plotParam_B_, plotParam_C_, plotParam_D_,
    Colors[QStringLiteral ("Indigo")], customPlot, QStringLiteral ("I₂ₙ(p)")
  );

  plotBoundingBox (
    plotParam_A_, plotParam_B_, plotParam_C_, plotParam_D_,
    Qt::darkGray, customPlot
  );

  customPlot->rescaleAxes (true);

  customPlot->xAxis->setRange (plotParam_A_ - Margins, plotParam_B_ + Margins);
  customPlot->yAxis->setRange (plotParam_C_ - Margins, plotParam_D_ + Margins);

  customPlot->replot ();

  ui_->prop_n_max_LcdNumber->display (int (rungeRule.n_max ()));
}


void
MainWindow::plotFunction (
  const std::function<Math::real_t (Math::real_t)>& func, int samplesCount,
  double keyStart, double keyEnd, double valueStart, double valueEnd,
  const QColor& color, QCustomPlot* customPlot, const QString& name
)
{
  QVector<double> keys (samplesCount), values (samplesCount);

  for (int sampleIdx (0); sampleIdx < samplesCount; ++sampleIdx)
  {
    const double key (
      Math::lerp (
        0, keyStart,
        samplesCount - 1, keyEnd,
        sampleIdx
      )
    );
    const double value (func (key));

    keys[sampleIdx] = key;

    // FIXME: [~-]
    if (std::isnan (value))
    {
      values[sampleIdx] = std::numeric_limits<double>::quiet_NaN ();
    }
    else
    {
      values[sampleIdx] = double (Math::clamp (valueStart, valueEnd, value));
    }
  }

  QCPGraph* const graph (customPlot->addGraph ());
  graph->setData (keys, values);
  graph->setPen (QPen (color));
  graph->setSelectedPen (
    QPen (QBrush (color), Config::Gui::PlotParams::SelectedPenWidth)
  );
  graph->setAdaptiveSampling (true);
  graph->setName (name);
}


void
MainWindow::plotBoundingBox (
  double keyStart, double keyEnd, double valueStart, double valueEnd,
  const QColor& color, QCustomPlot* customPlot
)
{
  QCPItemStraightLine* const top (new QCPItemStraightLine (customPlot));
  top->setPen (QPen (color));
  top->point1->setCoords (keyStart, valueEnd);
  top->point2->setCoords (keyEnd, valueEnd);
  top->setSelectable (false);
  top->setPen (QPen (Qt::DashLine));
  customPlot->addItem (top);

  QCPItemStraightLine* const bot (new QCPItemStraightLine (customPlot));
  bot->setPen (QPen (color));
  bot->point1->setCoords (keyStart, valueStart);
  bot->point2->setCoords (keyEnd, valueStart);
  bot->setSelectable (false);
  bot->setPen (QPen (Qt::DashLine));
  customPlot->addItem (bot);

  QCPItemStraightLine* const left (new QCPItemStraightLine (customPlot));
  left->setPen (QPen (color));
  left->point1->setCoords (keyStart, valueStart);
  left->point2->setCoords (keyStart, valueEnd);
  left->setSelectable (false);
  left->setPen (QPen (Qt::DashLine));
  customPlot->addItem (left);

  QCPItemStraightLine* const right (new QCPItemStraightLine (customPlot));
  right->setPen (QPen (color));
  right->point1->setCoords (keyEnd, valueStart);
  right->point2->setCoords (keyEnd, valueEnd);
  right->setSelectable (false);
  right->setPen (QPen (Qt::DashLine));
  customPlot->addItem (right);
}

#pragma endregion // private methods
