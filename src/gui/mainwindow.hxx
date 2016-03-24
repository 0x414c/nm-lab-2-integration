#ifndef MAINWINDOW_HXX
#define MAINWINDOW_HXX


#include <functional>

#include <QColor>
#include <QMainWindow>
#include <QMouseEvent>
#include <QString>
#include <QWheelEvent>
#include <QWidget>

#include "qcustomplot/qcustomplot.h"

#include "../math/numerictypes.hxx"


namespace Ui
{
  class MainWindow;
}


class MainWindow :
  public QMainWindow
{
  Q_OBJECT


  public:
    explicit MainWindow (QWidget* parent = nullptr);

    ~MainWindow (void);


  private slots:
    void on_funcParam_alpha_DoubleSpinBox_valueChanged (double arg1);
    void on_funcParam_beta_DoubleSpinBox_valueChanged (double arg1);
    void on_funcParam_gamma_DoubleSpinBox_valueChanged (double arg1);
    void on_funcParam_delta_DoubleSpinBox_valueChanged (double arg1);
    void on_funcParam_epsilon_DoubleSpinBox_valueChanged (double arg1);
    void on_funcParam_mu_DoubleSpinBox_valueChanged (double arg1);

    void on_plotParam_A_DoubleSpinBox_valueChanged (double arg1);
    void on_plotParam_B_DoubleSpinBox_valueChanged (double arg1);
    void on_plotParam_C_DoubleSpinBox_valueChanged (double arg1);
    void on_plotParam_D_DoubleSpinBox_valueChanged (double arg1);

    void on_integrParam_n_0_SpinBox_valueChanged (int arg1);
    void on_integrParam_delta_SpinBox_valueChanged (int arg1);
    void on_integrParam_a_DoubleSpinBox_valueChanged (double arg1);
    void on_integrParam_b_DoubleSpinBox_valueChanged (double arg1);

    void on_ctrl_plot_PushButton_clicked (void);
    void on_ctrl_reset_PushButton_clicked (void);
    void on_ctrl_liveUpdate_CheckBox_toggled (bool checked);

    void on_plot_functions_CustomPlot_selectionChangedByUser (void);
    void on_plot_functions_CustomPlot_mousePress (QMouseEvent* ev);
    void on_plot_functions_CustomPlot_mouseWheel (QWheelEvent* ev);
    void on_plot_functions_CustomPlot_mouseMove (QMouseEvent* ev);

    void on_integrParam_alpha_RadioButton_toggled (bool checked);
    void on_integrParam_beta_RadioButton_toggled (bool checked);
    void on_integrParam_gamma_RadioButton_toggled (bool checked);
    void on_integrParam_delta_RadioButton_toggled (bool checked);
    void on_integrParam_epsilon_RadioButton_toggled (bool checked);
    void on_integrParam_mu_RadioButton_toggled (bool checked);


  private:
    enum struct ParamType
    {
      None, Alpha, Beta, Gamma, Delta, Epsilon, Mu
    };


    Ui::MainWindow* ui_ = nullptr;

    double funcParam_alpha_ = 0.;
    double funcParam_beta_ = 0.;
    double funcParam_gamma_ = 0.;
    double funcParam_delta_ = 0.;
    double funcParam_epsilon_ = 0.;
    double funcParam_mu_ = 0.;

    double plotParam_A_ = 0.;
    double plotParam_B_ = 0.;
    double plotParam_C_ = 0.;
    double plotParam_D_ = 0.;

    int integrParam_n_0_ = 2;
    double integrParam_delta_ = 0.;
    double integrParam_a_ = 0.;
    double integrParam_b_ = 0.;

    double prop_x_max_ = 0.;

    ParamType paramType_ = ParamType::None;

    bool liveUpdateEnabled_ = false;
    bool isDirty_ = false;

    void initSignalsAndSlots (void);
    void setDefaults (void);

    void setDirty (bool isDirty = true);

    void initCustomPlot (QCustomPlot* customPlot);
    void enableCustomPlot (QCustomPlot* customPlot, bool enabled = true);
    void clearCustomPlot (QCustomPlot* customPlot);
    void updateCustomPlot (QCustomPlot* customPlot);

    void plotFunction (
      const std::function<Math::real_t (Math::real_t)>& f, int samplesCount,
      double keyStart, double keyEnd, double valueStart, double valueEnd,
      const QColor& color, QCustomPlot* customPlot, const QString& name
    );

    void plotBoundingBox (
      double keyStart, double keyEnd, double valueStart, double valueEnd,
      const QColor& color, QCustomPlot* customPlot
    );
};


#endif // MAINWINDOW_HXX
