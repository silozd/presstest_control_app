/****************************************************************************
** Meta object code from reading C++ file 'pressapp.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.9.5)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../press_v4/pressapp.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'pressapp.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.9.5. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_PressApp_t {
    QByteArrayData data[139];
    char stringdata0[2478];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_PressApp_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_PressApp_t qt_meta_stringdata_PressApp = {
    {
QT_MOC_LITERAL(0, 0, 8), // "PressApp"
QT_MOC_LITERAL(1, 9, 3), // "EOL"
QT_MOC_LITERAL(2, 13, 0), // ""
QT_MOC_LITERAL(3, 14, 5), // "char*"
QT_MOC_LITERAL(4, 20, 10), // "base_array"
QT_MOC_LITERAL(5, 31, 2), // "u8"
QT_MOC_LITERAL(6, 34, 1), // "i"
QT_MOC_LITERAL(7, 36, 7), // "crc_chk"
QT_MOC_LITERAL(8, 44, 3), // "u32"
QT_MOC_LITERAL(9, 48, 3), // "u8*"
QT_MOC_LITERAL(10, 52, 4), // "data"
QT_MOC_LITERAL(11, 57, 6), // "length"
QT_MOC_LITERAL(12, 64, 10), // "IIR_Filter"
QT_MOC_LITERAL(13, 75, 4), // "u32*"
QT_MOC_LITERAL(14, 80, 10), // "raw_signal"
QT_MOC_LITERAL(15, 91, 18), // "filter_coefficient"
QT_MOC_LITERAL(16, 110, 10), // "FIR_Filter"
QT_MOC_LITERAL(17, 121, 13), // "BIQUAD_Filter"
QT_MOC_LITERAL(18, 135, 15), // "BIQUAD_Filter_1"
QT_MOC_LITERAL(19, 151, 15), // "send_data_order"
QT_MOC_LITERAL(20, 167, 11), // "const char*"
QT_MOC_LITERAL(21, 179, 5), // "array"
QT_MOC_LITERAL(22, 185, 11), // "first_index"
QT_MOC_LITERAL(23, 197, 10), // "last_index"
QT_MOC_LITERAL(24, 208, 26), // "command_sending_protection"
QT_MOC_LITERAL(25, 235, 19), // "send_gains_and_cals"
QT_MOC_LITERAL(26, 255, 9), // "send_gain"
QT_MOC_LITERAL(27, 265, 4), // "gain"
QT_MOC_LITERAL(28, 270, 14), // "cal_assignment"
QT_MOC_LITERAL(29, 285, 27), // "send_new_calibration_values"
QT_MOC_LITERAL(30, 313, 4), // "chan"
QT_MOC_LITERAL(31, 318, 23), // "send_calibration_values"
QT_MOC_LITERAL(32, 342, 18), // "cal_channel_change"
QT_MOC_LITERAL(33, 361, 7), // "channel"
QT_MOC_LITERAL(34, 369, 12), // "tare_channel"
QT_MOC_LITERAL(35, 382, 19), // "tare_in_calibration"
QT_MOC_LITERAL(36, 402, 19), // "pid_combobox_handle"
QT_MOC_LITERAL(37, 422, 3), // "val"
QT_MOC_LITERAL(38, 426, 15), // "save_pid_values"
QT_MOC_LITERAL(39, 442, 22), // "save_pid_values_to_all"
QT_MOC_LITERAL(40, 465, 20), // "step_response_handle"
QT_MOC_LITERAL(41, 486, 8), // "relay_on"
QT_MOC_LITERAL(42, 495, 9), // "relay_off"
QT_MOC_LITERAL(43, 505, 18), // "usart_signalmapper"
QT_MOC_LITERAL(44, 524, 26), // "usart_signalmapper_handler"
QT_MOC_LITERAL(45, 551, 2), // "id"
QT_MOC_LITERAL(46, 554, 23), // "usart_gain_signalmapper"
QT_MOC_LITERAL(47, 578, 18), // "print_test_results"
QT_MOC_LITERAL(48, 597, 17), // "_100_msec_handler"
QT_MOC_LITERAL(49, 615, 13), // "GetScreenHRes"
QT_MOC_LITERAL(50, 629, 1), // "s"
QT_MOC_LITERAL(51, 631, 13), // "GetScreenVRes"
QT_MOC_LITERAL(52, 645, 9), // "setup_GUI"
QT_MOC_LITERAL(53, 655, 15), // "set_declaration"
QT_MOC_LITERAL(54, 671, 10), // "setup_PLOT"
QT_MOC_LITERAL(55, 682, 11), // "setup_users"
QT_MOC_LITERAL(56, 694, 14), // "calculate_area"
QT_MOC_LITERAL(57, 709, 14), // "saveParameters"
QT_MOC_LITERAL(58, 724, 9), // "file_name"
QT_MOC_LITERAL(59, 734, 14), // "readParameters"
QT_MOC_LITERAL(60, 749, 33), // "on_pushButton_saveResults_cli..."
QT_MOC_LITERAL(61, 783, 34), // "on_pushButton_printResults_cl..."
QT_MOC_LITERAL(62, 818, 35), // "on_pushButton_openFile_view_c..."
QT_MOC_LITERAL(63, 854, 30), // "on_pushButton_editFile_clicked"
QT_MOC_LITERAL(64, 885, 31), // "on_pushButton_printPlot_clicked"
QT_MOC_LITERAL(65, 917, 30), // "on_pushButton_quitFile_clicked"
QT_MOC_LITERAL(66, 948, 13), // "resize_window"
QT_MOC_LITERAL(67, 962, 10), // "start_comm"
QT_MOC_LITERAL(68, 973, 8), // "end_comm"
QT_MOC_LITERAL(69, 982, 25), // "periodic_response_handler"
QT_MOC_LITERAL(70, 1008, 8), // "datagram"
QT_MOC_LITERAL(71, 1017, 15), // "set_test_status"
QT_MOC_LITERAL(72, 1033, 31), // "read_parameters_from_the_device"
QT_MOC_LITERAL(73, 1065, 30), // "write_parameters_to_the_device"
QT_MOC_LITERAL(74, 1096, 29), // "write_specimens_to_the_device"
QT_MOC_LITERAL(75, 1126, 30), // "read_specimens_from_the_device"
QT_MOC_LITERAL(76, 1157, 29), // "on_toolBox_app_currentChanged"
QT_MOC_LITERAL(77, 1187, 3), // "tab"
QT_MOC_LITERAL(78, 1191, 27), // "on_pushButton_toApp_clicked"
QT_MOC_LITERAL(79, 1219, 29), // "on_pushButton_connect_clicked"
QT_MOC_LITERAL(80, 1249, 32), // "on_pushButton_cutconnect_clicked"
QT_MOC_LITERAL(81, 1282, 30), // "on_pushButton_saveFile_clicked"
QT_MOC_LITERAL(82, 1313, 30), // "on_pushButton_openFile_clicked"
QT_MOC_LITERAL(83, 1344, 31), // "on_pushButton_startTest_clicked"
QT_MOC_LITERAL(84, 1376, 31), // "on_pushButton_pauseTest_clicked"
QT_MOC_LITERAL(85, 1408, 30), // "on_pushButton_stopTest_clicked"
QT_MOC_LITERAL(86, 1439, 33), // "on_pushButton_refreshTest_cli..."
QT_MOC_LITERAL(87, 1473, 25), // "on_btn_okSpecimen_clicked"
QT_MOC_LITERAL(88, 1499, 21), // "on_btn_expand_clicked"
QT_MOC_LITERAL(89, 1521, 37), // "on_pushButton_write_to_device..."
QT_MOC_LITERAL(90, 1559, 38), // "on_pushButton_read_from_devic..."
QT_MOC_LITERAL(91, 1598, 22), // "on_btn_saveSet_clicked"
QT_MOC_LITERAL(92, 1621, 32), // "on_pushButton_removeUser_clicked"
QT_MOC_LITERAL(93, 1654, 43), // "on_pushButton_load_factory_se..."
QT_MOC_LITERAL(94, 1698, 37), // "on_combo_testType_currentInde..."
QT_MOC_LITERAL(95, 1736, 5), // "index"
QT_MOC_LITERAL(96, 1742, 40), // "on_comboBox_specimen_currentI..."
QT_MOC_LITERAL(97, 1783, 36), // "on_comboBox_unit_currentIndex..."
QT_MOC_LITERAL(98, 1820, 39), // "on_comboBox_unit_ch_currentIn..."
QT_MOC_LITERAL(99, 1860, 35), // "on_combo_scrRes_currentIndexC..."
QT_MOC_LITERAL(100, 1896, 42), // "on_comboBox_formatFile_curren..."
QT_MOC_LITERAL(101, 1939, 40), // "on_comboBox_standard_currentI..."
QT_MOC_LITERAL(102, 1980, 12), // "assign_frame"
QT_MOC_LITERAL(103, 1993, 18), // "assign_controlType"
QT_MOC_LITERAL(104, 2012, 16), // "assign_printMode"
QT_MOC_LITERAL(105, 2029, 14), // "record_results"
QT_MOC_LITERAL(106, 2044, 2), // "no"
QT_MOC_LITERAL(107, 2047, 20), // "pace_rate_handler_kn"
QT_MOC_LITERAL(108, 2068, 21), // "pace_rate_handler_mpa"
QT_MOC_LITERAL(109, 2090, 15), // "on_loadFinished"
QT_MOC_LITERAL(110, 2106, 2), // "ok"
QT_MOC_LITERAL(111, 2109, 12), // "get_password"
QT_MOC_LITERAL(112, 2122, 29), // "on_pushButton_pswSave_clicked"
QT_MOC_LITERAL(113, 2152, 19), // "authorization_event"
QT_MOC_LITERAL(114, 2172, 9), // "authorize"
QT_MOC_LITERAL(115, 2182, 10), // "plot_graph"
QT_MOC_LITERAL(116, 2193, 16), // "selectionChanged"
QT_MOC_LITERAL(117, 2210, 10), // "mousePress"
QT_MOC_LITERAL(118, 2221, 10), // "mouseWheel"
QT_MOC_LITERAL(119, 2232, 18), // "contextMenuRequest"
QT_MOC_LITERAL(120, 2251, 3), // "pos"
QT_MOC_LITERAL(121, 2255, 10), // "moveLegend"
QT_MOC_LITERAL(122, 2266, 12), // "graphClicked"
QT_MOC_LITERAL(123, 2279, 21), // "QCPAbstractPlottable*"
QT_MOC_LITERAL(124, 2301, 9), // "plottable"
QT_MOC_LITERAL(125, 2311, 9), // "dataIndex"
QT_MOC_LITERAL(126, 2321, 20), // "axisLabelDoubleClick"
QT_MOC_LITERAL(127, 2342, 8), // "QCPAxis*"
QT_MOC_LITERAL(128, 2351, 4), // "axis"
QT_MOC_LITERAL(129, 2356, 23), // "QCPAxis::SelectablePart"
QT_MOC_LITERAL(130, 2380, 4), // "part"
QT_MOC_LITERAL(131, 2385, 17), // "legendDoubleClick"
QT_MOC_LITERAL(132, 2403, 10), // "QCPLegend*"
QT_MOC_LITERAL(133, 2414, 6), // "legend"
QT_MOC_LITERAL(134, 2421, 22), // "QCPAbstractLegendItem*"
QT_MOC_LITERAL(135, 2444, 4), // "item"
QT_MOC_LITERAL(136, 2449, 10), // "renderPlot"
QT_MOC_LITERAL(137, 2460, 9), // "QPrinter*"
QT_MOC_LITERAL(138, 2470, 7) // "printer"

    },
    "PressApp\0EOL\0\0char*\0base_array\0u8\0i\0"
    "crc_chk\0u32\0u8*\0data\0length\0IIR_Filter\0"
    "u32*\0raw_signal\0filter_coefficient\0"
    "FIR_Filter\0BIQUAD_Filter\0BIQUAD_Filter_1\0"
    "send_data_order\0const char*\0array\0"
    "first_index\0last_index\0"
    "command_sending_protection\0"
    "send_gains_and_cals\0send_gain\0gain\0"
    "cal_assignment\0send_new_calibration_values\0"
    "chan\0send_calibration_values\0"
    "cal_channel_change\0channel\0tare_channel\0"
    "tare_in_calibration\0pid_combobox_handle\0"
    "val\0save_pid_values\0save_pid_values_to_all\0"
    "step_response_handle\0relay_on\0relay_off\0"
    "usart_signalmapper\0usart_signalmapper_handler\0"
    "id\0usart_gain_signalmapper\0"
    "print_test_results\0_100_msec_handler\0"
    "GetScreenHRes\0s\0GetScreenVRes\0setup_GUI\0"
    "set_declaration\0setup_PLOT\0setup_users\0"
    "calculate_area\0saveParameters\0file_name\0"
    "readParameters\0on_pushButton_saveResults_clicked\0"
    "on_pushButton_printResults_clicked\0"
    "on_pushButton_openFile_view_clicked\0"
    "on_pushButton_editFile_clicked\0"
    "on_pushButton_printPlot_clicked\0"
    "on_pushButton_quitFile_clicked\0"
    "resize_window\0start_comm\0end_comm\0"
    "periodic_response_handler\0datagram\0"
    "set_test_status\0read_parameters_from_the_device\0"
    "write_parameters_to_the_device\0"
    "write_specimens_to_the_device\0"
    "read_specimens_from_the_device\0"
    "on_toolBox_app_currentChanged\0tab\0"
    "on_pushButton_toApp_clicked\0"
    "on_pushButton_connect_clicked\0"
    "on_pushButton_cutconnect_clicked\0"
    "on_pushButton_saveFile_clicked\0"
    "on_pushButton_openFile_clicked\0"
    "on_pushButton_startTest_clicked\0"
    "on_pushButton_pauseTest_clicked\0"
    "on_pushButton_stopTest_clicked\0"
    "on_pushButton_refreshTest_clicked\0"
    "on_btn_okSpecimen_clicked\0"
    "on_btn_expand_clicked\0"
    "on_pushButton_write_to_device_clicked\0"
    "on_pushButton_read_from_device_clicked\0"
    "on_btn_saveSet_clicked\0"
    "on_pushButton_removeUser_clicked\0"
    "on_pushButton_load_factory_settings_clicked\0"
    "on_combo_testType_currentIndexChanged\0"
    "index\0on_comboBox_specimen_currentIndexChanged\0"
    "on_comboBox_unit_currentIndexChanged\0"
    "on_comboBox_unit_ch_currentIndexChanged\0"
    "on_combo_scrRes_currentIndexChanged\0"
    "on_comboBox_formatFile_currentIndexChanged\0"
    "on_comboBox_standard_currentIndexChanged\0"
    "assign_frame\0assign_controlType\0"
    "assign_printMode\0record_results\0no\0"
    "pace_rate_handler_kn\0pace_rate_handler_mpa\0"
    "on_loadFinished\0ok\0get_password\0"
    "on_pushButton_pswSave_clicked\0"
    "authorization_event\0authorize\0plot_graph\0"
    "selectionChanged\0mousePress\0mouseWheel\0"
    "contextMenuRequest\0pos\0moveLegend\0"
    "graphClicked\0QCPAbstractPlottable*\0"
    "plottable\0dataIndex\0axisLabelDoubleClick\0"
    "QCPAxis*\0axis\0QCPAxis::SelectablePart\0"
    "part\0legendDoubleClick\0QCPLegend*\0"
    "legend\0QCPAbstractLegendItem*\0item\0"
    "renderPlot\0QPrinter*\0printer"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_PressApp[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      96,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    2,  494,    2, 0x0a /* Public */,
       7,    2,  499,    2, 0x0a /* Public */,
      12,    2,  504,    2, 0x0a /* Public */,
      16,    2,  509,    2, 0x0a /* Public */,
      17,    2,  514,    2, 0x0a /* Public */,
      18,    2,  519,    2, 0x0a /* Public */,
      19,    4,  524,    2, 0x0a /* Public */,
      24,    0,  533,    2, 0x0a /* Public */,
      25,    0,  534,    2, 0x0a /* Public */,
      26,    1,  535,    2, 0x0a /* Public */,
      28,    1,  538,    2, 0x0a /* Public */,
      29,    1,  541,    2, 0x0a /* Public */,
      31,    0,  544,    2, 0x0a /* Public */,
      32,    1,  545,    2, 0x0a /* Public */,
      34,    1,  548,    2, 0x0a /* Public */,
      35,    0,  551,    2, 0x0a /* Public */,
      36,    1,  552,    2, 0x0a /* Public */,
      38,    0,  555,    2, 0x0a /* Public */,
      39,    0,  556,    2, 0x0a /* Public */,
      40,    0,  557,    2, 0x0a /* Public */,
      41,    0,  558,    2, 0x0a /* Public */,
      42,    0,  559,    2, 0x0a /* Public */,
      43,    0,  560,    2, 0x0a /* Public */,
      44,    1,  561,    2, 0x0a /* Public */,
      46,    0,  564,    2, 0x0a /* Public */,
      47,    0,  565,    2, 0x0a /* Public */,
      48,    0,  566,    2, 0x0a /* Public */,
      49,    1,  567,    2, 0x0a /* Public */,
      51,    1,  570,    2, 0x0a /* Public */,
      52,    0,  573,    2, 0x0a /* Public */,
      53,    0,  574,    2, 0x0a /* Public */,
      54,    0,  575,    2, 0x0a /* Public */,
      55,    0,  576,    2, 0x0a /* Public */,
      56,    0,  577,    2, 0x0a /* Public */,
      57,    1,  578,    2, 0x0a /* Public */,
      59,    1,  581,    2, 0x0a /* Public */,
      60,    0,  584,    2, 0x0a /* Public */,
      61,    0,  585,    2, 0x0a /* Public */,
      62,    0,  586,    2, 0x0a /* Public */,
      63,    0,  587,    2, 0x0a /* Public */,
      64,    0,  588,    2, 0x0a /* Public */,
      65,    0,  589,    2, 0x0a /* Public */,
      66,    0,  590,    2, 0x08 /* Private */,
      67,    0,  591,    2, 0x08 /* Private */,
      68,    0,  592,    2, 0x08 /* Private */,
      69,    1,  593,    2, 0x08 /* Private */,
      71,    0,  596,    2, 0x08 /* Private */,
      72,    0,  597,    2, 0x08 /* Private */,
      73,    0,  598,    2, 0x08 /* Private */,
      74,    0,  599,    2, 0x08 /* Private */,
      75,    0,  600,    2, 0x08 /* Private */,
      76,    1,  601,    2, 0x08 /* Private */,
      78,    0,  604,    2, 0x08 /* Private */,
      79,    0,  605,    2, 0x08 /* Private */,
      80,    0,  606,    2, 0x08 /* Private */,
      81,    0,  607,    2, 0x08 /* Private */,
      82,    0,  608,    2, 0x08 /* Private */,
      83,    0,  609,    2, 0x08 /* Private */,
      84,    0,  610,    2, 0x08 /* Private */,
      85,    0,  611,    2, 0x08 /* Private */,
      86,    0,  612,    2, 0x08 /* Private */,
      87,    0,  613,    2, 0x08 /* Private */,
      88,    0,  614,    2, 0x08 /* Private */,
      89,    0,  615,    2, 0x08 /* Private */,
      90,    0,  616,    2, 0x08 /* Private */,
      91,    0,  617,    2, 0x08 /* Private */,
      92,    0,  618,    2, 0x08 /* Private */,
      93,    0,  619,    2, 0x08 /* Private */,
      94,    1,  620,    2, 0x08 /* Private */,
      96,    1,  623,    2, 0x08 /* Private */,
      97,    1,  626,    2, 0x08 /* Private */,
      98,    1,  629,    2, 0x08 /* Private */,
      99,    1,  632,    2, 0x08 /* Private */,
     100,    1,  635,    2, 0x08 /* Private */,
     101,    1,  638,    2, 0x08 /* Private */,
     102,    0,  641,    2, 0x08 /* Private */,
     103,    0,  642,    2, 0x08 /* Private */,
     104,    0,  643,    2, 0x08 /* Private */,
     105,    1,  644,    2, 0x08 /* Private */,
     107,    0,  647,    2, 0x08 /* Private */,
     108,    0,  648,    2, 0x08 /* Private */,
     109,    1,  649,    2, 0x08 /* Private */,
     111,    0,  652,    2, 0x08 /* Private */,
     112,    0,  653,    2, 0x08 /* Private */,
     113,    0,  654,    2, 0x08 /* Private */,
     114,    0,  655,    2, 0x08 /* Private */,
     115,    0,  656,    2, 0x08 /* Private */,
     116,    0,  657,    2, 0x08 /* Private */,
     117,    0,  658,    2, 0x08 /* Private */,
     118,    0,  659,    2, 0x08 /* Private */,
     119,    1,  660,    2, 0x08 /* Private */,
     121,    0,  663,    2, 0x08 /* Private */,
     122,    2,  664,    2, 0x08 /* Private */,
     126,    2,  669,    2, 0x08 /* Private */,
     131,    2,  674,    2, 0x08 /* Private */,
     136,    1,  679,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 3, 0x80000000 | 5,    4,    6,
    0x80000000 | 8, 0x80000000 | 9, 0x80000000 | 5,   10,   11,
    0x80000000 | 8, 0x80000000 | 13, 0x80000000 | 5,   14,   15,
    0x80000000 | 8, 0x80000000 | 13, 0x80000000 | 5,   14,   15,
    0x80000000 | 8, 0x80000000 | 13, 0x80000000 | 5,   14,   15,
    0x80000000 | 8, 0x80000000 | 13, 0x80000000 | 5,   14,   15,
    QMetaType::Void, 0x80000000 | 3, 0x80000000 | 20, 0x80000000 | 5, 0x80000000 | 5,    4,   21,   22,   23,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,   27,
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void, 0x80000000 | 5,   30,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,   33,
    QMetaType::Void, QMetaType::Int,   30,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,   37,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,   45,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Int, QMetaType::Int,   50,
    QMetaType::Int, QMetaType::Int,   50,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,   58,
    QMetaType::Void, QMetaType::QString,   58,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QByteArray,   70,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,   77,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,   95,
    QMetaType::Void, QMetaType::Int,   95,
    QMetaType::Void, QMetaType::Int,   95,
    QMetaType::Void, QMetaType::Int,   95,
    QMetaType::Void, QMetaType::Int,   95,
    QMetaType::Void, QMetaType::Int,   95,
    QMetaType::Void, QMetaType::Int,   95,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,  106,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Bool,  110,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QPoint,  120,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 123, QMetaType::Int,  124,  125,
    QMetaType::Void, 0x80000000 | 127, 0x80000000 | 129,  128,  130,
    QMetaType::Void, 0x80000000 | 132, 0x80000000 | 134,  133,  135,
    QMetaType::Void, 0x80000000 | 137,  138,

       0        // eod
};

void PressApp::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        PressApp *_t = static_cast<PressApp *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->EOL((*reinterpret_cast< char*(*)>(_a[1])),(*reinterpret_cast< u8(*)>(_a[2]))); break;
        case 1: { u32 _r = _t->crc_chk((*reinterpret_cast< u8*(*)>(_a[1])),(*reinterpret_cast< u8(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< u32*>(_a[0]) = std::move(_r); }  break;
        case 2: { u32 _r = _t->IIR_Filter((*reinterpret_cast< u32*(*)>(_a[1])),(*reinterpret_cast< u8(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< u32*>(_a[0]) = std::move(_r); }  break;
        case 3: { u32 _r = _t->FIR_Filter((*reinterpret_cast< u32*(*)>(_a[1])),(*reinterpret_cast< u8(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< u32*>(_a[0]) = std::move(_r); }  break;
        case 4: { u32 _r = _t->BIQUAD_Filter((*reinterpret_cast< u32*(*)>(_a[1])),(*reinterpret_cast< u8(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< u32*>(_a[0]) = std::move(_r); }  break;
        case 5: { u32 _r = _t->BIQUAD_Filter_1((*reinterpret_cast< u32*(*)>(_a[1])),(*reinterpret_cast< u8(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< u32*>(_a[0]) = std::move(_r); }  break;
        case 6: _t->send_data_order((*reinterpret_cast< char*(*)>(_a[1])),(*reinterpret_cast< const char*(*)>(_a[2])),(*reinterpret_cast< u8(*)>(_a[3])),(*reinterpret_cast< u8(*)>(_a[4]))); break;
        case 7: _t->command_sending_protection(); break;
        case 8: _t->send_gains_and_cals(); break;
        case 9: _t->send_gain((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 10: _t->cal_assignment((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 11: _t->send_new_calibration_values((*reinterpret_cast< u8(*)>(_a[1]))); break;
        case 12: _t->send_calibration_values(); break;
        case 13: _t->cal_channel_change((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 14: _t->tare_channel((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 15: _t->tare_in_calibration(); break;
        case 16: _t->pid_combobox_handle((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 17: _t->save_pid_values(); break;
        case 18: _t->save_pid_values_to_all(); break;
        case 19: _t->step_response_handle(); break;
        case 20: _t->relay_on(); break;
        case 21: _t->relay_off(); break;
        case 22: _t->usart_signalmapper(); break;
        case 23: _t->usart_signalmapper_handler((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 24: _t->usart_gain_signalmapper(); break;
        case 25: _t->print_test_results(); break;
        case 26: _t->_100_msec_handler(); break;
        case 27: { int _r = _t->GetScreenHRes((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 28: { int _r = _t->GetScreenVRes((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 29: _t->setup_GUI(); break;
        case 30: _t->set_declaration(); break;
        case 31: _t->setup_PLOT(); break;
        case 32: _t->setup_users(); break;
        case 33: _t->calculate_area(); break;
        case 34: _t->saveParameters((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 35: _t->readParameters((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 36: _t->on_pushButton_saveResults_clicked(); break;
        case 37: _t->on_pushButton_printResults_clicked(); break;
        case 38: _t->on_pushButton_openFile_view_clicked(); break;
        case 39: _t->on_pushButton_editFile_clicked(); break;
        case 40: _t->on_pushButton_printPlot_clicked(); break;
        case 41: _t->on_pushButton_quitFile_clicked(); break;
        case 42: _t->resize_window(); break;
        case 43: _t->start_comm(); break;
        case 44: _t->end_comm(); break;
        case 45: _t->periodic_response_handler((*reinterpret_cast< QByteArray(*)>(_a[1]))); break;
        case 46: _t->set_test_status(); break;
        case 47: _t->read_parameters_from_the_device(); break;
        case 48: _t->write_parameters_to_the_device(); break;
        case 49: _t->write_specimens_to_the_device(); break;
        case 50: _t->read_specimens_from_the_device(); break;
        case 51: _t->on_toolBox_app_currentChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 52: _t->on_pushButton_toApp_clicked(); break;
        case 53: _t->on_pushButton_connect_clicked(); break;
        case 54: _t->on_pushButton_cutconnect_clicked(); break;
        case 55: _t->on_pushButton_saveFile_clicked(); break;
        case 56: _t->on_pushButton_openFile_clicked(); break;
        case 57: _t->on_pushButton_startTest_clicked(); break;
        case 58: _t->on_pushButton_pauseTest_clicked(); break;
        case 59: _t->on_pushButton_stopTest_clicked(); break;
        case 60: _t->on_pushButton_refreshTest_clicked(); break;
        case 61: _t->on_btn_okSpecimen_clicked(); break;
        case 62: _t->on_btn_expand_clicked(); break;
        case 63: _t->on_pushButton_write_to_device_clicked(); break;
        case 64: _t->on_pushButton_read_from_device_clicked(); break;
        case 65: _t->on_btn_saveSet_clicked(); break;
        case 66: _t->on_pushButton_removeUser_clicked(); break;
        case 67: _t->on_pushButton_load_factory_settings_clicked(); break;
        case 68: _t->on_combo_testType_currentIndexChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 69: _t->on_comboBox_specimen_currentIndexChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 70: _t->on_comboBox_unit_currentIndexChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 71: _t->on_comboBox_unit_ch_currentIndexChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 72: _t->on_combo_scrRes_currentIndexChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 73: _t->on_comboBox_formatFile_currentIndexChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 74: _t->on_comboBox_standard_currentIndexChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 75: _t->assign_frame(); break;
        case 76: _t->assign_controlType(); break;
        case 77: _t->assign_printMode(); break;
        case 78: _t->record_results((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 79: _t->pace_rate_handler_kn(); break;
        case 80: _t->pace_rate_handler_mpa(); break;
        case 81: _t->on_loadFinished((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 82: _t->get_password(); break;
        case 83: _t->on_pushButton_pswSave_clicked(); break;
        case 84: _t->authorization_event(); break;
        case 85: _t->authorize(); break;
        case 86: _t->plot_graph(); break;
        case 87: _t->selectionChanged(); break;
        case 88: _t->mousePress(); break;
        case 89: _t->mouseWheel(); break;
        case 90: _t->contextMenuRequest((*reinterpret_cast< QPoint(*)>(_a[1]))); break;
        case 91: _t->moveLegend(); break;
        case 92: _t->graphClicked((*reinterpret_cast< QCPAbstractPlottable*(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 93: _t->axisLabelDoubleClick((*reinterpret_cast< QCPAxis*(*)>(_a[1])),(*reinterpret_cast< QCPAxis::SelectablePart(*)>(_a[2]))); break;
        case 94: _t->legendDoubleClick((*reinterpret_cast< QCPLegend*(*)>(_a[1])),(*reinterpret_cast< QCPAbstractLegendItem*(*)>(_a[2]))); break;
        case 95: _t->renderPlot((*reinterpret_cast< QPrinter*(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 92:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QCPAbstractPlottable* >(); break;
            }
            break;
        case 93:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QCPAxis* >(); break;
            case 1:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QCPAxis::SelectablePart >(); break;
            }
            break;
        case 94:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 1:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QCPAbstractLegendItem* >(); break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QCPLegend* >(); break;
            }
            break;
        }
    }
}

const QMetaObject PressApp::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_PressApp.data,
      qt_meta_data_PressApp,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *PressApp::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *PressApp::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_PressApp.stringdata0))
        return static_cast<void*>(this);
    return QMainWindow::qt_metacast(_clname);
}

int PressApp::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 96)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 96;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 96)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 96;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
