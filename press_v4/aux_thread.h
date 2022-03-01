#ifndef AUX_THREAD_H
#define AUX_THREAD_H

#include <QWidget>
#include <QTimer>
#include <QTime>
#include <QDebug>
#include <QThread>
#include <QtConcurrentRun>
#include <QSerialPort>
#include <QSerialPortInfo>

typedef char s8;
typedef unsigned char u8;
typedef unsigned int u32;
typedef signed int s32;

namespace Ui {
    class aux_thread;
}
class PressApp;

class aux_thread : public QWidget
{
    Q_OBJECT

public:
    explicit aux_thread(PressApp *master, QWidget *parent = 0);
    ~aux_thread();
    Ui::aux_thread *ui;

    PressApp *pressApp;

    QSerialPort *serial;

    bool command_silencer;
    bool test_finished;
    bool test_label_status;
    bool run_pid;
    bool hard_stop;
    bool max_load_error;
    u8 breaking_case;
    u8 relay_auto_man;
    u8 relay_start_stop;
    double dac_value;
    float load_value;
    float filtered_load_value;
    float ch1_value;
    float ch2_value;
    float ch3_value;
    float ch4_value;
    float stress;
    float max_load_value;
    float max_load_value_for_peak_detection;
    float peak_load;
    float peak_stress;
    float current_pace_rate;
    bool step_response_first_in;
    bool communication_established;
    bool PID_first_in;

    struct _to_gui{
        bool hit;
        u8 gain[4];
        s8 raw_sign[4];
        u32 raw[4];
        float calibrated[4];
        bool test_finished;
    };
    struct _to_gui to_gui;

signals:
    void cohen_coon_kp(QString);
    void cohen_coon_ki(QString);
    void cohen_coon_kd(QString);
    void let_step_response(void);

public slots:
    void read_parameters(void);
    double IIR_Filter_double_pace_rate(double* raw_signal);
    float IIR_Filter_double_load(float *raw_signal);
    double discrete_PID_dac(void);

private:
    QTimer* sender_timer;
    QTime   pid_delta_t_dac;

private slots:
    u8 read_data_order(QByteArray base_array,const char *array, u8 first_index, u8 last_index);
    void send_data_order(char *base_array,const char *array, u8 first_index, u8 last_index);
    u32 crc_chk(u8* data, u8 length);
    void serial_port_setup(void);

    void fuzpid_thread_handler(void);
    void always_send(void);
    void EOL(char *base_array, u8 i);
    void step_response(void);

};

#endif // AUX_THREAD_H
