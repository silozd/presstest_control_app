#ifndef PRESSAPP_H
#define PRESSAPP_H

#include "pressapp.h"
#include "ui_pressapp.h"
#include "remoteconnection.h"
#include "qcustomplot.h"
#include "editreport.h"
#include "ui_editreport.h"
#include "aux_thread.h"
#include <QDialog>
#include <QFile>

#define TAB_SPECIMEN    0
#define TAB_PARAMETERS  1
#define TAB_CHANNELS    2
#define TAB_GAIN        3
#define TAB_CALIB       4
#define TAB_PID         5

#define COMPRESSION     0
#define FLEXURAL        1
#define SPLIT_TENSILE   2

#define COMPRESSION_CUBE            0
#define COMPRESSION_CYLINDER        1
#define COMPRESSION_MASONRY_UNIT    2

#define FLEXURAL_BEAM3              0
#define FLEXURAL_BEAM4              1
#define FLEXURAL_KERB               2
#define FLEXURAL_FLAGSTONE          3

#define SPLIT_TENSILE_CUBE          0
#define SPLIT_TENSILE_CYLINDER      1
#define SPLIT_TENSILE_PAVING_STONE  2

#define KN_MM       0
#define LBF_IN      1
#define KGF_CM      2

#define FRAME1      0
#define FRAME2      1

#define AUTO        0
#define MAN         1

#define _PDF        0
#define _TXT        1

# define M_PI		3.14159265358979323846

#define RELAY_OFF           48
#define RELAY_ON            49

#define TEST_STOPPED        0
#define TEST_RUNNING        1
#define TEST_PAUSED         2
#define TEST_JUST_FINISHED  3

#define _10V        0
#define _5V         1
#define _2_5V       2
#define _1V         3
#define _500V       4
#define _250mV      5
#define _125mV      6
#define _50mV       7
#define _25mV       8
#define _10mV       9
#define _5mV        10

#define CH_1    0
#define CH_2    1
#define CH_3    2
#define CH_4    3

typedef unsigned char u8;
typedef unsigned int u32;

namespace Ui {
class PressApp;
}

class PressApp : public QMainWindow
{
    Q_OBJECT

public:
    explicit PressApp(QWidget *parent = 0);
    ~PressApp();

    Ui::PressApp *ui;
    RemoteConnection *remote;
    QCustomPlot *customPlot;
    EditReport *editReport;
    aux_thread *auxthread;
    QString header_report;
    QString testName_report;

    //u8 templ_type;
    QPrinter pdf_printer;
    QString pdf_fileName;
    QString pdf_path;
    int h_label;
    int t_label;

    struct _cal{
        double real_val[8];
        float assigned_val[8];
        u8 point_no;
    };
    struct _pid {
        double Kp;
        double Ki;
        u32 Kd;
    };

    struct _real_time{
        int test_no;
        QString status;
        double area;
        double load;
        double stress;
        double ch2;
        double ch3;
        double ch4;
    };
    struct _real_time real_time;
    struct _param{
        u8 dp_load;
        u8 dp_stress;
        u8 dp_ch2;
        u8 dp_ch3;
        u8 dp_ch4;
        double max_load;
        double zero_suppression;
        double load_treshold;
        u8 break_percentage;
        u8 speciment_type_index_compression;
        u8 speciment_type_index_flexural;
        u8 speciment_type_index_split_tensile;
        double load_tare_limit;
        double pace_rate;
        double pace_mPa;
        double cube_w;
        double cube_l;
        double cube_h;
        double masonry_unit_l;
        double masonry_unit_w;
        double cylindrical_d;
        double cylindrical_l;
        double split_cube_w;
        double split_cylinder_l;
        double split_cylinder_d;
        double split_paving_stone_d;
        double split_paving_stone_l;
        double beam3_l;
        double beam3_b;
        double beam3_d;
        double beam4_l;
        double beam4_s;
        double beam4_b;
        double beam4_d;
        double flagstone_l;
        double flagstone_s;
        double flagstone_b;
        double flagstone_d;
        double kerb_a;
        double kerb_b;
        double kerb_c;
        double kerb_d;
        double kerb_l;
        u8 step_transition_time;
        u8 guideline_spacing;
        double irregular_area;
        u8 start_speed_percentage;
        u8 axes_radiobutton_no;
        bool ch2_status;
        bool ch3_status;
        bool ch4_status;
        u8 autotuning_first_speed;
        u8 autotuning_second_speed;
        u8 test_type;
        u8 ch_unit;
        u8 ch2_unit;
        u8 ch3_unit;
        u8 ch4_unit;
        QString ch2_label;
        QString ch3_label;
        QString ch4_label;
        u8 gain[4];
        _cal cal[4];
        _pid pid[13];
    };
    struct _param parameters[2];

    u8 test_type;
    u8 specimen_type;
    u8 current_page;
    u8 current_cal_channel;
    u8 unit_index;
    u8 current_frame;
    u8 control_mode;
    u8 automatic_print;
    u32 current_channel_data;
    u32 current_test_no;

    QString start_date;
    QString start_time;
    QString finish_time;
    QString dimensions;
    QString material_type;

    double calc_area;
    double load_unit_multiplier;
    double length_unit_multiplier;
    double area_unit_multiplier;

    QString test_type_name;
    QString specimen_name;
    QString load_unit;
    QString stress_unit;
    QString length_unit;
    QString start_date_filename_arg;
    QString userDir;
    QString res_fileName;
    QString custom_path;

    QTimer *resizer;
    QTimer *_time;
    QTimer *eth_timer;
    QTimer *_100_msec_timer;
    QElapsedTimer global_running_timer;

    QDialog *dia_expand;

    QDialog *dialog_psw;
    QGridLayout *grid_dialogPsw;
    QWidget *wdg_dialogPsw;
    QWidget *psw_widget;                        // for mouse event permission
    QLabel *lbl_psw;
    QLineEdit *password;
    QPushButton *btn_newPsw;

    QStringList str_users;
    QStringList compression_list;
    QStringList flexural_list;
    QStringList splitTensile_list;
    QCPPlottableLegendItem *plItem;

    QGridLayout *grid_plotArea;

    int ScreenWidth, ScreenHeight;
    int Fontsize;
    int hr;
    int vr;
    int pr;
    int TabW, TabH;
    int AppW, AppH;
    int BtnH;
    bool _start_com = false;
    bool mouseevent = false;
    bool results_saved = false;
    bool custom_file_loaded = false;
    char show_graph;
    char statu_device;
    double key;
    int format_type;
    int graph_index;
    int device_stopped = 0;
    int device_running = 1;
    int statu;
    int test_no;

    // names :
    static bool label_name_compare(QLabel *p1, QLabel *p2);
    bool removeDir(const QString & dirName);
    int dac_voltage_to_raw(double val);

// // GUI'DEN  ////////////////////////////////////////
    struct chan {
        double max_value_x;
        double min_value_x;
        double max_value_y;
        double min_value_y;
        u32 counter;
        double xval[1200];
        double yval[1200];
        QTime elapsed_timer;
    };
    struct chan channel[2];
    u8 usart_signalmapper_no;
    bool bad_calibration_file;
    QTimer *gain_cal_send_timer;
    bool device_opening;
    char cal_tab_raw_sign;
    u8 precision[4];
    QList<QSpinBox*> spinBox_cal_raw_value;
    QList<QDoubleSpinBox*> doubleSpinBox_cal_point_value;
    QList<QLabel*> label_gain;
    QList<QLabel*> label_adc_cal_channel;
    QList<QLabel*> label_adc_channel;
    bool step_response_status;
    QTimer *command_send_protection_wait_timer;
    double tared_val;
    QDoubleSpinBox *doubleSpinBox_load_tare_limit;
    bool data_changed;
    QSignalMapper *signalMapper;
    QSignalMapper *signalMapper_usart;
    QFile excel_file;
    double paving_stone_k;
    u8 test_status;
    int signal_id;  // sila
    int step_res_clicked = 0;
// //////////////////////////////////////////////////////////

protected :


public slots:
// // GUI'DEN ///////////// ////////////////////////////////////////////
    void EOL(char *base_array, u8 i);
    u32 crc_chk(u8* data, u8 length);
    u32 IIR_Filter(u32* raw_signal,u8 filter_coefficient);
    u32 FIR_Filter(u32* raw_signal,u8 filter_coefficient);
    u32 BIQUAD_Filter(u32* raw_signal,u8 filter_coefficient);
    u32 BIQUAD_Filter_1(u32* raw_signal,u8 filter_coefficient);
    void send_data_order(char *base_array,const char *array, u8 first_index, u8 last_index);
    void command_sending_protection(void);
    void send_gains_and_cals(void);
    void send_gain(int gain);
    void cal_assignment(int);
    void send_new_calibration_values(u8 chan);
    void send_calibration_values(void);
    void cal_channel_change(int channel);
    void tare_channel(int chan);
    void tare_in_calibration(void);
    void pid_combobox_handle(int val);
    void save_pid_values();
    void save_pid_values_to_all();
    void step_response_handle(void);
    void relay_on(void);
    void relay_off(void);
    void usart_signalmapper(void);
    void usart_signalmapper_handler(int id);
    void usart_gain_signalmapper();   // sila
    void print_test_results();
    void _100_msec_handler();
// /////////////////////////////////////////////////////////////////////

    int GetScreenHRes(int s);
    int GetScreenVRes(int s);

    void setup_GUI();
    void set_declaration();
    void setup_PLOT();
    void setup_users();
    void calculate_area();

    void saveParameters(QString file_name);
    void readParameters(QString file_name);

    // results :
    void on_pushButton_saveResults_clicked();
    void on_pushButton_printResults_clicked();
    void on_pushButton_openFile_view_clicked();
    void on_pushButton_editFile_clicked();
    void on_pushButton_printPlot_clicked();
    void on_pushButton_quitFile_clicked();

private slots:
    void resize_window();
    void start_comm();
    void end_comm();
    void periodic_response_handler(QByteArray datagram);
    void set_test_status();
    void read_parameters_from_the_device(void);
    void write_parameters_to_the_device(void);
    void write_specimens_to_the_device(void);
    void read_specimens_from_the_device(void);

    void on_toolBox_app_currentChanged(int tab);
    void on_pushButton_toApp_clicked();
    void on_pushButton_connect_clicked();
    void on_pushButton_cutconnect_clicked();
    void on_pushButton_saveFile_clicked();
    void on_pushButton_openFile_clicked();
    void on_pushButton_startTest_clicked();
    void on_pushButton_pauseTest_clicked();
    void on_pushButton_stopTest_clicked();
    void on_pushButton_refreshTest_clicked();
    void on_btn_okSpecimen_clicked();
    void on_btn_expand_clicked();       // deneme
    void on_pushButton_write_to_device_clicked();
    void on_pushButton_read_from_device_clicked();
    void on_btn_saveSet_clicked();
    void on_pushButton_removeUser_clicked();
    void on_pushButton_load_factory_settings_clicked();
    void on_combo_testType_currentIndexChanged(int index);
    void on_comboBox_specimen_currentIndexChanged(int index);
    void on_comboBox_unit_currentIndexChanged(int index);
    void on_comboBox_unit_ch_currentIndexChanged(int index);
    void on_combo_scrRes_currentIndexChanged(int index);
    void on_comboBox_formatFile_currentIndexChanged(int index);
    void on_comboBox_standard_currentIndexChanged(int index);
    void assign_frame();
    void assign_controlType();
    void assign_printMode();
    void record_results(int no);
    void pace_rate_handler_kn(void);
    void pace_rate_handler_mpa(void);
    void on_loadFinished(bool ok);

    // password :
    void get_password();
    void on_pushButton_pswSave_clicked();
    void authorization_event();
    void authorize();

    // plot :
    void plot_graph();
    void selectionChanged();
    void mousePress();
    void mouseWheel();
    void contextMenuRequest(QPoint pos);
    void moveLegend();
    void graphClicked(QCPAbstractPlottable *plottable, int dataIndex);
    void axisLabelDoubleClick(QCPAxis *axis, QCPAxis::SelectablePart part);
    void legendDoubleClick(QCPLegend *legend, QCPAbstractLegendItem *item);
    void renderPlot(QPrinter *printer);



};

#endif // PRESSAPP_H

